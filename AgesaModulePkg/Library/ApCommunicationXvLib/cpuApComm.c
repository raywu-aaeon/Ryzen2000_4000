/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD CPU AP related utility functions.
 *
 * Contains code that provides mechanism to invoke and control APIC communication.
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  CPU
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-10 02:28:05 +0800 (Wed, 10 Dec 2014) $
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

/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include <Library/BaseLib.h>
#include "AGESA.h"
#include "Filecode.h"
#include "cpuApComm.h"
#include "cpuRegisters.h"
#include "Library/AmdBaseLib.h"
#include "Library/CcxBaseX86Lib.h"
#include "Library/CcxHaltLib.h"

#define FILECODE LIBRARY_APCOMMUNICATIONXVLIB_CPUAPCOMM_FILECODE

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
#define XFER_ELEMENT_SIZE    sizeof (UINT32)

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */
VOID
STATIC
ApUtilGetLocalApicBase (
     OUT   UINT64 *ApicBase,
  IN       AMD_CONFIG_PARAMS *StdHeader
  );

/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/*---------------------------------------------------------------------------------------*/
/**
 * Determines the unique ID of the input Socket/Core.
 *
 * This routine converts a socket-core combination to to a number
 * that will be used to directly address a particular core.  This
 * unique value must be less than 128 because we only have a byte
 * to use for status.  APIC IDs are not guaranteed to be below
 * 128.
 *
 * @param[in]      Socket       Socket number of the remote core
 * @param[in]      Core         Core number of the remote core
 * @param[in]      StdHeader    Configuration parameters pointer
 *
 * @return         The unique ID of the desired core
 *
 */
