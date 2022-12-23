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
#ifndef _AMD_NBIO_SMU_SERVICES_PPI_H_
#define _AMD_NBIO_SMU_SERVICES_PPI_H_

// Current PPI revision
#define AMD_NBIO_SMU_SERVICES_REVISION   0x00

typedef struct _PEI_AMD_NBIO_SMU_SERVICES_PPI PEI_AMD_NBIO_SMU_SERVICES_PPI;

//
// PPI prototype
//
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
typedef
EFI_STATUS
(EFIAPI *AMD_SMU_SERVICES_READ_FUSE_BY_NAME) (
  IN       PEI_AMD_NBIO_SMU_SERVICES_PPI  *This,
  IN       UINT32                         InstanceId,
  IN       UINTN                          FuseName,
  IN OUT   UINTN                          *BufferSize,
     OUT   UINT8                          *FuseValue
  );

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
typedef
EFI_STATUS
(EFIAPI * AMD_SMU_SERVICES_READ_FUSE_BY_NUMBER) (
  IN  PEI_AMD_NBIO_SMU_SERVICES_PPI  *This,
  IN  UINT32                         InstanceId,
  IN  UINT32                         FuseChain,
  IN  UINT32                         FuseStartBit,
  IN  UINT32                         FuseSize,
  OUT UINT32                         *FuseValue
);

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
typedef
EFI_STATUS
(EFIAPI * AMD_SMU_SERVICES_SMU_SERVICE_REQUEST) (
  IN  PEI_AMD_NBIO_SMU_SERVICES_PPI  *This,
  IN  UINT32                         InstanceId,
  IN  UINT32                         ServiceRequest,
  IN  UINT32                         *InputParameters,
  OUT UINT32                         *ReturnValues
);

/**
* Executes a specific DXIO service and returns the results
* (Generally intended for NBIO internal requests)

  Parameters:
  This
    A pointer to the PEI_AMD_NBIO_SMU_SERVICES_PPI instance.
  InstanceId
    The unique identifier of the NBIO instance associated with this socket/die
  ServiceRequest
    The DXIO service request identifier
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
typedef
EFI_STATUS
(EFIAPI * AMD_SMU_SERVICES_DXIO_SERVICE_REQUEST) (
  IN  PEI_AMD_NBIO_SMU_SERVICES_PPI  *This,
  IN  UINT32                         InstanceId,
  IN  UINT32                         ServiceRequest,
  IN  UINT32                         *InputParameters,
  OUT UINT32                         *ReturnValues
);

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
typedef
EFI_STATUS
(EFIAPI * AMD_SMU_SERVICES_SMU_REGISTER_READ) (
  IN  PEI_AMD_NBIO_SMU_SERVICES_PPI  *This,
  IN  UINT32                         InstanceId,
  IN  UINT32                         RegisterIndex,
  OUT UINT32                         *RegisterValue
);

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
typedef
EFI_STATUS
(EFIAPI * AMD_SMU_SERVICES_SMU_REGISTER_WRITE) (
  IN  PEI_AMD_NBIO_SMU_SERVICES_PPI  *This,
  IN  UINT32                         InstanceId,
  IN  UINT32                         RegisterIndex,
  IN  UINT32                         *RegisterValue
);

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
typedef
EFI_STATUS
(EFIAPI * AMD_SMU_SERVICES_SMU_REGISTER_RMW) (
  IN  PEI_AMD_NBIO_SMU_SERVICES_PPI  *This,
  IN  UINT32                         InstanceId,
  IN  UINT32                         RegisterIndex,
  IN  UINT32                         RegisterANDValue,
  IN  UINT32                         RegisterORValue
);

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
typedef
EFI_STATUS
(EFIAPI * AMD_SMU_SERVICES_HTC_CONTROL) (
  IN  PEI_AMD_NBIO_SMU_SERVICES_PPI  *This,
  IN  UINT32                         InstanceId,
  OUT BOOLEAN                        *HtcStatus
);

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
typedef
EFI_STATUS
(EFIAPI * AMD_SMU_SERVICES_READ_CAC_WEIGHTS) (
  IN  PEI_AMD_NBIO_SMU_SERVICES_PPI  *This,
  IN  UINT32                         InstanceId,
  IN  UINT32                         MaxNumWeights,
  OUT UINT64                         *ApmWeights,
  OUT UINT32                         *NumWeightsRead,
  OUT UINT32                         *EnergyCountNormalize
);

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
typedef
EFI_STATUS
(EFIAPI * AMD_SMU_SERVICES_PSI_CONTROL) (
  IN  PEI_AMD_NBIO_SMU_SERVICES_PPI  *This,
  IN  UINT32                         InstanceId,
  IN  UINT32                         TargetVid,
  IN  UINT32                         TargetNbVid
);

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
typedef
EFI_STATUS
(EFIAPI * AMD_SMU_SERVICES_GET_TDP_VALUE) (
  IN  PEI_AMD_NBIO_SMU_SERVICES_PPI  *This,
  IN  UINT32                         InstanceId,
  OUT UINT32                         *TdpValue
);

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
typedef
EFI_STATUS
(EFIAPI * AMD_SMU_SERVICES_READ_BRAND_STRING) (
  IN  PEI_AMD_NBIO_SMU_SERVICES_PPI  *This,
  IN  UINT32                         InstanceId,
  IN  UINT32                         BrandStringLength,
  OUT UINT8                          *BrandString
);

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
typedef
EFI_STATUS
(EFIAPI * AMD_SMU_SERVICES_READ_CORE_PLL_LOCK_TIMER) (
  IN  PEI_AMD_NBIO_SMU_SERVICES_PPI  *This,
  IN  UINT32                         InstanceId,
  OUT UINT32                         *LockTimerValue
);

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
typedef
EFI_STATUS
(EFIAPI * AMD_SMU_SERVICES_SET_DOWNCORE_REGISTER) (
  IN  PEI_AMD_NBIO_SMU_SERVICES_PPI  *This,
  IN  UINT32                         CoreDisMask
);

/**
  disable SMT on all dies across the system. This routine should only be called from the BSP.

  Parameters:
  This
    A pointer to the PEI_AMD_NBIO_SMU_SERVICES_PPI instance.

  Status Codes Returned:
  EFI_SUCCESS           - SMT was successfully disabled.
  EFI_NOT_FOUND         - the PPI is not in the database.

**/
typedef
EFI_STATUS
(EFIAPI * AMD_SMU_SERVICES_DISABLE_SMT) (
  IN  PEI_AMD_NBIO_SMU_SERVICES_PPI  *This
);

