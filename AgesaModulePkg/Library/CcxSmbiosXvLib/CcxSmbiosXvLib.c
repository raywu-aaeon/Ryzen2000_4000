/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD Ccx SMBIOS XV Library
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Lib
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-10 02:28:05 +0800 (Wed, 10 Dec 2014) $
 *
 */
/*
 ******************************************************************************
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

#include <Library/BaseLib.h>
#include <Library/PciLib.h>
#include "AGESA.h"
#include "cpuRegisters.h"
#include "CcxRegistersXv.h"
#include "UnbRegisters.h"
#include "Filecode.h"
#include "CcxSmbiosXvCommonLib.h"
#include "Library/AmdBaseLib.h"
#include "Library/CcxSmbiosLib.h"
#include <AmdSoc.h>

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
#define FILECODE LIBRARY_CCXSMBIOSXVLIB_CCXSMBIOSXVLIB_FILECODE

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */
CONST CHAR8 ROMDATA str_A12[] = "AMD A12-";
CONST CHAR8 ROMDATA str_A10[] = "AMD A10-";
CONST CHAR8 ROMDATA str_A8[]  = "AMD A8-";
CONST CHAR8 ROMDATA str_A6[]  = "AMD A6-";
CONST CHAR8 ROMDATA str_A4[]  = "AMD A4-";
CONST CHAR8 ROMDATA str_FX[]  = "AMD FX-";
CONST CHAR8 ROMDATA str_AthlonX4[] = "AMD Athlon(TM) X4";
CONST CHAR8 ROMDATA str_R[]  = "AMD Embedded R-Series RX-";
CONST CHAR8 ROMDATA str_G[]  = "AMD Embedded G-Series GX-";
CONST CHAR8 ROMDATA str_PRO_A12[] = "AMD PRO A12-";
CONST CHAR8 ROMDATA str_PRO_A10[] = "AMD PRO A10-";
CONST CHAR8 ROMDATA str_PRO_A8[]  = "AMD PRO A8-";
CONST CHAR8 ROMDATA str_PRO_A6[]  = "AMD PRO A6-";
CONST CHAR8 ROMDATA str_PRO_A4[]  = "AMD PRO A4-";
CONST CHAR8 ROMDATA str_PRO_FX[]  = "AMD PRO FX-";
CONST CHAR8 ROMDATA str_OpteronX3[] = "AMD Opteron(TM) X3";
/*---------------------------------------------------------------------------------------
 * Processor Family Table
 *       04Bh = "R-Series"
 *       049h = "G-Series"
 *       048h = "A-Series"
 *       066h = "AMD Athlon(TM) X4 Series Processor"
 *       03Fh = "FX (TM) Series"
 *       06Ah = "AMD Opteron(TM) X3000 Series APU"
 *-------------------------------------------------------------------------------------*/

CONST CPU_T4_PROC_FAMILY ROMDATA XvT4ProcFamily[] =
{
  {str_FX,  0x3F},
  {str_A12, 0x48},
  {str_A10, 0x48},
  {str_A8,  0x48},
  {str_A6,  0x48},
  {str_A4,  0x48},
  {str_R,   0x4B},
  {str_G,   0x49},
  {str_AthlonX4,  0x66},
  {str_PRO_FX, 0x3F},
  {str_PRO_A12, 0x48},
  {str_PRO_A10, 0x48},
  {str_PRO_A8,  0x48},
  {str_PRO_A6,  0x48},
  {str_PRO_A4,  0x48},
  {str_OpteronX3, 0x6A}
};


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/* -----------------------------------------------------------------------------*/
/**
 *
 *  CcxGetProcessorFamilyForSmbios
 *
 *    Get processor family information for SMBIOS
 *
 *    @param[in]      Socket         Zero-based socket number to check
 *    @param[in]      StdHeader      Standard Head Pointer
 *
 */
