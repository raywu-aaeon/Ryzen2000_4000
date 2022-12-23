/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD CPU SMBIOS functions.
 *
 * Contains code for collecting SMBIOS information
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Ccx
 * @e \$Revision: 315062 $   @e \$Date: 2015-03-19 07:54:52 +0800 (Thu, 19 Mar 2015) $
 *
 */
/*
 ****************************************************************************
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

/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include "Porting.h"
#include "AMD.h"
#include "Filecode.h"
#include "cpuRegisters.h"
#include <Library/BaseLib.h>
#include <Library/AmdBaseLib.h>
#include <Library/CcxBaseX86Lib.h>
#include <Library/CcxSmbiosLib.h>
#include <Library/CcxPstatesLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/AmdNbioSmuServicesProtocol.h>
#include <Protocol/AmdSmbiosServicesProtocol.h>

#define FILECODE CCX_ZEN_CCXZENRVDXE_CCXZENRVSMBIOSDXE_FILECODE

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */
EFI_STATUS
EFIAPI
ZenRvGetCoreDmiInfo (
  IN       AMD_CCX_SMBIOS_SERVICES_PROTOCOL       *This,
  IN       UINTN                                   Socket,
     OUT   AMD_CCX_CORE_DMI_INFO                  *CoreDmiInfo
  );

EFI_STATUS
EFIAPI
ZenRvGetCacheDmiInfo (
  IN       AMD_CCX_SMBIOS_SERVICES_PROTOCOL       *This,
  IN       UINTN                                   Socket,
     OUT   AMD_CACHE_DMI_INFO                     *CacheDmiInfo
  );

/*----------------------------------------------------------------------------------------
 *                           G L O B A L   V A R I A B L E S
 *----------------------------------------------------------------------------------------
 */
STATIC AMD_CCX_SMBIOS_SERVICES_PROTOCOL   mZenRvDmiServicesProtocol = {
  SMBIOS_3_1_1,      // Support SMBIOS 3.1.1
  ZenRvGetCoreDmiInfo,
  ZenRvGetCacheDmiInfo
};

CHAR8 ROMDATA str_ProcManufacturer[] = "Advanced Micro Devices, Inc.";

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

EFI_STATUS
EFIAPI
CcxZenRvSmbiosServicesProtocolInstall (
  IN       EFI_HANDLE        ImageHandle,
  IN       EFI_SYSTEM_TABLE  *SystemTable
  )
{
  // Install SMBIOS services protocol
  return gBS->InstallProtocolInterface (
                &ImageHandle,
                &gAmdCcxSmbiosServicesProtocolGuid,
                EFI_NATIVE_INTERFACE,
                &mZenRvDmiServicesProtocol
                );
}

/*----------------------------------------------------------------------------------------
 *                          L O C A L    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */
/**
 *  This service retrieves DMI information about the core.
 *
 * @param[in]  This                                 A pointer to the
 *                                                  AMD_CCX_SMBIOS_SERVICES_PROTOCOL instance.
 * @param[in]  Socket                               Zero-based socket number to check.
 * @param[out] CoreDmiInfo                          Contains core DMI information
 *
 * @retval EFI_SUCCESS                              The core DMI information was successfully retrieved.
 * @retval EFI_INVALID_PARAMETER                    CoreDmiInfo is NULL.
 *
 **/
