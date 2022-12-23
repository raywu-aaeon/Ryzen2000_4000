/* $NoKeywords:$ */
/**
 * @file
 *
 * AmdSmuServicesV10Ppi Implementation
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  AmdNbioSmuV10Pei
 * @e \$Revision: 312065 $   @e \$Date: 2015-01-30 04:23:05 -0600 (Fri, 30 Jan 2015) $
 *
 */
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
 */
#include <AMD.h>

#include <PiPei.h>
#include <Filecode.h>
#include <GnbRegistersRV.h>
#include <GnbDxio.h>
#include <Library/PeiServicesLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Library/PcdLib.h>
#include <Library/HobLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/NbioHandleLib.h>
#include <Library/NbioRegisterAccLib.h>
#include <Library/PcieConfigLib.h>
#include <Library/NbioSmuV10Lib.h>
#include <Ppi/NbioSmuServicesPpi.h>
#include <Ppi/NbioPcieServicesPpi.h>
#include <Guid/GnbPcieInfoHob.h>
//#include <Guid/GnbNbioBaseZPInfoHob.h>
#include <AmdNbioSmuV10Pei.h>

#define FILECODE        NBIO_SMU_AMDNBIOSMUV10PEI_AMDSMUSERVICESV10PPI_FILECODE

/*----------------------------------------------------------------------------------------
 *                         E X T E R N   D E F I N I T I O N S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U  R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U  N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
/**
  Reads a fuse value based on an enumerated list of fuse "names"

  Parameters:
  InstanceId
    The unique identifier of the NBIO instance associated with this socket/die
  MyHandle
    Pointer to GNB_HANDLE* to return GNB_HANDLE of this InstanceId
  FuseValue
    Pointer to the value of the fuse

  Status Codes Returned:
  EFI_SUCCESS           - The fuse was located and the FuseValue returned is valid
  EFI_INVALID_PARAMETER - InstanceId did not reference a valid NBIO instance
**/
EFI_STATUS
SmuGetGnbHandle (
  IN       UINT32                         InstanceId,
     OUT   GNB_HANDLE                     **MyHandle
  )
{
  EFI_PEI_HOB_POINTERS            Hob;
  GNB_PCIE_INFORMATION_DATA_HOB   *PciePlatformConfigHob;
  PCIe_PLATFORM_CONFIG            *Pcie;
  EFI_STATUS                      Status;
  GNB_HANDLE                      *GnbHandle;
  BOOLEAN                         InstanceFound;
  GNB_PCIE_INFORMATION_DATA_HOB   *GnbPcieInfoDataHob;

  GnbHandle = NULL;
  // Need topology structure
  GnbPcieInfoDataHob = NULL;
  PciePlatformConfigHob = NULL;

  Status = PeiServicesGetHobList (&Hob.Raw);

  while (!END_OF_HOB_LIST (Hob)) {
    if (Hob.Header->HobType == EFI_HOB_TYPE_GUID_EXTENSION &&
        CompareGuid ( &Hob.Guid->Name, &gGnbPcieHobInfoGuid)) {
        PciePlatformConfigHob = (GNB_PCIE_INFORMATION_DATA_HOB *)Hob.Raw;
      Status = EFI_SUCCESS;
      break;
    }
    Hob.Raw = GET_NEXT_HOB (Hob);
  }
  Pcie = &(PciePlatformConfigHob->PciePlatformConfigHob);
  GnbHandle = NbioGetHandle (Pcie);

  InstanceFound = FALSE;
  Status = EFI_INVALID_PARAMETER;
  while ((InstanceFound == FALSE) && (GnbHandle != NULL)) {
    if (GnbHandle->InstanceId == InstanceId) {
      InstanceFound = TRUE;
      Status = EFI_SUCCESS;
      IDS_HDT_CONSOLE (MAIN_FLOW, "InstanceId found!!\n");
    } else {
      GnbHandle = GnbGetNextHandle (GnbHandle);
    }
  }
  *MyHandle = GnbHandle;
  return Status;
}

