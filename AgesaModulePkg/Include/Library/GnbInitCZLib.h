/* $NoKeywords:$ */
/**
 * @file
 *
 *  GnbInitCZ Library
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 313706 $   @e \$Date: 2015-02-25 21:00:43 -0600 (Wed, 25 Feb 2015) $
 *
 */
/*
*****************************************************************************
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
*
*/


#ifndef _GNBINITCZLIB_H_
#define _GNBINITCZLIB_H_

// GPU information for CZ

#include <AMD.h>
#include <GnbRegistersCZ.h>
#include <GnbGfx.h>
#include <OptionGnb.h>


#define GPU__GC__NUM_SE 1
#define GPU__GC__NUM_SH_PER_SE 1
#define GPU__GC__NUM_CU_PER_SH 10

#define BIOSSMC_Result_OK             ((UINT8)0x1)      // The operations was successful.
#define BIOSSMC_Result_NoMore         ((UINT8)0x2)      // The operation cannot be done because a limit has been reached.
                                                          // E.g. trying to enable a HW state when all are enabled already.
                                                          // Depending on the circumstances this might not be an error.
#define BIOSSMC_Result_Failed         ((UINT8)0xFF)     // i.e. -1
#define BIOSSMC_Result_UnknownCmd     ((UINT8)0xFE)     // i.e. -2
#define BIOSSMC_Result_UnknownVT      ((UINT8)0xFD)     // i.e. -3

typedef UINT8 BIOSSMC_Msg;
typedef UINT8 BIOSSMC_Result;

#define BIOSSMC_isERROR(x)                      ((UINT8)0x80 & (x))          // The result code is an actual error.


//BIOSSMC_MSG_EnableAllSmuFeatures
struct BIOSSMC_MSG_EnableAllSmuFeatures_t
{
  UINT32 Mask;
};
typedef struct BIOSSMC_MSG_EnableAllSmuFeatures_t BIOSSMC_MSG_EnableAllSmuFeatures_t;

//BIOSSMC_MSG_DisableAllSmuFeatures
struct BIOSSMC_MSG_DisableAllSmuFeatures_t
{
  UINT32 Mask;
};
typedef struct BIOSSMC_MSG_DisableAllSmuFeatures_t BIOSSMC_MSG_DisableAllSmuFeatures_t;

//BIOSSMC_MSG_VddNbRequest
struct BIOSSMC_MSG_VddNbRequest_t
{
  UINT32 Voltage; //mV with 2 fractional bits
};
typedef struct BIOSSMC_MSG_VddNbRequest_t BIOSSMC_MSG_VddNbRequest_t;

//BIOSSMC_MSG_VddGfxRequest
struct BIOSSMC_MSG_VddGfxRequest_t
{
  UINT32 Voltage; //mV with 2 fractional bits
};
typedef struct BIOSSMC_MSG_VddGfxRequest_t BIOSSMC_MSG_VddGfxRequest_t;

//BIOSSMC_MSG_ReadScs
struct BIOSSMC_MSG_ReadScs_t
{
  UINT32 TablePointer;
};
typedef struct BIOSSMC_MSG_ReadScs_t BIOSSMC_MSG_ReadScs_t;

//BIOSSMC_MSG_LoadPort80MonitorParameters
struct BIOSSMC_MSG_LoadPort80MonitorParameters_t
{
  UINT32 MmioAddress;
  UINT32 MemoryBaseHi;
  UINT32 MemoryBaseLo;
  UINT32 MemoryBufferSize;
  UINT16 PollingInterval; // ms
  UINT8  EnableCsrShadow;
  UINT8  EnableDramShadow;
};
typedef struct BIOSSMC_MSG_LoadPort80MonitorParameters_t GNB_SMU_PORT80_PARAMS;

