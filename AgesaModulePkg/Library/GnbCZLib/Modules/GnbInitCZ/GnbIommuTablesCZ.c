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
 * @e \$Revision: 317957 $   @e \$Date: 2015-05-02 01:55:13 +0800 (Sat, 02 May 2015) $
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
/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include  "Gnb.h"
#include  "GnbPcie.h"
#include  "GnbCommonLib.h"
#include  "GnbTable.h"
#include  "GnbRegistersCZ.h"
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

GNB_TABLE ROMDATA GnbIommuEarlyInitTableCZ [] = {
//---------------------------------------------------------------------------
//Program D0F0x64_x0D[PciDev0Fn2RegEn] = 1h
  GNB_ENTRY_RMW (
    D0F0x64_x0D_TYPE,
    D0F0x64_x0D_ADDRESS,
    D0F0x64_x0D_PciDev0Fn2RegEn_MASK,
    (0x1 << D0F0x64_x0D_PciDev0Fn2RegEn_OFFSET)
    ),

// Set SB location for IOMMU
  GNB_ENTRY_COPY (
    D0F2xFC_x09_L1_TYPE,
    D0F2xFC_x09_L1_ADDRESS (L1_SEL_IOAGR),
    0,
    32,
    D0F0x64_x1F_TYPE,
    D0F0x64_x1F_ADDRESS,
    0,
    32
    ),
  GNB_ENTRY_COPY (
    D0F2xF4_x49_TYPE,
    D0F2xF4_x49_ADDRESS,
    0,
    32,
    D0F0x64_x1F_TYPE,
    D0F0x64_x1F_ADDRESS,
    0,
    32
    ),
  GNB_ENTRY_TERMINATE
};