/*----------------------------------------------------------------------------------------
/**
  Reads a fuse value based on an enumerated list of fuse "names"

  Parameters:
  This
    A pointer to the PEI_AMD_NBIO_SMU_SERVICES_PPI instance.
  InstanceId
    The unique identifier of the NBIO instance associated with this socket/die
  FuseName
    The "name" of the fuse from an enumerated list of fuses supported by this function. This translates
    to an number value used in a LUT at compile time
  BufferSize
    Pointer to value indicating the size of the buffer in bytes passed in. On return this value will
    be the actual size of the retrieved fuse.
  FuseValue
    Pointer to memory that will contain the value of the retrieved fuse. This memory should
    be managed by the caller.

  Status Codes Returned:
  EFI_SUCCESS           - The fuse was located and the FuseValue returned is valid
  EFI_INVALID_PARAMETER - One of the input parameters was invalid
                        - InstanceId did not reference a valid NBIO instance
                        - FuseName was not found in the list of supported fuse identifier values
  EFI_UNSUPPORTED       - This function is not supported by this version of the driver
**/
EFI_STATUS
SmuReadFuseByName (
  IN       PEI_AMD_NBIO_SMU_SERVICES_PPI  *This,
  IN       UINT32                         InstanceId,
  IN       UINTN                          FuseName,
  IN OUT   UINTN                          *BufferSize,
     OUT   UINT8                          *FuseValue
  )
{
  return EFI_UNSUPPORTED;
}

/*----------------------------------------------------------------------------------------
/**
  Reads a fuse value based on chain, start bit, and size

  Parameters:
  This
    A pointer to the PEI_AMD_NBIO_SMU_SERVICES_PPI instance.
  InstanceId
    The unique identifier of the NBIO instance associated with this socket/die
  FuseChain
    The chain number of the fuse to read
  FuseStartBit
    The starting bit within the specified fuse chain of the fuse to read
  FuseSize
    The bitfield width of the fuse to read
  FuseValue
    Pointer to the value of the fuse

  Status Codes Returned:
  EFI_SUCCESS           - The fuse was located and the FuseValue returned is valid
  EFI_INVALID_PARAMETER - One of the input parameters was invalid
                        - InstanceId did not reference a valid NBIO instance
                        - FuseChain was not a valid fuse chain value
                        - FuseStartBit was not valid within the specified fuse chain
                        - FuseSize exceeded the size available in the return field
  EFI_UNSUPPORTED       - This function is not supported by this version of the driver
**/
EFI_STATUS
SmuReadFuseByLocation (
  IN       PEI_AMD_NBIO_SMU_SERVICES_PPI  *This,
  IN       UINT32                         InstanceId,
  IN       UINT32                         FuseChain,
  IN       UINT32                         FuseStartBit,
  IN       UINT32                         FuseSize,
     OUT   UINT32                         *FuseValue
)
{
  return EFI_UNSUPPORTED;
}

