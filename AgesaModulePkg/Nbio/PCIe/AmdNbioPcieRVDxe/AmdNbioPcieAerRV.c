/* $NoKeywords:$ */
/**
 * @file
 *
 * Family specific PCIe configuration data
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 312288 $   @e \$Date: 2015-02-04 00:39:01 -0600 (Wed, 04 Feb 2015) $
 *
 */
/*
*****************************************************************************
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
*
*/

/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include <PiDxe.h>
#include <GnbRegistersRV.h>
#include <GnbDxio.h>
#include <IdsHookId.h>
#include <Guid/HobList.h>
#include <Guid/GnbPcieInfoHob.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Library/AmdIdsHookLib.h>
#include <Library/UefiLib.h>
#include <Library/HobLib.h>
#include <Library/NbioHandleLib.h>
#include <Library/GnbPciLib.h>
#include <Library/GnbPciAccLib.h>
#include <Library/PcieConfigLib.h>
#include <Library/NbioRegisterAccLib.h>
#include <Library/AmdIdsHookLib.h>
#include <Library/SmnAccessLib.h>
#include <Protocol/AmdNbioPcieServicesProtocol.h>
#include <Protocol/AmdNbioPcieAerProtocol.h>
#include "AmdNbioPcieAerRV.h"
#include "Filecode.h"

#define FILECODE NBIO_PCIE_AMDNBIOPCIERVDXE_AMDNBIOPCIEAERRV_FILECODE
/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
EFI_STATUS
EFIAPI
NbioSetPcieAerFeature (
  IN       AMD_NBIO_PCIE_AER_PROTOCOL  *This,
  IN       PCIe_PORT_AER_CONFIG        *PcieAerSetting
);

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */
AMD_NBIO_PCIe_AER_CONFIG NbioPcieAerConfig = {
  NUMBER_OF_PORTS,
  {
    { 1,       ///< PortAerEnable, 0=Disable 1=Enable 0xFF=do nothing //<Embedded_Override>
      1,          ///< PciDev
      1,          ///< PciFunc
      {0},        ///< CorrectableMask
      {0},        ///< UncorrectableMask
      {0},        ///< UncorrectableSeverity
    },
    { 1,       ///< PortAerEnable, 0=Disable 1=Enable 0xFF=do nothing //<Embedded_Override>
      1,          ///< PciDev
      2,          ///< PciFunc
      {0},        ///< CorrectableMask
      {0},        ///< UncorrectableMask
      {0},        ///< UncorrectableSeverity
    },
    { 1,       ///< PortAerEnable, 0=Disable 1=Enable 0xFF=do nothing //<Embedded_Override>
      1,          ///< PciDev
      3,          ///< PciFunc
      {0},        ///< CorrectableMask
      {0},        ///< UncorrectableMask
      {0},        ///< UncorrectableSeverity
    },
    { 1,       ///< PortAerEnable, 0=Disable 1=Enable 0xFF=do nothing //<Embedded_Override>
      1,          ///< PciDev
      4,          ///< PciFunc
      {0},        ///< CorrectableMask
      {0},        ///< UncorrectableMask
      {0},        ///< UncorrectableSeverity
    },
    { 1,       ///< PortAerEnable, 0=Disable 1=Enable 0xFF=do nothing //<Embedded_Override>
      1,          ///< PciDev
      5,          ///< PciFunc
      {0},        ///< CorrectableMask
      {0},        ///< UncorrectableMask
      {0},        ///< UncorrectableSeverity
    },
    { 1,       ///< PortAerEnable, 0=Disable 1=Enable 0xFF=do nothing //<Embedded_Override>
      1,          ///< PciDev
      6,          ///< PciFunc
      {0},        ///< CorrectableMask
      {0},        ///< UncorrectableMask
      {0},        ///< UncorrectableSeverity
    },
    { 1,       ///< PortAerEnable, 0=Disable 1=Enable 0xFF=do nothing //<Embedded_Override>
      1,          ///< PciDev
      7,          ///< PciFunc
      {0},        ///< CorrectableMask
      {0},        ///< UncorrectableMask
      {0},        ///< UncorrectableSeverity
    },
  }
}
  ;

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */
AMD_NBIO_PCIE_AER_PROTOCOL mAmdNbioPcieAerProtocol = {
  NbioSetPcieAerFeature
};

/*----------------------------------------------------------------------------------------*/

/**
 *---------------------------------------------------------------------------------------
 *
 *  NbioPcieAerFeatureEnable
 *
 *  Description:
 *     Enable/Disable AER.
 *
 *  Parameters:
 *    @param[in]     GnbHandle
 *    @param[in]     PortAerConfig
 *
 *    @retval         VOID
 *
 *---------------------------------------------------------------------------------------
 **/
