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
 */
#ifndef _AMD_NBIO_PCIE_TOPOLOGY_PPI_H_
#define _AMD_NBIO_PCIE_TOPOLOGY_PPI_H_

// Current PPI revision
#define AMD_NBIO_PCIE_TOPOLOGY_REVISION   0x00

typedef struct _PEI_AMD_NBIO_PCIE_TOPOLOGY_PPI PEI_AMD_NBIO_PCIE_TOPOLOGY_PPI; // Do we need this?

//
// PPI prototype
//
/**
  CreateTopologyTable
    This function will create a topology table with X number of entries, using the default settings for all entries.
    All devices will be initially unused devices  i.e. they will be ignored when passed in to the DXIO init.

  @param SocketNumber      Socket number of topology entries to allocate
  @param NumberOfEntries   Number of topology entries to allocate. Do not include table termination entry which is added automatically
  @param AllocateSuccess   Function was able to allocate table, where True/False is Success/Failure respectively. Pointer is passed in.
  @param TablePointer      Pointer to the newly created table. Memory does not need to be allocated beforehand

  @return EFI_STATUS       Always returns EFI_SUCCESS
**/
typedef
EFI_STATUS
(EFIAPI * AMD_NBIO_PCIE_TOPOLOGY_CREATE_TABLE) (
  IN  UINTN                           SocketNumber,
  IN  UINTN                           NumberOfEntries,
  OUT BOOLEAN                         *AllocateSuccess,
  OUT DXIO_COMPLEX_DESCRIPTOR         **InTablePointer
  );

//
// PPI prototype
//
/**
  InitializeTopologyEntry
    This function will initialize the first Unused entry using default values for the specified engine type

  @param TablePointer        Pointer to table containing entries to work with
  @param EngineType          Engine Type
  @param StartLane           Start lane number
  @param EndLane             End lane number
  @param ResetId             Reset ID number
  @param Device              Requested PCI Device (not applicable for non PCI devices)
  @param Function            Requested PCI Function (not applicable for non PCI devices)
  @param InitializeSuccess   Function was able to initialize entry, where True/False is Success/Failure respectively.
  @param EntryHandle         Unique handle ID for entry, pointer is passed in.

  @return EFI_STATUS         Always returns EFI_SUCCESS
**/
typedef
EFI_STATUS
(EFIAPI * AMD_NBIO_PCIE_TOPOLOGY_INITIALIZE_ENTRY) (
  IN  DXIO_COMPLEX_DESCRIPTOR         **InTablePointer,
  IN  UINT8                           EngineType,
  IN  UINT8                           StartLane,
  IN  UINT8                           EndLane,
  IN  UINT8                           ResetId,
  IN  UINT8                           Device,
  IN  UINT8                           Function,
  OUT BOOLEAN                         *InitializeSuccess,
  OUT UINT64                          *EntryHandle
  );

//
// PPI prototype
//
/**
  InitializeTopologyEntry
    This function will initialize the first Unused entry using default values for the specified engine type

  @param TablePointer        Pointer to table containing entries to work with
  @param EngineType          Engine Type
  @param StartLane           Start lane number
  @param EndLane             End lane number
  @param ResetId             Reset ID number
  @param InitializeSuccess   Function was able to initialize entry, where True/False is Success/Failure respectively.
  @param EntryHandle         Unique handle ID for entry, pointer is passed in.

  @return EFI_STATUS         Always returns EFI_SUCCESS
**/
typedef
EFI_STATUS
(EFIAPI * AMD_NBIO_PCIE_TOPOLOGY_ADD_PARAMETER) (
  IN  DXIO_COMPLEX_DESCRIPTOR         **TablePointer,
  IN  UINT64                          EntryHandle,
  IN  PORT_PARAM                      Parameter,
  OUT BOOLEAN                         *AddParamSuccess
  );

//
// PPI prototype
//
/**
  RemoveEntry
    This function will mark a previously created entry as unused and remove any parameters in the list.

  @param TablePointer             PEI_AMD_NBIO_PCIE_TOPOLOGY_PPI instance Pointer to table containing entries to work with  @param EntryHandle
  @param EntryHandle              Unique handle ID associated with a given entry
  @param RemoveEntrySuccess       Function was able to remove entry, where True/False is Success/Failure respectively. Pointer Is passed in

  @return EFI_STATUS              Always returns EFI_SUCCESS
**/
typedef
EFI_STATUS
(EFIAPI * AMD_NBIO_PCIE_TOPOLOGY_REMOVE_ENTRY) (
  IN  DXIO_COMPLEX_DESCRIPTOR         **TablePointer,
  IN  UINT64                          EntryHandle,
  OUT BOOLEAN                         *RemoveEntrySuccess
  );

//
// PPI prototype
//
/**
  IncreaseTableSize
   This function wouldis used to grow the table beyond the initial allocation. New memory is allocated and the old
   table is copied over. Do not use on any memory not associated with the heap.

  @param TablePointer             PEI_AMD_NBIO_PCIE_TOPOLOGY_PPI instance Pointer to table containing entries to work with
  @param NewSize                  New size of the table, in entries. Must be greater than the current size
  @param IncreaseSuccess          Returns false if there is an issue with the input parameters or the allocation process. True if success.

  @return EFI_STATUS              Always returns EFI_SUCCESS;
**/
typedef
EFI_STATUS
(EFIAPI * AMD_NBIO_PCIE_TOPOLOGY_INCREASE_TABLE_SIZE) (
  IN  DXIO_COMPLEX_DESCRIPTOR         **TablePointer,
  IN  UINTN                           NewSize,
  OUT BOOLEAN                         *IncreaseSuccess
  );

// TODO :
// Need some sort of function to get table pointer?
// Need some sort of way to block these calls after DXIO has run? Maybe uninstall protocol interface?

///
/// The Ppi of Pcie Topology
///
typedef struct _PEI_AMD_NBIO_PCIE_TOPOLOGY_PPI {
  UINT32 Revision;                                       ///< revision
  AMD_NBIO_PCIE_TOPOLOGY_CREATE_TABLE         CreateTopologyTable;        ///<
  AMD_NBIO_PCIE_TOPOLOGY_INITIALIZE_ENTRY     InitializeTopologyEntry;    ///<
  AMD_NBIO_PCIE_TOPOLOGY_ADD_PARAMETER        AddParameter;               ///<
  AMD_NBIO_PCIE_TOPOLOGY_REMOVE_ENTRY         RemoveEntry;                ///<
  AMD_NBIO_PCIE_TOPOLOGY_INCREASE_TABLE_SIZE  IncreaseTableSize;          ///<
} PEI_AMD_NBIO_PCIE_TOPOLOGY_PPI;

extern EFI_GUID gAmdNbioPcieTopologyPpiGuid ;

#endif /* _AMD_NBIO_PCIE_TOPOLOGY_PPI_H_ */