/*----------------------------------------------------------------------------------------
/**
  Executes a specific SMU service and returns the results (Generally intended for NBIO internal requests)

  Parameters:
  This
    A pointer to the PEI_AMD_NBIO_SMU_SERVICES_PPI instance.
  InstanceId
    The unique identifier of the NBIO instance associated with this socket/die
  ServiceRequest
    The service request identifier
  InputParameters
    Pointer to an array of service request arguments (for CZ, UINT32[6]).  Input parameters are not validated by the driver prior to issuing the service request.
  ReturnValues
    Pointer to an array of service request response values (for CZ, UINT32[6])

  Status Codes Returned:
  EFI_SUCCESS           - The SMU service request was completed and the argument registers are returned in "ReturnValues"
  EFI_INVALID_PARAMETER - One of the input parameters was invalid
                        - InstanceId did not reference a valid NBIO instance
                        - ServiceRequest was not supported by this version of SMU
  EFI_UNSUPPORTED       - This function is not supported by this version of the driver
**/
EFI_STATUS
SmuServiceRequest (
  IN       PEI_AMD_NBIO_SMU_SERVICES_PPI  *This,
  IN       UINT32                         InstanceId,
  IN       UINT32                         ServiceRequest,
  IN       UINT32                         *InputParameters,
     OUT   UINT32                         *ReturnValues
  )
{
  GNB_HANDLE                      *GnbHandle;
  EFI_STATUS                      Status;
  UINT32                          SmuArg[6];
  UINT32                          SmuResult;

  IDS_HDT_CONSOLE (MAIN_FLOW, "SmuServiceRequest Entry\n");
  Status = SmuGetGnbHandle (InstanceId, &GnbHandle);
  if (Status == EFI_SUCCESS) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "GnbHandle Found\n");
    LibAmdMemCopy (SmuArg, InputParameters, 24, (AMD_CONFIG_PARAMS *) NULL);
    SmuResult = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (GnbHandle), ServiceRequest, SmuArg, 0);
    if (SmuResult == 1) {
      LibAmdMemCopy (ReturnValues, SmuArg, 24, (AMD_CONFIG_PARAMS *) NULL);
    } else {
      Status = EFI_INVALID_PARAMETER;
      IDS_HDT_CONSOLE (MAIN_FLOW, "InstanceId not found!!\n");
      ASSERT (FALSE);       // Unsupported SMU service request
    }
  }
  IDS_HDT_CONSOLE (MAIN_FLOW, "SmuServiceRequest Exit Status = %d\n", Status);
  return Status;
}

/*----------------------------------------------------------------------------------------
/**
  Executes a specific DXIO service and returns the results (Generally intended for NBIO internal requests)

  Parameters:
  This
    A pointer to the PEI_AMD_NBIO_SMU_SERVICES_PPI instance.
  InstanceId
    The unique identifier of the NBIO instance associated with this socket/die
  ServiceRequest
    The service request identifier
  InputParameters
    Pointer to an array of service request arguments (for CZ, UINT32[6]).  Input parameters are not validated by the driver prior to issuing the service request.
  ReturnValues
    Pointer to an array of service request response values (for CZ, UINT32[6])

  Status Codes Returned:
  EFI_SUCCESS           - The SMU service request was completed and the argument registers are returned in "ReturnValues"
  EFI_INVALID_PARAMETER - One of the input parameters was invalid
                        - InstanceId did not reference a valid NBIO instance
                        - ServiceRequest was not supported by this version of SMU
  EFI_UNSUPPORTED       - This function is not supported by this version of the driver
**/
EFI_STATUS
SmuDxioServiceRequest (
  IN       PEI_AMD_NBIO_SMU_SERVICES_PPI  *This,
  IN       UINT32                         InstanceId,
  IN       UINT32                         ServiceRequest,
  IN       UINT32                         *InputParameters,
     OUT   UINT32                         *ReturnValues
  )
{
  GNB_HANDLE                      *GnbHandle;
  EFI_STATUS                      Status;
  UINT32                          SmuArg[6];
  UINT32                          SmuResult;

  IDS_HDT_CONSOLE (MAIN_FLOW, "SmuDxioServiceRequest Entry\n");
  Status = SmuGetGnbHandle (InstanceId, &GnbHandle);
  if (Status == EFI_SUCCESS) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "GnbHandle Found\n");
    LibAmdMemCopy (SmuArg, InputParameters, 24, (AMD_CONFIG_PARAMS *) NULL);

    SmuResult = NbioDxioServiceRequestV10 (GnbHandle, ServiceRequest, SmuArg, 0);
    if (SmuResult == 1) {
      LibAmdMemCopy (ReturnValues, SmuArg, 24, (AMD_CONFIG_PARAMS *) NULL);
    } else {
      Status = EFI_INVALID_PARAMETER;
      IDS_HDT_CONSOLE (MAIN_FLOW, "InstanceId not found!!\n");
      ASSERT (FALSE);       // Unsupported SMU service request
    }
  }
    IDS_HDT_CONSOLE (MAIN_FLOW, "SmuDxioServiceRequest Exit Status = %d\n", Status);
  return Status;
}