VOID
NbioPcieAerFeatureEnable (
  IN       GNB_HANDLE                 *GnbHandle,
  IN       NBIO_PCIe_PORT_AER_CONFIG  *PortAerConfig
  )
{
  UINT32                                        Value;
  UINT32                                        AddrIndex;
  UINT32                                        CorrMaskAddr;
  UINT32                                        UnCorrMaskAddr;
  UINT32                                        UnCorrSeverityAddr;
  UINT32                                        PcieErrCntlAddr;
  PCIe_ENGINE_CONFIG                            *PcieEngine;
  PCIe_WRAPPER_CONFIG                           *PcieWrapper;
  PCIE0PortASerr_ACTION_CONTROL_STRUCT          SerrAc;
  PCIE0PortAExtFatal_ACTION_CONTROL_STRUCT      ExtFatalAc;

  IDS_HDT_CONSOLE (GNB_TRACE, "NbioPcieAerFeatureEnable Enter\n");
  PcieWrapper = PcieConfigGetChildWrapper (GnbHandle);
  while (PcieWrapper != NULL) {
    AddrIndex = (PcieWrapper->WrapId == 0) ? 0x00100000 : 0x00200000;
    PcieEngine = PcieConfigGetChildEngine (PcieWrapper);
    while (PcieEngine != NULL) {
      if (PcieLibIsEngineAllocated (PcieEngine)) {
        if ((PcieEngine->Type.Port.PortData.DeviceNumber == PortAerConfig->PciDev) &&
            (PcieEngine->Type.Port.PortData.FunctionNumber == PortAerConfig->PciFunc)) {
          IDS_HDT_CONSOLE (PCIE_MISC, "Set AER feature: Dev%d Func%d %x\n", PortAerConfig->PciDev, PortAerConfig->PciFunc, PortAerConfig->PortAerEnable);
          AddrIndex |= (PcieEngine->Type.Port.PortId % 8) << 12;
          PcieErrCntlAddr = 0x110401A8 | AddrIndex;
          CorrMaskAddr = 0x11000164 | AddrIndex;
          UnCorrMaskAddr = 0x11000158 | AddrIndex;
          UnCorrSeverityAddr = 0x1100015c | AddrIndex;

          if (PortAerConfig->PortAerEnable == 0) {
            NbioRegisterRead ( GnbHandle, TYPE_SMN, PcieErrCntlAddr, &Value, 0);
            Value |= BIT0;
            NbioRegisterWrite (GnbHandle, TYPE_SMN, PcieErrCntlAddr, &Value, GNB_REG_ACC_FLAG_S3SAVE);
          } else if (PortAerConfig->PortAerEnable == 1) {
            //
            // PCIe Correctable Error Mask
            //
            NbioRegisterRead ( GnbHandle, TYPE_SMN, CorrMaskAddr, &Value, 0);
            Value &= ~(BIT6 | BIT7 | BIT8 | BIT12 | BIT13);
            if (PortAerConfig->CorrectableMask.Field.BadTLPMask == 1) {
              Value |= BIT6;
            }
            if (PortAerConfig->CorrectableMask.Field.BadDLLPMask == 1) {
              Value |= BIT7;
            }
            if (PortAerConfig->CorrectableMask.Field.ReplayNumberRolloverMask == 1) {
              Value |= BIT8;
            }
            if (PortAerConfig->CorrectableMask.Field.ReplayTimerTimeoutMask == 1) {
              Value |= BIT12;
            }
            if (PortAerConfig->CorrectableMask.Field.AdvisoryNonFatalErrorMask == 1) {
              Value |= BIT13;
            }
            NbioRegisterWrite (GnbHandle, TYPE_SMN, CorrMaskAddr, &Value, GNB_REG_ACC_FLAG_S3SAVE);

            //
            // PCIe Unorrectable Error Mask
            //
            NbioRegisterRead ( GnbHandle, TYPE_SMN, UnCorrMaskAddr, &Value, 0);
            Value &= ~(BIT4 | BIT12 | BIT14 | BIT15 | BIT16 | BIT18 | BIT19 | BIT20 | BIT21);
            if (PortAerConfig->UncorrectableMask.Field.DataLinkProtocolErrorMask == 1) {
              Value |= BIT4;
            }
            if (PortAerConfig->UncorrectableMask.Field.PoisonedTLPMask == 1) {
              Value |= BIT12;
            }
            if (PortAerConfig->UncorrectableMask.Field.CompletionTimeoutMask == 1) {
              Value |= BIT14;
            }
            if (PortAerConfig->UncorrectableMask.Field.CompleterAbortMask == 1) {
              Value |= BIT15;
            }
            if (PortAerConfig->UncorrectableMask.Field.UnexpectedCompletionMask == 1) {
              Value |= BIT16;
            }
            if (PortAerConfig->UncorrectableMask.Field.MalTlpMask == 1) {
              Value |= BIT18;
            }
            if (PortAerConfig->UncorrectableMask.Field.ECRCErrorMask == 1) {
              Value |= BIT19;
            }
            if (PortAerConfig->UncorrectableMask.Field.UnsupportedRequestErrorMask == 1) {
              Value |= BIT20;
            }
            if (PortAerConfig->UncorrectableMask.Field.AcsViolationMask == 1) {
              Value |= BIT21;
            }
            NbioRegisterWrite (GnbHandle, TYPE_SMN, UnCorrMaskAddr, &Value, GNB_REG_ACC_FLAG_S3SAVE);

            //
            // PCIe Unorrectable Error Severity
            //
            NbioRegisterRead ( GnbHandle, TYPE_SMN, UnCorrSeverityAddr, &Value, 0);
            Value &= ~(BIT4 | BIT12 | BIT14 | BIT15 | BIT16 | BIT18 | BIT19 | BIT20 | BIT21);
            if (PortAerConfig->UncorrectableSeverity.Field.DataLinkProtocolErrorSeverity == 1) {
              Value |= BIT4;
            }
            if (PortAerConfig->UncorrectableSeverity.Field.PoisonedTLPSeverity == 1) {
              Value |= BIT12;
            }
            if (PortAerConfig->UncorrectableSeverity.Field.CompletionTimeoutSeverity == 1) {
              Value |= BIT14;
            }
            if (PortAerConfig->UncorrectableSeverity.Field.CompleterAbortSeverity == 1) {
              Value |= BIT15;
            }
            if (PortAerConfig->UncorrectableSeverity.Field.UnexpectedCompletionSeverity == 1) {
              Value |= BIT16;
            }
            if (PortAerConfig->UncorrectableSeverity.Field.MalTlpSeverity == 1) {
              Value |= BIT18;
            }
            if (PortAerConfig->UncorrectableSeverity.Field.ECRCErrorSeverity == 1) {
              Value |= BIT19;
            }
            if (PortAerConfig->UncorrectableSeverity.Field.UnsupportedRequestErrorSeverity == 1) {
              Value |= BIT20;
            }
            if (PortAerConfig->UncorrectableSeverity.Field.AcsViolationSeverity == 1) {
              Value |= BIT21;
            }
            NbioRegisterWrite (GnbHandle, TYPE_SMN, UnCorrSeverityAddr, &Value, GNB_REG_ACC_FLAG_S3SAVE);
          }
        }
        IDS_HDT_CONSOLE (GNB_TRACE, "NbioPcieAerFeatureEnable(): PortID:0x%x\n", PcieEngine->Type.Port.PortId);
        //
        // Serr_ACTION_CONTROL
        //
        SmnRegisterRead(GnbHandle->Address.Address.Bus, IOHC_PORT_SPACE(GnbHandle, PcieWrapper, PcieEngine->Type.Port.PortId % 8, SMN_NBIO0_PCIE0PortASerr_ACTION_CONTROL), &(SerrAc.Value));
        SerrAc.Field.SyncFlood_En = 1;
        SerrAc.Field.LinkDis_En = 1;
        SmnRegisterWrite (GnbHandle->Address.Address.Bus, IOHC_PORT_SPACE (GnbHandle, PcieWrapper, PcieEngine->Type.Port.PortId % 8, SMN_NBIO0_PCIE0PortASerr_ACTION_CONTROL), &(SerrAc.Value), GNB_REG_ACC_FLAG_S3SAVE);
        //
        // ExtFatal_ACTION_CONTROL
        //
        SmnRegisterRead(GnbHandle->Address.Address.Bus, IOHC_PORT_SPACE(GnbHandle, PcieWrapper, PcieEngine->Type.Port.PortId % 8, SMN_NBIO0_PCIE0PortAExtFatal_ACTION_CONTROL), &(ExtFatalAc.Value));
        ExtFatalAc.Field.SyncFlood_En = 1;
        ExtFatalAc.Field.LinkDis_En = 1;
        SmnRegisterWrite (GnbHandle->Address.Address.Bus, IOHC_PORT_SPACE (GnbHandle, PcieWrapper, PcieEngine->Type.Port.PortId % 8, SMN_NBIO0_PCIE0PortAExtFatal_ACTION_CONTROL), &(ExtFatalAc.Value), GNB_REG_ACC_FLAG_S3SAVE);
      }
      PcieEngine = PcieLibGetNextDescriptor (PcieEngine);
    }
    PcieWrapper = PcieLibGetNextDescriptor (PcieWrapper);
  }

  IDS_HDT_CONSOLE (GNB_TRACE, "NbioPcieAerFeatureEnable Exit\n");
}

