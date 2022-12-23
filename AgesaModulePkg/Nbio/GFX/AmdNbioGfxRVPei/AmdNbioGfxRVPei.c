/* $NoKeywords:$ */
/**
 * @file
 *
 * AmdNbioGfxRVPei Driver
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  AmdNbioGfxRVPei
 * @e \$Revision: 312065 $   @e \$Date: 2015-01-30 04:23:05 -0600 (Fri, 30 Jan 2015) $
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
#include <AMD.h>
#include <Filecode.h>
#include <PiPei.h>
#include <GnbDxio.h>
#include <GnbRegistersRV.h>
#include <GfxTablesRV.h>
#include <IdsHookId.h>
#include <Guid/GnbPcieInfoHob.h>
#include <Guid/GnbNbioBaseZPInfoHob.h>
#include <Guid/AmdMemoryInfoHob.h>
#include <Guid/GnbIntegratedSysInfoHob.h>
#include <Library/PeiServicesLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Library/PcdLib.h>
#include <Library/HobLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PcieConfigLib.h>
#include <Library/NbioRegisterAccLib.h>
#include <Library/GnbHeapLib.h>
#include <Library/NbioHandleLib.h>
#include <Library/AmdIdsHookLib.h>
#include <Ppi/NbioPcieServicesPpi.h>
#include <Ppi/AmdMemoryInfoHobPpi.h>
#include <NbioGfx.h>
#include "GfxEnumConnectors.h"
#include <Ppi/Graphics.h>
#include <Ppi/NbioGfxPpi.h>
#include <Library/NbioSmuV10Lib.h>
#include <Ppi/NbioSmuServicesPpi.h>
#include <Ppi/SocLogicalIdPpi.h>

#define FILECODE        NBIO_GFX_AMDNBIOGFXRVPEI_AMDNBIOGFXRVPEI_FILECODE
/*----------------------------------------------------------------------------------------
 *                         E X T E R N   D E F I N I T I O N S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
#define SYSTEM_IA32_MAX_LINEAR_ADDRESS                         0xFFFFFFFF
#define UMA_BASE_HARDCODE                                      0xD0000000UL
#define UMA_SIZE_HARDCODE                                      0x10000000UL

// Address
#define MC_CONFIG_MEMSIZE_ADDRESS                              0x1012378CUL

// Type
#define MC_CONFIG_MEMSIZE_TYPE                                 TYPE_SMN

#define SMN_CONFIG_MEMSIZE_OFFSET                              0
#define SMN_CONFIG_MEMSIZE_WIDTH                               32
#define SMN_CONFIG_MEMSIZE_MASK                                0xffffffffUL

/// MC_CONFIG_MEMSIZE
typedef union {
  struct {                                                             ///<
    UINT32                                          CONFIG_MEMSIZE:32; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} MC_CONFIG_MEMSIZE_STRUCT;

// Address
#define MC_VM_FB_LOCATION_BASE_ADDRESS                         0x0006A0B0UL

// Type
#define MC_VM_FB_LOCATION_BASE_TYPE                            TYPE_SMN

#define SMN_FB_BASE_OFFSET                                     0
#define SMN_FB_BASE_WIDTH                                      24
#define SMN_FB_BASE_MASK                                       0xffffffUL

/// SMN_FB_BASE
typedef union {
  struct {                                                             ///<
    UINT32                                                 FB_BASE:24; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_FB_BASE_STRUCT;


// Address
#define MC_VM_FB_LOCATION_TOP_ADDRESS                          0x0006A0B4UL

// Type
#define MC_VM_FB_LOCATION_TOP_TYPE                             TYPE_SMN

#define SMN_FB_TOP_OFFSET                                      0
#define SMN_FB_TOP_WIDTH                                       24
#define SMN_FB_TOP_MASK                                        0xffffffUL


#define Umc0CapAddress                                         0X50df0
#define Umc1CapAddress                                         0X150df0
#define Umc0ConfigAddress                                      0X50100
#define Umc1ConfigAddress                                      0x0150100
#define MaskBit19                                              0x80000
#define MaskBit0To2                                            0x7

#define AddrMask_UMC0_Dimm0                                    0x00050020UL
#define AddrMask_UMC0_Dimm1                                    0x00050024UL
#define AddrMask_UMC1_Dimm0                                    0x00150020UL
#define AddrMask_UMC1_Dimm1                                    0x00150024UL

/// SMN_FB_TOP
typedef union {
  struct {                                                             ///<
    UINT32                                                  FB_TOP:24; ///<
  } Field;                                                             ///<
  UINT32 Value;                                                        ///<
} SMN_FB_TOP_STRUCT;

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */


STATIC EFI_PEI_PPI_DESCRIPTOR mNbioGfxServicesPpiList = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gAmdNbioGfxPpiGuid,
  NULL
};

EFI_STATUS
PeiGraphicInit (
  IN EFI_PEI_SERVICES                  **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR         *NotifyDescriptor,
  IN VOID                              *Ppi
  );

