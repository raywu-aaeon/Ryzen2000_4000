/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD CCX Zen - Zeppelin API, and related functions.
 *
 * Contains code that initializes the core complex
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  CCX
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
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/HobLib.h>
#include <Library/UefiLib.h>
#include <Protocol/MpService.h>
#include <Guid/HobList.h>
#include <Guid/EventGroup.h>
#include <Library/CcxRolesLib.h>
#include <Library/CcxBaseX86Lib.h>
#include <Library/AmdBaseLib.h>
#include <Library/CcxHaltLib.h>
#include <Library/AmdPspBaseLibV2.h>
#include <Library/CcxResetTablesLib.h>
#include <Library/AmdIdsHookLib.h>
#include <Addendum/Apcb/Inc/RV/APOB.h>
#include <Library/AmdPspApobLib.h>
#include <Library/AmdPspMboxLibV2.h>
#include <Library/AmdCapsuleLib.h>
#include <Library/FchBaseLib.h>
#include <Library/CcxSetMcaLib.h>
#include <Library/AmdHeapLib.h>
#include <Library/CcxSmmAccess2Lib.h>
#include <Library/AmdTableLib.h>
#include <Protocol/AmdCoreTopologyProtocol.h>
#include <Protocol/FabricTopologyServices2.h>
#include <Protocol/AmdMpServicesPreReqProtocol.h>
#include <Protocol/AmdCcxProtocol.h>
#include <Protocol/AmdNbioSmuServicesProtocol.h>
#include <Protocol/SmmControl2.h>
#include <Protocol/AmdNbioServicesProtocol.h>
#include "AmdCcxZenRvDxe.h"
#include "CcxZenRvMicrocodePatch.h"
#include "CcxZenRvAcpiServicesDxe.h"
#include "CcxZenRvSmbiosDxe.h"
#include "CcxZenRvC6.h"
#include "CcxZenRvCpb.h"
#include "CcxZenRvPrefetch.h"
#include "Filecode.h"

#define FILECODE CCX_ZEN_CCXZENRVDXE_AMDCCXZENRVDXE_FILECODE

extern  EFI_BOOT_SERVICES *gBS;

/*----------------------------------------------------------------------------------------
 *                               D E F I N I T I O N S
 *----------------------------------------------------------------------------------------
 */
#define  AP_ALLOCATION_SIZE  (128 * 1024)

/*----------------------------------------------------------------------------------------
 *                           G L O B A L   V A R I A B L E S
 *----------------------------------------------------------------------------------------
 */
EFI_EVENT            CcxRvInitWithMpServicesEvent;
EFI_EVENT            CcxRvOcCallbackEvent;
AP_MSR_SYNC          mLateMsrSyncTable[] =
{
  { 0xC0010010, 0x0000000000000000, 0xFFFFFFFFFFFFFFFF  },
  { 0xC0010030, 0x0000000000000000, 0xFFFFFFFFFFFFFFFF  },
  { 0xC0010031, 0x0000000000000000, 0xFFFFFFFFFFFFFFFF  },
  { 0xC0010032, 0x0000000000000000, 0xFFFFFFFFFFFFFFFF  },
  { 0xC0010033, 0x0000000000000000, 0xFFFFFFFFFFFFFFFF  },
  { 0xC0010034, 0x0000000000000000, 0xFFFFFFFFFFFFFFFF  },
  { 0xC0010035, 0x0000000000000000, 0xFFFFFFFFFFFFFFFF  },
  { 0xC0011029, 0x0000000000000000, BIT14  },               // PcdAmdRedirectForReturnDis
  { 0xC0011020, 0x0000000000000000, BIT28  }                // PcdAmdStreamingStoresCtrl
};
VOID                 *mRegistrationForCcxRvInitWithMpServicesEvent;
VOID                 *mRegistrationForCcxRvOcCallbackEvent;
UINT64               mUcodePatchAddr = 0;
UINT64               BspPatchLevel;
UINT32               BspMsrLocation;
UINT32               ApSyncLocation;
UINT32               AllowToLaunchNextThreadLocation;
UINT8                SleepType;
VOID                 *ApStackBasePtr;
UINTN                ApTempBufferSize;
EFI_PHYSICAL_ADDRESS ApStartupVector;
CCX_GDT_DESCRIPTOR   ApGdtDescriptor;
VOID                 *MemoryContentCopy;
EFI_PHYSICAL_ADDRESS ApPageAllocation = 0;
UINT8                mPcdAmdRedirectForReturnDis;
UINT8                mPcdAmdStreamingStoresCtrl;
DXE_AMD_CCX_INIT_COMPLETE_PROTOCOL    mCcxDxeInitCompleteProtocol;
DXE_AMD_CCX_OC_COMPLETE_PROTOCOL      mCcxOcCompleteProtocol;
AP_MTRR_SETTINGS     ApMsrSettingsList[] =
{
  { 0xC0010058,               0x0000000000000000  },
  { AMD_AP_MTRR_FIX64k_00000, 0x0000000000000000  },
  { AMD_AP_MTRR_FIX16k_80000, 0x0000000000000000  },
  { AMD_AP_MTRR_FIX16k_A0000, 0x0000000000000000  },
  { AMD_AP_MTRR_FIX4k_C0000,  0x0000000000000000  },
  { AMD_AP_MTRR_FIX4k_C8000,  0x0000000000000000  },
  { AMD_AP_MTRR_FIX4k_D0000,  0x0000000000000000  },
  { AMD_AP_MTRR_FIX4k_D8000,  0x0000000000000000  },
  { AMD_AP_MTRR_FIX4k_E0000,  0x0000000000000000  },
  { AMD_AP_MTRR_FIX4k_E8000,  0x0000000000000000  },
  { AMD_AP_MTRR_FIX4k_F0000,  0x0000000000000000  },
  { AMD_AP_MTRR_FIX4k_F8000,  0x0000000000000000  },
  { 0x00000200,               0x0000000000000000  },
  { 0x00000201,               0x0000000000000000  },
  { 0x00000202,               0x0000000000000000  },
  { 0x00000203,               0x0000000000000000  },
  { 0x00000204,               0x0000000000000000  },
  { 0x00000205,               0x0000000000000000  },
  { 0x00000206,               0x0000000000000000  },
  { 0x00000207,               0x0000000000000000  },
  { 0x00000208,               0x0000000000000000  },
  { 0x00000209,               0x0000000000000000  },
  { 0x0000020A,               0x0000000000000000  },
  { 0x0000020B,               0x0000000000000000  },
  { 0x0000020C,               0x0000000000000000  },
  { 0x0000020D,               0x0000000000000000  },
  { 0x0000020E,               0x0000000000000000  },
  { 0x0000020F,               0x0000000000000000  },
  { 0x000002FF,               0x0000000000000000  },
  { CPU_LIST_TERMINAL                             }
};