GNB_TABLE ROMDATA GnbIommuEnvInitTableCZ [] = {

  GNB_ENTRY_RMW (
    D0F2x50_TYPE,
    D0F2x50_ADDRESS,
    D0F2x50_IommuHtAtsResv_MASK,
    (0 << D0F2x50_IommuHtAtsResv_OFFSET)
    ),
  GNB_ENTRY_RMW (
    D0F2x7C_TYPE,
    D0F2x7C_ADDRESS,
    D0F2x7C_MsiMultMessCapW_MASK,
    (2 << D0F2x7C_MsiMultMessCapW_OFFSET)
    ),
  GNB_ENTRY_RMW (
    D0F2x80_TYPE,
    D0F2x80_ADDRESS,
    D0F2x80_PrefSupW_MASK,
    (0 << D0F2x80_PrefSupW_OFFSET)
    ),
//---------------------------------------------------------------------------
//IOMMU L2 Initialization
  GNB_ENTRY_RMW (
    D0F2xF4_x10_TYPE,
    D0F2xF4_x10_ADDRESS,
    D0F2xF4_x10_DTCInvalidationSel_MASK,
    0x2 << D0F2xF4_x10_DTCInvalidationSel_OFFSET
    ),
  GNB_ENTRY_RMW (
    D0F2xF4_x14_TYPE,
    D0F2xF4_x14_ADDRESS,
    D0F2xF4_x14_ITCInvalidationSel_MASK,
    0x2 << D0F2xF4_x14_ITCInvalidationSel_OFFSET
    ),
  GNB_ENTRY_RMW (
    D0F2xF4_x18_TYPE,
    D0F2xF4_x18_ADDRESS,
    D0F2xF4_x18_PTCAInvalidationSel_MASK,
    0x2 << D0F2xF4_x18_PTCAInvalidationSel_OFFSET
    ),
  GNB_ENTRY_RMW (
    D0F2xF4_x50_TYPE,
    D0F2xF4_x50_ADDRESS,
    D0F2xF4_x50_PDCInvalidationSel_MASK,
    0x2 << D0F2xF4_x50_PDCInvalidationSel_OFFSET
    ),
  GNB_ENTRY_RMW (
    D0F2xF4_x80_TYPE,
    D0F2xF4_x80_ADDRESS,
    D0F2xF4_x80_ERRRuleLock0_MASK,
    0x1 << D0F2xF4_x80_ERRRuleLock0_OFFSET
    ),
  GNB_ENTRY_RMW (
    D0F2xF4_x30_TYPE,
    D0F2xF4_x30_ADDRESS,
    D0F2xF4_x30_ERRRuleLock1_MASK,
    0x1 << D0F2xF4_x30_ERRRuleLock1_OFFSET
    ),
  GNB_ENTRY_RMW (
    D0F2xF4_x34_TYPE,
    D0F2xF4_x34_ADDRESS,
    D0F2xF4_x34_L2aregHostPgsize_MASK | D0F2xF4_x34_L2aregGstPgsize_MASK,
    (0x2 << D0F2xF4_x34_L2aregHostPgsize_OFFSET) | (0x2 <<  D0F2xF4_x34_L2aregGstPgsize_OFFSET)
    ),
  GNB_ENTRY_RMW (
    D0F2xF4_x94_TYPE,
    D0F2xF4_x94_ADDRESS,
    D0F2xF4_x94_L2bregHostPgsize_MASK | D0F2xF4_x94_L2bregGstPgsize_MASK,
    (0x2 << D0F2xF4_x94_L2bregHostPgsize_OFFSET) | (0x2ull << D0F2xF4_x94_L2bregGstPgsize_OFFSET)
    ),
  GNB_ENTRY_RMW (
    D0F2xF4_x4C_TYPE,
    D0F2xF4_x4C_ADDRESS,
    D0F2xF4_x4C_GstPartialPtcCntrl_MASK,
    0x3 << D0F2xF4_x4C_GstPartialPtcCntrl_OFFSET
    ),
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_IGFX_DISABLED,
    D0F2xF4_x57_TYPE,
    D0F2xF4_x57_ADDRESS,
    D0F2xF4_x57_L1ImuIntGfxDis_MASK,
    (0x1 << D0F2xF4_x57_L1ImuIntGfxDis_OFFSET)
    ),
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_DGFX_DISABLED,
    D0F2xF4_x57_TYPE,
    D0F2xF4_x57_ADDRESS,
    D0F2xF4_x57_L1ImuPcieGfxDis_MASK,
    (0x1 << D0F2xF4_x57_L1ImuPcieGfxDis_OFFSET)
    ),
  GNB_ENTRY_RMW (
    D0F2xF4_x47_TYPE,
    D0F2xF4_x47_ADDRESS,
    D0F2xF4_x47_TwAtomicFilterEn_MASK | D0F2xF4_x47_TwNwEn_MASK | D0F2xF4_x47_AtsIgnoreIWDis_MASK,
    (0x1 << D0F2xF4_x47_TwAtomicFilterEn_OFFSET) | (1 << D0F2xF4_x47_TwNwEn_OFFSET) | (1 << D0F2xF4_x47_AtsIgnoreIWDis_OFFSET)
    ),
  GNB_ENTRY_RMW (
    D0F2xF4_x56_TYPE,
    D0F2xF4_x56_ADDRESS,
    D0F2xF4_x56_CPFlushOnInv_MASK | D0F2xF4_x56_CPFlushOnWait_MASK,
    (0x0 << D0F2xF4_x56_CPFlushOnInv_OFFSET) | (1 << D0F2xF4_x56_CPFlushOnWait_OFFSET)
    ),
  GNB_ENTRY_RMW (
    D0F2xF4_x53_TYPE,
    D0F2xF4_x53_ADDRESS,
    D0F2xF4_x53_L2bUpdateFilterBypass_MASK,
    (0x0 << D0F2xF4_x53_L2bUpdateFilterBypass_OFFSET)
    ),
  GNB_ENTRY_RMW (
    D0F2xF4_x22_TYPE,
    D0F2xF4_x22_ADDRESS,
    D0F2xF4_x22_L2aUpdateFilterBypass_MASK,
    (0x0 << D0F2xF4_x22_L2aUpdateFilterBypass_OFFSET)
    ),
  GNB_ENTRY_RMW (
    D0F2xF4_x54_TYPE,
    D0F2xF4_x54_ADDRESS,
    D0F2xF4_x54_TWPrefetchEn_MASK | D0F2xF4_x54_TWPrefetchRange_MASK,
    (0x1 << D0F2xF4_x54_TWPrefetchEn_OFFSET) | (0x7 << D0F2xF4_x54_TWPrefetchRange_OFFSET)
    ),
