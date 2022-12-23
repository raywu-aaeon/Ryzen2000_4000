/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD Ccx Microcode Patch Library
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Lib
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-10 02:28:05 +0800 (Wed, 10 Dec 2014) $
 *
 */
/*
 ******************************************************************************
 *
 * Copyright (C) 2008-2022 Advanced Micro Devices, Inc. All rights reserved.
 *
 *******************************************************************************
 */


/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include <Library/BaseLib.h>
#include <Filecode.h>
#include <Library/AmdBaseLib.h>
#include <Library/CcxRolesLib.h>
#include <Library/CcxMicrocodePatchLib.h>
#include <Library/AmdPspBaseLibV2.h>
#include <Library/PciLib.h>
#include <Library/BaseCoreLogicalIdLib.h>
#include <Library/MemoryAllocationLib.h>

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
#define FILECODE LIBRARY_CCXMICROCODEPATCHLIB_CCXMICROCODEPATCHLIB_FILECODE

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */



BOOLEAN
STATIC
GetProcessorId (
  IN OUT   UINT16             *ProcessorId,
  IN OUT   AMD_CONFIG_PARAMS  *StdHeader
  );

BOOLEAN
STATIC
ValidateMicrocode (
  IN       MICROCODE_PATCH    *MicrocodePatchPtr,
  IN       UINT16             ProcessorId,
  IN OUT   AMD_CONFIG_PARAMS  *StdHeader
  );

BOOLEAN
STATIC
LoadMicrocode (
  IN       MICROCODE_PATCH    *MicrocodePatchPtr,
  IN OUT   AMD_CONFIG_PARAMS  *StdHeader
  );

VOID
STATIC
GetMicrocodeVersion (
     OUT   UINT32             *pMicrocodeVersion,
  IN OUT   AMD_CONFIG_PARAMS  *StdHeader
  );

/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */
/* -----------------------------------------------------------------------------*/
/**
 *  Update microcode patch in current processor.
 *
 *  Then reads the patch id, and compare it to the expected, in the Microprocessor
 *  patch block.
 *
 *  @param[in,out] UcodePatchAddr        - The selected UcodePatch address, return 0 if not found
 *  @param[in] StdHeader                 - Config handle for library and services.
 *
 *  @retval    TRUE   - Patch Loaded Successfully.
 *  @retval    FALSE  - Patch Did Not Get Loaded.
 *
 */
BOOLEAN
LoadMicrocodePatch (
  IN OUT   UINT64            *UcodePatchAddr,
  IN OUT   AMD_CONFIG_PARAMS *StdHeader
  )
{
  UINT8            InstanceNumber;
  UINT16           ProcessorId;
  TYPE_ATTRIB      TypeAttrib;
  UINT64           EntryAddress;
  UINT32           EntrySize;
  UINT64           EntryDest;
  BOOLEAN          Status;
  MICROCODE_PATCH  *MicroCode;
  UINTN            MicroCodePageCount;

  Status = FALSE;
  *UcodePatchAddr = 0;
  if (CcxIsBsp (StdHeader)) {
    IDS_HDT_CONSOLE (CPU_TRACE, "  Start to load microcode patch\n");
  }

  AsmWriteMsr64 (0xC001100C, 0);
  // Get the processor ID
  if (GetProcessorId (&ProcessorId, StdHeader)) {
    // parse the patch table to see if we have one for the current cpu
    InstanceNumber = 0;
    while (BIOSEntryInfo (UCODE_PATCH, InstanceNumber, &TypeAttrib, &EntryAddress, &EntrySize, &EntryDest)) {
      MicroCodePageCount = EFI_SIZE_TO_PAGES (EntrySize);
      MicroCode = (MICROCODE_PATCH *)AllocateRuntimePages (MicroCodePageCount);
      MapSpiDataToBuffer ((UINT32)(UINTN)EntryAddress, MicroCode, EntrySize);
      if (ValidateMicrocode (MicroCode, ProcessorId, StdHeader)) {
        // Workaround PLAT-11398, reload ucode patch during S3 resume, this should apply to all SOC-15 cores
        // Save address of ucode to scratch register
        ASSERT ((((UINT64)(UINTN)MicroCode) & 0xFFFFFFFF00000000) == 0);
        AsmWriteMsr64 (0xC001100C, (UINT64)(UINTN)MicroCode);
        *UcodePatchAddr = (UINT64)(UINTN)MicroCode;
        if (LoadMicrocode (MicroCode, StdHeader)) {
          Status = TRUE;
        }
        break; // Once we find a microcode patch that matches the processor, exit the while loop
      } else {
        FreePages (MicroCode, MicroCodePageCount);
      }
      InstanceNumber++;
    }
  }

  return Status;
}

