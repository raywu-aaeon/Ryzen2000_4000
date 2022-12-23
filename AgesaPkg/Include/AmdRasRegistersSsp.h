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

#ifndef _AMD_RAS_REGISTERS_SSP_H_
#define _AMD_RAS_REGISTERS_SSP_H_

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

///Platform
#define MAX_SOCKET_SUPPORT              (2)

///MSR
#define MSR_APIC_BAR                    (0x0000001BUL)
#define LAPIC_BASE_ADDR_MASK            (0x0000FFFFFFFFF000ULL)

#define APIC_ID_REG                     (0x20)
#define APIC20_ApicId_Offset            (24)

#define MSR_SYSENTER_EIP                (0x00000176UL)
#define MSR_MCG_CAP                     (0x00000179UL)
#define MSR_MCG_STAT                    (0x0000017AUL)
  #define MSR_MCG_EIPV                  BIT1
#define MSR_HWCR                        (0xC0010015UL)
  #define MCA_STS_WREN_BIT              BIT18
#define MSR_MCEXCEPREDIR                (0xC0010022UL)
#define MSR_SMITRIGIOCYCLE              (0xC0010056UL)
#define MSR_MMIO_CFG_BASE               (0xC0010058UL)
#define MSR_PSTATE_0                    (0xC0010064UL)
#define MSR_SMM_BASE                    (0xC0010111UL)
#define MSR_LOCAL_SMI_STATUS            (0xC001011AUL)
#define MSR_PFEH_CFG                    (0xC0010120UL)
  #define GENERATE_DEFERREDLVT_ON_EXIT      BIT1
  #define GENERATE_THRESHOLDLVT_ON_EXIT     BIT2
  #define GENERATE_MCE_ON_EXIT              BIT3
  #define SMI_EXITTYPE_MASK             (GENERATE_THRESHOLDLVT_ON_EXIT + GENERATE_DEFERREDLVT_ON_EXIT +GENERATE_MCE_ON_EXIT)

#define MSR_PFEH_CLOAK_CFG              (0xC0010121UL)
#define MSR_PFEH_DEF_INT_MASK           (0xC0010122UL)

#define MCA_LEGACY_BASE                 (0x00000400UL)
#define MCA_LEGACY_MAX_BANK             (32)
#define MCA_LEGACY_REG_PER_BANK         (1<<2)
#define MCA_LEGACY_TOP_ADDR             (MCA_LEGACY_BASE + (MCA_LEGACY_MAX_BANK * MCA_LEGACY_REG_PER_BANK))
#define MCA_REG_OFFSET_MASK             (0x00000003)

#define MCA_CTL_MASK_BASE               (0xC0010400UL)
#define MCA_EXTENSION_BASE              (0xC0002000UL)
#define SMCA_REG_PER_BANK               (1<<4)

#define SMCA_REG_OFFSET_MASK            (0x0000000F)
#define MCA_CTL_OFFSET                  (0x00)
#define MCA_STATUS_OFFSET               (0x01)
#define MCA_ADDR_OFFSET                 (0x02)
#define MCA_MISC0_OFFSET                (0x03)
#define MCA_CONFIG_OFFSET               (0x04)
#define MCA_IPID_OFFSET                 (0x05)
#define MCA_SYND_OFFSET                 (0x06)
#define MCA_DESTAT_OFFSET               (0x08)
#define MCA_DEADDR_OFFSET               (0x09)
#define MCA_MISC1_OFFSET                (0x0A)

#define MCA_EMPTY0_BANK                 (4)

//MCA Hardware ID
#define MCA_CPU_CORE_ID                 (0x0B0)
  #define LS_MCA_TYPE                   (0x0000)
  #define IF_MCA_TYPE                   (0x0001)
  #define L2_MCA_TYPE                   (0x0002)
  #define DE_MCA_TYPE                   (0x0003)
  #define EX_MCA_TYPE                   (0x0005)
  #define FP_MCA_TYPE                   (0x0006)
  #define L3_MCA_TYPE                   (0x0007)

#define MCA_DATA_FABRIC_ID              (0x02E)
  #define CS_MCA_TYPE                   (0x0002)
  #define PIE_MCA_TYPE                  (0x0001)

#define MCA_UMC_ID                      (0x096)
  #define UMC_MCA_TYPE                  (0x0000)
  #define UMC0_MCA_INS_ID               (0x050F0)
  #define UMC1_MCA_INS_ID               (0x150F0)
  #define UMC2_MCA_INS_ID               (0x250F0)
  #define UMC3_MCA_INS_ID               (0x350F0)
  #define UMC4_MCA_INS_ID               (0x450F0)
  #define UMC5_MCA_INS_ID               (0x550F0)
  #define UMC6_MCA_INS_ID               (0x650F0)
  #define UMC7_MCA_INS_ID               (0x750F0)