UINT64 GdtEntries[] =
{
 0x0000000000000000,  // [00h] Null descriptor
 0x00CF92000000FFFF,  // [08h] Linear data segment descriptor
 0x00CF9A000000FFFF,  // [10h] Linear code segment descriptor
 0x00CF92000000FFFF,  // [18h] System data segment descriptor
 0x00CF9A000000FFFF,  // [20h] System code segment descriptor
 0x0000000000000000,  // [28h] Spare segment descriptor
 0x00CF93000000FFFF,  // [30h] System data segment descriptor
 0x00AF9B000000FFFF,  // [38h] System code segment descriptor
 0x0000000000000000   // [40h] Spare segment descriptor
};

UINT8 AsmNearJump[] =
{ 0x90,         // nop
  0xE9,         // near jmp
  0xFC, 0xFB
};

UINT8 ApStartupCode[] =
{
//[000] [001] [002]
  0xBE, 0xF4, 0xFF,                     // mov si, 0FFF4h
//[003]
  0x66,
//[004] [005] [006] [007]
  0x2E, 0x0F, 0x01, 0x14,               // lgdt       fword ptr cs:[si]
//[008] [009] [010]
  0x0F, 0x20, 0xC0,                     // mov        eax, cr0                    ; Get control register 0
//[011] [012] [013] [014]
  0x66, 0x83, 0xC8, 0x03,               // or         eax, 000000003h             ; Set PE bit (bit #0)
//[015] [016] [017]
  0x0F, 0x22, 0xC0,                     // mov        cr0, eax
//[018] [019] [020]
  0x0F, 0x20, 0xE0,                     // mov        eax, cr4
//[021] [022] [023] [024] [025] [026]
  0x66, 0x0D, 0x00, 0x06, 0x00, 0x00,   // or         eax, 00000600h
//[027] [028] [029]
  0x0F, 0x22, 0xE0,                     // mov        cr4, eax
  // Protected Mode Start
//[030] [031] [032]
  0xB8, 0x18, 0x00,                     // mov        ax,  18h
//[033] [034]
  0x8E, 0xD8,                           // mov        ds,  ax
//[035] [036]
  0x8E, 0xC0,                           // mov        es,  ax
//[037] [038]
  0x8E, 0xE0,                           // mov        fs,  ax
//[039] [040]
  0x8E, 0xE8,                           // mov        gs,  ax
//[041] [042]
  0x8E, 0xD0,                           // mov        ss,  ax
//[043] [044] [045]
  0x66, 0x67, 0xEA,                     // Far jump
//[046] [047] [048] [049]
  0x24, 0xFC, 0x00, 0x00,               // Byte [48], [49] will be replaced with segment from BIOS Directory
//[050] [051]
  0x10, 0x00,

  // Long Mode setup
//[052] [053] [054]
  0x0F, 0x20, 0xE0,                     // mov eax, cr4
//[055] [056] [057] [058]
  0x0F, 0xBA, 0xE8, 0x05,               // bts eax, 5                             ; Set PAE (bit #5)
//[059] [060] [061]
  0x0F, 0x22, 0xE0,                     // mov cr4, eax
//[062] [063] [064] [065] [066]
  0xB9, 0x80, 0x00, 0x00, 0xC0,         // mov ecx, 0C0000080h                    ; Read EFER MSR
//[067] [068]
  0x0F, 0x32,                           // rdmsr
//[069] [070] [071] [072]
  0x0F, 0xBA, 0xE8, 0x08,               // bts eax, 8                             ; Set LME (bit #8)
//[073] [074]
  0x0F, 0x30,                           // wrmsr

//[075] [076] [077] [078] [079]
  0xBE, 0xE8, 0xFF, 0x00, 0x00,         // mov esi, 0000ffE8
                                        // Byte [78] [79] will be replaced with segment from BIOS Directory
//[080] [081]
  0x8B, 0x0E,                           // mov ecx, [esi]
//[082] [083] [084]
  0x0F, 0x22, 0xD9,                     // mov cr3, ecx                           ; Load CR3 with value from BSP

//[085] [086] [087]
  0x0F, 0x20, 0xC0,                     // mov eax, cr0
//[088] [089] [090] [091]
  0x0F, 0xBA, 0xE8, 0x1F,               // bts eax, 31                            ; Set PG bit (bit #31)
//[092] [093] [094]
  0x0F, 0x22, 0xC0,                     // mov cr0, eax

//[095] [096]
  0x67, 0xEA,                           // Far jump to long mode
//[097] [098] [099] [100]
  0x57, 0xFC, 0x00, 0x00,               // Bytes [99] [100] will be replaced with segment from BIOS Directory
//[101] [102]
  0x38, 0x00,
//[103] [104]
  0x48, 0xB8,                           // mov rax, offset ApEntryInCOffset
//[105] [106] [107] [108]               // Bytes [105] - [112] will be replaced with offset to APEntryInCOffset
  0xFF, 0xFF, 0xFF, 0xFF,
//[109] [110] [111] [112]
  0xFF, 0xFF, 0xFF, 0xFF,
//[113] [114]
  0xFF, 0xE0                            // jmp rax
};