/*---------------------------------------------------------------------------------------
 *                           L O C A L    F U N C T I O N S
 *---------------------------------------------------------------------------------------
 */

/* -----------------------------------------------------------------------------*/
/**
 *
 *  LoadMicrocode
 *
 *    Update microcode patch in current processor, then reads the
 *    patch id, and compare it to the expected, in the Microprocessor
 *    patch block.
 *
 *    @param[in]       MicrocodePatchPtr  - Pointer to Microcode Patch.
 *    @param[in,out]   StdHeader          - Pointer to AMD_CONFIG_PARAMS struct.
 *
 *    @retval          TRUE  - Patch Loaded Successfully.
 *    @retval          FALSE - Patch Did Not Get Loaded.
 *
 */
BOOLEAN
STATIC
LoadMicrocode (
  IN       MICROCODE_PATCH    *MicrocodePatchPtr,
  IN OUT   AMD_CONFIG_PARAMS  *StdHeader
  )
{
  UINT32       MicrocodeVersion;
  PATCH_LOADER PatchLoaderMsr;

  // Load microcode patch into CPU
  PatchLoaderMsr.RawData = (UINT64) (UINTN) MicrocodePatchPtr;
  PatchLoaderMsr.BitFields.SBZ = 0;
  AsmWriteMsr64 (MSR_PATCH_LOADER, PatchLoaderMsr.RawData);

  // Do ucode patch Authentication
  // Read microcode version back from CPU, determine if
  // it is the same patch level as contained in the source
  // microprocessor patch block passed in
  GetMicrocodeVersion (&MicrocodeVersion, StdHeader);
  if (MicrocodeVersion == MicrocodePatchPtr->PatchID) {
    if (CcxIsBsp (StdHeader)) {
      IDS_HDT_CONSOLE (CPU_TRACE, "  Microcode Patch %X is loaded\n", MicrocodeVersion);
    }
    return (TRUE);
  } else {
    return (FALSE);
  }
}


/* -----------------------------------------------------------------------------*/
/**
 *
 *  GetProcessorId
 *
 *    Return the processor ID
 *
 *    @param[in,out]   ProcessorId               - Processor ID.
 *    @param[in,out]   StdHeader                 - Pointer to AMD_CONFIG_PARAMS struct.
 *
 *    @retval          TRUE  - Processor Id found.
 *
 */
BOOLEAN
STATIC
GetProcessorId (
  IN OUT   UINT16             *ProcessorId,
  IN OUT   AMD_CONFIG_PARAMS  *StdHeader
  )
{
  CPUID_DATA   CpuIdData;

  // Read CPUID for family information
  AsmCpuid (AMD_CPUID_FMF,
      &(CpuIdData.EAX_Reg),
      &(CpuIdData.EBX_Reg),
      &(CpuIdData.ECX_Reg),
      &(CpuIdData.EDX_Reg)
      );
  // High byte contains extended model and extended family
  *ProcessorId  = (UINT16) ((CpuIdData.EAX_Reg & (CPUID_EXT_MODEL_MASK | CPUID_EXT_FAMILY_MASK)) >> 8);
  // Low byte contains model and family
  *ProcessorId |= (CpuIdData.EAX_Reg & (CPUID_STEPPING_MASK | CPUID_BASE_MODEL_MASK));

  return TRUE;
}

/*---------------------------------------------------------------------------------------*/
/**
 *
 *  ValidateMicrocode
 *
 *    Determine if the microcode patch block, currently pointed to
 *    is valid, and is appropriate for the current processor

 *    @param[in]       MicrocodePatchPtr      - Pointer to Microcode Patch.
 *    @param[in]       ProcessorId            - Processor ID.
 *    @param[in,out]   StdHeader              - Pointer to AMD_CONFIG_PARAMS struct.
 *
 *    @retval          TRUE  - Patch Found.
 *    @retval          FALSE - Patch Not Found.
 *
 */
