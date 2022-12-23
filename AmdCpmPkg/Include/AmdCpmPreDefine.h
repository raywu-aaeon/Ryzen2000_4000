/*****************************************************************************
 *
 * Copyright 2014 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
 ******************************************************************************
 */

#ifndef _AMD_CPM_PRE_DEFINE_H_
#define _AMD_CPM_PRE_DEFINE_H_

#include <AmdCpmRevision.h>
#include <AmdCpmPlatform.h>
#include <AmdCpmDefine.h>

#if (PI_SPECIFICATION_VERSION < 0x00010000)
  #ifndef AMD_CPM_EDKII
    #define gCpmFirmwareVolumeProtocolGuid  gEfiFirmwareVolumeProtocolGuid
    #define CpmFirmwareVolume               FirmwareVolume
    #define CPM_FIRMWARE_VOLUME_PROTOCOL    EFI_FIRMWARE_VOLUME_PROTOCOL
  #else
    #define gCpmFirmwareVolumeProtocolGuid  gEfiFirmwareVolume2ProtocolGuid
    #define CpmFirmwareVolume               FirmwareVolume2
    #define CPM_FIRMWARE_VOLUME_PROTOCOL    EFI_FIRMWARE_VOLUME2_PROTOCOL
  #endif
#else
  #define gCpmFirmwareVolumeProtocolGuid    gEfiFirmwareVolume2ProtocolGuid
  #define CpmFirmwareVolume                 FirmwareVolume2
  #define CPM_FIRMWARE_VOLUME_PROTOCOL      EFI_FIRMWARE_VOLUME2_PROTOCOL
#endif

#define CPM_STRINGIZE(a)            #a
#define CPM_PROTOCOL_DEFINITION(a)  CPM_STRINGIZE (Protocol/a/a.h)
#define CPM_GUID_DEFINITION(a)      CPM_STRINGIZE (Guid/a/a.h)
#define CPM_PPI_DEFINITION(a)       CPM_STRINGIZE (Ppi/a/a.h)
#define CPM_LIBRARY_DEFINITION(a)   CPM_STRINGIZE (Library/a.h)
#define CPM_INDUSTRYSTANDARD_DEFINITION(a)  CPM_STRINGIZE (IndustryStandard/a.h)
#define CPM_CALLBACK_NAME
#define CPM_CALLBACK_VAR_TYPE
#define CPM_CALLBACK_VAR_NAME