/*----------------------------------------------------------------------------------------
/**
  Reads a 32-bit register from SMU register space (Generally intended for NBIO internal requests)

  Parameters:
  This
    A pointer to the PEI_AMD_NBIO_SMU_SERVICES_PPI instance.
  InstanceId
    The unique identifier of the NBIO instance associated with this socket/die
  RegisterIndex
    The index of the register to be read
  RegisterValue
    Pointer to a UINT32 to store the value read from the register

  Status Codes Returned:
  EFI_SUCCESS           - The register value is returned in RegisterValue
  EFI_INVALID_PARAMETER - One of the input parameters was invalid
                        - InstanceId did not reference a valid NBIO instance
  EFI_UNSUPPORTED       - This function is not supported by this version of the driver
**/
EFI_STATUS
SmuRegisterRead (
  IN       PEI_AMD_NBIO_SMU_SERVICES_PPI  *This,
  IN       UINT32                         InstanceId,
  IN       UINT32                         RegisterIndex,
     OUT   UINT32                         *RegisterValue
  )
{
  GNB_HANDLE                      *GnbHandle;
  EFI_STATUS                      Status;

  Status = SmuGetGnbHandle (InstanceId, &GnbHandle);
  if (Status == EFI_SUCCESS) {
    Status = NbioRegisterRead (GnbHandle, TYPE_SMN, RegisterIndex, RegisterValue, 0);
  }
  return Status;
}

/*----------------------------------------------------------------------------------------
/**
  Writes a 32-bit register in SMU register space (Generally intended for NBIO internal requests)

  Parameters:
  This
    A pointer to the PEI_AMD_NBIO_SMU_SERVICES_PPI instance.
  InstanceId
    The unique identifier of the NBIO instance associated with this socket/die
  RegisterIndex
    The index of the register to be read
  RegisterValue
    Pointer to a UINT32 holding the value to write to the register

  Status Codes Returned:
  EFI_SUCCESS           - The specified register has been updated with the requested value
  EFI_INVALID_PARAMETER - One of the input parameters was invalid
                        - InstanceId did not reference a valid NBIO instance
  EFI_UNSUPPORTED       - This function is not supported by this version of the driver
**/
EFI_STATUS
SmuRegisterWrite (
  IN       PEI_AMD_NBIO_SMU_SERVICES_PPI  *This,
  IN       UINT32                         InstanceId,
  IN       UINT32                         RegisterIndex,
  IN       UINT32                         *RegisterValue
  )
{
  GNB_HANDLE                      *GnbHandle;
  EFI_STATUS                      Status;

  Status = SmuGetGnbHandle (InstanceId, &GnbHandle);
  if (Status == EFI_SUCCESS) {
    Status = NbioRegisterWrite (GnbHandle, TYPE_SMN, RegisterIndex, RegisterValue, 0);
  }
  return Status;
}

