/**
 * @file
 *
 * AMD Integrated Debug Debug_library Routines
 *
 * Contains the functions related to serial port output
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  IDS
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-10 02:28:05 +0800 (Wed, 10 Dec 2014) $
 */
/*****************************************************************************
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

 /*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include <Uefi.h>
#include <Pi/PiMultiPhase.h>
#include <Library/AmdBaseLib.h>
#include <Library/AmdIdsDebugPrintLib.h>
#include <AmdIdsDebugPrintLocal.h>
#include <Filecode.h>

#define FILECODE LIBRARY_AMDIDSDEBUGPRINTLIB_AMDIDSDPSERIAL_FILECODE

#define IDS_SERIAL_PORT (PcdGet64(PcdAmdIdsDebugPrintSerialPort))

#define IDS_SERIAL_PORT_LSR \
(IDS_SERIAL_PORT > 0xFFFF ? \
(IDS_SERIAL_PORT + 5*4) : \
(IDS_SERIAL_PORT + 5))

#define IDS_LSR_TRANSMIT_HOLDING_REGISTER_EMPTY_MASK BIT5

#define IDS_SERIAL_PORT_LSR_READ(Value) \
(IDS_SERIAL_PORT > 0xFFFF ? \
LibAmdMemRead (AccessWidth8, (UINT64) IDS_SERIAL_PORT_LSR, &Value, NULL) : \
LibAmdIoRead (AccessWidth8, (UINT16) IDS_SERIAL_PORT_LSR, &Value, NULL))

#define IDS_SERIAL_PORT_WRITE(ByteSended) \
(IDS_SERIAL_PORT > 0xFFFF ? \
LibAmdMemWrite (AccessWidth8, (UINT64) IDS_SERIAL_PORT, &ByteSended, NULL) : \
LibAmdIoWrite (AccessWidth8, (UINT16) IDS_SERIAL_PORT, &ByteSended, NULL))

#define IDS_SERIAL_PORT_MSR \
(IDS_SERIAL_PORT > 0xFFFF ? \
(IDS_SERIAL_PORT + 6*4) : \
(IDS_SERIAL_PORT + 6))

#define IDS_SERIAL_PORT_MSR_MASK     (BIT4 + BIT5)

#define IDS_SERIAL_PORT_MSR_READ(Value) \
(IDS_SERIAL_PORT > 0xFFFF ? \
LibAmdMemRead(AccessWidth8, (UINT64) IDS_SERIAL_PORT_MSR, &Value, NULL) : \
LibAmdIoRead(AccessWidth8, (UINT16) IDS_SERIAL_PORT_MSR, &Value, NULL))

/**
 *  Determine whether IDS console is enabled.
 *
 *
 *  @retval       TRUE    Alway return true
 *
 **/
BOOLEAN
AmdIdsDpSerialSupport (
  VOID
  )
{
  UINT8 Value;

  if (PcdGetBool (PcdAmdIdsDebugPrintSerialPortEnable)) {
    if (PcdGetBool (PcdAmdIdsDebugPrintSerialPortDetectCableConnection) ) {
      // Wait for both DSR and CTS to be set
      //   DSR is set if a cable is connected.
      //   CTS is set if it is ok to transmit data
      IDS_SERIAL_PORT_MSR_READ (Value);
      if ((Value == 0xFF) || ((Value & IDS_SERIAL_PORT_MSR_MASK) != IDS_SERIAL_PORT_MSR_MASK)) {
        return FALSE;
      }
    }
    return TRUE;
  }
  return FALSE;
}

VOID
AmdIdsDpSerialConstructor (
  VOID
  )
{
  return;
}

/**
 *  Get Serial customize Filter
 *
 *  @param[in,out] Filter    Filter do be filled
 *
 *  @retval       FALSE    Alway return FALSE
 *
 **/
BOOLEAN
AmdIdsDpSerialGetFilter (
  IN OUT   UINT64 *Filter
  )
{
  return FALSE;
}

/**
 *  Send byte to  Serial Port
 *
 *  Before use this routine, please make sure Serial Communications Chip have been initialed
 *
 *  @param[in] ByteSended   Byte to be sended
 *
 *  @retval       TRUE    Byte sended successfully
 *  @retval       FALSE   Byte sended failed
 *
 **/
BOOLEAN
AmdIdsDpSerialSendByte (
  IN      CHAR8   ByteSended
  )
{
  UINT32 RetryCount;
  UINT8 Value;

  // Wait until LSR.Bit5 (Transmitter holding register Empty)
  RetryCount = 2000;
  do {
    IDS_SERIAL_PORT_LSR_READ (Value);
    RetryCount--;
  } while (((Value & IDS_LSR_TRANSMIT_HOLDING_REGISTER_EMPTY_MASK) == 0) && (RetryCount > 0));

  if (RetryCount == 0) {
    // Time expired
    return FALSE;
  } else {
    IDS_SERIAL_PORT_WRITE (ByteSended);
    return TRUE;
  }
}


/**
 *  Print formated string
 *
 *  @param[in] Buffer  - Point to input buffer
 *  @param[in] BufferSize  - Buffer size
 *
**/
VOID
AmdIdsDpSerialPrint (
  IN      CHAR8   *Buffer,
  IN      UINTN BufferSize
  )
{
  BOOLEAN SendStatus;
  while (BufferSize--) {
    SendStatus = AmdIdsDpSerialSendByte (*Buffer);
    Buffer ++;
  }
}


CONST AMD_IDS_DEBUG_PRINT_INSTANCE   AmdIdsDebugPrintSerialInstance =
{
  AmdIdsDpSerialSupport,
  AmdIdsDpSerialConstructor,
  AmdIdsDpSerialGetFilter,
  AmdIdsDpSerialPrint
};