//IOMMU L1 Initialization
  GNB_ENTRY_RMW (
    D0F2xFC_x0C_L1_TYPE,
    D0F2xFC_x0C_L1_ADDRESS (L1_SEL_PPx40),
    D0F2xFC_x0C_L1_L1VirtOrderQueues_MASK,
    0x4 << D0F2xFC_x0C_L1_L1VirtOrderQueues_OFFSET
    ),
  GNB_ENTRY_RMW (
    D0F2xFC_x32_L1_TYPE,
    D0F2xFC_x32_L1_ADDRESS (L1_SEL_PPx40),
    D0F2xFC_x32_L1_AtsMultipleL1toL2En_MASK |
    D0F2xFC_x32_L1_AtsMultipleRespEn_MASK |
    D0F2xFC_x32_L1_TimeoutPulseExtEn_MASK |
    D0F2xFC_x32_L1_DmaBufCredits_MASK |
    D0F2xFC_x32_L1_DmaBufMaxNpCred_MASK |
    D0F2xFC_x32_L1_DmaNpHaltDis_MASK,
    (0x1 << D0F2xFC_x32_L1_AtsMultipleL1toL2En_OFFSET) |
    (0x1 << D0F2xFC_x32_L1_AtsMultipleRespEn_OFFSET) |
    (0x1 << D0F2xFC_x32_L1_TimeoutPulseExtEn_OFFSET) |
    (0x20 << D0F2xFC_x32_L1_DmaBufCredits_OFFSET) |
    (0x1F << D0F2xFC_x32_L1_DmaBufMaxNpCred_OFFSET)
    ),
  GNB_ENTRY_RMW (
    D0F2xFC_x07_L1_TYPE,
    D0F2xFC_x07_L1_ADDRESS (L1_SEL_PPx40),
    D0F2xFC_x07_L1_L1NwEn_MASK | D0F2xFC_x07_L1_AtsPhysPageOverlapDis_MASK |
    D0F2xFC_x07_L1_AtsSeqNumEn_MASK | D0F2xFC_x07_L1_SpecReqFilterEn_MASK | BIT6,
    (0x1 << D0F2xFC_x07_L1_L1NwEn_OFFSET) | (0x1 << D0F2xFC_x07_L1_AtsPhysPageOverlapDis_OFFSET) |
    (0x1 << D0F2xFC_x07_L1_AtsSeqNumEn_OFFSET) | (0x1 << D0F2xFC_x07_L1_SpecReqFilterEn_OFFSET) | BIT6
    ),
  GNB_ENTRY_RMW (
    D0F2xFC_x0C_L1_TYPE,
    D0F2xFC_x0C_L1_ADDRESS (L1_SEL_PPx41),
    D0F2xFC_x0C_L1_L1VirtOrderQueues_MASK,
    0x4 << D0F2xFC_x0C_L1_L1VirtOrderQueues_OFFSET
    ),
  GNB_ENTRY_RMW (
    D0F2xFC_x32_L1_TYPE,
    D0F2xFC_x32_L1_ADDRESS (L1_SEL_PPx41),
    D0F2xFC_x32_L1_AtsMultipleL1toL2En_MASK |
    D0F2xFC_x32_L1_AtsMultipleRespEn_MASK |
    D0F2xFC_x32_L1_TimeoutPulseExtEn_MASK |
    D0F2xFC_x32_L1_DmaBufCredits_MASK |
    D0F2xFC_x32_L1_DmaBufMaxNpCred_MASK |
    D0F2xFC_x32_L1_DmaNpHaltDis_MASK,
    (0x1 << D0F2xFC_x32_L1_AtsMultipleL1toL2En_OFFSET) |
    (0x1 << D0F2xFC_x32_L1_AtsMultipleRespEn_OFFSET) |
    (0x1 << D0F2xFC_x32_L1_TimeoutPulseExtEn_OFFSET) |
    (0x20 << D0F2xFC_x32_L1_DmaBufCredits_OFFSET) |
    (0x1F << D0F2xFC_x32_L1_DmaBufMaxNpCred_OFFSET)
    ),
  GNB_ENTRY_RMW (
    D0F2xFC_x07_L1_TYPE,
    D0F2xFC_x07_L1_ADDRESS (L1_SEL_PPx41),
    D0F2xFC_x07_L1_L1NwEn_MASK | D0F2xFC_x07_L1_AtsPhysPageOverlapDis_MASK |
    D0F2xFC_x07_L1_AtsSeqNumEn_MASK | D0F2xFC_x07_L1_SpecReqFilterEn_MASK | BIT6,
    (0x1 << D0F2xFC_x07_L1_L1NwEn_OFFSET) | (0x1 << D0F2xFC_x07_L1_AtsPhysPageOverlapDis_OFFSET) |
    (0x1 << D0F2xFC_x07_L1_AtsSeqNumEn_OFFSET) | (0x1 << D0F2xFC_x07_L1_SpecReqFilterEn_OFFSET) | BIT6
    ),
  GNB_ENTRY_RMW (
    D0F2xFC_x0C_L1_TYPE,
    D0F2xFC_x0C_L1_ADDRESS (L1_SEL_GBIF),
    D0F2xFC_x0C_L1_L1VirtOrderQueues_MASK,
    0x4 << D0F2xFC_x0C_L1_L1VirtOrderQueues_OFFSET
    ),
  GNB_ENTRY_RMW (
    D0F2xFC_x32_L1_TYPE,
    D0F2xFC_x32_L1_ADDRESS (L1_SEL_GBIF),
    D0F2xFC_x32_L1_AtsMultipleL1toL2En_MASK |
    D0F2xFC_x32_L1_AtsMultipleRespEn_MASK |
    D0F2xFC_x32_L1_TimeoutPulseExtEn_MASK |
    D0F2xFC_x32_L1_DmaBufCredits_MASK |
    D0F2xFC_x32_L1_DmaBufMaxNpCred_MASK |
    D0F2xFC_x32_L1_DmaNpHaltDis_MASK,
    (0x1 << D0F2xFC_x32_L1_AtsMultipleL1toL2En_OFFSET) |
    (0x1 << D0F2xFC_x32_L1_AtsMultipleRespEn_OFFSET) |
    (0x1 << D0F2xFC_x32_L1_TimeoutPulseExtEn_OFFSET) |
    (0x20 << D0F2xFC_x32_L1_DmaBufCredits_OFFSET) |
    (0x20 << D0F2xFC_x32_L1_DmaBufMaxNpCred_OFFSET) |
    (0x1 << D0F2xFC_x32_L1_DmaNpHaltDis_OFFSET)
    ),
 GNB_ENTRY_RMW (
    D0F2xFC_x07_L1_TYPE,
    D0F2xFC_x07_L1_ADDRESS (L1_SEL_GBIF),
    D0F2xFC_x07_L1_L1NwEn_MASK | D0F2xFC_x07_L1_AtsPhysPageOverlapDis_MASK |
    D0F2xFC_x07_L1_AtsSeqNumEn_MASK | D0F2xFC_x07_L1_SpecReqFilterEn_MASK | BIT6,
    (0x1 << D0F2xFC_x07_L1_L1NwEn_OFFSET) | (0x1 << D0F2xFC_x07_L1_AtsPhysPageOverlapDis_OFFSET) |
    (0x1 << D0F2xFC_x07_L1_AtsSeqNumEn_OFFSET) | (0x1 << D0F2xFC_x07_L1_SpecReqFilterEn_OFFSET) | BIT6
    ),
  GNB_ENTRY_RMW (
    D0F2xFC_x0C_L1_TYPE,
    D0F2xFC_x0C_L1_ADDRESS (L1_SEL_IOAGR),
    D0F2xFC_x0C_L1_L1VirtOrderQueues_MASK,
    0x4 << D0F2xFC_x0C_L1_L1VirtOrderQueues_OFFSET
    ),
 GNB_ENTRY_RMW (
    D0F2xFC_x07_L1_TYPE,
    D0F2xFC_x07_L1_ADDRESS (L1_SEL_IOAGR),
    D0F2xFC_x07_L1_L1NwEn_MASK | D0F2xFC_x07_L1_AtsPhysPageOverlapDis_MASK |
    D0F2xFC_x07_L1_AtsSeqNumEn_MASK | D0F2xFC_x07_L1_SpecReqFilterEn_MASK | BIT6,
    (0x1 << D0F2xFC_x07_L1_L1NwEn_OFFSET) | (0x1 << D0F2xFC_x07_L1_AtsPhysPageOverlapDis_OFFSET) |
    (0x1 << D0F2xFC_x07_L1_AtsSeqNumEn_OFFSET) | (0x1 << D0F2xFC_x07_L1_SpecReqFilterEn_OFFSET) | BIT6
    ),
