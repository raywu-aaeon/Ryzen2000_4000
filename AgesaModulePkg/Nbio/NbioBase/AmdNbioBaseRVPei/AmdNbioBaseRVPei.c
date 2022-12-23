/* $NoKeywords:$ */
/**
 * @file
 *
 * AmdNbioBaseRVPei Driver
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  AmdNbioBaseRVPei
 * @e \$Revision: 312065 $   @e \$Date: 2015-01-30 04:23:05 -0600 (Fri, 30 Jan 2015) $
 *
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
 */
#include <AMD.h>
#include <Filecode.h>
#include <PiPei.h>
#include <GnbDxio.h>
#include <GnbRegistersRV.h>
#include <PcieComplexDataRV.h>
#include <Library/PeiServicesLib.h>
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Library/PcdLib.h>
#include <Library/HobLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/NbioRegisterAccLib.h>
#include <Library/NbioTable.h>
#include <Library/GnbHeapLib.h>
#include <Library/NbioHandleLib.h>
#include <Library/PcieConfigLib.h>
#include <Library/AmdIdsHookLib.h>
#include <Library/SmnAccessLib.h>
#include <Guid/GnbPcieInfoHob.h>
#include <Guid/AmdMemoryInfoHob.h>
#include <Guid/GnbNbioBaseZPInfoHob.h>
#include <Ppi/NbioBaseServicesZPPpi.h>
#include <IdsHookId.h>
#include <Ppi/AmdMemoryInfoHobPpi.h>
#include <Ppi/NbioPcieServicesPpi.h>
#include <NbioTablesRV.h>
#include <Protocol/FabricResourceManagerServicesProtocol.h>
#include <Library/FabricResourceManagerLib.h>
#include <Ppi/SocLogicalIdPpi.h>
#include <Library/NbioSmuV10Lib.h>

#define FILECODE  NBIO_NBIOBASE_AMDNBIOBASERVPEI_AMDNBIOBASERVPEI_FILECODE

/*----------------------------------------------------------------------------------------
 *                         E X T E R N   D E F I N I T I O N S
 *----------------------------------------------------------------------------------------
 */

typedef UINT8 GNB_TABLE;

extern RV_COMPLEX_CONFIG      ComplexDataRV;
extern GNB_TABLE ROMDATA      GnbIommuEnvInitTableRV [];

EFI_STATUS
EFIAPI
MemoryConfigDoneCallbackPpi (
  IN CONST EFI_PEI_SERVICES     **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Ppi
);

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
#define IOHCMISC_BARSIZE_1MB                  0x100000ul              ///< Size of 1MB BAR
#define IOHCMISC_BARSIZE_4KB                  0x1000                  ///< Size of 4KB BAR

#define IOHCMISC_SMN_BASE                     0x13B10000ul            ///< Define the SMN Base address for NB MISC register
#define IOHCMISC_SMU_BASE_ADDR_LO             0x2E8                   ///< Pci offset of SMU_BASE_ADDR_LO
#define IOHCMISC_SMU_BASE_ADDR_HI             0x2EC                   ///< Pci offset of SMU_BASE_ADDR_HI
#define IOHCMISC_DBG_BASE_ADDR_LO             0x2F8                   ///< Pci offset of DBG_BASE_ADDR_LO
#define IOHCMISC_DBG_BASE_ADDR_HI             0x2FC                   ///< Pci offset of DBG_BASE_ADDR_HI
#define IOHCMISC_FASTREG_BASE_ADDR_LO         0x300                   ///< Pci offset of FASTREG_BASE_ADDR_LO
#define IOHCMISC_FASTREG_BASE_ADDR_HI         0x304                   ///< Pci offset of FASTREG_BASE_ADDR_HI
#define IOHCMISC_FASTREGCNTL_BASE_ADDR_LO     0x308                   ///< Pci offset of FASTREGCNTL_BASE_ADDR_LO
#define IOHCMISC_FASTREGCNTL_BASE_ADDR_HI     0x30C                   ///< Pci offset of FASTREGCNTL_BASE_ADDR_HI
#define RV_SOCKET_AM4                         2

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */
EFI_STATUS
DebugGetConfig (
  IN  PEI_AMD_NBIO_BASE_SERVICES_PPI  *This,
  OUT GNB_BUILD_OPTIONS_ZP_DATA_HOB   **DebugOptions
  );

EFI_STATUS
GnbRegisterRead (
  IN       GNB_HANDLE                 *GnbHandle,
  IN       UINT8                      RegisterSpaceType,
  IN       UINT32                     Address,
     OUT   VOID                       *Value,
  IN       UINT32                     Flags,
  IN       AMD_CONFIG_PARAMS          *StdHeader
  );

EFI_STATUS
GnbRegisterWrite (
  IN       GNB_HANDLE                 *GnbHandle,
  IN       UINT8                      RegisterSpaceType,
  IN       UINT32                     Address,
  IN       VOID                       *Value,
  IN       UINT32                     Flags,
  IN       AMD_CONFIG_PARAMS          *StdHeader
  );

EFI_STATUS
EFIAPI
MultiDieConfigureCallbackPpi (
  IN CONST EFI_PEI_SERVICES           **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR        *NotifyDescriptor,
  IN VOID                             *Ppi
  );

EFI_STATUS
EFIAPI
MemoryConfigDoneCallbackPpi (
  IN CONST EFI_PEI_SERVICES           **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR        *NotifyDescriptor,
  IN VOID                             *Ppi
  );

EFI_STATUS
EFIAPI
NbioTopologyConfigureCallbackPpi (
  IN CONST EFI_PEI_SERVICES           **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR        *NotifyDescriptor,
  IN VOID                             *Ppi
  );

VOID
NbioNBIFParityCheckWorkaroundRV (
  IN GNB_HANDLE                       *GnbHandle
  );

VOID
EFIAPI
DmaControlSetting (
  IN       SOC_LOGICAL_ID              LogicalId,
  IN       GNB_HANDLE                  *GnbHandle
  );

/*----------------------------------------------------------------------------------------
 *                    P P I   N O T I F Y   D E S C R I P T O R S
 *----------------------------------------------------------------------------------------
 */

STATIC PEI_AMD_NBIO_BASE_SERVICES_PPI mNbioBaseServicePpi = {
  AMD_NBIO_BASE_SERVICES_REVISION,  ///< revision
  (VOID *) &ComplexDataRV,
  sizeof (RV_COMPLEX_CONFIG),
  DebugGetConfig,
  GnbRegisterRead,
  GnbRegisterWrite
};

STATIC EFI_PEI_PPI_DESCRIPTOR mNbioBaseServicesPpiList = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gAmdNbioBaseServicesZpPpiGuid,
  &mNbioBaseServicePpi
};