#define MCA_PARAMETER_BLOCK_ID          (0x005)
  #define PB_MCA_TYPE                   (0x0001)
  #define PB0_MCA_INS_ID                (0x30082900)
  #define PB1_MCA_INS_ID                (0x32082900)
  #define PB2_MCA_INS_ID                (0x34082900)
  #define PB3_MCA_INS_ID                (0x36082900)
  #define PB4_MCA_INS_ID                (0x38082900)
  #define PB5_MCA_INS_ID                (0x3A082900)
  #define PB6_MCA_INS_ID                (0x3C082900)
  #define PB7_MCA_INS_ID                (0x3F082900)

#define MCA_PSP_ID                      (0x0FF)
  #define PSP_MCA_TYPE                  (0x0001)

#define MCA_SMU_ID                      (0x001)
  #define SMU_MCA_TYPE                  (0x0001)
  #define MP5_MCA_TYPE                  (0x0002)
  #define MP50_MCA_INS_ID               (0x30430400)
  #define MP51_MCA_INS_ID               (0x32430400)
  #define MP52_MCA_INS_ID               (0x34430400)
  #define MP53_MCA_INS_ID               (0x36430400)
  #define MP54_MCA_INS_ID               (0x38430400)
  #define MP55_MCA_INS_ID               (0x3A430400)
  #define MP56_MCA_INS_ID               (0x3C430400)
  #define MP57_MCA_INS_ID               (0x3F430400)

#define MCA_NBIO_ID                     (0x0018)
  #define NBIO_MCA_TYPE                 (0x0000)
  #define NBIO0_MCA_INS_ID              (0x13B1700)
  #define NBIO1_MCA_INS_ID              (0x13C1700)
  #define NBIO2_MCA_INS_ID              (0x13D1700)
  #define NBIO3_MCA_INS_ID              (0x13E1700)

#define MCA_PCIE_ID                     (0x0046)
  #define PCIE_MCA_TYPE                 (0x0000)
  #define PCIE0_MCA_INS_ID              (0x111C0000)
  #define PCIE1_MCA_INS_ID              (0x112C0000)
  #define PCIE2_MCA_INS_ID              (0x113C0000)
  #define PCIE3_MCA_INS_ID              (0x114C0000)

//This is old x86 MCA address
#define LMCA_ADDR_REG                   (0x00)
#define LMCA_STATUS_REG                 (0x01)

#define SMM_SAVE_STATE_OFFSET           (0xFE00)

#define DEVICE_WIDTH_x4                 (4)
#define DEVICE_WIDTH_x8                 (8)
#define ECC_SYMBOL_SIZE_x4              (0)
#define ECC_SYMBOL_SIZE_x8              (1)
#define ECC_SYMBOL_SIZE_x16             (2)
#define ECC_BIT_INTERLEAVING_DISABLED   (0)
#define ECC_BIT_INTERLEAVING_ENABLED    (1)

/// ACPI define
/// ACPI 6.2
#define GENERIC_ERROR_REVISION          (0x0300)
#define AMD_VENDOR_ID                   (0x1022)

///NBIO
#define IOHC_NB_SMN_INDEX_2_BIOS        (0x00B8)
#define IOHC_NB_SMN_DATA_2_BIOS         (0x00BC)

#define MAX_SOCKET_SUPPORT                  (2)
#define MAX_NBIO_PER_DIE                    (4)
#define MAX_NBIO_SUPPORT                    (8)             //Max availiable on SSP Platform
#define MCA_PCIE_CORE0_PORT_SUPPORT         (8)             //Max PCI-E port support for Core 0.
#define MCA_PCIE_CORE1_PORT_SUPPORT         (8)             //Max PCI-E port support for Core 1.
#define MCA_PCIE_CORE2_PORT_SUPPORT         (2)             //Max PCI-E port support for Core 2.
#define MAX_PCIE_PORT_SUPPORT               (18)            //Max PCI-E port support per NBIO.
#define MAX_NBIF_PER_NBIO                   (3)
#define MAX_LEAF_PER_NBIF                   (5)
#define MAX_SYSHUB_PER_NBIO                 (2)
#define MAX_GDCL_LEAF_PER_SYSHUB            (3)
#define MAX_GDCSOC_LEAF_PER_SYSHUB          (2)
#define MAX_GDCSHUB_LEAF_PER_SYSHUB         (2)
#define MAX_SHUB_MPX_LAST_XREQ_LOG          (3)
#define MAX_USB_PER_DIE                     (2)