/**
  Read/Modify/Write a 32-bit register from SMU register space (Generally intended for NBIO internal requests)

  Parameters:
  This
    A pointer to the PEI_AMD_NBIO_SMU_SERVICES_PPI instance.
  InstanceId
    The unique identifier of the NBIO instance associated with this socket/die
  RegisterIndex
    The index of the register to be read
  RegisterANDValue
    UINT32 holding the value to be "ANDed" with the data read from the register (i.e. mask of data that will not be modified)
  RegisterORValue
    UINT32 holding the value to be "ORed" with the data read from the register (i.e. data bits to be "set" by this function)

  Status Codes Returned:
  EFI_SUCCESS           - The specified register has been updated with the requested value
  EFI_INVALID_PARAMETER - One of the input parameters was invalid
                        - InstanceId did not reference a valid NBIO instance
  EFI_UNSUPPORTED       - This function is not supported by this version of the driver
**/
EFI_STATUS
SmuRegisterRMW (
  IN       PEI_AMD_NBIO_SMU_SERVICES_PPI  *This,
  IN       UINT32                         InstanceId,
  IN       UINT32                         RegisterIndex,
  IN       UINT32                         RegisterANDValue,
  IN       UINT32                         RegisterORValue
  )
{
  GNB_HANDLE                      *GnbHandle;
  EFI_STATUS                      Status;
  UINT32                          RegisterValue;

  Status = SmuGetGnbHandle (InstanceId, &GnbHandle);
  if (Status == EFI_SUCCESS) {
    Status = NbioRegisterRead (GnbHandle, TYPE_SMN, RegisterIndex, &RegisterValue, 0);
    RegisterValue = (RegisterValue & RegisterANDValue) | RegisterORValue;
    Status = NbioRegisterWrite (GnbHandle, TYPE_SMN, RegisterIndex, &RegisterValue, 0);
  }
  return Status;
}

/*----------------------------------------------------------------------------------------
/**
  Enable/Disable HTC

  Parameters:
  This
    A pointer to the PEI_AMD_NBIO_SMU_SERVICES_PPI instance.
  InstanceId
    The unique identifier of the NBIO instance associated with this socket/die
  HtcStatus
    Pointer to a BOOLEAN that returns the state of HTC.  If HtcReg.HtcTmpLmt != 0 then HTC will be enabled and return TRUE.
      TRUE   - HTC is enabled
      FALSE  - HTC is disabled

  Status Codes Returned:
  EFI_SUCCESS           - HTC register has been updated based on the value of HtcTmpLmt (i.e enable/disable)
  EFI_INVALID_PARAMETER - One of the input parameters was invalid
                        - InstanceId did not reference a valid NBIO instance
  EFI_UNSUPPORTED       - This function is not supported by this version of the driver
**/
EFI_STATUS
SmuHtcControl (
  IN       PEI_AMD_NBIO_SMU_SERVICES_PPI  *This,
  IN       UINT32                         InstanceId,
     OUT   BOOLEAN                        *HtcStatus
  )
{
  return EFI_UNSUPPORTED;
}

/*----------------------------------------------------------------------------------------
/**
  Returns the CAC weights read from SMU

  Parameters:
  This
    A pointer to the PEI_AMD_NBIO_SMU_SERVICES_PPI instance.
  InstanceId
    The unique identifier of the NBIO instance associated with this socket/die
  MaxNumWeights
    The number of values to read from the SMU (defines the maximum size of ApmWeights return data buffer)
  ApmWeights
    Pointer to return data buffer
  NumWeightsRead
    The number of values read from SMU
  EnergyCountNormalize
    Pointer to return value for energy count normalize

  Status Codes Returned:
  EFI_SUCCESS           - ApmWeights contains the CaC weights read from SMU
                        - ApmWeights contains the number of values available from SMU
                        - EnergyCountNormalize contains the value returned by SMU
  EFI_INVALID_PARAMETER - One of the input parameters was invalid
                        - InstanceId did not reference a valid NBIO instance
  EFI_BUFFER_TOO_SMALL  - The number of weights available exceeds MaxNumWeights
  EFI_UNSUPPORTED       - This function is not supported by this version of the driver
**/
EFI_STATUS
SmuReadCacWeights (
  IN       PEI_AMD_NBIO_SMU_SERVICES_PPI  *This,
  IN       UINT32                         InstanceId,
  IN       UINT32                         MaxNumWeights,
     OUT   UINT64                         *ApmWeights,
     OUT   UINT32                         *NumWeightsRead,
     OUT   UINT32                         *EnergyCountNormalize
  )
{
  return EFI_UNSUPPORTED;
}