/**
 *---------------------------------------------------------------------------------------
 *
 *  DumpPcieAerSetting
 *
 *  Description:
 *     dump Nbio PCIe each port AER feature.
 *
 *  Parameters:
 *    @param[in]     PortAerConfig
 *
 *    @retval        VOID
 *
 *---------------------------------------------------------------------------------------
 **/
VOID DumpPcieAerSetting (
  IN       NBIO_PCIe_PORT_AER_CONFIG  *PortAerConfig
  )
{
  IDS_HDT_CONSOLE (PCIE_MISC, "Dev%d Func%d AER - %a\n", PortAerConfig->PciDev, PortAerConfig->PciFunc, PortAerConfig->PortAerEnable == 0? "Disable":"Enable");
  IDS_HDT_CONSOLE (PCIE_MISC, "  BadTLPMask - %d\n", PortAerConfig->CorrectableMask.Field.BadTLPMask);
  IDS_HDT_CONSOLE (PCIE_MISC, "  BadDLLPMask - %d\n", PortAerConfig->CorrectableMask.Field.BadDLLPMask);
  IDS_HDT_CONSOLE (PCIE_MISC, "  ReplayNumberRolloverMask - %d\n", PortAerConfig->CorrectableMask.Field.ReplayNumberRolloverMask);
  IDS_HDT_CONSOLE (PCIE_MISC, "  ReplayTimerTimeoutMask - %d\n", PortAerConfig->CorrectableMask.Field.ReplayTimerTimeoutMask);
  IDS_HDT_CONSOLE (PCIE_MISC, "  AdvisoryNonFatalErrorMask - %d\n", PortAerConfig->CorrectableMask.Field.AdvisoryNonFatalErrorMask);

  IDS_HDT_CONSOLE (PCIE_MISC, "  DataLinkProtocolErrorMask - %d\n", PortAerConfig->UncorrectableMask.Field.DataLinkProtocolErrorMask);
  IDS_HDT_CONSOLE (PCIE_MISC, "  PoisonedTLPMask - %d\n", PortAerConfig->UncorrectableMask.Field.PoisonedTLPMask);
  IDS_HDT_CONSOLE (PCIE_MISC, "  CompletionTimeoutMask - %d\n", PortAerConfig->UncorrectableMask.Field.CompletionTimeoutMask);
  IDS_HDT_CONSOLE (PCIE_MISC, "  CompleterAbortMask - %d\n", PortAerConfig->UncorrectableMask.Field.CompleterAbortMask);
  IDS_HDT_CONSOLE (PCIE_MISC, "  UnexpectedCompletionMask - %d\n", PortAerConfig->UncorrectableMask.Field.UnexpectedCompletionMask);
  IDS_HDT_CONSOLE (PCIE_MISC, "  MalTlpMask - %d\n", PortAerConfig->UncorrectableMask.Field.MalTlpMask);
  IDS_HDT_CONSOLE (PCIE_MISC, "  ECRCErrorMask - %d\n", PortAerConfig->UncorrectableMask.Field.ECRCErrorMask);
  IDS_HDT_CONSOLE (PCIE_MISC, "  UnsupportedRequestErrorMask - %d\n", PortAerConfig->UncorrectableMask.Field.UnsupportedRequestErrorMask);
  IDS_HDT_CONSOLE (PCIE_MISC, "  AcsViolationMask - %d\n", PortAerConfig->UncorrectableMask.Field.AcsViolationMask);

  IDS_HDT_CONSOLE (PCIE_MISC, "  DataLinkProtocolErrorSeverity - %d\n", PortAerConfig->UncorrectableSeverity.Field.DataLinkProtocolErrorSeverity);
  IDS_HDT_CONSOLE (PCIE_MISC, "  PoisonedTLPSeverity - %d\n", PortAerConfig->UncorrectableSeverity.Field.PoisonedTLPSeverity);
  IDS_HDT_CONSOLE (PCIE_MISC, "  CompletionTimeoutSeverity - %d\n", PortAerConfig->UncorrectableSeverity.Field.CompletionTimeoutSeverity);
  IDS_HDT_CONSOLE (PCIE_MISC, "  CompleterAbortSeverity - %d\n", PortAerConfig->UncorrectableSeverity.Field.CompleterAbortSeverity);
  IDS_HDT_CONSOLE (PCIE_MISC, "  UnexpectedCompletionSeverity - %d\n", PortAerConfig->UncorrectableSeverity.Field.UnexpectedCompletionSeverity);
  IDS_HDT_CONSOLE (PCIE_MISC, "  MalTlpSeverity - %d\n", PortAerConfig->UncorrectableSeverity.Field.MalTlpSeverity);
  IDS_HDT_CONSOLE (PCIE_MISC, "  ECRCErrorSeverity - %d\n", PortAerConfig->UncorrectableSeverity.Field.ECRCErrorSeverity);
  IDS_HDT_CONSOLE (PCIE_MISC, "  UnsupportedRequestErrorSeverity - %d\n", PortAerConfig->UncorrectableSeverity.Field.UnsupportedRequestErrorSeverity);
  IDS_HDT_CONSOLE (PCIE_MISC, "  AcsViolationSeverity - %d\n", PortAerConfig->UncorrectableSeverity.Field.AcsViolationSeverity);
}

