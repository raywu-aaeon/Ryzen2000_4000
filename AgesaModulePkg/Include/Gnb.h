/* $NoKeywords:$ */
/**
 * @file
 *
 * Misc common definition
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
#ifndef _GNB_H_
#define _GNB_H_

#include <Library/IdsLib.h>

#pragma pack (push, 1)

#define GNB_DEADLOOP() \
{ \
  VOLATILE BOOLEAN k; \
  k = TRUE; \
  while (k) { \
  } \
}
#ifdef IDSOPT_TRACING_ENABLED
  #if (IDSOPT_TRACING_ENABLED == TRUE)
    #define GNB_TRACE_ENABLE
  #endif
#endif


#ifndef GNB_DEBUG_CODE
  #ifdef GNB_TRACE_ENABLE
    #define  GNB_DEBUG_CODE(Code) Code
  #else
    #define  GNB_DEBUG_CODE(Code)
  #endif
#endif

#ifndef MIN
  #define MIN(x, y) (((x) > (y))? (y):(x))
#endif

#ifndef MAX
  #define MAX(x, y) (((x) > (y))? (x):(y))
#endif

#define OFF 0

#define PVOID UINT64

#define STRING_TO_UINT32(a, b, c, d) ((UINT32) ((d << 24) | (c << 16) | (b << 8) | a))

#define GnbLibGetHeader(x)  ((AMD_CONFIG_PARAMS*) (x)->StdHeader)

#define AGESA_STATUS_UPDATE(Current, Aggregated) \
if (Current > Aggregated) { \
  Aggregated = Current; \
}

#ifndef offsetof
  #define offsetof(s, m) (UINTN)&(((s *)0)->m)
#endif


//Table properties

#define TABLE_PROPERTY_DEFAULT                     0x00000000ul
#define TABLE_PROPERTY_IGFX_DISABLED               0x00000001ul
#define TABLE_PROPERTY_IOMMU_DISABLED              0x00000002ul
#define TABLE_PROPERTY_SST_CLOCK_GATING_DISABLED   0x00000004ul
#define TABLE_PROPERTY_ORB_CLK_GATING              0x00000008ul
#define TABLE_PROPERTY_IOC_LCLK_CLOCK_GATING       0x00000010ul
#define TABLE_PROPERTY_IOC_SCLK_CLOCK_GATING       0x00000020ul
#define TABLE_PROPERTY_IOMMU_L1_CLOCK_GATING       0x00000040ul
#define TABLE_PROPERTY_IOMMU_L2_CLOCK_GATING       0x00000080ul
#define TABLE_PROPERTY_BAPM                        0x00000100ul
#define TABLE_PROPERTY_SECONDARY_GNB               0x00000200ul
#define TABLE_PROPERTY_NMI_SYNCFLOOD               0x00000400ul
#define TABLE_PROPERTY_PACKAGE_SP3                 0x00000800ul
#define TABLE_PROPERTY_LOADLINE_ENABLE             0x00001000ul
#define TABLE_PROPERTY_SMU_SCLK_CLOCK_GATING       0x00002000ul
#define TABLE_PROPERTY_CHUB_CLOCK_GATING           0x00004000ul
#define TABLE_PROPERTY_HYBRID_BOOST                0x00008000ul
#define TABLE_PROPERTY_LHTC                        0x00010000ul
#define TABLE_PROPERTY_SVI2                        0x00020000ul
#define TABLE_PROPERTY_TDC                         0x00040000ul
#define TABLE_PROPERTY_PKG_POWER_TRACKING          0x00080000ul
#define TABLE_PROPERTY_DGFX_DISABLED               0x00100000ul
#define TABLE_PROPERTY_ACP_CLOCK_GATING_DISABLED   0x00200000ul
#define TABLE_PROPERTY_ACP_POWER_GATING_ENABLED    0x00400000ul
#define TABLE_PROPERTY_ACP_POWER_GATING_DISABLED   0x00800000ul
#define TABLE_PROPERTY_IOMMU_L2_DEBUG_3_31         0x01000000ul
#define TABLE_PROPERTY_AXG_DISABLE                 0x02000000ul
#define TABLE_PROPERTY_SPG_CLOCK_GATING            0x04000000ul
#define TABLE_PROPERTY_ACG_AZ_CLOCK_GATING         0x08000000ul
#define TABLE_PROPERTY_IOMMU_L1_SST_CLOCK_GATING   0x10000000ul
#define TABLE_PROPERTY_IOHC_Clock_GATING           0x20000000ul
#define TABLE_PROPERTY_POISON_ACTION_CONTROL       0x40000000ul

//Register access flags Flags
#define GNB_REG_ACC_FLAG_S3SAVE                    0x00000001ul

// Gnb PCIe Master PLL
#define GNB_PCIE_MASTERPLL_A   0xA
#define GNB_PCIE_MASTERPLL_B   0xB
#define GNB_PCIE_MASTERPLL_C   0xC
#define GNB_PCIE_MASTERPLL_D   0xD

/// ORB memory power gating
typedef enum {
  OrbMemPowerGatingDisabled,                          ///< Disable Power gating
  OrbMemPowerGatingLS,                                ///< LS
  OrbMemPowerGatingDS,                                ///< DS
  OrbMemPowerGatingSD                                 ///< SD
} GNB_ORB_MEM_POWER_GATING;

/// Power gate data setting (do not change this structure definition)
typedef struct {
  UINT16  MothPsoPwrup;         ///< Mother Timer Powerup
  UINT16  MothPsoPwrdn;         ///< Mother Timer Powerdown
  UINT16  DaugPsoPwrup;         ///< Daughter Timer Powerup
  UINT16  DaugPsoPwrdn;         ///< Daughter Timer Powerdown
  UINT16  ResetTimer;           ///< Reset Timer
  UINT16  IsoTimer;             ///< Isolation Timer
} POWER_GATE_DATA;

/// SPG ACGAZ memory power gating
typedef enum {
  SPGACGAZMemPowerGatingAlwaysOn,   ///< AlwaysOn
  SPGACGAZMemPowerGatingLS,         ///< Light Sleep
  SPGACGAZMemPowerGatingDS,         ///< Deep Sleep
  SPGACGAZMemPowerGatingShutDown    ///< Shut Down
} GNB_SPGACGAZ_MEM_POWER_GATING;

/// Topology information
typedef struct {
  BOOLEAN   PhantomFunction;    ///< PCIe topology have device with phantom function
  BOOLEAN   PcieToPciexBridge;  ///< PCIe topology have device with Pcieto Pcix bridge
} GNB_TOPOLOGY_INFO;


/// GNB installable services
typedef enum {
  GnbPcieFamConfigService,                ///< PCIe config service
  GnbPcieFamInitService,                  ///< PCIe Init service
  GnbPcieFamDebugService,                 ///< PCIe Debug service
  GnbRegisterAccessService,               ///< GNB register access service
  GnbIommuService,                        ///< GNB IOMMU config service
  GnbUraService,                          ///< GNB Ura service
  GfxFamService,                          ///< GFX Family service
  GnbPcieMaxPayloadService,               ///< GNB MaxPayload service
  GnbFamTsService,                        ///< GNB TimeStamp service
  GnbFamAlibService,                      ///< GNB Alib service
  GnbFamBuildOptionPointer                ///< GNB Build Options service
} GNB_SERVICE_ID;

/// GNB service entry
typedef struct _GNB_SERVICE {
  GNB_SERVICE_ID        ServiceId;        ///< Service ID
  UINT64                Family;           ///< CPU family
  VOID                  *ServiceProtocol; ///< Service protocol
  struct  _GNB_SERVICE  *NextService;     ///< Pointer to next service
} GNB_SERVICE;

/// GNB SMU Firmware Pointers
typedef struct _GNB_FW_PTRS {
  VOID                  *FirmwareType1;   ///< Pointer to Type 1 SMU Firmware
  VOID                  *FirmwareType2;   ///< Poitner to Type 2 SMU Firmware
} GNB_FW_PTRS;

///
/// ACP Engine Structure
///
typedef struct {
  OUT UINT64 AcpEngineBase;           ///< AcpEngineBase[63:0] = Addr[63:0]
  OUT UINT32 AcpEngineSize;           ///< AcpEngineSize[31:0] = Addr[31:0]
} ACP_ENGINE_T;

//----------------------------------------------------------------------------
//                         TYPEDEFS, STRUCTURES, ENUMS
//
//----------------------------------------------------------------------------
/// Format for Header
typedef struct {
  UINT8   Sign[4];                      ///< Signature
  UINT32  TableLength;                  ///< Table Length
  UINT8   Revision;                     ///< Revision
  UINT8   Checksum;                     ///< Checksum
  UINT8   OemId[6];                     ///< OEM ID
  UINT8   OemTableId[8];                ///< OEM Tabled ID
  UINT32  OemRev;                       ///< OEM Revision
  UINT8   CreatorId[4];                 ///< Creator ID
  UINT32  CreatorRev;                   ///< Creator Revision
} ACPI_TABLE_HEADER;

#define GNB_STRINGIZE(x)                  #x
#define GNB_SERVICE_DEFINITIONS(x)        GNB_STRINGIZE (Services/x/x.h)
#define GNB_MODULE_DEFINITIONS(x)         GNB_STRINGIZE (Modules/x/x.h)
#define GNB_MODULE_INSTALL(x)             GNB_STRINGIZE (Modules/x/x##Install.h)
#pragma pack (pop)

#endif