EFI_PEI_NOTIFY_DESCRIPTOR mPeiGraphics[] = {
  (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiPeiGraphicsPpiGuid,
  PeiGraphicInit
};

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */
VOID
GfxDebugDumpDisplayPath (
  IN       EXT_DISPLAY_PATH            *DisplayPath
);

/*----------------------------------------------------------------------------------------
 *                    P P I   N O T I F Y   D E S C R I P T O R S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------*/
/**
 * Dump atom HDMI Retimer/Redriver Table
 *
 *
 *
 * @param[in] pTable   atom_hdmi_retimer_redriver_set pointer
 *
 */
VOID
DumpDpxRetimerRedriverSet(
  IN      atom_hdmi_retimer_redriver_set  *pTable
  )
{
  UINT32 Index;

  IDS_HDT_CONSOLE (GNB_TRACE, "  HdmiSlvAddr=0x%x\n", pTable->HdmiSlvAddr);
  IDS_HDT_CONSOLE (GNB_TRACE, "  HdmiRegNum=%d\n", pTable->HdmiRegNum);
  IDS_HDT_CONSOLE (GNB_TRACE, "  Hdmi6GRegNum=%d\n", pTable->Hdmi6GRegNum);
  for (Index = 0; Index < 9; Index++) {
    IDS_HDT_CONSOLE (GNB_TRACE, "    HdmiRegSetting[%d].ucI2cRegIndex=0x%x\n", Index, pTable->HdmiRegSetting[Index].ucI2cRegIndex);
    IDS_HDT_CONSOLE (GNB_TRACE, "    HdmiRegSetting[%d].ucI2cRegVal=0x%x\n", Index, pTable->HdmiRegSetting[Index].ucI2cRegVal);
  }
  for (Index = 0; Index < 3; Index++) {
    IDS_HDT_CONSOLE (GNB_TRACE, "    Hdmi6GhzRegSetting[%d].ucI2cRegIndex=0x%x\n", Index, pTable->Hdmi6GhzRegSetting[Index].ucI2cRegIndex);
    IDS_HDT_CONSOLE (GNB_TRACE, "    Hdmi6GhzRegSetting[%d].ucI2cRegVal=0x%x\n", Index, pTable->Hdmi6GhzRegSetting[Index].ucI2cRegVal);
  }
}

/*----------------------------------------------------------------------------------------*/
/**
 * Build integrated info table
 *
 *
 *
 * @param[in] SystemInfoTable   ATOM_INTEGRATED_SYSTEM_INFO_V1_11 pointer
 * @retval    AGESA_STATUS
 */
AGESA_STATUS
GfxIntInfoTableInitRV (
  IN      ATOM_FUSION_SYSTEM_INFO_V9  *SystemInfoTable,
  IN      PCIe_PLATFORM_CONFIG        *Pcie
  )
{
  AGESA_STATUS                    Status;
  UINT8                           Index;
  EFI_PEI_SERVICES                **PeiServices;
  atom_hdmi_retimer_redriver_set  *atomHDMIRetimerRedriverTable;
  ATOM_14NM_DPPHY_DP_SETTING      *AtomDpPhyDpSetting;
  ATOM_14NM_DPPHY_DP_SETTING      *AtomDpHbr3PhyDpSetting;

  ATOM_14NM_DPPHY_DP_SETTING      *AtomDpHbrPhyDpSetting;   //hbr 2.7G dp tuning set
  ATOM_14NM_DPPHY_DP_SETTING      *AtomDpHbr2PhyDpSetting;
  ATOM_14NM_DPPHY_DP_SETTING      *AtomEDpTuningSetting;

  PeiServices = (EFI_PEI_SERVICES **) GetPeiServicesTablePointer ();
  Status = AGESA_SUCCESS;
  atomHDMIRetimerRedriverTable = NULL;
  AtomDpPhyDpSetting = NULL;
  AtomDpHbr3PhyDpSetting = NULL;
  AtomDpHbrPhyDpSetting = NULL;
  AtomDpHbr2PhyDpSetting = NULL;
  AtomEDpTuningSetting = NULL;

  IDS_HDT_CONSOLE (GNB_TRACE, "GfxIntInfoTableInitRV Enter\n");

  // ATOM_COMMON_TABLE_HEADER  table_header;
  SystemInfoTable->sIntegratedSysInfo.table_header.usStructureSize = sizeof (ATOM_INTEGRATED_SYSTEM_INFO_V1_11);
  ASSERT (SystemInfoTable->sIntegratedSysInfo.table_header.usStructureSize == 1024);
  SystemInfoTable->sIntegratedSysInfo.table_header.ucTableFormatRevision = 1;
  SystemInfoTable->sIntegratedSysInfo.table_header.ucTableContentRevision = 11;
  IDS_HDT_CONSOLE (GNB_TRACE, "ATOM_INTEGRATED_SYSTEM_INFO_V1_11 size[%x] Ver%d.%d\n",
                              SystemInfoTable->sIntegratedSysInfo.table_header.usStructureSize,
                              SystemInfoTable->sIntegratedSysInfo.table_header.ucTableFormatRevision,
                              SystemInfoTable->sIntegratedSysInfo.table_header.ucTableContentRevision
                              );

  //UINT32  vbios_misc;                       //enum of atom_system_vbiosmisc_def
  SystemInfoTable->sIntegratedSysInfo.vbios_misc = 0;   // BLDCFG_DISPLAY_MISC_VBIOS_FAST_BOOT_ENABLE

  //UINT32  gpucapinfo;                       //enum of atom_system_gpucapinf_def
  SystemInfoTable->sIntegratedSysInfo.gpucapinfo = 0; //GPUCAPINFO_TMDS_HDMI_USE_CASCADE_PLL_MODE | GPUCAPINFO_DP_USE_SINGLE_PLL_MODE;

  //UINT32  system_config;
  SystemInfoTable->sIntegratedSysInfo.system_config = 0;
//      if (GnbBuildOptionData->CfgSMUServiceEnablementBitMap.Field.DFS_BYPASS == 1) {
//        SystemInfoTableV5.sIntegratedSysInfo.ulGPUCapInfo |= GPUCAPINFO_DFS_BYPASS_ENABLE;
//      }
//      if (GnbBuildOptionData->CfgSMUServiceEnablementBitMap.Field.CONN_STDBY == 1) {
//        SystemInfoTableV5.sIntegratedSysInfo.ulGPUCapInfo |= GPUCAPS__GNB_FAST_RESUME_CAPABLE;
//      }
//      if (GnbBuildOptionData->CfgSMUServiceEnablementBitMap.Field.NB_DPM == 1) {
//        SystemInfoTableV5.sIntegratedSysInfo.ulSystemConfig |= BIT3;
//      }

  //UINT32  cpucapinfo;
  SystemInfoTable->sIntegratedSysInfo.cpucapinfo = 0;

  //uint16_t  gpuclk_ss_percentage;             //unit of 0.001%,   1000 mean 1%
  //uint16_t  gpuclk_ss_type;
  //uint16_t  lvds_ss_percentage;               //unit of 0.001%,   1000 mean 1%
  //uint16_t  lvds_ss_rate_10hz;
  //uint16_t  hdmi_ss_percentage;               //unit of 0.001%,   1000 mean 1%
  //uint16_t  hdmi_ss_rate_10hz;
  //uint16_t  dvi_ss_percentage;                //unit of 0.001%,   1000 mean 1%
  //uint16_t  dvi_ss_rate_10hz;
  //uint16_t  dpphy_override;                   // bit vector, enum of atom_sysinfo_dpphy_override_def
  SystemInfoTable->sIntegratedSysInfo.gpuclk_ss_percentage = PcdGet16 (PcdCfgPcieRefClkSpreadSpectrum);
  SystemInfoTable->sIntegratedSysInfo.gpuclk_ss_type = 0; // bit0 = down/center spread mode. so far dalwaysown spread mode(=0)
  SystemInfoTable->sIntegratedSysInfo.lvds_ss_percentage = 0;
  SystemInfoTable->sIntegratedSysInfo.lvds_ss_rate_10hz = 0;
  SystemInfoTable->sIntegratedSysInfo.hdmi_ss_rate_10hz = 0;
  SystemInfoTable->sIntegratedSysInfo.hdmi_ss_rate_10hz = 0;
  SystemInfoTable->sIntegratedSysInfo.dvi_ss_percentage = 0;
  SystemInfoTable->sIntegratedSysInfo.dvi_ss_rate_10hz = 0;
  SystemInfoTable->sIntegratedSysInfo.dpphy_override = PcdGet16 (PcdAmdDpPhyOverride);

  //uint16_t  lvds_misc;                        // enum of atom_sys_info_lvds_misc_def
  SystemInfoTable->sIntegratedSysInfo.lvds_misc = 0;
  SystemInfoTable->sIntegratedSysInfo.backlight_pwm_hz = PcdGet16 (PcdBackLightPwmHz);  // pwm frequency in hz
  IDS_HDT_CONSOLE (GNB_TRACE, "backlight_pwm_hz  0x%x\n",SystemInfoTable->sIntegratedSysInfo.backlight_pwm_hz);
  SystemInfoTable->sIntegratedSysInfo.pwr_on_digon_to_de = PcdGet8 (PcdPwrOnDigonToDe); // all pwr sequence numbers below are in uint of 4ms
  SystemInfoTable->sIntegratedSysInfo.pwr_on_de_to_vary_bl = PcdGet8 (PcdPwrOnDeToVaryBl);
  SystemInfoTable->sIntegratedSysInfo.pwr_down_vary_bloff_to_de = PcdGet8 (PcdPwrDownVaryBloffToDe);
  SystemInfoTable->sIntegratedSysInfo.pwr_down_de_to_digoff = PcdGet8 (PcdPwrDownDeToDigOff);
  SystemInfoTable->sIntegratedSysInfo.pwr_off_delay = PcdGet8 (PcdPwrOffDelay);
  SystemInfoTable->sIntegratedSysInfo.pwr_on_vary_bl_to_blon = PcdGet8 (PcdPwrOnVaryBlToBlon);
  SystemInfoTable->sIntegratedSysInfo.pwr_down_bloff_to_vary_bloff = PcdGet8 (PcdPwrDownBloffToVaryBlOff);
  SystemInfoTable->sIntegratedSysInfo.min_allowed_bl_level = PcdGet8 (PcdMinAllowedBlLevel);
  //uint8_t   htc_hyst_limit;
  //uint8_t   htc_tmp_limit;
  SystemInfoTable->sIntegratedSysInfo.htc_hyst_limit = 0;
  SystemInfoTable->sIntegratedSysInfo.htc_tmp_limit = 0;
  SystemInfoTable->sIntegratedSysInfo.reserved1 = 0;
  SystemInfoTable->sIntegratedSysInfo.reserved2 = 0;

  //ATOM_EXTERNAL_DISPLAY_CONNECTION_INFO extdispconninfo;
  //Locate PCIe configuration data to get definitions of display connectors
  SystemInfoTable->sIntegratedSysInfo.extdispconninfo.sHeader.usStructureSize = sizeof (ATOM_EXTERNAL_DISPLAY_CONNECTION_INFO);
  SystemInfoTable->sIntegratedSysInfo.extdispconninfo.sHeader.ucTableFormatRevision = 1;
  SystemInfoTable->sIntegratedSysInfo.extdispconninfo.sHeader.ucTableContentRevision = 1;
  SystemInfoTable->sIntegratedSysInfo.extdispconninfo.uc3DStereoPinId = 0;
  SystemInfoTable->sIntegratedSysInfo.extdispconninfo.ucRemoteDisplayConfig = 0;
  SystemInfoTable->sIntegratedSysInfo.extdispconninfo.ucFixDPVoltageSwing = 0;
  GfxIntegratedEnumerateAllConnectors (&SystemInfoTable->sIntegratedSysInfo.extdispconninfo.sPath[0]);

  for (Index = 0; Index < 4; Index++) {
    IDS_HDT_CONSOLE (GNB_TRACE, "sPath[%x] address  0x%x\n",Index ,&SystemInfoTable->sIntegratedSysInfo.extdispconninfo.sPath[Index]);
    GfxDebugDumpDisplayPath (&SystemInfoTable->sIntegratedSysInfo.extdispconninfo.sPath[Index]);
  }
  //ATOM_14NM_DPPHY_DVIHDMI_TUNINGSET dvi_tuningset;
  if (PcdGet16 (PcdAmdDpPhyOverride) & ATOM_ENABLE_DVI_TUNINGSET) {
    SystemInfoTable->sIntegratedSysInfo.dvi_tuningset.max_symclk_in10khz = PcdGet32 (PcdAmdDVI_max_symclk_in10khz);
    SystemInfoTable->sIntegratedSysInfo.dvi_tuningset.encoder_mode = PcdGet8 (PcdAmdDVI_encoder_mode);
    SystemInfoTable->sIntegratedSysInfo.dvi_tuningset.phy_sel = PcdGet8 (PcdAmdDVI_phy_sel);
    SystemInfoTable->sIntegratedSysInfo.dvi_tuningset.margindeemph = PcdGet16 (PcdAmdDVI_margindeemph);
    SystemInfoTable->sIntegratedSysInfo.dvi_tuningset.deemph_6db_4 = PcdGet8 (PcdAmdDVI_deemph_6db_4);
    SystemInfoTable->sIntegratedSysInfo.dvi_tuningset.boostadj = PcdGet8 (PcdAmdDVI_boostadj);
    SystemInfoTable->sIntegratedSysInfo.dvi_tuningset.tx_driver_fifty_ohms = PcdGet8 (PcdAmdDVI_tx_driver_fifty_ohms);
    SystemInfoTable->sIntegratedSysInfo.dvi_tuningset.deemph_sel = PcdGet8 (PcdAmdDVI_deemph_sel);
  }
  //ATOM_14NM_DPPHY_DVIHDMI_TUNINGSET hdmi_tuningset;
  if (PcdGet16 (PcdAmdDpPhyOverride) & ATOM_ENABLE_HDMI_TUNINGSET) {
    SystemInfoTable->sIntegratedSysInfo.hdmi_tuningset.max_symclk_in10khz = PcdGet32 (PcdAmdHDMI_max_symclk_in10khz);
    SystemInfoTable->sIntegratedSysInfo.hdmi_tuningset.encoder_mode = PcdGet8 (PcdAmdHDMI_encoder_mode);
    SystemInfoTable->sIntegratedSysInfo.hdmi_tuningset.phy_sel = PcdGet8 (PcdAmdHDMI_phy_sel);
    SystemInfoTable->sIntegratedSysInfo.hdmi_tuningset.margindeemph = PcdGet16 (PcdAmdHDMI_margindeemph);
    SystemInfoTable->sIntegratedSysInfo.hdmi_tuningset.deemph_6db_4 = PcdGet8 (PcdAmdHDMI_deemph_6db_4);
    SystemInfoTable->sIntegratedSysInfo.hdmi_tuningset.boostadj = PcdGet8 (PcdAmdHDMI_boostadj);
    SystemInfoTable->sIntegratedSysInfo.hdmi_tuningset.tx_driver_fifty_ohms = PcdGet8 (PcdAmdHDMI_tx_driver_fifty_ohms);
    SystemInfoTable->sIntegratedSysInfo.hdmi_tuningset.deemph_sel = PcdGet8 (PcdAmdHDMI_deemph_sel);
  }
  //ATOM_14NM_DPPHY_DVIHDMI_TUNINGSET hdmi6g_tuningset;
  if (PcdGet16 (PcdAmdDpPhyOverride) & ATOM_ENABLE_HDMI6G_TUNINGSET) {
    SystemInfoTable->sIntegratedSysInfo.hdmi6g_tuningset.max_symclk_in10khz = PcdGet32 (PcdAmdHDMI6G_max_symclk_in10khz);
    SystemInfoTable->sIntegratedSysInfo.hdmi6g_tuningset.encoder_mode = PcdGet8 (PcdAmdHDMI6G_encoder_mode);
    SystemInfoTable->sIntegratedSysInfo.hdmi6g_tuningset.phy_sel = PcdGet8 (PcdAmdHDMI6G_phy_sel);
    SystemInfoTable->sIntegratedSysInfo.hdmi6g_tuningset.margindeemph = PcdGet16 (PcdAmdHDMI6G_margindeemph);
    SystemInfoTable->sIntegratedSysInfo.hdmi6g_tuningset.deemph_6db_4 = PcdGet8 (PcdAmdHDMI6G_deemph_6db_4);
    SystemInfoTable->sIntegratedSysInfo.hdmi6g_tuningset.boostadj = PcdGet8 (PcdAmdHDMI6G_boostadj);
    SystemInfoTable->sIntegratedSysInfo.hdmi6g_tuningset.tx_driver_fifty_ohms = PcdGet8 (PcdAmdHDMI6G_tx_driver_fifty_ohms);
    SystemInfoTable->sIntegratedSysInfo.hdmi6g_tuningset.deemph_sel = PcdGet8 (PcdAmdHDMI6G_deemph_sel);
  }

  //ATOM_14NM_DPPHY_DP_TUNINGSET dp_tuningset;
  if (PcdGet16 (PcdAmdDpPhyOverride) & ATOM_ENABLE_DP_TUNINGSET) {
    SystemInfoTable->sIntegratedSysInfo.dp_tuningset.phy_sel = PcdGet8 (PcdAmdDpPhySel);
    SystemInfoTable->sIntegratedSysInfo.dp_tuningset.version = PcdGet8 (PcdAmdDpVersion);
    SystemInfoTable->sIntegratedSysInfo.dp_tuningset.table_size = PcdGet16 (PcdAmdDpTableSize);
  }
  AtomDpPhyDpSetting = (ATOM_14NM_DPPHY_DP_SETTING*) PcdGet32 (PcdAtomDpPhyDpSetting);
  if (AtomDpPhyDpSetting != NULL) {
    for (Index = 0; Index < 10; Index++) {
      SystemInfoTable->sIntegratedSysInfo.dp_tuningset.dptuning[Index].dp_vs_pemph_level = AtomDpPhyDpSetting[Index].dp_vs_pemph_level;          //UINT8
      SystemInfoTable->sIntegratedSysInfo.dp_tuningset.dptuning[Index].margindeemph = AtomDpPhyDpSetting[Index].margindeemph;                    //UINT16
      SystemInfoTable->sIntegratedSysInfo.dp_tuningset.dptuning[Index].deemph_6db_4 = AtomDpPhyDpSetting[Index].deemph_6db_4;                    //UINT8
      SystemInfoTable->sIntegratedSysInfo.dp_tuningset.dptuning[Index].boostadj = AtomDpPhyDpSetting[Index].boostadj;                            //UINT8
    }
  } else {
    (*PeiServices)->SetMem (&(SystemInfoTable->sIntegratedSysInfo.dp_tuningset.dptuning), sizeof (ATOM_14NM_DPPHY_DP_SETTING) * 10, 0xFF);
  }

  //ATOM_14NM_DPPHY_DP_TUNINGSET dp_hbr3_tuningset;
  if (PcdGet16 (PcdAmdDpPhyOverride) & ATOM_ENABLE_DP_HBR3_TUNINGSET) {
    SystemInfoTable->sIntegratedSysInfo.dp_hbr3_tuningset.phy_sel = PcdGet8 (PcdAmdDpHbr3PhySel);
    SystemInfoTable->sIntegratedSysInfo.dp_hbr3_tuningset.version = PcdGet8 (PcdAmdDpHbr3Version);
    SystemInfoTable->sIntegratedSysInfo.dp_hbr3_tuningset.table_size = PcdGet16 (PcdAmdDpHbr3TableSize);
  }
  AtomDpHbr3PhyDpSetting = (ATOM_14NM_DPPHY_DP_SETTING*) PcdGet32 (PcdAtomDpHbr3PhyDpSetting);
  if (AtomDpHbr3PhyDpSetting != NULL) {
    for (Index = 0; Index < 10; Index++) {
      SystemInfoTable->sIntegratedSysInfo.dp_hbr3_tuningset.dptuning[Index].dp_vs_pemph_level = AtomDpHbr3PhyDpSetting[Index].dp_vs_pemph_level;  //UINT8
      SystemInfoTable->sIntegratedSysInfo.dp_hbr3_tuningset.dptuning[Index].margindeemph = AtomDpHbr3PhyDpSetting[Index].margindeemph;            //UINT16
      SystemInfoTable->sIntegratedSysInfo.dp_hbr3_tuningset.dptuning[Index].deemph_6db_4 = AtomDpHbr3PhyDpSetting[Index].deemph_6db_4;            //UINT8
      SystemInfoTable->sIntegratedSysInfo.dp_hbr3_tuningset.dptuning[Index].boostadj = AtomDpHbr3PhyDpSetting[Index].boostadj;                    //UINT8
    }
  } else {
    (*PeiServices)->SetMem (&(SystemInfoTable->sIntegratedSysInfo.dp_hbr3_tuningset.dptuning), sizeof (ATOM_14NM_DPPHY_DP_SETTING) * 10, 0xFF);
  }

  //ATOM_CAMERA_DATA  camera_info;

  //atom_hdmi_retimer_redriver_set dp0_retimer_redriver_set;
  atomHDMIRetimerRedriverTable = (atom_hdmi_retimer_redriver_set*)PcdGet32 (PcdCfgDp0RetimerRedriverTable);
  if (atomHDMIRetimerRedriverTable != NULL) {
    SystemInfoTable->sIntegratedSysInfo.gpucapinfo |= GPUCAPSINFO_EXT_HDMI_INIT_PER_PORT;
    SystemInfoTable->sIntegratedSysInfo.dp0_retimer_redriver_set.HdmiSlvAddr = atomHDMIRetimerRedriverTable->HdmiSlvAddr;
    SystemInfoTable->sIntegratedSysInfo.dp0_retimer_redriver_set.HdmiRegNum = atomHDMIRetimerRedriverTable->HdmiRegNum;
    SystemInfoTable->sIntegratedSysInfo.dp0_retimer_redriver_set.Hdmi6GRegNum = atomHDMIRetimerRedriverTable->Hdmi6GRegNum;
    for (Index = 0; Index < 9; Index++) {
      SystemInfoTable->sIntegratedSysInfo.dp0_retimer_redriver_set.HdmiRegSetting[Index].ucI2cRegIndex = atomHDMIRetimerRedriverTable->HdmiRegSetting[Index].ucI2cRegIndex;
      SystemInfoTable->sIntegratedSysInfo.dp0_retimer_redriver_set.HdmiRegSetting[Index].ucI2cRegVal = atomHDMIRetimerRedriverTable->HdmiRegSetting[Index].ucI2cRegVal;
    }
    for (Index = 0; Index < 3; Index++) {
      SystemInfoTable->sIntegratedSysInfo.dp0_retimer_redriver_set.Hdmi6GhzRegSetting[Index].ucI2cRegIndex = atomHDMIRetimerRedriverTable->Hdmi6GhzRegSetting[Index].ucI2cRegIndex;
      SystemInfoTable->sIntegratedSysInfo.dp0_retimer_redriver_set.Hdmi6GhzRegSetting[Index].ucI2cRegVal = atomHDMIRetimerRedriverTable->Hdmi6GhzRegSetting[Index].ucI2cRegVal;
    }
    IDS_HDT_CONSOLE (GNB_TRACE, "dp0_retimer_redriver_set:\n");
    DumpDpxRetimerRedriverSet (&SystemInfoTable->sIntegratedSysInfo.dp0_retimer_redriver_set);
  }
  //atom_hdmi_retimer_redriver_set dp1_retimer_redriver_set;
  atomHDMIRetimerRedriverTable = (atom_hdmi_retimer_redriver_set*)PcdGet32 (PcdCfgDp1RetimerRedriverTable);
  if (atomHDMIRetimerRedriverTable != NULL) {
    SystemInfoTable->sIntegratedSysInfo.gpucapinfo |= GPUCAPSINFO_EXT_HDMI_INIT_PER_PORT;
    SystemInfoTable->sIntegratedSysInfo.dp1_retimer_redriver_set.HdmiSlvAddr = atomHDMIRetimerRedriverTable->HdmiSlvAddr;
    SystemInfoTable->sIntegratedSysInfo.dp1_retimer_redriver_set.HdmiRegNum = atomHDMIRetimerRedriverTable->HdmiRegNum;
    SystemInfoTable->sIntegratedSysInfo.dp1_retimer_redriver_set.Hdmi6GRegNum = atomHDMIRetimerRedriverTable->Hdmi6GRegNum;
    for (Index = 0; Index < 9; Index++) {
      SystemInfoTable->sIntegratedSysInfo.dp1_retimer_redriver_set.HdmiRegSetting[Index].ucI2cRegIndex = atomHDMIRetimerRedriverTable->HdmiRegSetting[Index].ucI2cRegIndex;
      SystemInfoTable->sIntegratedSysInfo.dp1_retimer_redriver_set.HdmiRegSetting[Index].ucI2cRegVal = atomHDMIRetimerRedriverTable->HdmiRegSetting[Index].ucI2cRegVal;
    }
    for (Index = 0; Index < 3; Index++) {
      SystemInfoTable->sIntegratedSysInfo.dp1_retimer_redriver_set.Hdmi6GhzRegSetting[Index].ucI2cRegIndex = atomHDMIRetimerRedriverTable->Hdmi6GhzRegSetting[Index].ucI2cRegIndex;
      SystemInfoTable->sIntegratedSysInfo.dp1_retimer_redriver_set.Hdmi6GhzRegSetting[Index].ucI2cRegVal = atomHDMIRetimerRedriverTable->Hdmi6GhzRegSetting[Index].ucI2cRegVal;
    }
    IDS_HDT_CONSOLE (GNB_TRACE, "dp1_retimer_redriver_set:\n");
    DumpDpxRetimerRedriverSet (&SystemInfoTable->sIntegratedSysInfo.dp1_retimer_redriver_set);
  }
  //atom_hdmi_retimer_redriver_set dp2_retimer_redriver_set;
  atomHDMIRetimerRedriverTable = (atom_hdmi_retimer_redriver_set*)PcdGet32 (PcdCfgDp2RetimerRedriverTable);
  if (atomHDMIRetimerRedriverTable != NULL) {
    SystemInfoTable->sIntegratedSysInfo.gpucapinfo |= GPUCAPSINFO_EXT_HDMI_INIT_PER_PORT;
    SystemInfoTable->sIntegratedSysInfo.dp2_retimer_redriver_set.HdmiSlvAddr = atomHDMIRetimerRedriverTable->HdmiSlvAddr;
    SystemInfoTable->sIntegratedSysInfo.dp2_retimer_redriver_set.HdmiRegNum = atomHDMIRetimerRedriverTable->HdmiRegNum;
    SystemInfoTable->sIntegratedSysInfo.dp2_retimer_redriver_set.Hdmi6GRegNum = atomHDMIRetimerRedriverTable->Hdmi6GRegNum;
    for (Index = 0; Index < 9; Index++) {
      SystemInfoTable->sIntegratedSysInfo.dp2_retimer_redriver_set.HdmiRegSetting[Index].ucI2cRegIndex = atomHDMIRetimerRedriverTable->HdmiRegSetting[Index].ucI2cRegIndex;
      SystemInfoTable->sIntegratedSysInfo.dp2_retimer_redriver_set.HdmiRegSetting[Index].ucI2cRegVal = atomHDMIRetimerRedriverTable->HdmiRegSetting[Index].ucI2cRegVal;
    }
    for (Index = 0; Index < 3; Index++) {
      SystemInfoTable->sIntegratedSysInfo.dp2_retimer_redriver_set.Hdmi6GhzRegSetting[Index].ucI2cRegIndex = atomHDMIRetimerRedriverTable->Hdmi6GhzRegSetting[Index].ucI2cRegIndex;
      SystemInfoTable->sIntegratedSysInfo.dp2_retimer_redriver_set.Hdmi6GhzRegSetting[Index].ucI2cRegVal = atomHDMIRetimerRedriverTable->Hdmi6GhzRegSetting[Index].ucI2cRegVal;
    }
    IDS_HDT_CONSOLE (GNB_TRACE, "dp2_retimer_redriver_set:\n");
    DumpDpxRetimerRedriverSet (&SystemInfoTable->sIntegratedSysInfo.dp2_retimer_redriver_set);
  }
  //atom_hdmi_retimer_redriver_set dp3_retimer_redriver_set;
  atomHDMIRetimerRedriverTable = (atom_hdmi_retimer_redriver_set*)PcdGet32 (PcdCfgDp3RetimerRedriverTable);
  if (atomHDMIRetimerRedriverTable != NULL) {
    SystemInfoTable->sIntegratedSysInfo.gpucapinfo |= GPUCAPSINFO_EXT_HDMI_INIT_PER_PORT;
    SystemInfoTable->sIntegratedSysInfo.dp3_retimer_redriver_set.HdmiSlvAddr = atomHDMIRetimerRedriverTable->HdmiSlvAddr;
    SystemInfoTable->sIntegratedSysInfo.dp3_retimer_redriver_set.HdmiRegNum = atomHDMIRetimerRedriverTable->HdmiRegNum;
    SystemInfoTable->sIntegratedSysInfo.dp3_retimer_redriver_set.Hdmi6GRegNum = atomHDMIRetimerRedriverTable->Hdmi6GRegNum;
    for (Index = 0; Index < 9; Index++) {
      SystemInfoTable->sIntegratedSysInfo.dp3_retimer_redriver_set.HdmiRegSetting[Index].ucI2cRegIndex = atomHDMIRetimerRedriverTable->HdmiRegSetting[Index].ucI2cRegIndex;
      SystemInfoTable->sIntegratedSysInfo.dp3_retimer_redriver_set.HdmiRegSetting[Index].ucI2cRegVal = atomHDMIRetimerRedriverTable->HdmiRegSetting[Index].ucI2cRegVal;
    }
    for (Index = 0; Index < 3; Index++) {
      SystemInfoTable->sIntegratedSysInfo.dp3_retimer_redriver_set.Hdmi6GhzRegSetting[Index].ucI2cRegIndex = atomHDMIRetimerRedriverTable->Hdmi6GhzRegSetting[Index].ucI2cRegIndex;
      SystemInfoTable->sIntegratedSysInfo.dp3_retimer_redriver_set.Hdmi6GhzRegSetting[Index].ucI2cRegVal = atomHDMIRetimerRedriverTable->Hdmi6GhzRegSetting[Index].ucI2cRegVal;
    }
    IDS_HDT_CONSOLE (GNB_TRACE, "dp3_retimer_redriver_set:\n");
    DumpDpxRetimerRedriverSet (&SystemInfoTable->sIntegratedSysInfo.dp3_retimer_redriver_set);
  }

  //ATOM_14NM_DPPHY_DP_TUNINGSET dp_hbr_tuningset;
  if (PcdGet16 (PcdAmdDpPhyOverride) & ATOM_ENABLE_DP_HBR_TUNINGSET) {
    SystemInfoTable->sIntegratedSysInfo.dp_hbr_tuningset.phy_sel = PcdGet8 (PcdAmdDpHbrPhySel);
    SystemInfoTable->sIntegratedSysInfo.dp_hbr_tuningset.version = PcdGet8 (PcdAmdDpHbrVersion);
    SystemInfoTable->sIntegratedSysInfo.dp_hbr_tuningset.table_size = PcdGet16 (PcdAmdDpHbrTableSize);
  }
  AtomDpHbrPhyDpSetting = (ATOM_14NM_DPPHY_DP_SETTING*) PcdGet32 (PcdAtomDpHbrTuningSetting);
  if (AtomDpHbrPhyDpSetting != NULL) {
    for (Index = 0; Index < 10; Index++) {
      SystemInfoTable->sIntegratedSysInfo.dp_hbr_tuningset.dptuning[Index].dp_vs_pemph_level = AtomDpHbrPhyDpSetting[Index].dp_vs_pemph_level;  //UINT8
      SystemInfoTable->sIntegratedSysInfo.dp_hbr_tuningset.dptuning[Index].margindeemph = AtomDpHbrPhyDpSetting[Index].margindeemph;            //UINT16
      SystemInfoTable->sIntegratedSysInfo.dp_hbr_tuningset.dptuning[Index].deemph_6db_4 = AtomDpHbrPhyDpSetting[Index].deemph_6db_4;            //UINT8
      SystemInfoTable->sIntegratedSysInfo.dp_hbr_tuningset.dptuning[Index].boostadj = AtomDpHbrPhyDpSetting[Index].boostadj;                    //UINT8
    }
  } else {
    (*PeiServices)->SetMem (&(SystemInfoTable->sIntegratedSysInfo.dp_hbr_tuningset.dptuning), sizeof (ATOM_14NM_DPPHY_DP_SETTING) * 10, 0xFF);
  }

  //ATOM_14NM_DPPHY_DP_TUNINGSET dp_hbr2_tuningset;
  if (PcdGet16 (PcdAmdDpPhyOverride) & ATOM_ENABLE_DP_HBR2_TUNINGSET) {
    SystemInfoTable->sIntegratedSysInfo.dp_hbr2_tuningset.phy_sel = PcdGet8 (PcdAmdDpHbr2PhySel);
    SystemInfoTable->sIntegratedSysInfo.dp_hbr2_tuningset.version = PcdGet8 (PcdAmdDpHbr2Version);
    SystemInfoTable->sIntegratedSysInfo.dp_hbr2_tuningset.table_size = PcdGet16 (PcdAmdDpHbr2TableSize);
  }
  AtomDpHbrPhyDpSetting = (ATOM_14NM_DPPHY_DP_SETTING*) PcdGet32 (PcdAtomDpHbr2TuningSetting);
  if (AtomDpHbrPhyDpSetting != NULL) {
    for (Index = 0; Index < 10; Index++) {
      SystemInfoTable->sIntegratedSysInfo.dp_hbr2_tuningset.dptuning[Index].dp_vs_pemph_level = AtomDpHbrPhyDpSetting[Index].dp_vs_pemph_level;  //UINT8
      SystemInfoTable->sIntegratedSysInfo.dp_hbr2_tuningset.dptuning[Index].margindeemph = AtomDpHbrPhyDpSetting[Index].margindeemph;            //UINT16
      SystemInfoTable->sIntegratedSysInfo.dp_hbr2_tuningset.dptuning[Index].deemph_6db_4 = AtomDpHbrPhyDpSetting[Index].deemph_6db_4;            //UINT8
      SystemInfoTable->sIntegratedSysInfo.dp_hbr2_tuningset.dptuning[Index].boostadj = AtomDpHbrPhyDpSetting[Index].boostadj;                    //UINT8
    }
  } else {
    (*PeiServices)->SetMem (&(SystemInfoTable->sIntegratedSysInfo.dp_hbr2_tuningset.dptuning), sizeof (ATOM_14NM_DPPHY_DP_SETTING) * 10, 0xFF);
  }

  //ATOM_14NM_DPPHY_DP_TUNINGSET dp_edp_tuningset;
  if (PcdGet16 (PcdAmdDpPhyOverride) & ATOM_ENABLE_EDP_TUNINGSET) {
    SystemInfoTable->sIntegratedSysInfo.edp_tuningset.phy_sel = PcdGet8 (PcdAmdEDpPhySel);
    SystemInfoTable->sIntegratedSysInfo.edp_tuningset.version = PcdGet8 (PcdAmdEDpVersion);
    SystemInfoTable->sIntegratedSysInfo.edp_tuningset.table_size = PcdGet16 (PcdAmdEDpTableSize);
  }
  AtomEDpTuningSetting = (ATOM_14NM_DPPHY_DP_SETTING*) PcdGet32 (PcdAtomEDpTuningSetting);
  if (AtomEDpTuningSetting != NULL) {
    for (Index = 0; Index < 10; Index++) {
      SystemInfoTable->sIntegratedSysInfo.edp_tuningset.dptuning[Index].dp_vs_pemph_level = AtomEDpTuningSetting[Index].dp_vs_pemph_level;  //UINT8
      SystemInfoTable->sIntegratedSysInfo.edp_tuningset.dptuning[Index].margindeemph = AtomEDpTuningSetting[Index].margindeemph;            //UINT16
      SystemInfoTable->sIntegratedSysInfo.edp_tuningset.dptuning[Index].deemph_6db_4 = AtomEDpTuningSetting[Index].deemph_6db_4;            //UINT8
      SystemInfoTable->sIntegratedSysInfo.edp_tuningset.dptuning[Index].boostadj = AtomEDpTuningSetting[Index].boostadj;                    //UINT8
    }
  } else {
    (*PeiServices)->SetMem (&(SystemInfoTable->sIntegratedSysInfo.edp_tuningset.dptuning), sizeof (ATOM_14NM_DPPHY_DP_SETTING) * 10, 0xFF);
  }

  //uint32_t  reserved[66];

  IDS_HDT_CONSOLE (GNB_TRACE, "GfxIntInfoTableInitRV Exit [0x%x]\n", Status);
  return  Status;
}


/**
 *---------------------------------------------------------------------------------------
 *  ApplyIntegratedSysInfoOverride
 *
 *  Description:
 *     To apply IntegratedSysInfo Override
 *  Parameters:
 *    @param[in]     PeiServices   Pointer to EFI_PEI_SERVICES pointer
 *    @param[in]     LogicalId     To decide what CPU Family it is.
 *    @param[in]     PackageType   To decide what CPU Socket it is.
 *
 *---------------------------------------------------------------------------------------
 **/
VOID
ApplyIntegratedSysInfoOverride (
  IN CONST EFI_PEI_SERVICES         **PeiServices,
  IN       SOC_LOGICAL_ID           LogicalId,
  IN       UINT32                   PackageType
  )
{
  return;
}


/*----------------------------------------------------------------------------------------*/
/**
 * AmdNbiosGfx driver entry point for RV
 *
 *
 *
 * @param[in]  FileHandle  Standard configuration header
 * @param[in]  PeiServices Pointer to EFI_PEI_SERVICES pointer
 * @retval     EFI_STATUS
 */

EFI_STATUS
EFIAPI
AmdNbioGfxRVPeiEntry (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  PEI_AMD_NBIO_PCIE_SERVICES_PPI  *PcieServicesPpi;
  PCIe_PLATFORM_CONFIG            *Pcie;
  AMD_MEMORY_INFO_HOB             *AmdMemoryInfoHob;
  EFI_PEI_HOB_POINTERS            Hob;
  UINT32                          Index;
  AMD_MEMORY_RANGE_DESCRIPTOR     *Range;
  UINT32                          Property;
  EFI_STATUS                      Status;
  GNB_HANDLE                      *GnbHandle;
  AMD_CONFIG_PARAMS               *StdHeader;
  GNB_PCIE_INFORMATION_DATA_HOB   *PciePlatformConfigHob;
  UINT32                          FbTopValue;
  UINT32                          FbBaseValue;
  UINT32                          ConfigMemsizeValue;
  BOOLEAN                         ProgramValues;
  UINT64                          TopOfMemory;
  UINT64                          TopOfMemory2;
  UINT32                          MMIOBase;
  UINT32                          MMIOLimit;
  UINT32                          MMIOEnable;
  UINT32                          VGAHOLE;
  ATOM_FUSION_SYSTEM_INFO_V9      *SysInfoBuffer;
  UINT32                          TotalSize;
  UINT32                          IntegratedTableSize;
  UINT32                          UmcConfig;
  UINT32                          Memtype;
  UINT32                          Data;
  UINT32                          Umachannelnumber;
  UINT32                          UmaDimm0number;
  UINT32                          UmaDimm1number;
  UINT32                          ResultValue;
  AUDIO_PORT_CONNECTIVITY_STRUCT  AudioPortField;
  UINT8                           MaxAudioEndpoints;
  UINT8                           AudioEPCount;
  EFI_BOOT_MODE                   BootMode;
  NBIO_Frame_Buffer_DATA_HOB      *FrambufferHob;
  ATOM_FUSION_SYSTEM_INFO_V9      *SystemInfoBufferHob;
  BOOLEAN                         IsUmaAbove4G;
  UINT32                          SmuArg[6];
  SOC_LOGICAL_ID                  LogicalId;
  AMD_PEI_SOC_LOGICAL_ID_PPI      *SocLogicalIdPpi;
  UINT32                          PackageType;

  AGESA_TESTPOINT (TpNbioGfxPeiEntry, NULL);
  IDS_HDT_CONSOLE (MAIN_FLOW, "AmdNbioGfxInit Entry\n");
  StdHeader = NULL;
  GnbHandle = NULL;
  SysInfoBuffer = NULL;
  ProgramValues = FALSE;
  Umachannelnumber = 0;
  UmaDimm0number = 0;
  UmaDimm1number = 0;
  UmcConfig = 0;
  IsUmaAbove4G = FALSE;
  ConfigMemsizeValue = 0;
  FbTopValue = 0;
  FbBaseValue = 0;

  Status = PeiServicesGetBootMode (&BootMode);

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
  GnbHandle = NbioGetHandle (Pcie);

  IDS_HOOK (IDS_HOOK_NBIO_GFX_INIT_CONFIG, (VOID *)GnbHandle, NULL);

  // Need debug options
  Property = TABLE_PROPERTY_DEFAULT;

  // Locate AMD_MEMORY_INFO_HOB
  AmdMemoryInfoHob = NULL;
  Status = PeiServicesGetHobList (&Hob.Raw);
  while (!END_OF_HOB_LIST (Hob)) {
    if (Hob.Header->HobType == EFI_HOB_TYPE_GUID_EXTENSION &&
        CompareGuid ( &Hob.Guid->Name, &gAmdMemoryInfoHobGuid)) {
      AmdMemoryInfoHob = (AMD_MEMORY_INFO_HOB *) (Hob.Raw +
                          sizeof (EFI_HOB_GENERIC_HEADER) +
                          sizeof (EFI_GUID));
      Status = EFI_SUCCESS;
      break;
    }
    Hob.Raw = GET_NEXT_HOB (Hob);
  }
  if (AmdMemoryInfoHob != NULL) {
    // Adjust Property Gfxd on Debug Info and PCD's
    // From Earlier
    // Need to get UMA_BASE, UMA_SIZE to program these registers

    IDS_HDT_CONSOLE (MAIN_FLOW, "AMD_MEMORY_INFO_HOB at 0x%x\n", AmdMemoryInfoHob);
    IDS_HDT_CONSOLE (MAIN_FLOW, "  Version: 0x%x\n", AmdMemoryInfoHob->Version);
    IDS_HDT_CONSOLE (MAIN_FLOW, "  NumberOfDescriptor: 0x%x\n", AmdMemoryInfoHob->NumberOfDescriptor);
    for (Index = 0; Index < AmdMemoryInfoHob->NumberOfDescriptor; Index++) {
      Range = (AMD_MEMORY_RANGE_DESCRIPTOR*)&AmdMemoryInfoHob->Ranges[Index];
      IDS_HDT_CONSOLE (MAIN_FLOW, "  Range: %d\n", Index);
      IDS_HDT_CONSOLE (MAIN_FLOW, "    Base: 0x%lx\n", Range->Base);
      IDS_HDT_CONSOLE (MAIN_FLOW, "    Size: 0x%lx\n", Range->Size);
      IDS_HDT_CONSOLE (MAIN_FLOW, "    Attribute: 0x%x\n", Range->Attribute);
      if ((Range->Attribute) == AMD_MEMORY_ATTRIBUTE_UMA) {
        FbBaseValue = (UINT32) (Range->Base >> 24);

        if (PcdGet8 (PcdCfgIgpuContorl) == 0) {
          Range->Base = 0;
          Range->Size = 0;
          FbBaseValue = 0;
        }

        FbTopValue = (UINT32) ((Range->Base + Range->Size - 1) >> 24);
        ConfigMemsizeValue = (UINT32)(Range->Size >> 20);

        ProgramValues = TRUE;
        IDS_HDT_CONSOLE (MAIN_FLOW, "B  FbTopValue %x\n", FbTopValue);

        if (BootMode != BOOT_ON_S3_RESUME) {
          SysInfoBuffer = (ATOM_FUSION_SYSTEM_INFO_V9 *) (UINT32) (Range->Base + Range->Size);
          SysInfoBuffer = (ATOM_FUSION_SYSTEM_INFO_V9 *) ((UINT32) (SysInfoBuffer) - sizeof (ATOM_FUSION_SYSTEM_INFO_V9));
          if (Range->Base > SYSTEM_IA32_MAX_LINEAR_ADDRESS) {
            IsUmaAbove4G = TRUE;
            Status = PeiServicesCreateHob (
              EFI_HOB_TYPE_GUID_EXTENSION,
              sizeof (NBIO_Frame_Buffer_DATA_HOB),
              &FrambufferHob
              );

            FrambufferHob->EfiHobGuidType.Name = gGnbIntegratedSysInfoHobGuid;
            SystemInfoBufferHob = (ATOM_FUSION_SYSTEM_INFO_V9 *) &(FrambufferHob->AtomFusionSystemInfoV9);
            IDS_HDT_CONSOLE (MAIN_FLOW, "B  SystemInfoBufferHob %x\n", SystemInfoBufferHob);
            IDS_HDT_CONSOLE (MAIN_FLOW, "B  SysInfoBuffer %x\n", SysInfoBuffer);

            SysInfoBuffer = SystemInfoBufferHob;
            IDS_HDT_CONSOLE (MAIN_FLOW, "A  SystemInfoBufferHob %x\n", SystemInfoBufferHob);
            IDS_HDT_CONSOLE (MAIN_FLOW, "A  SysInfoBuffer %x\n", SysInfoBuffer);

            FrambufferHob->UMAInfo.Base = Range->Base;
            FrambufferHob->UMAInfo.Size = Range->Size;
            IDS_HDT_CONSOLE (MAIN_FLOW, "A  FrambufferHob->UMAInfo.Base %lx\n", FrambufferHob->UMAInfo.Base);
            IDS_HDT_CONSOLE (MAIN_FLOW, "A  FrambufferHob->UMAInfo.Size %lx\n", FrambufferHob->UMAInfo.Size);
          }

          TotalSize = sizeof (ATOM_FUSION_SYSTEM_INFO_V9);
          IntegratedTableSize = sizeof (ATOM_INTEGRATED_SYSTEM_INFO_V1_11);
          (**PeiServices).SetMem (
                            SysInfoBuffer,
                            sizeof (ATOM_FUSION_SYSTEM_INFO_V9),
                            0
                            );
          // Get Dimm Info
          // UMC 0 Dimm 0
          NbioRegisterRead (GnbHandle, TYPE_SMN, AddrMask_UMC0_Dimm0, &Memtype, 0);
          IDS_HDT_CONSOLE (MAIN_FLOW, "AddrMask_UMC0_Dimm0 %x\n", Memtype);
          Data = (Memtype & 0xFF);
          if (Data != 0) {
            UmaDimm0number++;
            NbioRegisterRead (GnbHandle, TYPE_SMN, Umc0ConfigAddress, &UmcConfig, 0);
            UmcConfig = (UmcConfig & MaskBit0To2);
          }

          // UMC 0 Dimm 1
          NbioRegisterRead (GnbHandle, TYPE_SMN, AddrMask_UMC0_Dimm1, &Memtype, 0);
          IDS_HDT_CONSOLE (MAIN_FLOW, "AddrMask_UMC0_Dimm1 %x\n", Memtype);
          Data = (Memtype & 0xFF);
          if (Data != 0) {
            UmaDimm0number++;
            NbioRegisterRead (GnbHandle, TYPE_SMN, Umc0ConfigAddress, &UmcConfig, 0);
            UmcConfig = (UmcConfig & MaskBit0To2);
          }

          // UMC 1 Dimm0
          NbioRegisterRead (GnbHandle, TYPE_SMN, AddrMask_UMC1_Dimm0, &Memtype, 0);
          IDS_HDT_CONSOLE (MAIN_FLOW, "AddrMask_UMC1_Dimm0 %x\n", Memtype);
          Data = (Memtype & 0xFF);
          if (Data != 0) {
            UmaDimm1number++;
            NbioRegisterRead (GnbHandle, TYPE_SMN, Umc1ConfigAddress, &UmcConfig, 0);
            UmcConfig = (UmcConfig & MaskBit0To2);
          }

          // UMC 1 Dimm1
          NbioRegisterRead (GnbHandle, TYPE_SMN, AddrMask_UMC1_Dimm1, &Memtype, 0);
          IDS_HDT_CONSOLE (MAIN_FLOW, "AddrMask_UMC1_Dimm0 %x\n", Memtype);
          Data = (Memtype & 0xFF);
          if (Data != 0) {
            UmaDimm1number++;
            NbioRegisterRead (GnbHandle, TYPE_SMN, Umc1ConfigAddress, &UmcConfig, 0);
            UmcConfig = (UmcConfig & MaskBit0To2);
          }
          //Calculate channel number
          if (UmaDimm0number) {
            Umachannelnumber++;
          }
          if (UmaDimm1number) {
            Umachannelnumber++;
          }

          switch (UmcConfig) {
          case 1:  // DDR3
            SysInfoBuffer->sIntegratedSysInfo.memorytype = 0x18;
            break;
          case 0:  // DDR4
            SysInfoBuffer->sIntegratedSysInfo.memorytype = 0x1A;
            break;
          case 2:  // GDDR5
          default:
            SysInfoBuffer->sIntegratedSysInfo.memorytype = 0x02;
            break;
          case 4:  // LpDdr3MemType
            SysInfoBuffer->sIntegratedSysInfo.memorytype = 0x1D;
            break;
          case 5:  // LpDdr4MemType
            SysInfoBuffer->sIntegratedSysInfo.memorytype = 0x1E;
            break;
          }
          IDS_HDT_CONSOLE (MAIN_FLOW, "Memory Type = 0x%x\n", SysInfoBuffer->sIntegratedSysInfo.memorytype);

          SysInfoBuffer->sIntegratedSysInfo.umachannelnumber = (UINT8) Umachannelnumber;
          IDS_HDT_CONSOLE (MAIN_FLOW, "UmcConfig %x\n", UmcConfig);
          IDS_HDT_CONSOLE (MAIN_FLOW, "Umachannelnumber %x\n", Umachannelnumber);

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
          PackageType = LibAmdGetPackageType ((AMD_CONFIG_PARAMS *) NULL);

          ApplyIntegratedSysInfoOverride (PeiServices, LogicalId, PackageType);

          GfxIntInfoTableInitRV (SysInfoBuffer, Pcie);
        }
        IDS_HOOK (IDS_HOOK_NBIO_GFX_INIT_FRAME_BUFFER, NULL, (VOID *)SysInfoBuffer);
      }
    }
  } else {
    // For now, hardcode UMA at 0xD0000000 with size 256MB (0x10000000)
    IDS_HDT_CONSOLE (MAIN_FLOW, "Hardcoding UMA information\n");
    // CONFIG_MEMSIZE is the size of UMA in MB
    ConfigMemsizeValue = UMA_SIZE_HARDCODE >> 20;

    // This register defines the location of the frame buffer in the internal address space.
    // The internal address space has 48 address bits. Minimum Frame buffer size is 16 MB.
    // and the start location is required to be on a 16 MB boundary.
    // Therefore BASE(23:0) must be 0x000000 and TOP(23:0) must be 0xFFFFFF.
    // Only the 24 MSBs of each are loaded in the register.
    // If inside the TOP/BASE aperture, the address is corrected by subtracting BASE.
    // The register fields define bits (47:24) for both BASE and TOP
    FbBaseValue = UMA_BASE_HARDCODE >> 24;
    FbTopValue = (UMA_BASE_HARDCODE + UMA_SIZE_HARDCODE - 1) >> 24;
    ProgramValues = TRUE;
  }
  if (TRUE == ProgramValues) {
    NbioRegisterWrite (GnbHandle, MC_CONFIG_MEMSIZE_TYPE, MC_CONFIG_MEMSIZE_ADDRESS, &ConfigMemsizeValue, 0);
    NbioRegisterWrite (GnbHandle, MC_VM_FB_LOCATION_BASE_TYPE, 0x6A05C, &FbBaseValue, 0);
    NbioRegisterWrite (GnbHandle, MC_VM_FB_LOCATION_TOP_TYPE, MC_VM_FB_LOCATION_TOP_ADDRESS, &FbTopValue, 0);
    IDS_HDT_CONSOLE (MAIN_FLOW, "MC_CONFIG_MEMSIZE_ADDRESS : %x \n", ConfigMemsizeValue);
    IDS_HDT_CONSOLE (MAIN_FLOW, "0x6A05C : %x \n", FbBaseValue);
    IDS_HDT_CONSOLE (MAIN_FLOW, "MC_VM_FB_LOCATION_TOP_ADDRESS : %x \n", FbTopValue);

    //VMSHAREDPF:MC_VM_APT_CNTL
    NbioRegisterRMW (
      GnbHandle,
      TYPE_SMN,
      MC_VM_APT_CNTL_Address,
      (UINT32) ~(DIRECT_SYSTEM_EN_Mask),
      (UINT32) 2,
      0
      );

    // TOM
    TopOfMemory  = AsmReadMsr64 (TOP_MEM);
    NbioRegisterRMW (
      GnbHandle,
      TYPE_SMN,
      MC_VM_NB_TOP_OF_DRAM_SLOT1_Address,
      (UINT32) ~(TOP_OF_DRAM_Mask), // Bit23 ~ Bit31
      (UINT32) TopOfMemory,
      0
      );

    // Lower TOM2
    TopOfMemory2 = AsmReadMsr64 (TOP_MEM2);
    NbioRegisterRMW (
      GnbHandle,
      TYPE_SMN,
      MC_VM_NB_LOWER_Address,
      (UINT32)~(0xFF800001), // Bit23 ~ Bit31 and Bit0
      (UINT32)(TopOfMemory2 | BIT0),
      0
      );
    NbioRegisterRead (GnbHandle, TYPE_SMN, MC_VM_NB_LOWER_Address, &ResultValue, 1);
    IDS_HDT_CONSOLE (MAIN_FLOW, "PEI Lower TOM2 ResultValue : %x \n", ResultValue);

    // UPPER TOM2
    NbioRegisterRMW (
      GnbHandle,
      TYPE_SMN,
      MC_VM_NB_UPPER_TOP_OF_DRAM2_Address,
      (UINT32)~(MC_VM_NB_UPPER_TOM2_Mask), // Bit0 ~ Bit11
      (UINT32)(RShiftU64 ((UINT64) TopOfMemory2, 32)),
      0
      );
    NbioRegisterRead (GnbHandle, TYPE_SMN, MC_VM_NB_UPPER_TOP_OF_DRAM2_Address, &ResultValue, 1);
    IDS_HDT_CONSOLE (MAIN_FLOW, "PEI UPPER TOM2 ResultValue : %x \n", ResultValue);

    // MMIO BASE
    NbioRegisterRead (GnbHandle, TYPE_SMN, 0x13B1005C, &MMIOBase, 0);
    NbioRegisterWrite (GnbHandle, TYPE_SMN, MC_VM_NB_MMIOBASE_Address, &MMIOBase, 0);

    // MMIO Limit
    NbioRegisterRead (GnbHandle, TYPE_SMN, 0x13B10060, &MMIOLimit, 0);
    NbioRegisterWrite (GnbHandle, TYPE_SMN, MC_VM_NB_MMIOLIMIT_Address, &MMIOLimit, 0);

    // VGA HOLE
    NbioRegisterRead (GnbHandle, TYPE_SMN, 0x13B00084, &VGAHOLE, 0);
    NbioRegisterRMW (
      GnbHandle,
      TYPE_SMN,
      MC_VM_NB_PCI_ARB_ADDRESS,
      (UINT32)~(VGA_HOLE_Mask),
      (UINT32) VGAHOLE, // 1 means VGA range is decoded as MMIO region, 0 system memory.
      0
      );

    // MMIO Enable
    NbioRegisterRead (GnbHandle, TYPE_SMN, 0x13B0004C, &MMIOEnable, 0);
    NbioRegisterRMW (
      GnbHandle,
      TYPE_SMN,
      MC_VM_NB_PCI_CTRL_ADDRESS,
      (UINT32)~(MMIOENABLE_Mask),
      (UINT32) MMIOEnable, // MMIOEnable bit23 is valid, don't shift it.
      0
      );

    // ATHUB: RPB_SDPPORT_CNTL: NBIF_DMA_CFG_MODE to 0
    NbioRegisterRMW (
      GnbHandle,
      TYPE_SMN,
      RPB_SDPPORT_CNTL_Address,
      (UINT32)~(NBIF_DMA_CFG_MODE_Mask),
      (UINT32) 0,     // MMIOEnable bit23 is valid, don't shift it.
      0
      );
  }

  MaxAudioEndpoints = PcdGet8 (PcdCfgMaxNumAudioEndpoints);
  AudioEPCount = MaxAudioEndpoints;
  if (MaxAudioEndpoints != 0) {
    AudioEPCount = 7 - AudioEPCount; //   00 - CC_RCU_DC_AUDIO_PORT_CONNECTIVITY_PORT_CONNECTIVITY_ALL : All
                                     //   01 - CC_RCU_DC_AUDIO_PORT_CONNECTIVITY_PORT_CONNECTIVITY_6 : 6
                                     //   02 - CC_RCU_DC_AUDIO_PORT_CONNECTIVITY_PORT_CONNECTIVITY_5 : 5
                                     //   03 - CC_RCU_DC_AUDIO_PORT_CONNECTIVITY_PORT_CONNECTIVITY_4 : 4
                                     //   04 - CC_RCU_DC_AUDIO_PORT_CONNECTIVITY_PORT_CONNECTIVITY_3 : 3
                                     //   05 - CC_RCU_DC_AUDIO_PORT_CONNECTIVITY_PORT_CONNECTIVITY_2 : 2
                                     //   06 - CC_RCU_DC_AUDIO_PORT_CONNECTIVITY_PORT_CONNECTIVITY_1 : 1
                                     //   07 - CC_RCU_DC_AUDIO_PORT_CONNECTIVITY_PORT_CONNECTIVITY_0 : 0
    AudioPortField.Field.REG_PORT_CONNECTIVITY = AudioEPCount;
    AudioPortField.Field.REG_PORT_CONNECTIVITY_OVERRIDE_ENABLE = 1;
    NbioRegisterWrite (
      GnbHandle,
      TYPE_SMN,
      AUDIO_PORT_CONNECTIVITY_ADDRESS,
      &AudioPortField,
      0
      );
  }

  NbioRegisterRMW (GnbHandle,
                   TYPE_SMN,
                   NBIF1_SATA_STRAP0_ADDRESS,
                   (UINT32) ~(NBIFSTRAP0_FUNC_EN_DEV0_F0_MASK),
                   (1 << NBIFSTRAP0_FUNC_EN_DEV0_F0_OFFSET),
                   0
                   );

  // Enable SDMA Clock Gating
  NbioRegisterRMW (
    GnbHandle,
    TYPE_SMN,
    SDMA0_CLK_CTRL_ADDRESS,
    (UINT32)~(SDMA0_CLK_CTRL_SOFT_OVERRIDE7_MASK |
    SDMA0_CLK_CTRL_SOFT_OVERRIDE6_MASK |
    SDMA0_CLK_CTRL_SOFT_OVERRIDE5_MASK |
    SDMA0_CLK_CTRL_SOFT_OVERRIDE4_MASK |
    SDMA0_CLK_CTRL_SOFT_OVERRIDE3_MASK |
    SDMA0_CLK_CTRL_SOFT_OVERRIDE2_MASK |
    SDMA0_CLK_CTRL_SOFT_OVERRIDE1_MASK |
    SDMA0_CLK_CTRL_SOFT_OVERRIDE0_MASK),
    (UINT32) (0 << SDMA0_CLK_CTRL_SOFT_OVERRIDE7_OFFSET |
    0 << SDMA0_CLK_CTRL_SOFT_OVERRIDE6_OFFSET |
    0 << SDMA0_CLK_CTRL_SOFT_OVERRIDE5_OFFSET |
    0 << SDMA0_CLK_CTRL_SOFT_OVERRIDE4_OFFSET |
    0 << SDMA0_CLK_CTRL_SOFT_OVERRIDE3_OFFSET |
    0 << SDMA0_CLK_CTRL_SOFT_OVERRIDE2_OFFSET |
    0 << SDMA0_CLK_CTRL_SOFT_OVERRIDE1_OFFSET |
    0 << SDMA0_CLK_CTRL_SOFT_OVERRIDE0_OFFSET),
    0
    );

  IDS_HOOK (IDS_HOOK_NBIO_GFX_VGA_REGISTER_CONFIG, (VOID *)GnbHandle, NULL);
  //Recovery mode for PEI GOP
  if (BootMode == BOOT_IN_RECOVERY_MODE && PcdGetBool (PcdPeiGopEnable)) {
    NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
    Status = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (GnbHandle), SMC_MSG_PowerUpGfx, SmuArg, GNB_REG_ACC_FLAG_S3SAVE);
    PcdSet32 (PcdPeiGopConfigMemsize, ConfigMemsizeValue);
    PcdSet32 (PcdPeiGopVmFbOffset, FbBaseValue);
    PcdSet32 (PcdPeiGopVmFbLocationTop, FbTopValue);
    IDS_HDT_CONSOLE (MAIN_FLOW, "PcdPeiGopConfigMemsize : %x \n", PcdGet32 (PcdPeiGopConfigMemsize));
    IDS_HDT_CONSOLE (MAIN_FLOW, "PcdPeiGopVmFbOffset : %x \n", PcdGet32 (PcdPeiGopVmFbOffset));
    IDS_HDT_CONSOLE (MAIN_FLOW, "PcdPeiGopVmFbLocationTop : %x \n", PcdGet32 (PcdPeiGopVmFbLocationTop));
    Status = PeiServicesNotifyPpi (mPeiGraphics);
    Status = PeiServicesInstallPpi (&mNbioGfxServicesPpiList); //This driver is done.
  }
  IDS_HDT_CONSOLE (MAIN_FLOW, "AmdNbioGfxInit Exit\n");
  AGESA_TESTPOINT (TpNbioGfxPeiExit, NULL);

  return EFI_SUCCESS;
}

