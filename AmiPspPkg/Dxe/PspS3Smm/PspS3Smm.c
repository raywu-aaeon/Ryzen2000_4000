//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

//**********************************************************************
//
/** @file PspS3Smm.c
    Save PSP S3 data to Psp S3 Nvram

**/

#include "PspS3Smm.h"
#include "Guid/AmiPsp.h"
#include "Token.h"
#include <Library/AmiBufferValidationLib.h>
#include "Library/AmdPspBaseLibV1.h"


EFI_SMM_SYSTEM_TABLE2           *Smst2 = NULL;
extern  FLASH_PROTOCOL 			AmiAgesaFlashProtocol;
extern  FLASH_PROTOCOL          *AmiPspFlash;



/**
    This function returns base address of PSP S3 NVRAM

  @param Address  The base address of PSP S3 Nvram.

  @retval EFI_SUCCESS Command is handled successfully.

**/
EFI_STATUS
GetPspS3NvBase(
  IN OUT EFI_PHYSICAL_ADDRESS   *Address
)
{
    VOID    *RomPtr;
    UINTN   i;

    RomPtr = (VOID*)((0xFFFFFFFF - FLASH_SIZE + 1) + FCH_FIRMWARE_OFFSET);
    if (((FIRMWARE_ENTRY_TABLE*)RomPtr)->Signature != FIRMWARE_TABLE_SIGNATURE)
        return EFI_NOT_FOUND;  
    
    RomPtr = (VOID*)((FIRMWARE_ENTRY_TABLE*)RomPtr)->PspDirBase;
    for (i = 0; i < ((PSP_DIRECTORY*)RomPtr)->Header.TotalEntries; i++) {
        if (((PSP_DIRECTORY*)RomPtr)->PspEntry[i].Type.Field.Type == PSP_S3_NV_DATA) {
            *Address = ((PSP_DIRECTORY*)RomPtr)->PspEntry[i].Location;
            return  EFI_SUCCESS;
        }
    }
    
    return  EFI_NOT_FOUND;
}

/**
    This function saves the Psp S3 data to Psp S3 Nvram.

  @param DispatchHandle  The unique handle assigned to this handler by SmiHandlerRegister().
  @param Context         Points to an optional handler context which was specified when the
                         handler was registered.
  @param CommBuffer      A pointer to a collection of data in memory that will
                         be conveyed from a non-SMM environment into an SMM environment.
  @param CommBufferSize  The size of the CommBuffer.

  @retval EFI_SUCCESS Command is handled successfully.

**/
EFI_STATUS
SavePspS3DataToNvram (
    IN  EFI_HANDLE      DispatchHandle,
    IN  CONST   VOID    *DispatchContext OPTIONAL,
    IN  OUT VOID        *CommBuffer      OPTIONAL,
    IN  OUT UINTN       *CommBufferSize  OPTIONAL
)
{
    EFI_STATUS      		Status = EFI_SUCCESS;
    EFI_PHYSICAL_ADDRESS    PspS3NvBase = 0;
    UINTN                   EraseSize = 0;
    UINTN                   S3DataSize = 0;
    VOID                    *S3Data = NULL;

    Status = GetPspS3NvBase(&PspS3NvBase);
    if (Status != EFI_SUCCESS)
    {
        DEBUG((DEBUG_ERROR, "WARNING: Unable to get PSP S3 nvram base\n"));
        return EFI_UNSUPPORTED;
    }
    DEBUG((DEBUG_INFO, "\n PspS3NvBase = %lx\n", PspS3NvBase));

    S3Data = CommBuffer;
    S3DataSize = *CommBufferSize;

    Status = AmiValidateMemoryBuffer((VOID*)CommBuffer, *CommBufferSize);
    if (Status != EFI_SUCCESS)
        return  Status;

    DEBUG((DEBUG_INFO, "S3 Data size = %lx\n", S3DataSize));
    EraseSize = S3DataSize;
    if (AmiPspFlash != NULL)
    {
        Status = AmiAgesaFlashProtocol.Erase((VOID*)PspS3NvBase, EraseSize);
        DEBUG((DEBUG_INFO, "\n Flash Erase status = %lx\n", Status));

        Status = AmiAgesaFlashProtocol.Write((VOID*)PspS3NvBase, S3DataSize, S3Data);
        DEBUG((DEBUG_INFO, "\n Flash Write status = %lx\n", Status));
    }

    Smst2->SmiHandlerUnRegister(DispatchHandle);
    DEBUG((DEBUG_INFO, "\n SmiHandlerUnRegister SavePspS3DataToNvram status = %x\n", Status));

    return Status;
}

/**
    Called from InitSmmHandler

    @param

    @retval VOID

**/
EFI_STATUS
EFIAPI
InSmmFunction (
    IN  EFI_HANDLE       ImageHandle,
    IN  EFI_SYSTEM_TABLE *SystemTable
 )
{
    EFI_STATUS  Status;
    EFI_HANDLE  Handle;

    Status = Smst2->SmiHandlerRegister(
                        (VOID *)SavePspS3DataToNvram,
                        &gAmiPspS3SmmCommunicationGuid,
                        &Handle
                        );
    if (EFI_ERROR(Status)) 
    {
        ASSERT_EFI_ERROR(Status);
        return Status;
    }

    return EFI_SUCCESS;
}


/**
    Initializes Psp S3 SMM Drivers.

    @param

    @retval EFI_STATUS

    @note Here is the control flow of this function:
**/

EFI_STATUS
EFIAPI
PspS3SmmInit (
    IN  EFI_HANDLE       ImageHandle,
    IN  EFI_SYSTEM_TABLE *SystemTable
 )
{
    EFI_STATUS              Status;
    EFI_SMM_BASE2_PROTOCOL  *SmmBase2;

    InitAmiSmmLib(ImageHandle, SystemTable);

    Status = pBS->LocateProtocol(&gEfiSmmBase2ProtocolGuid, NULL, (VOID**)&SmmBase2);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    Status = SmmBase2->GetSmstLocation(SmmBase2, &Smst2);
    if (EFI_ERROR(Status)) {
        return EFI_UNSUPPORTED;
    }

    DEBUG ((DEBUG_INFO , "PspS3SmmInit entry\n"));

    return (InitSmmHandler (ImageHandle, SystemTable, InSmmFunction, NULL));
}

//***********************************************************************
//***********************************************************************
//**                                                                   **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.          **
//**                                                                   **
//**                       All Rights Reserved.                        **
//**                                                                   **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093         **
//**                                                                   **
//**                       Phone: (770)-246-8600                       **
//**                                                                   **
//***********************************************************************
//***********************************************************************
