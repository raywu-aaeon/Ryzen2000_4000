/* $NoKeywords:$ */
/**
 * @file
 *
 * mmflow.c
 *
 * Main Memory Flow Entrypoint file
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/Main)
 * @e \$Revision: 318592 $ @e \$Date: 2015-05-12 13:18:53 -0500 (Tue, 12 May 2015) $
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
#include "Library/AmdCalloutLib.h"
#include "Library/IdsLib.h"
#include "Ids.h"
#include "PlatformMemoryConfiguration.h"
#include "mu.h"
#include "Library/AmdHeapLib.h"
#include "Library/CcxPstatesLib.h"
#include "OptionMemory.h"
#include "Filecode.h"
#define FILECODE LIBRARY_MEM_MAINLIB_MMFLOW_FILECODE

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
VOID
STATIC
MemSPDDataProcess (
  IN OUT   MEM_DATA_STRUCT *MemPtr
  );

/*----------------------------------------------------------------------------
 *                            EXPORTED FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */
/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *      This function is the main memory configuration function for DR DDR3
 *
 *      Requirements:
 *
 *      Run-Time Requirements:
 *      1. Complete Hypertransport Bus Configuration
 *      2. AmdMemInitDataStructDef must be run to set default values
 *      3. MSR bit to allow access to high PCI regs set on all nodes
 *      4. BSP in Big Real Mode
 *      5. Stack available
 *      6. MCG_CTL=-1, MC4_EN=0 for all CPUs
 *      7. MCi_STS from shutdown/warm reset recorded (if desired) prior to entry
 *      8. All var MTRRs reset to zero
 *      9. State of NB_CFG.DisDatMsk set properly on all CPUs
 *
 *     @param[in,out]   *MemPtr   - Pointer to the MEM_DATA_STRUCT
 *
 *     @return          AGESA_STATUS
 *                          - AGESA_ALERT
 *                          - AGESA_FATAL
 *                          - AGESA_SUCCESS
 *                          - AGESA_WARNING
 */