/*----------------------------------------------------------------------------------------
/**
  Program PsiVid and PsiVidEn

  Parameters:
  This
    A pointer to the PEI_AMD_NBIO_SMU_SERVICES_PPI instance.
  InstanceId
    The unique identifier of the NBIO instance associated with this socket/die
  TargetVid
    Target Vid value (0 to skip enablement)
  TargetNbVid
    Target NbVid value (0 to skip enablement)
**/
EFI_STATUS
SmuPsiControl (
  IN       PEI_AMD_NBIO_SMU_SERVICES_PPI  *This,
  IN       UINT32                         InstanceId,
  IN       UINT32                         TargetVid,
  IN       UINT32                         TargetNbVid
  )
{
  return EFI_UNSUPPORTED;
}

/*----------------------------------------------------------------------------------------
/**
  Returns the TDP value from cTDP or SMU-defined value from SystemConfig in milliwatts

  Parameters:
  This
    A pointer to the PEI_AMD_NBIO_SMU_SERVICES_PPI instance.
  InstanceId
    The unique identifier of the NBIO instance associated with this socket/die
  TdpValue
    Pointer to a UINT32 to store the TDP value in milliwatts

  Status Codes Returned:
  EFI_SUCCESS           - TdpValue is updated with the cTDP or SmuTDP value as appropriate
  EFI_INVALID_PARAMETER - One of the input parameters was invalid
                        - InstanceId did not reference a valid NBIO instance
  EFI_UNSUPPORTED       - This function is not supported by this version of the driver OR TdpValue is not available
**/
EFI_STATUS
SmuGetTdpValue (
  IN       PEI_AMD_NBIO_SMU_SERVICES_PPI  *This,
  IN       UINT32                         InstanceId,
     OUT   UINT32                         *TdpValue
  )
{
  return EFI_UNSUPPORTED;
}

/*----------------------------------------------------------------------------------------
/**
  Returns the brand string read from SMN space.

  Parameters:
  This
    A pointer to the PEI_AMD_NBIO_SMU_SERVICES_PPI instance.
  InstanceId
    The unique identifier of the NBIO instance associated with this socket/die
  BrandStringLength
    Number of characters to be read.  This value does NOT have to be a multiple of 4.  NBIO driver code will be responsible for alignment, endianness, and string length.
  BrandString
    Pointer to a CHAR array to store the brand string.

  Status Codes Returned:
  EFI_SUCCESS           - BrandString has been updated with the value read from SMU
  EFI_INVALID_PARAMETER - One of the input parameters was invalid
                        - InstanceId did not reference a valid NBIO instance
  EFI_UNSUPPORTED       - This function is not supported by this version of the driver
**/
EFI_STATUS
SmuReadBrandString (
  IN       PEI_AMD_NBIO_SMU_SERVICES_PPI  *This,
  IN       UINT32                         InstanceId,
  IN       UINT32                         BrandStringLength,
     OUT   UINT8                          *BrandString
  )
{
  GNB_HANDLE                      *GnbHandle;
  EFI_STATUS                      Status;
  UINT32                          SmuArg[6];
  UINT32                          SmuResult;
  UINT8                           *StringPtr;
  UINT32                          StringCount;
  UINT32                          ByteCount;
  UINT32                          Iteration;

  IDS_HDT_CONSOLE (MAIN_FLOW, "SmuServiceRequest Entry\n");
  Status = SmuGetGnbHandle (InstanceId, &GnbHandle);
  if (Status == EFI_SUCCESS) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "GnbHandle Found\n");
    StringCount = BrandStringLength;
    StringPtr = BrandString;
    Iteration = 0;
    while (StringCount != 0) {
      NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
      SmuArg[0] = Iteration++;
      SmuResult = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (GnbHandle), BIOSSMC_MSG_GetNameString, SmuArg, 0);
      if (SmuResult == 1) {
        ByteCount = (StringCount < 4) ? StringCount : 4;
        LibAmdMemCopy (StringPtr, SmuArg, StringCount, (AMD_CONFIG_PARAMS *) NULL);
        StringPtr += ByteCount;
        StringCount -= ByteCount;
      } else {
        Status = EFI_INVALID_PARAMETER;
        IDS_HDT_CONSOLE (MAIN_FLOW, "SmuRequestFail!!\n");
        break;
      }
    }
  }
    IDS_HDT_CONSOLE (MAIN_FLOW, "SmuServiceRequest Exit Status = %d\n", Status);
  return Status;
}

