/* $NoKeywords:$ */
/**
 * @file
 *
 * PSP DXE Driver
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  PSP
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
#include <PiDxe.h>
#include <Guid/EventGroup.h>
#include <Library/BaseLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DxeServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/AmdCapsuleLib.h>
#include <Protocol/SmmControl2.h>
#include <Protocol/MpService.h>
#include <Protocol/PciRootBridgeIo.h>
#include <Protocol/PciEnumerationComplete.h>
#include <Protocol/SmmCommunication.h>
#include <Protocol/AmdCoreTopologyProtocol.h>
#include <Protocol/FabricTopologyServices2.h>
#include <Protocol/AmdNbioSmuServicesProtocol.h>
#include <Protocol/AmdPspCommonServiceProtocol.h>
#include "AGESA.h"
#include <Library/AmdBaseLib.h>
#include <Library/FabricResourceManagerLib.h>
#include <Library/IdsLib.h>
#include <Library/AmdIdsHookLib.h>
#include <Library/AmdSocBaseLib.h>
#include <Library/AmdPspBaseLibV2.h>
#include <Library/AmdPspMboxLibV2.h>
#include <Library/MemRestore.h>
#include <Addendum/Apcb/Inc/RV/APOB.h>
#include <Library/AmdPspApobLib.h>
#include <Protocol/PspPlatformProtocol.h>
#include <Library/CcxPspLib.h>
#include <Library/AmdPspFlashUpdateLib.h>
#include <Library/ApobCommonServiceLib.h>
#include <AmdPspSmmCommunication.h>
#include <Protocol/AmdApcbProtocol.h>
#include <Filecode.h>

#define FILECODE PSP_AMDPSPDXEV2_AMDPSPDXEV2_FILECODE

///@todo move below assert definition to Ids header file
#define ASSERT_EFI_ERROR(x) ASSERT (!EFI_ERROR (x))

#define AMD_SMM_COMMUNICATION_BUFFER_SIZE (4 * 1024)
#define PSP_BAR_SIZE                        0x100000ul             ///< Size of PSP BAR
#define NBMSIC_SMN_BASE                     0x13B10000ul           ///< Define the SMN Base address for NB MISC register
#define NBMSIC_PSP_BASE_ADDR_LO_OFFSET      0x2E0                ///< Define the offset of PSP_BASE_ADDR_LO in NB MISC block
#define NBMSIC_PSP_BASE_ADDR_HI_OFFSET      0x2E4                ///< Define the offset of PSP_BASE_ADDR_HI in NB MISC block

extern EFI_GUID gPspFlashAccSmmCommReadyProtocolGuid;
extern EFI_GUID gAmdApcbDxeServiceProtocolGuid;

EFI_SMM_CONTROL2_PROTOCOL              *mSmmControl;
PSP_PLATFORM_PROTOCOL                 *mPspPlatfromProtocol;

STATIC AMD_PSP_COMMON_SERVICE_PROTOCOL mPspCommonServiceProtocol = {
  GetFtpmControlAreaV2,
  SwitchPspMmioDecodeV2,
  CheckPspDevicePresentV2,
  CheckFtpmCapsV2,
  PSPEntryInfoV2,
  PspLibTimeOutV2
};

/*++

Routine Description:

  This function is invoked by EFI_EVENT_SIGNAL_LEGACY_BOOT.
  Before booting to legacy OS, inform SMM

Arguments:

  Event   - The triggered event.
  Context - Context for this event.

Returns:

  None

--*/
VOID
PspNotifySmmDrivers (
  VOID
  )
{

  UINT8 Cmd;
  EFI_STATUS Status;
  //Below two protocols haven't been added to driver's depex, assume it should be ready at RTB
  Status = gBS->LocateProtocol (&gEfiSmmControl2ProtocolGuid, NULL, &mSmmControl);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Locate SmmCtrl Protocol Fail\n");
    return;
  }

  //Locate Psp Platform Protocol to get customized information
  IDS_HDT_CONSOLE_PSP_TRACE ("Locate Psp Platform Protocol\n");
  Status = gBS->LocateProtocol (
                    &gPspPlatformProtocolGuid,
                    NULL,
                    &mPspPlatfromProtocol
                    );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Locate Psp Platform Protocol Fail\n");
    return;
  }

  Cmd = mPspPlatfromProtocol->SwSmiCmdtoBuildContext;

  IDS_HDT_CONSOLE_PSP_TRACE ("PspNotifySmmDrivers Cmd[%x]\n", Cmd);
  mSmmControl->Trigger (mSmmControl, &Cmd, NULL, FALSE, 0);
}

