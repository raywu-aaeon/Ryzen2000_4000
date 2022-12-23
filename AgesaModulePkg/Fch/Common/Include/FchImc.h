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


#ifndef _FCHIMC_H_
#define _FCHIMC_H_

#pragma pack (push, 1)
//
// IMC Message Register Software Interface
//
#define CPU_MISC_BUS_DEV_FUN          ((0x18 << 3) + 3)

#define MSG_SYS_TO_IMC                0x80
#define Fun_80                        0x80
#define Fun_81                        0x81
#define Fun_82                        0x82
#define Fun_83                        0x83
#define Fun_84                        0x84
#define Fun_85                        0x85
#define Fun_86                        0x86
#define Fun_87                        0x87
#define Fun_88                        0x88
#define Fun_89                        0x89
#define Fun_8B                        0x8B
#define Fun_8C                        0x8C
#define Fun_90                        0x90
#define MSG_IMC_TO_SYS                0x81
#define MSG_REG0                      0x82
#define MSG_REG1                      0x83
#define MSG_REG2                      0x84
#define MSG_REG3                      0x85
#define MSG_REG4                      0x86
#define MSG_REG5                      0x87
#define MSG_REG6                      0x88
#define MSG_REG7                      0x89
#define MSG_REG8                      0x8A
#define MSG_REG9                      0x8B
#define MSG_REGA                      0x8C
#define MSG_REGB                      0x8D
#define MSG_REGC                      0x8E
#define MSG_REGD                      0x8F

#define DISABLED                      0
#define ENABLED                       1