/*----------------------------------------------------------------------------------------
/**
  Reads the Core PllLock Timer and returns the programmed value

  Parameters:
  This
    A pointer to the PEI_AMD_NBIO_SMU_SERVICES_PPI instance.
  InstanceId
    The unique identifier of the NBIO instance associated with this socket/die
  LockTimerValue
    Pointer to a UINT32 to store the value read from the Core PLL Lock Timer.  This field alters the timing from PLL lock enable to Pll frequency lock. Please consult the PLL specification for more detail.

  Status Codes Returned:
  EFI_SUCCESS           - LockTimerValue has been updated with the value read from the PLL Lock Timer register field
  EFI_INVALID_PARAMETER - One of the input parameters was invalid
                        - InstanceId did not reference a valid NBIO instance
  EFI_UNSUPPORTED       - This function is not supported by this version of the driver
**/
EFI_STATUS
SmuReadCorePllLockTimer (
  IN       PEI_AMD_NBIO_SMU_SERVICES_PPI  *This,
  IN       UINT32                         InstanceId,
     OUT   UINT32                         *LockTimerValue
  )
{
  return EFI_UNSUPPORTED;
}

/*----------------------------------------------------------------------------------------
/**
  set the downcore register to the specified value on all dies across the system.

  Parameters:
  This
    A pointer to the PEI_AMD_NBIO_SMU_SERVICES_PPI instance.
  CoreDisMask
    The value to set the downcore register to.

  Status Codes Returned:
  EFI_SUCCESS           - The downcore register was successfully updated.
  EFI_NOT_FOUND         - the PPI is not in the database.

**/
EFI_STATUS
SmuSetDownCoreRegister (
  IN       PEI_AMD_NBIO_SMU_SERVICES_PPI  *This,
  IN       UINT32                         CoreDisMask
)
{
  UINT32                          SmuArg[6];
  EFI_PEI_SERVICES                **PeiServices;
  PEI_AMD_NBIO_PCIE_SERVICES_PPI  *PcieServicesPpi;
  PCIe_PLATFORM_CONFIG            *Pcie;
  EFI_STATUS                      Status;
  GNB_HANDLE                      *GnbHandle;
  GNB_PCIE_INFORMATION_DATA_HOB   *PciePlatformConfigHob;

  IDS_HDT_CONSOLE (MAIN_FLOW, "SmuSetDownCoreRegister Entry\n");
  GnbHandle = NULL;

  PeiServices = (EFI_PEI_SERVICES **) GetPeiServicesTablePointer ();
  Status = (*PeiServices)->LocatePpi (
                             PeiServices,
                             &gAmdNbioPcieServicesPpiGuid,
                             0,
                             NULL,
                             (VOID **)&PcieServicesPpi
                             );
  if (Status == EFI_SUCCESS) {
    PcieServicesPpi->PcieGetTopology (PcieServicesPpi, &PciePlatformConfigHob);
    Pcie = &(PciePlatformConfigHob->PciePlatformConfigHob);

    GnbHandle = NbioGetHandle (Pcie);
    while (GnbHandle != NULL) {
      IDS_HDT_CONSOLE (MAIN_FLOW, "  down core\n");
      Status = NbioRegisterWrite (GnbHandle, TYPE_SMN, PWR_060_ADDRESS, &CoreDisMask, 0);
      NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
      SmuArg[0] = 0xAA55AA55;
      Status = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (GnbHandle), SMC_MSG_TestMessage, SmuArg, 0);
      GnbHandle = GnbGetNextHandle (GnbHandle);
    }
  }

  IDS_HDT_CONSOLE (MAIN_FLOW, "SmuSetDownCoreRegister(%x) Exit\n", Status);
  return Status;
}

