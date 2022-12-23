/* $NoKeywords:$ */
/**
 * @file
 *
 * Fabric Pstate Services Protocol prototype definition
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Fabric
 * @e \$Revision: 313706 $   @e \$Date: 2015-02-25 21:00:43 -0600 (Wed, 25 Feb 2015) $
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
 **/

#ifndef _NBIO_SMU_SERVICES_PROTOCOL_H_
#define _NBIO_SMU_SERVICES_PROTOCOL_H_

// Current PROTOCOL revision
#define DXE_AMD_NBIO_SMU_SERVICES_DXE_REVISION   0x00

///
/// Forward declaration for the NBIO_SMU_SERVICES_PROTOCOL
///
typedef struct _DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL;


//
// Protocol Definitions
//
/**
  Reads a fuse value based on an enumerated list of fuse "names"
  This
    A pointer to the DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL instance.
  FuseChain
    The "name" of the fuse from an enumerated list of fuses supported by this function
  FuseValue
    Pointer to the value of the fuse
**/
typedef
EFI_STATUS
(EFIAPI * AMD_SMU_SERVICES_READ_FUSE_BY_NAME) (
  IN  DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL  *This,
  IN       UINT32                         InstanceId,
  IN       UINTN                          FuseName,
  IN OUT   UINTN                          *BufferSize,
     OUT   UINT8                          *FuseValue
);

/**
  Reads a fuse value based on chain, start bit, and size

  This
    A pointer to the DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL instance.
  FuseChain
    The chain number of the fuse to read
  FuseStartBit
    The starting bit within the specified fuse chain of the fuse to read
  FuseSize
    The bitfield width of the fuse to read
  FuseValue
    Pointer to the value of the fuse
**/
typedef
EFI_STATUS
(EFIAPI * AMD_SMU_SERVICES_READ_FUSE_BY_NUMBER) (
  IN  DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL  *This,
  IN  UINT32  FuseChain,
  IN  UINT32  FuseStartBit,
  IN  UINT32  FuseSize,
  OUT UINT32  *FuseValue
);

/**
  Executes a specific SMU service and returns the results

  This
    A pointer to the DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL instance.
  ServiceRequest
    The service request identifier
  InputParameters
    Pointer to an array of service request arguments (for CZ, UINT32[6])
  ReturnValues
    Pointer to an array of service request response values (for CZ, UINT32[6])
**/
typedef
EFI_STATUS
(EFIAPI * AMD_SMU_SERVICES_SMU_SERVICE_REQUEST) (
  IN  DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL  *This,
  IN  UINT32                              InstanceId,
  IN  UINT32                              ServiceRequest,
  IN  UINT32                              *InputParameters,
  OUT UINT32                              *ReturnValues
);

/**
  Reads a 32-bit register from SMU register space

  This
    A pointer to the DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL instance.
  InstanceId
    The unique identifier of the NBIO instance associated with this socket/die
  RegisterIndex
    The index of the register to be read
  RegisterValue
    Pointer to a UINT32 to store the value read from the register
**/
typedef
EFI_STATUS
(EFIAPI * AMD_SMU_SERVICES_SMU_REGISTER_READ) (
  IN  DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL  *This,
  IN  UINT32  InstanceId,
  IN  UINT32  RegisterIndex,
  OUT UINT32  *RegisterValue
);

/**
  Writes a 32-bit register in SMU register space

  This
    A pointer to the DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL instance.
  InstanceId
    The unique identifier of the NBIO instance associated with this socket/die
  RegisterIndex
    The index of the register to be read
  RegisterValue
    Pointer to a UINT32 holding the value to write to the register
**/
typedef
EFI_STATUS
(EFIAPI * AMD_SMU_SERVICES_SMU_REGISTER_WRITE) (
  IN  DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL  *This,
  IN  UINT32  InstanceId,
  IN  UINT32  RegisterIndex,
  IN  UINT32  *RegisterValue
);

/**
  Read/Modify/Write a 32-bit register from SMU register space

  This
    A pointer to the DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL instance.
  InstanceId
    The unique identifier of the NBIO instance associated with this socket/die
  RegisterIndex
    The index of the register to be read
  RegisterANDValue
    UINT32 holding the value to be "ANDed" with the data read from the register (i.e. mask of data that will not be modified)
  RegisterORValue
    UINT32 holding the value to be "ORed" with the data read from the register (i.e. data bits to be "set" by this function)
**/
typedef
EFI_STATUS
(EFIAPI * AMD_SMU_SERVICES_SMU_REGISTER_RMW) (
  IN  DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL  *This,
  IN  UINT32  InstanceId,
  IN  UINT32  RegisterIndex,
  IN  UINT32  RegisterANDValue,
  IN  UINT32  RegisterORValue
);

/**
  Returns the brand string read from SMN space.

  Parameters:
  This
    A pointer to the DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL instance.
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
  IN  DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL  *This,
  IN  UINT32                              InstanceId,
  IN  UINT32                              BrandStringLength,
  OUT UINT8                               *BrandString
);

/**
  Returns the CAC weights read from SMU

  Parameters:
  This
    A pointer to the DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL instance.
  MaxNumWeights
    The number of values to read from the SMU (defines the maximum size of ApmWeights return data buffer)
  DpmWeights
    Pointer to return data buffer

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
  IN  DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL  *This,
  IN  UINT32                              MaxNumWeights,
  OUT UINT64                              *DpmWeights
);

/**
  Returns the throttle thresholds read from SMU

  Parameters:
  This
    A pointer to the DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL instance.
  Thresholds
    Pointer to return data buffer

  Status Codes Returned:
  EFI_SUCCESS           - ApmWeights contains the throttle thresholds read from SMU
  EFI_UNSUPPORTED       - This function is not supported by this version of the driver
**/
typedef
EFI_STATUS
(EFIAPI * AMD_SMU_SERVICES_Read_THROTTLE_THRESHOLDS) (
  IN  DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL  *This,
  OUT UINT32                              *Thresholds
);

///
/// The Dxe of SMU Services
///
struct _DXE_AMD_NBIO_SMU_SERVICES_PROTOCOL {
  UINT32                                     Revision;                     ///< revision
  AMD_SMU_SERVICES_READ_FUSE_BY_NAME         AmdSmuReadFuseByName;         ///<
  AMD_SMU_SERVICES_READ_FUSE_BY_NUMBER       AmdSmuReadFuseByNumber;       ///<
  AMD_SMU_SERVICES_SMU_SERVICE_REQUEST       AmdSmuServiceRequest;         ///<
  AMD_SMU_SERVICES_SMU_REGISTER_READ         AmdSmuRegisterRead;           ///<
  AMD_SMU_SERVICES_SMU_REGISTER_WRITE        AmdSmuRegisterWrite;          ///<
  AMD_SMU_SERVICES_SMU_REGISTER_RMW          AmdSmuRegisterRMW;            ///<
  AMD_SMU_SERVICES_READ_BRAND_STRING         AmdSmuReadBrandString;        ///<
  AMD_SMU_SERVICES_READ_CAC_WEIGHTS          AmdSmuReadCacWeights;         ///<
  AMD_SMU_SERVICES_Read_THROTTLE_THRESHOLDS  AmdSmuReadThrottleThresholds; ///<
};

extern EFI_GUID gAmdNbioSmuServicesProtocolGuid;

#endif