VOID
SetPspAddrMsrTask (
  IN  VOID                                     *Buffer
  )
{
  UINT64 Tmp64;
  //Get PSP BAR Address
  Tmp64 = 0;
  Tmp64 = *((UINT64 *)Buffer);

  UpdatePspAddr (Tmp64);
}

VOID
PspBarInitOnDie (
  IN        UINTN SocketNum,
  IN        UINTN RbNum,
  IN        UINT32 SmuRegInstanceId,
  IN OUT    UINT64 *PspMmioBase
  )
{
  EFI_STATUS Status;
  UINT32 Value32;
  UINT64 Length;
  FABRIC_TARGET MmioTarget;
  FABRIC_MMIO_ATTRIBUTE Attributes;
  DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL   *NbioSmuServices;

  NbioSmuServices = NULL;
  Status = gBS->LocateProtocol (&gAmdNbioSmuServicesProtocolGuid, NULL, &NbioSmuServices);
  if (EFI_ERROR (Status)) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Locate SmuServices Protocol fail\n");
    return;
  }

  //Allocate MMIO Region from MMIO manager
  Length = PSP_BAR_SIZE;
  MmioTarget.TgtType = TARGET_RB;
  MmioTarget.SocketNum = (UINT8) SocketNum;
  MmioTarget.RbNum = (UINT8) RbNum;
  Attributes.ReadEnable = 1;
  Attributes.WriteEnable = 1;
  Attributes.NonPosted = 0;
  Attributes.MmioType = NON_PCI_DEVICE_BELOW_4G;
  Status = FabricAllocateMmio (PspMmioBase, &Length, ALIGN_1M, MmioTarget, &Attributes);
  ASSERT (Status == EFI_SUCCESS );
  if (EFI_ERROR (Status)) {
    IDS_HDT_CONSOLE_PSP_TRACE ("PspBarInitOnDie Allocate MMIO Fail\n");
  } else {
    IDS_HDT_CONSOLE_PSP_TRACE ("PspBarInitOnDie Allocate MMIO @0x%lx\n", *PspMmioBase);
  }

  //Set PSP BASE Address in NBMISC, and enable lock the MMIO
  Value32 = (UINT32) (*PspMmioBase | (BIT0 + BIT8));
  NbioSmuServices->AmdSmuRegisterWrite (NbioSmuServices, SmuRegInstanceId, NBMSIC_SMN_BASE + NBMSIC_PSP_BASE_ADDR_LO_OFFSET, &Value32);
  Value32 = (UINT32) RShiftU64 (*PspMmioBase, 32);
  NbioSmuServices->AmdSmuRegisterWrite (NbioSmuServices, SmuRegInstanceId, NBMSIC_SMN_BASE + NBMSIC_PSP_BASE_ADDR_HI_OFFSET, &Value32);
}