//BIOSSMC_MSG_LoadTdcLimitParameters
struct BIOSSMC_MSG_LoadTdcLimitParameters_t
{
  UINT32 VddLimit;
  UINT32 VddNbLimit;
  UINT32 VddGfxLimit;
};
typedef struct BIOSSMC_MSG_LoadTdcLimitParameters_t BIOSSMC_MSG_LoadTdcLimitParameters_t;

//BIOSSMC_MSG_LoadEdcLimitParameters
struct BIOSSMC_MSG_LoadEdcLimitParameters_t
{
  UINT32 VddLimit;
  UINT32 VddNbLimit;
  UINT32 VddGfxLimit;
};
typedef struct BIOSSMC_MSG_LoadEdcLimitParameters_t BIOSSMC_MSG_LoadEdcLimitParameters_t;

//BIOSSMC_MSG_LoadCTdpParameters
struct BIOSSMC_MSG_LoadCTdpParameters_t
{
  UINT32 Tdp;
};
typedef struct BIOSSMC_MSG_LoadCTdpParameters_t BIOSSMC_MSG_LoadCTdpParameters_t;

//BIOSSMC_MSG_LoadStapmParameters
struct BIOSSMC_MSG_LoadStapmParameters_t
{
  UINT32    Tsp; //Thermally sustainable power
  UINT32 CoolingTableID;
};
typedef struct BIOSSMC_MSG_LoadStapmParameters_t BIOSSMC_MSG_LoadStapmParameters_t;

//BIOSSMC_MSG_LoadBbbParameters
struct BIOSSMC_MSG_LoadBbbParameters_t
{
  UINT32 PowerLimit;
};
typedef struct BIOSSMC_MSG_LoadBbbParameters_t BIOSSMC_MSG_LoadBbbParameters_t;

//BIOSSMC_MSG_LoadMemoryParameters
struct BIOSSMC_MSG_LoadMemoryParameters_t
{
  UINT32 Vddio;
  UINT32 Vddr;
  UINT32 MemorySpeedHigh; //Mhz
  UINT32 MemorySpeedLow;  //MHz
  UINT32 Dimms;
};
typedef struct BIOSSMC_MSG_LoadMemoryParameters_t BIOSSMC_MSG_LoadMemoryParameters_t;

//BIOSSMC_MSG_LoadPkgPowerParameters
struct BIOSSMC_MSG_LoadPkgPowerParameters_t
{
  UINT32 PowerLimitAC;
  UINT32 PowerLimitDC;
};
typedef struct BIOSSMC_MSG_LoadPkgPowerParameters_t BIOSSMC_MSG_LoadPkgPowerParameters_t;

//BIOSSMC_MSG_LoadSystemConfigParameters
struct BIOSSMC_MSG_LoadSystemConfigParameters_t
{
  UINT32 SystemConfig;
};
typedef struct BIOSSMC_MSG_LoadSystemConfigParameters_t BIOSSMC_MSG_LoadSystemConfigParameters_t;


//#define MAX_NUM_PHYs            2
#define MAX_NUM_LANE_PER_PHY    8

#define NUMBER_OF_GFX_PORTS       5
#define NUMBER_OF_GPP_PORTS       5
#define NUMBER_OF_DDI_DDIS        3
#define NUMBER_OF_PORTS          (NUMBER_OF_GFX_PORTS + NUMBER_OF_GPP_PORTS)

#define NUMBER_OF_WRAPPERS        2

#define NON_INITIALIZED_PCI_ADDRESS  0

#define GFX_WRAP_ID               1
#define GFX_START_PHY_LANE        8
#define GFX_END_PHY_LANE          15
#define GFX_CORE_ID               1
#define GFX_NUMBER_OF_PIFs        1

#define GPP_WRAP_ID               0
#define GPP_START_PHY_LANE        0
#define GPP_END_PHY_LANE          7
#define GPP_CORE_ID               0
#define GPP_NUMBER_OF_PIFs        1

#define DDI_WRAP_ID               3
#define DDI_START_PHY_LANE        16
#define DDI_END_PHY_LANE          27
//#define DDI_NUMBER_OF_PIFs        1