EFI_STATUS
EFIAPI
ZenRvGetCoreDmiInfo (
  IN       AMD_CCX_SMBIOS_SERVICES_PROTOCOL       *This,
  IN       UINTN                                   Socket,
     OUT   AMD_CCX_CORE_DMI_INFO                  *CoreDmiInfo
  )
{
  UINT8                                 ByteIndexInUint64;
  UINT16                                Index;
  UINT32                                FuseValue;
  UINT32                                CoreCountByFuse;
  UINT32                                SmtEnByFuse;
  UINT32                                Fmax;
  UINT32                                CoreDisFuse;
  UINT64                                MsrData;
  UINTN                                 Frequency;
  UINTN                                 VoltageInuV;
  UINTN                                 PowerInmW;
  CPUID_DATA                            CpuId;
  AMD_CONFIG_PARAMS                     StdHeader;
  EFI_STATUS                            Status;
  DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL    *NbioSmuServices;

  NbioSmuServices = NULL;
  CoreDisFuse     = 0;
  Status = gBS->LocateProtocol (
                  &gAmdNbioSmuServicesProtocolGuid,
                  NULL,
                  &NbioSmuServices
                  );
  ASSERT (!EFI_ERROR (Status));


  // Type 4 Offset 0x05, Processor Type
  CoreDmiInfo->ProcessorType = CENTRAL_PROCESSOR;

  // Type 4 Offset 0x06, Processor Family
  CoreDmiInfo->ProcessorFamily = CcxGetProcessorFamilyForSmbios (0, &StdHeader);

  // Type4 Offset 0x08, Processor ID
  AsmCpuid (
      AMD_CPUID_APICID_LPC_BID,
      &(CpuId.EAX_Reg),
      &(CpuId.EBX_Reg),
      &(CpuId.ECX_Reg),
      &(CpuId.EDX_Reg)
      );
  CoreDmiInfo->ProcessorID.EaxFamilyId = CpuId.EAX_Reg;
  CoreDmiInfo->ProcessorID.EdxFeatureId = CpuId.EDX_Reg;

  // Type4 Offset 0x11/0x16, Voltage/Current Speed
  CcxGetPstateInfo (0, SwPstate0, &Frequency, &VoltageInuV, &PowerInmW, &StdHeader);
  CoreDmiInfo->Voltage = (UINT8) ((VoltageInuV + 50000) / 100000 + 0x80); // Voltage = 0x80 + Voltage * 10
  CoreDmiInfo->CurrentSpeed = (UINT16) Frequency;

  // Type4 Offset 0x14, Max Speed
  if (NbioSmuServices == NULL) {
    CoreDmiInfo->MaxSpeed = CoreDmiInfo->CurrentSpeed;
  } else {
    NbioSmuServices->AmdSmuRegisterRead (NbioSmuServices, 0, 0x5D254, &CoreDisFuse);
    NbioSmuServices->AmdSmuRegisterRead (NbioSmuServices, 0, 0x5D494, &FuseValue);
    Fmax = FuseValue & 0xFF;
    CoreDmiInfo->MaxSpeed = (UINT16) (Fmax * 25);
  }

  // Type4 Offset 0x12, External Clock
  CoreDmiInfo->ExternalClock = EXTERNAL_CLOCK_100MHZ;

  // Type4 Offset 0x18, Status
  CoreDmiInfo->Status = SOCKET_POPULATED | CPU_STATUS_ENABLED;

  // Type4 Offset 0x19, Processor Upgrade
  CoreDmiInfo->ProcessorUpgrade = CcxGetProcessorUpgradeForSmbios (0, &StdHeader);

  // Type4 Offset 0x23/0x25, Core Count/Thread Count
  AsmCpuid (
      AMD_CPUID_ASIZE_PCCOUNT,
      &(CpuId.EAX_Reg),
      &(CpuId.EBX_Reg),
      &(CpuId.ECX_Reg),
      &(CpuId.EDX_Reg)
      );

  if (NbioSmuServices != NULL) {
    // Get Core Count/Thread Count from FUSE
    SmtEnByFuse = ((CoreDisFuse >> 8) & 1) + 1;
    CoreDisFuse = CoreDisFuse & 0xFF;
    CoreCountByFuse = 4;
    while (CoreDisFuse != 0) {
      if ((CoreDisFuse & 1) == 1) {
        CoreCountByFuse--;
      }
      CoreDisFuse = CoreDisFuse >> 1;
    }

    CoreDmiInfo->CoreCount = (UINT16) CoreCountByFuse;
    CoreDmiInfo->ThreadCount = (UINT16) (CoreDmiInfo->CoreCount * SmtEnByFuse);
  } else {
    // Get Core Count/Thread Count from registers
    CoreDmiInfo->ThreadCount = (UINT16) ((CpuId.ECX_Reg & 0xFF) + 1); // bit 7:0
    CoreDmiInfo->CoreCount = CoreDmiInfo->ThreadCount / CcxGetThreadsPerCore ();
  }

  // Type4 Offset 0x24 Core Enabled
  CoreDmiInfo->CoreEnabled = (UINT16) (((CpuId.ECX_Reg & 0xFF) + 1) / CcxGetThreadsPerCore ());

  // Type4 Offset 0x26, Processor Characteristics
  CoreDmiInfo->ProcessorCharacteristics = P_CHARACTERISTICS_ZEN;

  // Type4 ProcessorVersion
  for (Index = 0; Index <= 5; Index++) {
    MsrData = AsmReadMsr64 ((MSR_CPUID_NAME_STRING0 + Index));
    for (ByteIndexInUint64 = 0; ByteIndexInUint64 <= 7; ByteIndexInUint64++) {
      CoreDmiInfo->ProcessorVersion[Index * 8 + ByteIndexInUint64] = (UINT8) RShiftU64 (MsrData, (8 * ByteIndexInUint64));
    }
  }

  // Type4 ProcessorManufacturer
  ASSERT (PROC_MANU_LENGTH >= sizeof (str_ProcManufacturer));
  LibAmdMemCopy (CoreDmiInfo->ProcessorManufacturer, str_ProcManufacturer, sizeof (str_ProcManufacturer), &StdHeader);

  return EFI_SUCCESS;
}