UINT8
ApUtilCalculateUniqueId (
  IN       UINT8 Socket,
  IN       UINT8 Core,
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  UINT8 UniqueId;

  UniqueId = ((Core << 3) | Socket);
  ASSERT ((UniqueId & 0x80) == 0);
  return (UniqueId);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Returns the 64-bit base address of the executing core's local APIC.
 *
 * This function reads the APICBASE MSR and isolates the programmed address.
 *
 * @param[out]     ApicBase     Base address
 * @param[in]      StdHeader    Configuration parameters pointer
 *
 */
VOID
STATIC
ApUtilGetLocalApicBase (
     OUT   UINT64 *ApicBase,
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  *ApicBase = AsmReadMsr64 (MSR_APIC_BAR);
  *ApicBase &= LAPIC_BASE_ADDR_MASK;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Calculate the APIC ID for a given core.
 *
 * Get the current node's apic id and deconstruct it to the base id of local apic id space.
 * Then construct the target's apic id using that base.
 * @b Assumes: The target Socket and Core exist!
 * Other Notes:
 *  - Must run after Topology initialization is complete.
 *  - Code sync: This calculation MUST match the assignment
 *    calculation done above in LocalApicInitializationAtEarly function.
 *  - Assumes family homogeneous population of all sockets.
 *
 *  @param[in]      TargetSocket   The socket in which the Core's Processor is installed.
 *  @param[in]      TargetCore     The Core on that Processor
 *  @param[out]     LocalApicId    Its APIC Id
 *  @param[in]      StdHeader      Handle to header for library and services.
 *
 */
VOID
GetLocalApicIdForCore (
  IN       UINT8             TargetSocket,
  IN       UINT8             TargetCore,
     OUT   UINT32            *LocalApicId,
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  UINT32  CurrentCore;
  UINT32  CurrentLocalApicId;
  UINT64  LocalApicBase;
  UINT32  TempVar_a;
  UINT64  Address;

  // Get local apic base Address
  ApUtilGetLocalApicBase (&LocalApicBase, StdHeader);
  Address = LocalApicBase + APIC_ID_REG;

  LibAmdMemRead32 (Address, &TempVar_a, StdHeader);

  // ApicId [7:0]
  CurrentLocalApicId = (TempVar_a >> APIC20_ApicId) & 0x000000FF;

  CurrentCore = CcxGetInitialApicID (StdHeader);

  //WA
  if ((TargetCore == 0) && ((CurrentLocalApicId - 0x10) != CurrentCore)) {
    CurrentCore = CurrentLocalApicId - 0x10;
  }
  //WA

  CurrentLocalApicId = CurrentLocalApicId - CurrentCore + TargetCore;

  *LocalApicId = CurrentLocalApicId;
}

/*---------------------------------------------------------------------------------------*/
/**
 * Reads the APIC register on the designated remote core.
 *
 * This function uses the remote read inter-processor interrupt protocol
 * to read an APIC register from the remote core
 *
 * @param[in]        TargetApicId  Local APIC ID of the desired core
 * @param[in]        RegAddr       APIC register to read
 * @param[in]        StdHeader     Configuration parameters pointer
 *
 * @return           The current value of the remote core's desired APIC register
 *
 */
UINT32
ApUtilRemoteRead (
  IN       UINT32            TargetApicId,
  IN       UINT8             RegAddr,
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  UINT32 ApicRegister;
  UINT64 ApicBase;
  UINT64 ApicAddr;

  ApUtilGetLocalApicBase (&ApicBase, StdHeader);
  TargetApicId <<= LOCAL_APIC_ID;

  do {
    ApicAddr = ApicBase + APIC_CMD_HI_REG;
    LibAmdMemWrite32 (ApicAddr, &TargetApicId, StdHeader);
    ApicAddr = ApicBase + APIC_CMD_LO_REG;
    ApicRegister = CMD_REG_TO_READ | (UINT32) RegAddr;
    LibAmdMemWrite32 (ApicAddr, &ApicRegister, StdHeader);
    do {
      LibAmdMemRead32 (ApicAddr, &ApicRegister, StdHeader);
    } while ((ApicRegister & CMD_REG_DELIVERY_STATUS) != 0);
    while ((ApicRegister & CMD_REG_REMOTE_RD_STS_MSK) == CMD_REG_REMOTE_DELIVERY_PENDING) {
      LibAmdMemRead32 (ApicAddr, &ApicRegister, StdHeader);
    }
  } while ((ApicRegister & CMD_REG_REMOTE_RD_STS_MSK) != CMD_REG_REMOTE_DELIVERY_DONE);
  ApicAddr = ApicBase + APIC_REMOTE_READ_REG;
  LibAmdMemRead32 (ApicAddr, &ApicRegister, StdHeader);
  return (ApicRegister);
}


/*---------------------------------------------------------------------------------------*/
/**
 * Writes an APIC register on the executing core.
 *
 * This function gets the base address of the executing core's local APIC,
 * and writes a UINT32 value to a specified offset.
 *
 * @param[in]      RegAddr      APIC register to write to
 * @param[in]      Value        Data to be written to the desired APIC register
 * @param[in]      StdHeader    Configuration parameters pointer
 *
 */
VOID
ApUtilLocalWrite (
  IN       UINT32 RegAddr,
  IN       UINT32 Value,
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  UINT64 ApicAddr;

  ApUtilGetLocalApicBase (&ApicAddr, StdHeader);
  ApicAddr += RegAddr;

  LibAmdMemWrite32 (ApicAddr, &Value, StdHeader);
}


/*---------------------------------------------------------------------------------------*/
/**
 * Reads an APIC register on the executing core.
 *
 * This function gets the base address of the executing core's local APIC,
 * and reads a UINT32 value from a specified offset.
 *
 * @param[in]      RegAddr      APIC register to read from
 * @param[in]      StdHeader    Configuration parameters pointer
 *
 * @return         The current value of the local APIC register
 *
 */
UINT32
ApUtilLocalRead (
  IN       UINT32  RegAddr,
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  UINT32 ApicRegister;
  UINT64 ApicAddr;

  ApUtilGetLocalApicBase (&ApicAddr, StdHeader);
  ApicAddr += RegAddr;
  LibAmdMemRead32 (ApicAddr, &ApicRegister, StdHeader);

  return (ApicRegister);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Waits for a remote core's control byte value to either be equal or
 * not equal to any number of specified values.
 *
 * This function will loop doing remote read IPIs until the remote core's
 * control byte becomes one of the values in the input array if the input
 * flags are set for equality.  Otherwise, the loop will continue until
 * the control byte value is not equal to one of the elements in the
 * array.  The caller can also specify an iteration count for timeout
 * purposes.
 *
 * @param[in]      Socket         Socket number of the target core
 * @param[in]      Die            Die number of the target core
 * @param[in]      Complex        Complex number of the target core
 * @param[in]      Core           Core number of the target core
 * @param[in]      Thread         Thread number of the target core
 * @param[in]      WaitParamsPtr  Wait parameter structure
 * @param[in]      StdHeader      Configuration parameteres pointer
 *
 * @return         The current value of the remote core's control byte
 *
 */
UINT8
ApUtilWaitForCoreStatus (
  IN       UINT8 Socket,
  IN       UINT8 Die,
  IN       UINT8 Complex,
  IN       UINT8 Core,
  IN       UINT8 Thread,
  IN       AP_WAIT_FOR_STATUS *WaitParamsPtr,
  IN       AMD_CONFIG_PARAMS  *StdHeader
  )
{
  BOOLEAN  IsEqual;
  UINT8 CoreStatus;
  UINT8 i;
  UINT8 j;

  CoreStatus = 0;
  for (i = 0; (WaitParamsPtr->RetryCount == WAIT_INFINITELY) ||
              (i < WaitParamsPtr->RetryCount); ++i) {
    CoreStatus = ApReadRemoteCtrlByte (Socket, 0, 0, Core, 0, StdHeader);
    // Determine whether or not the current remote status is equal
    // to an element in the array.
    IsEqual = FALSE;
    for (j = 0; !IsEqual && j < WaitParamsPtr->NumberOfElements; ++j) {
      if (CoreStatus == WaitParamsPtr->Status[j]) {
        IsEqual = TRUE;
      }
    }
    if ((((WaitParamsPtr->WaitForStatusFlags & WAIT_STATUS_EQUALITY) != 0) && IsEqual) ||
        (((WaitParamsPtr->WaitForStatusFlags & WAIT_STATUS_EQUALITY) == 0) && !IsEqual)) {
      break;
    }
  }
  return (CoreStatus);
}


/*---------------------------------------------------------------------------------------*/
/**
 * Runs the AP task on the executing core.
 *
 * @param[in]      TaskPtr      Function descriptor
 * @param[in]      StdHeader    Configuration parameters pointer
 *
 * @return         Return value of the task, or zero if the task
 *                 was VOID.
 *
 */
UINT32
ApUtilTaskOnExecutingCore (
  IN       AP_TASK *TaskPtr,
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  UINT32   InvocationOptions;
  UINT32   ReturnCode;

  ReturnCode = 0;
  InvocationOptions = 0;

  if (TaskPtr->DataTransfer.DataSizeInDwords != 0) {
    InvocationOptions |= AP_TASK_HAS_INPUT;
  }
  if ((TaskPtr->ExeFlags & TASK_HAS_OUTPUT) != 0) {
    InvocationOptions |= AP_TASK_HAS_OUTPUT;
  }

  switch (InvocationOptions) {
  case 0:
    TaskPtr->FuncAddress.PfApTask (StdHeader);
    break;
  case AP_TASK_HAS_INPUT:
    TaskPtr->FuncAddress.PfApTaskI (TaskPtr->DataTransfer.DataPtr, StdHeader);
    break;
  case AP_TASK_HAS_OUTPUT:
    ReturnCode = TaskPtr->FuncAddress.PfApTaskO (StdHeader);
    break;
  case (AP_TASK_HAS_INPUT | AP_TASK_HAS_OUTPUT):
    ReturnCode = TaskPtr->FuncAddress.PfApTaskIO (TaskPtr->DataTransfer.DataPtr, StdHeader);
    break;
  default:
    ReturnCode = 0;
    break;
  }
  return (ReturnCode);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Securely passes a buffer to the designated remote core.
 *
 * This function uses a sequence of remote reads to transmit a data
 * buffer, one UINT32 at a time.
 *
 * @param[in]      Socket       Socket number of the remote core
 * @param[in]      Core         Core number of the remote core
 * @param[in]      BufferInfo   Information about the buffer to pass, and
 *                              how to pass it
 * @param[in]      StdHeader    Configuration parameters pointer
 *
 */
VOID
ApUtilTransmitBuffer (
  IN       UINT8   Socket,
  IN       UINT8   Core,
  IN       AP_DATA_TRANSFER  *BufferInfo,
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  UINT8  TargetCore;
  UINT8  MyUniqueId;
  UINT8  CurrentStatus;
  UINT32 *CurrentPtr;
  UINT32 i;
  UINT32 MyCore;
  AP_WAIT_FOR_STATUS WaitForStatus;

  if ((BufferInfo->DataTransferFlags & DATA_IN_MEMORY) != 0) {
    ApWriteDataDword ((UINT32) 0x00000000, StdHeader);
  } else {
    ApWriteDataDword ((UINT32) BufferInfo->DataSizeInDwords, StdHeader);
  }
  TargetCore = ApUtilCalculateUniqueId (Socket, Core, StdHeader);

  ApWriteCtrlByte (TargetCore, StdHeader);

  MyCore = CcxGetInitialApicID (StdHeader);

  MyUniqueId = ApUtilCalculateUniqueId (0, (UINT8)MyCore, StdHeader);

  WaitForStatus.Status = &MyUniqueId;
  WaitForStatus.NumberOfElements = 1;
  WaitForStatus.RetryCount = WAIT_INFINITELY;
  WaitForStatus.WaitForStatusFlags = WAIT_STATUS_EQUALITY;

  ApUtilWaitForCoreStatus (Socket, 0, 0, Core, 0, &WaitForStatus, StdHeader);
  ApWriteDataDword (BufferInfo->DataTransferFlags, StdHeader);

  ApWriteCtrlByte (CORE_DATA_FLAGS_READY, StdHeader);
  WaitForStatus.WaitForStatusFlags = 0;
  ApUtilWaitForCoreStatus (Socket, 0, 0, Core, 0, &WaitForStatus, StdHeader);
  if ((BufferInfo->DataTransferFlags & DATA_IN_MEMORY) != 0) {
    ApUtilTransmitPointer (Socket, Core, (VOID **) &BufferInfo->DataPtr, StdHeader);
  } else {
    ApWriteCtrlByte (CORE_STS_DATA_READY_1, StdHeader);
    CurrentStatus = CORE_STS_DATA_READY_0;
    WaitForStatus.Status = &CurrentStatus;
    WaitForStatus.WaitForStatusFlags = WAIT_STATUS_EQUALITY;
    ApUtilWaitForCoreStatus (Socket, 0, 0, Core, 0, &WaitForStatus, StdHeader);
    WaitForStatus.WaitForStatusFlags = 0;
    CurrentPtr = (UINT32 *) BufferInfo->DataPtr;
    for (i = 0; i < BufferInfo->DataSizeInDwords; ++i) {
      ApWriteDataDword (*CurrentPtr++, StdHeader);
      ApWriteCtrlByte (CurrentStatus, StdHeader);
      ApUtilWaitForCoreStatus (Socket, 0, 0, Core, 0, &WaitForStatus, StdHeader);
      CurrentStatus ^= 0x01;
    }
  }
  ApWriteCtrlByte (CORE_ACTIVE, StdHeader);
}


/*---------------------------------------------------------------------------------------*/
/**
 * Securely receives a buffer from the designated remote core.
 *
 * This function uses a sequence of remote reads to receive a data
 * buffer, one UINT32 at a time.
 *
 * @param[in]      Socket       Socket number of the remote core
 * @param[in]      Core         Core number of the remote core
 * @param[in]      BufferInfo   Information about where to place the buffer
 * @param[in]      StdHeader    Configuration parameters pointer
 *
 * @retval         AGESA_SUCCESS Transaction was successful
 * @retval         AGESA_ALERT   The non-NULL desired location to place
 *                               the buffer was not used as the buffer
 *                               resides in a shared memory space.  The
 *                               input data pointer has changed.
 * @retval         AGESA_ERROR   There is not enough room to receive the
 *                               buffer.
 *
 */
AGESA_STATUS
ApUtilReceiveBuffer (
  IN       UINT8   Socket,
  IN       UINT8   Core,
  IN OUT   AP_DATA_TRANSFER  *BufferInfo,
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  UINT8    MyUniqueId;
  UINT8    SourceUniqueId;
  UINT8    CurrentStatus;
  UINT32   i;
  UINT32   MyCore;
  UINT32   *CurrentPtr;
  UINT32   TransactionSize;
  AGESA_STATUS ReturnStatus;
  AP_WAIT_FOR_STATUS WaitForStatus;

  ReturnStatus = AGESA_SUCCESS;
  MyCore = CcxGetInitialApicID (StdHeader);

  MyUniqueId = ApUtilCalculateUniqueId (0, (UINT8)MyCore, StdHeader);

  WaitForStatus.Status = &MyUniqueId;
  WaitForStatus.NumberOfElements = 1;
  WaitForStatus.RetryCount = WAIT_INFINITELY;
  WaitForStatus.WaitForStatusFlags = WAIT_STATUS_EQUALITY;

  ApUtilWaitForCoreStatus (Socket, 0, 0, Core, 0, &WaitForStatus, StdHeader);
  TransactionSize = ApReadRemoteDataDword (Socket, 0, 0, Core, 0, StdHeader);

//  if (BufferInfo->DataPtr == NULL && TransactionSize != 0) {
//    HeapMalloc.BufferHandle = AMD_CPU_AP_TASKING_HANDLE;
//    HeapMalloc.Persist = HEAP_LOCAL_CACHE;
//    // Deallocate the general purpose heap structure, if it exists.  Ignore
//    // the status in case it does not exist.
//    HeapDeallocateBuffer (HeapMalloc.BufferHandle, StdHeader);
//    HeapMalloc.RequestedBufferSize = (TransactionSize * XFER_ELEMENT_SIZE);
//    if (HeapAllocateBuffer (&HeapMalloc, StdHeader) == AGESA_SUCCESS) {
//      BufferInfo->DataPtr = (UINT32 *) HeapMalloc.BufferPtr;
//      BufferInfo->DataSizeInDwords = (UINT16) (HeapMalloc.RequestedBufferSize / XFER_ELEMENT_SIZE);
//    } else {
//      BufferInfo->DataSizeInDwords = 0;
//    }
//  }

  BufferInfo->DataPtr = (UINT32 *) StdHeader->HeapBasePtr;
  BufferInfo->DataSizeInDwords = (UINT16) TransactionSize;

  if (TransactionSize <= BufferInfo->DataSizeInDwords) {
    SourceUniqueId = ApUtilCalculateUniqueId (Socket, Core, StdHeader);
    ApWriteCtrlByte (SourceUniqueId, StdHeader);
    CurrentStatus = CORE_DATA_FLAGS_READY;
    WaitForStatus.Status = &CurrentStatus;
    ApUtilWaitForCoreStatus (Socket, 0, 0, Core, 0, &WaitForStatus, StdHeader);
    BufferInfo->DataTransferFlags =  ApReadRemoteDataDword (Socket, 0, 0, Core, 0, StdHeader);
    ApWriteCtrlByte (CORE_DATA_FLAGS_ACKNOWLEDGE, StdHeader);
    if ((BufferInfo->DataTransferFlags & DATA_IN_MEMORY) != 0) {
      if (BufferInfo->DataPtr != NULL) {
        ReturnStatus = AGESA_ALERT;
      }
      ApUtilReceivePointer (Socket, Core, (VOID **) &BufferInfo->DataPtr, StdHeader);
    } else {
      CurrentStatus = CORE_STS_DATA_READY_1;
      ApUtilWaitForCoreStatus (Socket, 0, 0, Core, 0, &WaitForStatus, StdHeader);
      CurrentStatus = CORE_STS_DATA_READY_0;
      ApWriteCtrlByte (CurrentStatus, StdHeader);
      CurrentPtr = BufferInfo->DataPtr;
      for (i = 0; i < TransactionSize; ++i) {
        ApUtilWaitForCoreStatus (Socket, 0, 0, Core, 0, &WaitForStatus, StdHeader);
        *CurrentPtr++ = ApReadRemoteDataDword (Socket, 0, 0, Core, 0, StdHeader);
        CurrentStatus ^= 0x01;
        ApWriteCtrlByte (CurrentStatus, StdHeader);
      }
    }
    ApWriteCtrlByte (CORE_ACTIVE, StdHeader);
  } else {
    BufferInfo->DataSizeInDwords = (UINT16) TransactionSize;
    ReturnStatus = AGESA_ERROR;
  }
  return (ReturnStatus);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Securely transmits a pointer to the designated remote core.
 *
 * This function uses a sequence of remote reads to transmit a pointer,
 * one UINT32 at a time.
 *
 * @param[in]      Socket        Socket number of the target core
 * @param[in]      Core          Core number of the target core
 * @param[out]     Pointer       Pointer passed from remote core
 * @param[in]      StdHeader     Configuration parameters pointer
 *
 */
VOID
ApUtilTransmitPointer (
  IN       UINT8   Socket,
  IN       UINT8   Core,
  IN       VOID  **Pointer,
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  UINT8   i;
  UINT8   WaitStatus;
  UINT32  *AddressScratchPtr;
  AP_WAIT_FOR_STATUS WaitForStatus;

  WaitStatus = CORE_NEEDS_PTR;
  WaitForStatus.Status = &WaitStatus;
  WaitForStatus.NumberOfElements = 1;
  WaitForStatus.RetryCount = WAIT_INFINITELY;

  AddressScratchPtr = (UINT32 *) Pointer;

  for (i = 0; i < SIZE_IN_DWORDS (AddressScratchPtr); i++) {
    WaitForStatus.WaitForStatusFlags = WAIT_STATUS_EQUALITY;
    ApUtilWaitForCoreStatus (Socket, 0, 0, Core, 0, &WaitForStatus, StdHeader);
    ApWriteDataDword (*AddressScratchPtr++, StdHeader);
    ApWriteCtrlByte (CORE_STS_DATA_READY_0, StdHeader);
    WaitForStatus.WaitForStatusFlags = 0;
    ApUtilWaitForCoreStatus (Socket, 0, 0, Core, 0, &WaitForStatus, StdHeader);
    ApWriteCtrlByte (CORE_ACTIVE, StdHeader);
  }
}

/*---------------------------------------------------------------------------------------*/
/**
 * Securely receives a pointer from the designated remote core.
 *
 * This function uses a sequence of remote reads to receive a pointer,
 * one UINT32 at a time.
 *
 * @param[in]      Socket         Socket number of the target core
 * @param[in]      Core           Core number of the target core
 * @param[out]     ReturnPointer Pointer passed from remote core
 * @param[in]      StdHeader     Configuration parameters pointer
 *
 */
VOID
ApUtilReceivePointer (
  IN       UINT8   Socket,
  IN       UINT8   Core,
  OUT   VOID  **ReturnPointer,
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  UINT8   i;
  UINT8   WaitStatus;
  UINT32  *AddressScratchPtr;
  AP_WAIT_FOR_STATUS WaitForStatus;

  WaitStatus = CORE_STS_DATA_READY_0;
  WaitForStatus.Status = &WaitStatus;
  WaitForStatus.NumberOfElements = 1;
  WaitForStatus.RetryCount = WAIT_INFINITELY;
  AddressScratchPtr = (UINT32 *) ReturnPointer;
  for (i = 0; i < SIZE_IN_DWORDS (AddressScratchPtr); ++i) {
    ApWriteCtrlByte (CORE_NEEDS_PTR, StdHeader);
    WaitForStatus.WaitForStatusFlags = WAIT_STATUS_EQUALITY;
    ApUtilWaitForCoreStatus (Socket, 0, 0, Core, 0, &WaitForStatus, StdHeader);
    *AddressScratchPtr++ = ApReadRemoteDataDword (Socket, 0, 0, Core, 0, StdHeader);
    ApWriteCtrlByte (CORE_ACTIVE, StdHeader);
    WaitForStatus.WaitForStatusFlags = 0;
    ApUtilWaitForCoreStatus (Socket, 0, 0, Core, 0, &WaitForStatus, StdHeader);
  }
}

/*---------------------------------------------------------------------------------------*/
/**
 * Wakes up a core from the halted state.
 *
 * This function sends a directed NMI inter-processor interrupt to
 * the input Socket/Core.
 *
 * @param[in]      TargetApicId    Local APIC ID of the desired core
 * @param[in]      StdHeader       Configuration parameters pointer
 *
 */
VOID
ApUtilFireDirectedNmi (
  IN       UINT32 TargetApicId,
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  TargetApicId <<= LOCAL_APIC_ID;

  ApUtilLocalWrite ((UINT32) APIC_CMD_HI_REG, TargetApicId, StdHeader);
  ApUtilLocalWrite ((UINT32) APIC_CMD_LO_REG, (UINT32) CMD_REG_TO_NMI, StdHeader);
}

/*---------------------------------------------------------------------------------------*/
/**
 * Sets up the AP's IDT with NMI (INT2) being the only valid descriptor
 *
 * This function prepares the executing AP core for recovering from a hlt
 * instruction by initializing its IDTR.
 *
 * @param[in]        NmiIdtDescPtr Pointer to a writable IDT entry to
 *                                 be used for NMIs
 * @param[in]        StdHeader     Configuration parameters pointer
 *
 */
VOID
ApUtilSetupIdtForHlt (
  IN       IDT_DESCRIPTOR *NmiIdtDescPtr,
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  UINT8   DescSize;
  UINT64  HandlerOffset;
  UINT64  EferRegister;
  IDT_BASE_LIMIT IdtInfo;

  EferRegister = AsmReadMsr64 (MSR_EXTENDED_FEATURE_EN);
  if ((EferRegister & 0x100) != 0) {
    DescSize = 16;
  } else {
    DescSize = 8;
  }

  HandlerOffset = (UINT64) (UINTN) NmiHandler;
  NmiIdtDescPtr->OffsetLo = (UINT16) HandlerOffset & 0xFFFF;
  NmiIdtDescPtr->OffsetHi = (UINT16) RShiftU64 (HandlerOffset, 16);
  GetCsSelector (&NmiIdtDescPtr->Selector, StdHeader);
  NmiIdtDescPtr->Flags = IDT_DESC_PRESENT | IDT_DESC_TYPE_INT32;
  NmiIdtDescPtr->Rsvd = 0;
  NmiIdtDescPtr->Offset64 = (UINT32) RShiftU64 (HandlerOffset, 32);
  NmiIdtDescPtr->Rsvd64 = 0;
  IdtInfo.Limit = (UINT16) ((DescSize * 3) - 1);
  IdtInfo.Base = (UINT64) (UINTN) NmiIdtDescPtr - (DescSize * 2);
  SetIdtr (&IdtInfo , StdHeader);
}

/*---------------------------------------------------------------------------------------
 *                           L O C A L    F U N C T I O N S
 *---------------------------------------------------------------------------------------
 */



