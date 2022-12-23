/* $NoKeywords:$ */
/**
 * @file
 *
 * PSP related functions in SMM
 *
 * Contains PSP SMM Resume handler
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  PSP
 * @e \$Revision$   @e \$Date$
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

#include "AmdPspSmmV2.h"
#include "AmdPspResumeServicesV2.h"
#include <Library/FchBaseLib.h>
#include <Library/PciLib.h>
#include <Library/CcxPspLib.h>

#define FILECODE PSP_AMDPSPSMMV2_AMDPSPRESUMEHANDLINGV2_FILECODE

///@todo remove below FCH definition when it has been declared by FCH module
#define ACPIMMIO16(x) (*(volatile UINT16*)(UINTN)(x))
#define ACPI_MMIO_BASE  0xFED80000ul
#define PMIO_BASE       0x300   // DWORD
#define FCH_PMIOA_REG62          0x62         // AcpiPm1CntBlk
#define CAPSULE_UPDATE_SIGNATURE 0xCA9501EFul

volatile BOOLEAN              WaitForBspToFinishRestore = FALSE;
volatile UINTN                CoreInSmm = 0;

STATIC UINT8 ApExitS3Count = 0;
volatile BOOLEAN  mCapsuleUpdateFlag = 0;
volatile UINT8  mResumeType = 0;

VOID
GetSmmSaveArea (
  IN OUT   volatile UINT64  *CoreSaveAreaOffset
  )
{
  *CoreSaveAreaOffset  = AsmReadMsr64 (0xC0010111) + 0xFE00;
}

EFI_STATUS
CopySmmSaveAreaToLocal (
  IN OUT   VOID **SmmSaveStart
  )
{
  UINTN   i;
  volatile UINT64                  CoreSaveAreaOffset;
  SMM_SAVE_AREA_CONTEXT   *Dest;
  EFI_STATUS              Status;

  IDS_HDT_CONSOLE_PSP_TRACE ("CopySmmSaveAreaToLocal\n");
  // Allocate SMM buffer to save SMM save area for each core
  Status = gSmst->SmmAllocatePool (
                    EfiRuntimeServicesData,
                    (gSmst->NumberOfCpus)* (SMM_SAVE_SIZE + sizeof (UINT64)),
                    SmmSaveStart
                    );

  IDS_HDT_CONSOLE_PSP_TRACE ("SmmSaveArea at %08x\n", *SmmSaveStart);

  if (EFI_ERROR (Status)) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Smm Pool Allocate fail\n");
    return (Status);
  }
  Dest = (SMM_SAVE_AREA_CONTEXT *)*SmmSaveStart;

  for (i = 0; i < gSmst->NumberOfCpus; i++) {
    // Set CoreSaveAreaOffset with invalid default, to makesure CoreSaveAreaOffset been filled correctly in SMM AP non-blocking mode
    CoreSaveAreaOffset = 0xFFFFFFFFFFFFFFFFull;
    if (i == 0) {
      GetSmmSaveArea (&CoreSaveAreaOffset);
    } else {
      gSmst->SmmStartupThisAp (
             GetSmmSaveArea,
             i,
             (VOID *)&CoreSaveAreaOffset
             );
    }
    //Wait CoreSaveAreaOffset be filled by AP
    while (CoreSaveAreaOffset == 0xFFFFFFFFFFFFFFFFull) {
      CpuPause ();
    }

    IDS_HDT_CONSOLE_PSP_TRACE ("Core%d SMM SaveState0x%08x\n", i, CoreSaveAreaOffset);

    Dest->SaveAreaOffset = (VOID *)CoreSaveAreaOffset;
    IDS_HDT_CONSOLE_PSP_TRACE ("Copy SMM SaveState from 0x%08x to 0x%08x\n", Dest->SaveAreaOffset, Dest->SaveAreaBuffer);

    CopyMem (Dest->SaveAreaBuffer,
      Dest->SaveAreaOffset,
      SMM_SAVE_SIZE
      );
    Dest++;
  }
  return Status;
}


VOID
EFIAPI
OverrideSmmSaveArea (
  IN OUT   VOID                *SmmSaveArea,
  IN       REGISTER_OVERRIDE   *RegisterOverride,
  IN       UINTN                CpuIndex
  )
{
  SMM_SAVE_MAP  *SmmSavePtr = (SMM_SAVE_MAP *)SmmSaveArea;


  SmmSavePtr->CS_Selector   = RegisterOverride->CodeSegOverrideValue;
  SmmSavePtr->CS_Attributes = RegisterOverride->CodeSegAttrib;
  SmmSavePtr->DS_Selector   = RegisterOverride->DateSegOverrideValue;
  SmmSavePtr->DS_Attributes = RegisterOverride->DataSegAttrib;
  SmmSavePtr->DS_Attributes = RegisterOverride->DataSegAttrib;
  SmmSavePtr->ES_Selector   = RegisterOverride->DateSegOverrideValue;
  SmmSavePtr->FS_Selector   = RegisterOverride->DateSegOverrideValue;
  SmmSavePtr->FS_Attributes = RegisterOverride->DataSegAttrib;
  SmmSavePtr->DS_Attributes = RegisterOverride->DataSegAttrib;
  SmmSavePtr->GS_Selector   = RegisterOverride->DateSegOverrideValue;
  SmmSavePtr->GS_Attributes = RegisterOverride->DataSegAttrib;
  SmmSavePtr->DS_Attributes = RegisterOverride->DataSegAttrib;
  SmmSavePtr->SS_Selector   = RegisterOverride->DateSegOverrideValue;
  SmmSavePtr->DS_Attributes = RegisterOverride->DataSegAttrib;


  SmmSavePtr->RAX = RegisterOverride->RaxOverrideValue;
  SmmSavePtr->RBX = RegisterOverride->RbxOverrideValue;
  SmmSavePtr->RDX = RegisterOverride->RdxOverrideValue;

  SmmSavePtr->GDTR_Base   = RegisterOverride->GdtOverrideValue;
  SmmSavePtr->GDTR_Limit  = 0x3f;
  SmmSavePtr->IDTR_Base   = 0;
  SmmSavePtr->IDTR_Limit  = 0;

  SmmSavePtr->CR0 = RegisterOverride->Cr0;
  SmmSavePtr->CR3 = RegisterOverride->Cr3;
  SmmSavePtr->CR4 = RegisterOverride->Cr4;
  SmmSavePtr->RFLAGS = 0;

  if (CpuIndex == 0) {
    SmmSavePtr->RIP = RegisterOverride->RipBspOverrideValue;
    SmmSavePtr->RSP = RegisterOverride->StackBase + RegisterOverride->BspStackSize;
  } else {
    SmmSavePtr->RIP = RegisterOverride->RipApOverrideValue;
    SmmSavePtr->RSP = ( RegisterOverride->StackBase +
                        RegisterOverride->BspStackSize +
                        (RegisterOverride->ApStackSize * CpuIndex)
                       );
  }

  //Clear Auto Halt
  SmmSavePtr->Auto_Halt_Restart = 0;
}


EFI_STATUS
EFIAPI
RestoreSaveAreaFromLocal (
  IN OUT   SMM_SAVE_AREA_CONTEXT *SmmSaveStart,
  IN OUT   REGISTER_OVERRIDE     *RegisterOverride
  )
{
  UINTN   i;

  for (i = 0; i < gSmst->NumberOfCpus; i++) {

    IDS_HDT_CONSOLE_PSP_TRACE ("Restore SmmSave from %08x to %08x\n", SmmSaveStart->SaveAreaBuffer, SmmSaveStart->SaveAreaOffset);
    CopyMem (
      SmmSaveStart->SaveAreaOffset,
      SmmSaveStart->SaveAreaBuffer,
      SMM_SAVE_SIZE
      );

    OverrideSmmSaveArea (
      SmmSaveStart->SaveAreaOffset,
      RegisterOverride,
      i
      );
    SmmSaveStart++;
  }
  return EFI_SUCCESS;
}


VOID
PspConnectedStandbyResumeHandling (
  )
{
  // Call Register callback for connected standby
  PspResumeServiceCallBackV2 (ResumeFromConnectedStandby);
}

EFI_STATUS
EFIAPI
CustomizeSmmRsmVector (
  IN OUT   REGISTER_OVERRIDE       *RegisterOverride
  )
{
  RSM_HANDOFF_INFO *ResumeHandoffInfo;

  ResumeHandoffInfo = mPspPlatformProtocolCopy.RsmHandOffInfo;
  RegisterOverride->RipBspOverrideValue   = ResumeHandoffInfo->RsmEntryPoint;
  RegisterOverride->RipApOverrideValue    = ResumeHandoffInfo->RsmEntryPoint;
  //Set Special value to identify CapsuleUpdate
  if (mCapsuleUpdateFlag) {
    RegisterOverride->RbxOverrideValue     = CAPSULE_UPDATE_SIGNATURE;
  } else {
    RegisterOverride->RbxOverrideValue     = 0;
  }

  RegisterOverride->RdxOverrideValue      = ResumeHandoffInfo->EdxResumeSignature;
  RegisterOverride->GdtOverrideValue      = ResumeHandoffInfo->GdtOffset;
  RegisterOverride->CodeSegOverrideValue  = ResumeHandoffInfo->CodeSelector;
  RegisterOverride->DateSegOverrideValue  = ResumeHandoffInfo->DataSelector;

  RegisterOverride->GdtOverrideLimit      = 0x3f;
  RegisterOverride->CodeSegAttrib         = 0xc9b;
  RegisterOverride->DataSegAttrib         = 0xc93;
  RegisterOverride->Cr0                   = 0x00000013;
  RegisterOverride->Cr3                   = 0x00;
  RegisterOverride->Cr4                   = 0x00040608;

  RegisterOverride->RaxOverrideValue      = (UINTN) mPspSmmRsmMemInfoPtr;      //Rax Point to mPspSmmRsmMemInfo structure
  RegisterOverride->StackBase             = mPspSmmRsmMemInfoPtr->StackPtr;
  RegisterOverride->BspStackSize          = mPspSmmRsmMemInfoPtr->BspStackSize; //Reserve Stack for BSP
  RegisterOverride->ApStackSize           = mPspSmmRsmMemInfoPtr->ApStackSize; //Reserve Stack for AP


  return (EFI_SUCCESS);
}

VOID
EFIAPI
PspS3ResumeHandling (
  VOID
  )
{
  REGISTER_OVERRIDE     RegisterOverride;

  ZeroMem (&RegisterOverride, sizeof (RegisterOverride));

  //Set OEM customized info
  CustomizeSmmRsmVector (&RegisterOverride);

  // Patch Smm save area
  RestoreSaveAreaFromLocal (
    mSmmSaveAreaCopy,
    &RegisterOverride
  );

  // Now call all the Register callback handling
  PspResumeServiceCallBackV2 (ResumeFromS3);

}
BOOLEAN
IsS0i3Resume (
  )
{
  UINT32    S0i3Ctrl;
  UINTN     PciAddress;

  PciAddress = MAKE_SBDFO (0, 0, 0x18, 5, 0x204);
  S0i3Ctrl = PciRead32 (PciAddress);
  return (((S0i3Ctrl & BIT3) == 0) ? FALSE : TRUE);
}


UINT8
GetResumeType (
  )
{
  if (IsS0i3Resume ()) {
    return ResumeFromConnectedStandby;
  } else if (FchReadSleepType () == 0x03) {
    return ResumeFromS3;
  } else {
    if (!mCapsuleUpdateFlag) {
      IDS_HDT_CONSOLE_PSP_TRACE ("Unsupported Resume type\n");
      ASSERT (FALSE);
      CpuDeadLoop ();  //Should never come here
      return InvalidResumeValue;
    } else {
      return ResumeFromS3;
    }
  }
}



// This is the entry point of AP when we resume from sleep /CS and
// after PSP restore the memory. PSP release BSP and BSP will go through PEI Agesa
// driver to release AP. Here we setup stack etc and AP will rsm to SEC code
// AP from here
//
VOID
ApSmmResumeVector (
  )
{
  AGESA_TESTPOINT (TpPspSmmV2ApRsmEntry, NULL);
  IDS_HDT_CONSOLE_PSP_TRACE ("PSP.ApSmmResumeVector\n");

  if (mResumeType == ResumeFromS3) {
    // Now call all the Register callback handling
    PspResumeServiceCallBackV2 (ResumeFromS3);

    AGESA_TESTPOINT (TpPspSmmV2ApRsmExit, NULL);

    // Increse global variable for AP count
    *mApSyncFlag = *mApSyncFlag + 1;

    S3ExitToBiosV2 ();
  } else if (mResumeType == ResumeFromConnectedStandby) {
    // Call Register callback for connected standby
    PspConnectedStandbyResumeHandling ();
  }

  CpuDeadLoop ();
}

//
// This is the entry point of BSP when we resume from sleep and
// after PSP restore the memory will release the CPU code to run
// BSP from here
//
VOID
BspSmmResumeVector (
  )
{

  AGESA_TESTPOINT (TpPspSmmV2BspRsmEntry, NULL);
  IDS_HDT_CONSOLE_PSP_TRACE ("PSP.BspSmmResumeVector\n");

  mResumeType = GetResumeType (); //Check resume type is S3 or connected standby
  if (mResumeType == ResumeFromS3) {
    IDS_HDT_CONSOLE_PSP_TRACE ("S3 Resume Handling\n");

    PspS3ResumeHandling ();

    AGESA_TESTPOINT (TpPspSmmV2BspRsmExit, NULL);
    //Clear Sleep Type to force S5 Path, Specail value is set in RDX to identify CapsuleUpdate mode
    if (mCapsuleUpdateFlag) {
      FchWriteSleepType (0);
    }

    // Clear the global variable for AP count
    *mApSyncFlag = 0;

    S3ExitToBiosV2 ();
  } else if (mResumeType == ResumeFromConnectedStandby) {
    // Call Register callback for connected standby
    IDS_HDT_CONSOLE_PSP_TRACE ("S0i3 resume Handling\n");
    PspConnectedStandbyResumeHandling ();
  }

  // we should never come here
  CpuDeadLoop ();
}

VOID
UpdateS3SaveAreaMapV2 (
  )
{
  UINTN i;
  IDS_HDT_CONSOLE_PSP_TRACE ("UpdateS3SaveAreaMap Num %d BSP %x AP %x\n", gSmst->NumberOfCpus, &BspSmmResumeVector, &ApSmmResumeVector);
  for (i = 1; i < gSmst->NumberOfCpus; i++) {
    gSmst->SmmStartupThisAp (
             SetupReleaseVector,
             i,
             (VOID *)(UINTN)ApSmmResumeVector
             );

  }

  SetupReleaseVector ((VOID *) (UINTN) &BspSmmResumeVector);
}


