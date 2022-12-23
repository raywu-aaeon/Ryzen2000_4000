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


#ifndef _FCHSATA_H_
#define _FCHSATA_H_

#pragma pack (push, 1)

///
/// SATA controller Structure
///
typedef struct {
  BOOLEAN               SataEnable;                     ///< SATA enable
  BOOLEAN               SataSetMaxGen2;                 ///< SATA enable
  BOOLEAN               SataMsiEnable;                  ///< SATA MSI capability
  UINT32                SataRaidSsid;                   ///< SATA RAID mode SSID
  UINT32                SataRaid5Ssid;                  ///< SATA RAID 5 mode SSID
  UINT32                SataAhciSsid;                   ///< SATA AHCI mode SSID

  SATA_CLASS            SataClass;                      ///< SataClass - SATA Controller mode [2:0]

  UINT8                 SataEspPort;                    ///<  SataEspPort - SATA port is external accessible on a signal only connector (eSATA:)

  UINT8                 SataPortPower;                  ///<  SataPortPower - Port Power configuration

  UINT16                SataPortMd;                     ///<  SataPortMd - Port Mode

  UINT8                 SataAggrLinkPmCap;              /// SataAggrLinkPmCap - 0:OFF   1:ON
  UINT8                 SataPortMultCap;                /// SataPortMultCap - 0:OFF   1:ON
  UINT8                 SataClkAutoOff;                 /// SataClkAutoOff - AutoClockOff 0:Disabled, 1:Enabled
  UINT8                 SataPscCap;                     /// SataPscCap 1:Enable PSC, 0:Disable PSC capability
  UINT8                 BiosOsHandOff;                  /// BiosOsHandOff - Reserved
  UINT8                 SataFisBasedSwitching;          /// SataFisBasedSwitching - Reserved
  UINT8                 SataCccSupport;                 /// SataCccSupport - Reserved
  UINT8                 SataSscCap;                     /// SataSscCap - 1:Enable, 0:Disable SSC capability
  UINT8                 SataTargetSupport8Device;       /// SataTargetSupport8Device - Reserved
  UINT8                 SataDisableGenericMode;         /// SataDisableGenericMode - Reserved
  BOOLEAN               SataAhciEnclosureManagement;    /// SataAhciEnclosureManagement - Reserved
  UINT8                 SataSgpio0;                     /// SataSgpio0 - Reserved
  UINT8                 SataSgpio1;                     /// SataSgpio1 - Reserved
  UINT8                 SataPhyPllShutDown;             /// SataPhyPllShutDown - Reserved
  BOOLEAN               SataOobDetectionEnh;            /// SataOobDetectionEnh - TRUE
  BOOLEAN               SataRasSupport;                 /// SataRasSupport - Support RAS function TRUE: Enable FALSE: Disable
  BOOLEAN               SataAhciDisPrefetchFunction;    /// SataAhciDisPrefetchFunction - Disable AHCI Prefetch Function Support
  BOOLEAN               SataDevSlpPort0;                /// SataDevSlpPort0 - Reserved
  BOOLEAN               SataDevSlpPort1;                /// SataDevSlpPort1 - Reserved
  UINT8                 SataDevSlpPort0Num;             /// SataDevSlpPort0Num - Reserved
  UINT8                 SataDevSlpPort1Num;             /// SataDevSlpPort1Num - Reserved
  UINT32                TempMmio;                       /// TempMmio - Reserved
  UINT8                 Reserved[19];
} FCH_SATA2;

#pragma pack (pop)

#endif // _FCHSATA_H_

