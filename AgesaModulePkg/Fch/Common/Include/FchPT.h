/* $NoKeywords:$ */
/**
 * @file
 *
 * Agesa structures and definitions
 *
 * Contains AMD AGESA core interface
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Include
 * @e \$Revision: 317069 $   @e \$Date: 2015-04-20 11:25:50 -0700 (Mon, 20 Apr 2015) $
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
 **/


#ifndef _FCHPT_H_
#define _FCHPT_H_

#pragma pack (push, 1)

//++++++++++++++++++++++++++++++++++ Promontory param structure
/// PT_USB structure
typedef struct {
  UINT8         PTXhciGen1;                     ///< PTXhciGen1
  UINT8         PTXhciGen2;                     ///< PTXhciGen2
  UINT8         PTAOAC;                         ///< PTAOAC
  UINT8         PTHW_LPM ;                      ///< PTHW_LPM
  UINT8         PTDbC;                          ///< PTDbC
  UINT8         PTXHC_PME;                      ///< PTXHC_PME
  UINT8         Equalization4;                  ///< Enable/Disable Equalization 4
  UINT8         Redriver;                       ///< Enable/Disable Redriver Setting
  UINT8         XhciLockEnable;                 ///< Enable/Disable PT lock
} PT_USB;
/// PT_SATA structure
typedef struct {
  UINT8         PTSataMode;                     ///< PTSataMode
  UINT8         PTSataAggresiveDevSlpP0;        ///< PTSataAggresiveDevSlpP0
  UINT8         PTSataAggresiveDevSlpP1;        ///< PTSataAggresiveDevSlpP1
  UINT8         PTSataAggrLinkPmCap;            ///< PTSataAggrLinkPmCap
  UINT8         PTSataPscCap;                   ///< PTSataPscCap
  UINT8         PTSataSscCap;                   ///< PTSataSscCap
  UINT8         PTSataMsiCapability;            ///< PTSataPscCap
  UINT8         PTSataPortMdPort0;              ///< PTSataPortMdPort0
  UINT8         PTSataPortMdPort1;              ///< PTSataPortMdPort1
  UINT8         PTSataHotPlug;                  ///< PTSataHotPlug
} PT_SATA;

/// PT_SATAPort structure
typedef struct {
  UINT8         PTSataPort0Enable;             ///<PTSataPort0 Enable/Disable
  UINT8         PTSataPort1Enable;             ///<PTSataPort1 Enable/Disable        
  UINT8         PTSataPort2Enable;             ///<PTSataPort2 Enable/Disable       
  UINT8         PTSataPort3Enable;             ///<PTSataPort3 Enable/Disable          
  UINT8         PTSataPort4Enable;             ///<PTSataPort4 Enable/Disable
  UINT8         PTSataPort5Enable;             ///<PTSataPort5 Enable/Disable
  UINT8         PTSataPort6Enable;             ///<PTSataPort6 Enable/Disable
  UINT8         PTSataPort7Enable;             ///<PTSataPort7 Enable/Disable
} PT_SATAPort;


/// PT_PCIE structure
typedef struct {
  UINT8         PromontoryPCIeEnable;                   ///< PCIeEnable
  UINT8         PromontoryPCIeASPM;                     ///< PCIeASPM
} PT_PCIE;
/// PT_DIDVID structure
typedef struct {
  UINT8         GppNumber;                             ///< GppNumber
  UINT8         PXEFound;                              ///< PXE Bridge Found
  UINT8         PXEDevNumber;                          ///< PXE Device Number
  UINT8         XhciLock;                              ///< XHCI lock detect
  UINT32        XhciID;                                ///< XhciDIDVID
  UINT32        SataID;                                ///< SataDIDVID
  UINT32        GpioID;                                ///< GpioDIDVID
  UINT64        FwVersion;                             ///< FwVersion
} PT_ADDR;

/// PT_USBPort structure
typedef struct {
  UINT8         PTUsb31P0;                    ///< PTUsb31Port0 Enable/Disable for PROM3/4
  UINT8         PTUsb31P1;                    ///< PTUsb31Port0 Enable/Disable for PROM3/4
  UINT8         PTUsb30P0;                    ///< PTUsb30Port0 Enable/Disable for PROM3/4
  UINT8         PTUsb30P1;                    ///< PTUsb30Port1 Enable/Disable for PROM3/4
  UINT8         PTUsb30P2;                    ///< PTUsb30Port2 Enable/Disable for PROM3/4
  UINT8         PTUsb30P3;                    ///< PTUsb30Port3 Enable/Disable for PROM3/4
  UINT8         PTUsb30P4;                    ///< PTUsb30Port4 Enable/Disable for PROM3/4
  UINT8         PTUsb30P5;                    ///< PTUsb30Port5 Enable/Disable for PROM3/4
  UINT8         PTUsb20P0;                    ///< PTUsb20Port0 Enable/Disable for PROM3/4
  UINT8         PTUsb20P1;                    ///< PTUsb20Port1 Enable/Disable for PROM3/4
  UINT8         PTUsb20P2;                    ///< PTUsb20Port2 Enable/Disable for PROM3/4
  UINT8         PTUsb20P3;                    ///< PTUsb20Port3 Enable/Disable for PROM3/4
  UINT8         PTUsb20P4;                    ///< PTUsb20Port4 Enable/Disable for PROM3/4
  UINT8         PTUsb20P5;                    ///< PTUsb20Port5 Enable/Disable for PROM3/4
} PT_USBPort;