#define MAX_UNCORR_GRP_NUM                  (25)
#define MAX_CORR_GRP_NUM                    (23)
#define MAX_UCP_GRP_NUM                     (17)

#define NBIO_SMN_ADDR_OFFSET                (0x100000)
#define IOHC_INTERRUPT_EOI                  (0x13B10120)
#define RAS_PARITY_CONTROL_0                (0x13B20000)
#define RAS_PARITY_CONTROL_1                (0x13B20004)
#define RAS_GLOBAL_STATUS_LO                (0x13B20020)
#define RAS_GLOBAL_STATUS_HI                (0x13B20024)
#define RAS_GLOBAL_STATUS_NBIO_ERR_MASK     (0x0000000F)
#define RAS_GLOBAL_STATUS_LO_MASK           (0x000001FF)
#define RAS_GLOBAL_STATUS_HI_MASK           (0x0003FFFF)

#define PARITY_ERROR_STATUS_UNCORR_GRP      (0x13B20028)
#define PARITY_ERROR_STATUS_CORR_GRP        (0x13B2008C)
#define PARITY_COUNTER_CORR_GRP             (0x13B200E8)
#define PARITY_ERROR_STATUS_UCP_GRP         (0x13B20144)
#define PARITY_COUNTER_UCP_GRP              (0x13B20188)
#define PCIE_PORT_ACTION_CONTROL_BASE       (0x13B201F0)
#define PCIE_ACTION_CONTROL_OFFSET          (0x20)
#define NBIF0_ACTION_CONTROL_BASE           (0x13B20430)
#define NBIF1_ACTION_CONTROL_BASE           (0x13B20450)

#define NBIF0_BIFL_RAS_CENTRAL_STATUS       (0x10139040)
#define NBIF0_BIFL_RAS_LEAF0_CTRL           (0x10139080)
#define NBIF0_BIFL_RAS_LEAF1_CTRL           (0x10139084)
#define NBIF0_BIFL_RAS_LEAF2_CTRL           (0x10139088)
#define NBIF2_BIFL_RAS_LEAF3_CTRL           (0x1093908C)
#define NBIF2_BIFL_RAS_LEAF4_CTRL           (0x10939090)
#define NBIF0_BIFL_RAS_LEAF0_STATUS         (0x101390C0)
#define NBIF0_BIFL_RAS_LEAF1_STATUS         (0x101390C4)
#define NBIF0_BIFL_RAS_LEAF2_STATUS         (0x101390C8)
#define NBIF2_BIFL_RAS_LEAF3_STATUS         (0x109390CC)
#define NBIF2_BIFL_RAS_LEAF4_STATUS         (0x109390D0)

#define GDCL_RAS_CENTRAL_STATUS             (0x0141F840)
#define GDCL_RAS_LEAF0_CTRL                 (0x0141F880)
#define GDCL_RAS_LEAF1_CTRL                 (0x0141F884)
#define GDCL_RAS_LEAF2_CTRL                 (0x0141F888)
#define GDCL_RAS_LEAF0_STATUS               (0x0141F8C0)
#define GDCL_RAS_LEAF1_STATUS               (0x0141F8C4)
#define GDCL_RAS_LEAF2_STATUS               (0x0141F8C8)
#define GDCSOC_RAS_CENTRAL_STATUS           (0x0141FA40)
#define GDCSOC_RAS_LEAF0_CTRL               (0x0141FA80)
#define GDCSOC_RAS_LEAF1_CTRL               (0x0141FA84)
#define GDCSOC_RAS_LEAF0_STATUS             (0x0141FAC0)
#define GDCSOC_RAS_LEAF1_STATUS             (0x0141FAC4)
#define GDCSHUB_RAS_CENTRAL_STATUS          (0x0141FC40)
#define GDCSHUB_RAS_LEAF0_STATUS            (0x0181FCC0)
#define GDCSHUB_RAS_LEAF1_STATUS            (0x0181FCC4)
#define SHUB_MP_TODET_CTRL                  (0x0181F8C4)
#define SHUB_MP_TODET_STATUS                (0x0181F8C8)
#define SHUB_MP0_LAST_WRREQ_LOG_0           (0x0181F8CC)
#define SHUB_MP0_LAST_WRREQ_LOG_1           (0x0181F8D0)
#define SHUB_MP0_LAST_WRREQ_LOG_2           (0x0181F8D4)
#define SHUB_MP0_LAST_RDREQ_LOG_0           (0x0181F8D8)
#define SHUB_MP0_LAST_RDREQ_LOG_1           (0x0181F8DC)
#define SHUB_MP0_LAST_RDREQ_LOG_2           (0x0181F8E0)
#define SHUB_MP1_LAST_WRREQ_LOG_0           (0x0181F8E4)
#define SHUB_MP1_LAST_WRREQ_LOG_1           (0x0181F8E8)
#define SHUB_MP1_LAST_WRREQ_LOG_2           (0x0181F8EC)
#define SHUB_MP1_LAST_RDREQ_LOG_0           (0x0181F8F0)
#define SHUB_MP1_LAST_RDREQ_LOG_1           (0x0181F8F4)
#define SHUB_MP1_LAST_RDREQ_LOG_2           (0x0181F8F8)
#define SHUB_MP_LAST_REQ_LOG_CLEAR          (0x0181F8FC)

