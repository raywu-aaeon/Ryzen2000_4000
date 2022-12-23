
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
#include <Filecode.h>

#define FILECODE PSP_AMDPSPP2CMBOXV2_AMDPSPP2CMBOXCMDV2_FILECODE

extern UINTN                                 mBlockSize;
extern PSP_NV_DESCRIPTOR mPspNvDb[];

EFI_STATUS
GetPspNvDescriptor (
  IN       UINT64 TargetNvId,
     OUT   PSP_NV_DESCRIPTOR **PspNvDescriptor
  )
{
  PSP_NV_DESCRIPTOR *_PspNvDescriptor;
  IDS_HDT_CONSOLE_PSP_TRACE ("GetPspNvDescriptor %x\n", TargetNvId);

  for (_PspNvDescriptor = &mPspNvDb[0]; _PspNvDescriptor->TargetID != SMI_TARGET_END; _PspNvDescriptor++) {
    if (TargetNvId == _PspNvDescriptor->TargetID) {
      if (_PspNvDescriptor->Detected) {
        *PspNvDescriptor = _PspNvDescriptor;
        return EFI_SUCCESS;
      } else {
        IDS_HDT_CONSOLE_PSP_TRACE ("TargetNvId is not Detected\n");
        return EFI_NOT_FOUND;
      }
    }
  }
  IDS_HDT_CONSOLE_PSP_TRACE ("TargetNvId is not in the DB\n");
  return EFI_NOT_FOUND;
}