EFI_STATUS
SetPspAddrMsr (
  )
{
  EFI_STATUS  Status;
  EFI_MP_SERVICES_PROTOCOL              *MpServices;
  AMD_CORE_TOPOLOGY_SERVICES_PROTOCOL   *CoreTopology;
  AMD_FABRIC_TOPOLOGY_SERVICES2_PROTOCOL *FabricTopology;
  UINT64                                PspMmioBase;
  UINT32                                SmuRegInstanceId;
  UINT32                                LogicalCoreId;
  UINTN                                 PspBarInitFlag;
  UINTN                                 i;
  UINTN                                 j;
  UINTN                                 k;
  UINTN                                 m;
  UINTN                                 n;
  UINTN                                 NumberOfSockets;
  UINTN                                 NumberOfDies;
  UINTN                                 NumberOfComplexes;
  UINTN                                 NumberOfCores;
  UINTN                                 NumberOfThreads;


  IDS_HDT_CONSOLE_PSP_TRACE ("Locate MP Protocol\n");
  Status = gBS->LocateProtocol (&gEfiMpServiceProtocolGuid, NULL, &MpServices);

  if (EFI_ERROR (Status)) {
    return EFI_UNSUPPORTED;
  }

  CoreTopology = NULL;
  Status = gBS->LocateProtocol (
                &gAmdCoreTopologyServicesProtocolGuid,
                NULL,
                &CoreTopology
                );
  if (EFI_ERROR (Status)) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Locate CoreTopology Protocol fail\n");
    return EFI_UNSUPPORTED;
  }

  FabricTopology = NULL;
  Status = gBS->LocateProtocol (
                &gAmdFabricTopologyServices2ProtocolGuid,
                NULL,
                &FabricTopology
                );
  if (EFI_ERROR (Status)) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Locate FabricTopology Protocol fail\n");
    return EFI_UNSUPPORTED;
  }

  if (FabricTopology->GetSystemInfo (FabricTopology, &NumberOfSockets, NULL, NULL, NULL, NULL) != EFI_SUCCESS) {
    IDS_HDT_CONSOLE_PSP_TRACE ("NumberOfSockets get fail\n");
    return EFI_DEVICE_ERROR;
  }
  SmuRegInstanceId = 0;
  LogicalCoreId = 0;
  PspBarInitFlag = 0;
  for (i = 0; i < NumberOfSockets; i++) {
    if (FabricTopology->GetProcessorInfo (FabricTopology, i, &NumberOfDies, NULL) != EFI_SUCCESS) {
      IDS_HDT_CONSOLE_PSP_TRACE ("Processor information get fail\n");
      return EFI_DEVICE_ERROR;
    }
    for (j = 0; j < NumberOfDies; j++) {
      if (CoreTopology->GetCoreTopologyOnDie (CoreTopology, i, j, &NumberOfComplexes, &NumberOfCores, &NumberOfThreads ) != EFI_SUCCESS) {
        IDS_HDT_CONSOLE_PSP_TRACE ("CoreTopology information get fail\n");
        return EFI_DEVICE_ERROR;
      }
      //PSP BAR already initialized on master die, skip it
      if ((i == 0) && (j == 0)) {
        PspMmioBase = 0;
        GetPspMmioBase ((UINT32 *) &PspMmioBase);
      } else {
        PspMmioBase = 0;
        if (PspBarInitFlag != ((i << 16) + j)) {
          IDS_HDT_CONSOLE_PSP_TRACE ("Setup PSP BAR on socket-0x%x die-0x%x\n", i, j);
          PspBarInitOnDie (i, j, SmuRegInstanceId, &PspMmioBase);
          PspBarInitFlag = (i << 16) + j;
        }
      }
      SmuRegInstanceId ++;
      for (k = 0; k < NumberOfComplexes; k++) {
        for (m = 0; m < NumberOfCores; m++) {
          for (n = 0; n < NumberOfThreads; n++) {
            if (LogicalCoreId != 0) {
              IDS_HDT_CONSOLE_PSP_TRACE ("Set PSPADDR MSR 0x%x for core 0x%x [%x-%x-%x-%x-%x] \n", PspMmioBase, LogicalCoreId, i, j, k, m, n);
              Status = MpServices->StartupThisAP (
                                    MpServices,                                    // EFI_MP_SERVICES_PROTOCOL *this
                                    (EFI_AP_PROCEDURE) SetPspAddrMsrTask,              // EFI_AP_PROCEDURE
                                    LogicalCoreId,
                                    NULL,                                          // EFI_EVENT WaitEvent OPTIONAL
                                    0,                                             // UINTN Timeout (Unsupported)
                                    &PspMmioBase,                                  // VOID *ProcArguments OPTIONAL
                                    NULL                                           // Failed CPUList OPTIONAL (unsupported)
                                    );
            }
            LogicalCoreId ++;
          }
        }
      }
    }
  }

  //Setup PSP BAR MSR for master die
  PspMmioBase = 0;
  GetPspMmioBase ((UINT32 *) &PspMmioBase);
  IDS_HDT_CONSOLE_PSP_TRACE ("Set PSPADDR MSR for BSP 0x%x\n", PspMmioBase);
  SetPspAddrMsrTask (&PspMmioBase);

  return EFI_SUCCESS;
}