// PBR0
#define PBR0                      0
#define PBR0_NATIVE_PCI_DEV       2
#define PBR0_NATIVE_PCI_FUN       1
#define PBR0_CORE_ID              GPP_CORE_ID
#define PBR0_PORT_ID              0
#define PBR0_PCI_ADDRESS          NON_INITIALIZED_PCI_ADDRESS
#define PBR0_UNIT_ID              0x4
#define PBR0_NUM_UNIT_IDs         0x1

// PBR1
#define PBR1                      1
#define PBR1_NATIVE_PCI_DEV       2
#define PBR1_NATIVE_PCI_FUN       2
#define PBR1_CORE_ID              GPP_CORE_ID
#define PBR1_PORT_ID              1
#define PBR1_PCI_ADDRESS          NON_INITIALIZED_PCI_ADDRESS
#define PBR1_UNIT_ID              0x5
#define PBR1_NUM_UNIT_IDs         0x1

// PBR2
#define PBR2                      2
#define PBR2_NATIVE_PCI_DEV       2
#define PBR2_NATIVE_PCI_FUN       3
#define PBR2_CORE_ID              GPP_CORE_ID
#define PBR2_PORT_ID              2
#define PBR2_PCI_ADDRESS          NON_INITIALIZED_PCI_ADDRESS
#define PBR2_UNIT_ID              0x6
#define PBR2_NUM_UNIT_IDs         0x1

// PBR3
#define PBR3                      3
#define PBR3_NATIVE_PCI_DEV       2
#define PBR3_NATIVE_PCI_FUN       4
#define PBR3_CORE_ID              GPP_CORE_ID
#define PBR3_PORT_ID              3
#define PBR3_PCI_ADDRESS          NON_INITIALIZED_PCI_ADDRESS
#define PBR3_UNIT_ID              0x7
#define PBR3_NUM_UNIT_IDs         0x1

// PBR4
#define PBR4                      4
#define PBR4_NATIVE_PCI_DEV       2
#define PBR4_NATIVE_PCI_FUN       5
#define PBR4_CORE_ID              GPP_CORE_ID
#define PBR4_PORT_ID              4
#define PBR4_PCI_ADDRESS          NON_INITIALIZED_PCI_ADDRESS
#define PBR4_UNIT_ID              0x8
#define PBR4_NUM_UNIT_IDs         0x1

// PBR5
#define PBR5                      5
#define PBR5_NATIVE_PCI_DEV       3
#define PBR5_NATIVE_PCI_FUN       1
#define PBR5_CORE_ID              GFX_CORE_ID
#define PBR5_PORT_ID              0
#define PBR5_PCI_ADDRESS          NON_INITIALIZED_PCI_ADDRESS
#define PBR5_UNIT_ID              0x9
#define PBR5_NUM_UNIT_IDs         0x1

// PBR6
#define PBR6                      6
#define PBR6_NATIVE_PCI_DEV       3
#define PBR6_NATIVE_PCI_FUN       2
#define PBR6_CORE_ID              GFX_CORE_ID
#define PBR6_PORT_ID              1
#define PBR6_PCI_ADDRESS          NON_INITIALIZED_PCI_ADDRESS
#define PBR6_UNIT_ID              0xA
#define PBR6_NUM_UNIT_IDs         0x1

// PBR7
#define PBR7                      7
#define PBR7_NATIVE_PCI_DEV       3
#define PBR7_NATIVE_PCI_FUN       3
#define PBR7_CORE_ID              GFX_CORE_ID
#define PBR7_PORT_ID              2
#define PBR7_PCI_ADDRESS          NON_INITIALIZED_PCI_ADDRESS
#define PBR7_UNIT_ID              0xB
#define PBR7_NUM_UNIT_IDs         0x1

