/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD Family 17h Starship Information definition
 *
 */
/*
 ******************************************************************************
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

#ifndef _FABRIC_INFO_SSP_H_
#define _FABRIC_INFO_SSP_H_
#pragma pack (push, 1)

// Fabric IDs
#define  SSP_CS0_FABRIC_ID         0
#define  SSP_CS1_FABRIC_ID         1
#define  SSP_CS2_FABRIC_ID         2
#define  SSP_CS3_FABRIC_ID         3
#define  SSP_CS4_FABRIC_ID         4
#define  SSP_CS5_FABRIC_ID         5
#define  SSP_CS6_FABRIC_ID         6
#define  SSP_CS7_FABRIC_ID         7
#define  SSP_CS8_FABRIC_ID         8
#define  SSP_CS9_FABRIC_ID         9
#define  SSP_CS10_FABRIC_ID       10
#define  SSP_CS11_FABRIC_ID       11

#define  SSP_CSUMC0_FABRIC_ID     SSP_CS0_FABRIC_ID
#define  SSP_CSUMC1_FABRIC_ID     SSP_CS1_FABRIC_ID
#define  SSP_CSUMC2_FABRIC_ID     SSP_CS2_FABRIC_ID
#define  SSP_CSUMC3_FABRIC_ID     SSP_CS3_FABRIC_ID
#define  SSP_CSUMC4_FABRIC_ID     SSP_CS4_FABRIC_ID
#define  SSP_CSUMC5_FABRIC_ID     SSP_CS5_FABRIC_ID
#define  SSP_CSUMC6_FABRIC_ID     SSP_CS6_FABRIC_ID
#define  SSP_CSUMC7_FABRIC_ID     SSP_CS7_FABRIC_ID

#define  SSP_CSCCIX0_FABRIC_ID    SSP_CS8_FABRIC_ID
#define  SSP_CSCCIX1_FABRIC_ID    SSP_CS9_FABRIC_ID
#define  SSP_CSCCIX2_FABRIC_ID    SSP_CS10_FABRIC_ID
#define  SSP_CSCCIX3_FABRIC_ID    SSP_CS11_FABRIC_ID

#define  SSP_CCM0_FABRIC_ID       16
#define  SSP_CCM1_FABRIC_ID       17
#define  SSP_CCM2_FABRIC_ID       18
#define  SSP_CCM3_FABRIC_ID       19
#define  SSP_CCM4_FABRIC_ID       20
#define  SSP_CCM5_FABRIC_ID       21
#define  SSP_CCM6_FABRIC_ID       22
#define  SSP_CCM7_FABRIC_ID       23

#define  SSP_IOMS0_FABRIC_ID      24
#define  SSP_IOMS1_FABRIC_ID      25
#define  SSP_IOMS2_FABRIC_ID      26
#define  SSP_IOMS3_FABRIC_ID      27

#define  SSP_PIE_FABRIC_ID        30

// Instance IDs
#define  SSP_CS0_INSTANCE_ID       0
#define  SSP_CS1_INSTANCE_ID       1
#define  SSP_CS2_INSTANCE_ID       2
#define  SSP_CS3_INSTANCE_ID       3
#define  SSP_CS4_INSTANCE_ID       4
#define  SSP_CS5_INSTANCE_ID       5
#define  SSP_CS6_INSTANCE_ID       6
#define  SSP_CS7_INSTANCE_ID       7
#define  SSP_CS8_INSTANCE_ID       8
#define  SSP_CS9_INSTANCE_ID       9
#define  SSP_CS10_INSTANCE_ID     10
#define  SSP_CS11_INSTANCE_ID     11

#define  SSP_CSUMC0_INSTANCE_ID   SSP_CS0_INSTANCE_ID
#define  SSP_CSUMC1_INSTANCE_ID   SSP_CS1_INSTANCE_ID
#define  SSP_CSUMC2_INSTANCE_ID   SSP_CS2_INSTANCE_ID
#define  SSP_CSUMC3_INSTANCE_ID   SSP_CS3_INSTANCE_ID
#define  SSP_CSUMC4_INSTANCE_ID   SSP_CS4_INSTANCE_ID
#define  SSP_CSUMC5_INSTANCE_ID   SSP_CS5_INSTANCE_ID
#define  SSP_CSUMC6_INSTANCE_ID   SSP_CS6_INSTANCE_ID
#define  SSP_CSUMC7_INSTANCE_ID   SSP_CS7_INSTANCE_ID

#define  SSP_CSCCIX0_INSTANCE_ID  SSP_CS8_INSTANCE_ID
#define  SSP_CSCCIX1_INSTANCE_ID  SSP_CS9_INSTANCE_ID
#define  SSP_CSCCIX2_INSTANCE_ID  SSP_CS10_INSTANCE_ID
#define  SSP_CSCCIX3_INSTANCE_ID  SSP_CS11_INSTANCE_ID

#define  SSP_CCM0_INSTANCE_ID     16
#define  SSP_CCM1_INSTANCE_ID     17
#define  SSP_CCM2_INSTANCE_ID     18
#define  SSP_CCM3_INSTANCE_ID     19
#define  SSP_CCM4_INSTANCE_ID     20
#define  SSP_CCM5_INSTANCE_ID     21
#define  SSP_CCM6_INSTANCE_ID     22
#define  SSP_CCM7_INSTANCE_ID     23

#define  SSP_IOMS0_INSTANCE_ID    24
#define  SSP_IOMS1_INSTANCE_ID    25
#define  SSP_IOMS2_INSTANCE_ID    26
#define  SSP_IOMS3_INSTANCE_ID    27

#define  SSP_PIE_INSTANCE_ID      30

#define  SSP_CAKE0_INSTANCE_ID    31
#define  SSP_CAKE1_INSTANCE_ID    32
#define  SSP_CAKE2_INSTANCE_ID    33
#define  SSP_CAKE3_INSTANCE_ID    34
#define  SSP_CAKE4_INSTANCE_ID    35
#define  SSP_CAKE5_INSTANCE_ID    36

#define  SSP_TCDX0_INSTANCE_ID    37
#define  SSP_TCDX1_INSTANCE_ID    38
#define  SSP_TCDX2_INSTANCE_ID    39
#define  SSP_TCDX3_INSTANCE_ID    40
#define  SSP_TCDX4_INSTANCE_ID    41
#define  SSP_TCDX5_INSTANCE_ID    42
#define  SSP_TCDX6_INSTANCE_ID    43
#define  SSP_TCDX7_INSTANCE_ID    44
#define  SSP_TCDX8_INSTANCE_ID    45
#define  SSP_TCDX9_INSTANCE_ID    46
#define  SSP_TCDX10_INSTANCE_ID   47
#define  SSP_TCDX11_INSTANCE_ID   48

#define  SSP_NUM_CS_BLOCKS        12
#define  SSP_NUM_CS_UMC_BLOCKS     8
#define  SSP_NUM_CS_CCIX_BLOCKS    4
#define  SSP_NUM_CCM_BLOCKS        8
#define  SSP_NUM_IOMS_BLOCKS       4
#define  SSP_NUM_PIE_BLOCKS        1
#define  SSP_NUM_CAKE_BLOCKS       6
#define  SSP_NUM_TCDX_BLOCKS      12

#define  SSP_NUM_DF_BLOCKS        43

/* PCI Bus Regions */
#define SSP_NUMBER_OF_BUS_REGIONS         0x8
#define SSP_BUS_REGION_REGISTER_OFFSET    0x4

