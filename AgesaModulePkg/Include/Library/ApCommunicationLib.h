/* $NoKeywords:$ */
/**
 * @file
 *
 * AP communication Services library
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Lib
 * @e \$Revision$   @e \$Date$
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
 **/

#ifndef _AP_COMMUNICATION_LIB_H_
#define _AP_COMMUNICATION_LIB_H_
#pragma pack (push, 1)

typedef VOID (*PF_AP_TASK) (AMD_CONFIG_PARAMS *StdHeader);
typedef VOID (*PF_AP_TASK_I) (VOID *, AMD_CONFIG_PARAMS *StdHeader);
typedef UINT32 (*PF_AP_TASK_O) (AMD_CONFIG_PARAMS *StdHeader);
typedef UINT32 (*PF_AP_TASK_IO) (VOID *, AMD_CONFIG_PARAMS *StdHeader);

/// Function pointer union representing the eight different
/// types of functions that an AP can be asked to perform.
typedef union {
  PF_AP_TASK     PfApTask;      ///< AMD_CONFIG_PARAMS *  input with no output
  PF_AP_TASK_I   PfApTaskI;     ///< VOID * + AMD_CONFIG_PARAMS *  input with no output
  PF_AP_TASK_O   PfApTaskO;     ///< AMD_CONFIG_PARAMS * input with UINT32 output
  PF_AP_TASK_IO  PfApTaskIO;    ///< VOID * + AMD_CONFIG_PARAMS * input with UINT32 output
} AP_FUNCTION_PTR;

/// Input structure for ApUtilTransmitBuffer and ApUtilReceiveBuffer
/// containing information about the data transfer from one core
/// to another.
typedef struct {
  IN OUT   UINT16 DataSizeInDwords;   ///< Size of the data to be transferred rounded up to the nearest dword
  IN OUT   VOID   *DataPtr;           ///< Pointer to the data
  IN       UINT32 DataTransferFlags;  ///< Flags dictating certain aspects of the data transfer
} AP_DATA_TRANSFER;

/// Input structure for ApUtilRunCodeOnSocketCore.
typedef struct _AP_TASK {
  AP_FUNCTION_PTR  FuncAddress;   ///< Pointer to the function that the AP will run
  AP_DATA_TRANSFER DataTransfer;  ///< Data transfer struct for optionally passing data that the AP should use as input to the function
  UINT32           ExeFlags;      ///< Flags dictating certain aspects of the AP tasking sequence
} AP_TASK;

/// Input structure for ApUtilWaitForCoreStatus.
typedef struct {
  IN       UINT8  *Status;            ///< Pointer to the 1st element of an array of values to wait for
  IN       UINT8  NumberOfElements;   ///< Number of elements in the array
  IN       UINT32 RetryCount;         ///< Number of remote read cycles to complete before quitting
  IN       UINT32 WaitForStatusFlags; ///< Flags dictating certain aspects of ApUtilWaitForCoreStatus
} AP_WAIT_FOR_STATUS;

// ExeFlags bits
#define WAIT_FOR_CORE     0x00000001ul
#define TASK_HAS_OUTPUT   0x00000002ul
#define RETURN_PARAMS     0x00000004ul
#define END_AT_HLT        0x00000008ul

// Control Byte Values
// bit 7 indicates the type of message
// 1 - control message
// 0 - launch + APIC ID = message to go
//
#define CORE_UNAVAILABLE            0xFF
#define CORE_IDLE                   0xFE
#define CORE_IDLE_HLT               0xFD
#define CORE_ACTIVE                 0xFC
#define CORE_NEEDS_PTR              0xFB
#define CORE_NEEDS_DATA_SIZE        0xFA
#define CORE_STS_DATA_READY_1       0xF9
#define CORE_STS_DATA_READY_0       0xF8
#define CORE_DATA_FLAGS_READY       0xF7
#define CORE_DATA_FLAGS_ACKNOWLEDGE 0xF6
#define CORE_DATA_PTR_READY         0xF5

// Wait Status Flags
#define WAIT_STATUS_EQUALITY 0x00000001ul
#define WAIT_INFINITELY 0

