/**
 * @file
 *
 * AMD Integrated Debug Debug_library Routines
 *
 * Contains all functions related to HDTOUT
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
#include <Library/BaseLib.h>
#include <Pi/PiMultiPhase.h>
#include <Library/AmdBaseLib.h>
#include <Library/AmdIdsDebugPrintLib.h>
#include <Library/AmdHeapLib.h>
#include <AmdIdsDebugPrintLocal.h>
#include <Library/CcxRolesLib.h>
#include <Filecode.h>

#define FILECODE LIBRARY_AMDIDSDEBUGPRINTLIB_AMDIDSDPHDTOUTLIB_FILECODE
 /*----------------------------------------------------------------------------------------
 *                             MODULES STATIC DATA
 *----------------------------------------------------------------------------------------
 */

 /*----------------------------------------------------------------------------------------
 *                             MODULES PRIVATE DECLARATION
 *----------------------------------------------------------------------------------------
 */
VOID
EFIAPI
HdtOutIoWrite (
  IN       UINT32 Addr,
  IN       UINT32 Value,
  IN       UINT32 Flag
  );

#define HDTOUT_VERSION          0x0200

/// HDTOUT command
#define HDTOUT_COMMAND        0x99cc
#define HDTOUT_INIT           (0x10BF0000ul | HDTOUT_COMMAND)
#define HDTOUT_ASSERT         (0xA0BF0000ul | HDTOUT_COMMAND)
#define HDTOUT_EXIT           (0xE0BF0000ul | HDTOUT_COMMAND)
#define HDTOUT_PRINT          (0xC0BF0000ul | HDTOUT_COMMAND)
#define HDTOUT_TIME_ANALYSE   (0xD0BF0000ul | HDTOUT_COMMAND)
#define HDTOUT_BREAKPOINT     (0xB0BF0000ul | HDTOUT_COMMAND)
#define HDTOUT_ERROR          (0x1EBF0000ul | HDTOUT_COMMAND)


#define HDTOUT_ERROR_HEAP_ALLOCATION       0x1
#define HDTOUT_ERROR_HEAP_AllOCATE_FAIL       0x2

#define HDTOUT_PRINTCTRL_OFF      0
#define HDTOUT_PRINTCTRL_ON       1
#define HDTOUT_ALL_CORES          0
#define HDTOUT_BSP_ONLY           1
#define HDTOUT_BUFFER_MODE_OFF    0
#define HDTOUT_BUFFER_MODE_ON     1

#define HDTOUT_HEADER_SIGNATURE     0xDB1099CCul
#define HDTOUT_DEFAULT_BUFFER_SIZE  0x1000


#define IDS_HDTOUT_BP_AND_OFF             0
#define IDS_HDTOUT_BP_AND_ON              1

#define IDS_HDTOUT_BPFLAG_FORMAT_STR   0
#define IDS_HDTOUT_BPFLAG_STATUS_STR   1

#define HDTOUT_BP_ACTION_HALT          1
#define HDTOUT_BP_ACTION_PRINTON       2
#define HDTOUT_BP_ACTION_PRINTONE      3
#define HDTOUT_BP_ACTION_PRINTOFF      4

///breakpoint unit of HDTOUT
typedef struct _BREAKPOINT_UNIT {
  UINT8 AndFlag : 1;        ///< Next string is ANDed to current string
  UINT8 BpFlag : 1;         ///< Format string or Status string
  UINT8 Action : 4;         ///< Halt, start HDTOUT, or stop HDT,...
  UINT8 BpStrOffset;        ///< Offset from BreakpointList to the breakpoint string
} BREAKPOINT_UNIT;


/**
 *  Determine whether IDS console is enabled.
 *
 *  @param[in,out] pHdtoutHeaderPtr    Address of hdtout header pointer
 *
 *  @retval       TRUE       pHdtoutHeader Non zero
 *  @retval       FALSE   pHdtoutHeader is NULL
 *
 **/