/// PT_USBPort structure for PRO460
typedef struct {
  BOOLEAN       PTUsb31P0;                    ///< PTUsb31Port0 Enable/Disable for PRO460
  BOOLEAN       PTUsb31P1;                    ///< PTUsb31Port1 Enable/Disable for PRO460
  BOOLEAN       PTUsb30P0;                    ///< PTUsb30Port0 Enable/Disable for PRO460
  BOOLEAN       PTUsb30P1;                    ///< PTUsb30Port1 Enable/Disable for PRO460
  BOOLEAN       PTUsb30P2;                    ///< PTUsb30Port2 Enable/Disable for PRO460
  BOOLEAN       PTUsb30P3;                    ///< PTUsb30Port3 Enable/Disable for PRO460
  BOOLEAN       PTUsb20P0;                    ///< PTUsb20Port0 Enable/Disable for PRO460
  BOOLEAN       PTUsb20P1;                    ///< PTUsb20Port1 Enable/Disable for PRO460
  BOOLEAN       PTUsb20P2;                    ///< PTUsb20Port2 Enable/Disable for PRO460
  BOOLEAN       PTUsb20P3;                    ///< PTUsb20Port3 Enable/Disable for PRO460
  BOOLEAN       PTUsb20P4;                    ///< PTUsb20Port4 Enable/Disable for PRO460
  BOOLEAN       PTUsb20P5;                    ///< PTUsb20Port5 Enable/Disable for PRO460
} PT_USBPortP460;

/// PT_USBPort structure for PROM2
typedef struct {
  UINT8         PTUsb31P0;                    ///< PTUsb31Port0 Enable/Disable for PROM2
  UINT8         PTUsb31P1;                    ///< PTUsb31Port0 Enable/Disable for PROM2
  UINT8         PTUsb30P0;                    ///< PTUsb30Port0 Enable/Disable for PROM2
  UINT8         PTUsb30P1;                    ///< PTUsb30Port1 Enable/Disable for PROM2
  UINT8         PTUsb20P0;                    ///< PTUsb20Port0 Enable/Disable for PROM2
  UINT8         PTUsb20P1;                    ///< PTUsb20Port1 Enable/Disable for PROM2
  UINT8         PTUsb20P2;                    ///< PTUsb20Port2 Enable/Disable for PROM2
  UINT8         PTUsb20P3;                    ///< PTUsb20Port3 Enable/Disable for PROM2
  UINT8         PTUsb20P4;                    ///< PTUsb20Port4 Enable/Disable for PROM2
  UINT8         PTUsb20P5;                    ///< PTUsb20Port5 Enable/Disable for PROM2
} PT_USBPortPROM2;


/// PT_USBPort structure for PROM1
typedef struct {
  UINT8         PTUsb31P0;                    ///< PTUsb31Port0 Enable/Disable for PROM1
  UINT8         PTUsb31P1;                    ///< PTUsb31Port0 Enable/Disable for PROM1
  UINT8         PTUsb30P0;                    ///< PTUsb30Port0 Enable/Disable for PROM1
  UINT8         PTUsb20P0;                    ///< PTUsb20Port0 Enable/Disable for PROM1
  UINT8         PTUsb20P1;                    ///< PTUsb20Port1 Enable/Disable for PROM1
  UINT8         PTUsb20P2;                    ///< PTUsb20Port2 Enable/Disable for PROM1
  UINT8         PTUsb20P3;                    ///< PTUsb20Port3 Enable/Disable for PROM1
  UINT8         PTUsb20P4;                    ///< PTUsb20Port4 Enable/Disable for PROM1
  UINT8         PTUsb20P5;                    ///< PTUsb20Port5 Enable/Disable for PROM1
} PT_USBPortPROM1;


///PTUSB31TxStructure
typedef struct {
  UINT8         USB31Gen1Swing;           ///< PT USB31PCS_B1 genI swing
  UINT8         USB31Gen2Swing;           ///< PT USB31PCS_B1 genII swing
  UINT8         USB31Gen1PreEmEn;         ///< PT USB31PCS_B1 genI pre-emphasis enable
  UINT8         USB31Gen2PreEmEn;         ///< PT USB31PCS_B1 genII pre-emphasis enable
  UINT8         USB31Gen1PreEmLe;         ///< PT USB31PCS_B1 genI pre-emphasis level
  UINT8         USB31Gen2PreEmLe;         ///< PT USB31PCS_B1 genII pre-emphasis level
  UINT8         USB31Gen1PreShEn;         ///< PT USB31PCS_B1 genI pre-shoot enable
  UINT8         USB31Gen2PreShEn;         ///< PT USB31PCS_B1 genII pre-shoot enable
  UINT8         USB31Gen1PreShLe;         ///< PT USB31PCS_B1 genI pre-shoot level
  UINT8         USB31Gen2PreShLe;         ///< PT USB31PCS_B1 genII pre-shoot level
} PT_USB31Tx;