///
/// The Ppi of SMU sevices
///
struct _PEI_AMD_NBIO_SMU_SERVICES_PPI {
  UINT32                                     Revision;                ///< revision
  AMD_SMU_SERVICES_READ_FUSE_BY_NAME         SmuReadFuseByName;       ///<
  AMD_SMU_SERVICES_READ_FUSE_BY_NUMBER       SmuReadFuseByLocation;   ///<
  AMD_SMU_SERVICES_SMU_SERVICE_REQUEST       SmuServiceRequest;       ///<
  AMD_SMU_SERVICES_DXIO_SERVICE_REQUEST      SmuDxioServiceRequest;   ///<
  AMD_SMU_SERVICES_SMU_REGISTER_READ         SmuRegisterRead;         ///<
  AMD_SMU_SERVICES_SMU_REGISTER_WRITE        SmuRegisterWrite;        ///<
  AMD_SMU_SERVICES_SMU_REGISTER_RMW          SmuRegisterRMW;          ///<
  AMD_SMU_SERVICES_HTC_CONTROL               SmuHtcControl;           ///<
  AMD_SMU_SERVICES_READ_CAC_WEIGHTS          SmuReadCacWeights;       ///<
  AMD_SMU_SERVICES_PSI_CONTROL               SmuPsiControl;           ///<
  AMD_SMU_SERVICES_GET_TDP_VALUE             SmuGetTdpValue;          ///<
  AMD_SMU_SERVICES_READ_BRAND_STRING         SmuReadBrandString;      ///<
  AMD_SMU_SERVICES_READ_CORE_PLL_LOCK_TIMER  SmuReadCorePllLockTimer; ///<
  AMD_SMU_SERVICES_SET_DOWNCORE_REGISTER     SmuSetDownCoreRegister;  ///<
  AMD_SMU_SERVICES_DISABLE_SMT               SmuDisableSmt;           ///<
};

extern EFI_GUID gAmdNbioSmuServicesPpiGuid ;

#endif //

