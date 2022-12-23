/* $NoKeywords:$ */
/**
 * @file
 *
 * PspP2Cmbox Driver
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AMD PSP UEFI Driver
 * @e sub-project   PspP2Cmbox Driver
 * @e \$Revision$   @e \$Date$
 *
 */
/*****************************************************************************
 *
 * Copyright 2008 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
 *
 * AMD is granting you permission to use this software and documentation (if
 * any) (collectively, the "Materials") pursuant to the terms and conditions of
 * the Software License Agreement included with the Materials.  If you do not
 * have a copy of the Software License Agreement, contact your AMD
 * representative for a copy.
 *
 * You agree that you will not reverse engineer or decompile the Materials, in
 * whole or in part, except as allowed by applicable law.
 *
 * WARRANTY DISCLAIMER:  THE MATERIALS ARE PROVIDED "AS IS" WITHOUT WARRANTY OF
 * ANY KIND.  AMD DISCLAIMS ALL WARRANTIES, EXPRESS, IMPLIED, OR STATUTORY,
 * INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE, NON-INFRINGEMENT, THAT THE
 * MATERIALS WILL RUN UNINTERRUPTED OR ERROR-FREE OR WARRANTIES ARISING FROM
 * CUSTOM OF TRADE OR COURSE OF USAGE.  THE ENTIRE RISK ASSOCIATED WITH THE USE
 * OF THE MATERIAL IS ASSUMED BY YOU.  Some jurisdictions do not allow the
 * exclusion of implied warranties, so the above exclusion may not apply to
 * You.
 *
 * LIMITATION OF LIABILITY AND INDEMNIFICATION:  AMD AND ITS LICENSORS WILL
 * NOT, UNDER ANY CIRCUMSTANCES BE LIABLE TO YOU FOR ANY PUNITIVE, DIRECT,
 * INCIDENTAL, INDIRECT, SPECIAL OR CONSEQUENTIAL DAMAGES ARISING FROM USE OF
 * THE MATERIALS OR THIS AGREEMENT EVEN IF AMD AND ITS LICENSORS HAVE BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.  In no event shall AMD's total
 * liability to You for all damages, losses, and causes of action (whether in
 * contract, tort (including negligence) or otherwise) exceed the amount of
 * $100 USD. You agree to defend, indemnify and hold harmless AMD and its
 * licensors, and any of their directors, officers, employees, affiliates or
 * agents from and against any and all loss, damage, liability and other
 * expenses (including reasonable attorneys' fees), resulting from Your use of
 * the Materials or violation of the terms and conditions of this Agreement.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS:  The Materials are provided with
 * "RESTRICTED RIGHTS." Use, duplication, or disclosure by the Government is
 * subject to the restrictions as set forth in FAR 52.227-14 and
 * DFAR252.227-7013, et seq., or its successor.  Use of the Materials by the
 * Government constitutes acknowledgment of AMD's proprietary rights in them.
 *
 * EXPORT RESTRICTIONS: The Materials may be subject to export restrictions as
 * stated in the Software License Agreement.
 *******************************************************************************
 */
#include "AmdPspP2CmboxV2.h"
#include <AmdPspSmmCommunication.h>
#include <Library/S3BootScriptLib.h>
#include <Filecode.h>

#define FILECODE PSP_AMDPSPP2CMBOXV2_AMDPSPP2CMBOXV2_FILECODE

#undef  GET_MASK8
#define GET_MASK8(HighBit, LowBit) ((((UINT8) 1 << (HighBit - LowBit + 1)) - 1) << LowBit)

#undef  GET_MASK16
#define GET_MASK16(HighBit, LowBit) ((((UINT16) 1 << (HighBit - LowBit + 1)) - 1) << LowBit)

#undef  GET_MASK32
#define GET_MASK32(HighBit, LowBit) ((((UINT32) 1 << (HighBit - LowBit + 1)) - 1) << LowBit)

#undef  GET_MASK64
#define GET_MASK64(HighBit, LowBit) ((((UINT64) 1 << (HighBit - LowBit + 1)) - 1) << LowBit)

#define MSR_SMMADDR                 0xC0010112ul
#define MSR_SMMADDR_TSEGBASE_BITS   GET_MASK64 (39, 17)

#define MSR_SMMMASK                 0xC0010113ul
#define MSR_SMMMASK_TSEGMASK_BITS   GET_MASK64 (39, 17)