UINT16
CcxGetProcessorFamilyForSmbios (
  IN       UINTN               Socket,
  IN       AMD_CONFIG_PARAMS  *StdHeader
  )
{
  CHAR8 NameString[49];
  CONST CHAR8 *DmiString;
  CONST VOID  *DmiStringTable;
  UINT8 NumberOfDmiString;
  UINT8 i;
  UINT16 ProcessofFamily;

  ProcessofFamily = P_FAMILY_UNKNOWN;

  // Get name string from MSR_C001_00[30:35]
  GetNameString (NameString, StdHeader);

  // Get DMI String
  DmiStringTable = (CONST VOID *) &XvT4ProcFamily[0];
  NumberOfDmiString = sizeof (XvT4ProcFamily) / sizeof (CPU_T4_PROC_FAMILY);

  // Find out which DMI string matches current processor's name string
  if (NumberOfDmiString != 0) {
    for (i = 0; i < NumberOfDmiString; i++) {
      DmiString = (((CPU_T4_PROC_FAMILY *) DmiStringTable)[i]).Stringstart;
      if (IsSourceStrContainTargetStr (NameString, DmiString, StdHeader)) {
        ProcessofFamily = (((CPU_T4_PROC_FAMILY *) DmiStringTable)[i]).T4ProcFamilySetting;
        break;
      }
    }
  }
  return ProcessofFamily;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  CcxGetProcessorUpgradeForSmbios
 *
 *    Get processor upgrade information for SMBIOS
 *
 *    @param[in]      Socket         Zero-based socket number to check
 *    @param[in]      StdHeader      Standard Head Pointer
 *
 */
UINT8
CcxGetProcessorUpgradeForSmbios (
  IN       UINTN               Socket,
  IN       AMD_CONFIG_PARAMS  *StdHeader
  )
{
  UINT8      PackageType;
  UINT8      ProcUpgrade;
  CPUID_DATA CpuId;

  AsmCpuid (
      AMD_CPUID_FMF,
      &(CpuId.EAX_Reg),
      &(CpuId.EBX_Reg),
      &(CpuId.ECX_Reg),
      &(CpuId.EDX_Reg)
      );
  PackageType = (UINT8) (CpuId.EBX_Reg >> 28) & 0xF; // bit 31:28

  switch (PackageType) {
  case BR_PKG_AM4:
    ProcUpgrade = P_UPGRADE_AM4;
    break;
  default:
    ProcUpgrade = P_UPGRADE_UNKNOWN;
    break;
  }
  return ProcUpgrade;
}

VOID
CcxGetCacheInfo (
  IN       UINTN               Socket,
  IN       GET_CACHE_INFO     *CacheInfo,
  IN       AMD_CONFIG_PARAMS  *StdHeader
  )
{
  UINT8                 NumOfCoresPerCU;
  UINT8                 NumOfCU;
  UINT32                CacheSize;
  UINTN                 PciAddress;
  CPUID_DATA            CpuId;
  CU_STATUS_1_REGISTER  CuStatus;

  PciAddress = CU_STATUS_1_PCI_ADDR;
  *((UINT32 *) &CuStatus) = PciRead32 (PciAddress);
  if (CuStatus.DualCore == 0) {
    NumOfCoresPerCU = 1;
  } else {
    NumOfCoresPerCU = 2;
  }

  switch (CuStatus.Enabled) {
  case 1:
  case 2:
    NumOfCU = 1;
    break;
  case 3:
    NumOfCU = 2;
    break;
  default:
    NumOfCU = 1;
    ASSERT (FALSE);
  }

  // L1 Size & Associativity
  AsmCpuid (
      AMD_CPUID_TLB_L1Cache,
      &(CpuId.EAX_Reg),
      &(CpuId.EBX_Reg),
      &(CpuId.ECX_Reg),
      &(CpuId.EDX_Reg)
      );
  CacheSize  = ((CpuId.ECX_Reg >> 24) * NumOfCoresPerCU + (CpuId.EDX_Reg >> 24)) * NumOfCU;
  CacheInfo->CacheEachLevelInfo[CpuL1Cache].CacheSize = AdjustGranularity (&CacheSize);
  CacheInfo->CacheEachLevelInfo[CpuL1Cache].Associativity = DMI_ASSOCIATIVE_2_WAY; // Per the BKDG, this is hard-coded to 2-Way.

  // L2 Size & Associativity
  AsmCpuid (
      AMD_CPUID_L2L3Cache_L2TLB,
      &(CpuId.EAX_Reg),
      &(CpuId.EBX_Reg),
      &(CpuId.ECX_Reg),
      &(CpuId.EDX_Reg)
      );
  CacheSize = (CpuId.ECX_Reg >> 16) * NumOfCU;
  CacheInfo->CacheEachLevelInfo[CpuL2Cache].CacheSize = AdjustGranularity (&CacheSize);
  CacheInfo->CacheEachLevelInfo[CpuL2Cache].Associativity = DMI_ASSOCIATIVE_16_WAY; // Per the BKDG, this is hard-coded to 16-Way.

  // L3 Size & Associativity
  CacheInfo->CacheEachLevelInfo[CpuL3Cache].CacheSize = 0;
  CacheInfo->CacheEachLevelInfo[CpuL3Cache].Associativity = DMI_ASSOCIATIVE_UNKNOWN;
}

/*---------------------------------------------------------------------------------------
 *                           L O C A L    F U N C T I O N S
 *---------------------------------------------------------------------------------------
 */


