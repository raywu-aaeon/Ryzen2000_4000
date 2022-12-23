/* $NoKeywords:$ */
/**
 * @file
 *
 * mfs3.c
 *
 * Main S3 resume memory Entrypoint file
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/FEAT/S3)
 * @e \$Revision: 309090 $ @e \$Date: 2014-12-10 02:28:05 +0800 (Wed, 10 Dec 2014) $
 *
 **/
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
*
*/

/*
 *----------------------------------------------------------------------------
 *                                MODULES USED
 *
 *----------------------------------------------------------------------------
 */



#include "AGESA.h"
#include "Library/AmdBaseLib.h"
#include "Library/AmdMemBaseV5Lib.h"
#include "Library/IdsLib.h"
#include "Ids.h"
#include "cpuRegisters.h"
#include "OptionMemory.h"
#include "mm.h"
#include "mn.h"
#include "S3.h"
#include "Library/AmdMemFeatS3Lib.h"
#include "Library/AmdHeapLib.h"
#include "Library/CcxPstatesLib.h"
#include "Filecode.h"
CODE_GROUP (G2_PEI)
RDATA_GROUP (G2_PEI)

#define FILECODE LIBRARY_MEM_FEATS3LIB_MFS3_FILECODE

extern MEM_NB_SUPPORT memNBInstalled[];

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

/*----------------------------------------------------------------------------
 *                        PROTOTYPES OF LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------
 *                            EXPORTED FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */
/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *      This function is the main memory entry point for the S3 resume sequence
 *      Requirements:
 *
 *      Run-Time Requirements:
 *      1. Complete Hypertransport Bus Configuration
 *      4. BSP in Big Real Mode
 *      5. Stack available
 *
 *      @param[in]  *StdHeader - Config handle for library and services
 *
 *      @return     AGESA_STATUS
 *                          - AGESA_ALERT
 *                          - AGESA_FATAL
 *                          - AGESA_SUCCESS
 *                          - AGESA_WARNING
 */
