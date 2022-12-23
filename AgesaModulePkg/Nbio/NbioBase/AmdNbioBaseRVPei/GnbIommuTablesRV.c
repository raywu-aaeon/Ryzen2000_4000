/**
 * @file
 *
 * IOMMU init tables
 *
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: GNB
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-09 12:28:05 -0600 (Tue, 09 Dec 2014) $
 *
 */
/*
*****************************************************************************
*
* Copyright 2008 - 2020 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
#include  <GnbDxio.h>
#include  <Library/GnbCommonLib.h>
#include  <Library/NbioTable.h>
#include  <GnbRegistersRV.h>
#include  <Filecode.h>

#define FILECODE  NBIO_NBIOBASE_AMDNBIOBASERVPEI_GNBIOMMUTABLESRV_FILECODE

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *           T A B L E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */

GNB_TABLE ROMDATA GnbIommuEarlyInitTableRV [] = {
//---------------------------------------------------------------------------

  GNB_ENTRY_TERMINATE
};

GNB_TABLE ROMDATA GnbIommuEnvInitTableRV [] = {
//---------------------------------------------------------------------------
// Set SB location for IOMMU
  GNB_ENTRY_COPY (
    L1_SB_LOCATION_TYPE,
    L1_SB_LOCATION_ADDRESS,
    0,
    32,
    SB_LOCATION_TYPE,
    SB_LOCATION_ADDRESS,
    0,
    32
    ),
  GNB_ENTRY_COPY (
    L2_SB_LOCATION_TYPE,
    L2_SB_LOCATION_ADDRESS,
    0,
    32,
    SB_LOCATION_TYPE,
    SB_LOCATION_ADDRESS,
    0,
    32
    ),

//---------------------------------------------------------------------------
// Disable INTx in IOMMU
  GNB_ENTRY_RMW (
    IOMMU_CONTROL_W_TYPE,
    IOMMU_CONTROL_W_ADDRESS,
    IOMMU_CONTROL_W_INTERRUPT_PIN_W_MASK,
    0x0 << IOMMU_CONTROL_W_INTERRUPT_PIN_W_OFFSET
    ),

  //---------------------------------------------------------------------------
//programs IOHC::CFG_IOHC_PCI[CFG_IOHC_PCI_Dev0Fn2RegEn] = 1h
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_IOMMU_DISABLED,
    CFG_IOHC_PCI_TYPE,
    CFG_IOHC_PCI_ADDRESS,
    SMN_00000034_CFG_IOHC_PCI_Dev0Fn2RegEn_MASK,
    (0x1 << SMN_00000034_CFG_IOHC_PCI_Dev0Fn2RegEn_OFFSET)
    ),
//Program IOMMU::L2::IOMMU_CAP_MISC[IOMMU_HT_ATS_RESV] = 0h
  GNB_ENTRY_RMW (
    IOMMU_CAP_MISC_TYPE,
    IOMMU_CAP_MISC_ADDRESS,
    SMN_00000050_IOMMU_HT_ATS_RESV_MASK,
    (0 << SMN_00000050_IOMMU_HT_ATS_RESV_OFFSET)
    ),

//---------------------------------------------------------------------------
//IOMMU L1 Initialization
//// IOAGR
  GNB_ENTRY_RMW (
    L1_CNTRL_4_AGR_TYPE,
    L1_CNTRL_4_AGR_ADDRESS,
    IOMMUL1IOAGR_0C8_ATS_multiple_resp_en_MASK |
    IOMMUL1IOAGR_0C8_Timeout_pulse_ext_En_MASK,
    (0x1 << IOMMUL1IOAGR_0C8_ATS_multiple_resp_en_OFFSET) |
    (0x1 << IOMMUL1IOAGR_0C8_Timeout_pulse_ext_En_OFFSET)
    ),
  GNB_ENTRY_RMW (
    L1_DEBUG_1_AGR_TYPE,
    L1_DEBUG_1_AGR_ADDRESS,
    IOMMUL1IOAGR_01C_REG_enable_nw_MASK |
    IOMMUL1IOAGR_01C_REG_disble_eco_invaldation_0_MASK,
    (0x1 << IOMMUL1IOAGR_01C_REG_enable_nw_OFFSET) |
    (0x1 << IOMMUL1IOAGR_01C_REG_disble_eco_invaldation_0_OFFSET)
    ),
  GNB_ENTRY_RMW (
    L1_FEATURE_CNTRL_AGR_TYPE,
    L1_FEATURE_CNTRL_AGR_ADDRESS,
    BIT1 |
    BIT2,
    1 << 1 |
    1 << 2
    ),
