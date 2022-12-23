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
  *
 */

#include <Filecode.h>
#include <PiPei.h>
#include <Library/AmdBaseLib.h>
#include <Library/AmdErrorLogLib.h>

#define FILECODE LIBRARY_AMDERRORLOGLIB_AMDERRORLOGLIB_FILECODE

/*----------------------------------------------------------------------------
 *                          DEFINITIONS AND MACROS
 *
 *----------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------
 *                           TYPEDEFS AND STRUCTURES
 *
 *----------------------------------------------------------------------------
 */

VOID
AquireErrorLog (
  IN       AMD_ERROR_BUFFER *ErrorLogBuffer,
  IN OUT   ERROR_LOG_DATA_STRUCT *ErrorLogDataPtr
  )
{
  UINT32        ErrorLogCounter;
  UINT16        Index;

  ErrorLogCounter = 0;
  LibAmdMemFill (ErrorLogDataPtr, 0, sizeof (ERROR_LOG_DATA_STRUCT), NULL);
  while (!((ErrorLogBuffer->ReadRecordPtr == ErrorLogBuffer->WriteRecordPtr) && (ErrorLogBuffer->ReadWriteFlag == 1))) {
    Index = ErrorLogBuffer->ReadRecordPtr;
    // ErrorLogCounter is start from 0
    ErrorLogDataPtr->ErrorLog_Param[ErrorLogCounter].ErrorClass = ErrorLogBuffer->AmdErrorStruct[Index].AmdError.ErrorClass;
    ErrorLogDataPtr->ErrorLog_Param[ErrorLogCounter].ErrorInfo  = ErrorLogBuffer->AmdErrorStruct[Index].AmdError.ErrorInfo;
    ErrorLogDataPtr->ErrorLog_Param[ErrorLogCounter].DataParam1 = ErrorLogBuffer->AmdErrorStruct[Index].AmdError.DataParam1;
    ErrorLogDataPtr->ErrorLog_Param[ErrorLogCounter].DataParam2 = ErrorLogBuffer->AmdErrorStruct[Index].AmdError.DataParam2;
    ErrorLogDataPtr->ErrorLog_Param[ErrorLogCounter].DataParam3 = ErrorLogBuffer->AmdErrorStruct[Index].AmdError.DataParam3;
    ErrorLogDataPtr->ErrorLog_Param[ErrorLogCounter].DataParam4 = ErrorLogBuffer->AmdErrorStruct[Index].AmdError.DataParam4;
    if (ErrorLogBuffer->ReadRecordPtr == (TOTAL_ERROR_LOG_BUFFERS - 1)) {
      ErrorLogBuffer->ReadRecordPtr = 0;
    } else {
      ErrorLogBuffer->ReadRecordPtr = ErrorLogBuffer->ReadRecordPtr + 1;
    }
    if (ErrorLogBuffer->ReadRecordPtr == ErrorLogBuffer->WriteRecordPtr) {
      ErrorLogBuffer->ReadWriteFlag = 1;
    }
    // Actual Error Log count
    ErrorLogCounter += 1;
  }
  ErrorLogDataPtr->Count = ErrorLogCounter;
}

VOID
AddErrorLog (
  IN OUT   AMD_ERROR_BUFFER *ErrorLogBuffer,
  IN       AMD_ERROR_ENTRY  *AmdErrorEntry
  )
{
  UINT16 Index;

  Index = ErrorLogBuffer->WriteRecordPtr;

  // Add the new Error log data into a circular buffer
  ErrorLogBuffer->AmdErrorStruct[Index].AmdError.ErrorClass = AmdErrorEntry->ErrorClass;
  ErrorLogBuffer->AmdErrorStruct[Index].AmdError.ErrorInfo  = AmdErrorEntry->ErrorInfo;
  ErrorLogBuffer->AmdErrorStruct[Index].AmdError.DataParam1 = AmdErrorEntry->DataParam1;
  ErrorLogBuffer->AmdErrorStruct[Index].AmdError.DataParam2 = AmdErrorEntry->DataParam2;
  ErrorLogBuffer->AmdErrorStruct[Index].AmdError.DataParam3 = AmdErrorEntry->DataParam3;
  ErrorLogBuffer->AmdErrorStruct[Index].AmdError.DataParam4 = AmdErrorEntry->DataParam4;

  if ((ErrorLogBuffer->WriteRecordPtr == ErrorLogBuffer->ReadRecordPtr) &&
     (ErrorLogBuffer->ReadWriteFlag == 0)) {
    ErrorLogBuffer->WriteRecordPtr += 1;
    ErrorLogBuffer->ReadRecordPtr += 1;
    if (ErrorLogBuffer->WriteRecordPtr == TOTAL_ERROR_LOG_BUFFERS) {
      ErrorLogBuffer->WriteRecordPtr = 0;
      ErrorLogBuffer->ReadRecordPtr  = 0;
    }
  } else {
    ErrorLogBuffer->WriteRecordPtr += 1;
    if (ErrorLogBuffer->WriteRecordPtr == TOTAL_ERROR_LOG_BUFFERS) {
      ErrorLogBuffer->WriteRecordPtr = 0;
    }
    ErrorLogBuffer->ReadWriteFlag = 0;
  }
  ErrorLogBuffer->Count = ErrorLogBuffer->Count + 1;

  if (ErrorLogBuffer->Count <= TOTAL_ERROR_LOG_BUFFERS) {
    ErrorLogBuffer->AmdErrorStruct[Index].Count = Index;
  }
}

VOID
ErrorLogBufferInit (
  IN OUT   AMD_ERROR_BUFFER *ErrorLogBuffer
  )
{
  ErrorLogBuffer->Count = 0;
  ErrorLogBuffer->ReadRecordPtr = 0;
  ErrorLogBuffer->WriteRecordPtr = 0;
  ErrorLogBuffer->ReadWriteFlag = 1;
}