STATIC EFI_PEI_NOTIFY_DESCRIPTOR   mNotifyMemDonePpi = {
  EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
  &gAmdMemoryInfoHobPpiGuid,
  MemoryConfigDoneCallbackPpi
};

STATIC EFI_PEI_NOTIFY_DESCRIPTOR   mNotifyNbioTopologyPpi = {
  EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
  &gAmdNbioPcieServicesPpiGuid,
  NbioTopologyConfigureCallbackPpi
};
/*----------------------------------------------------------------------------------------*/
/**
 * DebugGetConfig PPI function
 *
 *
 *
 * @param[in]  This          PEI_AMD_NBIO_BASE_SERVICES_PPI pointer
 * @param[out] DebugOptions  Pointer to GNB_BUILD_OPTIONS_ZP_DATA_HOB pointer
 * @retval     EFI_STATUS
 */

EFI_STATUS
DebugGetConfig (
  IN       PEI_AMD_NBIO_BASE_SERVICES_PPI      *This,
     OUT   GNB_BUILD_OPTIONS_ZP_DATA_HOB       **DebugOptions
  )
{
  EFI_STATUS                     Status;
  EFI_PEI_HOB_POINTERS           Hob;
  GNB_BUILD_OPTIONS_ZP_DATA_HOB  *GnbBuildOptionsRVDataHob;

  GnbBuildOptionsRVDataHob = NULL;

  Status = PeiServicesGetHobList (&Hob.Raw);

  while (!END_OF_HOB_LIST (Hob)) {
    if (Hob.Header->HobType == EFI_HOB_TYPE_GUID_EXTENSION &&
        CompareGuid ( &Hob.Guid->Name, &gGnbNbioBaseZPHobInfoGuid)) {
      GnbBuildOptionsRVDataHob = (GNB_BUILD_OPTIONS_ZP_DATA_HOB *) (Hob.Raw);
      Status = EFI_SUCCESS;
      break;
    }
    Hob.Raw = GET_NEXT_HOB (Hob);
  }
  *DebugOptions = GnbBuildOptionsRVDataHob;
  return Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * GnbRegisterRead PPI function
 *
 *
 *
 * @param[in] GnbHandle          GnbHandle
 * @param[in] RegisterSpaceType  Register space type
 * @param[in] Address            Register offset, but PortDevice
 * @param[out] Value             Return value
 * @param[in] Flags              Flags - BIT0 indicates S3 save/restore
 * @param[in] StdHeader          Standard configuration header
 * @retval    AGESA_STATUS
 */

EFI_STATUS
GnbRegisterRead (
  IN       GNB_HANDLE          *GnbHandle,
  IN       UINT8               RegisterSpaceType,
  IN       UINT32              Address,
     OUT   VOID                *Value,
  IN       UINT32              Flags,
  IN       AMD_CONFIG_PARAMS   *StdHeader
  )
{
  EFI_STATUS status;
  status = NbioRegisterRead (GnbHandle, RegisterSpaceType, Address, Value, Flags);
  return status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * GnbRegisterWrite PPI function
 *
 *
 *
 * @param[in] GnbHandle          GnbHandle
 * @param[in] RegisterSpaceType  Register space type
 * @param[in] Address            Register offset, but PortDevice
 * @param[out] Value             Return value
 * @param[in] Flags              Flags - BIT0 indicates S3 save/restore
 * @param[in] StdHeader          Standard configuration header
 * @retval    AGESA_STATUS
 */

EFI_STATUS
GnbRegisterWrite (
  IN       GNB_HANDLE          *GnbHandle,
  IN       UINT8               RegisterSpaceType,
  IN       UINT32              Address,
  IN       VOID                *Value,
  IN       UINT32              Flags,
  IN       AMD_CONFIG_PARAMS   *StdHeader
  )
{
  EFI_STATUS status;
  status = NbioRegisterWrite (GnbHandle, RegisterSpaceType, Address, Value, Flags);
  return status;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Check RV2 B4 OPN number
 *
 * @retval    TRUE    This is RV2 B4 part
 *            FALSE   This is not RV B4 part
 *
 */
BOOLEAN
CheckRv2B4Opn (
  )
{
  UINT32              RegisterData;
  UINT32              TempData32;

  SmnRegisterRead (0, SMUFUSEx000005C0_ADDRESS, &RegisterData);
  TempData32 = (RegisterData >> 30) & 0x3;
  if (TempData32 == 3) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "RV2 B4 \n");
    return TRUE;
  }

  return FALSE;
}

/**
 *---------------------------------------------------------------------------------------
 *  DmaControlSetting
 *
 *  Description:
 *     To set the DMA control bit
 *  Parameters:
 *    @param[in]     LogicalId     To decide what CPU Family it is.
 *    @param[in]     GnbHandle     GnbHandle
 *
 *---------------------------------------------------------------------------------------
 **/
VOID
EFIAPI
DmaControlSetting (
  IN       SOC_LOGICAL_ID              LogicalId,
  IN       GNB_HANDLE                  *GnbHandle
  )
{
  BOOLEAN                              IsRv2SingleSource;
  BOOLEAN                              IsRv1AM4;
  UINT32                               PackageType;

  IsRv2SingleSource = FALSE;
  IsRv1AM4 = FALSE;

  PackageType = LibAmdGetPackageType ((AMD_CONFIG_PARAMS *) NULL);
  if ((1 << RV_SOCKET_AM4) == PackageType) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "RV1 AM4 \n");
    IsRv1AM4 = TRUE;
  }

  IsRv2SingleSource = CheckRv2B4Opn();
  // Check RV2 Single Source
  if ((LogicalId.Family & AMD_FAMILY_RV2) != 0) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "RV2 Single Source \n");
    IsRv2SingleSource = TRUE;
  }
  // Non RV2 family
  if (IsRv2SingleSource != TRUE) {
  if (PcdGetBool (PcdDmaDsXgbeEnable) == TRUE) {
    NbioRegisterRMW (GnbHandle,
                     TYPE_SMN,
                     SYSHUB_DS_CTRL_SHUBCLK_ADDRESS,
                     (UINT32) ~(DMA_CL3_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_Mask),
                     1 << DMA_CL3_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_OFFSET,
                     0);
  }
  }
  // RV2
  if (IsRv2SingleSource == TRUE) {
    if (PcdGetBool (PcdDmaDsUsb1Enable) == TRUE) {
      NbioRegisterRMW (GnbHandle,
                       TYPE_SMN,
                       SYSHUB_DS_CTRL_SHUBCLK_ADDRESS,
                       (UINT32) ~(DMA_CL2_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_Mask),
                       1 << DMA_CL2_SHUBCLK_DEEPSLEEP_ALLOW_ENABLE_OFFSET,
                       0);
    }
  }

  if (IsRv1AM4 == TRUE) {
    NbioRegisterRMW (GnbHandle,
                     TYPE_SMN,
                     SYSHUB_DS_CTRL_SOCCLK_ADDRESS,
                     (UINT32) ~(DMA_CL4_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_Mask),
                     1 << DMA_CL4_SOCCLK_DEEPSLEEP_ALLOW_ENABLE_OFFSET,
                     0);
  }

}