#ifndef AMD_CPM_EDKII

  #define CpmInitializeDriverLib(x, y)    EfiInitializeDriverLib (x, y)
  #define CPM_PEI_FILE_HANDLE             EFI_FFS_FILE_HEADER*
  #define CPM_PEI_SERVICES                EFI_PEI_SERVICES
  #define gCpmPeiMemoryDiscoveredPpiGuid  gPeiMemoryDiscoveredPpiGuid
  #define CPM_SMBUS_PPI                   PEI_SMBUS_PPI
  #define gCpmPeiSmbusPpiGuid             gPeiSmbusPpiGuid
  #define CpmSmbusPpi                     PeiServices, SmbusPpi
  #define CPM_DEADLOOP                    EFI_DEADLOOP
  #define CPM_EVENT_NOTIFY_SIGNAL         EFI_EVENT_NOTIFY_SIGNAL
  #define CPM_EVENT_SIGNAL_EXIT_BOOT_SERVICES EFI_EVENT_SIGNAL_EXIT_BOOT_SERVICES
  #define CPM_TPL_NOTIFY                  EFI_TPL_NOTIFY
  #define CPM_TPL_CALLBACK                EFI_TPL_CALLBACK
  #define CpmZeroMem                      EfiZeroMem
  #define CPM_SIGNATURE_32                EFI_SIGNATURE_32
  #define gCpmSmbusProtocolGuid           gEfiSmbusProtocolGuid
  #define CPM_ACPI_SUPPORT_PROTOCOL       EFI_ACPI_SUPPORT_PROTOCOL
  #define gCpmAcpiSupportGuid             gEfiAcpiSupportGuid
  #define CpmGetSystemConfigurationTable  EfiLibGetSystemConfigurationTable
  #define CPM_SMM_SX_DISPATCH_PROTOCOL    EFI_SMM_SX_DISPATCH_PROTOCOL
  #define CPM_SMM_SX_DISPATCH_CONTEXT     EFI_SMM_SX_DISPATCH_CONTEXT
  #define CPM_SMM_SW_DISPATCH_PROTOCOL    EFI_SMM_SW_DISPATCH_PROTOCOL
  #define CPM_SMM_SW_DISPATCH_CONTEXT     EFI_SMM_SW_DISPATCH_CONTEXT
  #define CpmSmmLocateProtocol            gBS->LocateProtocol
  #define gCpmSmmSxDispatchProtocolGuid   gEfiSmmSxDispatchProtocolGuid
  #define gCpmSmmSwDispatchProtocolGuid   gEfiSmmSwDispatchProtocolGuid
  #define CpmCreateEventReadyToBoot       EfiCreateEventReadyToBoot
  #define CPM_PEI_READ_ONLY_VARIABLE_PPI  PEI_READ_ONLY_VARIABLE_PPI
  #define gCpmPeiReadOnlyVariablePpiGuid  gPeiReadOnlyVariablePpiGuid
  #define CpmGetVariable(Ppi, Name, Guid, Attr, Size, Setup) Ppi->PeiGetVariable (PeiServices, Name, &Guid, NULL, &Size, &Setup)
  #define CpmVariableAttribute            NULL
  #define CpmVariable                     Variable

  #define CPM_DEFINE_gBS                  EFI_BOOT_SERVICES *gBS
  #define CPM_DEFINE_gSmst                EFI_SMM_SYSTEM_TABLE *gSmst
  #define CPM_EXTERN_gBS                  extern EFI_BOOT_SERVICES *gBS

  #define CFG_CPM_ASL_OEM_CALLBACK        AMD_CPM_ASL_OEM_CALLBACK
  #define CFG_CPM_ASL_OEM_MLIB            AMD_CPM_ASL_OEM_MLIB
  #define CFG_AMD_CPM_ASL_CPU0            AMD_CPM_ASL_CPU0
  #define CFG_AMD_CPM_ASL_EC_NAME         AMD_CPM_ASL_EC_NAME
  #define CFG_AMD_CPM_ASL_EC_MUTEX        AMD_CPM_ASL_EC_MUTEX
  #define CFG_AMD_CPM_ASL_LPC_NAME        AMD_CPM_ASL_LPC_NAME
  #define CFG_AMD_CPM_ASL_GP17_NAME       AMD_CPM_PCIE_GP17_NAME_4
  #define CFG_AMD_CPM_ASL_GP18_NAME       AMD_CPM_PCIE_GP18_NAME_4
  #define CFG_AMD_CPM_ASL_OKEC_NAME       AMD_CPM_ASL_OKEC_NAME
  #define CFG_CPM_ACPI_RESTORE_SW_SMI     CPM_ACPI_RESTORE_SW_SMI
  #define CFG_CPM_ACPI_ENABLE_SW_SMI      CPM_ACPI_ENABLE_SW_SMI
  #define CFG_CPM_PLATFORM_ID_OVERRIDE    CPM_PLATFORM_ID_OVERRIDE
  #define CFG_CPM_ECRAM_BASE_ADDR         CPM_ECRAM_BASE_ADDR
  #define CFG_CPM_ECRAM_GPIO_OFFSET       CPM_ECRAM_GPIO_OFFSET
  #define CFG_CPM_SWSMICMD_SETAUTOUMAMODE CPM_SWSMICMD_SETAUTOUMAMODE
  #define CFG_CPM_ACPI_DISABLE_DGPU_AUDIO_SW_SMI    CPM_ACPI_DISABLE_DGPU_AUDIO_SW_SMI
  #define CFG_AMD_CPM_ASL_ACP_NAME        AMD_CPM_ASL_ACP_NAME
  #define CFG_AMD_CPM_ASL_AZALIA_NAME     AMD_CPM_ASL_AZALIA_NAME
  #define CFG_AMD_CPM_ASL_LAN_NAME        AMD_CPM_ASL_LAN_NAME
  #define CFG_AMD_CPM_ASL_WLAN_NAME       AMD_CPM_ASL_WLAN_NAME

  #define CFG_CPM_X86_IO_REMAP_BASE       CPM_X86_IO_REMAP_BASE
  #define CFG_CPM_PCI_MMIO_BASE           CPM_PCI_MMIO_BASE

  #define CPM_SET_CURRENT_PLATFORM_ID(x)
  #define CPM_SET_ORIGINAL_PLATFORM_ID(x)

  #define If_CpmBuildGuidHob(Guid, Hob, Data, Size, Status) Status = PeiBuildHobGuid (PeiServices, &Guid, Size, &Hob); \
    if (!EFI_ERROR (Status)) { \
      ((EFI_HOB_GUID_TYPE *) Hob) ++; \
      if (Data) { \
        CpmCopyMem (Hob, Data, Size); \
      } \
    }  \
    if (!EFI_ERROR (Status)) \

  #define CpmSetAcpiTable(AcpiSupport, CurrentTable, Flag, Mask, Size, TableList, Status) \
    Status = AcpiSupport->SetAcpiTable ( \
            AcpiSupport, \
            CurrentTable, \
            Flag, \
            Mask, \
            &TableList \
            ); \

  #define If_CpmGetHobBuffer(HobList, Guid, Buffer, BufferSize, GuidHob) \
    if (GetNextGuidHob (&HobList, &Guid, &Buffer, &BufferSize) == EFI_SUCCESS ) \


  #define If_CpmInSmm(ImageHandle, SystemTable, gBS, gSmst, Status) \
    BOOLEAN                         InSmm; \
    EFI_HANDLE                      SmmImageHandle; \
    EFI_SMM_BASE_PROTOCOL           *SmmBase; \
    EFI_LOADED_IMAGE_PROTOCOL       *LoadedImage; \
    EFI_DEVICE_PATH_PROTOCOL        *ImageDevicePath; \
    EFI_DEVICE_PATH_PROTOCOL        *CompleteFilePath; \
    InSmm   = FALSE; \
    gBS     = SystemTable->BootServices; \
    RECORD_TIME_DXE (BeginAmdCpmInitSmmDriver); \
    Status = gBS->LocateProtocol (&gEfiSmmBaseProtocolGuid, NULL, (VOID**)&SmmBase); \
    if (EFI_ERROR (Status)) { \
      return Status; \
    } \
    SmmBase->GetSmstLocation (SmmBase, &gSmst); \
    SmmBase->InSmm (SmmBase, &InSmm); \
    if (!InSmm) { \
      if (ImageHandle != NULL) { \
        Status = gBS->HandleProtocol (ImageHandle, &gEfiLoadedImageProtocolGuid, (VOID**)&LoadedImage); \
        if (EFI_ERROR (Status)) { \
          return Status; \
        } \
        Status = gBS->HandleProtocol (LoadedImage->DeviceHandle, &gEfiDevicePathProtocolGuid, (VOID*) &ImageDevicePath); \
        if (EFI_ERROR (Status)) { \
          return Status; \
        } \
        CompleteFilePath = AppendDevicePath (ImageDevicePath, LoadedImage->FilePath); \
        SmmBase->Register (SmmBase, CompleteFilePath, NULL, 0, &SmmImageHandle, FALSE); \
      } \
    } else \

  #define CPM_DEFINE_CALLBACK(function, type1, var1, type2, var2) function (type1 var1, type2 var2)

