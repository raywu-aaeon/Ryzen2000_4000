/* $NoKeywords:$ */
 /**
 * @file
 *
 * AMD FCH INIT API, and related functions.
 *
 * Contains code that initializes the FCH Init PPI.
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  UEFI
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-09 10:28:05 -0800 (Tue, 09 Dec 2014) $
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

#ifndef _AMD_FCH_INIT_PPI_H_
#define _AMD_FCH_INIT_PPI_H_

extern EFI_GUID gAmdFchInitPpiGuid;

typedef struct _AMD_FCH_INIT_PPI  AMD_FCH_INIT_PPI;

/// Configuration values for BLDCFG_FCH_GPP_LINK_CONFIG
typedef enum {
  FchPortA4       = 0,                   ///< 4:0:0:0
  FchPortA2B2     = 2,                   ///< 2:2:0:0
  FchPortA2B1C1   = 3,                   ///< 2:1:1:0
  FchPortA1B1C1D1 = 4                    ///< 1:1:1:1
} FCH_GPP_LINKMODE;

///
/// FCH_GPP_PORT_CONFIG - Fch GPP port config structure
///
typedef struct {
  BOOLEAN               PortPresent;                    ///< Port connection
                                                        ///  @par
                                                        ///  @li <b>0</b> - Port doesn't have slot. No need to train the link
                                                        ///  @li <b>1</b> - Port connection defined and needs to be trained
                                                        ///
  BOOLEAN               PortDetected;                   ///< Link training status
                                                        ///  @par
                                                        ///  @li <b>0</b> - EP not detected
                                                        ///  @li <b>1</b> - EP detected
                                                        ///
  BOOLEAN               PortIsGen2;                     ///< Port link speed configuration
                                                        ///  @par
                                                        ///  @li <b>00</b> - Auto
                                                        ///  @li <b>01</b> - Forced GEN1
                                                        ///  @li <b>10</b> - Forced GEN2
                                                        ///  @li <b>11</b> - Reserved
                                                        ///
  BOOLEAN               PortHotPlug;                    ///< Support hot plug?
                                                        ///  @par
                                                        ///  @li <b>0</b> - No support
                                                        ///  @li <b>1</b> - support
                                                        ///
  UINT8                 PortMisc;                       ///  PortMisc - Reserved
} FCH_GPP_PORT_CONFIG_R;

///
/// GPP structure
///
typedef struct {
  FCH_GPP_PORT_CONFIG_R PortCfg[4];                     /// GPP port configuration structure
  FCH_GPP_LINKMODE      GppLinkConfig;                  ///< GppLinkConfig - PCIE_GPP_Enable[3:0]
                                                        ///  @li  <b>0000</b> - Port ABCD -> 4:0:0:0
                                                        ///  @li  <b>0010</b> - Port ABCD -> 2:2:0:0
                                                        ///  @li  <b>0011</b> - Port ABCD -> 2:1:1:0
                                                        ///  @li  <b>0100</b> - Port ABCD -> 1:1:1:1
                                                        ///
  BOOLEAN               GppFunctionEnable;              ///< GPP Function - 0:disable, 1:enable
  BOOLEAN               GppToggleReset;                 ///< Toggle GPP core reset
  UINT8                 GppHotPlugGeventNum;            ///< Hotplug GEVENT # - valid value 0-31
  UINT8                 GppFoundGfxDev;                 ///< Gpp Found Gfx Device
                                                        ///  @li   <b>0</b> - Not found
                                                        ///  @li   <b>1</b> - Found
                                                        ///
  BOOLEAN               GppGen2;                        ///< GPP Gen2 - 0:disable, 1:enable
  UINT8                 GppGen2Strap;                   ///< GPP Gen2 Strap - 0:disable, 1:enable, FCH itself uses this
  BOOLEAN               GppMemWrImprove;                ///< GPP Memory Write Improve - 0:disable, 1:enable
  BOOLEAN               GppUnhidePorts;                 ///< GPP Unhide Ports - 0:disable, 1:enable
  UINT8                 GppPortAspm;                    ///< GppPortAspm - ASPM state for all GPP ports
                                                        ///  @li   <b>01</b> - Disabled
                                                        ///  @li   <b>01</b> - L0s
                                                        ///  @li   <b>10</b> - L1
                                                        ///  @li   <b>11</b> - L0s + L1
                                                        ///
  BOOLEAN               GppLaneReversal;                ///< GPP Lane Reversal - 0:disable, 1:enable
  BOOLEAN               GppPhyPllPowerDown;             ///< GPP PHY PLL Power Down - 0:disable, 1:enable
  BOOLEAN               GppDynamicPowerSaving;          ///< GPP Dynamic Power Saving - 0:disable, 1:enable
  BOOLEAN               PcieAer;                        ///< PcieAer - Advanced Error Report: 0/1-disable/enable
  BOOLEAN               PcieRas;                        ///< PCIe RAS - 0:disable, 1:enable
  BOOLEAN               PcieCompliance;                 ///< PCIe Compliance - 0:disable, 1:enable
  BOOLEAN               PcieSoftwareDownGrade;          ///< PCIe Software Down Grade
  BOOLEAN               UmiPhyPllPowerDown;             ///< UMI PHY PLL Power Down - 0:disable, 1:enable
  BOOLEAN               SerialDebugBusEnable;           ///< Serial Debug Bus Enable
  UINT8                 GppHardwareDownGrade;           ///< GppHardwareDownGrade - Gpp HW Down Grade function 0:Disable, 1-4: portA-D
  UINT8                 GppL1ImmediateAck;              ///< GppL1ImmediateAck - Gpp L1 Immediate ACK 0: enable, 1: disable
  BOOLEAN               NewGppAlgorithm;                ///< NewGppAlgorithm - New GPP procedure
  UINT8                 HotPlugPortsStatus;             ///< HotPlugPortsStatus - Save Hot-Plug Ports Status
  UINT8                 FailPortsStatus;                ///< FailPortsStatus - Save Failure Ports Status
  UINT8                 GppPortMinPollingTime;          ///< GppPortMinPollingTime - Min. Polling time for Gpp Port Training
} FCH_GPP_R;


/// FCH INIT PPI definition for XHCI
typedef
VOID
(EFIAPI *FP_FCH_XHCI_RECOVERY_PR) (
  AMD_FCH_INIT_PPI   *This,
  UINT32             XhciRomAddress
  );

/// FCH INIT PPI definition for EHCI
typedef
VOID
(EFIAPI *FP_FCH_EHCI_RECOVERY_PR) (
  AMD_FCH_INIT_PPI   *This,
  UINT32             EhciTemporaryBarAddress
  );

/// FCH INIT PPI definition for SATA
typedef
VOID
(EFIAPI *FP_FCH_SATA_RECOVERY_PR) (
  AMD_FCH_INIT_PPI   *This,
  UINT32             SataBar0,
  UINT32             SataBar5
  );

// FCH INIT PPI defiition for GPP
typedef
VOID
(EFIAPI *FP_FCH_GPP_RECOVERY_PR) (
  AMD_FCH_INIT_PPI   *This,
  FCH_GPP_R          *FchGpp
  );

// FCH INIT PPI defiition for eMMC
typedef
VOID
(EFIAPI *FP_FCH_EMMC_RECOVERY_PR) (
  AMD_FCH_INIT_PPI   *This
  );
/// FCH INIT PPI definition
typedef struct _AMD_FCH_INIT_PPI {
  UINTN                      Revision;                ///< Revision number
  VOID                       *FchResetData;           ///< Fch Reset Data structure
  VOID                       *PtResetData;            ///< PT Reset Data structure
  FP_FCH_XHCI_RECOVERY_PR    FpFchXhciRecovery;       ///< Xhci initial Fcuntion for recovery mode.
  FP_FCH_EHCI_RECOVERY_PR    FpFchEhciRecovery;       ///< Ehci Initial Function for recovery mode.
  FP_FCH_SATA_RECOVERY_PR    FpFchSataRecovery;       ///< Sata Initial Function for recovery mode.
  FP_FCH_GPP_RECOVERY_PR     FpFchGppRecovery;        ///< Gpp Initial Function for Recovery mode.
  FP_FCH_EMMC_RECOVERY_PR    FpFchEmmcRecovery;       ///< eMMC Initial Function for Recovery mode.
} AMD_FCH_INIT_PPI;

//
// current PPI revision
//
#define AMD_FCH_INIT_PPI_REV  0x01


#endif // _AMD_FCH_INIT_PPI_H_