BOOLEAN
STATIC
ValidateMicrocode (
  IN       MICROCODE_PATCH    *MicrocodePatchPtr,
  IN       UINT16             ProcessorId,
  IN OUT   AMD_CONFIG_PARAMS  *StdHeader
  )
{
  BOOLEAN   Chipset1Matched;
  BOOLEAN   Chipset2Matched;
  PCI_ADDR  PciAddress;
  UINT32    PciDeviceVidDid;
  UINT8     PciDeviceRevision;
  UINT8     DevCount;
  UINT8     FunCount;
  UINT32    Chipset1DeviceID;
  UINT32    Chipset2DeviceID;
  UINT8     MulitFunction;

  Chipset1Matched = FALSE;
  Chipset2Matched = FALSE;
  PciDeviceVidDid = 0;
  PciDeviceRevision = 0;
  Chipset1DeviceID = MicrocodePatchPtr->Chipset1DeviceID;
  Chipset2DeviceID = MicrocodePatchPtr->Chipset2DeviceID;
  MulitFunction = 0;

  //
  // parse the supplied microcode to see if it is compatible with the processor
  //
  if (MicrocodePatchPtr->ProcessorRevisionID !=  ProcessorId) {
    return (FALSE);
  }

  if (Chipset1DeviceID == 0) {
    Chipset1Matched = TRUE;
  }
  if (Chipset2DeviceID == 0) {
    Chipset2Matched = TRUE;
  }

  if ((!Chipset1Matched) || (!Chipset2Matched)) {
    //
    // Scan all PCI devices in Bus 0, try to find out matched case.
    //
    for (DevCount = 0; DevCount < 32; DevCount++) {
      for (FunCount = 0; FunCount < 8; FunCount++) {
        PciAddress.AddressValue = MAKE_SBDFO (0, 0, DevCount, FunCount, 0);
        PciDeviceVidDid = PciRead32 (PciAddress.AddressValue);
        if (PciDeviceVidDid == 0xFFFFFFFF) {
          if (FunCount == 0) {
            break;
          } else {
            continue;
          }
        }
        PciAddress.Address.Register = 0x8;
        PciDeviceRevision = PciRead8 (PciAddress.AddressValue);
        if ((!Chipset1Matched) && (PciDeviceVidDid == Chipset1DeviceID)) {
          if (PciDeviceRevision == MicrocodePatchPtr->Chipset1RevisionID) {
            Chipset1Matched = TRUE;
          }
        }
        if ((!Chipset2Matched) && (PciDeviceVidDid == Chipset2DeviceID)) {
          if (PciDeviceRevision == MicrocodePatchPtr->Chipset2RevisionID) {
            Chipset2Matched = TRUE;
          }
        }
        if (Chipset1Matched && Chipset2Matched) {
          break;
        }
        //
        // Check multi-function. If it doesen't exist, we don't have to loop functions to 7.
        //
        if (FunCount == 0) {
          MulitFunction = 0;
          PciAddress.Address.Register = 0xE;
          MulitFunction = PciRead8 (PciAddress.AddressValue);
          if ((MulitFunction & 0x80) == 0) {
            break;
          }
        }
      } // end FunCount for loop.

      if (Chipset1Matched && Chipset2Matched) {
        break;
      }
    }  // end DevCount for loop.
  }

  return (Chipset1Matched && Chipset2Matched);
}


/*---------------------------------------------------------------------------------------*/
/**
 *
 *  GetMicrocodeVersion
 *
 *    Return the version of the currently loaded microcode patch, if any.
 *    Read from the patch level MSR, return the value in eax. If no patch
 *    has been loaded, 0 will be returned.
 *
 *    @param[out]      pMicrocodeVersion  - Pointer to Microcode Version.
 *    @param[in,out]   StdHeader          - Pointer to AMD_CONFIG_PARAMS struct.
 *
 */
VOID
STATIC
GetMicrocodeVersion (
     OUT   UINT32             *pMicrocodeVersion,
  IN OUT   AMD_CONFIG_PARAMS  *StdHeader
  )
{
  UINT64  MsrData;

  MsrData = 0;
  MsrData = AsmReadMsr64 (MSR_PATCH_LEVEL);

  *pMicrocodeVersion = (UINT32) MsrData;
}