/*----------------------------------------------------------------------------------------*/
/**
 * GNB load build options data
 *
 *
 *
 * @param[in]  PeiServices       Pointer to EFI_PEI_SERVICES pointer
 * @retval     EFI_STATUS
 */

EFI_STATUS
STATIC
GnbLoadBuildOptionDataRV (
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  EFI_STATUS                    Status;
  GNB_BUILD_OPTIONS_ZP_DATA_HOB *GnbBuildOptionsRVDataHob;
// 1. Create Build Options Structure (in HOB)
  Status = PeiServicesCreateHob (
        EFI_HOB_TYPE_GUID_EXTENSION,
        sizeof (GNB_BUILD_OPTIONS_ZP_DATA_HOB),
        &GnbBuildOptionsRVDataHob
        );
  IDS_HOOK (IDS_HOOK_NBIO_LOAD_BUILD_OPTION, NULL, NULL);
  GnbBuildOptionsRVDataHob->EfiHobGuidType.Name = gGnbNbioBaseZPHobInfoGuid;
  GnbBuildOptionsRVDataHob->CfgNbioRASEnable = PcdGetBool (PcdAmdNbioRASControl);
  GnbBuildOptionsRVDataHob->CfgNbioPoisonConsumption = PcdGetBool (PcdAmdNbioPoisonConsumption);
  GnbBuildOptionsRVDataHob->CfgIOHCClkGatinSgupport = PcdGetBool (PcdIOHCClkGatingSupport);
  GnbBuildOptionsRVDataHob->CfgIommuSupport = PcdGetBool (PcdCfgIommuSupport);

  GnbBuildOptionsRVDataHob->GnbCommonOptions.CfgIommuL2ClockGatingEnable = PcdGetBool (PcdIommuL2ClockGatingEnable);
  GnbBuildOptionsRVDataHob->GnbCommonOptions.CfgIommuL1ClockGatingEnable = PcdGetBool (PcdIommuL1ClockGatingEnable);

  GnbBuildOptionsRVDataHob->CfgChubClockGating = PcdGetBool (PcdCfgChubClockGating);
  GnbBuildOptionsRVDataHob->CfgAcpClockGating = PcdGetBool (PcdCfgAcpClockGating);
  GnbBuildOptionsRVDataHob->CfgAxgDisable = PcdGetBool (PcdCfgAxgDisable);
  GnbBuildOptionsRVDataHob->CfgPcieHwInitPwerGating = PcdGet8 (PcdCfgPcieHwInitPwerGating);
  GnbBuildOptionsRVDataHob->CfgAriSupport = PcdGetBool (PcdCfgPcieAriSupport);
  GnbBuildOptionsRVDataHob->CfgSpgClockGatingEnable = PcdGetBool (PcdCfgSpgClockGatingEnable);
  GnbBuildOptionsRVDataHob->CfgAcgAzClockGatingEnable = PcdGetBool (PcdCfgAcgAzClockGatingEnable);
  GnbBuildOptionsRVDataHob->CfgIommuL1MemPowerGating = PcdGetBool (PcdCfgIommuL1MemPowerGating);
  GnbBuildOptionsRVDataHob->CfgIommuL2MemPowerGating = PcdGetBool (PcdCfgIommuL2MemPowerGating);
  GnbBuildOptionsRVDataHob->CfgOrbTxMemPowerGating = PcdGet8 (PcdCfgOrbTxMemPowerGating);
  GnbBuildOptionsRVDataHob->CfgOrbRxMemPowerGating = PcdGet8 (PcdCfgOrbRxMemPowerGating);
  GnbBuildOptionsRVDataHob->CfgSstunlClkGating = PcdGetBool (PcdCfgSstunlClkGating);
  GnbBuildOptionsRVDataHob->CfgParityErrorConfiguration = PcdGetBool (PcdCfgParityErrorConfiguration);
  GnbBuildOptionsRVDataHob->CfgSpgMemPowerGatingEnable = PcdGet8 (PcdCfgSpgMemPowerGatingEnable);
  GnbBuildOptionsRVDataHob->CfgAcgAzMemPowerGatingEnable = PcdGet8 (PcdCfgAcgAzMemPowerGatingEnable);
  GnbBuildOptionsRVDataHob->CfgBifMemPowerGatingEnable = PcdGet8 (PcdCfgBifMemPowerGatingEnable);
  GnbBuildOptionsRVDataHob->CfgSDMAMemPowerGatingEnable = PcdGetBool (PcdCfgSDMAMemPowerGatingEnable);
  GnbBuildOptionsRVDataHob->CfgPcieTxpwrInOff = PcdGet8 (PcdCfgPcieTxpwrInOff);
  GnbBuildOptionsRVDataHob->CfgPcieRxpwrInOff = PcdGet8 (PcdCfgPcieRxpwrInOff);
  GnbBuildOptionsRVDataHob->CfgSmuDeterminismAmbient = PcdGet32 (PcdCfgSmuDeterminismAmbient);
  GnbBuildOptionsRVDataHob->CfgBTCEnable = PcdGetBool (PcdCfgBTCEnable);
  GnbBuildOptionsRVDataHob->CfgPSIEnable = PcdGetBool (PcdCfgPSIEnable);
  GnbBuildOptionsRVDataHob->CfgACSEnable = PcdGetBool (PcdCfgACSEnable);

  GnbBuildOptionsRVDataHob->GnbCommonOptions.CfgScsSupport = PcdGetBool (PcdCfgScsSupport);
  GnbBuildOptionsRVDataHob->GnbCommonOptions.CfgUmaSteering = PcdGet8 (PcdCfgUmaSteering);
  GnbBuildOptionsRVDataHob->GnbCommonOptions.GmcPowerGating = PcdGet8 (PcdGmcPowerGating);
  GnbBuildOptionsRVDataHob->GnbCommonOptions.CfgGmcClockGating = PcdGetBool (PcdCfgGmcClockGating);
  GnbBuildOptionsRVDataHob->GnbCommonOptions.CfgOrbDynWakeEnable = PcdGetBool (PcdCfgOrbDynWakeEnable);
  GnbBuildOptionsRVDataHob->GnbCommonOptions.CfgOrbClockGatingEnable = PcdGetBool (PcdCfgOrbClockGatingEnable);
  GnbBuildOptionsRVDataHob->GnbCommonOptions.CfgIocLclkClockGatingEnable = PcdGetBool (PcdCfgIocLclkClockGatingEnable);
  GnbBuildOptionsRVDataHob->GnbCommonOptions.CfgBapmSupport = PcdGetBool (PcdCfgBapmSupport);
  GnbBuildOptionsRVDataHob->GnbCommonOptions.CfgDcTdpEnable = PcdGetBool (PcdCfgDcTdpEnable);
  GnbBuildOptionsRVDataHob->GnbCommonOptions.CfgGnbNumDisplayStreamPipes = PcdGet8 (PcdCfgGnbNumDisplayStreamPipes);

  return EFI_SUCCESS;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Callback to Enable IOAPIC on GNB
 *
 *
 *
 * @param[in] GnbHandle          GnbHandle
 * @retval    AGESA_STATUS
 */
AGESA_STATUS
STATIC
IoapicEnableCallback (
  IN       GNB_HANDLE          *GnbHandle
  )
{
  UINT32              Value;
  UINT64              GnbNbIoapicAddress;

  if (GnbHandle->InstanceId == 0) {
    GnbNbIoapicAddress = PcdGet64 (PcdCfgGnbIoapicAddress);
    if (GnbNbIoapicAddress != 0x0ull) {
      Value = (UINT32) RShiftU64 (GnbNbIoapicAddress, 32);
      GnbRegisterWrite (GnbHandle, TYPE_SMN, 0x13b102f4, &Value, 0, (AMD_CONFIG_PARAMS *) NULL);
      Value = GnbNbIoapicAddress & 0xFFFFFF00;
      GnbRegisterWrite (GnbHandle, TYPE_SMN, 0x13b102f0, &Value, 0, (AMD_CONFIG_PARAMS *) NULL);  //Ioapic Address Hi
      Value |= 1;
      GnbRegisterWrite (GnbHandle, TYPE_SMN, 0x13b102f0, &Value, 0, (AMD_CONFIG_PARAMS *) NULL);  //Ioapic Address Low
    }
    GnbRegisterRead (GnbHandle, TYPE_SMN, 0x14300000, &Value, 0, (AMD_CONFIG_PARAMS *) NULL);
    Value |= 1 << 2;    //Ioapic_id_ext_en
    Value |= 1 << 4;    //Ioapic_sb_feature_en
    GnbRegisterWrite (GnbHandle, TYPE_SMN, 0x14300000, &Value, 0, (AMD_CONFIG_PARAMS *) NULL);
  } else {
    GnbRegisterRead (GnbHandle, TYPE_SMN, 0x14300000, &Value, 0, (AMD_CONFIG_PARAMS *) NULL);
    Value |= 1 << 2;    //Ioapic_id_ext_en
    Value |= 1 << 4;    //Ioapic_sb_feature_en
    Value |= 1 << 5;    //Ioapic_secondary_en
    GnbRegisterWrite (GnbHandle, TYPE_SMN, 0x14300000, &Value, 0, (AMD_CONFIG_PARAMS *) NULL);
  }
  Value = GnbHandle->Address.Address.Bus;
  Value |= 1 << 8;
  GnbRegisterWrite (GnbHandle, TYPE_SMN, 0x13B10044, &Value, 0, (AMD_CONFIG_PARAMS *) NULL);
  return AGESA_SUCCESS;
}

VOID
STATIC
AudioIOConfigCallback (
  IN       GNB_HANDLE          *GnbHandle
  )
{
  UINT8  Value;
  UINT32 RegisterValue;

  Value = PcdGet8 (PcdAmdNbioAudioSelect);

  if (Value != Soundwire) {
    NbioRegisterRMW (GnbHandle,
                     TYPE_SMN,
                     SMN_ACP_I2S_PIN_CONFIG_ADDRESS,
                     (UINT32) ~(SMN_ACP_I2S_PIN_CONFIG_MASK),
                     Value << SMN_ACP_I2S_PIN_CONFIG_OFFSET,
                     0
                     );
  } else {
    IDS_HDT_CONSOLE (MAIN_FLOW, "Program Soundwire Entry\n");

    NbioRegisterRMW (GnbHandle,
                     TYPE_SMN,
                     SMN_ACP_I2S_PIN_CONFIG_ADDRESS,
                     (UINT32) ~(SMN_ACP_I2S_PIN_CONFIG_MASK),
                     0x0 << SMN_ACP_I2S_PIN_CONFIG_OFFSET,
                     0
                     );
    //
    // Set Audio_Az_Global_Control.CRTS = 0x0"
    //

    //First Set to 0 and confirm
    NbioRegisterRMW (GnbHandle,
                     TYPE_SMN,
                     0x1200008,
                     (UINT32) ~(BIT0),
                     0x0 << 0,
                     0
                     );

    NbioRegisterRead (GnbHandle, TYPE_SMN, 0x1200008, &RegisterValue, 0);

    while (RegisterValue != 0) {
      NbioRegisterRead (GnbHandle, TYPE_SMN, 0x1200008, &RegisterValue, 0);
    }
   //Then Set to 1 and confirm
    RegisterValue = 1;
    NbioRegisterRMW (GnbHandle,
                     TYPE_SMN,
                     0x1200008,
                     (UINT32) ~(BIT0),
                     RegisterValue << 0,
                     0
                     );

    NbioRegisterRead (GnbHandle, TYPE_SMN, 0x1200008, &RegisterValue, 0);
    while (RegisterValue != 1) {
      NbioRegisterRead (GnbHandle, TYPE_SMN, 0x1200008, &RegisterValue, 0);
    }
   //Finally Set to 0 and confirm
    RegisterValue = 0;
    NbioRegisterRMW (GnbHandle,
                     TYPE_SMN,
                     0x1200008,
                     (UINT32) ~(BIT0),
                     RegisterValue << 0,
                     0
                     );
    NbioRegisterRead (GnbHandle, TYPE_SMN, 0x1200008, &RegisterValue, 0);
    while (RegisterValue != 0) {
      NbioRegisterRead (GnbHandle, TYPE_SMN, 0x1200008, &RegisterValue, 0);
    }

    //Disable F6
    NbioRegisterRMW (GnbHandle,
                     TYPE_SMN,
                     NBIF0_HDAUDIO_STRAP0_ADDRESS,
                     (UINT32) ~(NBIFSTRAP0_FUNC_EN_DEV0_F0_MASK),
                     (0 << NBIFSTRAP0_FUNC_EN_DEV0_F0_OFFSET),
                     0
                     );

  }

  IDS_HDT_CONSOLE (MAIN_FLOW, "ACP_I2S_PIN_CONFIG Entry: %x\n", Value);

  if (!PcdGetBool (PcdCfgAzaliaEnable)) {
    /*Disable F1*/
    NbioRegisterRMW (GnbHandle,
                     TYPE_SMN,
                     NBIF0_DCE_AZ_STRAP0_ADDRESS,
                     (UINT32) ~(NBIFSTRAP0_FUNC_EN_DEV0_F0_MASK),
                     (0 << NBIFSTRAP0_FUNC_EN_DEV0_F0_OFFSET),
                     0
                     );
    IDS_HDT_CONSOLE (MAIN_FLOW, "Disable Azlia \n");
  }

}

/*----------------------------------------------------------------------------------------*/
/**
 * Callback to initialize NBIO Base function
 *
 *
 *
 * @param[in] GnbHandle          GnbHandle
 * @retval    AGESA_STATUS
 */
EFI_STATUS
STATIC
NbioBaseInitCallback (
  IN       GNB_HANDLE          *GnbHandle
  )
{
  UINT32               Value;
  NBRASCFG_0400_STRUCT NBRASCFG_0400;

  NBRASCFG_0400.Value = 0;
  // initialize IOMMU
  NbioRegisterRead (GnbHandle, TYPE_SMN, SMN_0x13f00080, &Value, 0);
  IDS_HDT_CONSOLE (MAIN_FLOW, "BXXD00F2x080 = 0x%x\n", Value);
  NbioRegisterWrite (GnbHandle, TYPE_SMN, SMN_0x15704330, &Value, 0);

  NbioRegisterRead (GnbHandle, TYPE_SMN, SMN_0x0240001C, &Value, 0);
  IDS_HDT_CONSOLE (MAIN_FLOW, "0x0240001C = 0x%x\n", Value);
  NbioRegisterWrite (GnbHandle, TYPE_SMN, SMN_0x1570401C, &Value, 0);

  // To Enable/Disable NBIO Poison Consumption
  if (!PcdGetBool (PcdAmdNbioPoisonConsumption)) {
    NbioRegisterRead (GnbHandle, POISON_ACTION_CONTROL_TYPE, POISON_ACTION_CONTROL_ADDRESS, &NBRASCFG_0400.Value, 0);
    NBRASCFG_0400.Field.EgressPoisonLSAPMLErrEn = 0x1;
    NBRASCFG_0400.Field.EgressPoisonLSIntrGenSel =  0x0;
    NBRASCFG_0400.Field.EgressPoisonLSSyncFloodEn =  0x1;
    NBRASCFG_0400.Field.EgressPoisonHSAPMLErrEn =  0x1;
    NBRASCFG_0400.Field.EgressPoisonHSIntrGenSel =  0x0;
    NBRASCFG_0400.Field.EgressPoisonHSSyncFloodEn =  0x1;
    IDS_HDT_CONSOLE (MAIN_FLOW, "NBRASCFG_0400 = 0x%x\n", NBRASCFG_0400.Value);
    NbioRegisterWrite (GnbHandle, POISON_ACTION_CONTROL_TYPE, POISON_ACTION_CONTROL_ADDRESS, &NBRASCFG_0400.Value, 0);
  }


  if (PcdGetBool (PcdCfgIOMMUL2MemoryPGEnable)) {
    NbioRegisterRMW (GnbHandle,
                     IOMMU_L2A_MEMPWR_GATE_1_TYPE,
                     IOMMU_L2A_MEMPWR_GATE_1_ADDRESS,
                     (UINT32) ~(L2AREG_LS_EN_MASK |
                     L2AREG_DS_EN_MASK |
                     L2AREG_SD_EN_MASK),
                     (1 << L2AREG_LS_EN_OFFSET) |
                     (1 << L2AREG_DS_EN_OFFSET) |
                     (1 << L2AREG_SD_EN_OFFSET),
                     0
                     );

    NbioRegisterRMW (GnbHandle,
                     IOMMU_L2B_MEMPWR_GATE_1_TYPE,
                     IOMMU_L2B_MEMPWR_GATE_1_ADDRESS,
                     (UINT32) ~(L2BREG_LS_EN_MASK |
                     L2BREG_DS_EN_MASK |
                     L2BREG_SD_EN_MASK),
                     (1 << L2BREG_LS_EN_OFFSET) |
                     (1 << L2BREG_DS_EN_OFFSET) |
                     (1 << L2BREG_SD_EN_OFFSET),
                     0
                     );
  }

  if (PcdGetBool (PcdCfgIOMMUDynamicPgEnable)) {
    NbioRegisterRMW (GnbHandle,
                     IOMMU_L2A_L2_PWRGATE_CNTRL_REG_3_TYPE,
                     IOMMU_L2A_L2_PWRGATE_CNTRL_REG_3_ADDRESS,
                     (UINT32) ~(IP_PG_EN_MASK),
                     (1 << IP_PG_EN_OFFSET),
                     0
                     );
    NbioRegisterRMW (GnbHandle,
                     IOMMU_L2A_MEMPWR_GATE_1_TYPE,
                     IOMMU_L2A_MEMPWR_GATE_1_ADDRESS,
                     (UINT32) ~(L2AREG_CACHE_PGMEM_SEL_MASK),
                     (1 << L2AREG_CACHE_PGMEM_SEL_OFFSET),
                     0
                     );
    NbioRegisterRMW (GnbHandle,
                     IOMMU_L2B_MEMPWR_GATE_1_TYPE,
                     IOMMU_L2B_MEMPWR_GATE_1_ADDRESS,
                     (UINT32) ~(L2BREG_CACHE_PGMEM_SEL_MASK),
                     (1 << L2BREG_CACHE_PGMEM_SEL_OFFSET),
                     0
                     );

    NbioRegisterRMW (GnbHandle,
                     L1_CLKCNTRL_0_AGR_TYPE,
                     L1_CLKCNTRL_0_AGR_ADDRESS,
                     (UINT32) ~(IOMMUL1IOAGR_0CC_L1_L2_CLKGATE_EN_MASK),
                     (UINT32)(1 << IOMMUL1IOAGR_0CC_L1_L2_CLKGATE_EN_OFFSET),
                     0
                     );

    NbioRegisterRMW (GnbHandle,
                     L1_CLKCNTRL_0_PCIE0_TYPE,
                     L1_CLKCNTRL_0_PCIE0_ADDRESS,
                     (UINT32) ~(IOMMUL1PCIE0_0CC_L1_L2_CLKGATE_EN_MASK),
                     (UINT32)(1 << IOMMUL1PCIE0_0CC_L1_L2_CLKGATE_EN_OFFSET),
                     0
                     );
  }

  //IOMMU_L2A
  Value = 0x800;
  NbioRegisterWrite (GnbHandle, TYPE_SMN, L2_PWRGATE_CNTRL_REG_0_Address, &Value, 0);

  //
  // IOHC Power Gating
  //

  if (PcdGetBool (PcdIOHCPgEnable)) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "PcdIOHCPgEnable = TRUE\n");
    // Enable IOHC_PGMST_CTRL
    NbioRegisterRMW (GnbHandle,
                     IOHC_PGMST_CTRL_Type,
                     IOHC_PGMST_CTRL_ADDRESS,
                     (UINT32) ~(IOHC_CFG_PG_EN_MASK),
                     (UINT32)(1 << IOHC_CFG_PG_EN_OFFSET),
                     0
                     );
    NbioRegisterRMW (GnbHandle,
                     NB_IOAGR_PGMST_TYPE,
                     NB_IOAGR_PGMST_ADDRESS,
                     (UINT32) ~(NBIOAGR_CFG_PG_EN_MASK),
                     (UINT32)(1 << NBIOAGR_CFG_PG_EN_OFFSET),
                     0
                     );


    NbioRegisterRMW (GnbHandle,
                     IOHC_MISC_PGMST_CTRL_Type,
                     IOHC_MISC_PGMST_CTRL_ADDRESS,
                     (UINT32) ~(IOHC_MISC_DMA_ENABLE_EARLY_CLKREQ_MASK),
                     (UINT32)(1 << IOHC_MISC_DMA_ENABLE_EARLY_CLKREQ_OFFSET),
                     0
                     );

    NbioRegisterRMW (GnbHandle,
                     IOAGR_SDP_PORT_CTRL_Type,
                     IOAGR_SDP_PORT_CTRL_ADDRESS,
                     (UINT32) ~(IOAGR_SDP_DMA_ENABLE_EARLY_CLKREQ_MASK),
                     (UINT32)(1 << IOAGR_SDP_DMA_ENABLE_EARLY_CLKREQ_OFFSET),
                     0
                     );
  }
  Value = 0x00000018;
  NbioRegisterWrite (GnbHandle, TYPE_D0F0xBC, ParitySerr_ACTION_CONTROL, &Value, 0);
  Value = 0x00000018;
  NbioRegisterWrite (GnbHandle, TYPE_D0F0xBC, ParityFatal_ACTION_CONTROL, &Value, 0);
  Value = 0x00000018;
  NbioRegisterWrite (GnbHandle, TYPE_D0F0xBC, ParityNonFatal_ACTION_CONTROL, &Value, 0);
  
  return EFI_SUCCESS;
}