//---------------------------------------------------------------------------
// IOMMU Initialization
// IOMMU L2 clock gating
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_IOMMU_L2_CLOCK_GATING,
    D0F2xF4_x33_TYPE,
    D0F2xF4_x33_ADDRESS,
    D0F2xF4_x33_CKGateL2ARegsDisable_MASK | D0F2xF4_x33_CKGateL2ADynamicDisable_MASK | D0F2xF4_x33_CKGateL2ACacheDisable_MASK,
    0x0
    ),
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_IOMMU_L2_CLOCK_GATING,
    D0F2xF4_x90_TYPE,
    D0F2xF4_x90_ADDRESS,
    D0F2xF4_x90_CKGateL2BRegsDisable_MASK | D0F2xF4_x90_CKGateL2BDynamicDisable_MASK | D0F2xF4_x90_CKGateL2BMiscDisable_MASK | D0F2xF4_x90_CKGateL2BCacheDisable_MASK,
    (0x1 << D0F2xF4_x90_CKGateL2BMiscDisable_OFFSET)
    ),
// IOMMU L1 clock gating
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_IOMMU_L1_CLOCK_GATING,
    D0F2xFC_x33_L1_TYPE,
    D0F2xFC_x33_L1_ADDRESS (L1_SEL_PPx40),
    D0F2xFC_x33_L1_L1DmaClkgateEn_MASK | D0F2xFC_x33_L1_L1CacheClkgateEn_MASK |
    D0F2xFC_x33_L1_L1CpslvClkgateEn_MASK | D0F2xFC_x33_L1_L1DmaInputClkgateEn_MASK |
    D0F2xFC_x33_L1_L1PerfClkgateEn_MASK | D0F2xFC_x33_L1_L1MemoryClkgateEn_MASK |
    D0F2xFC_x33_L1_L1RegClkgateEn_MASK | D0F2xFC_x33_L1_L1L2ClkgateEn_MASK |
    D0F2xFC_x33_L1_L1HostreqClkgateEn_MASK,
    (0x1 << D0F2xFC_x33_L1_L1DmaClkgateEn_OFFSET) | (0x1 << D0F2xFC_x33_L1_L1CacheClkgateEn_OFFSET) |
    (0x1 << D0F2xFC_x33_L1_L1CpslvClkgateEn_OFFSET) | (0x1 << D0F2xFC_x33_L1_L1DmaInputClkgateEn_OFFSET) |
    (0x1 << D0F2xFC_x33_L1_L1PerfClkgateEn_OFFSET) | (0x1 << D0F2xFC_x33_L1_L1MemoryClkgateEn_OFFSET) |
    (0x1 << D0F2xFC_x33_L1_L1RegClkgateEn_OFFSET) | (0x1 << D0F2xFC_x33_L1_L1L2ClkgateEn_OFFSET) |
    (0x1 << D0F2xFC_x33_L1_L1HostreqClkgateEn_OFFSET)
    ),
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_IOMMU_L1_CLOCK_GATING,
    D0F2xFC_x33_L1_TYPE,
    D0F2xFC_x33_L1_ADDRESS (L1_SEL_PPx41),
    D0F2xFC_x33_L1_L1DmaClkgateEn_MASK | D0F2xFC_x33_L1_L1CacheClkgateEn_MASK |
    D0F2xFC_x33_L1_L1CpslvClkgateEn_MASK | D0F2xFC_x33_L1_L1DmaInputClkgateEn_MASK |
    D0F2xFC_x33_L1_L1PerfClkgateEn_MASK | D0F2xFC_x33_L1_L1MemoryClkgateEn_MASK |
    D0F2xFC_x33_L1_L1RegClkgateEn_MASK | D0F2xFC_x33_L1_L1L2ClkgateEn_MASK |
    D0F2xFC_x33_L1_L1HostreqClkgateEn_MASK,
    (0x1 << D0F2xFC_x33_L1_L1DmaClkgateEn_OFFSET) | (0x1 << D0F2xFC_x33_L1_L1CacheClkgateEn_OFFSET) |
    (0x1 << D0F2xFC_x33_L1_L1CpslvClkgateEn_OFFSET) | (0x1 << D0F2xFC_x33_L1_L1DmaInputClkgateEn_OFFSET) |
    (0x1 << D0F2xFC_x33_L1_L1PerfClkgateEn_OFFSET) | (0x1 << D0F2xFC_x33_L1_L1MemoryClkgateEn_OFFSET) |
    (0x1 << D0F2xFC_x33_L1_L1RegClkgateEn_OFFSET) | (0x1 << D0F2xFC_x33_L1_L1L2ClkgateEn_OFFSET) |
    (0x1 << D0F2xFC_x33_L1_L1HostreqClkgateEn_OFFSET)
    ),
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_IOMMU_L1_CLOCK_GATING,
    D0F2xFC_x33_L1_TYPE,
    D0F2xFC_x33_L1_ADDRESS (L1_SEL_GBIF),
    D0F2xFC_x33_L1_L1DmaClkgateEn_MASK | D0F2xFC_x33_L1_L1CacheClkgateEn_MASK |
    D0F2xFC_x33_L1_L1CpslvClkgateEn_MASK | D0F2xFC_x33_L1_L1DmaInputClkgateEn_MASK |
    D0F2xFC_x33_L1_L1PerfClkgateEn_MASK | D0F2xFC_x33_L1_L1MemoryClkgateEn_MASK |
    D0F2xFC_x33_L1_L1RegClkgateEn_MASK | D0F2xFC_x33_L1_L1L2ClkgateEn_MASK |
    D0F2xFC_x33_L1_L1HostreqClkgateEn_MASK,
    (0x1 << D0F2xFC_x33_L1_L1DmaClkgateEn_OFFSET) | (0x1 << D0F2xFC_x33_L1_L1CacheClkgateEn_OFFSET) |
    (0x1 << D0F2xFC_x33_L1_L1CpslvClkgateEn_OFFSET) | (0x1 << D0F2xFC_x33_L1_L1DmaInputClkgateEn_OFFSET) |
    (0x1 << D0F2xFC_x33_L1_L1PerfClkgateEn_OFFSET) | (0x1 << D0F2xFC_x33_L1_L1MemoryClkgateEn_OFFSET) |
    (0x1 << D0F2xFC_x33_L1_L1RegClkgateEn_OFFSET) | (0x1 << D0F2xFC_x33_L1_L1L2ClkgateEn_OFFSET) |
    (0x1 << D0F2xFC_x33_L1_L1HostreqClkgateEn_OFFSET)
    ),
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_IOMMU_L1_CLOCK_GATING,
    D0F2xFC_x33_L1_TYPE,
    D0F2xFC_x33_L1_ADDRESS (L1_SEL_IOAGR),
    D0F2xFC_x33_L1_L1DmaClkgateEn_MASK | D0F2xFC_x33_L1_L1CacheClkgateEn_MASK |
    D0F2xFC_x33_L1_L1CpslvClkgateEn_MASK | D0F2xFC_x33_L1_L1DmaInputClkgateEn_MASK |
    D0F2xFC_x33_L1_L1PerfClkgateEn_MASK | D0F2xFC_x33_L1_L1MemoryClkgateEn_MASK |
    D0F2xFC_x33_L1_L1RegClkgateEn_MASK | D0F2xFC_x33_L1_L1L2ClkgateEn_MASK |
    D0F2xFC_x33_L1_L1HostreqClkgateEn_MASK,
    (0x1 << D0F2xFC_x33_L1_L1DmaClkgateEn_OFFSET) | (0x1 << D0F2xFC_x33_L1_L1CacheClkgateEn_OFFSET) |
    (0x1 << D0F2xFC_x33_L1_L1CpslvClkgateEn_OFFSET) | (0x1 << D0F2xFC_x33_L1_L1DmaInputClkgateEn_OFFSET) |
    (0x1 << D0F2xFC_x33_L1_L1PerfClkgateEn_OFFSET) | (0x1 << D0F2xFC_x33_L1_L1MemoryClkgateEn_OFFSET) |
    (0x1 << D0F2xFC_x33_L1_L1RegClkgateEn_OFFSET) | (0x1 << D0F2xFC_x33_L1_L1L2ClkgateEn_OFFSET) |
    (0x1 << D0F2xFC_x33_L1_L1HostreqClkgateEn_OFFSET)
    ),
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_IOMMU_L1_SST_CLOCK_GATING,
    D0F2xFC_x3D_L1_TYPE,
    D0F2xFC_x3D_L1_ADDRESS (L1_SEL_IOAGR),
    BIT14,
    BIT14
    ),
