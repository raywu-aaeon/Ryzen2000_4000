//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2017, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**             5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093          **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************

/** @file
  Reflash SMM driver.
  
**/

#include <PiSmm.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/AmiBufferValidationLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>

#include <Protocol/AmiNvramUpdate.h>
#include <Protocol/AmiFlash.h>

#include <Token.h>
#include "ReFlashSmm.h"
#include "ReFlashSec.h"

static AMI_SECURE_FLASH_SESSION *Session;

/**
 * @brief Check image signature and version
 *
 * @param Image Pointer to image
 *
 * @return Status of operation
 */
static EFI_STATUS SmmValidateImage (VOID *Image)
{
    EFI_STATUS st;
    AMI_SECURE_FLASH_PROTOCOL *sf;
    UINT8 *p = (UINT8 *)Image;
    
    st = gSmst->SmmLocateProtocol (&ReflashSecureFlashProtocolGuid, NULL, &sf);
    if (!EFI_ERROR (st))
        st = sf->ValidateCapsule (&p, NULL);
    return st;
}

/**
 * @brief Flash image
 *
 * @param Image Image address
 * @param Size Image size
 * @param FbInfo Address of framebuffer descriptor
 *
 * @return Status of operation
 */
static EFI_STATUS SmmUpdateImage (UINT64 Image, UINTN Size, UINT64 FbInfo)
{
    EFI_STATUS st;
    AMI_SECURE_FLASH_PROTOCOL *sf;
    AMI_FLASH_PROTOCOL *af;
    UINT64 src, dst;
    UINT64 tot, rem;
    UINT16 pc;
    AMI_REFLASH_FRAMEBUFFER_INFO *Info = (AMI_REFLASH_FRAMEBUFFER_INFO *)(UINTN)FbInfo;
    
    DrawLogo (Info);
    st = gSmst->SmmLocateProtocol (&ReflashSecureFlashProtocolGuid, NULL, &sf);
    if (st)
        return EFI_UNSUPPORTED;
    
    CopyMem (sf->ReservedBuffer, (VOID *)(UINTN)Image, FLASH_SIZE);
    Session->FlUpdBlock.FlashOpType = 4;	//FlRuntime
    Session->FlUpdBlock.ROMSection = 7;		//nv,bb,main
    Session->FlUpdBlock.FwImage.CapsuleMailboxPtr[0] = 0;
    Session->FlUpdBlock.ImageSize = FLASH_SIZE;
    st = sf->SetFlashUpdateMethod (Session);
    if (st)
        return EFI_SECURITY_VIOLATION;
    
    st = gSmst->SmmLocateProtocol (&gAmiSmmFlashProtocolGuid, NULL, &af);
    if (st)
        return EFI_UNSUPPORTED;
    
    st = af->DeviceWriteEnable ();
    tot = FLASH_SIZE;
    for (src = Image, dst = FLASH_BASE; dst < 0x100000000; src += 0x10000, dst += 0x10000) {
        rem = 0x100000000 - dst;
        pc = (UINT16)((tot - rem) * 100 / tot);
        DrawProgress (Info, pc);
//      st = af->Erase ((VOID *)(UINTN)dst, 0x10000);
//      st = af->Write ((VOID *)(UINTN)dst, 0x10000, (VOID *)(UINTN)src);
        st = af->Update ((VOID *)(UINTN)dst, 0x10000, (VOID *)(UINTN)src);
    }
    st = af->DeviceWriteDisable ();
    return EFI_SUCCESS;	
}