/// @todo move this out of this file to common place
/// @todo make it customizable via build option etc. Also check the Size of this buffer is
/// sufficient for PSP communication

#define PSP_DATA_BLOCK_SIZE            (8*1024)
#define PSP_DATA_BLOCK_ALIGNMENT       (4*1024)
#define PSP_P2CMBOX_SW_SMI_CALLBACK    0xAD
//#define PSP2BIOS_USING_SW_SMI

#define PSP_SMM_BUFFER_ALIGNMENT    (0x20u) // Must be 32-byte aligned
#define PSP_SMM_BUFFER_PAGES        1u
#define PSP_MBOX_SMM_BUFFER_OFFSET  0u
#define PSP_MBOX_SMM_FLAG_OFFSET    0x00000C00 //Start from 3K

///@todo remove below FCH definition when it has been declared by FCH module
#define ACPIMMIO16(x) (*(volatile UINT16*)(UINTN)(x))
#define ACPIMMIO32(x) (*(volatile UINT32*)(UINTN)(x))
#define ACPI_MMIO_BASE  0xFED80000ul
#define SMI_BASE        0x200   // DWORD
#define PMIO_BASE       0x300   // DWORD
#define FCH_PMIOA_REG6A          0x6A         // AcpiSmiCmd
#define FCH_SMI_REG84            0x84         // SmiStatus1
#define FCH_SMI_REG98            0x98         // SmiTrig
#define FCH_SMI_REGA8            0xA8

///@todo move below assert definition to Ids header file
#define ASSERT_EFI_ERROR(x) ASSERT (!EFI_ERROR (x))

PSP_NV_DESCRIPTOR mPspNvDb[] = {
// TargetID,           Directory,   DirEntryID, Detect, NvRegionBase, NvRegionSize
  {SMI_TARGET_NVRAM, DIR_TYPE_PSP, PSP_NV_DATA, FALSE, 0, 0},
  {SMI_TARGET_TOKEN_UNLOCK, DIR_TYPE_PSP, PSP_TOKEN_UNLOCK_DATA, FALSE, 0, 0},
  {SMI_TARGET_VM_GUARD, DIR_TYPE_PSP, PSP_VM_GUARD_DATA, FALSE, 0, 0},
  {SMI_TARGET_COREMCE_DATA, DIR_TYPE_BIOS, CORE_MCEDATA, FALSE, 0, 0},
  {SMI_TARGET_TEE_WONE_NVRAM, DIR_TYPE_PSP, TEE_WONE_NVRAM,  FALSE, 0, 0},
  {SMI_TARGET_PSP_NVRAM, DIR_TYPE_PSP, PSP_NVRAM,  FALSE, 0, 0},
  {SMI_TARGET_END, DIR_TYPE_END, 0, FALSE, 0, 0},
};

PSP_MBOX_SMMBUFFER_ADDRESS_PROTOCOL mPspMboxSmmBufferAddressProtocol;

UINT64                                mTsegBase = 0;
UINT64                                mTsegMask = 0;
BIOS_MBOX                             *mPspToBiosMbox = NULL;
UINT64                                mPspNvRamRegionBase = 0;
UINT32                                mPspNvRamRegionSize = 0;
UINTN                                 mBlockSize = 0;
EFI_HANDLE                            mPspSmmCommHandle;
extern EFI_GUID gPspFlashAccSmmCommReadyProtocolGuid;

UINT8
Checksum8 (
  IN  UINT8   *Data,
  IN  UINT32  DataSize
  )
{
  UINT32 Index;
  UINT8  Sum;

  Sum = 0;
  for (Index = 0; Index < DataSize; Index++, Data++) {
    Sum += (*Data);
  }
  return Sum;
 }

BOOLEAN
IsValidP2CCommand (
  IN  MBOX_COMMAND     MboxCmd
  )
{
  if ((MboxCmd == MboxPspCmdSpiGetAttrib) ||
      (MboxCmd == MboxPspCmdSpiSetAttrib) ||
      (MboxCmd == MboxPspCmdSpiGetBlockSize) ||
      (MboxCmd == MboxPspCmdSpiReadFV) ||
      (MboxCmd == MboxPspCmdSpiWriteFV) ||
      (MboxCmd == MboxPspCmdSpiEraseFV) ||
      (MboxCmd == MboxPspCmdRpmcIncMc) ||
      (MboxCmd == MboxPspCmdRpmcReqMc) ||
      (MboxCmd == MboxPspCmdRpmcIncMcWrite)
      ) {
    return TRUE;
  }
  return FALSE;
}

