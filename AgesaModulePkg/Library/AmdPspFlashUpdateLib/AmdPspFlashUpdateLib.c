/* $NoKeywords:$ */
/**
 * @file
 *
 * PSP Flash Access DXE Library
 * It will route the Flash access to SMM libary through SMM communication protocol
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AMD PSP UEFI Driver
 * @e sub-project   PspStorage Library
 * @e \$Revision$   @e \$Date$
 *
 *//*****************************************************************************
 *
 * Copyright (C) 2008-2022 Advanced Micro Devices, Inc. All rights reserved.
 *
 *******************************************************************************
 */
#include <PiDxe.h>
#include <Library/AmdPspFlashAccLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include "AGESA.h"
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/SmmBase2.h>
#include <Filecode.h>

#define FILECODE LIBRARY_AMDPSPFLASHUPDATELIB_AMDPSPFLASHUPDATELIB_FILECODE
#define ALLOCATED_BUFFER_SIZE 0x20000

extern EFI_GUID gSmmFlashUpdateTempBufferAddressProtocolGuid;

EFI_SMM_SYSTEM_TABLE2          *mPspFlashSmst = NULL;
BOOLEAN                        mIsInSmm = FALSE;
UINT8                          *mFlashUpdateTmpBufferProtocol = NULL;
UINT8                          *mTempRuntimeBufferAddress;

/**
 *  Update Flash region with Buffer by step
 *
 *  @param[in]  Address   Address on flash
 *  @param[in]  BlockSize Block Size of flash
 *  @param[in]  Size      Size of the buffer
 *  @param[in]  Buffer    Pointing to the start of the Buffer
 *
 *  @retval EFI_SUCCESS       The Data save to FLASH successfully
 *
 **/
EFI_STATUS
PspUpdateFlashByStep (
  IN       UINT32 Address,
  IN       UINTN  BlockSize,
  IN       UINT32 Size,
  IN       VOID  *Buffer
  )
{
  EFI_STATUS                      Status;
  UINTN                           FlashStartAddr;
  UINTN                           FlashBytes;
  UINT8                           *TempBuffer;
  UINTN                           NumBytes;

  //Make sure the address on the boundary of SPI block size
  FlashStartAddr = Address & (~ (BlockSize - 1));
  if (((Address + Size) % BlockSize) == 0) {
    FlashBytes = ((UINTN) Address + Size) - FlashStartAddr;
  } else {
    FlashBytes = (((UINTN) Address + Size + BlockSize) & (~ (BlockSize - 1))) - FlashStartAddr;
  }
  IDS_HDT_CONSOLE_PSP_TRACE ("Calc FlashAddr %x %x\n", FlashStartAddr, FlashBytes);

  //
  //Get Temp buffer with block size
  //
  TempBuffer = mTempRuntimeBufferAddress;
  IDS_HDT_CONSOLE_PSP_TRACE ("Temp Buffer is 0x%x\n", TempBuffer);

  ASSERT (TempBuffer != NULL);
  if (TempBuffer == NULL) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Temp Buffer is not allocate for Flash update\n");
    return EFI_UNSUPPORTED;
  }
  //Read the block
  //Update the block
  CopyMem (TempBuffer + (Address - FlashStartAddr), Buffer, Size);
  //Erase the blocks
  NumBytes = FlashBytes;
  Status = EFI_UNSUPPORTED;
  Status = PspEraseFlash (FlashStartAddr, &NumBytes);
  ASSERT (NumBytes == FlashBytes);
  ASSERT (Status == EFI_SUCCESS);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  //Write the data
  NumBytes = FlashBytes;
  Status = EFI_UNSUPPORTED;
  Status = PspWriteFlash (FlashStartAddr, &NumBytes, TempBuffer);
  ASSERT (NumBytes == FlashBytes);
  ASSERT (Status == EFI_SUCCESS);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  return EFI_SUCCESS;
}

/**
 *  Update Flash region with Buffer
 *
 *  @param[in]  Address   Address on flash
 *  @param[in]  Size      Size of the buffer
 *  @param[in]  Buffer    Pointing to the start of the Buffer
 *
 *  @retval EFI_SUCCESS       The Data save to FLASH successfully
 *
 **/
