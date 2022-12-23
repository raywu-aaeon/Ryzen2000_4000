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
 * @e \$Revision: 312135 $   @e \$Date: 2015-02-03 03:16:17 +0800 (Tue, 03 Feb 2015) $
 */
/*****************************************************************************
 *
 * Copyright 2008 - 2021 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
 *
 * AMD is granting You permission to use this software and documentation (if
 * any) (collectively, the "Software") pursuant to the terms and conditions of
 * the Software License Agreement included with the Software. If You do not have
 * a copy of the Software License Agreement, contact Your AMD representative for
 * a copy.
 *
 * You agree that You will not reverse engineer or decompile the Software, in
 * whole or in part, except as allowed by applicable law.
 *
 * WARRANTY DISCLAIMER: THE SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND. AMD DISCLAIMS ALL WARRANTIES, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
 * BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, QUALITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE, NON-INFRINGEMENT AND WARRANTIES
 * ARISING FROM CUSTOM OF TRADE OR COURSE OF USAGE WITH RESPECT TO THE SOFTWARE,
 * INCLUDING WITHOUT LIMITATION, THAT THE SOFTWARE WILL RUN UNINTERRUPTED OR
 * ERROR-FREE. THE ENTIRE RISK ASSOCIATED WITH THE USE OF THE SOFTWARE IS
 * ASSUMED BY YOU. Some jurisdictions do not allow the exclusion of implied
 * warranties, so the above exclusion may not apply to You, but only to the
 * extent required by law.
 *
 * LIMITATION OF LIABILITY AND INDEMNIFICATION: TO THE EXTENT NOT PROHIBITED BY
 * APPLICABLE LAW, AMD AND ITS LICENSORS WILL NOT, UNDER ANY CIRCUMSTANCES BE
 * LIABLE TO YOU FOR ANY PUNITIVE, DIRECT, INCIDENTAL, INDIRECT, SPECIAL OR
 * CONSEQUENTIAL DAMAGES ARISING FROM POSSESSION OR USE OF THE SOFTWARE OR
 * OTHERWISE IN CONNECTION WITH ANY PROVISION OF THIS AGREEMENT EVEN IF AMD AND
 * ITS LICENSORS HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES. THIS
 * INCLUDES, WITHOUT LIMITATION, DAMAGES DUE TO LOST OR MISAPPROPRIATED DATA,
 * LOST PROFITS OR CONFIDENTIAL OR OTHER INFORMATION, FOR BUSINESS INTERRUPTION,
 * FOR PERSONAL INJURY, FOR LOSS OF PRIVACY, FOR FAILURE TO MEET ANY DUTY
 * INCLUDING OF GOOD FAITH OR REASONABLE CARE, FOR NEGLIGENCE AND FOR ANY OTHER
 * PECUNIARY OR OTHER LOSS WHTSOEVER. In no event shall AMD's total liability to
 * You for all damages, losses, and causes of action (whether in contract, tort
 * (including negligence) or otherwise) exceed the amount of $50 USD. You agree
 * to defend, indemnify and hold harmless AMD, its subsidiaries and affiliates
 * and their respective licensors, directors, officers, employees, affiliates or
 * agents from and against any and all loss, damage, liability and other
 * expenses (including reasonable attorneys' fees), resulting from Your
 * possession or use of the Software or violation of the terms and conditions of
 * this Agreement.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS: Notice to U.S. Government End Users. The
 * Software and related documentation are "commercial items", as that term is
 * defined at 48 C.F.R. Section 2.101, consisting of "commercial computer
 * software" and "commercial computer software documentation", as such terms are
 * used in 48 C.F.R. Section 12.212 and 48 C.F.R. Section 227.7202,
 * respectively. Consistent with 48 C.F.R. Section 12.212 or 48 C.F.R. Sections
 * 227.7202-1 through 227.7202-4, as applicable, the commercial computer
 * software and commercial computer software documentation are being licensed to
 * U.S. Government end users: (a) only as commercial items, and (b) with only
 * those rights as are granted to all other end users pursuant to the terms and
 * conditions set forth in this Agreement. Unpublished rights are reserved under
 * the copyright laws of the United States.
 *
 * EXPORT RESTRICTIONS:  You shall adhere to all applicable U.S. import/export
 * laws and regulations, as well as the import/export control laws and
 * regulations of other countries as applicable. You further agree You will not
 * export, re-export, or transfer, directly or indirectly, any product,
 * technical data, software or source code received from AMD under this license,
 * or the direct product of such technical data or software to any country for
 * which the United States or any other applicable government requires an export
 * license or other governmental approval without first obtaining such licenses
 * or approvals, or in violation of any applicable laws or regulations of the
 * United States or the country where the technical data or software was
 * obtained. You acknowledges the technical data and software received will not,
 * in the absence of authorization from U.S. or local law and regulations as
 * applicable, be used by or exported, re-exported or transferred to: (i) any
 * sanctioned or embargoed country, or to nationals or residents of such
 * countries; (ii) any restricted end-user as identified on any applicable
 * government end-user list; or (iii) any party where the end-use involves
 * nuclear, chemical/biological weapons, rocket systems, or unmanned air
 * vehicles.  For the most current Country Group listings, or for additional
 * information about the EAR or Your obligations under those regulations, please
 * refer to the website of the U.S. Bureau of Industry and Security at
 * http://www.bis.doc.gov/.
 *******************************************************************************
 **/

