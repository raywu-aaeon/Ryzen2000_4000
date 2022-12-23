/*****************************************************************************
 *
 * Copyright 2016 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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

#ifndef _AMD_RAS_REGISTERS_ZP_H_
#define _AMD_RAS_REGISTERS_ZP_H_

#include "AmdRas.h"

#undef BIT0
#undef BIT1
#undef BIT2
#undef BIT3
#undef BIT4
#undef BIT5
#undef BIT6
#undef BIT7
#undef BIT8
#undef BIT9
#undef BIT10
#undef BIT10
#undef BIT11
#undef BIT12
#undef BIT13
#undef BIT14
#undef BIT15
#undef BIT16
#undef BIT17
#undef BIT18
#undef BIT19
#undef BIT20
#undef BIT21
#undef BIT22
#undef BIT23
#undef BIT24
#undef BIT25
#undef BIT26
#undef BIT27
#undef BIT28
#undef BIT29
#undef BIT30
#undef BIT31
#undef BIT32
#undef BIT33
#undef BIT34
#undef BIT35
#undef BIT36
#undef BIT37
#undef BIT38
#undef BIT39
#undef BIT40
#undef BIT41
#undef BIT42
#undef BIT43
#undef BIT44
#undef BIT45
#undef BIT46
#undef BIT47
#undef BIT48
#undef BIT49
#undef BIT40
#undef BIT41
#undef BIT42
#undef BIT43
#undef BIT44
#undef BIT45
#undef BIT46
#undef BIT47
#undef BIT48
#undef BIT49
#undef BIT50
#undef BIT51
#undef BIT52
#undef BIT53
#undef BIT54
#undef BIT55
#undef BIT56
#undef BIT57
#undef BIT58
#undef BIT59
#undef BIT60
#undef BIT61
#undef BIT62
#undef BIT63

#define BIT0        (0x0000000000000001ull)
#define BIT1        (0x0000000000000002ull)
#define BIT2        (0x0000000000000004ull)
#define BIT3        (0x0000000000000008ull)
#define BIT4        (0x0000000000000010ull)
#define BIT5        (0x0000000000000020ull)
#define BIT6        (0x0000000000000040ull)
#define BIT7        (0x0000000000000080ull)
#define BIT8        (0x0000000000000100ull)
#define BIT9        (0x0000000000000200ull)
#define BIT10       (0x0000000000000400ull)
#define BIT11       (0x0000000000000800ull)
#define BIT12       (0x0000000000001000ull)
#define BIT13       (0x0000000000002000ull)
#define BIT14       (0x0000000000004000ull)
#define BIT15       (0x0000000000008000ull)
#define BIT16       (0x0000000000010000ull)
#define BIT17       (0x0000000000020000ull)
#define BIT18       (0x0000000000040000ull)
#define BIT19       (0x0000000000080000ull)
#define BIT20       (0x0000000000100000ull)
#define BIT21       (0x0000000000200000ull)
#define BIT22       (0x0000000000400000ull)
#define BIT23       (0x0000000000800000ull)
#define BIT24       (0x0000000001000000ull)
#define BIT25       (0x0000000002000000ull)
#define BIT26       (0x0000000004000000ull)
#define BIT27       (0x0000000008000000ull)
#define BIT28       (0x0000000010000000ull)
#define BIT29       (0x0000000020000000ull)
#define BIT30       (0x0000000040000000ull)
#define BIT31       (0x0000000080000000ull)
#define BIT32       (0x0000000100000000ull)
#define BIT33       (0x0000000200000000ull)
#define BIT34       (0x0000000400000000ull)
#define BIT35       (0x0000000800000000ull)
#define BIT36       (0x0000001000000000ull)
#define BIT37       (0x0000002000000000ull)
#define BIT38       (0x0000004000000000ull)
#define BIT39       (0x0000008000000000ull)
#define BIT40       (0x0000010000000000ull)
#define BIT41       (0x0000020000000000ull)
#define BIT42       (0x0000040000000000ull)
#define BIT43       (0x0000080000000000ull)
#define BIT44       (0x0000100000000000ull)
#define BIT45       (0x0000200000000000ull)
#define BIT46       (0x0000400000000000ull)
#define BIT47       (0x0000800000000000ull)
#define BIT48       (0x0001000000000000ull)
#define BIT49       (0x0002000000000000ull)
#define BIT50       (0x0004000000000000ull)
#define BIT51       (0x0008000000000000ull)
#define BIT52       (0x0010000000000000ull)
#define BIT53       (0x0020000000000000ull)
#define BIT54       (0x0040000000000000ull)
#define BIT55       (0x0080000000000000ull)
#define BIT56       (0x0100000000000000ull)
#define BIT57       (0x0200000000000000ull)
#define BIT58       (0x0400000000000000ull)
#define BIT59       (0x0800000000000000ull)
#define BIT60       (0x1000000000000000ull)
#define BIT61       (0x2000000000000000ull)
#define BIT62       (0x4000000000000000ull)
#define BIT63       (0x8000000000000000ull)

///MSR
#define MSR_APIC_BAR                   (0x0000001BUL)
#define LAPIC_BASE_ADDR_MASK           (0x0000FFFFFFFFF000ULL)

#define APIC_ID_REG                    (0x20)
#define APIC20_ApicId_Offset           (24)

#define MSR_SYSENTER_EIP               (0x00000176UL)
#define MSR_MCG_CAP                    (0x00000179UL)
#define MSR_MCG_STAT                   (0x0000017AUL)
  #define MSR_MCG_EIPV                   BIT1
#define MSR_HWCR                       (0xC0010015UL)
  #define MCA_STS_WREN_BIT               BIT18
#define MSR_MCEXCEPREDIR               (0xC0010022UL)
#define MSR_SMITRIGIOCYCLE             (0xC0010056UL)
#define MSR_MMIO_CFG_BASE              (0xC0010058UL)
#define MSR_SMM_BASE                   (0xC0010111UL)
#define MSR_LOCAL_SMI_STATUS           (0xC001011AUL)
#define MSR_PFEH_CFG                   (0xC0010120UL)
  #define GENERATE_DEFERREDLVT_ON_EXIT      BIT1
  #define GENERATE_THRESHOLDLVT_ON_EXIT     BIT2
  #define GENERATE_MCE_ON_EXIT              BIT3
  #define SMI_EXITTYPE_MASK            (GENERATE_THRESHOLDLVT_ON_EXIT + GENERATE_DEFERREDLVT_ON_EXIT +GENERATE_MCE_ON_EXIT)

#define MSR_PFEH_CLOAK_CFG             (0xC0010121UL)
#define MSR_PFEH_DEF_INT_MASK          (0xC0010122UL)

#define MCA_LEGACY_BASE                (0x00000400UL)
#define MCA_LEGACY_MAX_BANK            (32)
#define MCA_LEGACY_REG_PER_BANK        (1<<2)
#define MCA_LEGACY_TOP_ADDR            (MCA_LEGACY_BASE + (MCA_LEGACY_MAX_BANK * MCA_LEGACY_REG_PER_BANK))
#define MCA_REG_OFFSET_MASK            (0x00000003)

#define MCA_CTL_MASK_BASE              (0xC0010400UL)
#define MCA_EXTENSION_BASE             (0xC0002000UL)
#define SMCA_REG_PER_BANK              (1<<4)

#define SMCA_REG_OFFSET_MASK           (0x0000000F)
#define MCA_CTL_OFFSET                 (0x00)
#define MCA_STATUS_OFFSET              (0x01)
#define MCA_ADDR_OFFSET                (0x02)
#define MCA_MISC0_OFFSET               (0x03)
#define MCA_CONFIG_OFFSET              (0x04)
#define MCA_IPID_OFFSET                (0x05)
#define MCA_SYND_OFFSET                (0x06)
#define MCA_DESTAT_OFFSET              (0x08)
#define MCA_DEADDR_OFFSET              (0x09)
#define MCA_MISC1_OFFSET               (0x0A)

/// RAS MCA Bank enumerate
typedef enum _AMD_MCA_BANK_NUM {
//CORE MCA Banks, access through each thread.
  MCA_LS_BANK = 0,        ///< / 0  = MCA LS
  MCA_IF_BANK,            ///< / 1  = MCA IF
  MCA_L2_BANK,            ///< / 2  = MCA L2
  MCA_DE_BANK,            ///< / 3  = MCA DE
  MCA_EMPTY0_BANK,        ///< / 4  = EMPTY BANK
  MCA_EX_BANK,            ///< / 5  = MCA EX
  MCA_FP_BANK,            ///< / 6  = MCA FP

//NON-CORE MCA banks, access from logic core 0 from each Die

//MCA L3 CCXx SLIDEx Bank number define
  MCA_L3_C0_S0_BANK,      ///< / 7  = MCA L3 CCX 0 SLIDE 0
  MCA_L3_C0_S1_BANK,      ///< / 8  = MCA L3 CCX 0 SLIDE 1
  MCA_L3_C0_S2_BANK,      ///< / 9  = MCA L3 CCX 0 SLIDE 2
  MCA_L3_C0_S3_BANK,      ///< / 10  = MCA L3 CCX 0 SLIDE 3
  MCA_L3_C1_S0_BANK,      ///< / 11  = MCA L3 CCX 1 SLIDE 0
  MCA_L3_C1_S1_BANK,      ///< / 12  = MCA L3 CCX 1 SLIDE 1
  MCA_L3_C1_S2_BANK,      ///< / 13  = MCA L3 CCX 1 SLIDE 2
  MCA_L3_C1_S3_BANK,      ///< / 14  = MCA L3 CCX 1 SLIDE 3

  MCA_UMC0_BANK,          ///< / 15  = MCA UMC CHANNEL 0
  MCA_UMC1_BANK,          ///< / 16  = MCA UMC CHANNEL 1
  MCA_SMU_BANK,           ///< / 17  = MCA 
  MCA_PSP_BANK,           ///< / 18  = MCA 
  MCA_FUSE_BANK,          ///< / 19  = MCA 
  MCA_CS0_BANK,           ///< / 20  = MCA 
  MCA_CS1_BANK,           ///< / 21  = MCA 
  MCA_PIE_BANK            ///< / 22  = MCA 
} AMD_MCA_BANK_NUM;

//MCA Hardware ID
#define MCA_CPU_CORE_ID                    (0x0B0)
  #define LS_MCA_TYPE                      (0x0000)
  #define IF_MCA_TYPE                      (0x0001)
  #define L2_MCA_TYPE                      (0x0002)
  #define DE_MCA_TYPE                      (0x0003)
  #define EX_MCA_TYPE                      (0x0005)
  #define FP_MCA_TYPE                      (0x0006)
  #define L3_MCA_TYPE                      (0x0007)

#define MCA_DATA_FABRIC_ID                 (0x02E)
  #define CS_MCA_TYPE                      (0x0000)
  #define PIE_MCA_TYPE                     (0x0001)

#define MCA_UMC_ID                         (0x096)
  #define UMC_MCA_TYPE                     (0x0000)

#define MCA_PARAMETER_BLOCK_ID             (0x005)
  #define PB_MCA_TYPE                      (0x0000)

#define MCA_PSP_ID                         (0x0FF)
  #define PSP_MCA_TYPE                     (0x0000)

#define MCA_SMU_ID                         (0x001)
  #define SMU_MCA_TYPE                     (0x0000)

//This is old x86 MCA address
#define LMCA_ADDR_REG                  (0x00)
#define LMCA_STATUS_REG                (0x01)

#define SMM_SAVE_STATE_OFFSET          (0xFE00)

#define DEVICE_WIDTH_x4                (4)
#define DEVICE_WIDTH_x8                (8)
#define ECC_SYMBOL_SIZE_x4             (0)
#define ECC_SYMBOL_SIZE_x8             (1)
#define ECC_BIT_INTERLEAVING_DISABLED  (0)
#define ECC_BIT_INTERLEAVING_ENABLED   (1)

/// ACPI define
/// ACPI 6.0
#define GENERIC_ERROR_REVISION     (0x0201)

///NBIO
#define IOHC_NB_SMN_INDEX_2_BIOS  (0x00B8)
#define IOHC_NB_SMN_DATA_2_BIOS   (0x00BC)

#define RAS_PARITY_CONTROL_0                (0x13B20000)
#define RAS_PARITY_CONTROL_1                (0x13B20004)
#define RAS_GLOBAL_STATUS_LO                (0x13B20020)
#define RAS_GLOBAL_STATUS_HI                (0x13B20024)
#define RAS_GLOBAL_STATUS_NBIO_ERR_MASK     (0x0000000F)
#define RAS_GLOBAL_STATUS_LO_MASK           (0x000001FF)
#define RAS_GLOBAL_STATUS_HI_MASK           (0x0003FFFF)

#define PARITY_ERROR_STATUS_UNCORR_GRP      (0x13B20028)
#define PARITY_ERROR_STATUS_CORR_GRP        (0x13B20068)
#define PARITY_COUNTER_CORR_GRP             (0x13B200B0)
#define PARITY_ERROR_STATUS_UCP_GRP         (0x13B200F8)
#define PARITY_COUNTER_UCP_GRP              (0x13B20128)
#define PCIE_PORT_ACTION_CONTROL_BASE       (0x13B2017C)
#define PCIE_ACTION_CONTROL_OFFSET          (0x20)
#define NBIF0_ACTION_CONTROL_BASE           (0x13B2037C)
#define NBIF1_ACTION_CONTROL_BASE           (0x13B2039C)

#define NBIF_GDC_RAS_LEAF0_CTRL             (0x0141F800)
#define NBIF_BIF_RAS_LEAF0_CTRL             (0x10139000)


#define MAX_UNCORR_GRP_NUM                  (16)
#define MAX_CORR_GRP_NUM                    (18)
#define MAX_UCP_GRP_NUM                     (12)

///NBIO
typedef union {
  /// Bitfields of IOHCRAS Parity Control 0 Register
  struct {
    UINT32 ParityCorrThreshold:16;          ///< The number of ucp parity errors logged before an action is triggered.
    UINT32 ParityUCPThreshold:16;           ///< The number of correctable parity errors logged before an action is triggered.
  } Fields;
  UINT32  Value;
} PARITY_CONTROL_0_REG;

///NBIO IOHCRAS Parity Control 1 Register
typedef union {
  /// Bitfields of IOHCRAS Parity Control 1 Register
  struct {
    UINT32 ParityErrGenGroupSel:8;          ///< Controls the parity error group that is the target of error injection or masking.
    UINT32 ParityErrGenGroupTypeSel:1;      ///< 0- Uncorrectable Group Type, 1- - Correctable Group Type.
    UINT32 :2;                              ///< Reserved.
    UINT32 ParityErrGenIdSel:5;             ///< Selects a structure within the target parity group for error injection or masking.
    UINT32 ParityErrGenCmd:4;               ///< 0000 - Reserved
                                            ///< 0001 - Error Injection on Write Side
                                            ///< 0010 - Error Injection on Read Side
                                            ///< 0011 - Reserved
                                            ///< 0100 - Disable Error Reporting
                                            ///< 0101 - Enable Error Reporting
                                            ///< 0110 - Reserved
                                            ///< 0111-1111 - Reserved
                                            ///< Encoding for ECC Parity Wrappers:
                                            ///< 0000 - Disable ECC Error Detection and Correction
                                            ///< 0001 - Enable ECC Error Detection and Correction
                                            ///< 0010 - SEC Error Injection
                                            ///< 0011 - Disable SEC Error Reporting
                                            ///< 0100 - Enable SEC Error Reporting
                                            ///< 0101 - DED Error Injection
                                            ///< 0110 - Disable DED Error Reporting
                                            ///< 0111 - Enable DED Error Reporting
                                            ///< 1000 - Disable Conversion of DED Errors to Poisoned Data
                                            ///< 1001 - Enable Conversion of DED Errors to Poisoned Data
                                            ///< 1010 - UCP Error Injection
                                            ///< 1011 - Disable UCP Error Reporting
                                            ///< 1100 - Enable UCP Error Reporting
    UINT32 :10;                             ///< Reserved.
    UINT32 ParityErrGenTrigger:1;           ///< Writing this bit to 1 triggers the command defined by the other ParityErrGen* fields in this register.
    UINT32 ParityErrGenInjectAllow:1;       ///< Software must poll this bit and make sure this bit is asserted before updating the rest of the fields in this register.
  } Fields;
  UINT32  Value;
} PARITY_CONTROL_1_REG;

typedef union {
  /// Bitfields of IOHCRAS PCIE0/1PortA/H*_ACTION_CONTROL Register
  struct {
    UINT32 ApmlErrEn:1;                     ///< 1 causes an interrupt to SMU/MP1 to be triggered when the associated error is logged.
    UINT32 IntrGenSel:2;                    ///< A non-zero value causes an interrupt to be sent to the CPU complex when the associated error is logged.
    UINT32 LinkDisEn:1;                     ///< 1 causes PCIe links to be disabled when the associated error is logged.
    UINT32 SyncFloodEn:1;                   ///< 1 causes an SDP ErrEvent to be triggered when the associated error is logged.
    UINT32 :27;                             ///< Reserved.
  } Fields;
  UINT32  Value;
} ERR_ACT_CTRL_REG;

typedef union {
  /// Bitfields of NBIFRAS NBIF_RAS_LEAFx_CTRL, NBIFGDCRAS GDC_RAS_LEAFx_CTRL Register
  struct {
    UINT32 PoisonDetEn:1;                  ///< Control bit for port poison data detection.
    UINT32 PoisonErrEventEn:1;             ///< Control for sending error event when dectecting poison data.
    UINT32 PoisonStallEn:1;                ///< Control for stalling its egress port when dectecting poison data.
    UINT32 :1;                             ///< Reserved
    UINT32 ParityDetEn:1;                  ///< Control for port parity error detection.
    UINT32 ParityErrEventEn:1;             ///< Control for sending error event when dectecting parity error.
    UINT32 ParityStallEn:1;                ///< Control for stalling its egress port when dectecting parity error.
    UINT32 :9;                             ///< Reserved
    UINT32 ErrEventRecv:1;                 ///< Status for SDP error event receive recording.
    UINT32 LinkDisRecv:1;                  ///< Status for Link disable receive recording.
    UINT32 PoisonErrDet:1;                 ///< Status for self-detected poison data recording.
    UINT32 ParityErrDet:1;                 ///< Status for self-detected parity error recording.
    UINT32 ErrEventSent:1;                 ///< Status for SDP error event sent recording.
    UINT32 EgressStalled:1;                ///< Status for egress stall recordin.
    UINT32 :10;                            ///< Reserved
  } Fields;
  UINT32  Value;
}RAS_LEAF_CTRL_REG;

typedef union {
  /// Bitfields of NBIFRAS NBIF_RAS_LEAFx_CTRL, NBIFGDCRAS GDC_RAS_LEAFx_CTRL Register
  struct {
    UINT32 Pcie0PortA:1;                    ///< The status of errors from PCIE0 PortA
    UINT32 Pcie0PortB:1;                    ///< The status of errors from PCIE0 PortB
    UINT32 Pcie0PortC:1;                    ///< The status of errors from PCIE0 PortC
    UINT32 Pcie0PortD:1;                    ///< The status of errors from PCIE0 PortD
    UINT32 Pcie0PortE:1;                    ///< The status of errors from PCIE0 PortE
    UINT32 Pcie0PortF:1;                    ///< The status of errors from PCIE0 PortF
    UINT32 Pcie0PortG:1;                    ///< The status of errors from PCIE0 PortG
    UINT32 Pcie0PortH:1;                    ///< The status of errors from PCIE0 PortH
    UINT32 Pcie1PortA:1;                    ///< The status of errors from PCIE1 PortA
    UINT32 Pcie1PortB:1;                    ///< The status of errors from PCIE1 PortB
    UINT32 Pcie1PortC:1;                    ///< The status of errors from PCIE1 PortC
    UINT32 Pcie1PortD:1;                    ///< The status of errors from PCIE1 PortD
    UINT32 Pcie1PortE:1;                    ///< The status of errors from PCIE1 PortE
    UINT32 Pcie1PortF:1;                    ///< The status of errors from PCIE1 PortF
    UINT32 Pcie1PortG:1;                    ///< The status of errors from PCIE1 PortG
    UINT32 Pcie1PortH:1;                    ///< The status of errors from PCIE1 PortH
    UINT32 Nbif0PortA:1;                    ///< The status of errors from NBIF0 PortA.
    UINT32 Nbif1PortA:1;                    ///< The status of errors from NBIF1 PortA.
    UINT32 :14;                             ///< Reserved
  } Fields;
  UINT32  Value;
}RAS_GLOBAL_STS_HI_REG;

///FCH
#define ACPI_MMIO_BASE                 (0xFED80000ul)
#define PMIO_BASE                      (0x300)          // DWORD
#define FCH_PMIOA_REG6A                (0x6A)           // AcpiSmiCmd

#define MAX_DIE_SUPPORT                (8)
#define MAX_PCIE_PORT_SUPPORT          (16)             //Max PCI-E port support per Die.
#define AMD_VENDOR_ID                  (0x1022)

// PMIO BreakEvent Register for SMN errors
#define PMIO_SMN_BREAK_EVENT                (0x02D01380)

#define SMN_CATEGORY_SMN_PARITY_TIMEOUT_PSP_SMU_PARITY_ECC (1 << 0)
#define SMN_CATEGORY_PSP_PARITY_ECC         (1 << 2)
#define SMN_CATEGORY_SMN_TIMEOUT_SMU        (1 << 3)
#define SMN_CATEGORY_SMN_LINK_PACKET_CRC_WITH_RETRY (1 << 4)
#define SMN_CATEGORY_MASK                   (SMN_CATEGORY_SMN_PARITY_TIMEOUT_PSP_SMU_PARITY_ECC | SMN_CATEGORY_PSP_PARITY_ECC | SMN_CATEGORY_SMN_TIMEOUT_SMU | SMN_CATEGORY_SMN_LINK_PACKET_CRC_WITH_RETRY)

///SATA
#define FCH_SMN_SATA_CONTROL_BAR5           (0x03101000ul)
#define FCH_SMN_SATA_CONTROL_SLOR           (0x03101800ul)
#define FCH_SATA_SLOR_REG88                 (0x0088)
#define FCH_SATA_BAR5_REG110                (0x0110)
#define FCH_SATA_BAR5_REG130                (0x0130)

#define TAISHAN_SATA_PORT_NUM               (8)

#define SATA_PAR_ERR_CNXT_STS               (BIT10)
#define SATA_PAR_ERR_H2D_STS                (BIT9)
#define SATA_PAR_ERR_D2H2D_STS              (BIT8)
#define SATA_PAR_ERR_STS                    (SATA_PAR_ERR_CNXT_STS + SATA_PAR_ERR_H2D_STS + SATA_PAR_ERR_D2H2D_STS)

///UMC
#define UMC0_CH_REG_BASE                    (0x00050000)
#define UMC1_CH_REG_BASE                    (0x00150000)
#define UMC_ECC_CTRL                        (0x0000014C)
#define UMC_MISC_CFG                        (0x000001E0)
#define UMC_ECC_ERR_INJ_CTRL                (0x00000D88)
  #define ECC_ERR_ADDR_EN                   (BIT2)
#define UMC_ECC_ERR_INJ                     (0x00000DB0)

///DF
#define DF_CFGADDRESSCNTL_FUNC         (0x00)
#define DF_CFGADDRESSCNTL_OFFSET       (0x84)

#define DF_DFF6_REG_BASE                    (0x0001D800)
#define DRAM_SCRUBBER_ERRORADDR_LO          (0x00000040)
  #define ERR_INJ_EN                        (BIT0)
#define DRAM_SCRUBBER_ERRORADDR_HI          (0x00000044)
#define DRAM_SCRUBBER_BASEADDR_REG          (0x00000048)
#define DRAM_SCRUBBER_LIMIT_ADDR            (0x0000004C)  //DramScrubLimitAddr
#define DRAM_SCRUBBER_ADDR_LO               (0x00000050)  //DramScrubAddrLo
#define DRAM_SCRUBBER_ADDR_HI               (0x00000054)  //DramScrubAddrHi

#define DRAM_SCRUBBER_ERROR_ADDRESS_LOW_MASK (0xFFFFFFFFFFFFFFC0)

#pragma pack (push, 1)

typedef struct {
  IN       UINT8   TOTAL_NUM_RANKS_PER_UMCCH_ADDR_TRANS[16];
  IN       UINT8   RANK_ENABLE_PER_UMCCH_ADDR_TRANS[16];
  IN       UINT32  ADDRHASHBANK0[16];
  IN       UINT32  ADDRHASHBANK1[16];
  IN       UINT32  ADDRHASHBANK2[16];
  IN       UINT32  ADDRHASHBANK3[16];
  IN       UINT32  ADDRHASHBANK4[16];
  IN       UINT32  ADDRHASHBANKPC[16];
  IN       UINT32  ADDRHASHBANKPC2[16];
  IN       UINT32  ADDRHASHNORMADDR[16][2];
  IN       UINT32  CSBASE[16][4];     
  IN       UINT32  CSBASESEC[16][4];     
  IN       UINT32  CSMASK[16][2];
  IN       UINT32  CSMASKSEC[16][2];
  IN       UINT32  CONFIGDIMM[16][4]; //[25:24] is the secondary CSEnable. [29:26] can be rmselsec
  IN       UINT32  BANKSELDIMM[16][2];
  IN       UINT32  ROWSELDIMM[16][2];
  IN       UINT32  COL0SELDIMM[16][2];
  IN       UINT32  COL1SELDIMM[16][2];
  IN       UINT32  RMSELDIMM[16][2];
  IN       UINT32  RMSELDIMMSEC[16][2];
  IN       UINT32  CSSIZEDIMM[16][8];
  IN       UINT32  CHANSIZEDIMM[16];
  IN       UINT8   CSPOSHI[16][4];
  IN       UINT8   CSPOSLO[16][4];
  IN       UINT32  CTRLREG[16][4];
  IN       BOOLEAN addrhash[6];
} ADDR_DATA;

#pragma pack (pop)

///
/// Platform RAS configuration data structure
///
typedef struct {
    BOOLEAN       PFEHEnable;
    UINT16        SwSmiCmdPortAddr;
    UINT8         MceSwSmiData;
    BOOLEAN       McaErrThreshEn;
    UINT16        McaErrThreshCount;
    BOOLEAN       NbioCorrectedErrThreshEn;
    UINT16        NbioCorrectedErrThreshCount;
    BOOLEAN       NbioDeferredErrThreshEn;
    UINT16        NbioDeferredErrThreshCount;
    UINTN         TotalNumberOfProcessors;
    CPU_INFO      *RasCpuMap;
    ADDR_DATA     *AddrData;
} AMD_RAS_POLICY;

#endif  // _AMD_RAS_REGISTERS_ZP_H_