/**
  Dispatch function for a Software SMI handler.

  Caution: This function may receive untrusted input.
  Communicate buffer and buffer size are external input, so this function will do basic validation.

  @param DispatchHandle  The unique handle assigned to this handler by SmiHandlerRegister().
  @param Context         Points to an optional handler context which was specified when the
                         handler was registered.
  @param CommBuffer      A pointer to a collection of data in memory that will
                         be conveyed from a non-SMM environment into an SMM environment.
  @param CommBufferSize  The size of the CommBuffer.

  @retval EFI_SUCCESS Command is handled successfully.

**/
static EFI_STATUS
EFIAPI
ReflashSmmandler (
    IN EFI_HANDLE  DispatchHandle,
    IN CONST VOID  *Context         OPTIONAL,
    IN OUT VOID    *CommBuffer      OPTIONAL,
    IN OUT UINTN   *CommBufferSize  OPTIONAL
    )
{
    AMI_REFLASH_SMM_COMMUNICATE_HEADER *hdr;
    AMI_NVRAM_UPDATE_PROTOCOL *nu;
    EFI_STATUS Status;
    
    if (CommBuffer == NULL || CommBufferSize == NULL)
        return EFI_SUCCESS;
    
    Status = AmiValidateMemoryBuffer(CommBuffer, *CommBufferSize);
    if (EFI_ERROR (Status))
    	return EFI_SUCCESS;
    
    hdr = (AMI_REFLASH_SMM_COMMUNICATE_HEADER *)CommBuffer;
    Status = gSmst->SmmLocateProtocol (&gAmiSmmNvramUpdateProtocolGuid, NULL, &nu);
    if (EFI_ERROR (Status)) {
        hdr->Status = (UINT64) Status;
        return EFI_SUCCESS;
    }
    
    switch (hdr->Action) {
    	case AMI_REFLASH_SMM_UPDATE_NVRAM_IN_BUFFER:
    	case AMI_REFLASH_SMM_UPDATE_NVRAM_IN_PLACE:
            Status = AmiValidateMemoryBuffer((VOID *)(UINTN)hdr->Data[0], (UINTN)hdr->Data[1]);
            if (!EFI_ERROR (Status))
                 Status = nu->UpdateNvram (nu, (VOID *)(UINTN)hdr->Data[0], (UINTN)hdr->Data[1], (BOOLEAN)hdr->Action);
            break;
    	case AMI_REFLASH_SMM_MIGRATE_NVRAM:
            Status = nu->MigrateNvram (nu, hdr->Data[0], hdr->Data[1], (UINTN)hdr->Data[2]);
            break;
    	case AMI_REFLASH_SMM_VALIDATE_IMAGE:
            Status = SmmValidateImage ((VOID *)(UINTN)hdr->Data[0]);
            break;
    	case AMI_REFLASH_SMM_UPDATE_IMAGE:
            Status = SmmUpdateImage (hdr->Data[0], (UINTN)hdr->Data[1], hdr->Data[2]);
            break;
    	default:
            Status = EFI_INVALID_PARAMETER;
            break;
    }
    
    hdr->Status = (UINT64) Status;
    return EFI_SUCCESS;
}

/**
  Entry Point for Reflash SMM driver.

  @param[in] ImageHandle  Image handle of this driver.
  @param[in] SystemTable  A Pointer to the EFI System Table.

  @retval EFI_SUCEESS     
  @return Others          Some error occurs.
**/
EFI_STATUS
EFIAPI
ReFlashSmmEntry (
    IN EFI_HANDLE        ImageHandle,
    IN EFI_SYSTEM_TABLE  *SystemTable
    )
{
    EFI_STATUS Status;
    EFI_HANDLE DispatchHandle;
    static EFI_GUID AmiReflashSmmHandlerGuid = AMI_REFLASH_SMM_HANDLER_GUID;
    
    gBS->AllocatePool (EfiRuntimeServicesData, sizeof (*Session), &Session);
    
    Status = gSmst->SmiHandlerRegister (
                    ReflashSmmandler,
                    &AmiReflashSmmHandlerGuid,
                    &DispatchHandle);
    return Status;
}

//****************************************************************************
//****************************************************************************
//**                                                                        **
//**             (C)Copyright 1985-2017, American Megatrends, Inc.          **
//**                                                                        **
//**                          All Rights Reserved.                          **
//**                                                                        **
//**             5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093          **
//**                                                                        **
//**                          Phone (770)-246-8600                          **
//**                                                                        **
//****************************************************************************
//****************************************************************************