EFI_STATUS
CheckMboxValidity (
  IN  BIOS_MBOX *P2CMbox
  )
{
  if ( (P2CMbox == NULL) ||
       (mTsegBase == 0)  ||
       ( (UINT64) P2CMbox < mTsegBase) ||
       (P2CMbox->Buffer.Dflt.Header.TotalSize > PSP_DATA_BLOCK_SIZE ) ||
       (IsValidP2CCommand (P2CMbox->MboxCmd) == FALSE)
      ) {
    return (EFI_INVALID_PARAMETER);
  }
  //Do the checksum calculation if Checksum enabled
  if (P2CMbox->MboxSts.CheckSumEn == TRUE) {
    if (Checksum8 ((UINT8 *) &P2CMbox->Buffer, P2CMbox->Buffer.Dflt.Header.TotalSize) != P2CMbox->MboxSts.CheckSumValue) {
      return (EFI_CRC_ERROR);
    }
  }

  return (EFI_SUCCESS);
}

EFI_STATUS
P2CmboxSmmCallBackWorker (
  VOID
  )
{
  UINT32                MboxCmd;
  MBOX_DEFAULT_BUFFER   *MboxBuffer;
  EFI_STATUS            Status;
  P2C_MBOX_STATUS       P2cStatus;

  Status = EFI_SUCCESS;

  MboxCmd     = mPspToBiosMbox->MboxCmd;
  MboxBuffer  = (MBOX_DEFAULT_BUFFER *)&(mPspToBiosMbox->Buffer.Dflt);
  IDS_HDT_CONSOLE_PSP_TRACE ("\nPsp.P2CMbox Cmd:0x%x >> \n", MboxCmd);

  mPspToBiosMbox->MboxSts.CommandReady = FALSE;
  // basic check. Ignore all the invalid case
  Status = CheckMboxValidity (mPspToBiosMbox);
  IDS_HDT_CONSOLE_PSP_TRACE ("CheckMboxValidity[%x]\n", Status);
  if (EFI_ERROR (Status)) {
    if (Status == EFI_INVALID_PARAMETER) {
      IDS_HDT_CONSOLE_PSP_TRACE ("Invalid parameter\n");
      MboxBuffer->Header.Status = PSP_MBOX_INVALID_PARAMETER;
    } else if (Status == EFI_CRC_ERROR) {
      IDS_HDT_CONSOLE_PSP_TRACE ("Input Buffer CRC fail\n");
      MboxBuffer->Header.Status = PSP_MBOX_CRC_ERROR;
    } else {
      IDS_HDT_CONSOLE_PSP_TRACE ("Unexpected Failure\n");
      MboxBuffer->Header.Status = PSP_MBOX_UNSUPPORTED;
    }
    AGESA_TESTPOINT (TpPspP2CmboxCmdFailExit, NULL);
  } else {
    P2cStatus = ProcessPspCommand (
                MboxCmd,
                MboxBuffer
               );
    if (P2cStatus != PSP_MBOX_SUCCESS) {
      // MboxBuffer->Header.Status = PSP_MBOX_COMMAND_PROCESS_ERROR;
      AGESA_TESTPOINT (TpPspP2CmboxCmdFailExit, NULL);
    } else {
      MboxBuffer->Header.Status = PSP_MBOX_SUCCESS;
      if (mPspToBiosMbox->MboxSts.CheckSumEn == TRUE) {
        //Update checksum field
        mPspToBiosMbox->MboxSts.CheckSumValue = Checksum8 ((UINT8 *) MboxBuffer, MboxBuffer->Header.TotalSize);
      }
      AsmWbinvd ();    // Invalid the cache to make sure DRAM contents has been updated
      AGESA_TESTPOINT (TpPspP2CmboxCmdExit, NULL);
    }
  }

  mPspToBiosMbox->MboxCmd  = 0;     //Clear the command register
  mPspToBiosMbox->MboxSts.CommandReady = TRUE;
  AsmWbinvd ();    // Invalid the cache to make sure DRAM contents has been updated
  IDS_HDT_CONSOLE_PSP_TRACE ("P2CMbox Exit[0x%x]<<\n", MboxBuffer->Header.Status);
  return (Status);
}
//
// Soft SMI handle to repond to sw smi call coming from PSP
//
EFI_STATUS
EFIAPI
P2CmboxSwSmiCallback (
  IN       EFI_HANDLE DispatchHandle,
  IN       CONST FCH_SMM_SW_REGISTER_CONTEXT *DispatchContext,
  IN OUT   FCH_SMM_SW_CONTEXT *SwContext,
  IN OUT   UINTN *SizeOfSwContext
  )
{
  return P2CmboxSmmCallBackWorker ();
}