// PBR8
#define PBR8                      8
#define PBR8_NATIVE_PCI_DEV       3
#define PBR8_NATIVE_PCI_FUN       4
#define PBR8_CORE_ID              GFX_CORE_ID
#define PBR8_PORT_ID              3
#define PBR8_PCI_ADDRESS          NON_INITIALIZED_PCI_ADDRESS
#define PBR8_UNIT_ID              0xC
#define PBR8_NUM_UNIT_IDs         0x1

// PBR9
#define PBR9                      9
#define PBR9_NATIVE_PCI_DEV       3
#define PBR9_NATIVE_PCI_FUN       5
#define PBR9_CORE_ID              GFX_CORE_ID
#define PBR9_PORT_ID              4
#define PBR9_PCI_ADDRESS          NON_INITIALIZED_PCI_ADDRESS
#define PBR9_UNIT_ID              0xD
#define PBR9_NUM_UNIT_IDs         0x1


#define MaxDevNum                 3
#define MaxDevFunc                5

///@todo CZ STRAP_BIF_LINK_CONFIG has not been confirmed
#define GFX_CORE_x8               ((0ull << 8) | (8ull << 0))
//#define GFX_CORE_x4x4             ((4ull << 8) | (4ull << 0))
//#define GFX_CORE_x4x2x2           ((2ull << 16) | (2ull << 8) | (4ull << 0))
//#define GFX_CORE_x4x2x1x1         ((1ull << 24) | (1ull << 16) | (2ull << 8) | (4ull << 0))
//#define GFX_CORE_x4x1x1x1x1       ((1ull << 32) | (1ull << 24) | (1ull << 16) | (1ull << 8) | (4ull << 0))

#define GPP_CORE_x4x4             ((4ull << 8) | (4ull << 0))
#define GPP_CORE_x4x2x2           ((2ull << 16) | (2ull << 8) | (4ull << 0))
#define GPP_CORE_x4x2x1x1         ((1ull << 24) | (1ull << 16) | (2ull << 8) | (4ull << 0))
#define GPP_CORE_x4x1x1x1x1       ((1ull << 32) | (1ull << 24) | (1ull << 16) | (1ull << 8) | (4ull << 0))

///Family specific silicon configuration
typedef struct {
  UINT8     PortDevMap [10];                      ///< Device number that has beed allocated already
} CZ_PCIe_SILICON_CONFIG;



/// Complex Configuration for silicon module
typedef struct {
  PCIe_SILICON_CONFIG     Silicon;                ///< Silicon

  PCIe_WRAPPER_CONFIG     GfxWrapper;             ///< GFX Wrapper
  PCIe_WRAPPER_CONFIG     GppWrapper;             ///< GPP Wrapper
  PCIe_WRAPPER_CONFIG     DdiWrapper;             ///< DDI   Wrapper
  // GFX
  ///@todo CZ STRAP_BIF_LINK_CONFIG has not been confirmed, so, GFX either could be configured 1x8 or 2x4.
  PCIe_ENGINE_CONFIG      PortPBR9;               ///< Port PBR9
  PCIe_ENGINE_CONFIG      PortPBR8;               ///< Port PBR8
  PCIe_ENGINE_CONFIG      PortPBR7;               ///< Port PBR7
  PCIe_ENGINE_CONFIG      PortPBR6;               ///< Port PBR6
  PCIe_ENGINE_CONFIG      PortPBR5;               ///< Port PBR5
  // GPP
  PCIe_ENGINE_CONFIG      PortPBR4;               ///< Port PBR4
  PCIe_ENGINE_CONFIG      PortPBR3;               ///< Port PBR3
  PCIe_ENGINE_CONFIG      PortPBR2;               ///< Port PBR2
  PCIe_ENGINE_CONFIG      PortPBR1;               ///< Port PBR1
  PCIe_ENGINE_CONFIG      PortPBR0;               ///< Port PBR0
  // DDI
  ///@todo CZ may have 4 Ddi
  PCIe_ENGINE_CONFIG      Ddi0;                   ///< Ddi0
  PCIe_ENGINE_CONFIG      Ddi1;                   ///< Ddi1
  PCIe_ENGINE_CONFIG      Ddi2;                   ///< Ddi2
  CZ_PCIe_SILICON_CONFIG  FmSilicon;              ///< Fm silicon config
} CZ_COMPLEX_CONFIG;