/**
 * This service retrieves information about the cache.
 *
 * @param[in]  This                                 A pointer to the
 *                                                  AMD_CCX_SMBIOS_SERVICES_PROTOCOL instance.
 * @param[in]  Socket                               Zero-based socket number to check.
 * @param[out] CacheDmiInfo                         Contains cache DMI information
 *
 * @retval EFI_SUCCESS                              The cache DMI information was successfully retrieved.
 * @retval EFI_INVALID_PARAMETER                    CacheDmiInfo is NULL.
 *
 **/
EFI_STATUS
EFIAPI
ZenRvGetCacheDmiInfo (
  IN       AMD_CCX_SMBIOS_SERVICES_PROTOCOL       *This,
  IN       UINTN                                   Socket,
     OUT   AMD_CACHE_DMI_INFO                     *CacheDmiInfo
  )
{
  GET_CACHE_INFO     CacheInfo;
  AMD_CONFIG_PARAMS  StdHeader;

  CcxGetCacheInfo (0, &CacheInfo, &StdHeader);

  // Type7 Offset 0x05, Cache Configuration
  CacheDmiInfo->CacheEachLevelInfo[CpuL1Cache].CacheCfg = CACHE_CFG_L1;
  CacheDmiInfo->CacheEachLevelInfo[CpuL2Cache].CacheCfg = CACHE_CFG_L2;
  CacheDmiInfo->CacheEachLevelInfo[CpuL3Cache].CacheCfg = CACHE_CFG_L3;

  // Type7 Offset 0x07 and 09, Maximum Cache Size and Installed Size

  // Maximum L1 cache size
  if (CacheInfo.CacheEachLevelInfo[CpuL1Cache].CacheSize > 0xFFFF) {
    CacheDmiInfo->CacheEachLevelInfo[CpuL1Cache].MaxCacheSize  = 0xFFFF;
    CacheDmiInfo->CacheEachLevelInfo[CpuL1Cache].MaxCacheSize2 = CacheInfo.CacheEachLevelInfo[CpuL1Cache].CacheSize;
  } else {
    CacheDmiInfo->CacheEachLevelInfo[CpuL1Cache].MaxCacheSize  = (UINT16) CacheInfo.CacheEachLevelInfo[CpuL1Cache].CacheSize;
    CacheDmiInfo->CacheEachLevelInfo[CpuL1Cache].MaxCacheSize2 = ((CacheInfo.CacheEachLevelInfo[CpuL1Cache].CacheSize & 0x7FFF) |
                                                                 ((CacheInfo.CacheEachLevelInfo[CpuL1Cache].CacheSize & 0x8000) << 16));
  }

  // Installed L1 cache size
  CacheDmiInfo->CacheEachLevelInfo[CpuL1Cache].InstallSize  = CacheDmiInfo->CacheEachLevelInfo[CpuL1Cache].MaxCacheSize;
  CacheDmiInfo->CacheEachLevelInfo[CpuL1Cache].InstallSize2 = CacheDmiInfo->CacheEachLevelInfo[CpuL1Cache].MaxCacheSize2;

  // Maximum L2 cache size
  if (CacheInfo.CacheEachLevelInfo[CpuL2Cache].CacheSize > 0xFFFF) {
    CacheDmiInfo->CacheEachLevelInfo[CpuL2Cache].MaxCacheSize  = 0xFFFF;
    CacheDmiInfo->CacheEachLevelInfo[CpuL2Cache].MaxCacheSize2 = CacheInfo.CacheEachLevelInfo[CpuL2Cache].CacheSize;
  } else {
    CacheDmiInfo->CacheEachLevelInfo[CpuL2Cache].MaxCacheSize  = (UINT16) CacheInfo.CacheEachLevelInfo[CpuL2Cache].CacheSize;
    CacheDmiInfo->CacheEachLevelInfo[CpuL2Cache].MaxCacheSize2 = ((CacheInfo.CacheEachLevelInfo[CpuL2Cache].CacheSize & 0x7FFF) |
                                                                 ((CacheInfo.CacheEachLevelInfo[CpuL2Cache].CacheSize & 0x8000) << 16));
  }

  // Installed L2 cache size
  CacheDmiInfo->CacheEachLevelInfo[CpuL2Cache].InstallSize  = CacheDmiInfo->CacheEachLevelInfo[CpuL2Cache].MaxCacheSize;
  CacheDmiInfo->CacheEachLevelInfo[CpuL2Cache].InstallSize2 = CacheDmiInfo->CacheEachLevelInfo[CpuL2Cache].MaxCacheSize2;

  // Maximum L3 cache size
  if (CacheInfo.CacheEachLevelInfo[CpuL3Cache].CacheSize > 0xFFFF) {
    CacheDmiInfo->CacheEachLevelInfo[CpuL3Cache].MaxCacheSize  = 0xFFFF;
    CacheDmiInfo->CacheEachLevelInfo[CpuL3Cache].MaxCacheSize2 = CacheInfo.CacheEachLevelInfo[CpuL3Cache].CacheSize;
  } else {
    CacheDmiInfo->CacheEachLevelInfo[CpuL3Cache].MaxCacheSize  = (UINT16) CacheInfo.CacheEachLevelInfo[CpuL3Cache].CacheSize;
    CacheDmiInfo->CacheEachLevelInfo[CpuL3Cache].MaxCacheSize2 = ((CacheInfo.CacheEachLevelInfo[CpuL3Cache].CacheSize & 0x7FFF) |
                                                                 ((CacheInfo.CacheEachLevelInfo[CpuL3Cache].CacheSize & 0x8000) << 16));
  }

  // Installed L3 cache size
  CacheDmiInfo->CacheEachLevelInfo[CpuL3Cache].InstallSize  = CacheDmiInfo->CacheEachLevelInfo[CpuL3Cache].MaxCacheSize;
  CacheDmiInfo->CacheEachLevelInfo[CpuL3Cache].InstallSize2 = CacheDmiInfo->CacheEachLevelInfo[CpuL3Cache].MaxCacheSize2;

  // Type7 Offset 0x0B and 0D, Supported SRAM Type and Current SRAM Type
  CacheDmiInfo->CacheEachLevelInfo[CpuL1Cache].SupportedSramType = SRAM_TYPE_PIPELINE_BURST;
  CacheDmiInfo->CacheEachLevelInfo[CpuL1Cache].CurrentSramType   = SRAM_TYPE_PIPELINE_BURST;
  CacheDmiInfo->CacheEachLevelInfo[CpuL2Cache].SupportedSramType = SRAM_TYPE_PIPELINE_BURST;
  CacheDmiInfo->CacheEachLevelInfo[CpuL2Cache].CurrentSramType   = SRAM_TYPE_PIPELINE_BURST;
  CacheDmiInfo->CacheEachLevelInfo[CpuL3Cache].SupportedSramType = SRAM_TYPE_PIPELINE_BURST;
  CacheDmiInfo->CacheEachLevelInfo[CpuL3Cache].CurrentSramType   = SRAM_TYPE_PIPELINE_BURST;

  // Type7 Offset 0x0F, Cache Speed
  CacheDmiInfo->CacheEachLevelInfo[CpuL1Cache].CacheSpeed = 1;
  CacheDmiInfo->CacheEachLevelInfo[CpuL2Cache].CacheSpeed = 1;
  CacheDmiInfo->CacheEachLevelInfo[CpuL3Cache].CacheSpeed = 1;

  // Type7 Offset 0x10, Error Correction Type
  CacheDmiInfo->CacheEachLevelInfo[CpuL1Cache].ErrorCorrectionType = ERR_CORRECT_TYPE_MULTI_BIT_ECC;
  CacheDmiInfo->CacheEachLevelInfo[CpuL2Cache].ErrorCorrectionType = ERR_CORRECT_TYPE_MULTI_BIT_ECC;
  CacheDmiInfo->CacheEachLevelInfo[CpuL3Cache].ErrorCorrectionType = ERR_CORRECT_TYPE_MULTI_BIT_ECC;

  // Type7 Offset 0x11, System Cache Type
  CacheDmiInfo->CacheEachLevelInfo[CpuL1Cache].SystemCacheType = CACHE_TYPE_UNIFIED;
  CacheDmiInfo->CacheEachLevelInfo[CpuL2Cache].SystemCacheType = CACHE_TYPE_UNIFIED;
  CacheDmiInfo->CacheEachLevelInfo[CpuL3Cache].SystemCacheType = CACHE_TYPE_UNIFIED;

  // Type7 Offset 0x12, Associativity
  CacheDmiInfo->CacheEachLevelInfo[CpuL1Cache].Associativity = CacheInfo.CacheEachLevelInfo[CpuL1Cache].Associativity;
  CacheDmiInfo->CacheEachLevelInfo[CpuL2Cache].Associativity = CacheInfo.CacheEachLevelInfo[CpuL2Cache].Associativity;
  CacheDmiInfo->CacheEachLevelInfo[CpuL3Cache].Associativity = CacheInfo.CacheEachLevelInfo[CpuL3Cache].Associativity;

  return EFI_SUCCESS;

}


