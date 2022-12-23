/* $NoKeywords:$ */
/**
 * @file
 *
 * Service procedure to Set PCIe topology segment ASPM L1SS
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 313706 $   @e \$Date: 2020-01-31 11:02:43 +0800 (Fri, 31 Jan 2020) $
 *
 */
/*
 ****************************************************************************
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
/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include <GnbDxio.h>
#include <Filecode.h>
#include <Library/IdsLib.h>
#include <Library/GnbPcieConfigLib.h>
#include <Library/AmdBaseLib.h>
#include <Library/NbioSmuV10Lib.h>
#include <Library/PcieMiscCommLib.h>
#include <Library/SmnAccessLib.h>
#include <GnbRegistersRV.h>

//#define FILECODE        NBIO_PCIE_RN_DXE_AMDNBIOPCIEDXE_FILECODE

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

#define DXIO_MSG_RNTM_MBOXROUTINES         58
#define FUSE_ACCESS_LOCATION               0xFFFE0000
#define FUSE_INSTANCE_MULTIPLIER           0x1000
#define HOLD_TRAINING_A_INDEX              173  ///< HOLD_TRAINING_A
#define HOLD_TRAINING_B_INDEX              254  ///< HOLD_TRAINING_B
#define PORT_STRAP_INDEX(INDEX, PORT) (INDEX + (PORT * (HOLD_TRAINING_B_INDEX - HOLD_TRAINING_A_INDEX)))
#ifndef PORT_SPACE
  #define  PORT_SPACE(HANDLE, WRAPPER, PORTINDEX, ADDRESS)   (ADDRESS + (HANDLE->RBIndex << 20) + (WRAPPER->WrapId << 22) + (PORTINDEX << 12))
#endif
/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */
BOOLEAN CheckRvOpn(VOID);

/*----------------------------------------------------------------------------------------*/
/*
 *  Routine to write pcie soft straps
 *
 *
 *
 * @param[in]  GnbHandle         The associated Gnb Handle
 * @param[in]  StrapIndex        Strap index
 * @param[out] Value             Pointer to byte
 * @param[in]  Wrapper           Pcie wrapper number
 */
VOID
WritePcieStrap (
  IN   GNB_HANDLE   *GnbHandle,
  IN   UINT16        StrapIndex,
  IN   UINT32       Value,
  IN   UINT8        Wrapper
  )
{
  UINT32 Index;
  UINT8  InstanceNumber;

  Index = FUSE_ACCESS_LOCATION;
  Index += StrapIndex;
  InstanceNumber = GnbHandle->RBIndex + Wrapper * 4; /// RBIndex is the NBIO #

  SmnRegisterWrite (
    GnbHandle->Address.Address.Bus,
    PCIE0_STRAP_INDEX_ADDRESS+ FUSE_INSTANCE_MULTIPLIER * InstanceNumber,
    &Index,
    0
    );

  SmnRegisterWrite (
    GnbHandle->Address.Address.Bus,
     PCIE0_STRAP_DATA_ADDRESS + FUSE_INSTANCE_MULTIPLIER * InstanceNumber,
     &Value,
     0
     );
}


/**----------------------------------------------------------------------------------------*/
/**
 * Interface to Disable ASPM
 *
 *
 * @param[in]  GnbHandle      Pointer to the Silicon Descriptor for this node
 *
 */
 /*----------------------------------------------------------------------------------------*/