#include <Uefi.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PciLib.h>
#include "AGESA.h"
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Library/AmdPspBaseLibV2.h>
#include <Library/AmdPspMboxLibV2.h>
#include <FchRegistersCommon.h>
#include <Filecode.h>
#include <Library/PcdLib.h>

#define FILECODE LIBRARY_AMDPSPMBOXLIBV2_AMDPSPMBOXLIBV2_FILECODE

/**
  BIOS sends command to PSP

  @param[in]  MboxBuffer        PSP mbox buffer
  @param[in]  Cmd               Psp Mailbox Command

  @retval BOOLEAN                0: Success, 1 Error

**/
BOOLEAN
SendPspCommand (
  IN       VOID       *MboxBuffer,
  IN       MBOX_COMMAND       Cmd
  )
{
  BOOLEAN    Status;
  PSP_MBOX_V2 *PspMbox;
  PSP_MBOX_V2_CMD PspCmd;
  MBOX_BUFFER_HEADER *BufferHdrPtr;
  UINT32     i;
  Status = TRUE;

  IDS_HDT_CONSOLE_PSP_TRACE ("Psp.SendC2PCMD [0x%x] Buffer:0x%x\n", Cmd, MboxBuffer);
  BufferHdrPtr = MboxBuffer;
  for (i = 0; i < BufferHdrPtr->TotalSize; i++) {
    IDS_HDT_CONSOLE_PSP_TRACE ("%02x ", * (((UINT8 *) BufferHdrPtr) + i) );
    if ((i != 0) && ((i + 1) % 16 == 0)) {
      IDS_HDT_CONSOLE_PSP_TRACE ("\n");
    }
  }
  // Get PspMbox location. fail if not found
  if (GetPspMboxLocation (&PspMbox) == FALSE) {
    IDS_HDT_CONSOLE_PSP_TRACE ("GetPspMboxLocation Error\n");
    ASSERT (FALSE); // Assertion in the debug build
    return (FALSE);
  }

  if (PspMbox->Cmd.Field.Recovery) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Recovery Flag detected, ignore the command\n");
    return (FALSE);
  }

  AGESA_TESTPOINT (TpPspC2PmboxBeforeSendCmdBase + Cmd, NULL);

  // Wait till mailbox is ready and PSP finish processing command
  while ( (!PspMbox->Cmd.Field.Ready) ||  (PspMbox->Cmd.Field.CommandId)) {
    ;
  }
  //Clear the ready bit before send the command
  //Do it on local variable 1st to avoid pontencial racing issue
  PspCmd.Value = 0;
  PspCmd.Field.Ready = 0;
  PspCmd.Field.CommandId = (UINT8) Cmd;
  PspMbox->Buffer = (UINT64) (UINTN) MboxBuffer;
  // Now send the command
  PspMbox->Cmd.Value = PspCmd.Value;

  AGESA_TESTPOINT (TpPspC2PmboxWaitCmdBase + Cmd, NULL);

  /// Wait for PSP to be done or reflect error @todo add timeout
  while (PspMbox->Cmd.Field.CommandId) {
    ;
  }
  IDS_HDT_CONSOLE_PSP_TRACE ("\nBuffer dump after CMD finished:\n");
  BufferHdrPtr = MboxBuffer;
  for (i = 0; i < BufferHdrPtr->TotalSize; i++) {
    IDS_HDT_CONSOLE_PSP_TRACE ("%02x ", * (((UINT8 *) BufferHdrPtr) + i) );
    if ((i != 0) && ((i + 1) % 16 == 0)) {
      IDS_HDT_CONSOLE_PSP_TRACE ("\n");
    }
  }
  IDS_HDT_CONSOLE_PSP_TRACE ("\nPsp.SendC2PCMD Exit\n");
  return Status;
}

