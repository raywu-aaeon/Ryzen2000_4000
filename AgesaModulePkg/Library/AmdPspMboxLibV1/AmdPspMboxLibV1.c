/* $NoKeywords:$ */
/**
 * @file
 *
 * PSP Mailbox related functions
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  PSP
 * @e \$Revision: 319679 $   @e \$Date: 2015-06-01 14:52:21 +0800 (Mon, 01 Jun 2015) $
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
 **/
#include <Library/BaseMemoryLib.h>
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Library/AmdPspMboxLibV1.h>
#include <Filecode.h>

#define FILECODE LIBRARY_AMDPSPMBOXLIBV1_AMDPSPMBOXLIBV1_FILECODE

/**
  Return the PspMbox MMIO location


  @retval EFI_STATUS  0: Success, NonZero Error

**/
EFI_STATUS
GetPspMboxLocation (
  IN OUT   PSP_MBOX **PspMbox
  )
{
  UINT32 PspMmio;

  if (GetPspBar3Addr (&PspMmio) == FALSE) {
    return (EFI_UNSUPPORTED);
  }

  *PspMbox = (PSP_MBOX *)( (UINTN)PspMmio + PSP_MAILBOX_BASE);   // PSPMbox base is at offset CP2MSG_28 ie. offset 28*4 = 0x70

  return (EFI_SUCCESS);
}


/**
  BIOS sends command to PSP

  @param[in]  MboxBuffer        PSP mbox buffer
  @param[in]  Cmd               Psp Mailbox Command

  @retval BOOLEAN                0: Success, 1 Error

**/
/// @todo Change function to some status type and appropriate status
/// Also add code in caller to handle this change
BOOLEAN
SendPspCommand (
  IN       VOID       *MboxBuffer,
  IN       MBOX_COMMAND       Cmd
  )
{
  UINT32     Command;
  BOOLEAN    Status;
  PSP_MBOX   *PspMbox;
  Status = TRUE;
  PspMbox = NULL;

  IDS_HDT_CONSOLE_PSP_TRACE ("Psp.SendC2PCMD [0x%x]\n", Cmd);

  // Get PspMbox location. fail if not found
  if (EFI_ERROR (GetPspMboxLocation (&PspMbox))) {
    IDS_HDT_CONSOLE_PSP_TRACE ("GetPspMboxLocation Error\n");
    ASSERT (FALSE); // Assertion in the debug build
    return (FALSE);
  }

  // The Command register may be disable by PSP driver when entering D3.
  // Save Command register
  Command = PspLibPciReadPspConfig (PSP_PCI_CMD_REG);
   //Enable BusMaster & MemAccess
  PspLibPciWritePspConfig (PSP_PCI_CMD_REG, Command | 0x6);

  if (PspMbox->MboxSts.Halt) {
    IDS_HDT_CONSOLE_PSP_TRACE ("MboxSts Halt\n");
    ASSERT (FALSE); // Assertion in the debug build
    //Restore Command register
    PspLibPciWritePspConfig (PSP_PCI_CMD_REG, Command);
    return (FALSE);
  }

  if (PspMbox->MboxSts.Recovery) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Recovery Flag detected, ignore the command\n");
    //Restore Command register
    PspLibPciWritePspConfig (PSP_PCI_CMD_REG, Command);
    return (FALSE);
  }

  AGESA_TESTPOINT (TpPspC2PmboxBeforeSendCmdBase + Cmd, NULL);

  // Wait till mailbox is initialized or done processing command
  /// Wait for PSP to be ready. @todo add timeout
  while ( (!PspMbox->MboxSts.MboxInitialized) ||  (PspMbox->MboxCmd)) {
    ;
  }

  // Now send the command
  PspMbox->Buffer = (MBOX_BUFFER *)MboxBuffer;
  PspMbox->MboxCmd = Cmd;

  AGESA_TESTPOINT (TpPspC2PmboxWaitCmdBase + Cmd, NULL);

  /// Wait for PSP to be done or reflect error @todo add timeout
  while (PspMbox->MboxCmd) {
    ;
  }

  // error vs. terminated
  if (PspMbox->MboxSts.Error || PspMbox->MboxSts.Terminated) {
    IDS_HDT_CONSOLE_PSP_TRACE ("MboxSts Error\n");
    Status = FALSE;
  }
  //Restore Command register
  PspLibPciWritePspConfig (PSP_PCI_CMD_REG, Command);
  return Status;

}