VOID
PspMpServiceCallBack (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
{
  EFI_STATUS  Status;
  VOID        *Interface;

  AGESA_TESTPOINT (TpPspDxeV2MpCallBackEntry, NULL);
  //
  // Try to locate it because EfiCreateProtocolNotifyEvent will trigger it once when registration.
  // Just return if it is not found.
  //
  Status = gBS->LocateProtocol (
                  &gEfiMpServiceProtocolGuid,
                  NULL,
                  &Interface
                  );
  if (EFI_ERROR (Status)) {
    return ;
  }

  //Make sure the hook ONLY called one time.
  if (Event != NULL) {
    gBS->CloseEvent (Event);
  }
  SetPspAddrMsr ();
  AGESA_TESTPOINT (TpPspDxeV2MpCallBackExit, NULL);
}

/**
 *  Prepare the APOB Buffer and write to BIOS Directory Entry 0x63
 *
 *
 *  @retval EFI_SUCCESS       The Data save to FLASH successfully
 *
 **/
EFI_STATUS
PspWriteApobS3Entry (
  VOID
  )
{
  APOB_HEADER                     *ApobDramPtr;
  BOOLEAN                         ApobEntryExist;
  TYPE_ATTRIB                     TypeAttrib;
  UINT64                          EntryAddress;
  UINT32                          EntrySize;
  UINT64                          EntryDest;
  APOBLIB_INFO                    *ApobInfo;
  IDS_HDT_CONSOLE_PSP_TRACE ("PspWriteApobS3Entry\n");

  if (AmdPspGetApobInfo (&ApobInfo) != EFI_SUCCESS) {
    IDS_HDT_CONSOLE_PSP_TRACE ("No APOB memory copy detected\n");
    return EFI_UNSUPPORTED;
  }

  ApobDramPtr = (APOB_HEADER *) (UINTN) ApobInfo->ApobAddr;

  //Check the existence and size of APOB NV entry 0x63
  ApobEntryExist = BIOSEntryInfo (APOB_NV_COPY, INSTANCE_IGNORED, &TypeAttrib, &EntryAddress, &EntrySize, &EntryDest);
  if (!ApobEntryExist) {
    IDS_HDT_CONSOLE_PSP_TRACE ("PspWriteApobS3Entry Entry not exist\n");
    return EFI_UNSUPPORTED;
  }
  //Check the size of APOB DRAM copy
  if (ApobDramPtr->Header.Size > EntrySize) {
    IDS_HDT_CONSOLE_PSP_TRACE ("APOB SPI Entry too small\n");
    return EFI_UNSUPPORTED;
  }
  //Compare if any changes
  if (CompareMem (ApobDramPtr, (VOID *) (UINTN) EntryAddress, ApobDramPtr->Header.Size)) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Data difference between APOB DRAM copy & SPI copy\n");
    PspUpdateFlash ((UINT32) EntryAddress, ApobDramPtr->Header.Size, ApobDramPtr);
  }
  return EFI_SUCCESS;
}