AGESA_STATUS
AmdMemS3Resume (
  IN   AMD_CONFIG_PARAMS *StdHeader
  )
{
  AGESA_STATUS RetVal;
  MEM_MAIN_DATA_BLOCK mmData;
  S3_MEM_NB_BLOCK *S3NBPtr;
  MEM_DATA_STRUCT *MemData;
  UINT8 Die;
  UINT8 DieCount;

  //---------------------------------------------
  //  Creation of NB Block for S3 resume
  //---------------------------------------------
  RetVal = MemS3InitNB (&S3NBPtr, &MemData, &mmData, StdHeader);
  if (RetVal == AGESA_FATAL) {
    return RetVal;
  }
  DieCount = mmData.DieCount;

  //---------------------------------------------
  //1. Errata Before resume sequence
  //2. S3 Resume sequence
  //3. Errata After resume sequence
  //---------------------------------------------
  for (Die = 0; Die < DieCount; Die ++) {
    if (!S3NBPtr[Die].MemS3Resume (&S3NBPtr[Die], Die)) {
      return AGESA_FATAL;
    }
    S3NBPtr[Die].MemS3RestoreScrub (S3NBPtr[Die].NBPtr, Die);
  }

  HeapDeallocateBuffer (AMD_MEM_S3_DATA_HANDLE, StdHeader);
  return AGESA_SUCCESS;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *      This function deallocates heap space allocated in memory S3 resume.
 *
 *      @param[in]  *StdHeader - Config handle for library and services
 *
 *      @return     AGESA_STATUS
 *                          - AGESA_ALERT
 *                          - AGESA_FATAL
 *                          - AGESA_SUCCESS
 *                          - AGESA_WARNING
 */
AGESA_STATUS
MemS3Deallocate (
  IN   AMD_CONFIG_PARAMS *StdHeader
  )
{
  AGESA_STATUS RetVal;
  AGESA_STATUS tempRetVal;
  UINT8 Tab;

  RetVal = AGESA_SUCCESS;
  for (Tab = 0; Tab < NumberOfNbRegTables; Tab++) {
    HeapDeallocateBuffer (GENERATE_MEM_HANDLE (ALLOC_NB_REG_TABLE, Tab, 0, 0), StdHeader);
  }

  tempRetVal = HeapDeallocateBuffer (GENERATE_MEM_HANDLE (ALLOC_DIE_STRUCT_HANDLE, 0, 0, 0), StdHeader);
  if (tempRetVal > RetVal) {
    RetVal = tempRetVal;
  }
  tempRetVal = HeapDeallocateBuffer (AMD_MEM_AUTO_HANDLE, StdHeader);
  if (tempRetVal > RetVal) {
    RetVal = tempRetVal;
  }
  RetVal = HeapDeallocateBuffer (AMD_MEM_S3_NB_HANDLE, StdHeader);
  if (tempRetVal > RetVal) {
    RetVal = tempRetVal;
  }
  RetVal = HeapDeallocateBuffer (AMD_MEM_DATA_HANDLE, StdHeader);
  if (tempRetVal > RetVal) {
    RetVal = tempRetVal;
  }
  return RetVal;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *      This function is the entrance to get device list for memory registers.
 *
 *      @param[in, out]  **DeviceBlockHdrPtr - Pointer to the memory containing the
 *                                             device descriptor list
 *      @param[in]       *OptionMemoryInstallPtr - Pointer to the Option Memory Installer
 *      @param[in]       *StdHeader - Config handle for library and services
 *      @return          AGESA_STATUS
 *                          - AGESA_ALERT
 *                          - AGESA_FATAL
 *                          - AGESA_SUCCESS
 *                          - AGESA_WARNING
 */
AGESA_STATUS
MemFS3GetDeviceList (
  IN OUT   DEVICE_BLOCK_HEADER **DeviceBlockHdrPtr,
  IN       VOID *OptionMemoryInstallPtr,
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  UINT8 i;
  UINT16 BufferSize;
  UINT8  *BufferOffset;
  S3_MEM_NB_BLOCK *S3NBPtr;
  MEM_DATA_STRUCT *MemDataPtr;
  MEM_DATA_STRUCT MemData;
  MEM_MAIN_DATA_BLOCK mmData;
  UINT8 Die;
  UINT8 DieCount;
  AGESA_STATUS RetVal;
  ALLOCATE_HEAP_PARAMS AllocHeapParams;
  DESCRIPTOR_GROUP DeviceDescript[MAX_NODES_SUPPORTED];
  BufferSize = 0;

  MemDataPtr = &MemData;
  MemDataPtr->OptionMemoryInstallPtr = OptionMemoryInstallPtr;

  //---------------------------------------------
  //  Creation of NB Block for S3 resume
  //---------------------------------------------
  RetVal = MemS3InitNB (&S3NBPtr, &MemDataPtr, &mmData, StdHeader);
  if (RetVal == AGESA_FATAL) {
    return RetVal;
  }
  DieCount = mmData.DieCount;

  // Get the mask bit and the register list for node that presents
  for (Die = 0; Die < DieCount; Die ++) {
    S3NBPtr->MemS3GetConPCIMask (S3NBPtr[Die].NBPtr, (VOID *)&DeviceDescript[Die]);
    S3NBPtr->MemS3GetConMSRMask (S3NBPtr[Die].NBPtr, (VOID *)&DeviceDescript[Die]);
    BufferSize = BufferSize + S3NBPtr->MemS3GetRegLstPtr (S3NBPtr[Die].NBPtr, (VOID *)&DeviceDescript[Die]);
  }

  // Base on the size of the device list, apply for a buffer for it.
  AllocHeapParams.RequestedBufferSize = BufferSize + sizeof (DEVICE_BLOCK_HEADER);
  AllocHeapParams.BufferHandle = AMD_S3_NB_INFO_BUFFER_HANDLE;
  AllocHeapParams.Persist = HEAP_S3_RESUME;
  AGESA_TESTPOINT (TpIfBeforeAllocateMemoryS3SaveBuffer, StdHeader);
  if (HeapAllocateBuffer (&AllocHeapParams, StdHeader) != AGESA_SUCCESS) {
    return AGESA_FATAL;
  }
  AGESA_TESTPOINT (TpIfAfterAllocateMemoryS3SaveBuffer, StdHeader);

  *DeviceBlockHdrPtr = (DEVICE_BLOCK_HEADER *) AllocHeapParams.BufferPtr;
  (*DeviceBlockHdrPtr)->Revision = S3NBPtr->S3DatablobRev;
  (*DeviceBlockHdrPtr)->RelativeOrMaskOffset = (UINT16) AllocHeapParams.RequestedBufferSize;

  // Copy device list on the stack to the heap.
  BufferOffset = sizeof (DEVICE_BLOCK_HEADER) + AllocHeapParams.BufferPtr;
  for (Die = 0; Die < DieCount; Die ++) {
    for (i = PRESELFREF; i <= POSTSELFREF; i ++) {
      // Copy PCI device descriptor to the heap if it exists.
      if (DeviceDescript[Die].PCIDevice[i].RegisterListID != 0xFFFFFFFF) {
        LibAmdMemCopy ((VOID *) BufferOffset, &(DeviceDescript[Die].PCIDevice[i]), sizeof (PCI_DEVICE_DESCRIPTOR), StdHeader);
        (*DeviceBlockHdrPtr)->NumDevices ++;
        BufferOffset += sizeof (PCI_DEVICE_DESCRIPTOR);
      }
      // Copy conditional PCI device descriptor to the heap if it exists.
      if (DeviceDescript[Die].CPCIDevice[i].RegisterListID != 0xFFFFFFFF) {
        LibAmdMemCopy ((VOID *) BufferOffset, &(DeviceDescript[Die].CPCIDevice[i]), sizeof (CONDITIONAL_PCI_DEVICE_DESCRIPTOR), StdHeader);
        (*DeviceBlockHdrPtr)->NumDevices ++;
        BufferOffset += sizeof (CONDITIONAL_PCI_DEVICE_DESCRIPTOR);
      }
      // Copy MSR device descriptor to the heap if it exists.
      if (DeviceDescript[Die].MSRDevice[i].RegisterListID != 0xFFFFFFFF) {
        LibAmdMemCopy ((VOID *) BufferOffset, &(DeviceDescript[Die].MSRDevice[i]), sizeof (MSR_DEVICE_DESCRIPTOR), StdHeader);
        (*DeviceBlockHdrPtr)->NumDevices ++;
        BufferOffset += sizeof (MSR_DEVICE_DESCRIPTOR);
      }
      // Copy conditional MSR device descriptor to the heap if it exists.
      if (DeviceDescript[Die].CMSRDevice[i].RegisterListID != 0xFFFFFFFF) {
        LibAmdMemCopy ((VOID *) BufferOffset, &(DeviceDescript[Die].PCIDevice[i]), sizeof (CONDITIONAL_MSR_DEVICE_DESCRIPTOR), StdHeader);
        (*DeviceBlockHdrPtr)->NumDevices ++;
        BufferOffset += sizeof (CONDITIONAL_MSR_DEVICE_DESCRIPTOR);
      }
    }
  }

  return RetVal;
}


/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *      This function initialize the northbridge block and apply for heap space
 *      before any function call is made to memory component during S3 resume.
 *
 *      @param[in]       *StdHeader - Config handle for library and services
 *      @return          AGESA_STATUS
 *                          - AGESA_ALERT
 *                          - AGESA_FATAL
 *                          - AGESA_SUCCESS
 *                          - AGESA_WARNING
 */
AGESA_STATUS
MemS3ResumeInitNB (
  IN   AMD_CONFIG_PARAMS *StdHeader
  )
{
  AGESA_STATUS RetVal;
  MEM_MAIN_DATA_BLOCK mmData;
  S3_MEM_NB_BLOCK *S3NBPtr;
  MEM_DATA_STRUCT *MemData;
  UINT8 Die;
  UINT8 DieCount;
  UINT8 SpecialCaseHeapSize;
  ALLOCATE_HEAP_PARAMS AllocHeapParams;
  S3_SPECIAL_CASE_HEAP_HEADER SpecialHeapHeader[MAX_NODES_SUPPORTED];

  SpecialCaseHeapSize = 0;

  //---------------------------------------------
  //  Creation of NB Block for S3 resume
  //---------------------------------------------
  RetVal = MemS3InitNB (&S3NBPtr, &MemData, &mmData, StdHeader);
  if (RetVal == AGESA_FATAL) {
    return RetVal;
  }
  DieCount = mmData.DieCount;

  //--------------------------------------------------
  //  Apply for heap space for special case registers
  //--------------------------------------------------
  for (Die = 0; Die < DieCount; Die ++) {
    // Construct the header for the special case heap.
    SpecialHeapHeader[Die].Node = S3NBPtr[Die].NBPtr->Node;
    SpecialHeapHeader[Die].Offset = SpecialCaseHeapSize + (DieCount * (sizeof (S3_SPECIAL_CASE_HEAP_HEADER)));
    SpecialCaseHeapSize = SpecialCaseHeapSize + S3NBPtr->MemS3SpecialCaseHeapSize;
  }
  AllocHeapParams.RequestedBufferSize = (DieCount * (sizeof (S3_SPECIAL_CASE_HEAP_HEADER))) + SpecialCaseHeapSize;
  AllocHeapParams.BufferHandle = AMD_MEM_S3_DATA_HANDLE;
  AllocHeapParams.Persist = HEAP_SYSTEM_MEM;
  if (HeapAllocateBuffer (&AllocHeapParams, StdHeader) != AGESA_SUCCESS) {
    PutEventLog (AGESA_FATAL, MEM_ERROR_HEAP_ALLOCATE_FOR_S3_SPECIAL_CASE_REGISTERS, S3NBPtr[Die].NBPtr->Node, 0, 0, 0, StdHeader);
    SetMemError (AGESA_FATAL, S3NBPtr[Die].NBPtr->MCTPtr);
    ASSERT(FALSE); // Could not allocate heap space for "S3_SPECIAL_CASE_HEAP_HEADER"
    return AGESA_FATAL;
  }
  LibAmdMemCopy ((VOID *) AllocHeapParams.BufferPtr, (VOID *) SpecialHeapHeader, (sizeof (S3_SPECIAL_CASE_HEAP_HEADER) * DieCount), StdHeader);
  return AGESA_SUCCESS;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *      This function returns the PCI device register list according to the register
 *      list ID.
 *
 *      @param[in]       *Device - pointer to the PCI_DEVICE_DESCRIPTOR
 *      @param[out]      **RegisterHdr - pointer to the address of the register list
 *      @param[in]       *StdHeader - Config handle for library and services
 *
 *      @return          AGESA_STATUS
 *                          - AGESA_ALERT
 *                          - AGESA_FATAL
 *                          - AGESA_SUCCESS
 *                          - AGESA_WARNING
 */
AGESA_STATUS
MemFS3GetPciDeviceRegisterList (
  IN       PCI_DEVICE_DESCRIPTOR     *Device,
     OUT   PCI_REGISTER_BLOCK_HEADER **RegisterHdr,
  IN       AMD_CONFIG_PARAMS         *StdHeader
  )
{
  AGESA_STATUS RetVal;
  S3_MEM_NB_BLOCK *S3NBPtr;
  VOID *RegisterHeader;
  LOCATE_HEAP_PTR LocHeap;
  MEM_NB_BLOCK *NBPtr;
  LocHeap.BufferHandle = AMD_MEM_S3_NB_HANDLE;

  AGESA_TESTPOINT (TpIfBeforeLocateS3PciBuffer, StdHeader);
  if (HeapLocateBuffer (&LocHeap, StdHeader) == AGESA_SUCCESS) {
    S3NBPtr = (S3_MEM_NB_BLOCK *)LocHeap.BufferPtr;
  } else {
    ASSERT(FALSE) ; // No match for heap status, but could not locate "AMD_MEM_S3_NB_HANDLE" in heap for S3GetMsr
    return AGESA_FATAL;
  }
  AGESA_TESTPOINT (TpIfAfterLocateS3PciBuffer, StdHeader);

  // NB block has already been constructed by main block.
  // No need to construct it here.
  NBPtr = S3NBPtr[Device->Node].NBPtr;
  RetVal = S3NBPtr[Device->Node].MemS3GetDeviceRegLst (Device->RegisterListID, &RegisterHeader, NBPtr);
  *RegisterHdr = (PCI_REGISTER_BLOCK_HEADER *)RegisterHeader;
  return RetVal;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *      This function returns the conditional PCI device register list according
 *      to the register list ID.
 *
 *      @param[in]       *Device - pointer to the CONDITIONAL_PCI_DEVICE_DESCRIPTOR
 *      @param[out]      **RegisterHdr - pointer to the address of the register list
 *      @param[in]       *StdHeader - Config handle for library and services
 *
 *      @return          AGESA_STATUS
 *                          - AGESA_ALERT
 *                          - AGESA_FATAL
 *                          - AGESA_SUCCESS
 *                          - AGESA_WARNING
 */
AGESA_STATUS
MemFS3GetCPciDeviceRegisterList (
  IN       CONDITIONAL_PCI_DEVICE_DESCRIPTOR *Device,
     OUT   CPCI_REGISTER_BLOCK_HEADER        **RegisterHdr,
  IN       AMD_CONFIG_PARAMS                 *StdHeader
  )
{
  AGESA_STATUS RetVal;
  S3_MEM_NB_BLOCK *S3NBPtr;
  VOID *RegisterHeader;
  LOCATE_HEAP_PTR LocHeap;
  MEM_NB_BLOCK *NBPtr;

  LocHeap.BufferHandle = AMD_MEM_S3_NB_HANDLE;

  AGESA_TESTPOINT (TpIfBeforeLocateS3CPciBuffer, StdHeader);
  if (HeapLocateBuffer (&LocHeap, StdHeader) == AGESA_SUCCESS) {
    S3NBPtr = (S3_MEM_NB_BLOCK *)LocHeap.BufferPtr;
  } else {
    ASSERT(FALSE) ; // No match for heap status, but could not locate "AMD_MEM_S3_NB_HANDLE" in heap for S3GetMsr
    return AGESA_FATAL;
  }
  AGESA_TESTPOINT (TpIfAfterLocateS3CPciBuffer, StdHeader);

  // NB block has already been constructed by main block.
  // No need to construct it here.
  NBPtr = S3NBPtr[Device->Node].NBPtr;
  RetVal = S3NBPtr[Device->Node].MemS3GetDeviceRegLst (Device->RegisterListID, &RegisterHeader, NBPtr);
  *RegisterHdr = (CPCI_REGISTER_BLOCK_HEADER *)RegisterHeader;
  return RetVal;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *      This function returns the MSR device register list according to the register
 *      list ID.
 *
 *      @param[in]       *Device - pointer to the MSR_DEVICE_DESCRIPTOR
 *      @param[out]      **RegisterHdr - pointer to the address of the register list
 *      @param[in]       *StdHeader - Config handle for library and services
 *
 *      @return          AGESA_STATUS
 *                          - AGESA_ALERT
 *                          - AGESA_FATAL
 *                          - AGESA_SUCCESS
 *                          - AGESA_WARNING
 */
AGESA_STATUS
MemFS3GetMsrDeviceRegisterList (
  IN       MSR_DEVICE_DESCRIPTOR     *Device,
     OUT   MSR_REGISTER_BLOCK_HEADER **RegisterHdr,
  IN       AMD_CONFIG_PARAMS         *StdHeader
  )
{
  AGESA_STATUS RetVal;
  S3_MEM_NB_BLOCK *S3NBPtr;
  VOID *RegisterHeader;
  LOCATE_HEAP_PTR LocHeap;
  MEM_NB_BLOCK *NBPtr;

  LocHeap.BufferHandle = AMD_MEM_S3_NB_HANDLE;

  AGESA_TESTPOINT (TpIfBeforeLocateS3MsrBuffer, StdHeader);
  if (HeapLocateBuffer (&LocHeap, StdHeader) == AGESA_SUCCESS) {
    S3NBPtr = (S3_MEM_NB_BLOCK *)LocHeap.BufferPtr;
  } else {
    ASSERT(FALSE) ; // No match for heap status, but could not locate "AMD_MEM_S3_NB_HANDLE" in heap for S3GetMsr
    return AGESA_FATAL;
  }
  AGESA_TESTPOINT (TpIfAfterLocateS3MsrBuffer, StdHeader);

  // NB block has already been constructed by main block.
  // No need to construct it here.
  NBPtr = S3NBPtr[BSP_DIE].NBPtr;
  RetVal = S3NBPtr[BSP_DIE].MemS3GetDeviceRegLst (Device->RegisterListID, &RegisterHeader, NBPtr);
  *RegisterHdr = (MSR_REGISTER_BLOCK_HEADER *)RegisterHeader;
  return RetVal;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *      This function returns the conditional MSR device register list according
 *      to the register list ID.
 *
 *      @param[in]       *Device - pointer to the CONDITIONAL_PCI_DEVICE_DESCRIPTOR
 *      @param[out]      **RegisterHdr - pointer to the address of the register list
 *      @param[in]       *StdHeader - Config handle for library and services
 *
 *      @return          AGESA_STATUS
 *                          - AGESA_ALERT
 *                          - AGESA_FATAL
 *                          - AGESA_SUCCESS
 *                          - AGESA_WARNING
 */
AGESA_STATUS
MemFS3GetCMsrDeviceRegisterList (
  IN       CONDITIONAL_MSR_DEVICE_DESCRIPTOR     *Device,
     OUT   CMSR_REGISTER_BLOCK_HEADER            **RegisterHdr,
  IN       AMD_CONFIG_PARAMS                     *StdHeader
  )
{
  AGESA_STATUS RetVal;
  S3_MEM_NB_BLOCK *S3NBPtr;
  VOID *RegisterHeader;
  LOCATE_HEAP_PTR LocHeap;
  MEM_NB_BLOCK *NBPtr;

  LocHeap.BufferHandle = AMD_MEM_S3_NB_HANDLE;

  AGESA_TESTPOINT (TpIfBeforeLocateS3CMsrBuffer, StdHeader);
  if (HeapLocateBuffer (&LocHeap, StdHeader) == AGESA_SUCCESS) {
    S3NBPtr = (S3_MEM_NB_BLOCK *)LocHeap.BufferPtr;
  } else {
    ASSERT(FALSE) ; // No match for heap status, but could not locate "AMD_MEM_S3_NB_HANDLE" in heap for S3GetMsr
    return AGESA_FATAL;
  }
  AGESA_TESTPOINT (TpIfAfterLocateS3CMsrBuffer, StdHeader);

  // NB block has already been constructed by main block.
  // No need to construct it here.
  NBPtr = S3NBPtr[BSP_DIE].NBPtr;
  RetVal = S3NBPtr[BSP_DIE].MemS3GetDeviceRegLst (Device->RegisterListID, &RegisterHeader, NBPtr);
  *RegisterHdr = (CMSR_REGISTER_BLOCK_HEADER *)RegisterHeader;
  return RetVal;
}

/*----------------------------------------------------------------------------
 *                              LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *      This function initialize needed data structures for S3 resume.
 *
 *      @param[in, out]  **S3NBPtr - Pointer to the pointer of northbridge block.
 *      @param[in, out]  *MemPtr - Pointer to MEM_DATA_STRUCT.
 *      @param[in, out]  *mmData - Pointer to MEM_MAIN_DATA_BLOCK.
 *      @param[in]       *StdHeader - Config handle for library and services.
 *
 *      @return          AGESA_STATUS
 *                          - AGESA_ALERT
 *                          - AGESA_FATAL
 *                          - AGESA_SUCCESS
 *                          - AGESA_WARNING
 */
AGESA_STATUS
MemS3InitNB (
  IN OUT   S3_MEM_NB_BLOCK **S3NBPtr,
  IN OUT   MEM_DATA_STRUCT **MemPtr,
  IN OUT   MEM_MAIN_DATA_BLOCK *mmData,
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  AGESA_STATUS RetVal;
  LOCATE_HEAP_PTR LocHeap;
  MEM_NB_BLOCK *NBPtr;
  ALLOCATE_HEAP_PARAMS AllocHeapParams;
  UINT8 Die;
  UINT8 DieCount;
  BOOLEAN SkipScan;
  UINTN VoltageInuV;
  UINTN PowerInmW;
  MEM_OPTION_INSTALL_STRUCT *OptionMemoryInstallPtr;

  OptionMemoryInstallPtr = (MEM_OPTION_INSTALL_STRUCT *) ((*MemPtr)->OptionMemoryInstallPtr);

  SkipScan = FALSE;
  LocHeap.BufferHandle = AMD_MEM_DATA_HANDLE;
  if (HeapLocateBuffer (&LocHeap, StdHeader) == AGESA_SUCCESS) {
    // NB block has already been constructed by main block.
    // No need to construct it here.
    *MemPtr = (MEM_DATA_STRUCT *)LocHeap.BufferPtr;
    SkipScan = TRUE;
  } else {
    AllocHeapParams.RequestedBufferSize = sizeof (MEM_DATA_STRUCT);
    AllocHeapParams.BufferHandle = AMD_MEM_DATA_HANDLE;
    AllocHeapParams.Persist = HEAP_SYSTEM_MEM;
    if (HeapAllocateBuffer (&AllocHeapParams, StdHeader) != AGESA_SUCCESS) {
      ASSERT(FALSE); // Allocate failed for MEM_DATA_STRUCT
      return AGESA_FATAL;
    }
    *MemPtr = (MEM_DATA_STRUCT *)AllocHeapParams.BufferPtr;
    LibAmdMemCopy (&(*MemPtr)->StdHeader, StdHeader, sizeof (AMD_CONFIG_PARAMS), StdHeader);

    CcxGetPstateInfo (0, SwPstate0, (UINTN *)&(*MemPtr)->TscRate, &VoltageInuV, &PowerInmW, &(*MemPtr)->StdHeader);

  }
  mmData->MemPtr = *MemPtr;

  if (!SkipScan) {
    RetVal = MemSocketScan (mmData);
    if (RetVal == AGESA_FATAL) {
      return RetVal;
    }
  } else {
    // We already have initialize data block, no need to do it again.
    mmData->DieCount = mmData->MemPtr->DieCount;
  }
  DieCount = mmData->DieCount;

  //---------------------------------------------
  //  Creation of NB Block for S3 resume
  //---------------------------------------------
  // Search for AMD_MEM_AUTO_HANDLE on the heap first.
  // Only apply for space on the heap if cannot find AMD_MEM_AUTO_HANDLE on the heap.
  LocHeap.BufferHandle = AMD_MEM_S3_NB_HANDLE;
  if (HeapLocateBuffer (&LocHeap, StdHeader) == AGESA_SUCCESS) {
    // NB block has already been constructed by main block.
    // No need to construct it here.
    *S3NBPtr = (S3_MEM_NB_BLOCK *)LocHeap.BufferPtr;
  } else {
    AllocHeapParams.RequestedBufferSize = (DieCount * (sizeof (S3_MEM_NB_BLOCK)));
    AllocHeapParams.BufferHandle = AMD_MEM_S3_NB_HANDLE;
    AllocHeapParams.Persist = HEAP_SYSTEM_MEM;
    if (HeapAllocateBuffer (&AllocHeapParams, StdHeader) != AGESA_SUCCESS) {
      ASSERT(FALSE); // Could not allocate space for "S3_MEM_NB_BLOCK"
      return AGESA_FATAL;
    }
    *S3NBPtr = (S3_MEM_NB_BLOCK *)AllocHeapParams.BufferPtr;

    LocHeap.BufferHandle = AMD_MEM_AUTO_HANDLE;
    if (HeapLocateBuffer (&LocHeap, StdHeader) == AGESA_SUCCESS) {
      // NB block has already been constructed by main block.
      // No need to construct it here.
      NBPtr = (MEM_NB_BLOCK *)LocHeap.BufferPtr;
    } else {
      AllocHeapParams.RequestedBufferSize = (DieCount * (sizeof (MEM_NB_BLOCK)));
      AllocHeapParams.BufferHandle = AMD_MEM_AUTO_HANDLE;
      AllocHeapParams.Persist = HEAP_SYSTEM_MEM;
      if (HeapAllocateBuffer (&AllocHeapParams, StdHeader) != AGESA_SUCCESS) {
        ASSERT(FALSE); // Allocate failed for "MEM_NB_BLOCK"
        return AGESA_FATAL;
      }
      NBPtr = (MEM_NB_BLOCK *)AllocHeapParams.BufferPtr;
    }
    // Construct each die.
    for (Die = 0; Die < DieCount; Die ++) {
      ((*S3NBPtr)[Die]).NBPtr = &NBPtr[Die];
      if (OptionMemoryInstallPtr->memNBInstalled.MemS3ResumeConstructNBBlock != 0) {
        if (OptionMemoryInstallPtr->memNBInstalled.MemS3ResumeConstructNBBlock ((VOID *)&((*S3NBPtr)[Die]), *MemPtr, Die) != TRUE) {
          ASSERT (FALSE);
          return AGESA_FATAL;
        }
      }
    }
  }
  return AGESA_SUCCESS;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function determines if the PSP is present
 *
 *      @param[in]       *StdHeader - Config handle for library and services.
 *
 *      @return          AGESA_STATUS
 *                          - AGESA_FATAL
 *                          - AGESA_SUCCESS
 */
AGESA_STATUS
AmdMemDoResume (
  IN   AMD_CONFIG_PARAMS *StdHeader
  )
{
  S3_MEM_NB_BLOCK *S3NBPtr;
  MEM_NB_BLOCK *NBPtr;
  LOCATE_HEAP_PTR LocHeap;

  LocHeap.BufferHandle = AMD_MEM_S3_NB_HANDLE;
  S3NBPtr = NULL;
  if (HeapLocateBuffer (&LocHeap, StdHeader) == AGESA_SUCCESS) {
    S3NBPtr = (S3_MEM_NB_BLOCK *)LocHeap.BufferPtr;
    NBPtr = ((S3_MEM_NB_BLOCK *)S3NBPtr)->NBPtr;
  } else {
    ASSERT (FALSE) ; // No match for heap status, but could not locate "AMD_MEM_S3_NB_HANDLE" in heap for S3GetMsr
    return AGESA_FATAL;
  }

  if (S3NBPtr[BSP_DIE].MemS3PspPlatformSecureBootEn (S3NBPtr[BSP_DIE].NBPtr) == NBPtr->MemRunningOnPsp (NBPtr)) {
    return AGESA_SUCCESS;
  } else {
    return AGESA_FATAL;
  }
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function determines if the revision S3 data blob matches the S3 engine
 *
 *      @param[in]       Storage    - Beginning of the device list.
 *      @param[in]       *StdHeader - Config handle for library and services.
 *
 *      @return          AGESA_STATUS
 *                          - AGESA_FATAL
 *                          - AGESA_SUCCESS
 */
AGESA_STATUS
AmdMemS3DatablobRevMatch (
  IN   VOID              *Storage,
  IN   AMD_CONFIG_PARAMS *StdHeader
  )
{
  S3_MEM_NB_BLOCK *S3NBPtr;
  LOCATE_HEAP_PTR LocHeap;
  DEVICE_BLOCK_HEADER *DeviceList;

  DeviceList = (DEVICE_BLOCK_HEADER *) Storage;

  LocHeap.BufferHandle = AMD_MEM_S3_NB_HANDLE;
  S3NBPtr = NULL;
  if (HeapLocateBuffer (&LocHeap, StdHeader) == AGESA_SUCCESS) {
    S3NBPtr = (S3_MEM_NB_BLOCK *)LocHeap.BufferPtr;
  } else {
    ASSERT (FALSE) ; // No match for heap status, but could not locate "AMD_MEM_S3_NB_HANDLE" in heap for S3GetMsr
    return AGESA_FATAL;
  }

  if (S3NBPtr[BSP_DIE].S3DatablobRev == DeviceList->Revision) {
    return AGESA_SUCCESS;
  } else {
    ASSERT (FALSE);
    return AGESA_FATAL;
  }
}