///@todo this should be based on data parity error handling
//  GNB_ENTRY_RMW (
//    L1_CNTRL_2_AGR_TYPE,
//    L1_CNTRL_2_AGR_ADDRESS,
//    1,
//    0x01
//    ),
//// PCIE0
  GNB_ENTRY_RMW (
    L1_CNTRL_4_PCIE0_TYPE,
    L1_CNTRL_4_PCIE0_ADDRESS,
    IOMMUL1PCIE0_0C8_ATS_multiple_resp_en_MASK |
    IOMMUL1PCIE0_0C8_Timeout_pulse_ext_En_MASK,
    (0x1 << IOMMUL1PCIE0_0C8_ATS_multiple_resp_en_OFFSET) |
    (0x1 << IOMMUL1PCIE0_0C8_Timeout_pulse_ext_En_OFFSET)
    ),
  GNB_ENTRY_RMW (
    L1_DEBUG_1_PCIE0_TYPE,
    L1_DEBUG_1_PCIE0_ADDRESS,
    IOMMUL1PCIE0_01C_REG_enable_nw_MASK |
    IOMMUL1PCIE0_01C_REG_disble_eco_invaldation_0_MASK,
    (0x1 << IOMMUL1PCIE0_01C_REG_enable_nw_OFFSET) |
    (0x1 << IOMMUL1PCIE0_01C_REG_disble_eco_invaldation_0_OFFSET)
    ),
  GNB_ENTRY_RMW (
    L1_FEATURE_CNTRL_PCIE0_TYPE,
    L1_FEATURE_CNTRL_PCIE0_ADDRESS,
    BIT1 |
    BIT2,
    1 << 1 |
    1 << 2
    ),