/*----------------------------------------------------------------------------------------*/
/**
 * This function assigns MMIO for a IOHC non-pci device. This function is generic and
 * assumes the lock enable bit are both bit 1 and 0 respectively.
 *
 *
 *
 * @param[in]  GnbHandle       Silicon handle to assign
 * @param[in]  LowOffset       Offset of low byte
 * @param[in]  HighOffset      Offset of high byte
 * @param[in]  MemorySize      Size of the allocated bar required
 * @retval     EFI_STATUS
 */
EFI_STATUS
IohcNonPCIBarInit (
  GNB_HANDLE   *GnbHandle,
  UINT32       LowOffset,
  UINT32       HighOffset,
  UINT32       MemorySize
  )
{
  EFI_STATUS             Status;
  FABRIC_TARGET          MmioTarget;
  FABRIC_MMIO_ATTRIBUTE  Attributes;
  UINT64                 MmioBase, Length;
  UINT32                 BarLow, BarHigh;

  BarLow = 0;
  BarHigh = 0;
  IDS_HDT_CONSOLE (MAIN_FLOW, "%a : Begin to allocate bars for SMN low %x high %x\n", __FUNCTION__, BarLow, BarHigh);

  ///
  /// See if the given BAR have already been assigned
  ///
  GnbRegisterRead (GnbHandle, TYPE_SMN, IOHCMISC_SMN_BASE + HighOffset, &BarHigh, 0, (AMD_CONFIG_PARAMS *) NULL);
  GnbRegisterRead (GnbHandle, TYPE_SMN, IOHCMISC_SMN_BASE + LowOffset, &BarLow, 0, (AMD_CONFIG_PARAMS *) NULL);

  if (BarLow == 0 && BarHigh == 0) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "%a : Bars have not been assigned, attempting to allocate MMIO \n", __FUNCTION__);
    ///
    /// Assign bars:
    /// Allocate a chunk of MMIO first
    ///
    Length = MemorySize;
    MmioTarget.TgtType = TARGET_RB;
    MmioTarget.SocketNum = GnbHandle->SocketId;
    MmioTarget.RbNum = GnbHandle->DieNumber;
    Attributes.ReadEnable = 1;
    Attributes.WriteEnable = 1;
    Attributes.NonPosted = 0;
    Attributes.MmioType = NON_PCI_DEVICE_BELOW_4G;
    MmioBase  = 0;

    Status = FabricAllocateMmio (&MmioBase, &Length, ALIGN_1M, MmioTarget, &Attributes);
    ASSERT (Status == EFI_SUCCESS );
    if (EFI_ERROR (Status)) {
      IDS_HDT_CONSOLE (MAIN_FLOW, "%a : Allocate MMIO Fail\n", __FUNCTION__);
      return EFI_OUT_OF_RESOURCES;
    } else {
      IDS_HDT_CONSOLE (MAIN_FLOW, "%a : Allocate MMIO @0x%lx\n", __FUNCTION__, MmioBase);
    }
  }
  else {
    IDS_HDT_CONSOLE (MAIN_FLOW, "%a : Bars have already been assigned!\n", __FUNCTION__);
    IDS_HDT_CONSOLE (MAIN_FLOW, "%a : End\n", __FUNCTION__);
    return EFI_SUCCESS;
  }

  ///
  /// Write the assigned memory address registers to SMN
  ///
  BarHigh = (UINT32) RShiftU64 (MmioBase, 32);
  BarLow = (UINT32) (MmioBase | (BIT0 + BIT1)); /// Set lock bit and enable bit
  IDS_HDT_CONSOLE (MAIN_FLOW, "%a : BarLo = @x , BarHigh %x\n", __FUNCTION__, BarLow, BarHigh);

  Status = GnbRegisterWrite (GnbHandle, TYPE_SMN, IOHCMISC_SMN_BASE + HighOffset, &BarHigh, 0, (AMD_CONFIG_PARAMS *) NULL);
  ASSERT (Status == EFI_SUCCESS );
  Status = GnbRegisterWrite (GnbHandle, TYPE_SMN, IOHCMISC_SMN_BASE + LowOffset, &BarLow, 0, (AMD_CONFIG_PARAMS *) NULL);
  ASSERT (Status == EFI_SUCCESS );

  IDS_HDT_CONSOLE (MAIN_FLOW, "%a : End\n", __FUNCTION__);
  return EFI_SUCCESS;
}