VOID
ApcbRecoveryByInstance (
  UINT8             ApcbInstance
  )
{
  TYPE_ATTRIB       TypeAttrib;
  UINT64            ActiveApcbEntryAddress;
  UINT64            BackupApcbEntryAddress;
  UINT32            ActiveApcbSize;
  UINT32            BackUpApcbSize;
  UINT64            EntryDest;
  UINT8             *Buffer;


  IDS_HDT_CONSOLE_PSP_TRACE ("Recover Active APCB Instance %x\n", ApcbInstance);
  //Query APCB Backup instace information
  if (BIOSEntryInfo (BIOS_APCB_INFO_BACKUP, ApcbInstance, &TypeAttrib, &BackupApcbEntryAddress, &BackUpApcbSize, &EntryDest) == FALSE) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Fatal Error: Backup Apcb Not Detected\n");
    ASSERT (FALSE);
    AGESA_TESTPOINT (TpPspRecoverApcbFail, NULL);
    return;
  }
  //Query APCB active instace information
  if (BIOSEntryInfo (BIOS_APCB_INFO, ApcbInstance, &TypeAttrib, &ActiveApcbEntryAddress, &ActiveApcbSize, &EntryDest) == FALSE) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Fatal Error: Active Apcb instance Not Detected\n");
    ASSERT (FALSE);
    AGESA_TESTPOINT (TpPspRecoverApcbFail, NULL);
    return;
  }
  //Do size check between APCB active instace & APCB Backup instace
  ASSERT (ActiveApcbSize >= BackUpApcbSize);
  if (ActiveApcbSize < BackUpApcbSize) {
    IDS_HDT_CONSOLE_PSP_TRACE ("ActiveApcbSize too small\n");
    ASSERT (FALSE);
    AGESA_TESTPOINT (TpPspRecoverApcbFail, NULL);
    return;
  }
  //Start APCB recovery
  //Allocate temp memory to hold backup apcb
  Buffer = NULL;
  Buffer = AllocateZeroPool (BackUpApcbSize);
  ASSERT (Buffer != NULL);
  if (Buffer == NULL) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Allocate temp buffer fail\n");
    return;
  }
  CopyMem (Buffer, (VOID *) (UINTN) BackupApcbEntryAddress, BackUpApcbSize);
  //Restore APCB active instance SPI region
  IDS_HDT_CONSOLE_PSP_TRACE ("Restore APCB active instance SPI region [0x%x] with 0x%x bytes from Buffer [0x%x]\n", ActiveApcbEntryAddress, BackUpApcbSize, Buffer);
  PspUpdateFlash ((UINT32) ActiveApcbEntryAddress, BackUpApcbSize, Buffer);
  IDS_HDT_CONSOLE_PSP_TRACE ("Restore APCB Instance %x Completed, Restart the system", ApcbInstance);
  FreePool (Buffer);
}


VOID
ApcbRecovery (
  )
{
  EFI_STATUS        Status;
  BOOLEAN           ApcbRecoveryFlag;
  UINT8             ApcbInstance;
  UINT8             Value8;

  ApcbRecoveryFlag = FALSE;
  Status = ApobGetApcbRecoveryFlag (&ApcbRecoveryFlag);
  ASSERT (Status == EFI_SUCCESS);
  if (ApcbRecoveryFlag) {
    IDS_HDT_CONSOLE_PSP_TRACE ("APCB.RecoveryFlag Set\n");
    //Query APCB instace
    ApcbInstance = 0;
    Status = ApobGetApcbInstance (&ApcbInstance);
    ASSERT (Status == EFI_SUCCESS);

    ApcbRecoveryByInstance (ApcbInstance);
    // For multiple APCB instance, recover instance 0 as well.
    if (ApcbInstance != 0) {
      ApcbRecoveryByInstance (0);
    }

    IDS_HDT_CONSOLE_PSP_TRACE ("Restore Completed, Restart the system");
    //Update the CMOS[6:7] with flag 0xA55A to indicate the APCB recovery succeed
    Value8 = 0x06;
    LibAmdIoWrite (AccessWidth8, 0x72, &Value8, NULL);
    Value8 = 0x5A;
    LibAmdIoWrite (AccessWidth8, 0x73, &Value8, NULL);

    Value8 = 0x07;
    LibAmdIoWrite (AccessWidth8, 0x72, &Value8, NULL);
    Value8 = 0xA5;
    LibAmdIoWrite (AccessWidth8, 0x73, &Value8, NULL);

    AmdMemRestoreDiscardCurrentMemContext ();

    gRT->ResetSystem (EfiResetWarm, EFI_SUCCESS, 0, NULL);
    //Should not come here
    CpuDeadLoop ();
  }
  // Above recovery will be ignored when PcdAmdPspApcbRecoveryEnable is set to FALSE, which make system always read from Entry 0x68
  // Set the CMOS to force ABL to read from Entry 0x60
  if (PcdGetBool (PcdAmdPspApcbRecoveryEnable) == FALSE) {
    Value8 = 0x06;
    LibAmdIoWrite (AccessWidth8, 0x72, &Value8, NULL);
    Value8 = 0x5A;
    LibAmdIoWrite (AccessWidth8, 0x73, &Value8, NULL);

    Value8 = 0x07;
    LibAmdIoWrite (AccessWidth8, 0x72, &Value8, NULL);
    Value8 = 0xA5;
    LibAmdIoWrite (AccessWidth8, 0x73, &Value8, NULL);
  }
}