/**
  BIOS sends the SMM information to PSP. SMM information is used by PSP to pass data back to BIOS

  @param[in]  SmmInfoReq          Point to the structure containing SMMInfo command required data

  @retval EFI_STATUS              0: Success, NonZero Error

**/
EFI_STATUS
PspMboxBiosCmdSmmInfo (
  IN SMM_REQ_BUFFER      *SmmInfoReq
  )
{
  MBOX_SMM_BUFFER    *Buffer;
  UNALIGNED_MBOX_BUFFER   UBuff;    // Unaligned buffer
  BOOLEAN CmdSts;

  CmdSts = FALSE;
  ZeroMem (&UBuff, sizeof (UNALIGNED_MBOX_BUFFER));

  Buffer = BALIGN32 (&UBuff);
  IDS_HDT_CONSOLE_PSP_TRACE ("Psp.C2PMbox.SmmInfo\n");

  Buffer->Header.TotalSize             = sizeof (MBOX_SMM_BUFFER);

  CopyMem (&Buffer->Req, SmmInfoReq, sizeof (SMM_REQ_BUFFER));
  IDS_HDT_CONSOLE_PSP_TRACE ("SMMBase %x SMMMask %x\n", SmmInfoReq->SMMBase, SmmInfoReq->SMMMask);
  IDS_HDT_CONSOLE_PSP_TRACE ("PSPSmmDataRegion %x PspSmmDataLength %x\n", SmmInfoReq->PSPSmmDataRegion, SmmInfoReq->PspSmmDataLength);
  IDS_HDT_CONSOLE_PSP_TRACE ("SmmTrigInfo::Addr:0x%x AddrType:0x%x Width:0x%x AndMask:0x%x OrMask:0x%x\n",
              SmmInfoReq->SmmTrigInfo.Address,
              SmmInfoReq->SmmTrigInfo.AddressType,
              SmmInfoReq->SmmTrigInfo.ValueWidth,
              SmmInfoReq->SmmTrigInfo.ValueAndMask,
              SmmInfoReq->SmmTrigInfo.ValueOrMask);

  IDS_HDT_CONSOLE_PSP_TRACE ("SmiEnb.Address:0x%x AddrType:0x%x Width:0x%x Mask:0x%x ExpectValue:0x%x\n",
  SmmInfoReq->SmmRegInfo.SmiEnb.Address,
  SmmInfoReq->SmmRegInfo.SmiEnb.AddressType,
  SmmInfoReq->SmmRegInfo.SmiEnb.ValueWidth,
  SmmInfoReq->SmmRegInfo.SmiEnb.RegBitMask,
  SmmInfoReq->SmmRegInfo.SmiEnb.ExpectValue);


  IDS_HDT_CONSOLE_PSP_TRACE ("Eos.Address:0x%x AddrType:0x%x Width:0x%x Mask:0x%x ExpectValue:0x%x\n",
  SmmInfoReq->SmmRegInfo.Eos.Address,
  SmmInfoReq->SmmRegInfo.Eos.AddressType,
  SmmInfoReq->SmmRegInfo.Eos.ValueWidth,
  SmmInfoReq->SmmRegInfo.Eos.RegBitMask,
  SmmInfoReq->SmmRegInfo.Eos.ExpectValue);


  IDS_HDT_CONSOLE_PSP_TRACE ("FakeSmiEn.Address:0x%x AddrType:0x%x Width:0x%x Mask:0x%x ExpectValue:0x%x\n",
  SmmInfoReq->SmmRegInfo.FakeSmiEn.Address,
  SmmInfoReq->SmmRegInfo.FakeSmiEn.AddressType,
  SmmInfoReq->SmmRegInfo.FakeSmiEn.ValueWidth,
  SmmInfoReq->SmmRegInfo.FakeSmiEn.RegBitMask,
  SmmInfoReq->SmmRegInfo.FakeSmiEn.ExpectValue);

  IDS_HDT_CONSOLE_PSP_TRACE ("PspMboxSmmBufferAddress:0x%x PspMboxSmmFlagAddress:0x%x\n",
  SmmInfoReq->PspMboxSmmBufferAddress,
  SmmInfoReq->PspMboxSmmFlagAddress);

  CmdSts = SendPspCommand (Buffer, MboxBiosCmdSmmInfo);
  if (CmdSts == FALSE) {
    return EFI_DEVICE_ERROR;
  }
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
    SendPspCommand (Buffer, MboxBiosCmdSxInfo);
    *SmmFlag = FALSE;
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
///@todo Reopen this command
  return EFI_SUCCESS;
//  MBOX_RSM_BUFFER    *Buffer;
//  UNALIGNED_MBOX_BUFFER   UBuff;    // Unaligned buffer
//
//  Buffer = BALIGN32 (&UBuff);
//  PSP_DEBUG ("Psp.C2PMbox.ResumeInfo\n");
//
//  Buffer->Header.TotalSize      = sizeof (MBOX_RSM_BUFFER);
//
//  Buffer->Req.ResumeVecorAddress = S3ResumeAddress;
//  Buffer->Req.ResumeVecorLength  = S3ResumeCodeSize;
//
//  SendPspCommand (Buffer, MboxBiosCmdRsmInfo);
//  PSP_DEBUG ("Mbox.Hdr.Sts:0x%x\n", Buffer->Header.Status);
//  return (Buffer->Header.Status);
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
  BOOLEAN CmdSts;
  BOOLEAN KvmMboxSts;

  KvmMboxSts = PcdGetBool (PcdAmdPspKvmMbox);

  if (KvmMboxSts == TRUE) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Kvm psp msg is detected, skip BOOT_DONE msg\n");
    return EFI_SUCCESS;
  } else {
    CmdSts = FALSE;
    ZeroMem (&UBuff, sizeof (UNALIGNED_MBOX_BUFFER));

    Buffer = BALIGN32 (&UBuff);
    IDS_HDT_CONSOLE_PSP_TRACE ("Psp.C2PMbox.ExitBootServices\n");

    Buffer->Header.TotalSize      = sizeof (MBOX_DEFAULT_BUFFER);

    CmdSts = SendPspCommand (Buffer, MboxBiosCmdBootDone);
    if (CmdSts == FALSE) {
      return EFI_DEVICE_ERROR;
    }
    IDS_HDT_CONSOLE_PSP_TRACE ("Mbox.Hdr.Sts:0x%x\n", Buffer->Header.Status);
    return (Buffer->Header.Status);
  }
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
  BOOLEAN CmdSts;

  CmdSts = FALSE;
  ZeroMem (&UBuff, sizeof (UNALIGNED_MBOX_BUFFER));

  Buffer = BALIGN32 (&UBuff);
  IDS_HDT_CONSOLE_PSP_TRACE ("Psp.PspMboxBiosQueryCaps\n");

  if (Capabilities == NULL) {
    return (EFI_NOT_FOUND);
  }

  Buffer->Header.TotalSize      = sizeof (MBOX_CAPS_BUFFER);

  Buffer->Req.Capabilities      = 1; // 1 to identify the command is sending from V9

  CmdSts = SendPspCommand (Buffer, MboxBiosCmdPspQuery);
  if (CmdSts == FALSE) {
    return EFI_DEVICE_ERROR;
  }
  *Capabilities = Buffer->Req.Capabilities;
  IDS_HDT_CONSOLE_PSP_TRACE ("Caps return %x\n", Buffer->Req.Capabilities);
  IDS_HDT_CONSOLE_PSP_TRACE ("Mbox.Hdr.Sts:0x%x\n", Buffer->Header.Status);
  return (Buffer->Header.Status);
}