///@todo this should be based on data parity error handling
//  GNB_ENTRY_RMW (
//    L1_CNTRL_2_PCIE0_TYPE,
//    L1_CNTRL_2_PCIE0_ADDRESS,
//    1,
//    0x01
//    ),
////---------------------------------------------------------------------------
//// IOMMU L2 Initialization
  GNB_ENTRY_RMW (
    L2_ERR_RULE_CONTROL_0_TYPE,
    L2_ERR_RULE_CONTROL_0_ADDRESS,
    SMN_00000200_ERRRuleLock0_MASK,
    0x1 << SMN_00000200_ERRRuleDisable0_OFFSET
    ),
  GNB_ENTRY_RMW (
    L2_ERR_RULE_CONTROL_3_TYPE,
    L2_ERR_RULE_CONTROL_3_ADDRESS,
    SMN_157000C0_ERRRuleLock1_MASK,
    0x1 << SMN_157000C0_ERRRuleLock1_OFFSET
    ),
  GNB_ENTRY_RMW (
    L2_L2A_PGSIZE_CONTROL_TYPE,
    L2_L2A_PGSIZE_CONTROL_ADDRESS,
    SMN_157000D0_L2AREG_HOST_PGSIZE_MASK |
    SMN_157000D0_L2AREG_GST_PGSIZE_MASK,
    (0x49 << SMN_157000D0_L2AREG_HOST_PGSIZE_OFFSET) |
    (0x49 << SMN_157000D0_L2AREG_GST_PGSIZE_OFFSET)
    ),
  GNB_ENTRY_RMW (
    L2_L2B_PGSIZE_CONTROL_TYPE,
    L2_L2B_PGSIZE_CONTROL_ADDRESS,
    SMN_00000250_L2BREG_HOST_PGSIZE_MASK |
    SMN_00000250_L2BREG_GST_PGSIZE_MASK,
    (0x49 << SMN_00000250_L2BREG_HOST_PGSIZE_OFFSET) |
    (0x49 << SMN_00000250_L2BREG_GST_PGSIZE_OFFSET)
    ),
  GNB_ENTRY_RMW (
    L2_CONTROL_5_TYPE,
    L2_CONTROL_5_ADDRESS,
    SMN_00000130_GST_partial_ptc_cntrl_MASK,
    (0x49 << SMN_00000130_GST_partial_ptc_cntrl_OFFSET)
    ),
  GNB_ENTRY_RMW (
    L2_DEBUG_3_TYPE,
    L2_DEBUG_3_ADDRESS,
    SMN_0000011C_REG_atomic_filter_en_MASK |
    SMN_0000011C_REG_mask_l2_nw_MASK |
    SMN_0000011C_REG_ats_iw_MASK,
    (0x1 << SMN_0000011C_REG_atomic_filter_en_OFFSET) |
    (0x1 << SMN_0000011C_REG_mask_l2_nw_OFFSET) |
    (0x1 << SMN_0000011C_REG_ats_iw_OFFSET)
    ),
  GNB_ENTRY_RMW (
    L2_CP_CONTROL_TYPE,
    L2_CP_CONTROL_ADDRESS,
    SMN_00000158_CPFlushOnWait_MASK |
    SMN_00000158_CPFlushOnInv_MASK,
    (0x1 << SMN_00000158_CPFlushOnWait_OFFSET) |
    (0x0 << SMN_00000158_CPFlushOnInv_OFFSET)
    ),
  GNB_ENTRY_RMW (
    L2B_UPDATE_FILTER_CNTL_TYPE,
    L2B_UPDATE_FILTER_CNTL_ADDRESS,
    SMN_0000014C_L2b_Update_Filter_Bypass_MASK,
    (0x0 << SMN_0000014C_L2b_Update_Filter_Bypass_OFFSET)
    ),
  GNB_ENTRY_RMW (
    L2A_UPDATE_FILTER_CNTL_TYPE,
    L2A_UPDATE_FILTER_CNTL_ADDRESS,
    SMN_15700088_L2a_Update_Filter_Bypass_MASK,
    (0x0 << SMN_15700088_L2a_Update_Filter_Bypass_OFFSET)
    ),
  GNB_ENTRY_RMW (
    L2_TW_CONTROL_TYPE,
    L2_TW_CONTROL_ADDRESS,
    SMN_00000150_TWPrefetchRange_MASK |
    SMN_00000150_TWPrefetchEn_MASK,
    (0x7 << SMN_00000150_TWPrefetchRange_OFFSET) |
    (0x1 << SMN_00000150_TWPrefetchEn_OFFSET)
    ),
//---------------------------------------------------------------------------
// IOMMU Initialization
// IOMMU L2 clock gating
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_IOMMU_L2_CLOCK_GATING,
    L2_L2A_CK_GATE_CONTROL_TYPE,
    L2_L2A_CK_GATE_CONTROL_ADDRESS,
    IOMMUL2A_0CC_CKGateL2ARegsDisable_MASK | IOMMUL2A_0CC_CKGateL2ADynamicDisable_MASK | IOMMUL2A_0CC_CKGateL2ACacheDisable_MASK,
    (0x0 << IOMMUL2A_0CC_CKGateL2ARegsDisable_OFFSET) |
    (0x0 << IOMMUL2A_0CC_CKGateL2ADynamicDisable_OFFSET) |
    (0x0 << IOMMUL2A_0CC_CKGateL2ACacheDisable_OFFSET)
    ),
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_IOMMU_L2_CLOCK_GATING,
    L2_L2B_CK_GATE_CONTROL_TYPE,
    L2_L2B_CK_GATE_CONTROL_ADDRESS,
    SMN_00000240_CKGateL2BRegsDisable_MASK | SMN_00000240_CKGateL2BDynamicDisable_MASK |
    SMN_00000240_CKGateL2BMiscDisable_MASK | SMN_00000240_CKGateL2BCacheDisable_MASK,
    (0x0 << SMN_00000240_CKGateL2BRegsDisable_OFFSET) |
    (0x0 << SMN_00000240_CKGateL2BDynamicDisable_OFFSET) |
    (0x0 << SMN_00000240_CKGateL2BMiscDisable_OFFSET) |
    (0x0 << SMN_00000240_CKGateL2BCacheDisable_OFFSET)
    ),