/*----------------------------------------------------------------------------------------*/
/**
 * This is the main function for early NBIO initialization.
 *
 *
 *
 * @param[in]  PeiServices       Pointer to EFI_PEI_SERVICES pointer
 * @retval     EFI_STATUS
 */

EFI_STATUS
AmdNbioBaseInit (
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  PEI_AMD_NBIO_PCIE_SERVICES_PPI  *PcieServicesPpi;
  PCIe_PLATFORM_CONFIG            *Pcie;
  UINT32                          Property;
  UINT32                          Value;
  EFI_STATUS                      Status;
  GNB_HANDLE                      *GnbHandle;
  AMD_CONFIG_PARAMS               *StdHeader;
  GNB_PCIE_INFORMATION_DATA_HOB   *PciePlatformConfigHob;
  GNB_BUILD_OPTIONS_ZP_DATA_HOB   *GnbBuildOptionData;
  PEI_AMD_NBIO_BASE_SERVICES_PPI  *NbioBaseServices;
  SOC_LOGICAL_ID                  LogicalId;
  AMD_PEI_SOC_LOGICAL_ID_PPI      *SocLogicalIdPpi;
  BOOLEAN                         IsRv2;
  PCI_ADDR                        NbioPciAddress;
  UINT32                          SmuArg[6];

  IDS_HDT_CONSOLE (MAIN_FLOW, "AmdNbioBaseInit Entry\n");
  StdHeader = NULL;
  GnbHandle = NULL;
  IsRv2 = FALSE;

  // Need topology structure
  Status = (*PeiServices)->LocatePpi (
                             PeiServices,
                             &gAmdNbioPcieServicesPpiGuid,
                             0,
                             NULL,
                             (VOID **)&PcieServicesPpi
                             );
  PcieServicesPpi->PcieGetTopology (PcieServicesPpi, &PciePlatformConfigHob);
  Pcie = &(PciePlatformConfigHob->PciePlatformConfigHob);

  Status = (*PeiServices)->LocatePpi (
                             PeiServices,
                             &gAmdNbioBaseServicesZpPpiGuid,
                             0,
                             NULL,
                             (VOID **)&NbioBaseServices
                             );

  NbioBaseServices->DebugOptions (NbioBaseServices, &GnbBuildOptionData);

  // Need debug options
  Property = TABLE_PROPERTY_DEFAULT;

  Property |= GnbBuildOptionData->CfgIOHCClkGatinSgupport ? TABLE_PROPERTY_IOHC_Clock_GATING : 0;
  Property |= GnbBuildOptionData->CfgIommuSupport ? 0 : TABLE_PROPERTY_IOMMU_DISABLED;
  Property |= GnbBuildOptionData->GnbCommonOptions.CfgIommuL2ClockGatingEnable ? TABLE_PROPERTY_IOMMU_L2_CLOCK_GATING : 0;
  Property |= GnbBuildOptionData->GnbCommonOptions.CfgIommuL1ClockGatingEnable ? TABLE_PROPERTY_IOMMU_L1_CLOCK_GATING : 0;
  Property |= GnbBuildOptionData->CfgNbioPoisonConsumption ? TABLE_PROPERTY_POISON_ACTION_CONTROL : 0;
  Property |= GnbBuildOptionData->CfgSstunlClkGating ? 0 : TABLE_PROPERTY_SST_CLOCK_GATING_DISABLED;

  // Get fuse data from SMU
  NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
  NbioPciAddress.AddressValue = 0;
  if (NbioSmuServiceRequestV10 (NbioPciAddress, SMC_MSG_GetOpnSpareFuse, SmuArg,0)) {
    IDS_HDT_CONSOLE (NB_MISC, "  SmuArg 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x\n", SmuArg[0], SmuArg[1], SmuArg[2], SmuArg[3], SmuArg[4], SmuArg[5]);
  }
  // To check MP0 GFX Disable
  Value = SmuArg[0];
  Value &= BIT16;
  IDS_HDT_CONSOLE (MAIN_FLOW, "MP0_GFX_DISABLE Value = 0x%x\n", Value);
  if (Value == 0x10000) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "Value = 0x%x\n", Value);
    PcdSet8 (PcdCfgIgpuContorl, 0);
  }

  // Adjust Property based on Debug Info and PCD's
  // From Earlier
  GnbHandle = NbioGetHandle (Pcie);
  IDS_HDT_CONSOLE (MAIN_FLOW, "GnbHandle = 0x%x\n", GnbHandle);
  while (GnbHandle != NULL) {
    // To Check GFX IP is disable or not
    NbioRegisterRead (GnbHandle, TYPE_SMN, RSMU_HCID_NBIF_RV_GPU_ADDRESS, &Value, 0);
    if (Value == 0) {
      PcdSet8 (PcdCfgIgpuContorl, 0);
    }

    Property |= PcdGet8 (PcdCfgIgpuContorl) ? 0 : TABLE_PROPERTY_IGFX_DISABLED;

    Status = GnbProcessTable (
               GnbHandle,
               GnbEarlyInitTableRV,
               Property,
               0,
               StdHeader
               );
    // From Early (these can all be combined??)
    Status = GnbProcessTable (
               GnbHandle,
               GnbEnvInitTableRV,
               Property,
               0,
               StdHeader
               );

    Status = GnbProcessTable (
               GnbHandle,
               GnbIommuEnvInitTableRV,
               Property,
               0,
               StdHeader
               );
    // Get the CPU revision
    SetMem ((VOID *)(&LogicalId), sizeof (LogicalId), 0);
      // Get package type
    Status = (*PeiServices)->LocatePpi (
                             PeiServices,
                             &gAmdSocLogicalIdPpiGuid,
                             0,
                             NULL,
                             &SocLogicalIdPpi
                             );
    if (!EFI_ERROR (Status)) {
      Status = SocLogicalIdPpi->GetLogicalIdOnCurrentCore (&LogicalId);
    }
    if ((LogicalId.Family & AMD_FAMILY_RV2) != 0) {
      IDS_HDT_CONSOLE (MAIN_FLOW, "RV2 Single Source \n");
      IsRv2 = TRUE;
      if (PcdGetBool (PcdShubclkDpmControl) == TRUE) {
        NbioRegisterRMW (GnbHandle,
                         TYPE_SMN,
                         SHUBCLK_DPM_RD_WEIGHT_ADDRESS,
                         (UINT32) ~(SHUBCLK_DPM_RD_WEIGHT_32B_Mask),
                         (0x8 << SHUBCLK_DPM_RD_WEIGHT_32B_OFFSET),
                         0
                         );
        NbioRegisterRMW (GnbHandle,
                         TYPE_SMN,
                         SHUBCLK_DPM_WR_WEIGHT_ADDRESS,
                         (UINT32) ~(SHUBCLK_DPM_WR_WEIGHT_32B_Mask),
                         (0x8 << SHUBCLK_DPM_WR_WEIGHT_32B_OFFSET),
                         0
                         );
        NbioRegisterRMW (GnbHandle,
                         TYPE_SMN,
                         SHUBCLK_DPM_CTRL_ADDRESS,
                         (UINT32) ~(SHUBCLK_DPM_ENABLE_Mask |
                         SHUBCLK_DPM_MODE_Mask |
                         SHUBCLK_DPM_DMAWR_QUANT_Mask |
                         SHUBCLK_DPM_DMARD_QUANT_Mask),
                         (1 << SHUBCLK_DPM_ENABLE_OFFSET) |
                         (0 << SHUBCLK_DPM_MODE_OFFSET) |
                         (0x10 << SHUBCLK_DPM_DMAWR_QUANT_OFFSET) |
                         (0x10 << SHUBCLK_DPM_DMARD_QUANT_OFFSET),
                         0);
      }
    }

    IDS_HOOK (IDS_HOOK_NBIO_BASE_INIT, NULL, (VOID *)GnbHandle);
    IoapicEnableCallback (GnbHandle);
    AudioIOConfigCallback (GnbHandle);
    NbioBaseInitCallback (GnbHandle);

    if (GnbBuildOptionData->CfgNbioRASEnable) {
      NbioNBIFParityCheckWorkaroundRV (GnbHandle);
    }

    ///
    /// Bar allocation for SMN non pci devices
    /// Note that PSPP bar allocation is slightly different and is
    /// done elsewhere
    ///
    if (PcdGetBool(PcdCfgIohcNonPCIBarInitSmu)) {
      IohcNonPCIBarInit(
        GnbHandle,
        IOHCMISC_SMU_BASE_ADDR_LO,
        IOHCMISC_SMU_BASE_ADDR_HI,
        IOHCMISC_BARSIZE_1MB
        );
    }
    if (PcdGetBool(PcdCfgIohcNonPCIBarInitDbg)) {
      IohcNonPCIBarInit(
        GnbHandle,
        IOHCMISC_DBG_BASE_ADDR_LO,
        IOHCMISC_DBG_BASE_ADDR_HI,
        IOHCMISC_BARSIZE_1MB
        );
    }
    if (PcdGetBool(PcdCfgIohcNonPCIBarInitFastReg)) {
      IohcNonPCIBarInit(
        GnbHandle,
        IOHCMISC_FASTREG_BASE_ADDR_LO,
        IOHCMISC_FASTREG_BASE_ADDR_HI,
        IOHCMISC_BARSIZE_1MB
        );
    }
    if (PcdGetBool(PcdCfgIohcNonPCIBarInitFastRegCtl)) {
      IohcNonPCIBarInit(
        GnbHandle,
        IOHCMISC_FASTREGCNTL_BASE_ADDR_LO,
        IOHCMISC_FASTREGCNTL_BASE_ADDR_HI,
        IOHCMISC_BARSIZE_4KB
        );
    }

    DmaControlSetting (LogicalId, GnbHandle);

    GnbHandle = GnbGetNextHandle (GnbHandle);
  }

  IDS_HDT_CONSOLE (MAIN_FLOW, "AmdNbioBaseInit Exit\n");
  return Status;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Callback for NbioPcieServicesPpi installation when NbioTopology is completed
 *
 *
 *
 * @param[in]  PeiServices       Pointer to EFI_PEI_SERVICES pointer
 * @param[in]  NotifyDescriptor  NotifyDescriptor pointer
 * @param[in]  Ppi               Ppi pointer
 * @retval     EFI_STATUS
 */