#define NBIO2NBIF1_RCC_DEV0_EPF3_STRAP0     (0x10734600)
#define NBIO3NBIF1_RCC_DEV0_EPF3_STRAP0     (0x10834600)
#define NBIO2NBIF1_MEM_ECC_STATUS_CNTR0     (0x16D8013C)  //USB0
#define NBIO3NBIF1_MEM_ECC_STATUS_CNTR0     (0x16F8013C)  //USB1
#define NBIO2NBIF1_MEM_ECC_SMI_STATUS_CNTR0 (0x16D80140)  //USB0
#define NBIO3NBIF1_MEM_ECC_SMI_STATUS_CNTR0 (0x16F80140)  //USB1

#define NBIO0_EGRESS_POISON_STATUS_LO       (0x13B20820)
#define NBIO1_EGRESS_POISON_STATUS_LO       (0x13C20820)
#define NBIO2_EGRESS_POISON_STATUS_LO       (0x13D20820)
#define NBIO3_EGRESS_POISON_STATUS_LO       (0x13E20820)
#define NBIO0_EGRESS_POISON_STATUS_HI       (0x13B20824)
#define NBIO1_EGRESS_POISON_STATUS_HI       (0x13C20824)
#define NBIO2_EGRESS_POISON_STATUS_HI       (0x13D20824)
#define NBIO3_EGRESS_POISON_STATUS_HI       (0x13E20824)

///MSR
/// P-state MSR
typedef union {
  struct {                             ///< Bitfields of P-state MSR
    UINT64 CpuFid_7_0:8;               ///< CpuFid[7:0]
    UINT64 CpuDfsId:6;                 ///< CpuDfsId
    UINT64 CpuVid:8;                   ///< CpuVid
    UINT64 IddValue:8;                 ///< IddValue
    UINT64 IddDiv:2;                   ///< IddDiv
    UINT64 :31;                        ///< Reserved
    UINT64 PstateEn:1;                 ///< Pstate Enable
  } Field;
  UINT64  Value;
} PSTATE_MSR;

typedef union {
  /// Bitfields of MCA_SYND_UMC DramEccErr error type error information decode.
  struct {
    UINT32 ChipSelect:3;                ///< Chip Select
    UINT32 :1;                          ///< Reserved
    UINT32 Cid:3;                       ///< Specifies the rank multiply ID for supported DIMMs
    UINT32 :1;                          ///< Reserved
    UINT32 Symbol:6;                    ///< Only contains valid information on a corrected error.
    UINT32 HwHistoryErr:1;              ///< Hardware history error
    UINT32 SwManagedBadSymbolIdErr:1;   ///< Software-Managed Bad Symbol ID Error
    UINT32 :16;                         ///< Reserved
  } Fields;
  UINT32  Value;
} UMC_SYND_ECC_ERR_INFO;

///NBIO
typedef enum _NBIO_ERROR_CODE_EXT_NUM {
  NBIO_PARITY = 0,                          ///< 0
  NBIO_PCIE_SIDEBAND,                       ///< 1
  NBIO_ERREVENT,                            ///< 2
  NBIO_EGRESS_POISON,                       ///< 3
  NBIO_IOHC_INTERNAL_POISON                 ///< 4
} NBIO_ERROR_CODE_EXT_NUM;

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
  /// Bitfields of NBIFRAS BIFL_RAS_LEAFx_STATUS, NBIFGDCRAS GDCL_RAS_LEAFx_STATUS and GDCSOC_RAS_LEAF0_STATUS
  struct {
    UINT32 ErrEventRecv:1;                 ///< Status for SDP error event receive recording.
    UINT32 PoisonErrDet:1;                 ///< Status for self-detected poison data recording.
    UINT32 ParityErrDet:1;                 ///< Status for self-detected parity error recording.
    UINT32 :5;                             ///< Reserved
    UINT32 ErrEventGennStat:1;             ///< Has sent errEvent from self-generated error.
    UINT32 EgressStalledGennStat:1;        ///< Has stalled egress port from self-generated error.
    UINT32 ErrEventPropStat:1;             ///< Sent error event from propagated errEvent.
    UINT32 EgressStalledPropStat:1;        ///< stalled egress port from propagated stall.
    UINT32 :20;                            ///< Reserved
  } Fields;
  UINT32  Value;
} RAS_LEAF_STATUS_REG;