// IOMMU L1 clock gating
  // IOAGR
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_IOMMU_L1_CLOCK_GATING,
    L1_CLKCNTRL_0_AGR_TYPE,
    L1_CLKCNTRL_0_AGR_ADDRESS,
    IOMMUL1IOAGR_0CC_L1_DMA_CLKGATE_EN_MASK | IOMMUL1IOAGR_0CC_L1_CACHE_CLKGATE_EN_MASK | IOMMUL1IOAGR_0CC_L1_CPSLV_CLKGATE_EN_MASK |
    IOMMUL1IOAGR_0CC_L1_PERF_CLKGATE_EN_MASK | IOMMUL1IOAGR_0CC_L1_MEMORY_CLKGATE_EN_MASK | IOMMUL1IOAGR_0CC_L1_REG_CLKGATE_EN_MASK |
    IOMMUL1IOAGR_0CC_L1_HOSTREQ_CLKGATE_EN_MASK | IOMMUL1IOAGR_0CC_L1_DMARSP_CLKGATE_EN_MASK | IOMMUL1IOAGR_0CC_L1_HOSTRSP_CLKGATE_EN_MASK |
    IOMMUL1IOAGR_0CC_L1_L2_CLKGATE_EN_MASK | IOMMUL1IOAGR_0CC_L1_CLKGATE_HYSTERESIS_MASK,
    (0x1 << IOMMUL1IOAGR_0CC_L1_DMA_CLKGATE_EN_OFFSET) |
    (0x1 << IOMMUL1IOAGR_0CC_L1_CACHE_CLKGATE_EN_OFFSET) |
    (0x0 << IOMMUL1IOAGR_0CC_L1_CPSLV_CLKGATE_EN_OFFSET) |
    (0x1 << IOMMUL1IOAGR_0CC_L1_PERF_CLKGATE_EN_OFFSET) |
    (0x1 << IOMMUL1IOAGR_0CC_L1_MEMORY_CLKGATE_EN_OFFSET) |
    (0x1 << IOMMUL1IOAGR_0CC_L1_REG_CLKGATE_EN_OFFSET) |
    (0x1 << IOMMUL1IOAGR_0CC_L1_HOSTREQ_CLKGATE_EN_OFFSET) |
    (0x1 << IOMMUL1IOAGR_0CC_L1_DMARSP_CLKGATE_EN_OFFSET) |
    (0x1 << IOMMUL1IOAGR_0CC_L1_HOSTRSP_CLKGATE_EN_OFFSET) |
    (0x1 << IOMMUL1IOAGR_0CC_L1_L2_CLKGATE_EN_OFFSET) |
    (0x20 << IOMMUL1IOAGR_0CC_L1_CLKGATE_HYSTERESIS_OFFSET)
    ),
  // PCIE0
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_IOMMU_L1_CLOCK_GATING,
    L1_CLKCNTRL_0_PCIE0_TYPE,
    L1_CLKCNTRL_0_PCIE0_ADDRESS,
    IOMMUL1PCIE0_0CC_L1_DMA_CLKGATE_EN_MASK | IOMMUL1PCIE0_0CC_L1_CACHE_CLKGATE_EN_MASK | IOMMUL1PCIE0_0CC_L1_CPSLV_CLKGATE_EN_MASK |
    IOMMUL1PCIE0_0CC_L1_PERF_CLKGATE_EN_MASK | IOMMUL1PCIE0_0CC_L1_MEMORY_CLKGATE_EN_MASK | IOMMUL1PCIE0_0CC_L1_REG_CLKGATE_EN_MASK |
    IOMMUL1PCIE0_0CC_L1_HOSTREQ_CLKGATE_EN_MASK | IOMMUL1PCIE0_0CC_L1_DMARSP_CLKGATE_EN_MASK | IOMMUL1PCIE0_0CC_L1_HOSTRSP_CLKGATE_EN_MASK |
    IOMMUL1PCIE0_0CC_L1_L2_CLKGATE_EN_MASK | IOMMUL1PCIE0_0CC_L1_CLKGATE_HYSTERESIS_MASK,
    (0x1 << IOMMUL1PCIE0_0CC_L1_DMA_CLKGATE_EN_OFFSET) |
    (0x1 << IOMMUL1PCIE0_0CC_L1_CACHE_CLKGATE_EN_OFFSET) |
    (0x1 << IOMMUL1PCIE0_0CC_L1_CPSLV_CLKGATE_EN_OFFSET) |
    (0x1 << IOMMUL1PCIE0_0CC_L1_PERF_CLKGATE_EN_OFFSET) |
    (0x1 << IOMMUL1PCIE0_0CC_L1_MEMORY_CLKGATE_EN_OFFSET) |
    (0x1 << IOMMUL1PCIE0_0CC_L1_REG_CLKGATE_EN_OFFSET) |
    (0x1 << IOMMUL1PCIE0_0CC_L1_HOSTREQ_CLKGATE_EN_OFFSET) |
    (0x1 << IOMMUL1PCIE0_0CC_L1_DMARSP_CLKGATE_EN_OFFSET) |
    (0x1 << IOMMUL1PCIE0_0CC_L1_HOSTRSP_CLKGATE_EN_OFFSET) |
    (0x1 << IOMMUL1PCIE0_0CC_L1_L2_CLKGATE_EN_OFFSET) |
    (0x20 << IOMMUL1PCIE0_0CC_L1_CLKGATE_HYSTERESIS_OFFSET)
    ),