#else

  #define CpmInitializeDriverLib(x, y)
  #define CPM_PEI_FILE_HANDLE             EFI_PEI_FILE_HANDLE
  #define CPM_PEI_SERVICES                CONST EFI_PEI_SERVICES
  #define gCpmPeiMemoryDiscoveredPpiGuid  gEfiPeiMemoryDiscoveredPpiGuid
  #define CPM_SMBUS_PPI                   EFI_PEI_SMBUS2_PPI
  #define gCpmPeiSmbusPpiGuid             gEfiPeiSmbus2PpiGuid
  #define CpmSmbusPpi                     SmbusPpi
  #define CPM_DEADLOOP                    CpuDeadLoop
  #define CPM_EVENT_NOTIFY_SIGNAL         EVT_NOTIFY_SIGNAL
  #define CPM_EVENT_SIGNAL_EXIT_BOOT_SERVICES EVT_SIGNAL_EXIT_BOOT_SERVICES
  #define CPM_TPL_NOTIFY                  TPL_NOTIFY
  #define CPM_TPL_CALLBACK                TPL_CALLBACK
  #define CpmZeroMem                      ZeroMem
  #define CPM_SIGNATURE_32                SIGNATURE_32
  #define gCpmSmbusProtocolGuid           gEfiSmbusHcProtocolGuid
  #define CPM_ACPI_SUPPORT_PROTOCOL       EFI_ACPI_TABLE_PROTOCOL
  #define gCpmAcpiSupportGuid             gEfiAcpiTableProtocolGuid
  #define CpmGetSystemConfigurationTable  EfiGetSystemConfigurationTable
  #define CPM_PEI_READ_ONLY_VARIABLE_PPI  EFI_PEI_READ_ONLY_VARIABLE2_PPI
  #define gCpmPeiReadOnlyVariablePpiGuid  gEfiPeiReadOnlyVariable2PpiGuid
  #define CpmGetVariable(Ppi, Name, Guid, Attr, Size, Setup) Ppi->GetVariable (Ppi, Name, &Guid, &Attr, &Size, &Setup)
  #define CpmVariable                     ReadOnlyVariable2
  #define CpmVariableAttribute EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS

  #define CPM_SMM_SX_DISPATCH_PROTOCOL    EFI_SMM_SX_DISPATCH2_PROTOCOL
  #define CPM_SMM_SX_DISPATCH_CONTEXT     EFI_SMM_SX_REGISTER_CONTEXT
  #define CPM_SMM_SW_DISPATCH_PROTOCOL    EFI_SMM_SW_DISPATCH2_PROTOCOL
  #define CPM_SMM_SW_DISPATCH_CONTEXT     EFI_SMM_SW_REGISTER_CONTEXT
  #define CpmSmmLocateProtocol            gSmst->SmmLocateProtocol
  #define gCpmSmmSxDispatchProtocolGuid   gEfiSmmSxDispatch2ProtocolGuid
  #define gCpmSmmSwDispatchProtocolGuid   gEfiSmmSwDispatch2ProtocolGuid
  #define CpmCreateEventReadyToBoot       EfiCreateEventReadyToBootEx

  #define CPM_DEFINE_gBS
  #define CPM_DEFINE_gSmst
  #define CPM_EXTERN_gBS

  #define CFG_CPM_ASL_OEM_CALLBACK        PcdGet32 (OemCallBackAslName)
  #define CFG_CPM_ASL_OEM_MLIB            PcdGet32 (OemMLibAslName)
  #define CFG_AMD_CPM_ASL_CPU0            PcdGet32 (Cpu0AslName)
  #define CFG_AMD_CPM_ASL_EC_NAME         PcdGet32 (EcAslName)
  #define CFG_AMD_CPM_ASL_EC_MUTEX        PcdGet32 (EcMutexAslName)
  #define CFG_AMD_CPM_ASL_LPC_NAME        PcdGet32 (LpcAslName)
  #define CFG_AMD_CPM_ASL_GP17_NAME       PcdGet32 (PcieGp17AslName)
  #define CFG_AMD_CPM_ASL_GP18_NAME       PcdGet32 (PcieGp18AslName)
  #define CFG_AMD_CPM_ASL_OKEC_NAME       PcdGet32 (OkEcAslName)
  #define CFG_CPM_ACPI_RESTORE_SW_SMI     PcdGet8 (AcpiRestoreSwSmi)
  #define CFG_CPM_ACPI_ENABLE_SW_SMI      PcdGet8 (AcpiEnableSwSmi)
  #define CFG_CPM_PLATFORM_ID_OVERRIDE    PcdGet16 (PlatformIdOverride)
  #define CFG_CPM_ECRAM_BASE_ADDR         PcdGet16 (EcRamBaseAddr)
  #define CFG_CPM_ECRAM_GPIO_OFFSET       PcdGet8 (EcRamGpioOffset)
  #define CFG_CPM_SWSMICMD_SETAUTOUMAMODE PcdGet8 (SwSmiCmdSetAutoUmaMode)
  #define CFG_CPM_ACPI_DISABLE_DGPU_AUDIO_SW_SMI    PcdGet8 (AcpiDisableDgpuAudioSwSmi)
  #define CFG_AMD_CPM_ASL_ACP_NAME        PcdGet32 (AcpAslName)
  #define CFG_AMD_CPM_ASL_AZALIA_NAME     PcdGet32 (AzaliaAslName)
  #define CFG_AMD_CPM_ASL_LAN_NAME        PcdGet32 (LanAslName)
  #define CFG_AMD_CPM_ASL_WLAN_NAME       PcdGet32 (WLanAslName)

  #define CFG_CPM_X86_IO_REMAP_BASE       PcdGet64 (X86IoRemapBase)
  #define CFG_CPM_PCI_MMIO_BASE           PcdGet64 (PciMmioBase)

  #define CPM_SET_CURRENT_PLATFORM_ID(x)  PcdSet16 (CurrentPlatformId, x)
  #define CPM_SET_ORIGINAL_PLATFORM_ID(x) PcdSet16 (OriginalPlatformId, x)

  #define If_CpmBuildGuidHob(Guid, Hob, Data, Size, Status) Hob = BuildGuidHob (&Guid, Size); \
    if (Hob != NULL) { \
      if (Data) { \
        CpmCopyMem (Hob, Data, Size); \
      } \
    }  \
    if (Hob != NULL) \

  #define CpmSetAcpiTable(AcpiSupport, CurrentTable, Flag, Mask, Size, TableList, Status) \
    Status = AcpiSupport->InstallAcpiTable ( \
            AcpiSupport, \
            CurrentTable, \
            Size, \
            &TableList \
            ); \

  #define If_CpmGetHobBuffer(HobList, Guid, Buffer, BufferSize, GuidHob) \
    { \
      EFI_HOB_GUID_TYPE *GuidHob; \
      GuidHob = GetNextGuidHob (&Guid, HobList); \
      if (GuidHob != NULL) { \
        Buffer = GET_GUID_HOB_DATA (GuidHob); \
        BufferSize = GET_GUID_HOB_DATA_SIZE (GuidHob); \
      } \
    } \
    if (Buffer != NULL ) \

  #define If_CpmInSmm(ImageHandle, SystemTable, gBS, gSmst, Status) \
    BOOLEAN                         InSmm; \
    EFI_SMM_BASE2_PROTOCOL          *SmmBase; \
    RECORD_TIME_DXE (BeginAmdCpmInitSmmDriver); \
    Status = gBS->LocateProtocol (&gEfiSmmBase2ProtocolGuid, NULL, (VOID**)&SmmBase); \
    ASSERT_EFI_ERROR (Status); \
    if (EFI_ERROR (Status)) { \
      return Status; \
    } \
    SmmBase->InSmm (SmmBase, &InSmm); \
    if (InSmm) \

  #define CPM_DEFINE_CALLBACK(function, type1, var1, type2, var2) function (type1 var1, CONST VOID var2, VOID *CommBuffer, UINTN *CommBufferSize)