/**
  BIOS sends the DRAM ready message to PSP.

  @retval EFI_STATUS              0: Success, NonZero Error
**/
EFI_STATUS
PspMboxBiosCmdDramInfo (
  )
{
  UNALIGNED_MBOX_BUFFER   UBuff;    // Unaligned buffer
  MBOX_DEFAULT_BUFFER     *Buffer;  // Pointer to aligned buffer in stack

  Buffer = BALIGN32 (&UBuff);
  ZeroMem (&UBuff, sizeof (UNALIGNED_MBOX_BUFFER));

  IDS_HDT_CONSOLE_PSP_TRACE ("Psp.C2PMbox.DramInfo\n");

  Buffer->Header.TotalSize      = sizeof (MBOX_DEFAULT_BUFFER);

  SendPspCommand (Buffer, MboxBiosCmdDramInfo);
  IDS_HDT_CONSOLE_PSP_TRACE ("Mbox.Hdr.Sts:0x%x\n", Buffer->Header.Status);
  return (Buffer->Header.Status);
}

/**
 *
 *
 * Bios send this command to inform PSP to save the data needed to restore SRAM during resume from S3
 *
 * @param[in]  S3RestoreBufferBase           PSP reserve memory base near TOM
 * @param[in]  S3RestoreBufferSize           Size of PSP memory
 * @param[in,out]  Hmac                      Hmac value for S3RestoreBufferBase with S3RestoreBufferSize
 *
 * @retval EFI_STATUS              0: Success, NonZero Error
 *
 */
EFI_STATUS
PspMboxBiosCmdS3Info (
  IN       UINT64 S3RestoreBufferBase,
  IN       UINT64 S3RestoreBufferSize,
  IN OUT   UINT8 *Hmac
   )
{
  UNALIGNED_MBOX_BUFFER   UBuff;    // Unaligned buffer
  MBOX_S3DATA_BUFFER      *Buffer;

  Buffer = BALIGN32 (&UBuff);
  ZeroMem (&UBuff, sizeof (UNALIGNED_MBOX_BUFFER));

  IDS_HDT_CONSOLE_PSP_TRACE ("Psp.C2PMbox.S3Info\n");

  Buffer->Header.TotalSize      = sizeof (MBOX_S3DATA_BUFFER);

  Buffer->Req.S3RestoreBufferBase  = S3RestoreBufferBase;
  Buffer->Req.S3RestoreBufferSize  = S3RestoreBufferSize;
  ZeroMem (&Buffer->Req.Hmac, S3_RESTORE_BUFFER_HMAC_SIZE);
  SendPspCommand (Buffer, MboxBiosS3DataInfo);
  CopyMem (Hmac, &Buffer->Req.Hmac, S3_RESTORE_BUFFER_HMAC_SIZE);
  IDS_HDT_CONSOLE_PSP_TRACE ("Mbox.Hdr.Sts:0x%x\n", Buffer->Header.Status);
  return (Buffer->Header.Status);
}