//---------------------------------------------------------------------------
// Configure IOMMU Power Island
// Hide IOMMU function if disabled
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_IOMMU_DISABLED,
    CFG_IOHC_PCI_TYPE,
    CFG_IOHC_PCI_ADDRESS,
    SMN_00000034_CFG_IOHC_PCI_Dev0Fn2RegEn_MASK,
    0x0
    ),
  // Iommu
  GNB_ENTRY_RMW (
    L2_TW_CONTROL_TYPE,
    L2_TW_CONTROL_ADDRESS,
    SMN_00000150_TWPrefetchRange_MASK |
    SMN_00000150_TWPrefetchEn_MASK,
    (0x7 << SMN_00000150_TWPrefetchRange_OFFSET) |
    (0x1 << SMN_00000150_TWPrefetchEn_OFFSET)
    ),
  // PCIE0
  GNB_ENTRY_RMW (
    TYPE_SMN,
    0x1470001c,
    IOMMUL1IOAGR_01C_REG_eco_allow_update_dis_MASK,
    (0x1 << IOMMUL1IOAGR_01C_REG_Block_On_4K_wait_dis_OFFSET)
    ),
  // PCIE0
  GNB_ENTRY_RMW (
    TYPE_SMN,
    0x1480001c,
    IOMMUL1IOAGR_01C_REG_eco_allow_update_dis_MASK,
    (0x1 << IOMMUL1IOAGR_01C_REG_Block_On_4K_wait_dis_OFFSET)
    ),
  GNB_ENTRY_RMW (
    TYPE_SMN,
    0x14700034,
    IOMMUL1IOAGR_01C_REG_eco_allow_update_dis_MASK,
    (0x1 << IOMMUL1IOAGR_01C_REG_Block_On_4K_wait_dis_OFFSET)
    ),
  // PCIE0
  GNB_ENTRY_RMW (
    TYPE_SMN,
    0x13f01200,
    0xFF,
    0x1
    ),
  GNB_ENTRY_TERMINATE
};