EFI_STATUS
EFIAPI
NbioTopologyConfigureCallbackPpi (
  IN CONST EFI_PEI_SERVICES     **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Ppi
  )
{

  AGESA_TESTPOINT (TpNbioTopologyConfigureCallbackEntry, NULL);
  IDS_HDT_CONSOLE (MAIN_FLOW, "NbioTopologyConfigureCallbackPpi Entry\n");
  // At this point we know the NBIO topology, so we can initialize all NBIO base registers
  AmdNbioBaseInit (PeiServices);
  IDS_HDT_CONSOLE (MAIN_FLOW, "NbioTopologyConfigureCallbackPpi Exit\n");
  AGESA_TESTPOINT (TpNbioTopologyConfigureCallbackExit, NULL);
  return EFI_SUCCESS;
}

/*----------------------------------------------------------------------------------------*/
/**
 * AmdNbiosBase driver entry point for RV
 *
 *
 *
 * @param[in]  FileHandle  Standard configuration header
 * @param[in]  PeiServices Pointer to EFI_PEI_SERVICES pointer
 * @retval     EFI_STATUS
 */

EFI_STATUS
EFIAPI
AmdNbioBaseRVPeiEntry (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  EFI_STATUS    Status;

  AGESA_TESTPOINT (TpNbioBasePeiEntry, NULL);
  IDS_HDT_CONSOLE (MAIN_FLOW, "AmdNbioBaseRVPeiEntry Entry\n");

  // 1. Set conditionals based on debug configuration and PCDs
  GnbLoadBuildOptionDataRV (PeiServices);

  // 2. PCIe topology is dependent on NbioBaseServicesPpi, so Pcie driver will not publish PPI until after
  // this code is completed. We can simply request notification when gAmdNbioPcieServicesPpiGuid is published
  Status = (**PeiServices).NotifyPpi (PeiServices, &mNotifyNbioTopologyPpi);

  // 3. Publish callback for memory config done so that we can set top of memory
  Status = (**PeiServices).NotifyPpi (PeiServices, &mNotifyMemDonePpi);

  // 4. @todo - do we need a callback for late PEI?  TBD

  // 5. Install PPI for NbioBaseServices
  Status = PeiServicesInstallPpi (&mNbioBaseServicesPpiList); //This driver is done.
  IDS_HDT_CONSOLE (MAIN_FLOW, "AmdNbioBaseRVPeiEntry Exit\n");
  AGESA_TESTPOINT (TpNbioBasePeiExit, NULL);
  return EFI_SUCCESS;
}