/**
  BIOS sends the SMM information to PSP. SMM information is used by PSP to pass data back to BIOS

  @param[in]  SMMBase             Location of SMM base (TSEG)

  @param[in]  SMMLength           Length/Size of SMM space (TSEG)

  @param[in]  PSPSmmDataRegion    Location of reserved PSPSmmDataRegion within the SMM space.
                                  PSP will use this region to communicate with BIOS (i.e pass
                                  data/command at this region for BIOS SMM to process)

  @param[in]  PspSmmDataLength    Length of reserve PSPSmmDataRegion in SMM space for PSP communication

  @param[in]  SmmTrigInfo  IO port address to generate SoftSmi

  @retval EFI_STATUS              0: Success, NonZero Error

**/
EFI_STATUS
PspMboxBiosCmdSmmInfo (
  IN UINT64            SMMBase,
  IN UINT64            SMMLength,
  IN UINT64            PSPSmmDataRegion,
  IN UINT64            PspSmmDataLength,
  IN SMM_TRIGGER_INFO  *SmmTrigInfo,
  IN UINT64            PspMboxSmmBufferAddress,
  IN UINT64            PspMboxSmmFlagAddress
  )
{
  MBOX_SMM_BUFFER    *Buffer;
  UNALIGNED_MBOX_BUFFER   UBuff;    // Unaligned buffer

  Buffer = BALIGN32 (&UBuff);
  ZeroMem (&UBuff, sizeof (UNALIGNED_MBOX_BUFFER));

  IDS_HDT_CONSOLE_PSP_TRACE ("Psp.C2PMbox.SmmInfo\n");

  Buffer->Header.TotalSize             = sizeof (MBOX_SMM_BUFFER);

  Buffer->Req.SMMBase                  = SMMBase;
  Buffer->Req.SMMLength                = SMMLength;
  Buffer->Req.PSPSmmDataRegion         = PSPSmmDataRegion;
  Buffer->Req.PspSmmDataLength         = PspSmmDataLength;

  Buffer->Req.SmmTrigInfo.AddressType  = SmmTrigInfo->AddressType;
  Buffer->Req.SmmTrigInfo.Address      = SmmTrigInfo->Address;
  Buffer->Req.SmmTrigInfo.ValueWidth   = SmmTrigInfo->ValueWidth;
  Buffer->Req.SmmTrigInfo.ValueAndMask = SmmTrigInfo->ValueAndMask;
  Buffer->Req.SmmTrigInfo.ValueOrMask  = SmmTrigInfo->ValueOrMask;
  Buffer->Req.PspMboxSmmBufferAddress  = PspMboxSmmBufferAddress;
  Buffer->Req.PspMboxSmmFlagAddress    = PspMboxSmmFlagAddress;

  SendPspCommand (Buffer, MboxBiosCmdSmmInfo);
  IDS_HDT_CONSOLE_PSP_TRACE ("Mbox.Hdr.Sts:0x%x\n", Buffer->Header.Status);
  return (Buffer->Header.Status);

}


/**
  BIOS sends the Sx information to PSP. This mailbox command is send just prior of entering Sx state

  @param[in]  SleepType           SleepType the system is transition to.
                                    3 : S3, 4:S4, 5:S5

  @retval EFI_STATUS              0: Success, NonZero Error
**/
EFI_STATUS
PspMboxBiosCmdSxInfo (
  IN UINT8 SleepType,
  IN UINT8     *SmmBuffer,
  IN BOOLEAN   *SmmFlag
  )
{
  EFI_STATUS        Status;
  MBOX_SX_BUFFER    *Buffer;
  BOOLEAN CmdSts;

  CmdSts = FALSE;
  Status = EFI_INVALID_PARAMETER;
  Buffer = NULL;
  IDS_HDT_CONSOLE_PSP_TRACE ("Psp.C2PMbox.SxInfo\n");
  if ((SmmBuffer != NULL) && (SmmFlag != NULL)) {
    IDS_HDT_CONSOLE_PSP_TRACE ("SmmBuffer: %x\n",  SmmBuffer);
    IDS_HDT_CONSOLE_PSP_TRACE ("SmmFlag: %x\n",  SmmFlag);
    Buffer = (MBOX_SX_BUFFER*)SmmBuffer;
    ZeroMem (Buffer, sizeof (MBOX_SX_BUFFER));
    Buffer->Header.TotalSize      = sizeof (MBOX_SX_BUFFER);
    Buffer->Req.SleepType        = SleepType;
    *SmmFlag = TRUE;
    CmdSts = SendPspCommand (Buffer, MboxBiosCmdSxInfo);
    *SmmFlag = FALSE;
    if (CmdSts == FALSE) {
      return EFI_DEVICE_ERROR;
    }
    IDS_HDT_CONSOLE_PSP_TRACE ("Mbox.Hdr.Sts:0x%x\n", Buffer->Header.Status);
    Status = (Buffer->Header.Status) ? EFI_DEVICE_ERROR : EFI_SUCCESS;
  }
  return Status;

}