/**
  BIOS sends AP CS BASE

  @param[in]  ApCsBase       Address to update the code segment base on APs

  @retval EFI_STATUS                0: Success, NonZero Error

**/
EFI_STATUS
PspMboxBiosSendApCsBase (
  IN       UINT32 ApCsBase
  )
{
  MBOX_AP_CS_BASE_BUFFER  *Buffer;
  UNALIGNED_MBOX_BUFFER    UBuff;    // Unaligned buffer
  BOOLEAN CmdSts;

  CmdSts = FALSE;
  ZeroMem (&UBuff, sizeof (UNALIGNED_MBOX_BUFFER));

  Buffer = BALIGN32 (&UBuff);
  IDS_HDT_CONSOLE_PSP_TRACE ("Psp.PspMboxApCsBase\n");

  Buffer->Header.TotalSize      = sizeof (MBOX_AP_CS_BASE_BUFFER);

  Buffer->Req.Value = ApCsBase;

  CmdSts = SendPspCommand (Buffer, MboxBiosCmdSetApCsBase);
  if (CmdSts == FALSE) {
    return EFI_DEVICE_ERROR;
  }

  IDS_HDT_CONSOLE_PSP_TRACE ("Mbox.Hdr.Sts:0x%x\n", Buffer->Header.Status);
  return (Buffer->Header.Status);
}


/**
  BIOS get FW versions from the PSP

  @param[in]  FwVersions      PSP Writes multiple FW versions into this buffer when it returns.

  @retval EFI_STATUS                0: Success, NonZero Error

**/
EFI_STATUS
PspMboxBiosGetFwVersions (
  IN OUT   VERSION_BUFFER *FwVersions
  )
{
  MBOX_GET_VERSION_BUFFER *Buffer;
  UNALIGNED_MBOX_BUFFER   UBuff;    // Unaligned buffer
  BOOLEAN CmdSts;

  CmdSts = FALSE;
  ZeroMem (&UBuff, sizeof (UNALIGNED_MBOX_BUFFER));

  Buffer = BALIGN32 (&UBuff);
  IDS_HDT_CONSOLE_PSP_TRACE ("Psp.PspMboxBiosGetFwVersions\n");

  if (FwVersions == NULL) {
    return (EFI_NOT_FOUND);
  }

  Buffer->Header.TotalSize      = sizeof (MBOX_GET_VERSION_BUFFER);

  CmdSts = SendPspCommand (Buffer, MboxBiosCmdGetVersion);
  if (CmdSts == FALSE) {
    return EFI_DEVICE_ERROR;
  }
  CopyMem (FwVersions, &Buffer->VersionBuffer, sizeof (VERSION_BUFFER));
  IDS_HDT_CONSOLE_PSP_TRACE ("Mbox.Hdr.Sts:0x%x\n", Buffer->Header.Status);
  return (Buffer->Header.Status);
}

/**
  Check if Ftpm is ready

  @retval EFI_STATUS  0: Success, NonZero Error

**/
EFI_STATUS
CheckFtpmCapsV2 (
  IN OUT   UINT32 *Caps
  )
{
  UINT32 Capabilities;

  if (PspMboxBiosQueryCaps (&Capabilities)) {
    IDS_HDT_CONSOLE_PSP_TRACE ("QueryCaps command return status fail\n");
    return (EFI_UNSUPPORTED);
  }
  IDS_HDT_CONSOLE_PSP_TRACE ("Mbox return Caps %x\n", Capabilities);

  *Caps = (Capabilities & (PSP_CAP_TPM_SUPPORTED + PSP_CAP_TPM_REQ_FACTORY_RESET + PSP_CAP_FTPM_NEED_RECOVERY));

  return (EFI_SUCCESS);
}