/*----------------------------------------------------------------------------------------
/**
  disable SMT on all dies across the system. This routine should only be called from the BSP.

  Parameters:
  This
    A pointer to the PEI_AMD_NBIO_SMU_SERVICES_PPI instance.

  Status Codes Returned:
  EFI_SUCCESS           - SMT was successfully disabled.
  EFI_NOT_FOUND         - the PPI is not in the database.

**/
EFI_STATUS
SmuDisableSmt (
  IN       PEI_AMD_NBIO_SMU_SERVICES_PPI  *This
)
{
  UINT32                          SmuArg[6];
  EFI_PEI_SERVICES                **PeiServices;
  PEI_AMD_NBIO_PCIE_SERVICES_PPI  *PcieServicesPpi;
  PCIe_PLATFORM_CONFIG            *Pcie;
  EFI_STATUS                      Status;
  GNB_HANDLE                      *GnbHandle;
  GNB_PCIE_INFORMATION_DATA_HOB   *PciePlatformConfigHob;
  PWR_01C_STRUCT                  ThreadConfiguration;

  IDS_HDT_CONSOLE (MAIN_FLOW, "SmuDisableSmt Entry\n");
  GnbHandle = NULL;

  PeiServices = (EFI_PEI_SERVICES **) GetPeiServicesTablePointer ();
  Status = (*PeiServices)->LocatePpi (
                             PeiServices,
                             &gAmdNbioPcieServicesPpiGuid,
                             0,
                             NULL,
                             (VOID **)&PcieServicesPpi
                             );
  if (Status == EFI_SUCCESS) {
    PcieServicesPpi->PcieGetTopology (PcieServicesPpi, &PciePlatformConfigHob);
    Pcie = &(PciePlatformConfigHob->PciePlatformConfigHob);

    GnbHandle = NbioGetHandle (Pcie);
    while (GnbHandle != NULL) {
      IDS_HDT_CONSOLE (MAIN_FLOW, "  Disabling SMT\n");
      Status = NbioRegisterRead (GnbHandle, TYPE_SMN, THREAD_CONFIGURATION_ADDRESS, &ThreadConfiguration, 0);
      ThreadConfiguration.Field.SMTDisable = 1;
      Status = NbioRegisterWrite (GnbHandle, TYPE_SMN, THREAD_CONFIGURATION_ADDRESS, &ThreadConfiguration.Value, 0);
      NbioSmuServiceCommonInitArgumentsV10 (SmuArg);
      SmuArg[0] = 0xAA55AA55;
      Status = NbioSmuServiceRequestV10 (NbioGetHostPciAddress (GnbHandle), SMC_MSG_TestMessage, SmuArg, 0);
      GnbHandle = GnbGetNextHandle (GnbHandle);
    }
  }

  IDS_HDT_CONSOLE (MAIN_FLOW, "SmuDisableSmt(%x) Exit\n", Status);
  return Status;
}

/*----------------------------------------------------------------------------------------
 *                          P P I   D E S C R I P T O R
 *----------------------------------------------------------------------------------------
 */

PEI_AMD_NBIO_SMU_SERVICES_PPI mNbioSmuServicePpi = {
  AMD_NBIO_SMU_SERVICES_REVISION,  ///< revision
  SmuReadFuseByName,
  SmuReadFuseByLocation,
  SmuServiceRequest,
  SmuDxioServiceRequest,
  SmuRegisterRead,
  SmuRegisterWrite,
  SmuRegisterRMW,
  SmuHtcControl,
  SmuReadCacWeights,
  SmuPsiControl,
  SmuGetTdpValue,
  SmuReadBrandString,
  SmuReadCorePllLockTimer,
  SmuSetDownCoreRegister,
  SmuDisableSmt
};