typedef union {
  /// Bitfields of RAS_CENTRAL_STATUS
  struct {
    UINT32 BiflL2cEgStallDet:1;             ///< Local EgStall_det.
    UINT32 BiflL2cErrEventDet:1;            ///< Local ErrEvent_det.
    UINT32 BiflC2lEgStallDet:1;             ///< Propagated EgStall_det.
    UINT32 BiflC2lErrEventDet:1;            ///< Propagated ErrEvent_det.
    UINT32 :25;                             ///< Reserved
    UINT32 BiflRasContllerErrEventRecv:1;   ///< Recieved ras err_event from RAS controller.
    UINT32 BiflRasContllerIntrRecv:1;       ///< Recieved ras_intr from RAS controller.
    UINT32 BiflLinkDisRecv:1;               ///< Received LinkDis.
  } Fields;
  UINT32  Value;
} RAS_CENTRAL_STATUS_REG;

typedef union {
  /// Bitfields of RAS_GLOBAL_STS_HI Register
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
    UINT32 Pcie2PortA:1;                    ///< The status of errors from PCIE2 PortA
    UINT32 Pcie2PortB:1;                    ///< The status of errors from PCIE2 PortB
    UINT32 Nbif0PortA:1;                    ///< The status of errors from NBIF0 PortA
    UINT32 Nbif1PortA:1;                    ///< The status of errors from NBIF1 PortA
    UINT32 Nbif1PortB:1;                    ///< The status of errors from NBIF1 PortB
    UINT32 Nbif1PortC:1;                    ///< The status of errors from NBIF1 PortC
    UINT32 :10;                             ///< Reserved
  } Fields;
  UINT32  Value;
} RAS_GLOBAL_STS_HI_REG;

typedef union {
  struct {
    UINT32                            ShubMp0WrTimeoutDetected:1 ; ///< SHUB_MP0_WR_TIMEOUT_DETECTED
    UINT32                            shubMp0RdTimeoutDetected:1 ; ///< SHUB_MP0_RD_TIMEOUT_DETECTED
    UINT32                                                    :6 ; ///< Reserved
    UINT32                            ShubMp1WrTimeoutDetected:1 ; ///< SHUB_MP1_WR_TIMEOUT_DETECTED
    UINT32                            ShubMp1RdTimeoutDetected:1 ; ///< SHUB_MP1_RD_TIMEOUT_DETECTED
    UINT32                                                    :22; ///< Reserved
  } Field;
  UINT32 Value;
} SHUB_MP_TODET_STATUS_REG;

typedef union {
  struct {
    UINT32                               ShubMpLastReqLogClear:1 ; ///< SHUB_MP_LAST_REQ_LOG_CLEAR
    UINT32                                                    :31; ///< Reserved
  } Field;
  UINT32 Value;
} SHUB_MP_LAST_REQ_LOG_CLEAR_REG;

///DXIO

typedef union {
  /// Bitfields of PHY_IVC_40_ECC_MEMORY_CNTL1 Register
  struct {
    UINT32 ForceSecOnDed:1;                 ///< FORCE_SEC_ON_DED
    UINT32 :7;                              ///<
    UINT32 DED:1;                           ///< Double Error Detect
    UINT32 SEC:1;                           ///< Single Error Detect
  } Fields;
  UINT16  Value;
}PHY_IVC_40_ECC_MEMORY_CNTL1;

// USB
typedef union {
  struct {
    UINT32 ECC_DedErrSMI:1 ; ///<
    UINT32              :31; ///<
  } Field;
  UINT32 Value;
} MEM_ECC_SMI_STATUS_CNTR0_REG;

#define PHY_IVC_40_ECC_MEMORY_CNTL1_REG     (0x10072)

#define PAPCS0_OFFSET                       (0x00000)
#define PAPCS1_OFFSET                       (0x20000)
#define PAPCS2_OFFSET                       (0x40000)
#define PAPCS3_OFFSET                       (0x60000)
#define PAPCS_APERTURE_SIZE                 (0x20000)

#define PCS_RANGE                           (4)
#define SATA_PCS_RANGE                      (2)