/**
  AerSettingsOnAllPcieDevices

    When PcdAmdPcieAerReportMechanism is set to "legacy" or "MCA", firmware must program the following standard PCIe registers:
    BRIDGE_CNTL[Serr_En]=1'b1 within each root port or switch
    DEVICE_CNTL[CORR_ERR_EN, NONFATAL_ERR_EN, FATAL_ERR_EN]=3'b111 within each root port, switch and endpoint device

  @return VOID   Returns nothing
**/
VOID
AerSettingsOnAllPcieDevices (
  VOID
  )
{
  UINT16    Bus, Dev, Fun;
  PCI_ADDR  Device;
  UINT16    DeviceCapabilitiesPointer;
  PCICFG_SPACE_BRIDGE_CONTROL_STRUCT    BridgeControlReg;
  PCIE_DEVICE_CTRL_REGISTER_STRUCT      DeviceControlReg;
  UINT32    DeviceId;
  UINT32    LegacyPciAccess;

  Device.AddressValue = 0;
  DeviceCapabilitiesPointer = 0;

  for (Bus = 0; Bus <= 255; Bus++) {
    for (Dev = 0; Dev < 32; Dev++) {
      for (Fun = 0; Fun <= 7; Fun++) {
        Device.Address.Bus = Bus;
        Device.Address.Device = Dev;
        Device.Address.Function = Fun;
		
		// read from PCI register
        LegacyPciAccess = ((1 << 31) + (Device.Address.Register & 0xFC) + (Device.Address.Function << 8) + (Device.Address.Device << 11) +  (Device.Address.Bus << 16));
        LibAmdIoWrite (AccessWidth32, IOCF8, &LegacyPciAccess, NULL);
        LibAmdIoRead (AccessWidth32, IOCFC, &DeviceId, NULL);

        // Make sure device is present
        if (DeviceId != 0xFFFFFFFF) {
          if (GnbLibPciIsBridgeDevice (Device.AddressValue, NULL)) {
            // This is a bridge
            //
            // Set Serr_En in BRIDGE_CONTROL
            // IDS_HDT_CONSOLE(MAIN_FLOW, "%a Bridge BDF = %d %d %d\n", __FUNCTION__, Bus, Dev, Fun);
            GnbLibPciRead(
              Device.AddressValue | PCICFG_SPACE_BRIDGE_CONTROL_OFFSET,
              AccessWidth16,
              &(BridgeControlReg.Value),
              NULL
              );
            BridgeControlReg.Field.SerrEnable = 1;
            GnbLibPciWrite(
              Device.AddressValue | PCICFG_SPACE_BRIDGE_CONTROL_OFFSET,
              AccessWidth16,
              &(BridgeControlReg.Value),
              NULL
              );
          }
          else {
            if (GnbLibPciIsPcieDevice(Device.AddressValue, NULL)) {
              // This an Endpoint Device
              // Set CORR_ERR_EN, NONFATAL_ERR_EN, FATAL_ERR_EN in DEVICE_CNTRL
              // IDS_HDT_CONSOLE(MAIN_FLOW, "  %a Device BDF = %d %d %d\n", __FUNCTION__, Bus, Dev, Fun);
              DeviceCapabilitiesPointer = GnbLibFindPciCapability (Device.AddressValue, PCIE_CAP_ID, NULL);
              if (DeviceCapabilitiesPointer != 0) {
                GnbLibPciRead (
                  Device.AddressValue | (DeviceCapabilitiesPointer + PCIE_DEVICE_CTRL_REGISTER),
                  AccessWidth16,
                  &(DeviceControlReg.Value),
                  NULL
                );
                DeviceControlReg.Field.CorrectableErrorReportingEn = 1;
                DeviceControlReg.Field.NonFatalErrorReportingEn = 1;
                DeviceControlReg.Field.FatalErrorReportingEn = 1;
                GnbLibPciWrite (
                  Device.AddressValue | (DeviceCapabilitiesPointer + PCIE_DEVICE_CTRL_REGISTER),
                  AccessWidth16,
                  &(DeviceControlReg.Value),
                  NULL
                );
              }
            }
          }
        }
      }  //Fun
    }  //Dev
  }  //Bus
}