/**
  BIOS sends the Resume information to PSP. PSP will use this information to measure the resume code.
  During resume path PSP will use this information before handing off to BIOS to ensure the resume
  code is not tampered

  @param[in]  S3ResumeAddress       Location of BIOS reset code that will first fetch on resume

  @param[in]  S3ResumeCodeSize      Size of resume code that PSP need to measure to ensure authenticity

  @retval EFI_STATUS              0: Success, NonZero Error
**/
EFI_STATUS
PspMboxBiosCmdResumeInfo (
  IN UINT64 S3ResumeAddress,
  IN UINT64 S3ResumeCodeSize
  )
{
  MBOX_RSM_BUFFER    *Buffer;
  UNALIGNED_MBOX_BUFFER   UBuff;    // Unaligned buffer

  Buffer = BALIGN32 (&UBuff);
  ZeroMem (&UBuff, sizeof (UNALIGNED_MBOX_BUFFER));

  IDS_HDT_CONSOLE_PSP_TRACE ("Psp.C2PMbox.ResumeInfo\n");

  Buffer->Header.TotalSize      = sizeof (MBOX_RSM_BUFFER);

  Buffer->Req.ResumeVecorAddress = S3ResumeAddress;
  Buffer->Req.ResumeVecorLength  = S3ResumeCodeSize;

  SendPspCommand (Buffer, MboxBiosCmdRsmInfo);
  IDS_HDT_CONSOLE_PSP_TRACE ("Mbox.Hdr.Sts:0x%x\n", Buffer->Header.Status);
  return (Buffer->Header.Status);
}


/**
  BIOS sends this command to inform PSP that BIOS is handing off to OS/OROM. Any mailbox command
  after this message need to come from SMM space (the SMM info is provided earlier via mailbox)
  i.e. PSP should check the parameter address to ensure it falls in SMM region

  @retval EFI_STATUS              0: Success, NonZero Error
**/
EFI_STATUS
PspMboxBiosCmdExitBootServices ()
{
  MBOX_DEFAULT_BUFFER     *Buffer;
  UNALIGNED_MBOX_BUFFER   UBuff;    // Unaligned buffer

  Buffer = BALIGN32 (&UBuff);
  ZeroMem (&UBuff, sizeof (UNALIGNED_MBOX_BUFFER));

  IDS_HDT_CONSOLE_PSP_TRACE ("Psp.C2PMbox.ExitBootServices\n");

  Buffer->Header.TotalSize      = sizeof (MBOX_DEFAULT_BUFFER);

  SendPspCommand (Buffer, MboxBiosCmdBootDone);
  IDS_HDT_CONSOLE_PSP_TRACE ("Mbox.Hdr.Sts:0x%x\n", Buffer->Header.Status);
  return (Buffer->Header.Status);
}

/**
  BIOS requests the capabilities from the PSP

  @param[in]  Capabilities      PSP Writes capabilities into this field when it returns.

  @retval EFI_STATUS                0: Success, NonZero Error

**/
EFI_STATUS
PspMboxBiosQueryCaps (
  IN OUT   UINT32 *Capabilities
  )
{
  MBOX_CAPS_BUFFER   *Buffer;
  UNALIGNED_MBOX_BUFFER   UBuff;    // Unaligned buffer

  Buffer = BALIGN32 (&UBuff);
  ZeroMem (&UBuff, sizeof (UNALIGNED_MBOX_BUFFER));

  IDS_HDT_CONSOLE_PSP_TRACE ("Psp.PspMboxBiosQueryCaps\n");

  if (Capabilities == NULL) {
    return (EFI_NOT_FOUND);
  }

  Buffer->Header.TotalSize      = sizeof (MBOX_CAPS_BUFFER);

  Buffer->Req.Capabilities      = 1; // 1 to identify the command is sending from V9

  SendPspCommand (Buffer, MboxBiosCmdPspQuery);
  *Capabilities = Buffer->Req.Capabilities;
  IDS_HDT_CONSOLE_PSP_TRACE ("Mbox.Hdr.Sts:0x%x\n", Buffer->Header.Status);
  return (Buffer->Header.Status);
}