/**

  Checks PSP NVRAM status which used for RPMC feature

  Arguments:  pointer

  @param[in]  *PspCapability      Pointer to PSP Capability pointer.

  @retval EFI_STATUS                0: Success, NonZero Error
**/
EFI_STATUS
CheckPspCapsV2 (
  IN OUT UINT32 *PspCaps
  )
{
  EFI_STATUS                  Status;
  UINT32                      PspCapabilities;

  PspCapabilities = 0;
  Status = PspMboxPspCapsQuery (&PspCapabilities);

  if (EFI_ERROR (Status)) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Get PSP Capabilities fail, status = 0x%x\n", Status);
    return Status;
  }

  *PspCaps = PspCapabilities;

  return (EFI_SUCCESS);
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
  BOOLEAN CmdSts;

  CmdSts = FALSE;
  ZeroMem (&UBuff, sizeof (UNALIGNED_MBOX_BUFFER));

  Buffer = BALIGN32 (&UBuff);
  IDS_HDT_CONSOLE_PSP_TRACE ("Psp.PspMboxBiosQueryHSTIState\n");

  if (HSTIState == NULL) {
    return (EFI_NOT_FOUND);
  }

  Buffer->Header.TotalSize = sizeof (MBOX_HSTI_STATE);

  Buffer->HSTIState = 0; // Result of command will be placed here

  CmdSts = SendPspCommand (Buffer, MboxBiosCmdHSTIQuery);
  if (CmdSts == FALSE) {
    return EFI_DEVICE_ERROR;
  }
  *HSTIState = Buffer->HSTIState;
  IDS_HDT_CONSOLE_PSP_TRACE ("Mbox.Hdr.Sts:0x%x HSTIState:0x%x\n", Buffer->Header.Status, Buffer->HSTIState);
  return (Buffer->Header.Status);
}
/**
  BIOS sends the message to PSP o lock DF registers

  @retval EFI_STATUS              0: Success, NonZero Error
**/
EFI_STATUS
PspMboxBiosLockDFReg (
  )
{
  MBOX_DEFAULT_BUFFER     *Buffer;
  UNALIGNED_MBOX_BUFFER   UBuff;    // Unaligned buffer
  BOOLEAN CmdSts;

  CmdSts = FALSE;
  Buffer = BALIGN32 (&UBuff);
  ZeroMem (&UBuff, sizeof (UNALIGNED_MBOX_BUFFER));

  IDS_HDT_CONSOLE_PSP_TRACE ("Psp.C2PMbox.LockDFReg\n");

  Buffer->Header.TotalSize      = sizeof (MBOX_DEFAULT_BUFFER);

  CmdSts = SendPspCommand (Buffer, MboxBiosCmdLockDFReg);
  if (CmdSts == FALSE) {
    return EFI_DEVICE_ERROR;
  }
  IDS_HDT_CONSOLE_PSP_TRACE ("Mbox.Hdr.Sts:0x%x\n", Buffer->Header.Status);
  return (Buffer->Header.Status);
}

/**
 *
 *
 * Bios send this command to inform PSP the information KVM required
 *
 * @param[in]  KvmMboxMemBuffer           Point to KVM information buffer
 *
 * @retval EFI_STATUS              0: Success, NonZero Error
 *
 */
EFI_STATUS
PspMboxBiosCmdKvmInfo (
  MBOX_KVM *KvmMboxMemBuffer
  )
{
  UNALIGNED_MBOX_BUFFER   UBuff;    // Unaligned buffer
  MBOX_KVM      *Buffer;
  EFI_STATUS    Status;

  ZeroMem (&UBuff, sizeof (UNALIGNED_MBOX_BUFFER));

  Buffer = BALIGN32 (&UBuff);
  IDS_HDT_CONSOLE_PSP_TRACE ("Psp.C2PMbox.KvmInfo\n");
  IDS_HDT_CONSOLE_PSP_TRACE ("KvmDmaAddr=0x%08x%08x\n DMABufferSize=0x%x\n", KvmMboxMemBuffer->KvmDmaAddrHi, KvmMboxMemBuffer->KvmDmaAddrLo, KvmMboxMemBuffer->KvmDmaSize);

  Buffer->Header.TotalSize      = sizeof (MBOX_KVM);
  Buffer->KvmDmaAddrLo = KvmMboxMemBuffer->KvmDmaAddrLo;
  Buffer->KvmDmaAddrHi = KvmMboxMemBuffer->KvmDmaAddrHi;
  Buffer->KvmDmaSize = KvmMboxMemBuffer->KvmDmaSize;

  SendPspCommand (Buffer, MboxBiosCmdKvmInfo);
  Status = Buffer->Header.Status;
  IDS_HDT_CONSOLE_PSP_TRACE ("Mbox.Hdr.Sts:0x%x\n", Status);
  return (Status);
}