#define PCIE_SCAN_RANGE                     (8)
#define SATA_SCAN_RANGE                     (4)
#define XGMI_SCAN_RANGE                     (6)
#define WALF_SCAN_RANGE                     (2)

#define APERTURE_SIZE                       (0x100000)

#define PCS_PCIE0P0_BASE                    (0x12200000)
#define PCS_PCIE1P0_BASE                    (0x12300000)
#define PCS_PCIE2P0_BASE                    (0x12400000)
#define PCS_PCIE3P0_BASE                    (0x12500000)
#define PCS_PCIE4P0_BASE                    (0x12600000)
#define PCS_PCIE5P0_BASE                    (0x12700000)
#define PCS_PCIE6P0_BASE                    (0x12800000)
#define PCS_PCIE7P0_BASE                    (0x12900000)

#define PCS_SATA0P0_BASE                    (0x12A00000)
#define PCS_SATA1P0_BASE                    (0x12B00000)
#define PCS_SATA2P0_BASE                    (0x12C00000)
#define PCS_SATA3P0_BASE                    (0x12D00000)

#define PCS_XGMI0P0_BASE                    (0x12E00000)
#define PCS_XGMI1P0_BASE                    (0x12F00000)
#define PCS_XGMI2P0_BASE                    (0x13000000)
#define PCS_XGMI3P0_BASE                    (0x13100000)
#define PCS_XGMI4P0_BASE                    (0x13200000)
#define PCS_XGMI5P0_BASE                    (0x13300000)

#define PCS_WAFL0P0_BASE                    (0x13400000)
#define PCS_WAFL1P0_BASE                    (0x13500000)

#define PCS_WAFLPCIE1P0_BASE                (0x18000000)

///FCH
#define ACPIMMIO32(x) (*(volatile UINT32*)(UINTN)(x))
#define ACPI_MMIO_BASE                  (0xFED80000ul)
#define SMI_BASE                        (0x200)          // DWORD
#define FCH_SMI_REG18                   (0x18)
#define FCH_SMI_REG1C                   (0x1C)
#define FCH_SMI_REG96                   (0x96)
#define FCH_SMI_REG98                   (0x98)
#define FCH_SMI_REGC0                   (0xC0)
#define FCH_SMI_REGC3                   (0xC3)
#define PMIO_BASE                       (0x300)          // DWORD
#define FCH_PMIOA_REG6A                 (0x6A)           // AcpiSmiCmd

#define SMI_TIMER_ENABLE                BIT15

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

//FCH A-Link RAS
#define FCH_SMI_REG88                       (0x88)
#define FCH_SMBUS_BUS                       (0x00)
#define FCH_SMBUS_DEV                       (0x14)
#define FCH_SMBUS_FUNC                      (0x00)
#define FCH_LPC_BUS                         (0x00)
#define FCH_LPC_DEV                         (0x14)
#define FCH_LPC_FUNC                        (0X03)
#define PCI_STATUS                          (0X06)

#define HUASHAN_SATA_PORT_NUM               (8)

#define SATA_PAR_ERR_CNXT_STS               BIT10
#define SATA_PAR_ERR_H2D_STS                BIT9
#define SATA_PAR_ERR_D2H2D_STS              BIT8
#define SATA_PAR_ERR_STS                    (SATA_PAR_ERR_CNXT_STS + SATA_PAR_ERR_H2D_STS + SATA_PAR_ERR_D2H2D_STS)

///UMC
#define UMC0_CH_REG_BASE                    (0x00050000)
#define UMC_SMN_ADDR_OFFSET                 (0x100000)
#define UMC1_CH_REG_BASE                    (0x00150000)
#define UMC_ECC_CTRL                        (0x0000014C)
#define UMC_MISC_CFG                        (0x000001E0)
#define UMC_ECC_ERR_INJ_CTRL                (0x00000D88)
  #define ECC_ERR_ADDR_EN                   BIT2
#define UMC_ECC_ERR_INJ                     (0x00000DB0)

///DF
#define DF_CFGADDRESSCNTL_FUNC              (0x00)
#define DF_CFGADDRESSCNTL_OFFSET            (0x84)

#define DF_DFF6_REG_BASE                    (0x0001D800)
#define DRAM_SCRUBBER_ERRORADDR_LO          (0x000000B0)
  #define ERR_INJ_EN                        BIT0