/*----------------------------------------------------------------------------------------*/
/**
 * Dump  display path settings
 *
 *
 *
 * @param[in] DisplayPath            Display path
 */

VOID
GfxDebugDumpDisplayPath (
  IN       EXT_DISPLAY_PATH            *DisplayPath
  )
{
  IDS_HDT_CONSOLE (GNB_TRACE, "     usDeviceTag = 0x%x\n",
   DisplayPath->usDeviceTag
   );
  IDS_HDT_CONSOLE (GNB_TRACE, "     usDeviceACPIEnum = 0x%x\n",
   DisplayPath->usDeviceACPIEnum
   );
  IDS_HDT_CONSOLE (GNB_TRACE, "     usDeviceConnector = 0x%x\n",
   DisplayPath->usDeviceConnector
   );

  IDS_HDT_CONSOLE (GNB_TRACE, "     ucExtAUXDDCLutIndex = 0x%x\n",
   DisplayPath->ucExtAUXDDCLutIndex
   );

  IDS_HDT_CONSOLE (GNB_TRACE, "     ucExtHPDPINLutIndex = 0x%x\n",
   DisplayPath->ucExtHPDPINLutIndex
   );

  IDS_HDT_CONSOLE (GNB_TRACE, "     usExtEncoderObjId = 0x%x\n",
   DisplayPath->usExtEncoderObjId
   );
  IDS_HDT_CONSOLE (GNB_TRACE, "     ucChannelMapping = 0x%x\n",
   DisplayPath->ChannelMapping.ucChannelMapping
   );
  IDS_HDT_CONSOLE (GNB_TRACE, "     ucChPNInvert = 0x%x\n",
   DisplayPath->ucChPNInvert
   );
  IDS_HDT_CONSOLE (GNB_TRACE, "     usCaps = 0x%x\n",
   DisplayPath->usCaps
   );
}



EFI_STATUS
PeiGraphicInit (
  IN EFI_PEI_SERVICES                  **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR         *NotifyDescriptor,
  IN VOID                              *Ppi
  )
{
  return EFI_SUCCESS;
}