///
/// EC structure
///
typedef struct _FCH_EC {
  UINT8                 MsgFun81Zone0MsgReg0;           ///<Thermal zone
  UINT8                 MsgFun81Zone0MsgReg1;           ///<Thermal zone
  UINT8                 MsgFun81Zone0MsgReg2;           ///<Thermal zone control byte 1
  UINT8                 MsgFun81Zone0MsgReg3;           ///<Thermal zone control byte 2
  UINT8                 MsgFun81Zone0MsgReg4;           ///<Bit[3:0] - Thermal diode offset adjustment in degrees Celsius.
  UINT8                 MsgFun81Zone0MsgReg5;           ///<Hysteresis information
  UINT8                 MsgFun81Zone0MsgReg6;           ///<SMBUS Address for SMBUS based temperature sensor such as SB-TSI and ADM1032
  UINT8                 MsgFun81Zone0MsgReg7;           ///<Bit[1:0]: 0 - 2,  SMBUS bus number where the SMBUS based temperature sensor is located.
  UINT8                 MsgFun81Zone0MsgReg8;           ///<Fan PWM stepping rate in unit of PWM level percentage
  UINT8                 MsgFun81Zone0MsgReg9;           ///<Fan PWM ramping rate in 5ms unit
//
// EC LDN9 function 81 zone 1
//
  UINT8                 MsgFun81Zone1MsgReg0;           ///<Thermal zone
  UINT8                 MsgFun81Zone1MsgReg1;           ///<Thermal zone
  UINT8                 MsgFun81Zone1MsgReg2;           ///<Thermal zone control byte 1
  UINT8                 MsgFun81Zone1MsgReg3;           ///<Thermal zone control byte 2
  UINT8                 MsgFun81Zone1MsgReg4;           ///<Bit[3:0] - Thermal diode offset adjustment in degrees Celsius.
  UINT8                 MsgFun81Zone1MsgReg5;           ///<Hysteresis information
  UINT8                 MsgFun81Zone1MsgReg6;           ///<SMBUS Address for SMBUS based temperature sensor such as SB-TSI and ADM1032
  UINT8                 MsgFun81Zone1MsgReg7;           ///<Bit[1:0]: 0 - 2,  SMBUS bus number where the SMBUS based temperature sensor is located.
  UINT8                 MsgFun81Zone1MsgReg8;           ///<Fan PWM stepping rate in unit of PWM level percentage
  UINT8                 MsgFun81Zone1MsgReg9;           ///<Fan PWM ramping rate in 5ms unit
//
//EC LDN9 function 81 zone 2
//
  UINT8                 MsgFun81Zone2MsgReg0;           ///<Thermal zone
  UINT8                 MsgFun81Zone2MsgReg1;           ///<Thermal zone
  UINT8                 MsgFun81Zone2MsgReg2;           ///<Thermal zone control byte 1
  UINT8                 MsgFun81Zone2MsgReg3;           ///<Thermal zone control byte 2
  UINT8                 MsgFun81Zone2MsgReg4;           ///<Bit[3:0] - Thermal diode offset adjustment in degrees Celsius.
  UINT8                 MsgFun81Zone2MsgReg5;           ///<Hysteresis information
  UINT8                 MsgFun81Zone2MsgReg6;           ///<SMBUS Address for SMBUS based temperature sensor such as SB-TSI and ADM1032
  UINT8                 MsgFun81Zone2MsgReg7;           ///<Bit[1:0]: 0 - 2,  SMBUS bus number where the SMBUS based temperature sensor is located.
  UINT8                 MsgFun81Zone2MsgReg8;           ///<Fan PWM stepping rate in unit of PWM level percentage
  UINT8                 MsgFun81Zone2MsgReg9;           ///<Fan PWM ramping rate in 5ms unit
//
//EC LDN9 function 81 zone 3
//
  UINT8                 MsgFun81Zone3MsgReg0;           ///<Thermal zone
  UINT8                 MsgFun81Zone3MsgReg1;           ///<Thermal zone
  UINT8                 MsgFun81Zone3MsgReg2;           ///<Thermal zone control byte 1
  UINT8                 MsgFun81Zone3MsgReg3;           ///<Thermal zone control byte 2
  UINT8                 MsgFun81Zone3MsgReg4;           ///<Bit[3:0] - Thermal diode offset adjustment in degrees Celsius.
  UINT8                 MsgFun81Zone3MsgReg5;           ///<Hysteresis information
  UINT8                 MsgFun81Zone3MsgReg6;           ///<SMBUS Address for SMBUS based temperature sensor such as SB-TSI and ADM1032
  UINT8                 MsgFun81Zone3MsgReg7;           ///<Bit[1:0]: 0 - 2,  SMBUS bus number where the SMBUS based temperature sensor is located.
  UINT8                 MsgFun81Zone3MsgReg8;           ///<Fan PWM stepping rate in unit of PWM level percentage
  UINT8                 MsgFun81Zone3MsgReg9;           ///<Fan PWM ramping rate in 5ms unit
//
//EC LDN9 function 83 zone 0
//
  UINT8                 MsgFun83Zone0MsgReg0;           ///<Thermal zone
  UINT8                 MsgFun83Zone0MsgReg1;           ///<Thermal zone
  UINT8                 MsgFun83Zone0MsgReg2;           ///<_AC0
  UINT8                 MsgFun83Zone0MsgReg3;           ///<_AC1
  UINT8                 MsgFun83Zone0MsgReg4;           ///<_AC2
  UINT8                 MsgFun83Zone0MsgReg5;           ///<_AC3
  UINT8                 MsgFun83Zone0MsgReg6;           ///<_AC4
  UINT8                 MsgFun83Zone0MsgReg7;           ///<_AC5
  UINT8                 MsgFun83Zone0MsgReg8;           ///<_AC6
  UINT8                 MsgFun83Zone0MsgReg9;           ///<_AC7
  UINT8                 MsgFun83Zone0MsgRegA;           ///<_CRT
  UINT8                 MsgFun83Zone0MsgRegB;           ///<_PSV
//
//EC LDN9 function 83 zone 1
//
  UINT8                 MsgFun83Zone1MsgReg0;           ///<Thermal zone
  UINT8                 MsgFun83Zone1MsgReg1;           ///<Thermal zone
  UINT8                 MsgFun83Zone1MsgReg2;           ///<_AC0
  UINT8                 MsgFun83Zone1MsgReg3;           ///<_AC1
  UINT8                 MsgFun83Zone1MsgReg4;           ///<_AC2
  UINT8                 MsgFun83Zone1MsgReg5;           ///<_AC3
  UINT8                 MsgFun83Zone1MsgReg6;           ///<_AC4
  UINT8                 MsgFun83Zone1MsgReg7;           ///<_AC5
  UINT8                 MsgFun83Zone1MsgReg8;           ///<_AC6
  UINT8                 MsgFun83Zone1MsgReg9;           ///<_AC7
  UINT8                 MsgFun83Zone1MsgRegA;           ///<_CRT
  UINT8                 MsgFun83Zone1MsgRegB;           ///<_PSV
//
//EC LDN9 function 83 zone 2
//
  UINT8                 MsgFun83Zone2MsgReg0;           ///<Thermal zone
  UINT8                 MsgFun83Zone2MsgReg1;           ///<Thermal zone
  UINT8                 MsgFun83Zone2MsgReg2;           ///<_AC0
  UINT8                 MsgFun83Zone2MsgReg3;           ///<_AC1
  UINT8                 MsgFun83Zone2MsgReg4;           ///<_AC2
  UINT8                 MsgFun83Zone2MsgReg5;           ///<_AC3
  UINT8                 MsgFun83Zone2MsgReg6;           ///<_AC4
  UINT8                 MsgFun83Zone2MsgReg7;           ///<_AC5
  UINT8                 MsgFun83Zone2MsgReg8;           ///<_AC6
  UINT8                 MsgFun83Zone2MsgReg9;           ///<_AC7
  UINT8                 MsgFun83Zone2MsgRegA;           ///<_CRT
  UINT8                 MsgFun83Zone2MsgRegB;           ///<_PSV
//
//EC LDN9 function 83 zone 3
//
  UINT8                 MsgFun83Zone3MsgReg0;           ///<Thermal zone
  UINT8                 MsgFun83Zone3MsgReg1;           ///<Thermal zone
  UINT8                 MsgFun83Zone3MsgReg2;           ///<_AC0
  UINT8                 MsgFun83Zone3MsgReg3;           ///<_AC1
  UINT8                 MsgFun83Zone3MsgReg4;           ///<_AC2
  UINT8                 MsgFun83Zone3MsgReg5;           ///<_AC3
  UINT8                 MsgFun83Zone3MsgReg6;           ///<_AC4
  UINT8                 MsgFun83Zone3MsgReg7;           ///<_AC5
  UINT8                 MsgFun83Zone3MsgReg8;           ///<_AC6
  UINT8                 MsgFun83Zone3MsgReg9;           ///<_AC7
  UINT8                 MsgFun83Zone3MsgRegA;           ///<_CRT
  UINT8                 MsgFun83Zone3MsgRegB;           ///<_PSV
//
//EC LDN9 function 85 zone 0
//
  UINT8                 MsgFun85Zone0MsgReg0;           ///<Thermal zone
  UINT8                 MsgFun85Zone0MsgReg1;           ///<Thermal zone
  UINT8                 MsgFun85Zone0MsgReg2;           ///<AL0 PWM level in percentage (0 - 100%)
  UINT8                 MsgFun85Zone0MsgReg3;           ///<AL1 PWM level in percentage (0 - 100%)
  UINT8                 MsgFun85Zone0MsgReg4;           ///<AL2 PWM level in percentage (0 - 100%)
  UINT8                 MsgFun85Zone0MsgReg5;           ///<AL3 PWM level in percentage (0 - 100%)
  UINT8                 MsgFun85Zone0MsgReg6;           ///<AL4 PWM level in percentage (0 - 100%)
  UINT8                 MsgFun85Zone0MsgReg7;           ///<AL5 PWM level in percentage (0 - 100%)
  UINT8                 MsgFun85Zone0MsgReg8;           ///<AL6 PWM level in percentage (0 - 100%)
  UINT8                 MsgFun85Zone0MsgReg9;           ///<AL7 PWM level in percentage (0 - 100%)
//
//EC LDN9 function 85 zone 1
//
  UINT8                 MsgFun85Zone1MsgReg0;           ///<Thermal zone
  UINT8                 MsgFun85Zone1MsgReg1;           ///<Thermal zone
  UINT8                 MsgFun85Zone1MsgReg2;           ///<AL0 PWM level in percentage (0 - 100%)
  UINT8                 MsgFun85Zone1MsgReg3;           ///<AL1 PWM level in percentage (0 - 100%)
  UINT8                 MsgFun85Zone1MsgReg4;           ///<AL2 PWM level in percentage (0 - 100%)
  UINT8                 MsgFun85Zone1MsgReg5;           ///<AL3 PWM level in percentage (0 - 100%)
  UINT8                 MsgFun85Zone1MsgReg6;           ///<AL4 PWM level in percentage (0 - 100%)
  UINT8                 MsgFun85Zone1MsgReg7;           ///<AL5 PWM level in percentage (0 - 100%)
  UINT8                 MsgFun85Zone1MsgReg8;           ///<AL6 PWM level in percentage (0 - 100%)
  UINT8                 MsgFun85Zone1MsgReg9;           ///<AL7 PWM level in percentage (0 - 100%)
//
//EC LDN9 function 85 zone 2
//
  UINT8                 MsgFun85Zone2MsgReg0;           ///<Thermal zone
  UINT8                 MsgFun85Zone2MsgReg1;           ///<Thermal zone
  UINT8                 MsgFun85Zone2MsgReg2;           ///<AL0 PWM level in percentage (0 - 100%)
  UINT8                 MsgFun85Zone2MsgReg3;           ///<AL1 PWM level in percentage (0 - 100%)
  UINT8                 MsgFun85Zone2MsgReg4;           ///<AL2 PWM level in percentage (0 - 100%)
  UINT8                 MsgFun85Zone2MsgReg5;           ///<AL3 PWM level in percentage (0 - 100%)
  UINT8                 MsgFun85Zone2MsgReg6;           ///<AL4 PWM level in percentage (0 - 100%)
  UINT8                 MsgFun85Zone2MsgReg7;           ///<AL5 PWM level in percentage (0 - 100%)
  UINT8                 MsgFun85Zone2MsgReg8;           ///<AL6 PWM level in percentage (0 - 100%)
  UINT8                 MsgFun85Zone2MsgReg9;           ///<AL7 PWM level in percentage (0 - 100%)
//
//EC LDN9 function 85 zone 3
//
  UINT8                 MsgFun85Zone3MsgReg0;           ///<Thermal zone
  UINT8                 MsgFun85Zone3MsgReg1;           ///<Thermal zone
  UINT8                 MsgFun85Zone3MsgReg2;           ///<AL0 PWM level in percentage (0 - 100%)
  UINT8                 MsgFun85Zone3MsgReg3;           ///<AL1 PWM level in percentage (0 - 100%)
  UINT8                 MsgFun85Zone3MsgReg4;           ///<AL2 PWM level in percentage (0 - 100%)
  UINT8                 MsgFun85Zone3MsgReg5;           ///<AL3 PWM level in percentage (0 - 100%)
  UINT8                 MsgFun85Zone3MsgReg6;           ///<AL4 PWM level in percentage (0 - 100%)
  UINT8                 MsgFun85Zone3MsgReg7;           ///<AL5 PWM level in percentage (0 - 100%)
  UINT8                 MsgFun85Zone3MsgReg8;           ///<AL6 PWM level in percentage (0 - 100%)
  UINT8                 MsgFun85Zone3MsgReg9;           ///<AL7 PWM level in percentage (0 - 100%)
//
//EC LDN9 function 89 TEMPIN channel 0
//
  UINT8                 MsgFun89Zone0MsgReg0;           ///<Thermal zone
  UINT8                 MsgFun89Zone0MsgReg1;           ///<Thermal zone
  UINT8                 MsgFun89Zone0MsgReg2;           ///<At DWORD bit 0-7
  UINT8                 MsgFun89Zone0MsgReg3;           ///<At DWORD bit 15-8
  UINT8                 MsgFun89Zone0MsgReg4;           ///<At DWORD bit 23-16
  UINT8                 MsgFun89Zone0MsgReg5;           ///<At DWORD bit 31-24
  UINT8                 MsgFun89Zone0MsgReg6;           ///<Ct DWORD bit 0-7
  UINT8                 MsgFun89Zone0MsgReg7;           ///<Ct DWORD bit 15-8
  UINT8                 MsgFun89Zone0MsgReg8;           ///<Ct DWORD bit 23-16
  UINT8                 MsgFun89Zone0MsgReg9;           ///<Ct DWORD bit 31-24
  UINT8                 MsgFun89Zone0MsgRegA;           ///<Mode bit 0-7
//
//EC LDN9 function 89 TEMPIN channel 1
//
  UINT8                 MsgFun89Zone1MsgReg0;           ///<Thermal zone
  UINT8                 MsgFun89Zone1MsgReg1;           ///<Thermal zone
  UINT8                 MsgFun89Zone1MsgReg2;           ///<At DWORD bit 0-7
  UINT8                 MsgFun89Zone1MsgReg3;           ///<At DWORD bit 15-8
  UINT8                 MsgFun89Zone1MsgReg4;           ///<At DWORD bit 23-16
  UINT8                 MsgFun89Zone1MsgReg5;           ///<At DWORD bit 31-24
  UINT8                 MsgFun89Zone1MsgReg6;           ///<Ct DWORD bit 0-7
  UINT8                 MsgFun89Zone1MsgReg7;           ///<Ct DWORD bit 15-8
  UINT8                 MsgFun89Zone1MsgReg8;           ///<Ct DWORD bit 23-16
  UINT8                 MsgFun89Zone1MsgReg9;           ///<Ct DWORD bit 31-24
  UINT8                 MsgFun89Zone1MsgRegA;           ///<Mode bit 0-7
//
//EC LDN9 function 89 TEMPIN channel 2
//
  UINT8                 MsgFun89Zone2MsgReg0;           ///<Thermal zone
  UINT8                 MsgFun89Zone2MsgReg1;           ///<Thermal zone
  UINT8                 MsgFun89Zone2MsgReg2;           ///<At DWORD bit 0-7
  UINT8                 MsgFun89Zone2MsgReg3;           ///<At DWORD bit 15-8
  UINT8                 MsgFun89Zone2MsgReg4;           ///<At DWORD bit 23-16
  UINT8                 MsgFun89Zone2MsgReg5;           ///<At DWORD bit 31-24
  UINT8                 MsgFun89Zone2MsgReg6;           ///<Ct DWORD bit 0-7
  UINT8                 MsgFun89Zone2MsgReg7;           ///<Ct DWORD bit 15-8
  UINT8                 MsgFun89Zone2MsgReg8;           ///<Ct DWORD bit 23-16
  UINT8                 MsgFun89Zone2MsgReg9;           ///<Ct DWORD bit 31-24
  UINT8                 MsgFun89Zone2MsgRegA;           ///<Mode bit 0-7
//
//EC LDN9 function 89 TEMPIN channel 3
//
  UINT8                 MsgFun89Zone3MsgReg0;           ///<Thermal zone
  UINT8                 MsgFun89Zone3MsgReg1;           ///<Thermal zone
  UINT8                 MsgFun89Zone3MsgReg2;           ///<At DWORD bit 0-7
  UINT8                 MsgFun89Zone3MsgReg3;           ///<At DWORD bit 15-8
  UINT8                 MsgFun89Zone3MsgReg4;           ///<At DWORD bit 23-16
  UINT8                 MsgFun89Zone3MsgReg5;           ///<At DWORD bit 31-24
  UINT8                 MsgFun89Zone3MsgReg6;           ///<Ct DWORD bit 0-7
  UINT8                 MsgFun89Zone3MsgReg7;           ///<Ct DWORD bit 15-8
  UINT8                 MsgFun89Zone3MsgReg8;           ///<Ct DWORD bit 23-16
  UINT8                 MsgFun89Zone3MsgReg9;           ///<Ct DWORD bit 31-24
  UINT8                 MsgFun89Zone3MsgRegA;           ///<Mode bit 0-7
//
//EC LDN9 function 8C Startup PWM channel 0
//
  UINT8                 MsgFun8CZone0MsgReg0;           ///<Reture 0xFA stands for success
  UINT8                 MsgFun8CZone0MsgReg1;           ///<Bit 2-0 Thermal zone number
  UINT8                 MsgFun8CZone0MsgReg2;           ///<Startup PWM flags; bit0: enable/disable current zone, bit1/2/3: 1 if values in reg3/4/5 are valid.
  UINT8                 MsgFun8CZone0MsgReg3;           ///<Startup PWM (effective range 1~100)
//
//EC LDN9 function 8C Startup PWM channel 1
//
  UINT8                 MsgFun8CZone1MsgReg0;           ///<Reture 0xFA stands for success
  UINT8                 MsgFun8CZone1MsgReg1;           ///<Bit 2-0 Thermal zone number
  UINT8                 MsgFun8CZone1MsgReg2;           ///<Startup PWM flags; bit0: enable/disable current zone, bit1/2/3: 1 if values in reg3/4/5 are valid.
  UINT8                 MsgFun8CZone1MsgReg3;           ///<Startup PWM (effective range 1~100)
//
//EC LDN9 function 8C Startup PWM channel 2
//
  UINT8                 MsgFun8CZone2MsgReg0;           ///<Reture 0xFA stands for success
  UINT8                 MsgFun8CZone2MsgReg1;           ///<Bit 2-0 Thermal zone number
  UINT8                 MsgFun8CZone2MsgReg2;           ///<Startup PWM flags; bit0: enable/disable current zone, bit1/2/3: 1 if values in reg3/4/5 are valid.
  UINT8                 MsgFun8CZone2MsgReg3;           ///<Startup PWM (effective range 1~100)
//
//EC LDN9 function 8C Startup PWM channel 3
//
  UINT8                 MsgFun8CZone3MsgReg0;           ///<Reture 0xFA stands for success
  UINT8                 MsgFun8CZone3MsgReg1;           ///<Bit 2-0 Thermal zone number
  UINT8                 MsgFun8CZone3MsgReg2;           ///<Startup PWM flags; bit0: enable/disable current zone, bit1/2/3: 1 if values in reg3/4/5 are valid.
  UINT8                 MsgFun8CZone3MsgReg3;           ///<Startup PWM (effective range 1~100)
//
// FLAG for Fun83/85/89/8C support
//
  UINT32                IMCFUNSupportBitMap;            ///< Bit0=81FunZone0 support(1=On;0=Off); bit1-3=81FunZone1-Zone3;Bit4-7=83FunZone0-Zone3;Bit8-11=85FunZone0-Zone3;Bit11-15=89FunZone0-Zone3;
} FCH_EC;

///
/// IMC structure
///
typedef struct _FCH_IMC {
  UINT8                 ImcEnable;                      ///< ImcEnable - IMC Enable
  UINT8                 ImcEnabled;                     ///< ImcEnabled - IMC Enable
  UINT8                 ImcSureBootTimer;               ///< ImcSureBootTimer - IMc SureBootTimer function
  FCH_EC                EcStruct;                       ///< EC structure
  UINT8                 ImcEnableOverWrite;             ///< OverWrite IMC with the EC structure
                                                        ///   @li <b>00</b> - by default strapping
                                                        ///   @li <b>01</b> - enable
                                                        ///   @li <b>10</b> - disable
                                                        ///
} FCH_IMC;

#pragma pack (pop)
#endif // _FCHIMC_H_