BOOLEAN
AmdIdsDpHdtOutGetHeader (
  IN OUT   HDTOUT_HEADER **pHdtoutHeaderPtr
  )
{
  UINTN Dr3Reg;
  HDTOUT_HEADER *HdtoutHeaderPtr;
  LOCATE_HEAP_PTR LocateHeapParam;
  AMD_CONFIG_PARAMS *StdHeader;

  StdHeader = NULL;
  Dr3Reg = AsmReadDr3 ();
  HdtoutHeaderPtr = (HDTOUT_HEADER *) Dr3Reg;
  if (HdtoutHeaderPtr == NULL) {
    return FALSE;
  }

  //Try to locate the header by locate Heap
  LocateHeapParam.BufferHandle = IDS_HDT_OUT_BUFFER_HANDLE;
  LocateHeapParam.BufferPtr = NULL;
  if (HeapLocateBuffer (&LocateHeapParam, StdHeader) == AGESA_SUCCESS) {
    HdtoutHeaderPtr = (HDTOUT_HEADER *) LocateHeapParam.BufferPtr;
    if (HdtoutHeaderPtr->Signature == HDTOUT_HEADER_SIGNATURE) {
      *pHdtoutHeaderPtr = HdtoutHeaderPtr;
      return TRUE;
    }
  }
  return FALSE;

}
/**
 *  Determine whether IDS console is enabled.
 *
 *
 *  @retval       TRUE    Ids console is enabled.
 *  @retval       FALSE   Ids console is disabled.
 *
 **/
BOOLEAN
AmdIdsDpHdtOutSupport (
  VOID
  )
{
  BOOLEAN Result;
  UINTN  DR2reg;

  Result = FALSE;
  if (PcdGetBool (PcdAmdIdsDebugPrintHdtOutEnable)) {
    if (PcdGetBool (PcdAmdIdsDebugPrintHdtOutForceEnable) == TRUE) {
      Result = TRUE;
    } else {
      DR2reg = AsmReadDr2 ();
      if (DR2reg == 0x99CC) {
        Result = TRUE;
      }
    }
  }
  return Result;
}

/**
 *  Get HDTOUT customize Filter
 *
 *  @param[in,out] Filter    Filter do be filled
 *
 *  @retval       TRUE    Alway return true, for HDTOUT has its own filter mechanism
 *
 **/
BOOLEAN
AmdIdsDpHdtOutGetFilter (
  IN OUT   UINT64 *Filter
  )
{
  HDTOUT_HEADER *HdtoutHeaderPtr;

  if (AmdIdsDpHdtOutGetHeader (&HdtoutHeaderPtr) == TRUE) {
    *Filter = HdtoutHeaderPtr->ConsoleFilter;
  }
  return TRUE;
}

/**
 *
 *  Initial register setting used for HDT out Function.
 *
 *
 *  @param[in,out] StdHeader    The Pointer of AGESA Header
 *
 **/
VOID
AmdIdsDpHdtOutRegisterRestore (
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  )
{
  UINTN CR4reg;

  AsmMsrAnd64 (0xC001100A, ~((UINT64)BIT0));

  AsmWriteDr2 (0);
  AsmWriteDr3 (0);
  AsmWriteDr7 (0);

  CR4reg = AsmReadCr4 ();
  AsmWriteCr4 (CR4reg & (~BIT3));

}


BOOLEAN
AmdIdsDpHdtOutRegInitCheck (
  )
{
  UINT64  v64;
  UINTN  value;

  v64 = 0;
  value = 0;
  v64 = AsmReadMsr64 (0xC001100A);
  if ((v64 & BIT0) == 0) {
    return FALSE;
  }

  v64 = 0;
  value = AsmReadDr7 ();
  if ((value & 0x02000420) != 0x02000420) {
    return FALSE;
  }

  v64 = 0;
  value = AsmReadCr4 ();
  if ((value & BIT3) == 0) {
    return FALSE;
  }
  return TRUE;
}