EFI_STATUS
EFIAPI
P2CmboxMiscSmiCallback (
  IN  EFI_HANDLE                       DispatchHandle,
  IN  FCH_SMM_MISC_REGISTER_CONTEXT   *MiscRegisterContext
  )
{
  EFI_STATUS Status;

  Status = P2CmboxSmmCallBackWorker ();
  ACPIMMIO32 (ACPI_MMIO_BASE + SMI_BASE + FCH_SMI_REG98) &= ~BIT25;  // Deassert fakeSts0

  return Status;
}

EFI_STATUS
InitFchFakeStsInfo (
  IN OUT   SMM_TRIGGER_INFO *SmmTriggerInfoPtr
  )
{
  SmmTriggerInfoPtr->Address = ACPI_MMIO_BASE + SMI_BASE + FCH_SMI_REG98;
  SmmTriggerInfoPtr->AddressType = SMM_TRIGGER_MEM;
  SmmTriggerInfoPtr->ValueWidth = SMM_TRIGGER_DWORD;
  SmmTriggerInfoPtr->ValueAndMask = (UINT32) ~BIT25;
  SmmTriggerInfoPtr->ValueOrMask = BIT25;
  return EFI_SUCCESS;
}

EFI_STATUS
EnablePspFakeStsSmi (
  VOID
  )
{
  FCH_SMM_MISC_DISPATCH_PROTOCOL    *AmdFchSmmMiscDispatch;
  EFI_HANDLE                        MiscHandle;
  FCH_SMM_MISC_REGISTER_CONTEXT     MiscRegisterContext;
  EFI_STATUS                        Status;
  UINT32                            OrMask;
  UINT32                            AndMask;

  // enable PSP SMM via Fake Sts0
  ACPIMMIO32 (ACPI_MMIO_BASE + SMI_BASE + FCH_SMI_REG84) |= BIT1;  //Clear FakeSts0
  OrMask = BIT1;
  AndMask = 0xFFFFFFFFul;
  S3BootScriptSaveMemReadWrite (S3BootScriptWidthUint32, (ACPI_MMIO_BASE + SMI_BASE + FCH_SMI_REG84), &OrMask, &AndMask);

  ACPIMMIO32 (ACPI_MMIO_BASE + SMI_BASE + FCH_SMI_REG98) &= ~BIT25;  // Deassert fakeSts0
  OrMask = 0;
  AndMask = (UINT32) ~BIT25;
  S3BootScriptSaveMemReadWrite (S3BootScriptWidthUint32, (ACPI_MMIO_BASE + SMI_BASE + FCH_SMI_REG98), &OrMask, &AndMask);

  ACPIMMIO32 (ACPI_MMIO_BASE + SMI_BASE + FCH_SMI_REGA8) &= ~(BIT3 + BIT2);  // Enable SMI [3:2] = 1
  ACPIMMIO32 (ACPI_MMIO_BASE + SMI_BASE + FCH_SMI_REGA8) |= BIT2;
  OrMask = BIT2;
  AndMask = (UINT32) ~(BIT3 + BIT2);
  S3BootScriptSaveMemReadWrite (S3BootScriptWidthUint32, (ACPI_MMIO_BASE + SMI_BASE + FCH_SMI_REGA8), &OrMask, &AndMask);


  MiscRegisterContext.SmiStatusReg = FCH_SMI_REG84;
  MiscRegisterContext.SmiStatusBit = BIT1;
  MiscRegisterContext.Order        = 0x80;

  Status = gSmst->SmmLocateProtocol (
                    &gFchSmmMiscDispatchProtocolGuid,
                    NULL,
                    &AmdFchSmmMiscDispatch
                    );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = AmdFchSmmMiscDispatch->Register (
                                      AmdFchSmmMiscDispatch,
                                      &P2CmboxMiscSmiCallback,
                                      &MiscRegisterContext,
                                      &MiscHandle
                                      );

  return Status;
}
EFI_STATUS
EnablePspSwSmi (
  IN OUT   SMM_TRIGGER_INFO *SmmTriggerInfoPtr
  )
{
  EFI_STATUS                      Status;
  FCH_SMM_SW_REGISTER_CONTEXT     SwContext;
  EFI_HANDLE                      SwHandle;
  FCH_SMM_SW_DISPATCH2_PROTOCOL    *SwDispatch;


  //
  //  Get the Sw dispatch protocol
  //
  Status = gSmst->SmmLocateProtocol (
                  &gFchSmmSwDispatch2ProtocolGuid,
                  NULL,
                  &SwDispatch
                  );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  SwContext.AmdSwValue  = PSP_P2CMBOX_SW_SMI_CALLBACK;
  SwContext.Order       = 0x80;
  Status = SwDispatch->Register (
                          SwDispatch,
                          &P2CmboxSwSmiCallback,
                          &SwContext,
                          &SwHandle
                          );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  SmmTriggerInfoPtr->Address = (UINT64) ACPIMMIO16 (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REG6A);
  SmmTriggerInfoPtr->AddressType = SMM_TRIGGER_IO;
  SmmTriggerInfoPtr->ValueWidth = SMM_TRIGGER_BYTE;
  SmmTriggerInfoPtr->ValueAndMask = 0;
  SmmTriggerInfoPtr->ValueOrMask = PSP_P2CMBOX_SW_SMI_CALLBACK;
  IDS_HDT_CONSOLE_PSP_TRACE ("\tSwSmiTriggerReg:0x%x\n", SmmTriggerInfoPtr->Address);

  return EFI_SUCCESS;
}