VOID
PcieSetPortPciAddressMapCZ (
  IN      PCIe_SILICON_CONFIG     *Silicon
  );


AGESA_STATUS
GfxGmcInitCZ (
  IN      GFX_PLATFORM_CONFIG     *Gfx
  );

VOID
GfxGmcInitializeFbLocationCZ (
  IN      GNB_HANDLE              *GnbHandle,
  IN      GFX_PLATFORM_CONFIG     *Gfx
  );

VOID
GfxGmcSecureGarlicAccessCZ (
  IN      GNB_HANDLE              *GnbHandle,
  IN      GFX_PLATFORM_CONFIG     *Gfx
  );

VOID
GfxGmcEnableStutterModePowerGatingCZ (
  IN      GNB_HANDLE              *GnbHandle,
  IN      GFX_PLATFORM_CONFIG     *Gfx
  );

VOID
GfxDisableControllerCZ (
  IN       AMD_CONFIG_PARAMS      *StdHeader
  );

UINT32
GfxLibGetSystemPllCofCZ (
  IN       AMD_CONFIG_PARAMS      *StdHeader
  );

UINT32
GfxCalculateClockCZ (
  IN       UINT8                  Did,
  IN       AMD_CONFIG_PARAMS      *StdHeader
  );

BOOLEAN
GfxIsVbiosPostedCZ (
  IN      GFX_PLATFORM_CONFIG     *Gfx
  );

AGESA_STATUS
GfxRequestVoltageCZ (
  IN       UINT8                  Vid,
  IN       AMD_CONFIG_PARAMS      *StdHeader
  );

AGESA_STATUS
GfxMakeHSAProcUnitEntryCZ (
  IN OUT   AMD_CONFIG_PARAMS      *StdHeader
);

#pragma pack (push, 1)

/// Fuse field entry
typedef struct {
  UINT8                    FieldOffset;              ///< Field offset in fuse register
  UINT8                    FieldWidth;               ///< Width of field
  UINT16                   FuseOffset;               ///< destination offset in translation table
} FUSE_REGISTER_ENTRY_CZ;

/// Fuse register entry
typedef struct {
  UINT8                    RegisterSpaceType;        ///< Register type
  UINT32                   Register;                 ///< FCR register address
  UINT8                    FuseRegisterTableLength;  ///< Length of field table for this register
  FUSE_REGISTER_ENTRY_CZ   *FuseRegisterTable;       ///< Pointer to field table
} FUSE_TABLE_ENTRY_CZ;

/// Fuse translation table
typedef struct {
  UINT8                    FuseTableLength;          ///< Length of translation table
  FUSE_TABLE_ENTRY_CZ      *FuseTable;               ///< Pointer to register table
} FUSE_TABLE_CZ;

#pragma pack (pop)

AGESA_STATUS
GnbLoadFuseTableCZ (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  );

/// PSP entry points to SCS data
#define SCS_BIN_SIGNATURE                 0x5F

AGESA_STATUS
GnbGetScsDataCZ (
  IN OUT   UINTN                          *EntryAddress,
  IN OUT   UINTN                          *EntrySize
  );

AGESA_STATUS
GnbRegisterWriteCZ (
  IN       GNB_HANDLE                     *GnbHandle,
  IN       UINT8                          RegisterSpaceType,
  IN       UINT32                         Address,
  IN       VOID                           *Value,
  IN       UINT32                         Flags,
  IN       AMD_CONFIG_PARAMS              *StdHeader
  );

AGESA_STATUS
GnbRegisterReadCZ (
  IN       GNB_HANDLE                     *GnbHandle,
  IN       UINT8                          RegisterSpaceType,
  IN       UINT32                         Address,
     OUT   VOID                           *Value,
  IN       UINT32                         Flags,
  IN       AMD_CONFIG_PARAMS              *StdHeader
  );