/**
 *---------------------------------------------------------------------------------------
 *
 *  SetPcieEcrcFeature
 *
 *  Description:
 *     Set Pcie AER ECRC feature enable.
 *
 *  Parameters:
 *    @param[in]     PciDevice
 *
 *    @retval        BOOLEAN
 *
 *---------------------------------------------------------------------------------------
 **/
BOOLEAN
SetPcieEcrcFeature (
  PCI_ADDR PciDevice
)
{
  UINT8     Bus, Dev, Fun;
  UINT16    ParentCapPtr;
  UINT16    ChildCapPtr;
  PCI_ADDR  Device;
  BOOLEAN   EcrcEnabled;
  UINT32    ParentCapFlag;      //Set Bit 5 ECRC Generation Capable, Bit 7 ECRC Check Capable
  UINT32    ChildCapFlag;
  UINT32    UceSeverity;

  ParentCapPtr = 0;
  ChildCapPtr = 0;
  Device.AddressValue = 0;
  EcrcEnabled = FALSE;
  ParentCapFlag = 0;
  ChildCapFlag = 0;
  UceSeverity = 0;

  IDS_HDT_CONSOLE (PCIE_MISC, "SetPcieEcrcFeature Entry.\n");

  // Check Bridge AER Capabilities
  ParentCapPtr = GnbLibFindPcieExtendedCapability (PciDevice.AddressValue, PCIE_EXT_AER_CAP_ID, NULL);
  if (ParentCapPtr != 0) {
    GnbLibPciRead (PciDevice.AddressValue | (ParentCapPtr + 0x18), AccessWidth32, &ParentCapFlag, NULL);
  }

  IDS_HDT_CONSOLE (PCIE_MISC, "SetPcieEcrcFeature(): ParentCapFlag=0x%x\n, ParentCapFlag");

  // Check Ecrc Capability support
  if ((ParentCapFlag & (BIT5 | BIT7)) != 0) {
    // Get Secondary Bug
    GnbLibPciRead (PciDevice.AddressValue | 0x19, AccessWidth8, &Bus, NULL);
    Device.Address.Bus = Bus;

    // Scan support ECRC endpoint device
    for (Dev = 0; Dev < 32; Dev++) {
      Device.Address.Device = Dev;

      for (Fun = 0; Fun <= 7; Fun++) {
        Device.Address.Function = Fun;

        if (GnbLibPciIsDevicePresent (Device.AddressValue, NULL)) {
          // Is Bridge ?
          if (GnbLibPciIsBridgeDevice (Device.AddressValue, NULL)) {
            EcrcEnabled = SetPcieEcrcFeature (Device);
          } else {
            // Is Endpoint Device
            ChildCapPtr = GnbLibFindPcieExtendedCapability (Device.AddressValue, PCIE_EXT_AER_CAP_ID, NULL);
            if (ChildCapPtr != 0) {
              GnbLibPciRead (Device.AddressValue | (ChildCapPtr + 0x18), AccessWidth32, &ChildCapFlag, NULL);

              // If Bridge & Endpoint device support than enable ECRC
              if ((ChildCapFlag & (BIT5 | BIT7)) != 0) {
                // Set Endpoint ECRC Generation & Check Enable
                ChildCapFlag |= (BIT6 | BIT8);
                GnbLibPciWrite (Device.AddressValue | (ChildCapPtr + 0x18), AccessS3SaveWidth32, &ChildCapFlag, NULL);
                IDS_HDT_CONSOLE (PCIE_MISC, "Set EndPoint ECRC Enable Bus=%02X, Dev=%02X, Fun=%02X, Reg=%03X\n", \
                    Device.Address.Bus, Device.Address.Device, Device.Address.Function, (Device.AddressValue | (ChildCapPtr + 0x18)));
                EcrcEnabled = TRUE;
                if (PcdGetBool (PcdPcieEcrcSeverityFatal)) {
                  // Set ECRC Severity as Fatal
                  GnbLibPciRead (Device.AddressValue | (ChildCapPtr + 0x0C), AccessWidth32, &UceSeverity, NULL);
                  UceSeverity |= BIT19;
                  GnbLibPciWrite (Device.AddressValue | (ChildCapPtr + 0x0C), AccessS3SaveWidth32, &UceSeverity, NULL);
                }
              }
            }
          }

          // If not multi function skip to next Device
          if (!GnbLibPciIsMultiFunctionDevice (Device.AddressValue, NULL)) {
            break;
          }
        }
      }  //Fun
    }  //Dev

    // Check if Endpoint device enable ECRC
    if (EcrcEnabled) {
      // Set Bridge ECRC Generation & Check Enable
      ParentCapFlag |= (BIT6 | BIT8);
      GnbLibPciWrite (PciDevice.AddressValue | (ParentCapPtr + 0x18), AccessS3SaveWidth32, &ParentCapFlag, NULL);
      IDS_HDT_CONSOLE (PCIE_MISC, "Set Bridget ECRC Enable Bus=%02X, Dev=%02X, Fun=%02X, Reg=%03X\n", \
          PciDevice.Address.Bus, PciDevice.Address.Device, PciDevice.Address.Function, (PciDevice.AddressValue | (ParentCapPtr + 0x18)));
      if (PcdGetBool (PcdPcieEcrcSeverityFatal)) {
        // Set ECRC Severity as Fatal
        GnbLibPciRead (PciDevice.AddressValue | (ParentCapPtr + 0x0C), AccessWidth32, &UceSeverity, NULL);
        UceSeverity |= BIT19;
        GnbLibPciWrite (PciDevice.AddressValue | (ParentCapPtr + 0x0C), AccessS3SaveWidth32, &UceSeverity, NULL);
      }
    }
  }

  IDS_HDT_CONSOLE (PCIE_MISC, "SetPcieEcrcFeature Exit EcrcEnabled=0x%x\n", EcrcEnabled);
  return EcrcEnabled;
}

