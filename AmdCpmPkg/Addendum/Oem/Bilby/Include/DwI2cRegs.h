/*****************************************************************************
 *
 * Copyright 2015 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
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
 ******************************************************************************
 */

#ifndef _DWI2C_REGS_H_
#define _DWI2C_REGS_H_

#define configI2C_MAX_SPEED      (400000)  /* Highest I2C speed */
#define configI2C_CLOCK_HZ       (150000)  /* I2C reference clock in Khz */
#define configI2C_FS_GLITCH_FILTER  (configI2C_CLOCK_HZ / 20000) // effectively 1/50ns / 1/CLK)
#define configI2C_HS_GLITCH_FILTER  (configI2C_CLOCK_HZ / 100000) // effectively 1/10ns / 1/CLK)

#define SS_SPEED           (100*1000)     //100kbps
#define FS_SPEED           (400*1000)     //400kbps
#define HS_SPEED           (3400*1000)    //3.4Mbps

//------------------------------------------------------------------;
//   DW I2C Bus Registers                                           ;
//------------------------------------------------------------------;
/*
 * Registers offset
 */
#define DW_IC_CON                               (0x0)
#define DW_IC_TAR                               (0x4)
#define DW_IC_SAR                               (0x8)
#define DW_IC_DATA_CMD                          (0x10)
#define DW_IC_SS_SCL_HCNT                       (0x14)
#define DW_IC_SS_SCL_LCNT                       (0x18)
#define DW_IC_FS_SCL_HCNT                       (0x1c)
#define DW_IC_FS_SCL_LCNT                       (0x20)
#define DW_IC_HS_SCL_HCNT                       (0x24)
#define DW_IC_HS_SCL_LCNT                       (0x28)
#define DW_IC_INTR_STAT                         (0x2c)
#define DW_IC_INTR_MASK                         (0x30)
#define DW_IC_RAW_INTR_STAT                     (0x34)
#define DW_IC_CLR_INTR                          (0x40)
#define DW_IC_CLR_RX_UNDER                      (0x44)
#define DW_IC_CLR_RX_OVER                       (0x48)
#define DW_IC_CLR_TX_ABRT                       (0x54)
#define DW_IC_CLR_ACTIVITY                      (0x5c)
#define DW_IC_CLR_STOP_DET                      (0x60)
#define DW_IC_CLR_START_DET                     (0x64)
#define DW_IC_ENABLE                            (0x6c)
#define DW_IC_STATUS                            (0x70)
#define DW_IC_TXFLR                             (0x74)
#define DW_IC_RXFLR                             (0x78)
#define DW_IC_SDA_HOLD                          (0x7c)
#define DW_IC_TX_ABRT_SOURCE                    (0x80)
#define DW_IC_ENABLE_STATUS                     (0x9c)
#define DW_IC_FS_SPKLEN                         (0xa0)
#define DW_IC_HS_SPKLEN                         (0xa4)
#define DW_IC_CLR_RESTART_DET                   (0xa8)
#define DW_IC_COMP_PARAM_1                      (0xf4)
#define DW_IC_COMP_TYPE                         (0xfc)

// I2C Control Register
#define DW_I2C_CON_MASTER_MODE                  (1 << 0)
#define DW_I2C_CON_SPEED_MASK                   (0x0006UL)
#define DW_I2C_CON_SPEED_SHIFT                  (1)
#define DW_I2C_CON_SPEED_SS                     (1 << 1)
#define DW_I2C_CON_SPEED_FS                     (1 << 2)
#define DW_I2C_CON_SPEED_HS                     ((1 << 1) | (1 << 2))
#define DW_I2C_CON_IC_10BITADDR_SLAVE           (1 << 3)
#define DW_I2C_CON_IC_10BITADDR_MASTER          (1 << 4)
#define DW_I2C_CON_IC_RESTART_EN                (1 << 5)
#define DW_I2C_CON_IC_SLAVE_DISABLE             (1 << 6)
#define DW_I2C_CON_STOP_DET_IFADDRESSED         (1 << 7)
#define DW_I2C_CON_TX_EMPTY_CTRL                (1 << 8)

#define DW_IC_CON_MASTER                        (0x1)
#define DW_IC_CON_SPEED_STD                     (0x2)
#define DW_IC_CON_SPEED_FAST                    (0x4)
#define DW_IC_CON_10BITADDR_MASTER              (0x10)
#define DW_IC_CON_RESTART_EN                    (0x20)
#define DW_IC_CON_SLAVE_DISABLE                 (0x40)

#define DW_IC_TAR_10BITS                        (1 << 12)