VOID
AmdIdsDpHdtOutBufferModeInit (
  )
{
  HDTOUT_HEADER HdtoutHeader;
  HDTOUT_HEADER *HdtOutHeaderPtr;
  UINT32 HdtOutHeapSize;
  AMD_CONFIG_PARAMS *StdHeader;
  ALLOCATE_HEAP_PARAMS AllocateHeapParams;
  AGESA_STATUS Status;

  StdHeader = NULL;

  //Skip AP buffer mode init
  if ((!AmdIdsDpHdtOutSupport ()) ||
      (!CcxIsBsp(StdHeader)) ||
      (AmdIdsDpHdtOutGetHeader (&HdtOutHeaderPtr) == TRUE)) {
    return;
  }


  AmdIdsDpHdtOutRegisterInit ();
  LibAmdMemFill (&HdtoutHeader, 0, sizeof (HDTOUT_HEADER), StdHeader);
// Initialize HDTOUT Header
  HdtoutHeader.Signature = HDTOUT_HEADER_SIGNATURE;
  HdtoutHeader.Version = HDTOUT_VERSION;
  HdtoutHeader.BufferSize = HDTOUT_DEFAULT_BUFFER_SIZE;
  HdtoutHeader.DataIndex = 0;
  HdtoutHeader.PrintCtrl = HDTOUT_PRINTCTRL_ON;
  HdtoutHeader.NumBreakpointUnit = 0;
//      HdtoutHeader.FuncListAddr = (UINT32) (UINT64) IDS_FUNCLIST_ADDR;
  HdtoutHeader.FuncListAddr = 0;
  HdtoutHeader.StatusStr[0] = 0;
  HdtoutHeader.OutBufferMode = HDTOUT_BUFFER_MODE_ON;
  HdtoutHeader.EnableMask = 0;
  HdtoutHeader.ConsoleFilter = 0xFFFFFFFFFFFFFFFF;

  // Trigger HDTOUT breakpoint to get inputs from script
  HdtOutIoWrite (HDTOUT_INIT, (UINT32) ((UINTN) &HdtoutHeader), 0);
  // Disable AP HDTOUT if set BspOnlyFlag
//      if (HdtoutHeader.BspOnlyFlag == HDTOUT_BSP_ONLY) {
//        if (!IsBsp (StdHeader)) {
//          AmdIdsDpHdtOutRegisterRestore (StdHeader);
//          return;
//        }
//      }
  // Convert legacy EnableMask to new ConsoleFilter
  HdtoutHeader.ConsoleFilter |= HdtoutHeader.EnableMask;

  // Disable the buffer if the size is not large enough
  if (HdtoutHeader.BufferSize < 128) {
    HdtoutHeader.BufferSize = 0;
    HdtoutHeader.OutBufferMode = HDTOUT_BUFFER_MODE_OFF;
  } else {
    HdtoutHeader.OutBufferMode = HDTOUT_BUFFER_MODE_ON;
  }

  // Check if Hdtout header have been initialed, if so it must 2nd time come here
//      if (AmdIdsDpHdtOutGetHeader (&pHdtoutHeader, StdHeader)) {
//        Persist = HEAP_SYSTEM_MEM;
//      } else {
//        Persist = HEAP_LOCAL_CACHE;
//      }


  HdtOutHeapSize = HdtoutHeader.BufferSize + sizeof (HdtoutHeader) - 2;
  //To avoid build HOB, check HdtOutHeapSize 1st, reduce the buffer size if exceed
  if (HdtOutHeapSize > 0xFFF8) {
    HdtoutHeader.BufferSize = 0xFFF8 - sizeof (HdtoutHeader);
    HdtOutHeapSize = HdtoutHeader.BufferSize + sizeof (HdtoutHeader) - 2;
  }
  // Allocate Heap
  AllocateHeapParams.BufferHandle = IDS_HDT_OUT_BUFFER_HANDLE;
  AllocateHeapParams.Persist = HEAP_BOOTTIME_SYSTEM_MEM;
  AllocateHeapParams.RequestedBufferSize = HdtOutHeapSize;
  AllocateHeapParams.BufferPtr = NULL;
  Status = HeapAllocateBuffer (&AllocateHeapParams, StdHeader);

  // If the buffer have been successfully allocated?
  if (Status == AGESA_SUCCESS) {
    //Copy Data to allocated buffer
    LibAmdMemCopy (AllocateHeapParams.BufferPtr, &HdtoutHeader, sizeof (HdtoutHeader), StdHeader);
    AsmWriteDr3 ((UINTN) AllocateHeapParams.BufferPtr);
  } else {
    /// Clear DR3_REG
    HdtOutIoWrite (HDTOUT_ERROR, HDTOUT_ERROR_HEAP_AllOCATE_FAIL, 0);
    AsmWriteDr3 (0);
  }
}
/**
 *
 *  Register Initial function for HDT out Function.
 *
 *  Init required Debug register
 *
 *  @param[in,out] StdHeader    The Pointer of AGESA Header
 *
 **/
VOID
AmdIdsDpHdtOutRegisterInit (
  VOID
  )
{
  UINTN CR4reg;

  //IDS_FUNCLIST_EXTERN ();
  if (AmdIdsDpHdtOutSupport ()) {
    //Check if HDTOUT register have already been initialized
    if (AmdIdsDpHdtOutRegInitCheck () == FALSE) {
      AsmMsrOr64 (0xC001100A, 1);

      AsmWriteDr2 (0x99CC);

      AsmWriteDr7 (0x02000420);

      CR4reg = AsmReadCr4 ();
      AsmWriteCr4 (CR4reg | (1 << 3));
    }
  }
}

/**
 *
 *  Flush all HDTOUT buffer data before HOB transfer
 *
 *
 **/