/**
 *---------------------------------------------------------------------------------------
 *
 *  NbioPcieAerInitRV
 *
 *  Description:
 *     Initializer Nbio PCIe each port AER feature.
 *
 *  Parameters:
 *    @param[in]     GnbHandle
 *
 *    @retval        VOID
 *
 *---------------------------------------------------------------------------------------
 **/
VOID
NbioPcieAerInitRV (
  IN       GNB_HANDLE  *GnbHandle
  )
{
  UINT32                   Index;
  PCI_ADDR                 Device;

  IDS_HDT_CONSOLE (GNB_TRACE, "NbioPcieAerInitRV Enter\n");
  NbioPcieAerConfig.NumberOfPorts = NUMBER_OF_PORTS;
  IDS_HDT_CONSOLE (GNB_TRACE, "Socket:%x, Die:%x, Instance:%x, Number of ports in NBIO: %d\n",  GnbHandle->SocketId, GnbHandle->DieNumber, GnbHandle->InstanceId, NbioPcieAerConfig.NumberOfPorts);
  IDS_HOOK (IDS_HOOK_NBIO_PCIE_AER_INIT, NULL, (VOID *)&NbioPcieAerConfig);

  for (Index = 0; Index < NbioPcieAerConfig.NumberOfPorts; Index++) {
    DumpPcieAerSetting ((NBIO_PCIe_PORT_AER_CONFIG *) &NbioPcieAerConfig.PortAerConfig[Index]);
    NbioPcieAerFeatureEnable (GnbHandle, (NBIO_PCIe_PORT_AER_CONFIG *) &NbioPcieAerConfig.PortAerConfig[Index]);
    Device.AddressValue = 0;
    Device.Address.Device = NbioPcieAerConfig.PortAerConfig[Index].PciDev;
    Device.Address.Function = NbioPcieAerConfig.PortAerConfig[Index].PciFunc;
    SetPcieEcrcFeature(Device);
	
    // disable the reporting of PCIe correctible errors.
	//<Embedded_Override_Start>
    /*NbioRegisterRMW (GnbHandle,
                     TYPE_SMN,
                     PCIE_PORT0_1A8_ADDRESS | (Index << 12),
                     (UINT32) ~(BIT0),
                     0x1,
                     GNB_REG_ACC_FLAG_S3SAVE
                     );
    */
	//<Embedded_Override_End>
  }

  IDS_HDT_CONSOLE (GNB_TRACE, "NbioPcieAerInitRV Exit\n");
}