EFI_STATUS
PspUpdateFlash (
  IN       UINT32 Address,
  IN       UINT32 Size,
  IN       VOID  *Buffer
  )
  {
  EFI_STATUS                      Status;
  UINTN                           BlockSize;
  UINT32                          AlignedStep;
  UINTN                           FlashStartAddr;
  UINTN                           Gap;
  UINT32                          CopiedSize;
  UINT32                          RemainingSize;

  Status = EFI_UNSUPPORTED;
  IDS_HDT_CONSOLE_PSP_TRACE ("Updating SPI %x %x %x\n", Address, Size, Buffer);

  //Get the block size
  PspGetFlashBlockSize (&BlockSize);
  //Make sure the address on the boundary of SPI block size
  FlashStartAddr = (UINTN)Address & (~(BlockSize - 1));
  Gap = (UINTN)Address - FlashStartAddr;

  AlignedStep = ALLOCATED_BUFFER_SIZE & (~(BlockSize - 1));
  IDS_HDT_CONSOLE_PSP_TRACE("FlashStartAddr: %x BlockSize: %x Step: %x\n", FlashStartAddr, BlockSize, AlignedStep);
  ASSERT(AlignedStep >= BlockSize);

  // if size is small, we can copy all the data in a single step
  if (Gap + (UINTN)Size <= AlignedStep)
  {
    Status = PspUpdateFlashByStep (Address, BlockSize, Size, Buffer);
    ASSERT(Status == EFI_SUCCESS);
    if (EFI_ERROR(Status))
    {
      return Status;
    }
  }
  else // if size is large, we need to copy data in multiple steps
  {
    // copy the buffer head to make the address aligned with flash boundary
    Status = PspUpdateFlashByStep (Address, BlockSize, AlignedStep - (UINT32)Gap, Buffer);
    ASSERT(Status == EFI_SUCCESS);
    if (EFI_ERROR(Status))
    {
      return Status;
    }
    CopiedSize = AlignedStep - (UINT32)Gap;
    RemainingSize = Size - CopiedSize;
    while (RemainingSize > AlignedStep)
    {
      Status = PspUpdateFlashByStep (Address + CopiedSize, BlockSize, AlignedStep, ((UINT8 *)Buffer) + CopiedSize);
      ASSERT(Status == EFI_SUCCESS);
      if (EFI_ERROR (Status))
      {
        return Status;
      }
      CopiedSize += AlignedStep;
      RemainingSize = Size - CopiedSize;
    }
    if (RemainingSize > 0)
    {
      Status = PspUpdateFlashByStep (Address + CopiedSize, BlockSize, RemainingSize, ((UINT8 *)Buffer) + CopiedSize);
      ASSERT (Status == EFI_SUCCESS);
      if (EFI_ERROR (Status))
      {
        return Status;
      }
    }
  }

  IDS_HDT_CONSOLE_PSP_TRACE ("Updated\n");
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
AmdPspFlashUpdateLibConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  UINT8                           *TempBuffer;
  UINTN                           BufferSize;
  EFI_SMM_BASE2_PROTOCOL          *SmmBase2;
  EFI_STATUS                      Status;
  EFI_HANDLE                      Handle;

  //
  // Get InSmm, we need to register SmmReadyToLock if this library is linked to SMM driver.
  //

  Status = gBS->LocateProtocol (&gEfiSmmBase2ProtocolGuid, NULL, (VOID**) &SmmBase2);
  if (!EFI_ERROR (Status)) {
    SmmBase2->InSmm (SmmBase2, &mIsInSmm);
  } else {
    IDS_HDT_CONSOLE_PSP_TRACE ("gEfiSmmBase2ProtocolGuid Locate Fail\n");
  }

  IDS_HDT_CONSOLE_PSP_TRACE ("%a\n", mIsInSmm ? "InSmm" : "OutSmm");

  BufferSize = 0;

  if (mIsInSmm) {
    //
    // Good, we are in SMM
    //
    Status = SmmBase2->GetSmstLocation (SmmBase2, &mPspFlashSmst);
    if (EFI_ERROR (Status)) {
      IDS_HDT_CONSOLE_PSP_TRACE ("GetSmstLocation Fail\n");
      return EFI_SUCCESS;
    }

    //Check if Temp Buffer already allocated by locate SmmProtocol
    Status = mPspFlashSmst->SmmLocateProtocol (&gSmmFlashUpdateTempBufferAddressProtocolGuid, NULL, (VOID **) &TempBuffer);
    if (EFI_ERROR (Status)) {
      //Allocate Temp Buffer
      BufferSize = ALLOCATED_BUFFER_SIZE;
      Status = mPspFlashSmst->SmmAllocatePool (
                       EfiRuntimeServicesData,
                       BufferSize,
                       (VOID **) &TempBuffer
                       );
      ASSERT (TempBuffer != NULL);

      if (TempBuffer == NULL) {
        IDS_HDT_CONSOLE_PSP_TRACE ("SMM Temp Buffer allocated  fail\n");
        return EFI_SUCCESS;
      }

      ZeroMem (TempBuffer, BufferSize);
      mFlashUpdateTmpBufferProtocol = TempBuffer;
      Handle = NULL;
      Status = mPspFlashSmst->SmmInstallProtocolInterface (
                        &Handle,
                        &gSmmFlashUpdateTempBufferAddressProtocolGuid,
                        EFI_NATIVE_INTERFACE,
                        &mFlashUpdateTmpBufferProtocol
                        );
      if (EFI_ERROR (Status)) {
        IDS_HDT_CONSOLE_PSP_TRACE ("SmmInstallProtocolInterface Fail\n");
      }
    }
  }else {
    TempBuffer = (UINT8*)(UINTN) PcdGet64 (PcdFlashUpdateTempRuntimeBufferAddress);
    if (TempBuffer == NULL) {
      //allocate 128k (NVRAM size) shared by DXE driver
      BufferSize = ALLOCATED_BUFFER_SIZE;
      TempBuffer = AllocateRuntimeZeroPool (BufferSize);
      ASSERT (TempBuffer != NULL);
      if (TempBuffer != NULL) {
        PcdSet64 (PcdFlashUpdateTempRuntimeBufferAddress, (UINT64) (UINTN) TempBuffer);
      }else {
        IDS_HDT_CONSOLE_PSP_TRACE ("Temp Buffer allocated fail!\n");
      }
    }
  }
  IDS_HDT_CONSOLE_PSP_TRACE ("Tmp buffer 0x%x; sise 0x%x\n", TempBuffer, BufferSize);
  mTempRuntimeBufferAddress = TempBuffer;
  return EFI_SUCCESS;
}