AGESA_STATUS
PcieAriInitCZ (
  IN       AMD_CONFIG_PARAMS              *StdHeader,
  IN       PCIe_PLATFORM_CONFIG           *Pcie
  );

VOID
PciePowerDownPllInL1CZ (
  IN       PCIe_WRAPPER_CONFIG            *Wrapper,
  IN       PCIe_PLATFORM_CONFIG           *Pcie
  );

VOID
PcieSetVoltageCZ (
  IN      PCIE_LINK_SPEED_CAP             LinkCap,
  IN      PCIe_PLATFORM_CONFIG            *Pcie
  );

UINT8
PciePifGetPllPowerUpLatencyCZ (
  IN      PCIe_WRAPPER_CONFIG             *Wrapper,
  IN      PCIe_PLATFORM_CONFIG            *Pcie
  );

PCIE_LINK_SPEED_CAP
PcieGetLinkSpeedCapCZ (
  IN       UINT32                         Flags,
  IN       PCIe_ENGINE_CONFIG             *Engine
  );

UINT32
GnbTimeStampCZ (
  IN       AMD_CONFIG_PARAMS              *StdHeader
  );

VOID
PcieTopologyLaneControlCZ (
  IN      LANE_CONTROL                    Control,
  IN      UINT32                          LaneBitMap,
  IN      PCIe_WRAPPER_CONFIG             *Wrapper,
  IN      PCIe_PLATFORM_CONFIG            *Pcie
  );

VOID
PciePwrPowerDownUnusedLanesCZ (
  IN       PCIe_WRAPPER_CONFIG            *Wrapper,
  IN       PCIe_PLATFORM_CONFIG           *Pcie
  );

AGESA_STATUS
PcieEdpPortPowerCheckCZ (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  );

AGESA_STATUS
PciePowerGateCZ (
  IN      PCIe_PLATFORM_CONFIG            *Pcie
  );

UINT32
GnbSmuLoadSystemConfigParamsCZ (
  IN       GNB_HANDLE                     *GnbHandle,
  IN       GNB_BUILD_OPTIONS_CZ           *GnbBuildOptionData,
  IN       AMD_CONFIG_PARAMS              *StdHeader
  );

VOID
GnbSmuLoadEdcLimitParamsCZ (
  IN       GNB_HANDLE                     *GnbHandle,
  IN       GNB_BUILD_OPTIONS_CZ           *GnbBuildOptionData,
  IN       AMD_CONFIG_PARAMS              *StdHeader
  );

VOID
GnbAzaliaEarlyInitCZ (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  );

AGESA_STATUS
STATIC
PcieEarlyInitCZ (
  IN      PCIe_PLATFORM_CONFIG            *Pcie
  );

AGESA_STATUS
PciePostEarlyInterfaceCZ (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  );

AGESA_STATUS
PciePostInterfaceCZ (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  );

AGESA_STATUS
GnbEnvInterfaceCZ (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  );

AGESA_STATUS
PcieEnvInterfaceCZ (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  );

AGESA_STATUS
GfxMidInterfaceCZ (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  );

AGESA_STATUS
GfxIntInfoTableInterfaceCZ (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  );

AGESA_STATUS
PcieMidInterfaceCZ (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  );

AGESA_STATUS
GnbMidInterfaceCZ (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  );

AGESA_STATUS
GnbBootTimeCalInterfaceCZ (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  );

AGESA_STATUS
GnbSmuMidInterfaceCZ (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  );

AGESA_STATUS
GnbSmuMidLateInterfaceCZ (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  );

AGESA_STATUS
GfxEnvInterfaceCZ (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  );

AGESA_STATUS
GnbEarlyInterfaceCZ (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  );

AGESA_STATUS
GnbSmuPostInterfaceCZ (
  IN      AMD_CONFIG_PARAMS               *StdHeader
  );

#endif