VOID
AmdIdsDpHdtOutBufferFlush (
  )
{
  HDTOUT_HEADER *HdtoutHeaderPtr ;

  if (AmdIdsDpHdtOutSupport ()) {
    if (AmdIdsDpHdtOutGetHeader (&HdtoutHeaderPtr)) {
      if ((HdtoutHeaderPtr->PrintCtrl == HDTOUT_PRINTCTRL_ON) &&
          (HdtoutHeaderPtr->OutBufferMode == HDTOUT_BUFFER_MODE_ON)) {
        HdtOutIoWrite (HDTOUT_PRINT, (UINT32) ((UINTN)HdtoutHeaderPtr->Data), HdtoutHeaderPtr->DataIndex);
        HdtoutHeaderPtr->DataIndex = 0;
      }
    }
  }
}

/**
 *
 *  Exit function for HDT out Function.
 *
 *  Restore debug register and Deallocate heap, and will also fire a HDTOUT
 *  Command to let hdtout script do corresponding things.
 *
 *
 **/
VOID
AmdIdsDpHdtOutExit (
  )
{
//  IDSAPLATETASK IdsApLateTask;
  if (AmdIdsDpHdtOutSupport ()) {
//    IdsApLateTask.ApTask = (PF_IDS_AP_TASK) AmdIdsDpHdtOutExitCoreTask;
//    IdsApLateTask.ApTaskPara = NULL;
//    IdsAgesaRunFcnOnAllCoresLate (&IdsApLateTask, StdHeader);
//    HeapDeallocateBuffer (IDS_HDT_OUT_BUFFER_HANDLE, StdHeader);
  }
}

/**
 *  Print formated string with accerate buffer
 *  Flow out only when buffer will full
 *
 *  @param[in] Buffer  - Point to input buffer
 *  @param[in] BufferSize  - Buffer size
 *  @param[in] HdtoutHeaderPtr  - Point to Hdtout Header
 *
**/
VOID
AmdIdsDpHdtOutPrintWithBuffer (
  IN      CHAR8   *Buffer,
  IN      UINTN BufferSize,
  IN      HDTOUT_HEADER *HdtoutHeaderPtr
  )
{
  if ((HdtoutHeaderPtr == NULL) || (Buffer == NULL)) {
    return;
  }
  LibAmdIoWrite (AccessWidth16, 0xFFED, Buffer, NULL);

  while (BufferSize--) {
    if (HdtoutHeaderPtr->DataIndex >= HdtoutHeaderPtr->BufferSize) {
      //Flow out current buffer, and clear the index
      HdtOutIoWrite (HDTOUT_PRINT, (UINT32) (UINTN) &HdtoutHeaderPtr->Data[0], HdtoutHeaderPtr->BufferSize);
      HdtoutHeaderPtr->DataIndex = 0;
    }
    HdtoutHeaderPtr->Data[HdtoutHeaderPtr->DataIndex++] = *(Buffer++);
  }
}


/**
 *  Print formated string to HDTOUT
 *
 *  @param[in] Buffer  - Point to input buffer
 *  @param[in] BufferSize  - Buffer size
 *
**/
VOID
AmdIdsDpHdtOutPrint (
  IN      CHAR8   *Buffer,
  IN      UINTN BufferSize
  )
{
  HDTOUT_HEADER *HdtoutHeaderPtr;

  if (!AmdIdsDpHdtOutSupport ()) {
    return;
  }

  if (AmdIdsDpHdtOutGetHeader (&HdtoutHeaderPtr)) {
    //Print Function
    if (HdtoutHeaderPtr->PrintCtrl == HDTOUT_PRINTCTRL_ON) {
      if (HdtoutHeaderPtr->OutBufferMode == HDTOUT_BUFFER_MODE_ON) {
        AmdIdsDpHdtOutPrintWithBuffer (Buffer, BufferSize, HdtoutHeaderPtr);
      } else {
        HdtOutIoWrite (HDTOUT_PRINT, (UINT32) (UINTN) Buffer, (UINT32) BufferSize);
      }
    }
    //Check BreakPoint
//    if (HdtoutHeaderPtr->NumBreakpointUnit) {
//      AmdIdsDpHdtOutBreakPoint (Buffer, BufferSize, HdtoutHeaderPtr);
//      if (debugPrintPrivate->saveContext) {
//        AmdIdsDpHdtOutSaveContext (Buffer, BufferSize, HdtoutHeaderPtr);
//        debugPrintPrivate->saveContext = FALSE;
//      }
//    }
  } else {
    //No HDTOUT header found print directly without buffer
    HdtOutIoWrite (HDTOUT_PRINT, (UINT32) (UINTN) Buffer, (UINT32) BufferSize);
  }
}

CONST AMD_IDS_DEBUG_PRINT_INSTANCE  AmdIdsDebugPrintHdtoutInstance =
{
  AmdIdsDpHdtOutSupport,
  AmdIdsDpHdtOutRegisterInit,
  AmdIdsDpHdtOutGetFilter,
  AmdIdsDpHdtOutPrint
};