VOID
ApcbAccReadyCallBack (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
{
  EFI_STATUS                      Status;
  UINT32                          SizeInByte;
  BOOLEAN                         MemRestoreEnabled;
  AMD_APCB_SERVICE_PROTOCOL       *mApcbDxeServiceProtocol;

  AGESA_TESTPOINT (TpPspDxeV2ApcbAccCallBackEntry, NULL);

  //Make sure the hook ONLY called one time.
  if (Event != NULL) {
    gBS->CloseEvent (Event);
  }

  Status = gBS->LocateProtocol (&gAmdApcbDxeServiceProtocolGuid, NULL, &mApcbDxeServiceProtocol);
  if (EFI_ERROR (Status)) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Unable to locate APCB Protocol");
    return ;
  }

  MemRestoreEnabled = FALSE;

  Status = mApcbDxeServiceProtocol->ApcbGetConfigParameter (mApcbDxeServiceProtocol, APCB_ID_CONFIG_MEMRESTORECTL, &SizeInByte, (UINT64 *)&MemRestoreEnabled);
  IDS_HOOK (IDS_HOOK_PSP_MEM_RESTORE_ENABLED, NULL, (VOID *)&MemRestoreEnabled);
  IDS_HDT_CONSOLE_PSP_TRACE ("Memory Context Restore requested: %d\n", MemRestoreEnabled);

  if ((MemRestoreEnabled && !AmdMemRestoreGetFailure ())) {
    //Save APOB to NV
    PspWriteApobS3Entry ();
  }

  //Do APCB recovery if APOB.APCBRecovery Flag set
  ApcbRecovery ();

  AGESA_TESTPOINT (TpPspDxeV2ApcbAccCallBackExit, NULL);
}