EFI_STATUS
EFIAPI
P2CmboxSpiGetBlockSize (
  IN OUT   SPI_INFO_REQ *Req
  )
{
  PSP_NV_DESCRIPTOR *PspNvDescriptor;
  EFI_STATUS        Status;
  IDS_HDT_CONSOLE_PSP_TRACE ("Psp.SpiGetBlockSize TargetNvId %x\n", Req->TargetNvId);
  Status = EFI_UNSUPPORTED;
  Status = GetPspNvDescriptor (Req->TargetNvId, &PspNvDescriptor);
  ASSERT (Status == EFI_SUCCESS);
  if (Status != EFI_SUCCESS) {
    return Status;
  }

  ASSERT (PspNvDescriptor->NvRegionBase % mBlockSize == 0);
  Req->BlockSize = mBlockSize;
  Req->NumberOfBlocks = (PspNvDescriptor->NvRegionSize / mBlockSize)? (PspNvDescriptor->NvRegionSize / mBlockSize) : 1;

  IDS_HDT_CONSOLE_PSP_TRACE ("Return Lba:0x%x BlockSize:0x%x NumberOfBlocks:0x%x\n",
         Req->Lba,
         Req->BlockSize,
         Req->NumberOfBlocks);

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
P2CmboxSpiReadFv (
  IN OUT   SPI_RW_REQ *Req
  )
{
  EFI_STATUS Status;
  UINTN NumBytes;
  PSP_NV_DESCRIPTOR *PspNvDescriptor;
  IDS_HDT_CONSOLE_PSP_TRACE ("Psp.SpiReadFv TargetNvId %x Lba:0x%x Offset:0x%x NumByte:0x%x Buffer:0x%x\n",
          Req->TargetNvId,
          Req->Lba,
          Req->Offset,
          Req->NumByte,
          &Req->Buffer);

  Status = EFI_UNSUPPORTED;
  Status = GetPspNvDescriptor (Req->TargetNvId, &PspNvDescriptor);
  ASSERT (Status == EFI_SUCCESS);
  if (Status != EFI_SUCCESS) {
    return Status;
  }

  NumBytes = Req->NumByte;
  IDS_HDT_CONSOLE_PSP_TRACE ("Call FlashAccLib PspReadFlash\n");
  Status = PspReadFlash ( PspNvDescriptor->NvRegionBase + (Req->Lba * mBlockSize) + Req->Offset, &NumBytes, &Req->Buffer[0]);
  IDS_HDT_CONSOLE_PSP_TRACE ("Return Sts=%r, Bytes to read=0x%Xs\n", Status, NumBytes);
  ASSERT (NumBytes == Req->NumByte);
  return (Status);
}

EFI_STATUS
EFIAPI
P2CmboxSpiWriteFv (
  IN OUT   SPI_RW_REQ  *Req
  )
{
  EFI_STATUS Status;
  UINTN NumBytes;
  PSP_NV_DESCRIPTOR *PspNvDescriptor;

  IDS_HDT_CONSOLE_PSP_TRACE ("Psp.SpiWriteFv TargetNvId %x Lba:0x%x Offset:0x%x NumByte:0x%x Buffer:0x%x\n",
          Req->TargetNvId,
          Req->Lba,
          Req->Offset,
          Req->NumByte,
          &Req->Buffer);

  Status = EFI_UNSUPPORTED;
  Status = GetPspNvDescriptor (Req->TargetNvId, &PspNvDescriptor);
  ASSERT (Status == EFI_SUCCESS);
  if (Status != EFI_SUCCESS) {
    return Status;
  }

  NumBytes = Req->NumByte;
  IDS_HDT_CONSOLE_PSP_TRACE ("Call FlashAccLib PspWriteFlash\n");
  Status = PspWriteFlash ( PspNvDescriptor->NvRegionBase + (Req->Lba * mBlockSize) + Req->Offset, &NumBytes, &Req->Buffer[0]);
  IDS_HDT_CONSOLE_PSP_TRACE ("Return Sts=%r, Bytes to write=0x%Xs\n", Status, NumBytes);
  ASSERT (NumBytes == Req->NumByte);



  return (Status);

}

EFI_STATUS
EFIAPI
P2CmboxSpiEraseFv (
  IN OUT   SPI_ERASE_REQ *Req
  )
{
  EFI_STATUS Status;
  UINTN NumBytes;
  PSP_NV_DESCRIPTOR *PspNvDescriptor;

  IDS_HDT_CONSOLE_PSP_TRACE ("Psp.SpiEraseFv TargetNvId 0x%x LBA 0x%x NumBlock 0x%x\n",
        Req->TargetNvId,
        Req->Lba,
        Req->NumberOfBlocks);

  Status = EFI_UNSUPPORTED;
  Status = GetPspNvDescriptor (Req->TargetNvId, &PspNvDescriptor);
  ASSERT (Status == EFI_SUCCESS);
  if (Status != EFI_SUCCESS) {
    return Status;
  }

  NumBytes = Req->NumberOfBlocks * mBlockSize;
  IDS_HDT_CONSOLE_PSP_TRACE ("Call FlashAccLib PspEraseFlash\n");
  Status = PspEraseFlash (PspNvDescriptor->NvRegionBase + (Req->Lba * mBlockSize), &NumBytes);
  IDS_HDT_CONSOLE_PSP_TRACE ("Return Sts=%r, Bytes to erased=0x%Xs\n", Status, NumBytes);
  ASSERT (NumBytes == Req->NumberOfBlocks * mBlockSize);
  return (Status);
}

EFI_STATUS
EFIAPI
P2CmboxSpiRpmcIncMc (
  IN OUT   SPI_RPMC_INC_MC_REQ *Req
  )
{
  EFI_STATUS Status;

  IDS_HDT_CONSOLE_PSP_TRACE ("Psp.SpiRpmcIncMc CounterAddr 0x%x CounterData 0x%x\n",
        Req->CounterAddr,
        Req->CounterData
        );

  Status = EFI_UNSUPPORTED;
  IDS_HDT_CONSOLE_PSP_TRACE ("Call FlashAccLib PspRpmcIncMc\n");
  Status = PspRpmcIncMc ((UINT8) Req->CounterAddr, Req->CounterData, &Req->Signature[0]);
  IDS_HDT_CONSOLE_PSP_TRACE ("Return Sts=%r\n", Status);

  return Status;
}

EFI_STATUS
EFIAPI
P2CmboxSpiRpmcReqMc (
  IN OUT   SPI_RPMC_REQ_MC *Req
  )
{
  EFI_STATUS Status;

  IDS_HDT_CONSOLE_PSP_TRACE ("Psp.SpiRpmcReqMc CounterAddr 0x%x\n", Req->CounterAddr);

  Status = EFI_UNSUPPORTED;
  Req->CounterData = 0;

  IDS_HDT_CONSOLE_PSP_TRACE ("Call FlashAccLib PspRpmcReqMc\n");
  Status = PspRpmcReqMc ((UINT8) Req->CounterAddr, &Req->Tag[0], &Req->Signature[0],
           &Req->CounterData, &Req->OutputSignature[0]);
  IDS_HDT_CONSOLE_PSP_TRACE ("Return Sts[%x] CounterData %x\n", Status, Req->CounterData);
  return Status;
}

#define SPI_SEMAPHORE_ADDR 0xFEC100FCul
#define DriverOwnership BIT4
#define BiosOwnership BIT3
#define ACPIMMIO8(x)  (*(volatile UINT8*)(UINTN)(x))

BOOLEAN
CheckSPIDriverOwnership (
  )
{
  if (ACPIMMIO8 (SPI_SEMAPHORE_ADDR) & DriverOwnership) {
    return TRUE;
  } else {
    return FALSE;
  }
}

BOOLEAN
CheckSPIBiosOwnership (
  )
{
  if (ACPIMMIO8 (SPI_SEMAPHORE_ADDR) & BiosOwnership) {
    return TRUE;
  } else {
    return FALSE;
  }
}

P2C_MBOX_STATUS
EFIAPI
ProcessPspCommand (
  IN UINT64                 Cmd,
  IN MBOX_DEFAULT_BUFFER   *MboxBuffer
  )
{

  P2C_MBOX_STATUS P2cMboxStatus = PSP_MBOX_SUCCESS;
  EFI_STATUS      Status = EFI_SUCCESS;

  // Check SPI BUS ownership before call SPI Library to do the real SPI operation.
  if ((SocFamilyIdentificationCheck (F17_RV_RAW_ID)) || (SocFamilyIdentificationCheck (F17_RV2_RAW_ID)) || (SocFamilyIdentificationCheck (F17_PIC_RAW_ID))) {
    if ((Cmd == MboxPspCmdSpiGetBlockSize) ||
        (Cmd == MboxPspCmdSpiReadFV) ||
        (Cmd == MboxPspCmdSpiWriteFV) ||
        (Cmd == MboxPspCmdSpiEraseFV)) {
      if (CheckSPIBiosOwnership() == TRUE || CheckSPIDriverOwnership() == TRUE) {
        MboxBuffer->Header.Status  = PSP_MBOX_SPI_BUSY_FPR_OWNED;
        return (PSP_MBOX_SPI_BUSY_FPR_OWNED);
      }
    }
  }

  switch (Cmd) {
  case MboxPspCmdSpiGetAttrib:
    AGESA_TESTPOINT (TpPspP2CmboxSpiGetAttribEntry, NULL);
    P2cMboxStatus = PSP_MBOX_SUCCESS;
    break;

  case MboxPspCmdSpiSetAttrib:
    AGESA_TESTPOINT (TpPspP2CmboxSpiSetAttribEntry, NULL);
    P2cMboxStatus = PSP_MBOX_SUCCESS;
    break;

  case MboxPspCmdSpiGetBlockSize :
    AGESA_TESTPOINT (TpPspP2CmboxSpiGetBlockSizeEntry, NULL);
    Status = P2CmboxSpiGetBlockSize ( &(((MBOX_SPI_INFO_BUFFER *)MboxBuffer)->Req) );
    break;

  case MboxPspCmdSpiReadFV:
    AGESA_TESTPOINT (TpPspP2CmboxSpiReadFVEntry, NULL);
    Status = P2CmboxSpiReadFv (&(((MBOX_SPI_RW_BUFFER *)MboxBuffer)->Req));
    break;

  case MboxPspCmdSpiWriteFV:
    AGESA_TESTPOINT (TpPspP2CmboxSpiWriteFVEntry, NULL);
    Status = P2CmboxSpiWriteFv (&(((MBOX_SPI_RW_BUFFER *)MboxBuffer)->Req) );
    break;

  case MboxPspCmdSpiEraseFV:
    AGESA_TESTPOINT (TpPspP2CmboxSpiEraseFVEntry, NULL);
    Status = P2CmboxSpiEraseFv (&(((MBOX_SPI_ERASE_BUFFER *)MboxBuffer)->Req));
    break;

  case MboxPspCmdRpmcIncMc:
    AGESA_TESTPOINT (TpMboxPspCmdRpmcIncMcEntry, NULL);
    Status = P2CmboxSpiRpmcIncMc (&(((MBOX_SPI_RPMC_INC_MC_BUFFER *)MboxBuffer)->Req));
    break;

  case MboxPspCmdRpmcReqMc:
    AGESA_TESTPOINT (TpMboxPspCmdRpmcReqMcEntry, NULL);
    Status = P2CmboxSpiRpmcReqMc (&(((MBOX_SPI_RPMC_REQ_MC_REQ_BUFFER *)MboxBuffer)->Req));
    break;

  case MboxPspCmdRpmcIncMcWrite:
    AGESA_TESTPOINT (TpMboxPspCmdRpmcIncMcWriteEntry, NULL);
    Status = P2CmboxSpiRpmcIncMc (&(((MBOX_SPI_RPMC_INC_MC_WRITE_BUFFER *)MboxBuffer)->McIncReq));
    if (EFI_ERROR (Status)) {
      IDS_HDT_CONSOLE_PSP_TRACE ("RpmcIncMc failed,RpmcIncMcWrite batch CMD abort\n");
      break;
    }
    Status = P2CmboxSpiWriteFv (&(((MBOX_SPI_RPMC_INC_MC_WRITE_BUFFER *)MboxBuffer)->WriteReq));
    break;
  default:
    IDS_HDT_CONSOLE_PSP_TRACE ("Unsupported P2C Command 0x%x\n", Cmd);
    P2cMboxStatus = PSP_MBOX_UNSUPPORTED;
    break;
  }
  // Translate the UEFI error Status to P2C mailbox error status
  if (EFI_ERROR (Status)) {
    P2cMboxStatus = PSP_MBOX_COMMAND_PROCESS_ERROR;
  }

  MboxBuffer->Header.Status  = (UINT32)P2cMboxStatus;

  return (P2cMboxStatus);
}