/**
  BIOS sends this dummy command to inform PSP that its done processing the SMM request
  The purpose of this command is to generate interrupt to PSP

  @retval EFI_STATUS              0: Success, NonZero Error
**/
EFI_STATUS
PspMboxBiosCmdNop ()
{
  MBOX_DEFAULT_BUFFER     *Buffer;
  UNALIGNED_MBOX_BUFFER   UBuff;    // Unaligned buffer

  Buffer = BALIGN32 (&UBuff);
  ZeroMem (&UBuff, sizeof (UNALIGNED_MBOX_BUFFER));

  IDS_HDT_CONSOLE_PSP_TRACE ("Psp.C2PMbox.Nop\n");

  Buffer->Header.TotalSize      = sizeof (MBOX_DEFAULT_BUFFER);

  SendPspCommand (Buffer, MboxBiosCmdNop);
  IDS_HDT_CONSOLE_PSP_TRACE ("Mbox.Hdr.Sts:0x%x\n", Buffer->Header.Status);
  return (Buffer->Header.Status);

}
/**
  BIOS sends the clear S3 Status message to PSP.

  @retval EFI_STATUS              0: Success, NonZero Error
**/
EFI_STATUS
PspMboxBiosClearS3Status (
  IN UINT8     *SmmBuffer,
  IN BOOLEAN   *SmmFlag
  )
{
  EFI_STATUS              Status;
  MBOX_DEFAULT_BUFFER     *Buffer;
  BOOLEAN CmdSts;

  CmdSts = FALSE;
  Status = EFI_INVALID_PARAMETER;
  Buffer = NULL;
  IDS_HDT_CONSOLE_PSP_TRACE ("Psp.C2PMbox.ClearS3Sts\n");
  if ((SmmBuffer != NULL) && (SmmFlag != NULL)) {
    IDS_HDT_CONSOLE_PSP_TRACE ("SmmBuffer: %x\n",  SmmBuffer);
    IDS_HDT_CONSOLE_PSP_TRACE ("SmmFlag: %x\n",  SmmFlag);
    Buffer = (MBOX_DEFAULT_BUFFER *) SmmBuffer;
    ZeroMem (Buffer, sizeof (MBOX_DEFAULT_BUFFER));
    Buffer->Header.TotalSize      = sizeof (MBOX_DEFAULT_BUFFER);
    *SmmFlag = TRUE;
    CmdSts = SendPspCommand (Buffer, MboxBiosCmdClearS3Sts);
    *SmmFlag = FALSE;
    if (CmdSts == FALSE) {
      return EFI_DEVICE_ERROR;
    }
    IDS_HDT_CONSOLE_PSP_TRACE ("Mbox.Hdr.Sts:0x%x\n", Buffer->Header.Status);
    Status = (Buffer->Header.Status) ? EFI_DEVICE_ERROR : EFI_SUCCESS;
  }
  return Status;
}
/**
  BIOS requests the HSTI state from the PSP

  @param[in]  HSTIState             PSP Writes HSTIState into this field when it returns.

  @retval EFI_STATUS                0: Success, NonZero Error

**/
EFI_STATUS
PspMboxBiosQueryHSTIState (
  IN OUT   UINT32 *HSTIState
  )
{
  MBOX_HSTI_STATE   *Buffer;
  UNALIGNED_MBOX_BUFFER   UBuff;    // Unaligned buffer

  Buffer = BALIGN32 (&UBuff);
  ZeroMem (&UBuff, sizeof (UNALIGNED_MBOX_BUFFER));

  IDS_HDT_CONSOLE_PSP_TRACE ("Psp.PspMboxBiosQueryHSTIState\n");

  if (HSTIState == NULL) {
    return (EFI_NOT_FOUND);
  }

  Buffer->Header.TotalSize = sizeof (MBOX_HSTI_STATE);

  Buffer->HSTIState = 0; // Result of command will be placed here

  SendPspCommand (Buffer, MboxBiosCmdHSTIQuery);
  *HSTIState = Buffer->HSTIState;
  IDS_HDT_CONSOLE_PSP_TRACE ("Mbox.Hdr.Sts:0x%x HSTIState:0x%x\n", Buffer->Header.Status, Buffer->HSTIState);
  return (Buffer->Header.Status);
}
/**
  BIOS sends the message to PSP for clear SmmLock bit in C6 private region

  @retval EFI_STATUS              0: Success, NonZero Error
**/
EFI_STATUS
PspMboxBiosClearSmmLock (
  )
{
  MBOX_DEFAULT_BUFFER     *Buffer;
  UNALIGNED_MBOX_BUFFER   UBuff;    // Unaligned buffer

  Buffer = BALIGN32 (&UBuff);
  ZeroMem (&UBuff, sizeof (UNALIGNED_MBOX_BUFFER));

  IDS_HDT_CONSOLE_PSP_TRACE ("Psp.C2PMbox.ClearSmmLock\n");

  Buffer->Header.TotalSize      = sizeof (MBOX_DEFAULT_BUFFER);

  SendPspCommand (Buffer, MboxBiosCmdClrSmmLock);
  IDS_HDT_CONSOLE_PSP_TRACE ("Mbox.Hdr.Sts:0x%x\n", Buffer->Header.Status);
  return (Buffer->Header.Status);
}

