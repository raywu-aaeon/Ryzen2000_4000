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
 *******************************************************************************
 */

#ifndef _MP2_I2C_REGS_H_
#define _MP2_I2C_REGS_H_

#define NBIF0EPF7CFGx00000004 0x10147004

//I2C frequency
#define SS_SPEED           (100*1000)     //100kbps
#define FS_SPEED           (400*1000)     //400kbps
#define HS_SPEED           (3400*1000)    //3.4Mbps

//C2P Mailbox
#define MP2_C2PMSG_0      0x03E10500
#define MP2_C2PMSG_1      0x03E10504
#define MP2_C2PMSG_2      0x03E10508
#define MP2_C2PMSG_3      0x03E1050C
#define MP2_C2PMSG_4      0x03E10510
#define MP2_C2PMSG_5      0x03E10514
#define MP2_C2PMSG_6      0x03E10518
#define MP2_C2PMSG_7      0x03E1051C
#define MP2_C2PMSG_8      0x03E10520
#define MP2_C2PMSG_9      0x03E10524
#define MP2_C2PMSG_10     0x03E10528
#define MP2_C2PMSG_11     0x03E1052C
#define MP2_C2PMSG_12     0x03E10530
#define MP2_C2PMSG_13     0x03E10534
#define MP2_C2PMSG_14     0x03E10538 
#define MP2_C2PMSG_15     0x03E1053C

//P2C Mailbox 
#define MP2_P2CMSG_0      0x03E10680 
#define MP2_P2CMSG_1      0x03E10684
#define MP2_P2CMSG_2      0x03E10688
#define MP2_P2CMSG_3      0x03E1068C
#define MP2_P2CMSG_INTEN  0x03E10690  ///< shall be enabled by the MP2 firmware to generate interrupt.
#define MP2_P2CMSG_INTSTS 0x03E10694 

typedef union {
  UINT32                          Raw;                        ///< MP2 I2C Command Reg
  struct {                                                    ///
    UINT32                        i2c_cmd:4;                  ///< I2c read write command
    UINT32                        i2cBusId :4;                ///< I2c bus index 
    UINT32                        devAddr:8;                  ///< Device address or Bus Speed
    UINT32                        length:12;                  ///< Read/write length 
    UINT32                        i2cSpeed:3;                 ///< Register address to be removed later
    UINT32                        memTypeI2cMode:1;           ///< Mem type or I2C 7bit/10bit mode 
  }                               Field;                      ///
} AMD_MP2_I2C_CMD_REG; 

typedef union {
  UINT32                          Raw;                        ///< MP2 I2C Command Reg
  struct {                                                    ///
    UINT32                        response:2;                 ///< I2C response_type
    UINT32                        status:5;                   ///< Status_type
    UINT32                        memType:1;                  ///< 0-output in DRAM,1-Output in C2PMsg
    UINT32                        i2cBusId:4;                 ///< I2C Bus ID
    UINT32                        Reserved:4;                 ///< Reserved
    UINT32                        length:14;                  ///< Length
    UINT32                        Dbg:2;                      ///< Debug message include in p2c msg 1-2 
  }                               Field;                      ///
} AMD_MP2_I2C_RESPOND_REG;

typedef enum speedEnum {
  speed100k  = 0,
  speed400k  = 1,
  speed1000k = 2,
  speed1400k = 3,
  speed3400k = 4
}speedEnum;

typedef enum i2c_cmd {
  i2cRead,
  i2cWrite,
  i2cEnable,
  i2cDisable,
  NumberOfSensorDiscovered,
  isMP2Active,
  InvalidCommand=0xF,
}i2c_cmd;

typedef enum response_type {
  InvalidResponse= 0,
  CommandSuccess = 1,
  CommandFailed  = 2,
}response_type;

typedef enum status_type {
  I2CReadCompleteEvent  = 0,
  I2CReadFailEvent      = 1,
  I2CWriteCompleteEvent = 2,
  I2CWriteFailEvent     = 3,
  I2CBusEnableComplete  = 4,
  I2CBusEnableFailed    = 5,
  I2CBusDisableComplete = 6,
  I2CBusDisableFailed   = 7,
  Invalid_Data_Length   = 8,
  Invalid_Slave_Address = 9,
  Invalid_I2CBus_Id     = 10,
  Invalid_DRAM_Addr     = 11,
  Invalid_Command       = 12,
  MP2Active             = 13,
  NumberOfSensorsDiscoveredResp = 14,
  I2CBusNotInitialized
}status_type;

typedef enum i2c_bus_index{
  I2C_BUS_0 = 0,
  I2C_BUS_1 = 1,
  I2C_BUS_MAX
}i2c_bus_index;

typedef enum mem_type {
  useDRAM   = 0,
  useC2PMsg = 1,
}mem_type;

#endif