#define DRAM_SCRUBBER_ERRORADDR_HI          (0x000000B4)
#define DRAM_SCRUBBER_BASEADDR_REG          (0x00000040)  //DramScrubBaseAddr
#define DRAM_SCRUBBER_LIMIT_ADDR            (0x00000044)  //DramScrubLimitAddr
#define DRAM_SCRUBBER_ADDR_LO               (0x00000048)  //DramScrubAddrLo
#define DRAM_SCRUBBER_ADDR_HI               (0x0000004C)  //DramScrubAddrHi
#define DRAM_SCRUBBER_BASEADDR_1            (0x00000050)  //DramScrubBaseAddr_1
#define DRAM_SCRUBBER_LIMIT_ADDR_1          (0x00000054)  //DramScrubLimitAddr_1
#define DRAM_SCRUBBER_ADDR_LO_1             (0x00000058)  //DramScrubAddrLo_1
#define DRAM_SCRUBBER_ADDR_HI_1             (0x0000005C)  //DramScrubAddrHi_1
#define DRAM_SCRUBBER_BASEADDR_2            (0x00000060)  //DramScrubBaseAddr_2
#define DRAM_SCRUBBER_LIMIT_ADDR_2          (0x00000064)  //DramScrubLimitAddr_2
#define DRAM_SCRUBBER_ADDR_LO_2             (0x00000068)  //DramScrubAddrLo_2
#define DRAM_SCRUBBER_ADDR_HI_2             (0x0000006C)  //DramScrubAddrHi_2
#define DRAM_SCRUBBER_BASEADDR_3            (0x00000070)  //DramScrubBaseAddr_3
#define DRAM_SCRUBBER_LIMIT_ADDR_3          (0x00000074)  //DramScrubLimitAddr_3
#define DRAM_SCRUBBER_ADDR_LO_3             (0x00000078)  //DramScrubAddrLo_3
#define DRAM_SCRUBBER_ADDR_HI_3             (0x0000007C)  //DramScrubAddrHi_3

#define DRAM_SCRUBBER_ERROR_ADDRESS_LOW_MASK (0xFFFFFFFFFFFFFFC0)

#define MYDIETYPELO             (21)
#define MYDIETYPEHI             (22)
#define SOCKETIDSHIFTLO_DF2     (28)
#define SOCKETIDSHIFTHI_DF2     (31)
#define SOCKETIDMASKLO_DF2      (16)
#define SOCKETIDMASKHI_DF2      (23)
#define DIEIDSHIFTLO_DF2        (24)
#define DIEIDSHIFTHI_DF2        (27)
#define DIEIDMASKLO_DF2         (8)
#define DIEIDMASKHI_DF2         (15)

#define SOCKETIDSHIFTLO_DF3     (8)
#define SOCKETIDSHIFTHI_DF3     (9)
#define SOCKETIDMASKLO_DF3      (24)
#define SOCKETIDMASKHI_DF3      (26)
#define DIEIDSHIFTLO_DF3        (0) // Same as NodeIDshift
#define DIEIDSHIFTHI_DF3        (3)
#define DIEIDMASKLO_DF3         (16)
#define DIEIDMASKHI_DF3         (18)
#define NODEIDSHIFTLO_DF3       (0)
#define NODEIDSHIFTHI_DF3       (3)

#define BLKINSTCOUNTLO          (0)
#define BLKINSTCOUNTHI          (7)
#define INSTANCETYPELO          (0)
#define INSTANCETYPEHI          (3)

#define BLOCKFABRICIDLO         (8)
#define BLOCKFABRICIDHI         (15)
#define HIADDROFFSETEN          (0)
#define HIADDROFFSETLO          (12)
#define HIADDROFFSETHI          (31)
#define ADDRRNGVAL              (0)
#define DRAMBASEADDRLO          (12)
#define DRAMBASEADDRHI          (31)
#define DRAMLIMITADDRLO         (12)
#define DRAMLIMITADDRHI         (31)
#define LGCYMMIOHOLEEN          (1)
#define DRAMHOLEBASELO          (24)
#define DRAMHOLEBASEHI          (31)

#define INTLVADDRSELLO_DF2      (8)
#define INTLVADDRSELHI_DF2      (10)
#define INTLVADDRSELLO_DF3      (9)
#define INTLVADDRSELHI_DF3      (11)
#define INTLVNUMCHANLO_DF2      (4)
#define INTLVNUMCHANHI_DF2      (7)
#define INTLVNUMCHANLO_DF3      (2)
#define INTLVNUMCHANHI_DF3      (5)
#define INTLVNUMDIESLO_DF2      (10)
#define INTLVNUMDIESHI_DF2      (11)
#define INTLVNUMDIESLO_DF3      (6)
#define INTLVNUMDIESHI_DF3      (7)
#define INTLVNUMSKTS_DF2        (8)
#define INTLVNUMSKTS_DF3        (8)
#define DSTFABRICIDLO_DF2       (0)
#define DSTFABRICIDHI_DF2       (7)
#define DSTFABRICIDLO_DF3       (0)
#define DSTFABRICIDHI_DF3       (9)