VOID
FlashAccSmmReadyCallBack (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
{
  EFI_STATUS                      Status;
  EFI_EVENT                       SecondaryEvent;
  VOID                            *Interface;
  VOID                            *Registration;

  AGESA_TESTPOINT (TpPspDxeV2FlashAccCallBackEntry, NULL);
  //
  // Try to locate it because EfiCreateProtocolNotifyEvent will trigger it once when registration.
  // Just return if it is not found.
  //
  Status = gBS->LocateProtocol (
                  &gPspFlashAccSmmCommReadyProtocolGuid,
                  NULL,
                  &Interface
                  );
  if (EFI_ERROR (Status)) {
    return ;
  }

  //Make sure the hook ONLY called one time.
  if (Event != NULL) {
    gBS->CloseEvent (Event);
  }

  IDS_HDT_CONSOLE_PSP_TRACE ("\tCreate Protocol event for Install APCB Protocol\n");
  SecondaryEvent = NULL;
  SecondaryEvent = EfiCreateProtocolNotifyEvent (
                      &gAmdApcbDxeServiceProtocolGuid,
                      TPL_NOTIFY,
                      ApcbAccReadyCallBack,
                      NULL,
                      &Registration
                      );
  ASSERT (SecondaryEvent != NULL);
  if (SecondaryEvent == NULL) {
    IDS_HDT_CONSOLE_PSP_TRACE ("\tCreate event fail\n");
  }

  AGESA_TESTPOINT (TpPspDxeV2FlashAccCallBackExit, NULL);
}

/**
 *  Close Psp Smm Communication Interface
 *
 *
 *  @retval EFI_SUCCESS       The Data save to FLASH successfully
 *
 **/
EFI_STATUS
ClosePspSmmCommunication (
  )
{
  EFI_STATUS Status;
  UINT8       *Buffer;
  EFI_SMM_COMMUNICATE_HEADER *SmmCommBuff;
  PSP_SMM_COMMUNICATION_CMN  *PspSmmCloseInterfaceBuff;
  UINTN       SmmCommBufferSize;
  EFI_SMM_COMMUNICATION_PROTOCOL *SmmCommunication = NULL;

  IDS_HDT_CONSOLE_PSP_TRACE ("ClosePspSmmCommunication\n");
  //Assume gEfiSmmCommunicationProtocolGuid should be ready at ExitBs
  Status = gBS->LocateProtocol (&gEfiSmmCommunicationProtocolGuid, NULL, (VOID **) &SmmCommunication);
  ASSERT (Status == EFI_SUCCESS);
  if (EFI_ERROR (Status)) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Locate SmmCommunicationProtocol fail \n");
    return Status;
  }

  //Init SMM communication buffer header
  Buffer = (UINT8 *) (UINTN) PcdGet64 (PcdAmdSmmCommunicationAddress);
  ASSERT (Buffer != NULL);
  if (Buffer != NULL) {
    ZeroMem (Buffer, PSP_CMM_COMM_CLOSE_INTERFACE_BUFFER_SIZE);
    SmmCommBuff = (EFI_SMM_COMMUNICATE_HEADER *) Buffer;
    CopyGuid (&SmmCommBuff->HeaderGuid, &gPspSmmCommHandleGuid);
    SmmCommBuff->MessageLength = sizeof (PSP_SMM_COMMUNICATION_CMN);
    //Init PSP SMM communicate private data
    PspSmmCloseInterfaceBuff = (PSP_SMM_COMMUNICATION_CMN *) &(((EFI_SMM_COMMUNICATE_HEADER *) Buffer)->Data);
    PspSmmCloseInterfaceBuff->id = PSP_SMM_COMM_ID_CLOSE_INTERFACE;

    //Communicate AMD SMM communication handler to close the FlashACC SMI interface
    SmmCommBufferSize = PSP_CMM_COMM_CLOSE_INTERFACE_BUFFER_SIZE;
    SmmCommunication->Communicate (SmmCommunication, Buffer, &SmmCommBufferSize);
  }
  return EFI_SUCCESS;
}
/*++

Routine Description:

  This function is invoked by gEfiEventReadyToBootGuid.
  Before booting to legacy OS, inform PSP that BIOS is transitioning
  preparing for S3 usage.

Arguments:

  Event   - The triggered event.
  Context - Context for this event.

Returns:

  None

--*/
VOID
PspDxeReadyToBoot (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
{
  AGESA_TESTPOINT (TpPspDxeV2RTBCallbackEntry, NULL);
  IDS_HDT_CONSOLE_PSP_TRACE ("PspDxeReadyToBoot\n");

  //Make sure the hook ONLY called one time.
  if (Event != NULL) {
    gBS->CloseEvent (Event);
  }
  //Notify PSP Driver about RTB, PSP SMM driver will save the Core register to S3 Save region
  PspNotifySmmDrivers ();
  //Notify PSP FW Boot done
  PspMboxBiosCmdExitBootServices ();
  AGESA_TESTPOINT (TpPspDxeV2RTBCallbackExit, NULL);
}

VOID
PspDxeExitBS (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
{
  AGESA_TESTPOINT (TpPspDxeV2ExitBsCallbackEntry, NULL);
  IDS_HDT_CONSOLE_PSP_TRACE ("PspDxeExitBS\n");

  //Make sure the hook ONLY called one time.
  if (Event != NULL) {
    gBS->CloseEvent (Event);
  }
  //Close PSP SMM communication interface mainly Flash Access to void security vulnerability
  ClosePspSmmCommunication ();
  AGESA_TESTPOINT (TpPspDxeV2ExitBsCallbackExit, NULL);
}

VOID
PspPciEnumerationCompleteCallBack (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
{
  EFI_STATUS  Status;
  VOID        *Interface;
  //
  // Try to locate it because EfiCreateProtocolNotifyEvent will trigger it once when registration.
  // Just return if it is not found.
  //
  Status = gBS->LocateProtocol (
                  &gEfiPciEnumerationCompleteProtocolGuid,
                  NULL,
                  &Interface
                  );
  if (EFI_ERROR (Status)) {
    return ;
  }

  //Make sure the hook ONLY called one time.
  if (Event != NULL) {
    gBS->CloseEvent (Event);
  }

  PspMboxBiosLockDFReg ();

}

EFI_STATUS
EFIAPI
AmdPspDxeV2DriverEntry (
  IN       EFI_HANDLE         ImageHandle,
  IN       EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_EVENT                   Event;
  EFI_STATUS                  Status;
  EFI_HANDLE                  Handle;
  VOID                        *Registration;
  UINT8                       *Buffer;

  AGESA_TESTPOINT (TpPspDxeV2Entry, NULL);
  IDS_HDT_CONSOLE_PSP_TRACE ("Psp.Drv.AmdPspDxeV2 Enter\n");
  Handle = NULL;
  //Install PSP Common service Protocol
  Status = gBS->InstallProtocolInterface (
                  &Handle,
                  &gAmdPspCommonServiceProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  &mPspCommonServiceProtocol
                  );
  if (EFI_ERROR (Status)) {
    ASSERT (FALSE);
  }

  //Always PSP ADDR MSR for RdRand Instruction
  if (AmdCapsuleGetStatus () == FALSE) {
    IDS_HDT_CONSOLE_PSP_TRACE ("\tCreate MpProtocol event for RdRand\n");
    Event = NULL;
    Event = EfiCreateProtocolNotifyEvent (
                        &gEfiMpServiceProtocolGuid,
                        TPL_NOTIFY,
                        PspMpServiceCallBack,
                        NULL,
                        &Registration
                        );
    ASSERT (Event != NULL);
    if (Event == NULL) {
      IDS_HDT_CONSOLE_PSP_TRACE ("\tCreate event fail\n");
    }

    IDS_HDT_CONSOLE_PSP_TRACE ("\tCreate Protocol event for Install FlashAcc Protocol\n");
    Event = NULL;
    Event = EfiCreateProtocolNotifyEvent (
                        &gPspFlashAccSmmCommReadyProtocolGuid,
                        TPL_NOTIFY,
                        FlashAccSmmReadyCallBack,
                        NULL,
                        &Registration
                        );
    ASSERT (Event != NULL);
    if (Event == NULL) {
      IDS_HDT_CONSOLE_PSP_TRACE ("\tCreate event fail\n");
    }
  }

  //Allocate RT buffer for Smm communication before EndOfDxe Event to satisfie WSMT test
  Buffer = NULL;
  Buffer = AllocateRuntimePool (AMD_SMM_COMMUNICATION_BUFFER_SIZE);
  ASSERT (Buffer != NULL);
  //Save to PCD database
  if (Buffer != NULL) {
    PcdSet64 (PcdAmdSmmCommunicationAddress, (UINT64) (UINTN) Buffer);
  }
  //If PSP feature turn off, exit the driver
  if ((CheckPspDevicePresentV2 () == FALSE) ||
      (PcdGetBool (PcdAmdPspEnable) == FALSE)) {
    return EFI_SUCCESS;
  }

  IDS_HDT_CONSOLE_PSP_TRACE ("\tCreate PciEnumerationCompleteProtocol callback\n");
  Event = NULL;
  Event = EfiCreateProtocolNotifyEvent (
                      &gEfiPciEnumerationCompleteProtocolGuid,
                      TPL_NOTIFY,
                      PspPciEnumerationCompleteCallBack,
                      NULL,
                      &Registration
                      );
  ASSERT (Event != NULL);
  if (Event == NULL) {
    IDS_HDT_CONSOLE_PSP_TRACE ("\tCreate event fail\n");
  }

  IDS_HDT_CONSOLE_PSP_TRACE ("\tCreate ReadyToBoot Event\n");
  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  PspDxeReadyToBoot,
                  NULL,
                  &gEfiEventReadyToBootGuid,
                  &Event
                  );

  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return (Status);
  }

  IDS_HDT_CONSOLE_PSP_TRACE ("\tCreate ExitBootServicesEvent\n");
  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  PspDxeExitBS,
                  NULL,
                  &gEfiEventExitBootServicesGuid,
                  &Event
                  );

  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return (Status);
  }

  IDS_HDT_CONSOLE_PSP_TRACE ("AmdPspDxeV2 Exit\n");
  AGESA_TESTPOINT (TpPspDxeV2Exit, NULL);
  return EFI_SUCCESS;
}