//---------------------------------------------------------------------------
// Configure IOMMU Power Island
// Hide IOMMU function if disabled
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_IOMMU_DISABLED,
    D0F2xF4_x3B_TYPE,
    D0F2xF4_x3B_ADDRESS,
    D0F2xF4_x3B_FSM_ADDR_MASK,
    (0xFF << D0F2xF4_x3B_FSM_ADDR_OFFSET)
    ),
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_IOMMU_DISABLED,
    D0F2xF4_x3B_TYPE,
    D0F2xF4_x3B_ADDRESS,
    D0F2xF4_x3B_Power_Down_MASK,
    (0x1 << D0F2xF4_x3B_Power_Down_OFFSET)
    ),
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_IOMMU_DISABLED,
    D0F2xF4_x3B_TYPE,
    D0F2xF4_x3B_ADDRESS,
    D0F2xF4_x3B_Power_Down_MASK,
    (0x0 << D0F2xF4_x3B_Power_Down_OFFSET)
    ),
  GNB_ENTRY_PROPERTY_RMW (
    TABLE_PROPERTY_IOMMU_DISABLED,
    D0F0x64_x0D_TYPE,
    D0F0x64_x0D_ADDRESS,
    D0F0x64_x0D_PciDev0Fn2RegEn_MASK,
    0x0
    ),
  GNB_ENTRY_TERMINATE
};