#define NUM_DRAM_MAPS           (16)
#define CCMINSTANCETYPE         (0)
#define CSINSTANCETYPE          (4)
#define BCAST                   (0xffffffff)
#define DIE_PER_SOCKET          (1)
#define UMC_PER_DIE             (8)
#define CHANNEL_PER_UMC         (1)

#define DF_SYSCFG_ADDR                      ((1<<10)|(0x200))
#define DF_SYSFABIDMASK_ADDR                ((1<<10)|(0x208))
#define DF_SYSFABIDMASK1_ADDR               ((1<<10)|(0x20C))   // DF3 only
#define DF_FABBLKINSTCNT_ADDR               ((0<<10)|(0x040))
#define DF_FABBLKINFO0_ADDR                 ((0<<10)|(0x044))
#define DF_FABBLKINFO3_ADDR                 ((0<<10)|(0x050))
#define DF_DRAMBASE0_ADDR                   ((0<<10)|(0x110))
#define DF_DRAMLIMIT0_ADDR                  ((0<<10)|(0x114))
#define DF_DRAMOFFSET0_ADDR                 ((0<<10)|(0x1B0)) // DramOffset0 doesn't technically exist.
#define DF_DRAMHOLECTRL_ADDR                ((0<<10)|(0x104))

#define RSPQWDTIOTRANSLOGLOW                ((6<<10)|(0x1E8))
#define RSPQWDTIOTRANSLOGHIGH               ((6<<10)|(0x1EC))
#define DF_HARDWAREASSERTSTATUSLOW_ADDR     ((6<<10)|(0x1F0))
#define DF_HARDWAREASSERTSTATUSHIGH_ADDR    ((6<<10)|(0x1F4))
#define DF_CFGADDRESSCNTL                   ((0<<10)|(0x084))

#define DF_CCM_HARDWAREASSERTSTATUSLOW_MASK     (BIT4 | BIT5)
#define DF_CCM_HARDWAREASSERTSTATUSHIGH_MASK    (BIT25 | BIT26)

#define SSP_MAX_CCM_PER_DIE                 (8)
#define SSP_CCM0_INSTANCE_ID                (16)
#define SSP_CCM1_INSTANCE_ID                (17)
#define SSP_CCM2_INSTANCE_ID                (18)
#define SSP_CCM3_INSTANCE_ID                (19)
#define SSP_CCM4_INSTANCE_ID                (20)
#define SSP_CCM5_INSTANCE_ID                (21)
#define SSP_CCM6_INSTANCE_ID                (22)
#define SSP_CCM7_INSTANCE_ID                (23)

#define SSP_MAX_IOMS_PER_DIE                (4)
#define SSP_IOMS0_INSTANCE_ID               (24)
#define SSP_IOMS1_INSTANCE_ID               (25)
#define SSP_IOMS2_INSTANCE_ID               (26)
#define SSP_IOMS3_INSTANCE_ID               (27)

#define FABRIC_REG_ACC_BC       (0xFF)

/* Fabric Indirect Config Access Address 3 Register */
#define FICAA3_FUNC             (0x4)
#define FICAA3_REG              (0x05C)

/* Fabric Indirect Config Access Data 3 Low Register */
#define FICAD3_LO_FUNC          (0x4)
#define FICAD3_LO_REG           (0x98)

/* Fabric Indirect Config Access Data 3 High Register */
#define FICAD3_HI_FUNC          (0x4)
#define FICAD3_HI_REG           (0x9C)

/// Fabric Indirect Config Access Address 3 Register
typedef union {
  struct {                             ///< Bitfields of Fabric Indirect Config Access Address 3 Register
    UINT32 CfgRegInstAccEn:1;          ///< CfgRegInstAccEn
    UINT32 :1;                         ///< Reserved
    UINT32 IndCfgAccRegNum:9;          ///< IndCfgAccRegNum
    UINT32 IndCfgAccFuncNum:3;         ///< IndCfgAccFuncNum
    UINT32 SixtyFourBitRegEn:1;        ///< SixtyFourBitRegEn
    UINT32 :1;                         ///< Reserved
    UINT32 CfgRegInstID:8;             ///< CfgRegInstID
    UINT32 :8;                         ///< Reserved
  } Field;
  UINT32  Value;
} FABRIC_IND_CFG_ACCESS_ADDR_REGISTER;

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
  IN       UINT32  ADDRHASHRMADDR[16][3];
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

#endif  // _AMD_RAS_REGISTERS_SSP_H_