/**
 *---------------------------------------------------------------------------------------
 *
 *  NbioSetPcieAerFeature
 *
 *  Description:
 *     Enable/Disable AER feature.
 *
 *  Parameters:
 *    @param[in]     GnbHandle
 *    @param[in]     PortAerConfig
 *
 *    @retval        EFI_STATUS
 *
 *---------------------------------------------------------------------------------------
 **/
EFI_STATUS
EFIAPI
NbioSetPcieAerFeature (
  IN       AMD_NBIO_PCIE_AER_PROTOCOL  *This,
  IN       PCIe_PORT_AER_CONFIG        *PcieAerSetting
  )
{
  EFI_STATUS        Status;
  UINT16            PcieCapPtr;
  UINT32            Value;
  PCI_ADDR          Device;

  // IDS_HDT_CONSOLE (MAIN_FLOW, "NbioSetPcieAerFeature Entry\n");
  Status = EFI_UNSUPPORTED;
  Device.AddressValue = 0;

  if (PcieAerSetting->AerEnable == 1) {
    Device.Address.Bus = PcieAerSetting->PciBus;
    Device.Address.Device = PcieAerSetting->PciDev;
    Device.Address.Function = PcieAerSetting->PciFunc;

    PcieCapPtr = GnbLibFindPcieExtendedCapability (Device.AddressValue, PCIE_EXT_AER_CAP_ID, NULL);
    if (PcieCapPtr != 0) {
      // Uncorrectable Error Mask Register (Offset 08h)
      GnbLibPciRead (Device.AddressValue | (PcieCapPtr + 0x08), AccessWidth32, &Value, NULL);
      if (PcieAerSetting->UncorrectableMask.Field.DataLinkProtocolErrorMask == 1) {
        Value |= BIT4;
      }
      if (PcieAerSetting->UncorrectableMask.Field.PoisonedTLPMask == 1) {
        Value |= BIT12;
      }
      if (PcieAerSetting->UncorrectableMask.Field.CompletionTimeoutMask == 1) {
        Value |= BIT14;
      }
      if (PcieAerSetting->UncorrectableMask.Field.CompleterAbortMask == 1) {
        Value |= BIT15;
      }
      if (PcieAerSetting->UncorrectableMask.Field.UnexpectedCompletionMask == 1) {
        Value |= BIT16;
      }
      if (PcieAerSetting->UncorrectableMask.Field.MalTlpMask == 1) {
        Value |= BIT18;
      }
      if (PcieAerSetting->UncorrectableMask.Field.ECRCErrorMask == 1) {
        Value |= BIT19;
      }
      if (PcieAerSetting->UncorrectableMask.Field.UnsupportedRequestErrorMask == 1) {
        Value |= BIT20;
      }
      if (PcieAerSetting->UncorrectableMask.Field.AcsViolationMask == 1) {
        Value |= BIT21;
      }
      GnbLibPciWrite (Device.AddressValue | (PcieCapPtr + 0x08), AccessS3SaveWidth32, &Value, NULL);

      // Uncorrectable Error Severity Register (Offset 0Ch)
      GnbLibPciRead (Device.AddressValue | (PcieCapPtr + 0x0C), AccessWidth32, &Value, NULL);
      if (PcieAerSetting->UncorrectableSeverity.Field.DataLinkProtocolErrorSeverity == 1) {
        Value |= BIT4;
      }
      if (PcieAerSetting->UncorrectableSeverity.Field.PoisonedTLPSeverity == 1) {
        Value |= BIT12;
      }
      if (PcieAerSetting->UncorrectableSeverity.Field.CompletionTimeoutSeverity == 1) {
        Value |= BIT14;
      }
      if (PcieAerSetting->UncorrectableSeverity.Field.CompleterAbortSeverity == 1) {
        Value |= BIT15;
      }
      if (PcieAerSetting->UncorrectableSeverity.Field.UnexpectedCompletionSeverity == 1) {
        Value |= BIT16;
      }
      if (PcieAerSetting->UncorrectableSeverity.Field.MalTlpSeverity == 1) {
        Value |= BIT18;
      }
      if (PcieAerSetting->UncorrectableSeverity.Field.ECRCErrorSeverity == 1) {
        Value |= BIT19;
      }
      if (PcieAerSetting->UncorrectableSeverity.Field.UnsupportedRequestErrorSeverity == 1) {
        Value |= BIT20;
      }
      if (PcieAerSetting->UncorrectableSeverity.Field.AcsViolationSeverity == 1) {
        Value |= BIT21;
      }
      GnbLibPciWrite (Device.AddressValue | (PcieCapPtr + 0x0C), AccessS3SaveWidth32, &Value, NULL);

      // Correctable Error Mask Register (Offset 14h)
      GnbLibPciRead (Device.AddressValue | (PcieCapPtr + 0x14), AccessWidth32, &Value, NULL);
      if (PcieAerSetting->CorrectableMask.Field.BadTLPMask == 1) {
        Value |= BIT6;
      }
      if (PcieAerSetting->CorrectableMask.Field.BadDLLPMask == 1) {
        Value |= BIT7;
      }
      if (PcieAerSetting->CorrectableMask.Field.ReplayNumberRolloverMask == 1) {
        Value |= BIT8;
      }
      if (PcieAerSetting->CorrectableMask.Field.ReplayTimerTimeoutMask == 1) {
        Value |= BIT12;
      }
      if (PcieAerSetting->CorrectableMask.Field.AdvisoryNonFatalErrorMask == 1) {
        Value |= BIT13;
      }
      GnbLibPciWrite (Device.AddressValue | (PcieCapPtr + 0x14), AccessS3SaveWidth32, &Value, NULL);
      Status = EFI_SUCCESS;
    }
  }

  // IDS_HDT_CONSOLE (MAIN_FLOW, "NbioSetPcieAerFeature Exit(%x)\n", Status);
  return Status;
}