/**
  BIOS sends the message to PSP for PCIE device information

  @retval EFI_STATUS              0: Success, NonZero Error
**/
EFI_STATUS
PspMboxBiosPcieInfo (
  UINT32              DevId,
  PCI_ADDR            Address
  )
{
  MBOX_PCIE_INFO_BUFFER     *Buffer;
  UNALIGNED_MBOX_BUFFER   UBuff;    // Unaligned buffer

  Buffer = BALIGN32 (&UBuff);
  ZeroMem (&UBuff, sizeof (UNALIGNED_MBOX_BUFFER));

  IDS_HDT_CONSOLE_PSP_TRACE ("Psp.C2PMbox.PspMboxBiosPcieInfo DevId:%x Address:%x\n", DevId, Address.AddressValue);

  Buffer->Header.TotalSize      = sizeof (MBOX_PCIE_INFO_BUFFER);
  Buffer->Header.Status         = 0;
  Buffer->Info.DevId            = DevId;
  Buffer->Info.Address          = Address;

  SendPspCommand (Buffer, MboxBiosCmdPcieInfo);
  IDS_HDT_CONSOLE_PSP_TRACE ("Mbox.Hdr.Sts:0x%x\n", Buffer->Header.Status);
  return (Buffer->Header.Status);
}

/**
  BIOS sends TA command to PSP

  @retval EFI_STATUS              0: Success, NonZero Error
**/
TEE_STATUS
PspMboxBiosTa (
  UINT64              TaCmdBufferAddress,
  UINT64              TaCmdBufferSize
  )
{
  MBOX_TA     *Buffer;
  UNALIGNED_MBOX_BUFFER   UBuff;    // Unaligned buffer

  Buffer = BALIGN32 (&UBuff);
  ZeroMem (&UBuff, sizeof (UNALIGNED_MBOX_BUFFER));

  IDS_HDT_CONSOLE_PSP_TRACE ("Psp.C2PMbox.PspMboxBiosTa Buffer:%x Size:%x\n", TaCmdBufferAddress, TaCmdBufferSize);

  Buffer->Header.TotalSize      = sizeof (MBOX_TA);
  Buffer->Header.Status         = 0;
  Buffer->TaCmdBufferAddress = TaCmdBufferAddress;
  Buffer->TaCmdBufferSize    = TaCmdBufferSize;

  SendPspCommand (Buffer, MboxBiosCmdTa);
  IDS_HDT_CONSOLE_PSP_TRACE ("Mbox.Hdr.Sts:0x%x\n", Buffer->Header.Status);
  return (Buffer->Header.Status);
}

/**
  Check if Ftpm is ready

  @retval EFI_STATUS  0: Success, NonZero Error

**/
EFI_STATUS
CheckFtpmCapsV1 (
  IN OUT   UINT32 *Caps
  )
{
  UINT32 Capabilities;

  if (PspMboxBiosQueryCaps (&Capabilities)) {
    return (EFI_UNSUPPORTED);
  }

  *Caps = (Capabilities & (PSP_CAP_TPM_SUPPORTED + PSP_CAP_TPM_REQ_FACTORY_RESET + PSP_CAP_FTPM_NEED_RECOVERY));

  return EFI_SUCCESS;
}