VOID
PcieAspmBlackListInterface (
  IN       GNB_HANDLE  *GnbHandle
  )
{
  PCIe_ENGINE_CONFIG             *PcieEngine;
  PCIe_WRAPPER_CONFIG            *PcieWrapper;
  UINT32                         AspmData;
  UINT16                         Index;

  IDS_HDT_CONSOLE (GNB_TRACE, "PcieAspmBlackListInterface Enter\n");
  PcieWrapper = PcieConfigGetChildWrapper (GnbHandle);
  while (PcieWrapper != NULL) {
    PcieEngine = PcieConfigGetChildEngine (PcieWrapper);
    while (PcieEngine != NULL) {
      if (PcieLibIsEngineAllocated (PcieEngine)) {
        if (PcieConfigCheckPortStatus (PcieEngine, INIT_STATUS_PCIE_TRAINING_SUCCESS)) {
          AspmData = PcieDisableASPMCallback (PcieEngine);
          if (AspmData != 0xFFFF) {
            // Configure PM Support
            //<Embedded_Override_Start>
            if(CheckRvOpn()) {
              Index = PORT_STRAP_INDEX(STRAP_BIF_PM_SUPPORT_A_INDEX_RV1, PcieEngine->Type.Port.PortId);
            }
            else {
              Index = PORT_STRAP_INDEX(STRAP_BIF_PM_SUPPORT_A_INDEX_RV2, PcieEngine->Type.Port.PortId);
            }
            //<Embedded_Override_End>
            IDS_HDT_CONSOLE (GNB_TRACE, " - writing strap 0x%x to ASPM %d\n", AspmData);
            WritePcieStrap (GnbHandle, Index, AspmData & 0x3, PcieWrapper->WrapId);
          }

          if ((PcieEngine->Type.Port.LinkAspmL1_1 == 1) || (PcieEngine->Type.Port.LinkAspmL1_2 == 1)) {
            if (PcieDisableL1SSCallback (PcieEngine)) {
              // PCIE_CNTL::HWINIT_WR_LOCK = 0
              SmnRegisterRMW (GnbHandle->Address.Address.Bus,
                    PCIE0_CNTL_ADDRESS,
                    (UINT32) ~(PCIE_CNTL_HWINIT_WR_LOCK_MASK),
                    0 << PCIE_CNTL_HWINIT_WR_LOCK_OFFSET,
                    GNB_REG_ACC_FLAG_S3SAVE
                    );
              if (PcieEngine->Type.Port.LinkAspmL1_1 == 0) {
                // PCIE_L1_PM_SUB_CAP_funcX::PCI_PM_L1_1_SUPPORTED = 0
                // PCIE_L1_PM_SUB_CAP_funcX::ASPM_L1_1_SUPPORTED = 0
               SmnRegisterRMW (GnbHandle->Address.Address.Bus,
                         PORT_SPACE (GnbHandle, PcieWrapper, (PcieEngine->Type.Port.PortId % 8), SMN_PCIE0FUNC0_PCIE_L1_PM_SUB_CAP_ADDRESS),
                         (UINT32) ~(PCIE_L1_PM_SUB_CNTL_PCI_PM_L1_1_EN_MASK | PCIE_L1_PM_SUB_CNTL_ASPM_L1_1_EN_MASK),
                         (0x0 << PCIE_L1_PM_SUB_CNTL_PCI_PM_L1_1_EN_OFFSET) | (0x0 << PCIE_L1_PM_SUB_CNTL_ASPM_L1_1_EN_OFFSET),
                         GNB_REG_ACC_FLAG_S3SAVE
                         );
              }
              if (PcieEngine->Type.Port.LinkAspmL1_2 == 0) {
                // PCIE_L1_PM_SUB_CAP_funcX::PCI_PM_L1_2_SUPPORTED = 0
                // PCIE_L1_PM_SUB_CAP_funcX::ASPM_L1_2_SUPPORTED = 0
               SmnRegisterRMW (GnbHandle->Address.Address.Bus,
                         PORT_SPACE (GnbHandle, PcieWrapper, (PcieEngine->Type.Port.PortId % 8), SMN_PCIE0FUNC0_PCIE_L1_PM_SUB_CAP_ADDRESS),
                         (UINT32) ~(PCIE_L1_PM_SUB_CNTL_PCI_PM_L1_2_EN_MASK | PCIE_L1_PM_SUB_CNTL_ASPM_L1_2_EN_MASK),
                         (0x0 << PCIE_L1_PM_SUB_CNTL_PCI_PM_L1_2_EN_OFFSET) | (0x0 << PCIE_L1_PM_SUB_CNTL_ASPM_L1_2_EN_OFFSET),
                         GNB_REG_ACC_FLAG_S3SAVE
                         );
              }
              // PCIE_CNTL::HWINIT_WR_LOCK = 1
              SmnRegisterRMW (GnbHandle->Address.Address.Bus,
                    PCIE0_CNTL_ADDRESS,
                    (UINT32) ~(PCIE_CNTL_HWINIT_WR_LOCK_MASK),
                    1 << PCIE_CNTL_HWINIT_WR_LOCK_OFFSET,
                    GNB_REG_ACC_FLAG_S3SAVE
                    );
            }
          }
        }
      }
      PcieEngine = PcieLibGetNextDescriptor (PcieEngine);
    }
    PcieWrapper = PcieLibGetNextDescriptor (PcieWrapper);
  }
  IDS_HDT_CONSOLE (GNB_TRACE, "PcieAspmBlackListInterface Exit\n");
}