// Move the following defines to AmdCpmPkg\Include\AmdCpmPlatform.h.
// Platform BIOS should redefine the following CPU SUPPORT defines in AmdCpmPkg\Addendum\Oem\*Board*\AmdCpmPlatform.h.
// Then, copy AmdCpmPkg\Addendum\Oem\*Board*\AmdCpmPlatform.h to AmdCpmPkg\AmdCpmPlatform.h before building BIOS.
//  #define AMD_CPM_CPU_FAMILY_0x14_ON_SUPPORT
//  #define AMD_CPM_CPU_FAMILY_0x15_TN_SUPPORT
//  #define AMD_CPM_CPU_FAMILY_0x15_KV_SUPPORT
//  #define AMD_CPM_CPU_FAMILY_0x15_CZ_SUPPORT
//  #define AMD_CPM_CPU_FAMILY_0x16_KB_SUPPORT
//  #define AMD_CPM_CPU_FAMILY_0x16_ML_SUPPORT
//  #define AMD_CPM_CPU_FAMILY_0x16_NL_SUPPORT
//  #define AMD_CPM_CPU_FAMILY_0x21_AM_SUPPORT
//  #define AMD_CPM_CPU_FAMILY_0x15_ST_SUPPORT
//  #define AMD_CPM_CPU_FAMILY_0x15_BR_SUPPORT
//  #define AMD_CPM_CPU_FAMILY_0x17_ZP_SUPPORT
//  #define AMD_CPM_CPU_FAMILY_0x17_RV_SUPPORT
//  #define AMD_CPM_CPU_FAMILY_0x17_RV2_SUPPORT
//  #define AMD_CPM_CPU_FAMILY_0x17_SSP_SUPPORT
//  #define AMD_CPM_CPU_FAMILY_0x17_MTS_SUPPORT

  #ifndef EFI_PPI_DEFINITION
    #define EFI_PPI_DEFINITION(a)       CPM_STRINGIZE (Ppi/a.h)
  #endif
  #ifndef EFI_PROTOCOL_DEFINITION
    #define EFI_PROTOCOL_DEFINITION(a)  CPM_STRINGIZE (Protocol/a.h)
  #endif
  #ifndef EFI_GUID_DEFINITION
    #define EFI_GUID_DEFINITION(a)      CPM_STRINGIZE (Guid/a.h)
  #endif

#endif

#endif