/* x86 IO Regions */
#define SSP_NUMBER_OF_X86IO_REGIONS       0x8
#define SSP_X86IO_REGION_REGISTER_OFFSET  0x8

/* DRAM Regions */
#define SSP_NUMBER_OF_DRAM_REGIONS        0x10
#define SSP_DRAM_REGION_REGISTER_OFFSET   0x8

/* MMIO Regions */
#define SSP_NUMBER_OF_MMIO_REGIONS        0x10
#define SSP_MMIO_REGION_REGISTER_OFFSET   0x10

#define SSP_MAX_SOCKETS                   2   ///< Max number of sockets in system
#define SSP_MAX_DIES_PER_SOCKET           1   ///< Max number of dies per socket
#define SSP_MAX_CCD_PER_SOCKET            8   ///< Max number of CCD per socket
#define SSP_MAX_CHANNELS_PER_DIE          8   ///< Max Channels per die
#define SSP_MAX_HOST_BRIDGES_PER_DIE      4   ///< Max host bridges per die

#define SSP_FABRIC_ID_SOCKET_SHIFT        5
#define SSP_FABRIC_ID_SOCKET_SIZE_MASK    1
#define SSP_FABRIC_ID_DIE_SHIFT           0
#define SSP_FABRIC_ID_DIE_SIZE_MASK       0

#pragma pack (pop)
#endif /* _FABRIC_INFO_SSP_H_ */