///PTUSB30TxStructure
typedef struct {
  UINT8         USB30Gen1Swing;           ///< PTUSB30PCS_B3 genI swing
  UINT8         USB30Gen1PreEmEn;         ///< PTUSB30PCS_B3 genI pre-emphasis enable
  UINT8         USB30Gen1PreEmLe;         ///< PTUSB30PCS_B3 genI pre-emphasis level
} PT_USB30Tx;

///PTUSBTxStructure
typedef struct {
  PT_USB31Tx    USB31Tx[2];               ///< PT /LP-PT USB31Tx setting
  PT_USB30Tx    USB30Tx[6];               ///< PT /LP-PT USB30Tx setting
  UINT8         USB20B2Tx00;              ///< PT USB2.0 TX driving current, 7: largest By USB_HSDP/N[0]
  UINT8         USB20B2Tx05;              ///< PT USB2.0 TX driving current, 7: largest By USB_HSDP/N[5]
  UINT8         USB20B3Tx1113;            ///< PT /LP-PT USB2.0 TX driving current, 7: largest By USB_HSDP/N[13][11]
  UINT8         USB20B3Tx1012;            ///< PT /LP-PT USB2.0 TX driving current, 7: largest By USB_HSDP/N[12][10]
  UINT8         USB20B4Tx0206;            ///< PT /LP-PT USB2.0 TX driving current, 7: largest By USB_HSDP/N[2][6]
  UINT8         USB20B4Tx0307;            ///< PT /LP-PT USB2.0 TX driving current, 7: largest By USB_HSDP/N[3][7]
  UINT8         USB20B5Tx0408;            ///< PT /LP-PT USB2.0 TX driving current, 7: largest By USB_HSDP/N[4][8]
  UINT8         USB20B5Tx0109;            ///< PT /LP-PT USB2.0 TX driving current, 7: largest By USB_HSDP/N[1][9]
} PT_USBTx;

///PTSataTxStructure
typedef struct {
  UINT8        SATAGen1Swing;             ///< genI swing
  UINT8        SATAGen2Swing;             ///< genII swing
  UINT8        SATAGen3Swing;             ///< genIII swing
  UINT8        SATAGen1PreEmEn;           ///< genI pre-emphasis enable
  UINT8        SATAGen2PreEmEn;           ///< genII pre-emphasis enable
  UINT8        SATAGen3PreEmEn;           ///< genIII pre-emphasis enable
  UINT8        SATAGen1PreEmLevel;        ///< genI pre-emphasis level
  UINT8        SATAGen2PreEmLevel;        ///< genII pre-emphasis level
  UINT8        SATAGen3PreEmLevel;        ///< genIII pre-emphasis level
} PT_SATATx;

///PT Svid Ssid Structure
typedef struct {
  UINT16        SVID;             ///< Svid
  UINT16        SSID;             ///< Ssid
} PT_ID;

///SSP data Structure to get PT root port
typedef struct {
  BOOLEAN      SspExist;                    ///< SspPlatform
  UINT8        SspRB;                       ///< Ssp RootBridge for PT root port
  UINT32       SspPtAddress;                ///< Ssp Pt root port
} SSP_RootBridge;

///Promontory param structure
typedef struct _FCH_PT {
  PT_USB          PromontoryUSB;             ///<PTUSBStructure
  PT_SATA         PromontorySATA;            ///<PTSATAStructure
  PT_SATAPort     PromontorySATAPort;        ///<PTSATAPortStructure
  PT_PCIE         PromontoryPCIE;            ///<PTPCIEStructure
  PT_ADDR         PromontoryAddr;            ///<PTIDStructure
  PT_USBPort      PromontoryUSBPort;         ///<PTUSBPortStructure
  PT_USBPortP460  PTUSBPortPRO460;           ///<PTUSBPortStructure for PRO460
  PT_USBPortPROM2 PTUSBPortPROM2;            ///<PTUSBPortStructure for PROM2
  PT_USBPortPROM1 PTUSBPortPROM1;            ///<PTUSBPortStructure for PROM1
  PT_USBTx        PTUSBTX;                   ///<PTUSBTX
  PT_USBTx        LPPTUSBTX;                 ///<LP-PTUSBTX
  PT_SATATx       PTSATATX[8];               ///<PTSATATX
  BOOLEAN         PCIEPorts[8];              ///<Enable/Disable PCIE Switch Downstream Ports
  BOOLEAN         LPPTGPPClkForceOn[8];      ///<Enable/Disable LP PT GPP Clock Force On
  SSP_RootBridge  SspPtBridge;               ///<SSP data Structure to get PT root port
  PT_ID           PTID[8];                   ///<PTID
} FCH_PT;

//-------------------------------------------- Promontory param structure
#pragma pack (pop)

#endif // _FCHPT_H_

