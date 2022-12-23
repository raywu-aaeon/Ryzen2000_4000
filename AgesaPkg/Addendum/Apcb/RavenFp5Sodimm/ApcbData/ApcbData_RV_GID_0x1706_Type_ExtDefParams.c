
/* $NoKeywords:$ */
/**
 * @file
 *
 * @e \$Revision:$   @e \$Date:$
 */
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
  **/


#include "MyPorting.h"
#include <RV/APCB.h>
#include <ApcbCustomizedDefinitions.h>
#include <ApcbDefaults.h>

CHAR8 mDummyBuf;

APCB_TYPE_DATA_START_SIGNATURE();
APCB_TYPE_HEADER       ApcbTypeHeader = {
  APCB_GROUP_FCH,
  APCB_FCH_TYPE_CONFIG_DEFAULT_PARAMETERS,
  (
    sizeof (APCB_TYPE_HEADER)
  ),
  0,
  0,
  0
};  // SizeOfType will be fixed up by tool

APCB_PARAM_ATTRIBUTE  ParameterListDefaultsAttribute[] = {
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_FCH_CONSOLE_OUT_ENABLE, sizeof (UINT8) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_FCH_CONSOLE_OUT_SERIAL_PORT, sizeof (UINT8) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_FCH_ASSERT_ENABLE, sizeof (BOOLEAN) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_FCH_TURTLE_BOOT_ENABLE, sizeof (BOOLEAN) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_FCH_ELEVATE_SMBUS_CLOCK, sizeof (BOOLEAN) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_FCH_UART_BAUD_RATE, sizeof (UINT32) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_FCH_ABL_DEBUG_PRINT_SERIAL_PORT_DETECT_EN, sizeof (BOOLEAN) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_FCH_ESPI_ABL_INIT_ENABLE, sizeof (BOOLEAN) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_FCH_ESPI_IO80_ENABLE, sizeof (BOOLEAN) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_FCH_ESPI_KBC6064_ENABLE, sizeof (BOOLEAN) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_FCH_ESPI_CLOCK, sizeof (UINT8) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_FCH_ESPI_IOMODE, sizeof (UINT8) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_FCH_ESPI_ALERT_MODE, sizeof (UINT8) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_FCH_ESPI_IORANGE0_SIZE, sizeof (UINT8) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_FCH_ESPI_IORANGE1_SIZE, sizeof (UINT8) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_FCH_ESPI_IORANGE2_SIZE, sizeof (UINT8) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_FCH_ESPI_IORANGE3_SIZE, sizeof (UINT8) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_FCH_ESPI_IORANGE0_BASE, sizeof (UINT16) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_FCH_ESPI_IORANGE1_BASE, sizeof (UINT16) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_FCH_ESPI_IORANGE2_BASE, sizeof (UINT16) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_FCH_ESPI_IORANGE3_BASE, sizeof (UINT16) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_FCH_ESPI_MMIORANGE0_SIZE, sizeof (UINT16) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_FCH_ESPI_MMIORANGE1_SIZE, sizeof (UINT16) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_FCH_ESPI_MMIORANGE2_SIZE, sizeof (UINT16) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_FCH_ESPI_MMIORANGE3_SIZE, sizeof (UINT16) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_FCH_ESPI_MMIORANGE0_BASE, sizeof (UINT32) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_FCH_ESPI_MMIORANGE1_BASE, sizeof (UINT32) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_FCH_ESPI_MMIORANGE2_BASE, sizeof (UINT32) - 1, 0},
  {APCB_TIME_POINT_ANY, APCB_TOKEN_CONFIG_FCH_ESPI_MMIORANGE3_BASE, sizeof (UINT32) - 1, 0},
  {0, APCB_TOKEN_CONFIG_LIMIT, 0, 0},
};

_1BYTE_ALIGN UINT8  ParameterListDefaultsValue[] = {
  BSU08 (BLDCFG_FCH_CONSOLE_OUT_ENABLE),               //< BMC SOcket Number
  BSU08 (BLDCFG_FCH_CONSOLE_OUT_SERIAL_PORT),          //< BMC Start Lane
  BSBLN (BLDCFG_FCH_ASSERT_ENABLE),                    //< ASSERTs enable
  BSBLN (BLDCFG_FCH_TURTLE_BOOT_ENABLE),               //< Turtle Boot Mode Enable
  BSBLN (BLDCFG_FCH_ELEVATE_SMBUS_CLOCK),              //< Elevate Smbus Clock Enable
  BSU32 (BLDCFG_FCH_UART_BAUD_RATE),                   //< FCH UART Baud rate
  BSBLN (BLDCFG_FCH_ABL_DEBUG_PRINT_SERIAL_PORT_DETECT_EN), //< Debug print cable detect
  BSBLN (BLDCFG_FCH_ESPI_ABL_INIT_ENABLE),
  BSBLN (BLDCFG_FCH_ESPI_IO80_ENABLE),
  BSBLN (BLDCFG_FCH_ESPI_KBC6064_ENABLE),
  BSU08 (BLDCFG_FCH_ESPI_CLOCK),
  BSU08 (BLDCFG_FCH_ESPI_IOMODE),
  BSU08 (BLDCFG_FCH_ESPI_ALERT_MODE),
  BSU08 (BLDCFG_FCH_ESPI_IORANGE0_SIZE),
  BSU08 (BLDCFG_FCH_ESPI_IORANGE1_SIZE),
  BSU08 (BLDCFG_FCH_ESPI_IORANGE2_SIZE),
  BSU08 (BLDCFG_FCH_ESPI_IORANGE3_SIZE),
  BSU16 (BLDCFG_FCH_ESPI_IORANGE0_BASE),
  BSU16 (BLDCFG_FCH_ESPI_IORANGE1_BASE),
  BSU16 (BLDCFG_FCH_ESPI_IORANGE2_BASE),
  BSU16 (BLDCFG_FCH_ESPI_IORANGE3_BASE),
  BSU16 (BLDCFG_FCH_ESPI_MMIORANGE0_SIZE),
  BSU16 (BLDCFG_FCH_ESPI_MMIORANGE1_SIZE),
  BSU16 (BLDCFG_FCH_ESPI_MMIORANGE2_SIZE),
  BSU16 (BLDCFG_FCH_ESPI_MMIORANGE3_SIZE),
  BSU32 (BLDCFG_FCH_ESPI_MMIORANGE0_BASE),
  BSU32 (BLDCFG_FCH_ESPI_MMIORANGE1_BASE),
  BSU32 (BLDCFG_FCH_ESPI_MMIORANGE2_BASE),
  BSU32 (BLDCFG_FCH_ESPI_MMIORANGE3_BASE),
  BSU08 (0xFF)
};

APCB_TYPE_DATA_END_SIGNATURE();


int main(IN int argc, IN char * argv[])
{
  return 0;
}