#define ZEN_COMPLEX_MASK  0x0F
#define ZEN_COMPLEX_SIZE  4
#define RV_COMPLEX_COUNT  1
UINT8  EnabledCoreCountOnComplex[16] =
{
  0x00,  //  0
  0x01,  //  1
  0x01,  //  2
  0x02,  //  3
  0x01,  //  4
  0x02,  //  5
  0x02,  //  6
  0x03,  //  7
  0x01,  //  8
  0x02,  //  9
  0x02,  // 10
  0x03,  // 11
  0x02,  // 12
  0x03,  // 13
  0x03,  // 14
  0x04,  // 15
};

#define ZEN_CAC_WEIGHT_NUM 21
UINT64 mCacWeights[ZEN_CAC_WEIGHT_NUM];

typedef struct {
  UINT8 *AsmNearJumpAddress;
  UINTN ApStartupOffset;
  UINTN Size;
} AP_ADDRESS_MAP;

VOID
ApGetStartupCodeInfo (
     OUT   AP_ADDRESS_MAP *AddressMap
  );
/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */
VOID
EFIAPI
CcxRvInitWithMpServices (
  IN EFI_EVENT        Event,
  IN VOID             *Context
  );

VOID
EFIAPI
CcxRvOcCallback (
  IN EFI_EVENT        Event,
  IN VOID             *Context
  );

VOID ApAsmCode (
  VOID
 );

VOID
RegSettingBeforeLaunchingNextThread (
  VOID
  );

VOID
ApEntryPointInC (
  VOID
  );

VOID
SetupApStartupRegion (
  );

VOID
RestoreResetVector (
  IN       UINT16 TotalCoresLaunched
  );

VOID
CcxZenRvSetMiscMsrs (
  IN       VOID  *Void
  );

VOID
CcxZenRvSyncMiscMsrs (
  IN       VOID  *Void
  );

VOID
CcxZenGetCacWeights (
  IN       DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL  *NbioSmuServices
  );

VOID
CcxZenSetCacWeights (
  );

VOID
CcxZenRvEnableSmee (
  );

VOID
EFIAPI
CcxReadyToBoot (
  IN EFI_EVENT        Event,
  IN VOID             *Context
  );

VOID
CcxZenRvOpCache (
  IN       DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL  *NbioSmuServices
  );

/* -----------------------------------------------------------------------------*/
/**
 *
 *  AmdCcxZenRvDxeInit
 *
 *  @param[in]  ImageHandle     EFI Image Handle for the DXE driver
 *  @param[in]  SystemTable     Pointer to the EFI system table
 *
 *  Description:
 *    Zen - Zeppelin Driver Entry.  Initialize the core complex.
 *
 *  @retval EFI_STATUS
 *
 */