/**
  * Bios send this command to PSP to decide which RPMC address to use.
  * A warm reset should be issued after receiving BIOS_MBOX_OK (0) from PSP tOS, otherwise BIOS do nothing.
  * It's caller's responsbility to issue the warm reset.
  *
  * @param[in]  RpmcAddressToUse           which RPMC address to program. Value 1 to 3
  *
  @retval EFI_STATUS              0: Success, NonZero Error
  * for example: 0x14 means the PSP report RPMC not available
**/
EFI_STATUS
PspMboxBiosCmdSetRpmcAddress (
  UINT32                RpmcAddressToUse
  )
{
  MBOX_SET_RPMC_ADDRESS_BUFFER     *Buffer;
  UNALIGNED_MBOX_BUFFER   UBuff;    // Unaligned buffer
  BOOLEAN CmdSts;

  CmdSts = FALSE;
  Buffer = BALIGN32 (&UBuff);
  ZeroMem (&UBuff, sizeof (UNALIGNED_MBOX_BUFFER));

  IDS_HDT_CONSOLE_PSP_TRACE ("Psp.C2PMbox.SetRpmcAddress RpmcAddressToUse:%x\n", RpmcAddressToUse);

  Buffer->Header.TotalSize      = sizeof (MBOX_SET_RPMC_ADDRESS_BUFFER);
  Buffer->Header.Status         = 0;
  Buffer->RpmcAddressToUse = RpmcAddressToUse;

  CmdSts = SendPspCommand (Buffer, MboxBiosCmdSetRpmcAddress);
  if (CmdSts == FALSE) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Psp.C2PMbox.SetRpmcAddress Failed with Status = 0x%x.\n", Buffer->Header.Status);
    return EFI_DEVICE_ERROR;
  }

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
  BOOLEAN CmdSts;

  CmdSts = FALSE;
  Buffer = BALIGN32 (&UBuff);
  ZeroMem (&UBuff, sizeof (UNALIGNED_MBOX_BUFFER));

  IDS_HDT_CONSOLE_PSP_TRACE ("Psp.C2PMbox.PspMboxBiosTa Buffer:%x Size:%x\n", TaCmdBufferAddress, TaCmdBufferSize);

  Buffer->Header.TotalSize      = sizeof (MBOX_TA);
  Buffer->Header.Status         = 0;
  Buffer->TaCmdBufferAddress = TaCmdBufferAddress;
  Buffer->TaCmdBufferSize    = TaCmdBufferSize;

  CmdSts = SendPspCommand (Buffer, MboxBiosCmdTa);
  if (CmdSts == FALSE) {
    return TEE_ERR_NWD_INVALID_SESSION;
  }
  IDS_HDT_CONSOLE_PSP_TRACE ("Mbox.Hdr.Sts:0x%x\n", Buffer->Header.Status);
  return (Buffer->Header.Status);
}

/**
  BIOS will send this command to lock SPI, X86 need in SMM mode when send this command

  @retval EFI_STATUS              0: Success, NonZero Error
**/
EFI_STATUS
PspMboxBiosLockSpi (
  )
{
  MBOX_DEFAULT_BUFFER     *Buffer;
  UNALIGNED_MBOX_BUFFER   UBuff;    // Unaligned buffer
  BOOLEAN CmdSts;

  CmdSts = FALSE;
  Buffer = BALIGN32 (&UBuff);
  ZeroMem (&UBuff, sizeof (UNALIGNED_MBOX_BUFFER));

  IDS_HDT_CONSOLE_PSP_TRACE ("Psp.C2PMbox.LockSpi\n");

  Buffer->Header.TotalSize      = sizeof (MBOX_DEFAULT_BUFFER);

  CmdSts = SendPspCommand (Buffer, MboxBiosCmdLockSpi);
  if (CmdSts == FALSE) {
    return EFI_DEVICE_ERROR;
  }
  IDS_HDT_CONSOLE_PSP_TRACE ("Mbox.Hdr.Sts:0x%x\n", Buffer->Header.Status);
  return (Buffer->Header.Status);
}

/**
 *
 *
 * Bios send this command to inform PSP the FCH GPIO require to turn on the screen
 *
 * @param[in]  GpioList           Point to GPIO list
 *
 * @retval EFI_STATUS              0: Success, NonZero Error
 *
 */
EFI_STATUS
PspMboxBiosScreenOnGpio (
  SCREENON_GPIO_LIST *GpioList
  )
{
  UNALIGNED_MBOX_BUFFER   UBuff;    // Unaligned buffer
  MBOX_SCREENON_GPIO      *Buffer;
  EFI_STATUS    Status;
  UINT32        i;

  ZeroMem (&UBuff, sizeof (UNALIGNED_MBOX_BUFFER));

  Buffer = BALIGN32 (&UBuff);
  IDS_HDT_CONSOLE_PSP_TRACE ("Psp.C2PMbox.ScreenOnGpio NumOfGpio:%d\n", GpioList->NumOfGpio);
  ASSERT (GpioList->NumOfGpio < MAX_NUM_WAKEUP_GPIO);

  IDS_HDT_CONSOLE_PSP_TRACE ("GpioList:\n", GpioList->NumOfGpio);
  for (i = 0; i < GpioList->NumOfGpio; i++) {
    IDS_HDT_CONSOLE_PSP_TRACE ("%d ", GpioList->Gpio[i]);
  }
  IDS_HDT_CONSOLE_PSP_TRACE ("\n");

  Buffer->Header.TotalSize      = sizeof (MBOX_SCREENON_GPIO);
  CopyMem (&Buffer->List, GpioList, sizeof (SCREENON_GPIO_LIST));

  SendPspCommand (Buffer, MboxBiosCmdScreenOnGpio);

  Status = Buffer->Header.Status;
  IDS_HDT_CONSOLE_PSP_TRACE ("Mbox.Hdr.Sts:0x%x\n", Status);
  return (Status);
}