AGESA_STATUS
AmdMemAuto (
  IN OUT   MEM_DATA_STRUCT *MemPtr
  )
{
  MEM_SHARED_DATA  mmSharedData;
  MEM_MAIN_DATA_BLOCK mmData;
  MEM_NB_BLOCK *NBPtr;
  MEM_TECH_BLOCK *TechPtr;
  ALLOCATE_HEAP_PARAMS AllocHeapParams;
  AGESA_STATUS Retval;
  UINT8 i;
  UINT8 Die;
  UINT8 DieCount;
  UINT8 Tab;
  UINTN VoltageInuV;
  UINTN PowerInmW;
  BOOLEAN TechInstalled;
  TECHNOLOGY_TYPE *TechTypePtr;
  MEM_OPTION_INSTALL_STRUCT *OptionMemoryInstallPtr;

  ASSERT (MemPtr != NULL);
  OptionMemoryInstallPtr = (MEM_OPTION_INSTALL_STRUCT *)MemPtr->OptionMemoryInstallPtr;

  AGESA_TESTPOINT (TpProcMemAmdMemAuto, &MemPtr->StdHeader);
  IDS_PERF_TIMESTAMP (TP_BEGINPROCAMDMEMAUTO, &MemPtr->StdHeader);

  IDS_HDT_CONSOLE (MEM_FLOW, "MEM PARAMS:\n");
  IDS_HDT_CONSOLE (MEM_FLOW, "\tBottomIo : %04x\n", MemPtr->ParameterListPtr->BottomIo);
  IDS_HDT_CONSOLE (MEM_FLOW, "\tMemHoleRemap : %d\n", MemPtr->ParameterListPtr->MemHoleRemapping);
  IDS_HDT_CONSOLE (MEM_FLOW, "\tLimitBelow1TB : %d\n", MemPtr->ParameterListPtr->LimitMemoryToBelow1Tb);
  IDS_HDT_CONSOLE (MEM_FLOW, "\tUserTimingMode : %d\n", MemPtr->ParameterListPtr->UserTimingMode);
  IDS_HDT_CONSOLE (MEM_FLOW, "\tMemClockValue : %d\n", MemPtr->ParameterListPtr->MemClockValue);
  IDS_HDT_CONSOLE (MEM_FLOW, "\tBankIntlv : %d\n", MemPtr->ParameterListPtr->EnableBankIntlv);
  IDS_HDT_CONSOLE (MEM_FLOW, "\tNodeIntlv : %d\n", MemPtr->ParameterListPtr->EnableNodeIntlv);
  IDS_HDT_CONSOLE (MEM_FLOW, "\tChannelIntlv : %d\n", MemPtr->ParameterListPtr->EnableChannelIntlv);
  IDS_HDT_CONSOLE (MEM_FLOW, "\tEccFeature : %d\n", MemPtr->ParameterListPtr->EnableEccFeature);
  IDS_HDT_CONSOLE (MEM_FLOW, "\tPowerDown : %d\n", MemPtr->ParameterListPtr->EnablePowerDown);
  IDS_HDT_CONSOLE (MEM_FLOW, "\tMacDefault : %d\n", MemPtr->ParameterListPtr->DramMacDefault);
  IDS_HDT_CONSOLE (MEM_FLOW, "\tExtendedTemperatureRange : %d\n", MemPtr->ParameterListPtr->EnableExtendedTemperatureRange);
  IDS_HDT_CONSOLE (MEM_FLOW, "\tDramTempControlledRefreshEn : %d\n", MemPtr->ParameterListPtr->DramTempControlledRefreshEn);
  IDS_HDT_CONSOLE (MEM_FLOW, "\tOnLineSpare : %d\n", MemPtr->ParameterListPtr->EnableOnLineSpareCtl);
  IDS_HDT_CONSOLE (MEM_FLOW, "\tParity : %d\n", MemPtr->ParameterListPtr->EnableParity);
  IDS_HDT_CONSOLE (MEM_FLOW, "\tBankSwizzle : %d\n", MemPtr->ParameterListPtr->EnableBankSwizzle);
  IDS_HDT_CONSOLE (MEM_FLOW, "\tMemClr : %d\n", MemPtr->ParameterListPtr->EnableMemClr);
  IDS_HDT_CONSOLE (MEM_FLOW, "\tUmaVersion : %d\n", MemPtr->ParameterListPtr->UmaVersion);
  IDS_HDT_CONSOLE (MEM_FLOW, "\tUmaMode : %d\n", MemPtr->ParameterListPtr->UmaMode);
  IDS_HDT_CONSOLE (MEM_FLOW, "\tUmaSize : %d\n", MemPtr->ParameterListPtr->UmaSize);
  IDS_HDT_CONSOLE (MEM_FLOW, "\tMemRestoreCtl : %d\n", MemPtr->ParameterListPtr->MemRestoreCtl);
  IDS_HDT_CONSOLE (MEM_FLOW, "\tSaveMemContextCtl : %d\n", MemPtr->ParameterListPtr->SaveMemContextCtl);
  IDS_HDT_CONSOLE (MEM_FLOW, "\tExternalVrefCtl : %d\n", MemPtr->ParameterListPtr->ExternalVrefCtl );
  IDS_HDT_CONSOLE (MEM_FLOW, "\tForceTrainMode : %d\n", MemPtr->ParameterListPtr->ForceTrainMode );
  IDS_HDT_CONSOLE (MEM_FLOW, "\tPmuTrainMode : %d\n", MemPtr->ParameterListPtr->PmuTrainMode );
  IDS_HDT_CONSOLE (MEM_FLOW, "\tAMP : %d\n\n", MemPtr->ParameterListPtr->AmpEnable);
  IDS_HDT_CONSOLE (MEM_FLOW, "\tCustomVddio : %d\n\n", MemPtr->ParameterListPtr->CustomVddioSupport);

  //
  // Force the DDR Voltage based upon the CustomVDDIO override by platform BIOS prior to calling AmdInitPost
  //
  MemPtr->ParameterListPtr->DDRVoltage = MemPtr->ParameterListPtr->CustomVddioSupport;
  //----------------------------------------------------------------------------
  // Get TSC rate, which will be used later in Wait10ns routine
  //----------------------------------------------------------------------------
  CcxGetPstateInfo (0, SwPstate0, (UINTN *)&MemPtr->TscRate, &VoltageInuV, &PowerInmW, &MemPtr->StdHeader);

  //----------------------------------------------------------------------------
  // Read In SPD Data
  //----------------------------------------------------------------------------
  AGESA_TESTPOINT (TpProcMemBeforeSpdProcessing, &MemPtr->StdHeader);
  MemSPDDataProcess (MemPtr);

  //----------------------------------------------------------------
  // Initialize Main Data Block
  //----------------------------------------------------------------
  mmData.MemPtr = MemPtr;
  mmData.mmSharedPtr = &mmSharedData;
  LibAmdMemFill (&mmSharedData, 0, sizeof (mmSharedData), &MemPtr->StdHeader);
  mmSharedData.DimmExcludeFlag = NORMAL;
  mmSharedData.NodeIntlv.IsValid = FALSE;
  //----------------------------------------------------------------
  // Discover populated CPUs
  //
  //----------------------------------------------------------------
  Retval = MemSocketScan (&mmData);
  if (Retval == AGESA_FATAL) {
    return Retval;
  }
  DieCount = mmData.DieCount;
  //----------------------------------------------------------------
  //
  // Allocate Memory for NB and Tech Blocks
  //
  //  NBPtr[Die]----+
  //                |
  //                V
  //  +---+---+---+---+---+---+---+---+
  //  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |   NB Blocks
  //  +---+---+---+---+---+---+---+---+
  //    |   |   |   |   |   |   |   |
  //    |   |   |   |   |   |   |   |
  //    v   v   v   v   v   v   v   v
  //  +---+---+---+---+---+---+---+---+
  //  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |   Tech Blocks
  //  +---+---+---+---+---+---+---+---+
  //
  //
  //----------------------------------------------------------------
  AllocHeapParams.RequestedBufferSize = (DieCount * (sizeof (MEM_NB_BLOCK) + sizeof (MEM_TECH_BLOCK)));
  AllocHeapParams.BufferHandle = AMD_MEM_AUTO_HANDLE;
  AllocHeapParams.Persist = HEAP_LOCAL_CACHE;
  if (AGESA_SUCCESS != HeapAllocateBuffer (&AllocHeapParams, &MemPtr->StdHeader)) {
    ASSERT(FALSE); // NB and Tech Block Heap allocate error
    return AGESA_FATAL;
  }
  NBPtr = (MEM_NB_BLOCK *)AllocHeapParams.BufferPtr;
  TechPtr = (MEM_TECH_BLOCK *) (&NBPtr[DieCount]);
  mmData.NBPtr = NBPtr;
  mmData.TechPtr = TechPtr;

  //----------------------------------------------------------------
  // Create NB Blocks
  //
  //----------------------------------------------------------------
  for (Die = 0 ; Die < DieCount ; Die++ ) {
    if (OptionMemoryInstallPtr->memNBInstalled.MemConstructNBBlock != NULL) {
      if (OptionMemoryInstallPtr->memNBInstalled.MemConstructNBBlock (&NBPtr[Die], MemPtr, &OptionMemoryInstallPtr->MemFeatBlock, &mmSharedData, Die) != TRUE) {
        ASSERT (FALSE);
        return AGESA_FATAL;
      }
    } else {
      ASSERT (FALSE);
      return AGESA_FATAL;
    }
  }
  //----------------------------------------------------------------
  // Create Technology Blocks
  //
  //----------------------------------------------------------------
  for (Die = 0 ; Die < DieCount ; Die++ ) {
    i = 0;
    TechInstalled = FALSE;
    //
    // Validate the installed Technology
    //
    TechTypePtr = (TECHNOLOGY_TYPE *) FindPSOverrideEntry (NBPtr->RefPtr->PlatformMemoryConfiguration, PSO_MEM_TECH, NBPtr[Die].MCTPtr->SocketId, 0, 0, NULL, NULL);
    if (TechTypePtr != NULL) {
      //
      // Run the list of Tech block contructors
      //
      ASSERT (OptionMemoryInstallPtr->memTechInstalled != NULL)
      while (OptionMemoryInstallPtr->memTechInstalled[i] != NULL) {
        if (OptionMemoryInstallPtr->memTechInstalled[i] (&TechPtr[Die], &NBPtr[Die])) {
          NBPtr[Die].TechPtr = &TechPtr[Die];
          TechInstalled = TRUE;
        }
        i++;
      }
    } else {
      //
      // Run only the first Constructor in the list
      //
      if (OptionMemoryInstallPtr->memTechInstalled[i] (&TechPtr[Die], &NBPtr[Die])) {
        NBPtr[Die].TechPtr = &TechPtr[Die];
        TechInstalled = TRUE;
      }
    }
    //
    // Couldn't find a Tech block which supported this family
    //
    if (TechInstalled == FALSE) {
      return AGESA_FATAL;
    }
  }

  //----------------------------------------------------------------
  // AMP initialization
  //
  //----------------------------------------------------------------
  for (Die = 0 ; Die < DieCount ; Die++ ) {
    NBPtr[Die].FeatPtr->InitAMP (&NBPtr[Die]);
  }

  //----------------------------------------------------------------
  //
  //                 MEMORY INITIALIZATION TASKS
  //
  ASSERT (OptionMemoryInstallPtr->memFlowControlInstalled != NULL)
  mmSharedData.TimesPmuRetrain = DEFAULT_PMU_RETRAIN_TIMES;
  IDS_OPTION_HOOK (IDS_MEM_PMU_RETRAIN_TIMES, &mmSharedData.TimesPmuRetrain, &(mmData.MemPtr->StdHeader));
  IDS_HDT_CONSOLE (MEM_FLOW, "\t\tPMU to be retrained %d times.\n", mmSharedData.TimesPmuRetrain);
  do {
    i = 0;
    mmSharedData.LastPmuTrainFail = FALSE;
    mmSharedData.TimesPmuRetrain --;
    Retval = OptionMemoryInstallPtr->memFlowControlInstalled (&mmData);
  } while (mmSharedData.TimesPmuRetrain != 0 && mmSharedData.LastPmuTrainFail == TRUE);
  ASSERT (Retval != AGESA_FATAL);

  //----------------------------------------------------------------
  // Deallocate NB register tables
  //----------------------------------------------------------------
  for (Tab = 0; Tab < NumberOfNbRegTables; Tab++) {
    HeapDeallocateBuffer (GENERATE_MEM_HANDLE (ALLOC_NB_REG_TABLE, Tab, 0, 0), &MemPtr->StdHeader);
  }

  //----------------------------------------------------------------
  // Check for errors and return
  //----------------------------------------------------------------
  AGESA_TESTPOINT (TpProcMemEnd, &MemPtr->StdHeader);
  IDS_PERF_TIMESTAMP (TP_ENDPROCAMDMEMAUTO, &MemPtr->StdHeader);
  for (Die = 0; Die < DieCount; Die++) {
    if (NBPtr[Die].MCTPtr->ErrCode > Retval) {
      Retval = NBPtr[Die].MCTPtr->ErrCode;
    }
  }
  return Retval;

  // Report error
  //  Status = (*PeiServices)->LocatePpi (PeiServices,
  //                                    &gAmdCommonErrorLogPpiGuid,
  //                                    0,
  //                                    NULL,
  //                                    (VOID **)&AmdCommonErrorLogPpiPtr);
  //  if (EFI_SUCCESS != Status) {
  //      AmdCommonErrorLogPpiPtr->MemPutEventLog (AGESA_FATAL, MEM_ERROR_HEAP_ALLOCATE_FOR_SPD, 0, 0, 0, 0, &MemPtr->StdHeader);
  //    }
  //  // Consume a CCx Service
  //    // Consume a PSP Service (APOB)
  //    // Consume a Fabric Service
  //    // Consume a GNB Service
  //    // Consume a FCH Service
  //    // Publish PPIs from memory
  //    // Consume a SOC service (package and soc ID)

  //      // Regsiter a notify callback
  //      // Add depex to driver on SOC ID

  //    // Wait function
  //    // IDS/CBS option

  //      // Save S3 data
  //      // How to deal with return data and output
  //return Status;

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *  This function fills a default SPD buffer with SPD values for all DIMMs installed in the system
 *
 *    The SPD Buffer is populated with a Socket-Channel-Dimm centric view of the Dimms.  At this
 *  point, the Memory controller type is not known, and the platform BIOS does not know the anything
 *  about which DIMM is on which DCT.  So the DCT relationship is abstracted from the arrangement
 *  of SPD information here.  We use the utility functions GetSpdSocketIndex(), GetMaxChannelsPerSocket(),
 *  and GetMaxDimmsPerChannel() to Map the SPD data according to which Socket-relative channel the DIMMs
 *  are connected to.  The functions rely on either the maximum values in the
 *  PlatformSpecificOverridingTable or if unspecified, the absolute maximums in AGESA.H.
 *
 *  This mapping is translated in the Northbridge object Constructor and the Technology block constructor.
 *
 *     @param[in,out]   *MemPtr   - Pointer to the MEM_DATA_STRUCT
 *
 */

VOID
STATIC
MemSPDDataProcess (
  IN OUT   MEM_DATA_STRUCT *MemPtr
  )
{
  UINT8 Socket;
  UINT8 Channel;
  UINT8 Dimm;
  UINT8 DimmIndex;
  UINT32 AgesaStatus;
  UINT8 MaxSockets;
  UINT8 MaxChannelsPerSocket;
  UINT8 MaxDimmsPerChannel;
  SPD_DEF_STRUCT *DimmSPDPtr;
  PSO_TABLE *PsoTable;
  ALLOCATE_HEAP_PARAMS AllocHeapParams;
  AGESA_READ_SPD_PARAMS SpdParam;

  ASSERT (MemPtr != NULL);

  MaxSockets = (UINT8) (0x000000FF & GetPlatformNumberOfSockets ());
  PsoTable = MemPtr->ParameterListPtr->PlatformMemoryConfiguration;
  //
  // Allocate heap for the table
  //
  AllocHeapParams.RequestedBufferSize = (GetSpdSocketIndex (PsoTable, MaxSockets, &MemPtr->StdHeader) * sizeof (SPD_DEF_STRUCT));
  AllocHeapParams.BufferHandle = AMD_MEM_SPD_HANDLE;
  AllocHeapParams.Persist = HEAP_LOCAL_CACHE;
  if (HeapAllocateBuffer (&AllocHeapParams, &MemPtr->StdHeader) == AGESA_SUCCESS) {
    MemPtr->SpdDataStructure = (SPD_DEF_STRUCT *) AllocHeapParams.BufferPtr;
    //
    // Initialize SpdParam Structure
    //
    LibAmdMemCopy ((VOID *)&SpdParam, (VOID *)MemPtr, (UINTN)sizeof (SpdParam.StdHeader), &MemPtr->StdHeader);
    //
    // Populate SPDDataBuffer
    //
    SpdParam.MemData = MemPtr;
    DimmIndex = 0;
    for (Socket = 0; Socket < (UINT16)MaxSockets; Socket++) {
      MaxChannelsPerSocket = GetMaxChannelsPerSocket (PsoTable, Socket, &MemPtr->StdHeader);
      SpdParam.SocketId = Socket;
      for (Channel = 0; Channel < MaxChannelsPerSocket; Channel++) {
        SpdParam.MemChannelId = Channel;
        MaxDimmsPerChannel = GetMaxDimmsPerChannel (PsoTable, Socket, Channel);
        for (Dimm = 0; Dimm < MaxDimmsPerChannel; Dimm++) {
          SpdParam.DimmId = Dimm;
          DimmSPDPtr = &(MemPtr->SpdDataStructure[DimmIndex++]);
          SpdParam.Buffer = DimmSPDPtr->Data;
          AGESA_TESTPOINT (TpProcMemBeforeAgesaReadSpd, &MemPtr->StdHeader);
          AgesaStatus = AgesaReadSpd (0, &SpdParam);
          AGESA_TESTPOINT (TpProcMemAfterAgesaReadSpd, &MemPtr->StdHeader);
          if (AgesaStatus == AGESA_SUCCESS) {
            DimmSPDPtr->DimmPresent = TRUE;
            IDS_HDT_CONSOLE (MEM_FLOW, "SPD Socket %d Channel %d Dimm %d: %08x\n", Socket, Channel, Dimm, SpdParam.Buffer);
          } else {
            DimmSPDPtr->DimmPresent = FALSE;
          }
        }
      }
    }
  } else {
    PutEventLog (AGESA_FATAL, MEM_ERROR_HEAP_ALLOCATE_FOR_SPD, 0, 0, 0, 0, &MemPtr->StdHeader);
    //
    // Assert here if unable to allocate heap for SPDs
    //
    IDS_ERROR_TRAP;
  }
}