VOID
InitPspNvDb (
  VOID
  )
{
  PSP_NV_DESCRIPTOR *PspNvDescriptor;
  TYPE_ATTRIB       TypeAttrib;
  UINT64            EntryDest;

  IDS_HDT_CONSOLE_PSP_TRACE ("Initial PSP NV region DB\n");
  for (PspNvDescriptor = &mPspNvDb[0]; PspNvDescriptor->TargetID != SMI_TARGET_END; PspNvDescriptor++) {
    if (PspNvDescriptor->Directory == DIR_TYPE_PSP) {
      PspNvDescriptor->Detected = PSPEntryInfoV2 (
                                      PspNvDescriptor->DirEntryID,
                                      &PspNvDescriptor->NvRegionBase,
                                      &PspNvDescriptor->NvRegionSize
                                      );
    } else if (PspNvDescriptor->Directory == DIR_TYPE_BIOS) {
      PspNvDescriptor->Detected = BIOSEntryInfo (
                                      PspNvDescriptor->DirEntryID,
                                      INSTANCE_IGNORED,
                                      &TypeAttrib,
                                      &PspNvDescriptor->NvRegionBase,
                                      &PspNvDescriptor->NvRegionSize,
                                      &EntryDest
                                      );
    } else {
      ASSERT (FALSE);
    }
    IDS_HDT_CONSOLE_PSP_TRACE ("PSP NV ID[%x] Detected:%x Base:%x Size:%x\n",
                                PspNvDescriptor->DirEntryID,
                                PspNvDescriptor->Detected,
                                PspNvDescriptor->NvRegionBase,
                                PspNvDescriptor->NvRegionSize);
  }
}