/**
 *
 *
 * Bios send this command to pass SPI Operation whitelistn
 *
 * @param[in]  WhiteList           Point to SPI OP white list
 * @param[in]  SmmBuffer           Point to allocated Smmbuffer, call gPspMboxSmmBufferAddressProtocolGuid->PspMboxSmmBuffer
 * @param[in]  SmmFlag             Point to allocated SmmFlag, call gPspMboxSmmBufferAddressProtocolGuid->PspMboxSmmFlagAddr
 *
 * @retval EFI_STATUS              0: Success, NonZero Error
 *
 */
EFI_STATUS
PspMboxBiosSpiOpWhiteList (
  SPI_OP_LIST *WhiteList,
  IN UINT8     *SmmBuffer,
  IN BOOLEAN   *SmmFlag
  )
{
  MBOX_SPI_OP_WHITELIST      *Buffer;
  EFI_STATUS    Status;
  UINT32        i;
  UINTN         PciAddr;

  Status = EFI_INVALID_PARAMETER;
  IDS_HDT_CONSOLE_PSP_TRACE ("Psp.C2PMbox.SpiOpWhiteList:");
  if ((SmmBuffer != NULL) && (SmmFlag != NULL)) {
    IDS_HDT_CONSOLE_PSP_TRACE ("SmmBuffer: %x\n",  SmmBuffer);
    IDS_HDT_CONSOLE_PSP_TRACE ("SmmFlag: %x\n",  SmmFlag);
    //Init Buffer
    Buffer = (MBOX_SPI_OP_WHITELIST*)SmmBuffer;
    ZeroMem (Buffer, sizeof (MBOX_SPI_OP_WHITELIST));
    //Print input parameters
    IDS_HDT_CONSOLE_PSP_TRACE ("NumOfOp:%d\n", WhiteList->NumOfOp);
    ASSERT (WhiteList->NumOfOp <= MAX_NUM_SPI_OP);

    IDS_HDT_CONSOLE_PSP_TRACE ("OpList:\n");
    for (i = 0; i < WhiteList->NumOfOp; i++) {
      IDS_HDT_CONSOLE_PSP_TRACE ("\t[%d]: OpCodes:0x%x  Options:0x%x Size:0x%x\n", i, WhiteList->Ops[i].OpCode, WhiteList->Ops[i].Options, WhiteList->Ops[i].Size);
    }
    //Fill buffer with input parameters
    Buffer->Header.TotalSize      = sizeof (MBOX_SPI_OP_WHITELIST);
    CopyMem (&Buffer->List, WhiteList, sizeof (SPI_OP_LIST));
    // Read LPC register, as it can't be accessed by SMU and PSP
    Buffer->ROMAddrRng2 = PciRead32 (PCI_LIB_ADDRESS (FCH_LPC_BUS, FCH_LPC_DEV, FCH_LPC_FUNC, FCH_LPC_REG6C));
    PciAddr = PCI_LIB_ADDRESS (FCH_LPC_BUS, FCH_LPC_DEV, FCH_LPC_FUNC, FCH_LPC_REG50);
    for (i = 0; i < 4; i++) {
      Buffer->RomProtect[i] = PciRead32 (PciAddr + 4 * i);
    }
    *SmmFlag = TRUE;
    SendPspCommand (Buffer, MboxBiosCmdSpiOpWhiteList);
    *SmmFlag = FALSE;

    Status = Buffer->Header.Status;
    IDS_HDT_CONSOLE_PSP_TRACE ("Mbox.Hdr.Sts:0x%x\n", Status);
  } else {
    IDS_HDT_CONSOLE_PSP_TRACE ("Invalid parameter\n");
  }
  return (Status);
}

/**
 *
 *
 * Bios send this command to pass RAS EINJ related action
 *
 * @param[in]  Action              Action of Einj, e.g. RAS_EINJ_ENABLE_INJECTION, RAS_EINJ_END_OPERATION
 * @param[in]  ActionStruct        Optional, Pass NULL for the action doesn't require extra parameters
 *                                 For RAS_EINJ_EXECUTE_OPERATION, point to RAS_EINJ_EXECUTE_OPERATION_STRUCT
 *
 * @retval EFI_STATUS              0: Success, NonZero Error
 *
 */