EFI_STATUS
EFIAPI
AmdCcxZenRvDxeInit (
  IN       EFI_HANDLE         ImageHandle,
  IN       EFI_SYSTEM_TABLE   *SystemTable
  )
{
  UINT8                                 OpnComplexCoreCount[RV_COMPLEX_COUNT];
  UINT16                                CoreNumber;
  UINTN                                 i;
  UINTN                                 j;
  UINTN                                 k;
  UINTN                                 m;
  UINTN                                 n;
  UINTN                                 LogicalThread;
  UINTN                                 NumberOfSockets;
  UINTN                                 NumberOfDies;
  UINTN                                 NumberOfComplexes;
  UINTN                                 NumberOfCores;
  UINTN                                 NumberOfThreads;
  UINTN                                 TotalCoresLaunched;
  UINTN                                 OpnThreadCount;
  UINTN                                 OpnComplexCount;
  UINTN                                 EnabledComplex;
  UINT32                                SystemDieLoop;
  UINT32                                OpnFuse;
  BOOLEAN                               S3Support;
  EFI_STATUS                            Status;
  EFI_STATUS                            CalledStatus;
  AMD_CONFIG_PARAMS                     StdHeader;
  AMD_CORE_TOPOLOGY_SERVICES_PROTOCOL   *CoreTopology;
  AMD_FABRIC_TOPOLOGY_SERVICES2_PROTOCOL *FabricTopology;
  EFI_HANDLE                            Handle;
  DXE_AMD_MP_SERVICES_PREREQ_PROTOCOL   AmdMpServicesPreReqProtocol;
  DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL   *NbioSmuServices;
  EFI_EVENT                             ReadyToBootEvent;
  ALLOCATE_HEAP_PARAMS                  AllocParams;
  PROFILE_FEATS                         PlatformProfile;
  PLATFORM_FEATS                        PlatformFeatures;

  AGESA_TESTPOINT (TpCcxDxeEntry, NULL);

  IDS_HDT_CONSOLE (CPU_TRACE, "  AmdCcxZenRvDxeInit Entry\n");

  Status = EFI_SUCCESS;

  if (CcxIsBsp (&StdHeader)) {

    // Load microcode on the BSP
    IDS_SKIP_HOOK (IDS_HOOK_CCX_SKIP_UCODE_PATCH, NULL, NULL) {
      CcxZenRvMicrocodeInit (&mUcodePatchAddr, &StdHeader);
    }

    RegSettingBeforeLaunchingNextThread ();

    // Get CacWeights from SMU
    gBS->LocateProtocol (&gAmdNbioSmuServicesProtocolGuid, NULL, &NbioSmuServices);
    CcxZenGetCacWeights (NbioSmuServices);

    S3Support = TRUE;
    if (AmdCapsuleGetStatus () == FALSE) {

      // Below 2 functions may be called by every threads in CcxProgramTablesAtReset
      // To avoid any UEFI services be called by APs, BSC calls them here
      // The result would be saved to a global variable
      GetPlatformFeatures (&PlatformFeatures, &StdHeader);
      GetPerformanceFeatures (&PlatformProfile, &StdHeader);

      // Setup reset vector with AP Start up code
      AGESA_TESTPOINT (TpCcxDxeStartLaunchAp, NULL);
      SetupApStartupRegion ();

      // Launch APs to get the APs to a known state before we publish
      // Ccx MP Services Protocol
      Status = gBS->LocateProtocol (
                    &gAmdCoreTopologyServicesProtocolGuid,
                    NULL,
                    &CoreTopology
                    );
      Status = gBS->LocateProtocol (
                    &gAmdFabricTopologyServices2ProtocolGuid,
                    NULL,
                    &FabricTopology
                    );

      if (FabricTopology->GetSystemInfo (FabricTopology, &NumberOfSockets, NULL, NULL, NULL, NULL) != EFI_SUCCESS) {
        AGESA_TESTPOINT (TpCcxDxeLaunchApAbort, NULL);
        return EFI_DEVICE_ERROR;
      }
      SystemDieLoop = 0;
      TotalCoresLaunched = 0;
      CoreNumber = 0xFFFF;
      for (i = 0; i < NumberOfSockets; i++) {
        if (FabricTopology->GetProcessorInfo (FabricTopology, i, &NumberOfDies, NULL) != EFI_SUCCESS) {
         AGESA_TESTPOINT (TpCcxDxeLaunchApAbort, NULL);
          return EFI_DEVICE_ERROR;
        }
        for (j = 0; j < NumberOfDies; j++) {
          if (CoreTopology->GetCoreTopologyOnDie (CoreTopology, i, j, &NumberOfComplexes, &NumberOfCores, &NumberOfThreads ) != EFI_SUCCESS) {
            AGESA_TESTPOINT (TpCcxDxeLaunchApAbort, NULL);
            return EFI_DEVICE_ERROR;
          }
          for (k = 0; k < NumberOfComplexes; k++) {
            LogicalThread = 0;
            for (m = 0; m < NumberOfCores; m++) {
              for (n = 0; n < NumberOfThreads; n++) {
                if (!((i == 0) && (j == 0) && (k == 0) && (LogicalThread == 0))) {

                  IDS_HDT_CONSOLE (CPU_TRACE, "    Launch socket %X die %X complex %X core %X thread %X\n", i, j, k, m, n);
                  CoreTopology->LaunchThread (CoreTopology, i, j, k, LogicalThread);
                  TotalCoresLaunched++;
                  // Check whether the last core has completed necessory initialization before launching next thread
                  do {
                    gBS->CopyMem ((VOID *) &CoreNumber,
                                  (VOID *) (EFI_PHYSICAL_ADDRESS)(AllowToLaunchNextThreadLocation),
                                  sizeof (CoreNumber)
                                  );
                  } while (CoreNumber != TotalCoresLaunched);

                }
                LogicalThread++;
              }
            }
          }
          // Determine if S3 should be disabled
          NbioSmuServices->AmdSmuRegisterRead (NbioSmuServices, SystemDieLoop, 0x5D254, &OpnFuse);
          OpnThreadCount = (UINTN) (((OpnFuse >> 8) & 1) + 1);
          OpnFuse = (~OpnFuse) & 0xFF;
          OpnComplexCount = 0;
          EnabledComplex = 0;
          for (k = 0; k < RV_COMPLEX_COUNT; k++) {
            OpnComplexCoreCount[k] = EnabledCoreCountOnComplex[((OpnFuse >> (ZEN_COMPLEX_SIZE * k)) & ZEN_COMPLEX_MASK)];
            if (OpnComplexCoreCount[k] != 0) {
              OpnComplexCount++;
            }
          }

          ASSERT ((OpnComplexCount > 0) && (OpnComplexCount <= RV_COMPLEX_COUNT));
          if (OpnComplexCount > 1) {
            ASSERT (OpnComplexCoreCount[0] == OpnComplexCoreCount[1]);
          }

          if ((OpnComplexCount != NumberOfComplexes) ||
              ((UINTN) OpnComplexCoreCount[EnabledComplex] != NumberOfCores) ||
              (OpnThreadCount != NumberOfThreads)) {
            IDS_HDT_CONSOLE (CPU_TRACE, "    Threads have been removed by software.  Disable S3\n");
            S3Support = FALSE;
          }
          SystemDieLoop++;
        }
      }
      // Restore the data located at the reset vector
      RestoreResetVector ((UINT16) TotalCoresLaunched);
      AGESA_TESTPOINT (TpCcxDxeEndLaunchAp, NULL);
    }

    if (!S3Support) {
      IDS_HDT_CONSOLE (CPU_TRACE, "    Setting PcdAmdAcpiS3Support to FALSE\n");
      PcdSetBool (PcdAmdAcpiS3Support, S3Support);
      PcdSet8 (PcdS0i3Enable, 0);
    }

    // Enable SMEE
    CcxZenRvEnableSmee ();

    // Mca initialization
    CcxSetMca ();

    // Cac Weights initialization
    AGESA_TESTPOINT (TpCcxDxeCacWeights, NULL);
    CcxZenSetCacWeights ();

    // Install gAmdMpServicesPreReqProtocolGuid protocol
    AmdMpServicesPreReqProtocol.Revision = AMD_MP_SERVICES_PREREQ_PROTOCOL_REVISION;
    Handle = NULL;
    CalledStatus = gBS->InstallProtocolInterface (
                            &Handle,
                            &gAmdMpServicesPreReqProtocolGuid,
                            EFI_NATIVE_INTERFACE,
                            &AmdMpServicesPreReqProtocol
                            );
    Status = (CalledStatus > Status) ? CalledStatus : Status;

    //
    // Set up call back after MP services are available.
    //
    CalledStatus = gBS->CreateEventEx (
                             EVT_NOTIFY_SIGNAL,
                             TPL_NOTIFY,
                             CcxRvInitWithMpServices,
                             NULL,
                             NULL,
                             &CcxRvInitWithMpServicesEvent
                             );
    Status = (CalledStatus > Status) ? CalledStatus : Status;

    CalledStatus = gBS->RegisterProtocolNotify (
                            &gEfiMpServiceProtocolGuid,
                            CcxRvInitWithMpServicesEvent,
                            &(mRegistrationForCcxRvInitWithMpServicesEvent)
                            );
    Status = (CalledStatus > Status) ? CalledStatus : Status;

    //
    // Set up call back for OverClock.
    //
    CalledStatus = gBS->CreateEventEx (
                             EVT_NOTIFY_SIGNAL,
                             TPL_NOTIFY,
                             CcxRvOcCallback,
                             NULL,
                             NULL,
                             &CcxRvOcCallbackEvent
                             );
    Status = (CalledStatus > Status) ? CalledStatus : Status;

    CalledStatus = gBS->RegisterProtocolNotify (
                            &gAmdNbioSmuInitCompleteProtocolGuid,
                            CcxRvOcCallbackEvent,
                            &(mRegistrationForCcxRvOcCallbackEvent)
                            );
    Status = (CalledStatus > Status) ? CalledStatus : Status;


    CalledStatus = gBS->CreateEventEx (
               EVT_NOTIFY_SIGNAL,
               TPL_NOTIFY,
               CcxReadyToBoot,
               NULL,
               &gEfiEventReadyToBootGuid,
               &ReadyToBootEvent
               );
    Status = (CalledStatus > Status) ? CalledStatus : Status;

    // Publish ACPI CPU SSDT services protocol
    CalledStatus = CcxZenRvAcpiCpuSsdtServicesProtocolInstall (ImageHandle, SystemTable);
    Status = (CalledStatus > Status) ? CalledStatus : Status;

    // Publish ACPI Ccx CRAT services protocol
    CalledStatus = CcxZenRvCratServicesProtocolInstall (ImageHandle, SystemTable);
    Status = (CalledStatus > Status) ? CalledStatus : Status;

    // Publish ACPI Ccx SRAT services protocol
    CalledStatus = CcxZenRvSratServicesProtocolInstall (ImageHandle, SystemTable);
    Status = (CalledStatus > Status) ? CalledStatus : Status;

    // Publish SMBIOS services protocol
    CalledStatus = CcxZenRvSmbiosServicesProtocolInstall (ImageHandle, SystemTable);
    Status = (CalledStatus > Status) ? CalledStatus : Status;

    // Install gAmdCcxDxeInitCompleteProtocolGuid protocol
    mCcxDxeInitCompleteProtocol.Revision = AMD_CCX_PROTOCOL_REVISION;
    Handle = NULL;
    CalledStatus = gBS->InstallProtocolInterface (
                            &Handle,
                            &gAmdCcxDxeInitCompleteProtocolGuid,
                            EFI_NATIVE_INTERFACE,
                            &mCcxDxeInitCompleteProtocol
                            );
    Status = (CalledStatus > Status) ? CalledStatus : Status;

    // Save PcdAmdCcxCfgPFEHEnable to heap so it could be gotten in SMI handler
    AllocParams.RequestedBufferSize = sizeof (BOOLEAN);
    AllocParams.BufferHandle = AMD_PFEH_HANDLE;
    AllocParams.Persist = HEAP_SYSTEM_MEM;

    if (HeapAllocateBuffer (&AllocParams, NULL) == AGESA_SUCCESS) {
      *((BOOLEAN *) AllocParams.BufferPtr) = PcdGetBool (PcdAmdCcxCfgPFEHEnable);
    }

    AGESA_TESTPOINT (TpCcxIdsAfterApLaunch, NULL);
    IDS_HOOK (IDS_HOOK_CCX_AFTER_AP_LAUNCH, NULL, NULL);
  }

  IDS_HDT_CONSOLE (CPU_TRACE, "  AmdCcxZenRvDxeInit End\n");

  AGESA_TESTPOINT (TpCcxDxeExit, NULL);

  return (Status);
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  SetupApStartupRegion
 *
 *
 *  Description:
 *    This routine sets up the necessary code and data to launch APs.
 *
 */
VOID
SetupApStartupRegion (
  VOID
  )
{
  UINT8             i;
  EFI_STATUS        Status;
  IA32_DESCRIPTOR   BspGdtr;
  TYPE_ATTRIB       TypeAttrib;
  UINT64            EntryAddress;
  UINT32            EntrySize;
  UINT64            EntryDest;
  UINT32            Segment;
  UINT32            C3Value;
  UINT64            ApEntryInCOffset;

  C3Value = (UINT32) AsmReadCr3 ();

  BIOSEntryInfo (BIOS_FIRMWARE, INSTANCE_IGNORED, &TypeAttrib, &EntryAddress, &EntrySize, &EntryDest);

  if (TypeAttrib.Copy == 0) {
    IDS_HDT_CONSOLE (CPU_TRACE, "  First fetch is pointing to SPI\n");

    // AP first fetch must be below 4GB boundary
    ApPageAllocation = 0xFFFFFFFF;
    Status = gBS->AllocatePages (AllocateMaxAddress,
                                 EfiBootServicesData,
                                 EFI_SIZE_TO_PAGES (AP_ALLOCATION_SIZE),
                                 &ApPageAllocation
                                 );

    if (Status == EFI_SUCCESS) {
      ASSERT ((ApPageAllocation & 0xFFFFFFFF00000000) == 0);

      // Align new EntryDest on a 64KB boundary
      EntryDest = ApPageAllocation;
      EntryDest += 0xFFFF;
      EntryDest &= ~0xFFFF;
      EntrySize = 0x10000;

      IDS_HDT_CONSOLE (CPU_TRACE, "  AP CS Base = 0x%x\n", (UINT32) EntryDest);

      // Send EntryDest to PSP
      Status = PspMboxBiosSendApCsBase ((UINT32) EntryDest);
      ASSERT (Status == EFI_SUCCESS);
    } else {
      ApPageAllocation = 0;
      ASSERT (FALSE);
    }
  }

  Segment = ((UINT32) EntryDest + EntrySize - 0x10000);
  ApStartupVector = (EFI_PHYSICAL_ADDRESS) (((UINT32) EntryDest + EntrySize - 0x10000) + 0xFFF0);

  ApStartupCode[48] = (UINT8) ((Segment >> 16) & 0xFF);
  ApStartupCode[78] = (UINT8) ((Segment >> 16) & 0xFF);
  ApStartupCode[99] = (UINT8) ((Segment >> 16) & 0xFF);

  ApStartupCode[49] = (UINT8) ((Segment >> 24) & 0xFF);
  ApStartupCode[79] = (UINT8) ((Segment >> 24) & 0xFF);
  ApStartupCode[100] = (UINT8) ((Segment >> 24) & 0xFF);

  ApEntryInCOffset = (UINT64) &ApAsmCode;

  ApStartupCode[105] = (UINT8) (ApEntryInCOffset & 0xFF);
  ApStartupCode[106] = (UINT8) ((ApEntryInCOffset >> 8) & 0xFF);
  ApStartupCode[107] = (UINT8) ((ApEntryInCOffset >> 16) & 0xFF);
  ApStartupCode[108] = (UINT8) ((ApEntryInCOffset >> 24) & 0xFF);
  ApStartupCode[109] = (UINT8) ((ApEntryInCOffset >> 32) & 0xFF);
  ApStartupCode[110] = (UINT8) ((ApEntryInCOffset >> 40) & 0xFF);
  ApStartupCode[111] = (UINT8) ((ApEntryInCOffset >> 48) & 0xFF);
  ApStartupCode[112] = (UINT8) ((ApEntryInCOffset >> 56) & 0xFF);

  // Allocate some space for APs to use as stack space
  Status = gBS->AllocatePool (EfiBootServicesData,
                              (127 * 0x400), // Allocate 1K for all possible cores
                              &ApStackBasePtr);

  // Allocate space to store data at reset vector
  ApTempBufferSize = 0x410;
  Status = gBS->AllocatePool (EfiBootServicesData,
                              ApTempBufferSize,
                              &MemoryContentCopy
                              );

  gBS->SetMem (MemoryContentCopy,
               ApTempBufferSize,
               0
               );

  // Copy data at reset vector to temporary buffer so we
  // can temporarily replace it with AP start up code.
  gBS->CopyMem (MemoryContentCopy,
                (VOID *) (ApStartupVector - 0x400),
                ApTempBufferSize
                );

  gBS->SetMem ((VOID *) (ApStartupVector - 0x400),
               ApTempBufferSize,
               0
               );


  // Copy AP start up code to Segment + 0xFBF0
  gBS->CopyMem ((VOID *) (ApStartupVector - 0x400),
               (VOID *) &ApStartupCode,
               sizeof (ApStartupCode)


               );

  // Save BSP's patch level so that AP can use it to determine whether microcode patch
  // loading should be skipped
  BspPatchLevel = AsmReadMsr64 (0x0000008B);

  // Save sleep type so that AP needn't to get it by running FchReadSleepType (),
  // otherwise, it would lead into a race condition.
  SleepType = FchReadSleepType ();

  // Sync Fixed-MTRRs with BSP
  AsmMsrOr64 (0xC0010010, BIT19);

  for (i = 0; ApMsrSettingsList[i].MsrAddr != CPU_LIST_TERMINAL; i++) {
    ApMsrSettingsList[i].MsrData = AsmReadMsr64 (ApMsrSettingsList[i].MsrAddr);
  }

  // Some Fixed-MTRRs should be set according to PCDs
  UpdateApMtrrSettings (ApMsrSettingsList);

  AsmMsrAnd64 (0xC0010010, ~((UINT64) BIT19));

  // Copy BSP MSR values to Segment + 0xFF00
  ApSyncLocation = (UINT32) (ApStartupVector + 0xE);
  AllowToLaunchNextThreadLocation = (UINT32) (ApStartupVector + 0xC);
  BspMsrLocation = (UINT32) (ApStartupVector - 0x1C0);

  ASSERT (sizeof (ApMsrSettingsList) <= 0x1C0);
  gBS->CopyMem ((VOID *) ((ApStartupVector - 0x1C0)),
                (VOID *) &ApMsrSettingsList,
                sizeof (ApMsrSettingsList)
                );


  // Copy GDT Entries to Segment + 0xFFA0
  gBS->CopyMem ((VOID *) (ApStartupVector - 0x50),
                (VOID *) &GdtEntries,
                sizeof (GdtEntries)
                );

  BspGdtr.Limit = sizeof (GdtEntries) - 1;
  BspGdtr.Base = (UINTN) ApStartupVector - 0x50;

  // Copy pointer to GDT entries to Segment + 0xFFF4
  gBS->CopyMem ((VOID *) (ApStartupVector + sizeof (AsmNearJump)),
                (VOID *) &BspGdtr,
                sizeof (BspGdtr)
                );

  // Copy the near jump to AP startup code to reset vector. The near jump
  // forces execution to start from CS:FBF0
  gBS->CopyMem ((VOID *) ApStartupVector,
                (VOID *) AsmNearJump,
                sizeof (AsmNearJump)
                );

  // Copy the value of C3 to Segment + 0xFFE8
  gBS->CopyMem ((VOID *) (ApStartupVector - 0x08),
                (VOID *) &C3Value,
                sizeof (C3Value)
                );

  ApGdtDescriptor.Size = (sizeof (GdtEntries)) - 1;
  ApGdtDescriptor.Pointer = (UINT64) &GdtEntries[0];

  AsmWbinvd ();
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  RestoreResetVector
 *
 *  @param[in] TotalCoresLaunched      The number of cores that were launched by the BSC
 *
 *  Description:
 *    This routine restores the code in the AP reset vector once all the APs that
 *    were launched are done running AP code
 *
 */
VOID
RestoreResetVector (
  IN       UINT16 TotalCoresLaunched
  )
{
  UINT16  CoreNumber;

  CoreNumber = 0xFFFF;

  // Check whether the last core has completed running the AP Startup code
  do {
    gBS->CopyMem ((VOID *) &CoreNumber,
                  (VOID *) (EFI_PHYSICAL_ADDRESS) (ApSyncLocation),
                  sizeof (CoreNumber)
                  );
  } while (CoreNumber != TotalCoresLaunched);

  gBS->CopyMem ((VOID *) (ApStartupVector - 0x400),
                MemoryContentCopy,
                ApTempBufferSize
                );

  // Clean up memory allocations
  gBS->FreePool (MemoryContentCopy);

  if (ApPageAllocation != 0) {
    gBS->FreePages (ApPageAllocation, EFI_SIZE_TO_PAGES (AP_ALLOCATION_SIZE));
  }
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  RegSettingBeforeLaunchingNextThread
 *
 *  Description:
 *    Necessory register setting before launching next thread
 *
 */
VOID
RegSettingBeforeLaunchingNextThread (
  VOID
  )
{
  AMD_CONFIG_PARAMS    StdHeader;

  if (CcxIsComputeUnitPrimary (&StdHeader)) {
    AsmMsrOr64 (0xC0010403, BIT3);
  }

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  ApEntryPointInC
 *
 *  Description:
 *    This routine is the C entry point for APs and is called from ApAsmCode
 *
 */
VOID
ApEntryPointInC (
  VOID
  )
{
  AMD_CONFIG_PARAMS    StdHeader;

  CcxProgramTablesAtReset (SleepType, &StdHeader);

  if (CcxIsComputeUnitPrimary (&StdHeader)) {
    // Skip loading microcode patch on AP if BSP's patch level is 0.
    if (BspPatchLevel != 0) {
      // Using the address saved by BSP previously
      if (mUcodePatchAddr != 0) {
        AsmWriteMsr64 (0xC0010020, mUcodePatchAddr);
      }
    }

  }

  // Mca initialization
  CcxSetMca ();

  // Cac Weights initialization
  CcxZenSetCacWeights ();
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  CcxRvInitWithMpServices
 *
 *  @param[in] Event        The event that invoked this routine
 *  @param[in] Context      Unused
 *
 *  Description:
 *    This routine runs necessary routines across all APs
 *
 */
VOID
EFIAPI
CcxRvInitWithMpServices (
  IN EFI_EVENT        Event,
  IN VOID             *Context
  )
{
  UINTN                     i;
  EFI_STATUS                Status;
  AMD_CONFIG_PARAMS         StdHeader;
  EFI_MP_SERVICES_PROTOCOL  *MpServices;
  EFI_HANDLE                Handle;

  AGESA_TESTPOINT (TpCcxDxeMpCallbackEntry, NULL);

  IDS_HDT_CONSOLE (CPU_TRACE, "  CcxRvInitWithMpServices Entry\n");
  IDS_HOOK (IDS_HOOK_CCX_CUSTOM_PSTATES, NULL, NULL);

  // Install gAmdCcxOcCompleteProtocolGuid protocol after custom Pstate feature
  mCcxOcCompleteProtocol.Revision = 0;
  Handle = NULL;
  gBS->InstallProtocolInterface (
           &Handle,
           &gAmdCcxOcCompleteProtocolGuid,
           EFI_NATIVE_INTERFACE,
           &mCcxOcCompleteProtocol
           );

  CcxZenRvInitializeC6 (&StdHeader);

  CcxZenRvInitializeCpb (&StdHeader);

  CcxZenRvInitializePrefetchMode (&StdHeader);

  Status = gBS->LocateProtocol (&gEfiMpServiceProtocolGuid, NULL, &MpServices);
  ASSERT (!EFI_ERROR (Status));
  if (EFI_ERROR (Status)) {
    AGESA_TESTPOINT (TpCcxDxeMpCallbackAbort, NULL);
    return;
  }

  // Get PCD here for CcxZenZpSetMiscMsrs
  // APs should avoid getting PCD
  mPcdAmdRedirectForReturnDis = PcdGet8 (PcdAmdRedirectForReturnDis);
  mPcdAmdStreamingStoresCtrl = PcdGet8 (PcdAmdStreamingStoresCtrl);

  MpServices->StartupAllAPs (
      MpServices,
      CcxZenRvSetMiscMsrs,
      FALSE,
      NULL,
      0,
      NULL,
      NULL
  );
  CcxZenRvSetMiscMsrs (NULL);

  for (i = 0; i < (sizeof (mLateMsrSyncTable) / sizeof (mLateMsrSyncTable[0])); i++) {
    mLateMsrSyncTable[i].MsrData = AsmReadMsr64 (mLateMsrSyncTable[i].MsrAddr);
  }
  MpServices->StartupAllAPs (
      MpServices,
      CcxZenRvSyncMiscMsrs,
      FALSE,
      NULL,
      0,
      NULL,
      NULL
  );

  Status = CcxSmmAccess2ProtocolInstall ();
  if (Status != EFI_SUCCESS) {
    IDS_HDT_CONSOLE (CPU_TRACE, "   WARNING! CcxSmmAccess2ProtocolInstall was not installed\n");
  }

  IDS_HOOK (IDS_HOOK_CCX_AFTER_PWR_MNG, NULL, NULL);

  IDS_HDT_CONSOLE (CPU_TRACE, "  CcxRvInitWithMpServices Exit\n");

  AGESA_TESTPOINT (TpCcxDxeMpCallbackExit, NULL);
}

VOID
EFIAPI
CcxRvOcCallback (
  IN EFI_EVENT        Event,
  IN VOID             *Context
  )
{
  EFI_HANDLE Handle;

  AGESA_TESTPOINT (TpCcxDxeOcCallbackEntry, NULL);
  IDS_HDT_CONSOLE (CPU_TRACE, "  CcxRvOcCallback Entry\n");

  CcxZenRvInitializeCpb (NULL);

  IDS_HOOK (IDS_HOOK_CCX_CUSTOM_PSTATES, NULL, NULL);

  // Install gAmdCcxOcCompleteProtocolGuid protocol after custom Pstate feature
  mCcxOcCompleteProtocol.Revision = 0;
  Handle = NULL;
  gBS->InstallProtocolInterface (
           &Handle,
           &gAmdCcxOcCompleteProtocolGuid,
           EFI_NATIVE_INTERFACE,
           &mCcxOcCompleteProtocol
           );

  IDS_HDT_CONSOLE (CPU_TRACE, "  CcxRvOcCallback Exit\n");
  AGESA_TESTPOINT (TpCcxDxeOcCallbackExit, NULL);
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  CcxZenRvSetMiscMsrs
 *
 *  Description:
 *    This routine sets miscellaneous MSRs:
 *    - Forces TSC recalculation
 *    - MSRC001_1023[49, TwCfgCombineCr0Cd]
 *
 */
VOID
CcxZenRvSetMiscMsrs (
  IN       VOID  *Void
  )
{
  UINT64  LocalMsrRegister;

  // Force recalc of TSC on all threads after loading patch
  LocalMsrRegister = AsmReadMsr64 (0xC0010064);
  AsmWriteMsr64 (0xC0010064, LocalMsrRegister);

  if (CcxIsComputeUnitPrimary (NULL)) {
    // MSRC001_1023[49, TwCfgCombineCr0Cd] = 1
    AsmMsrOr64 (0xC0011023, BIT49);
  }

  // MSR_C001_1029[14]
  if (mPcdAmdRedirectForReturnDis != 0xFF) {
    AsmMsrAndThenOr64 (0xC0011029, ~(UINT64) BIT14, LShiftU64 ((mPcdAmdRedirectForReturnDis & 1), 14));
  }

  // MSR_C001_1020[28]
  if (mPcdAmdStreamingStoresCtrl != 0xFF) {
    AsmMsrAndThenOr64 (0xC0011020, ~(UINT64) BIT28, LShiftU64 ((mPcdAmdStreamingStoresCtrl & 1), 28));
  }

}


/* -----------------------------------------------------------------------------*/
/**
 *
 *  CcxZenRvSyncMiscMsrs
 *
 *  Description:
 *    This routine synchronizes the MSRs in mLateMsrSyncTable across all APs
 *
 */
VOID
CcxZenRvSyncMiscMsrs (
  IN       VOID  *Void
  )
{
  UINTN  i;

  for (i = 0; i < (sizeof (mLateMsrSyncTable) / sizeof (mLateMsrSyncTable[0])); i++) {
    AsmMsrAndThenOr64 (
        mLateMsrSyncTable[i].MsrAddr,
        ~(mLateMsrSyncTable[i].MsrMask),
        (mLateMsrSyncTable[i].MsrData & mLateMsrSyncTable[i].MsrMask)
        );
  }
}


/* -----------------------------------------------------------------------------*/
/**
 *
 *  CcxZenGetCacWeights
 *
 *  @param[in] NbioSmuServices        SMU services
 *
 *  Description:
 *    This routine gets CAC weights from SMU
 *
 */
VOID
CcxZenGetCacWeights (
  IN       DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL  *NbioSmuServices
  )
{
  NbioSmuServices->AmdSmuReadCacWeights (NbioSmuServices, ZEN_CAC_WEIGHT_NUM, mCacWeights);
}


/* -----------------------------------------------------------------------------*/
/**
 *
 *  CcxZenSetCacWeights
 *
 *  Description:
 *    This routine sets all CAC weights
 *
 */
VOID
CcxZenSetCacWeights (
  )
{
  UINT8  WeightIndex;
  UINT64 LocalMsr;

  if (CcxIsComputeUnitPrimary (NULL)) {
    LocalMsr = AsmReadMsr64 (0xC0011074);
    AsmWriteMsr64 (0xC0011074, 0);

    for (WeightIndex = 0; WeightIndex < ZEN_CAC_WEIGHT_NUM; WeightIndex++) {
      AsmWriteMsr64 (0xC0011076, WeightIndex);
      AsmWriteMsr64 (0xC0011077, mCacWeights[WeightIndex]);
    }

    AsmWriteMsr64 (0xC0011074, (LocalMsr | BIT60 | BIT63));
  }
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  CcxZenZpEnableSmee
 *
 *  Description:
 *    This routine enables secure memory encryption
 *
 */
VOID
CcxZenRvEnableSmee (
  )
{
  // MSRC001_0010[23, SMEE] = 1, dependent on CBS setting
  IDS_SKIP_HOOK (IDS_HOOK_CCX_SKIP_SMEE, NULL, NULL) {
    AsmMsrOr64 (0xC0010010, BIT23);
  }
}

/*---------------------------------------------------------------------------------------*/
/**
 * CcxReadyToBoot
 *
 * Calls CcxReadyToBoot
 *
 *  Parameters:
 *    @param[in]     Event
 *    @param[in]     *Context
 *
 *    @retval        VOID
 */
VOID
EFIAPI
CcxReadyToBoot (
  IN EFI_EVENT        Event,
  IN VOID             *Context
  )
{
  EFI_STATUS                   Status;
  EFI_SMM_CONTROL2_PROTOCOL    *SmmControl;
  UINT8                        SmiDataValue;

  IDS_HDT_CONSOLE (CPU_TRACE, "  CcxReadyToBoot");
  AGESA_TESTPOINT (TpCcxDxeRtbCallBackEntry, NULL);

  Status = gBS->LocateProtocol (
                  &gEfiSmmControl2ProtocolGuid,
                  NULL,
                  (VOID **)&SmmControl
                  );

  if (EFI_ERROR (Status)) {
    return;
  }

  SmiDataValue = PcdGet8 (PcdAmdCcxS3SaveSmi);

  SmmControl->Trigger (
                    SmmControl,
                    &SmiDataValue,
                    NULL,
                    0,
                    0
                    );

  gBS->CloseEvent (Event);

  IDS_HOOK (IDS_HOOK_CCX_READY_TO_BOOT, NULL, NULL);

  AGESA_TESTPOINT (TpCcxDxeRtbCallBackExit, NULL);
}