// Data Transfer Flags
#define DATA_IN_MEMORY 0x00000001ul
/*---------------------------------------------------------------------------------------*/
/**
 * Reads the 'control byte' on the designated remote core.
 *
 * This function will read the current contents of the control byte
 * on the designated core.
 *
 * @param[in]      Socket        Socket number of the target core
 * @param[in]      Die           Die number of the target core
 * @param[in]      Complex       Complex number of the target core
 * @param[in]      Core          Core number of the target core
 * @param[in]      Thread        Thread number of the target core
 * @param[in]      StdHeader     Configuration parameters pointer
 *
 * @return         The current value of the remote cores control byte
 *
 */
UINT8 ApReadRemoteCtrlByte (
  IN       UINT8 Socket,
  IN       UINT8 Die,
  IN       UINT8 Complex,
  IN       UINT8 Core,
  IN       UINT8 Thread,
  IN       AMD_CONFIG_PARAMS *StdHeader
  );

/*---------------------------------------------------------------------------------------*/
/**
 * Writes the 'control byte' on the executing core.
 *
 * This function writes data to a local register used in inter-
 * processor communication.
 *
 * @param[in]      Value         Value to write
 * @param[in]      StdHeader     Configuration parameters pointer
 *
 */
VOID ApWriteCtrlByte (
  IN       UINT8 Value,
  IN       AMD_CONFIG_PARAMS *StdHeader
  );

/*---------------------------------------------------------------------------------------*/
/**
 * Reads the 'data dword' on the designated remote core.
 *
 * This function will read the current contents of the data dword
 * on the designated core.
 *
 * @param[in]      Socket        Socket number of the target core
 * @param[in]      Die           Die number of the target core
 * @param[in]      Complex       Complex number of the target core
 * @param[in]      Core          Core number of the target core
 * @param[in]      Thread        Thread number of the target core
 * @param[in]      StdHeader     Configuration parameters pointer
 *
 * @return         The current value of the remote cores control byte
 *
 */
UINT32 ApReadRemoteDataDword (
  IN       UINT8 Socket,
  IN       UINT8 Die,
  IN       UINT8 Complex,
  IN       UINT8 Core,
  IN       UINT8 Thread,
  IN       AMD_CONFIG_PARAMS *StdHeader
  );

/*---------------------------------------------------------------------------------------*/
/**
 * Writes the 'data dword' on the executing core.
 *
 * This function writes data to a local register used in inter-
 * processor communication.
 *
 * @param[in]      Value         Value to write
 * @param[in]      StdHeader     Configuration parameters pointer
 *
 */
VOID ApWriteDataDword (
  IN       UINT32 Value,
  IN       AMD_CONFIG_PARAMS *StdHeader
  );

/*---------------------------------------------------------------------------------------*/
/**
 * Runs the given task on the specified local core.
 *
 * This function is used to invoke an AP to run a specified AGESA
 * procedure.  It can only be called by cores that have subordinate
 * APs -- the BSC at POST, or any socket-relative core 0s at Early.
 *
 * @param[in]      Socket        Socket number of the target core
 * @param[in]      Die           Die number of the target core
 * @param[in]      Complex       Complex number of the target core
 * @param[in]      Core          Core number of the target core
 * @param[in]      Thread        Thread number of the target core
 * @param[in]      TaskPtr       Function descriptor
 * @param[in]      StdHeader     Configuration parameters pointer
 *
 * @return         Return value of the task that the AP core ran,
 *                 or zero if the task was VOID.
 *
 */
UINT32 ApRunCodeOnAp (
  IN       UINT8 Socket,
  IN       UINT8 Die,
  IN       UINT8 Complex,
  IN       UINT8 Core,
  IN       UINT8 Thread,
  IN       AP_TASK *TaskPtr,
  IN       AMD_CONFIG_PARAMS *StdHeader
  );


/*---------------------------------------------------------------------------------------*/
/**
 * Main entry point for all APs in the system.
 *
 * This routine puts the AP cores in an infinite loop in which the cores
 * will poll their masters, waiting to be told to perform a task.  At early,
 * all socket-relative core zeros will receive their tasks from the BSC.
 * All others will receive their tasks from the core zero of their local
 * processor.  At the end of AmdInitEarly, all cores will switch to receiving
 * their tasks from the BSC.
 *
 * @param[in]     StdHeader       Handle to config for library and services.
 *
 */
VOID ApEntry (
  IN       AMD_CONFIG_PARAMS *StdHeader
  );

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
  );

UINT32
ApUtilTaskOnExecutingCore (
  IN       AP_TASK *TaskPtr,
  IN       AMD_CONFIG_PARAMS *StdHeader
  );

#pragma pack (pop)
#endif // _AP_COMMUNICATION_LIB_H_