EFI_STATUS
PspMboxBiosRasEinj (
  UINT32  Action,
  VOID    *ActionStruct
  )
{
  UNALIGNED_MBOX_BUFFER   UBuff;    // Unaligned buffer
  MBOX_RAS_EINJ      *Buffer;
  EFI_STATUS    Status;
  
  IDS_HDT_CONSOLE_PSP_TRACE ("Psp.C2PMbox.RasEinj Action:%d\n", Action);
  // report issue to AGESA PSP owner, if assert here
  ASSERT (sizeof (MBOX_BUFFER) >= (sizeof (MBOX_RAS_EINJ) + sizeof (RAS_EINJ_EXECUTE_OPERATION_STRUCT)));
  if (sizeof (MBOX_BUFFER) < (sizeof (MBOX_RAS_EINJ) + sizeof (RAS_EINJ_EXECUTE_OPERATION_STRUCT))) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Buffer too small\n");
    return EFI_UNSUPPORTED;
  }

  ZeroMem (&UBuff, sizeof (MBOX_RAS_EINJ)); 
  Buffer = BALIGN32 (&UBuff);
  Buffer->Header.TotalSize      = sizeof (MBOX_RAS_EINJ);
  Buffer->Action      = Action;
  
  if (Action == RAS_EINJ_EXECUTE_OPERATION) {
    ASSERT (ActionStruct != NULL);
    if (ActionStruct == NULL) {
      return EFI_INVALID_PARAMETER;
    }
    Buffer->Header.TotalSize += sizeof (RAS_EINJ_EXECUTE_OPERATION_STRUCT);
    CopyMem ((Buffer + 1), ActionStruct, sizeof (RAS_EINJ_EXECUTE_OPERATION_STRUCT));
  }

  SendPspCommand (Buffer, MboxBiosCmdRasEinj);

  Status = Buffer->Header.Status;
  IDS_HDT_CONSOLE_PSP_TRACE ("Mbox.Hdr.Sts:0x%x\n", Status);
  return (Status);
}

/**
  BIOS sends the message to PSP to fusing PSB fuse

  @retval EFI_STATUS              0: Success, NonZero Error
**/
EFI_STATUS
PspMboxBiosPsbAutoFusing (
  )
{
  MBOX_DEFAULT_BUFFER     *Buffer;
  UNALIGNED_MBOX_BUFFER   UBuff;    // Unaligned buffer
  BOOLEAN CmdSts;

  CmdSts = FALSE;
  Buffer = BALIGN32 (&UBuff);
  ZeroMem (&UBuff, sizeof (UNALIGNED_MBOX_BUFFER));

  IDS_HDT_CONSOLE_PSP_TRACE ("Psp.C2PMbox.PsbAutoFusing\n");

  Buffer->Header.TotalSize      = sizeof (MBOX_DEFAULT_BUFFER);

  CmdSts = SendPspCommand (Buffer, MboxBiosCmdPsbAutoFusing);
  if (CmdSts == FALSE) {
    return EFI_DEVICE_ERROR;
  }
  IDS_HDT_CONSOLE_PSP_TRACE ("Mbox.Hdr.Sts:0x%x\n", Buffer->Header.Status);
  return (Buffer->Header.Status);
}

/**
  BIOS checks the PSP Capabilities from the PSP

  @param[in]  Capabilities      PSP Writes capabilities into this field when it returns.

  @retval EFI_STATUS                0: Success, NonZero Error

**/
EFI_STATUS
PspMboxPspCapsQuery (
  IN OUT   UINT32 *PspCapabilities
  )
{
  MBOX_PSP_CAPS_BUFFER          *Buffer;
  UNALIGNED_MBOX_BUFFER          UBuff;    // Unaligned buffer
  BOOLEAN                        CmdSts;
  PSP_MBOX_V2                    *PspMbox;

  CmdSts = FALSE;
  ZeroMem (&UBuff, sizeof (UNALIGNED_MBOX_BUFFER));

  Buffer = BALIGN32 (&UBuff);
  IDS_HDT_CONSOLE_PSP_TRACE ("Psp.MboxBiosCmdPspCapsQuery\n");

  if (PspCapabilities == NULL) {
    return (EFI_NOT_FOUND);
  }

  Buffer->Header.TotalSize = sizeof (MBOX_PSP_CAPS_BUFFER);

  Buffer->PspCapabilities = 0; // Result of command will be placed here

  CmdSts = SendPspCommand (Buffer, MboxBiosCmdPspCapsQuery);

  if (CmdSts == FALSE) {
    return EFI_DEVICE_ERROR;
  }

  // Get PspMbox location. fail if not found
  if (GetPspMboxLocation (&PspMbox) == FALSE) {
    IDS_HDT_CONSOLE_PSP_TRACE ("GetPspMboxLocation Error\n");
    ASSERT (FALSE); // Assertion in the debug build
    return EFI_DEVICE_ERROR;
  }

  IDS_HDT_CONSOLE_PSP_TRACE ("MailBox return status = %x\n", PspMbox->Cmd.Field.Status);
  if (PspMbox->Cmd.Field.Status != 0) {
    return EFI_UNSUPPORTED;
  }

  *PspCapabilities = Buffer->PspCapabilities;
  IDS_HDT_CONSOLE_PSP_TRACE ("Psp Capabilities return %x\n", Buffer->PspCapabilities);
  IDS_HDT_CONSOLE_PSP_TRACE ("Mbox.Hdr.Sts:0x%x\n", Buffer->Header.Status);
  return (Buffer->Header.Status);
}