EFI_STATUS
EFIAPI
AmdPspP2CmboxEntry (
  IN       EFI_HANDLE         ImageHandle,
  IN       EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS                      Status;
  SMM_REQ_BUFFER                  SmmInfoReq;
  UINT8                           *LocalPspMboxSmmBuffer;
  UINT8                           *PspMboxSmmBuffer;
  BOOLEAN                         *PspMboxSmmFlagAddr;
  EFI_HANDLE                      Handle;

  LocalPspMboxSmmBuffer = NULL;
  PspMboxSmmBuffer = NULL;
  PspMboxSmmFlagAddr = NULL;

  AGESA_TESTPOINT (TpPspP2CmboxV2Entry, NULL);
  //We are now in SMM
  IDS_HDT_CONSOLE_PSP_TRACE ("Psp.Drv.AmdPspP2Cmbox Enter\n");

  //Register SMI communication hanlder to support APOB, APCB region access
  IDS_HDT_CONSOLE_PSP_TRACE ("Register SMM COM Hdlr for PSP NV access\n");
  mPspSmmCommHandle = NULL;
  Status = gSmst->SmiHandlerRegister (PspFlashAccSmmCommunicateHandler, &gPspSmmCommHandleGuid, &mPspSmmCommHandle);

  if (Status == EFI_SUCCESS) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Install PspFlashAccSmmCommReady Protocol\n");
    Handle = NULL;
    Status = gBS->InstallProtocolInterface (
                                  &Handle,
                                  &gPspFlashAccSmmCommReadyProtocolGuid,
                                  EFI_NATIVE_INTERFACE,
                                  NULL
                                  );
    if (EFI_ERROR (Status)) {
      IDS_HDT_CONSOLE_PSP_TRACE ("Install fail\n");
    }
  } else {
    IDS_HDT_CONSOLE_PSP_TRACE ("Register fail\n");
  }
  //Init Blocksize
  PspGetFlashBlockSize (&mBlockSize);

  //If PSP feature turn off, exit the driver
  if ((CheckPspDevicePresentV2 () == FALSE) ||
      (PcdGetBool (PcdAmdPspEnable) == FALSE)) {
    return EFI_SUCCESS;
  }

  // Allocate SMM buffer for PSP-> BIOS communication
  IDS_HDT_CONSOLE_PSP_TRACE ("\tAllocate SMM buffer for P2C Mbox\n");
  mPspToBiosMbox = (BIOS_MBOX  *) AllocateAlignedPages (EFI_SIZE_TO_PAGES (PSP_DATA_BLOCK_SIZE), PSP_DATA_BLOCK_ALIGNMENT);
  ASSERT (mPspToBiosMbox != NULL);
  if (mPspToBiosMbox == NULL) {
    return EFI_SUCCESS;
  }
  // Allocate SMM buffer to hold C2P message after bootdone
  LocalPspMboxSmmBuffer = AllocateAlignedPages(PSP_SMM_BUFFER_PAGES, PSP_SMM_BUFFER_ALIGNMENT);
  ZeroMem (LocalPspMboxSmmBuffer, PSP_SMM_BUFFER_PAGES * EFI_PAGE_SIZE);
  ASSERT (LocalPspMboxSmmBuffer != NULL);
  if (LocalPspMboxSmmBuffer != NULL) {
    //Assign the address for C2P RT buffer, C2P SMM flag
    PspMboxSmmBuffer = LocalPspMboxSmmBuffer + PSP_MBOX_SMM_BUFFER_OFFSET;
    PspMboxSmmFlagAddr = LocalPspMboxSmmBuffer + PSP_MBOX_SMM_FLAG_OFFSET;
    IDS_HDT_CONSOLE_PSP_TRACE ("\tPspMboxSmmBuffer 0x%x\n", PspMboxSmmBuffer);
    IDS_HDT_CONSOLE_PSP_TRACE ("\tPspMboxSmmFlagAddr 0x%x\n", PspMboxSmmFlagAddr);
    //Saving the address through SMM protocol
    Handle = NULL;
    mPspMboxSmmBufferAddressProtocol.PspMboxSmmBuffer = PspMboxSmmBuffer;
    mPspMboxSmmBufferAddressProtocol.PspMboxSmmFlagAddr = PspMboxSmmFlagAddr;
    gSmst->SmmInstallProtocolInterface (
                      &Handle,
                      &gPspMboxSmmBufferAddressProtocolGuid,
                      EFI_NATIVE_INTERFACE,
                      &mPspMboxSmmBufferAddressProtocol
                      );
  }

  //Init PSP DIR NV region info DB
  InitPspNvDb ();

  //
  // Initialize the data structure
  //
  ZeroMem (mPspToBiosMbox, PSP_DATA_BLOCK_SIZE);

  //Align on 32 bytes boundary, init mailbox
  mPspToBiosMbox->MboxCmd      = 0;
  mPspToBiosMbox->MboxSts.CommandReady = TRUE;

  //Prepare SMM_REQ_BUFFER
  ZeroMem (&SmmInfoReq, sizeof (SmmInfoReq));
  SmmInfoReq.PSPSmmDataRegion =   (UINT64) mPspToBiosMbox;
  SmmInfoReq.PspSmmDataLength =   PSP_DATA_BLOCK_SIZE;

  #ifdef PSP2BIOS_USING_SW_SMI
  IDS_HDT_CONSOLE_PSP_TRACE ("P2C using SW SMI\n");
  Status = EnablePspSwSmi (&SmmInfoReq.SmmTrigInfo);
  if (EFI_ERROR (Status)) {
    return EFI_SUCCESS;
  }
  #else
  IDS_HDT_CONSOLE_PSP_TRACE ("P2C using fake SMI\n");
  InitFchFakeStsInfo (&SmmInfoReq.SmmTrigInfo);
  Status = EnablePspFakeStsSmi ();
  if (EFI_ERROR (Status)) {
    return EFI_SUCCESS;
  }
  #endif
  //Get TsegBase, TsegSize
  mTsegBase = AsmReadMsr64 (MSR_SMMADDR);
  mTsegBase &= MSR_SMMADDR_TSEGBASE_BITS;

  mTsegMask = AsmReadMsr64 (MSR_SMMMASK);
  // mTsegMask = (~(mTsegMask & MSR_SMMMASK_TSEGMASK_BITS) + 1) & MSR_SMMMASK_TSEGMASK_BITS;
  SmmInfoReq.SMMBase = mTsegBase;
  SmmInfoReq.SMMMask = mTsegMask;
  IDS_HDT_CONSOLE_PSP_TRACE ("\tSMMBase:0x%x SMMMask:0x%x\n\tPSPSmmDataRegion:0x%x PspSmmDataLength:0x%x\n", mTsegBase, mTsegMask, mPspToBiosMbox, PSP_DATA_BLOCK_SIZE);
  //Fill SmmRegisterInfo
  SmmInfoReq.SmmRegInfo.SmiEnb.Address = ACPI_MMIO_BASE + SMI_BASE + FCH_SMI_REG98;
  SmmInfoReq.SmmRegInfo.SmiEnb.AddressType = SMM_TRIGGER_MEM;
  SmmInfoReq.SmmRegInfo.SmiEnb.ValueWidth = SMM_TRIGGER_DWORD;
  SmmInfoReq.SmmRegInfo.SmiEnb.RegBitMask = BIT31;
  SmmInfoReq.SmmRegInfo.SmiEnb.ExpectValue = 0;

  SmmInfoReq.SmmRegInfo.Eos.Address = ACPI_MMIO_BASE + SMI_BASE + FCH_SMI_REG98;
  SmmInfoReq.SmmRegInfo.Eos.AddressType = SMM_TRIGGER_MEM;
  SmmInfoReq.SmmRegInfo.Eos.ValueWidth = SMM_TRIGGER_DWORD;
  SmmInfoReq.SmmRegInfo.Eos.RegBitMask = BIT28;
  SmmInfoReq.SmmRegInfo.Eos.ExpectValue = BIT28;

  SmmInfoReq.SmmRegInfo.FakeSmiEn.Address = ACPI_MMIO_BASE + SMI_BASE + FCH_SMI_REGA8;
  SmmInfoReq.SmmRegInfo.FakeSmiEn.AddressType = SMM_TRIGGER_MEM;
  SmmInfoReq.SmmRegInfo.FakeSmiEn.ValueWidth = SMM_TRIGGER_DWORD;
  SmmInfoReq.SmmRegInfo.FakeSmiEn.RegBitMask = BIT3 + BIT2;
  SmmInfoReq.SmmRegInfo.FakeSmiEn.ExpectValue = BIT2;

  // After command MBOX_C2P_BOOT_DONE (6), any subsequent commands have to have a command buffer
  // placed in the area started with the BiosSmmCmdBufAddr address provided by the command MBOX_SMI_INFO_BUFFER.
  // And the contents inside the word addressed by the BiosSmmFlagAddr should be non-0, indicating the CPU is in SMM mode
  SmmInfoReq.PspMboxSmmBufferAddress = (UINT64) (UINTN) PspMboxSmmBuffer;
  SmmInfoReq.PspMboxSmmFlagAddress = (UINT64) (UINTN) PspMboxSmmFlagAddr;

  PspMboxBiosCmdSmmInfo (
        &SmmInfoReq
        );

  IDS_HDT_CONSOLE_PSP_TRACE ("AmdPspP2Cmbox Exit\n");
  AGESA_TESTPOINT (TpPspP2CmboxV2Exit, NULL);

  return EFI_SUCCESS;
}