#define DW_IC_INTR_RX_UNDER                     (0x01)
#define DW_IC_INTR_RX_OVER                      (0x02)
#define DW_IC_INTR_TX_EMPTY                     (0x10)
#define DW_IC_INTR_TX_ABRT                      (0x40)
#define DW_IC_INTR_ACTIVITY                     (0x100)
#define DW_IC_INTR_STOP_DET                     (0x200)
#define DW_IC_INTR_START_DET                    (0x400)
#define DW_IC_ERR_CONDITION  (DW_IC_INTR_RX_UNDER | \
         DW_IC_INTR_RX_OVER | \
         DW_IC_INTR_TX_ABRT)

#define DW_IC_STATUS_ACTIVITY                   (0x1)

#define DW_IC_ERR_TX_ABRT                       (0x1)


// I2C Rx/Tx Data Buffer and Command Register
#define DW_I2C_DATA_MASK                        (0x00FFUL)
#define DW_I2C_DATA_CMD                         (1 << 8)
#define DW_I2C_DATA_STOP                        (1 << 9)
#define DW_I2C_DATA_RESTART                     (1 << 10)

// I2C Enable
#define DW_I2C_ENABLE                           (1 << 0)
#define DW_I2C_ABORT                            (1 << 1)

// I2C Status register
#define DW_I2C_STATUS_ACTIVITY                  (1 << 0)
#define DW_I2C_STATUS_TFNF                      (1 << 1)
#define DW_I2C_STATUS_TFE                       (1 << 2)
#define DW_I2C_STATUS_RFNE                      (1 << 3)
#define DW_I2C_STATUS_RFF                       (1 << 4)
#define DW_I2C_STATUS_MST_ACTIVITY              (1 << 5)
#define DW_I2C_STATUS_SLV_ACTIVITY              (1 << 6)

/*
 * status codes
 */
#define STATUS_IDLE                             (0x0)
#define STATUS_WRITE_IN_PROGRESS                (0x1)
#define STATUS_READ_IN_PROGRESS                 (0x2)

/* timeout and retry values */
#define DW_BUS_WAIT_TIMEOUT                     (80) /* ms */
#define DW_RX_DATA_RETRY                        (80)
#define DW_TX_DATA_RETRY                        (80)
#define DW_STATUS_WAIT_RETRY                    (40)
#define DW_BUS_WAIT_INACTIVE                    (80)

/*
 * hardware abort codes from the DW_IC_TX_ABRT_SOURCE register
 *
 * only expected abort codes are listed here
 * refer to the datasheet for the full list
 */
#define ABRT_7B_ADDR_NOACK                      (0)
#define ABRT_10ADDR1_NOACK                      (1)
#define ABRT_10ADDR2_NOACK                      (2)
#define ABRT_TXDATA_NOACK                       (3)
#define ABRT_GCALL_NOACK                        (4)
#define ABRT_GCALL_READ                         (5)
#define ABRT_SBYTE_ACKDET                       (7)
#define ABRT_SBYTE_NORSTRT                      (9)
#define ABRT_10B_RD_NORSTRT                     (10)
#define ARB_MASTER_DIS                          (11)
#define ARB_LOST                                (12)
#define ARB_OK                                  (0xFF)

// I2C Enable Status Register
#define DW_I2C_EN_STATUS_IC_EN                  (1 << 0)
#define DW_I2C_EN_STATUS_SLV_DIS_WHILE_BUSY     (1 << 1)
#define DW_I2C_EN_STATUS_SLV_RX_DATA_LOST       (1 << 2)

#define CHECK_IC_EN_HIGH                        (1 << 0)
#define CHECK_IC_EN_LOW                         (0 << 0)

// ISS and FS spike suppression limit
// HS spike suppression limit
#define DW_I2C_SPKLEN_MASK                      (0x000000FFUL)

// Component Parameter Register
#define DW_I2C_APB_DATA_WIDTH_MASK              (0x00000003UL)
#define DW_I2C_APB_DATA_WIDTH_SHIFT             (0)
#define DW_I2C_MAX_SPEED_MODE_MASK              (0x0000000CUL)
#define DW_I2C_MAX_SPEED_MODE_SHIFT             (1 << 2)
#define DW_I2C_HC_COUNT_VALUES                  (1 << 4)
#define DW_I2C_INTR_IO                          (1 << 5)
#define DW_I2C_HAS_DMA                          (1 << 6)
#define DW_I2C_ADD_ENCODED_PARAMS               (1 << 7)
#define DW_I2C_RX_BUFFER_DEPTH_MASK             (0x0000FF00UL)
#define DW_I2C_RX_BUFFER_DEPTH_SHIFT            (8)
#define DW_I2C_TX_BUFFER_DEPTH_MASK             (0x00FF0000UL)
#define DW_I2C_TX_BUFFER_DEPTH_SHIFT            (16)

#define I2C_FLAG_SMBUS_OPERATION_MASK           (0xFFFF0000)
#define I2C_FLAG_SMBUS_CMD_MASK                 (0x0000FFFE)

#define configXGBEI2C_FS_GLITCH_FILTER  0x3A

#endif  //_DWI2C_REGS_H_

