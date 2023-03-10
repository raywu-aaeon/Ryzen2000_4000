/** @file

  Copyright (c) 2015 - 2016, Intel Corporation. All rights reserved.<BR>
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "HstiDxe.h"
// AMI PORTING BEGIN
#include "Token.h"
// AMI PORTING END

EFI_GUID gAdapterInfoPlatformSecurityGuid = ADAPTER_INFO_PLATFORM_SECURITY_GUID;

/**
  Find HSTI table in AIP protocol, and return the data.
  This API will return the HSTI table with indicated Role and ImplementationID,
  NULL ImplementationID means to find the first HSTI table with indicated Role.

  @param Role             Role of HSTI data.
  @param ImplementationID ImplementationID of HSTI data.
                          NULL means find the first one match Role.
  @param HstiData         HSTI data. This buffer is allocated by callee, and it
                          is the responsibility of the caller to free it after
                          using it.
  @param HstiSize         HSTI size

  @return Aip             The AIP protocol having this HSTI.
  @return NULL            There is not HSTI table with the Role and ImplementationID published in system.
**/
VOID *
InternalHstiFindAip (
  IN UINT32                   Role,
  IN CHAR16                   *ImplementationID OPTIONAL,
  OUT VOID                    **HstiData OPTIONAL,
  OUT UINTN                   *HstiSize OPTIONAL
  )
{
  EFI_STATUS                        Status;
  EFI_ADAPTER_INFORMATION_PROTOCOL  *Aip;
  UINTN                             NoHandles;
  EFI_HANDLE                        *Handles;
  UINTN                             Index;
  EFI_GUID                          *InfoTypesBuffer;
  UINTN                             InfoTypesBufferCount;
  UINTN                             InfoTypesIndex;
  EFI_ADAPTER_INFORMATION_PROTOCOL  *AipCandidate;
  VOID                              *InformationBlock;
  UINTN                             InformationBlockSize;
  ADAPTER_INFO_PLATFORM_SECURITY    *Hsti;

  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiAdapterInformationProtocolGuid,
                  NULL,
                  &NoHandles,
                  &Handles
                  );
  if (EFI_ERROR (Status)) {
    return NULL;
  }

  Hsti = NULL;
  Aip = NULL;
  InformationBlock = NULL;
  InformationBlockSize = 0;
  for (Index = 0; Index < NoHandles; Index++) {
    Status = gBS->HandleProtocol (
                    Handles[Index],
                    &gEfiAdapterInformationProtocolGuid,
                    (VOID **)&Aip
                    );
    if (EFI_ERROR (Status)) {
      continue;
    }

    //
    // Check AIP
    //
    Status = Aip->GetSupportedTypes (
                    Aip,
                    &InfoTypesBuffer,
                    &InfoTypesBufferCount
                    );
    if (EFI_ERROR (Status)) {
      continue;
    }

    AipCandidate = NULL;
    for (InfoTypesIndex = 0; InfoTypesIndex < InfoTypesBufferCount; InfoTypesIndex++) {
      if (CompareGuid (&InfoTypesBuffer[InfoTypesIndex], &gAdapterInfoPlatformSecurityGuid)) {
        AipCandidate = Aip;
        break;
      }
    }
    FreePool (InfoTypesBuffer);

    if (AipCandidate == NULL) {
      continue;
    }

    //
    // Check HSTI Role
    //
    Aip = AipCandidate;
    Status = Aip->GetInformation (
                    Aip,
                    &gAdapterInfoPlatformSecurityGuid,
                    &InformationBlock,
                    &InformationBlockSize
                    );
    if (EFI_ERROR (Status)) {
      continue;
    }

    Hsti = InformationBlock;
    if ((Hsti->Role == Role) && 
        ((ImplementationID == NULL) || (StrCmp (ImplementationID, Hsti->ImplementationID) == 0))) {
      break;
    } else {
      Hsti = NULL;
      FreePool (InformationBlock);
      continue;
    }
  }
  FreePool (Handles);

  if (Hsti == NULL) {
    return NULL;
  }

  if (HstiData != NULL) {
    *HstiData = InformationBlock;
  }
  if (HstiSize != NULL) {
    *HstiSize = InformationBlockSize;
  }
  return Aip;
}

/**
  Return if input HSTI data follows HSTI specification.

  @param HstiData  HSTI data
  @param HstiSize  HSTI size

  @retval TRUE  HSTI data follows HSTI specification.
  @retval FALSE HSTI data does not follow HSTI specification.
**/
BOOLEAN
InternalHstiIsValidTable (
  IN VOID                     *HstiData,
  IN UINTN                    HstiSize
  )
{
  ADAPTER_INFO_PLATFORM_SECURITY  *Hsti;
  UINTN                           Index;
  CHAR16                          *ErrorString;
  CHAR16                          ErrorChar;
  UINTN                           ErrorStringSize;
  UINTN                           ErrorStringLength;

  Hsti = HstiData;

  //
  // basic check for header
  //
  if (HstiData == NULL) {
    DEBUG ((EFI_D_ERROR, "HstiData == NULL\n"));
    return FALSE;
  }
  if (HstiSize < sizeof(ADAPTER_INFO_PLATFORM_SECURITY)) {
    DEBUG ((EFI_D_ERROR, "HstiSize < sizeof(ADAPTER_INFO_PLATFORM_SECURITY)\n"));
    return FALSE;
  }
// AMI_PORTING BEGIN  
// Structure changed:  SecurityFeatureRequired[] removed, WindowsSecurityFeaturesVerified[] added
#if defined (HSTI_REVISION) && (HSTI_REVISION == 0)
  if (((HstiSize - sizeof(ADAPTER_INFO_PLATFORM_SECURITY)) / 3) < Hsti->SecurityFeaturesSize) {
    DEBUG ((EFI_D_ERROR, "((HstiSize - sizeof(ADAPTER_INFO_PLATFORM_SECURITY)) / 3) < SecurityFeaturesSize\n"));
#elif defined (HSTI_REVISION) && (HSTI_REVISION == 1)
  if ( ((HstiSize - sizeof(ADAPTER_INFO_PLATFORM_SECURITY)- (4 * sizeof(UINT32))) / 2 ) < Hsti->SecurityFeaturesSize) {
    DEBUG ((EFI_D_ERROR, "((HstiSize - sizeof(ADAPTER_INFO_PLATFORM_SECURITY)- (4 * sizeof(UINT32))) / 2 ) < SecurityFeaturesSize\n"));
#endif
    return FALSE;
  }
  // AMI_PORTING END 

  //
  // Check Version
  //
  if (Hsti->Version != PLATFORM_SECURITY_VERSION_VNEXTCS) {
    DEBUG ((EFI_D_ERROR, "Version != PLATFORM_SECURITY_VERSION_VNEXTCS\n"));
    return FALSE;
  }

  //
  // Check Role
  //
  if ((Hsti->Role < PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE) ||
      (Hsti->Role > PLATFORM_SECURITY_ROLE_IMPLEMENTOR_ODM)) {
    DEBUG ((EFI_D_ERROR, "Role < PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE ||\n"));
    DEBUG ((EFI_D_ERROR, "Role > PLATFORM_SECURITY_ROLE_IMPLEMENTOR_ODM\n"));
    return FALSE;
  }

  //
  // Check ImplementationID
  //
  for (Index = 0; Index < sizeof(Hsti->ImplementationID)/sizeof(Hsti->ImplementationID[0]); Index++) {
    if (Hsti->ImplementationID[Index] == 0) {
      break;
    }
  }
  if (Index == sizeof(Hsti->ImplementationID)/sizeof(Hsti->ImplementationID[0])) {
    DEBUG ((EFI_D_ERROR, "ImplementationID is no NUL CHAR\n"));
    return FALSE;
  }

// AMI PORTING BEGIN
#if defined (HSTI_REVISION) && (HSTI_REVISION == 0)
  ErrorStringSize = HstiSize - sizeof(ADAPTER_INFO_PLATFORM_SECURITY) - Hsti->SecurityFeaturesSize * 3;
  ErrorString = (CHAR16 *)((UINTN)Hsti + sizeof(ADAPTER_INFO_PLATFORM_SECURITY) - Hsti->SecurityFeaturesSize * 3);
#elif defined (HSTI_REVISION) && (HSTI_REVISION == 1)
  ErrorStringSize = HstiSize - sizeof(ADAPTER_INFO_PLATFORM_SECURITY) - Hsti->SecurityFeaturesSize * 2 - (4 * sizeof(UINT32));
  ErrorString = (CHAR16 *)
          ((UINTN)Hsti + sizeof(ADAPTER_INFO_PLATFORM_SECURITY) + Hsti->SecurityFeaturesSize * 2 + (4 * sizeof(UINT32)));
#endif
// AMI_PORTING END
  //
  // basic check for ErrorString
  //
  if (ErrorStringSize == 0) {
    DEBUG ((EFI_D_ERROR, "ErrorStringSize == 0\n"));
    return FALSE;
  }
  // make sure String is unicode
  if ((ErrorStringSize & BIT0) != 0) {
    DEBUG ((EFI_D_ERROR, "(ErrorStringSize & BIT0) != 0\n"));
    return FALSE;
  }

  //
  // ErrorString might not be CHAR16 aligned.
  //
  CopyMem (&ErrorChar, ErrorString, sizeof(ErrorChar));
  for (ErrorStringLength = 0; (ErrorChar != 0) && (ErrorStringLength < (ErrorStringSize/2)); ErrorStringLength++) {
    ErrorString++;
    CopyMem (&ErrorChar, ErrorString, sizeof(ErrorChar));
  }

  //
  // check the length of ErrorString
  //
  if (ErrorChar != 0) {
    DEBUG ((EFI_D_ERROR, "ErrorString has no NUL CHAR\n"));
    return FALSE;
  }
  if (ErrorStringLength == (ErrorStringSize/2)) {
    DEBUG ((EFI_D_ERROR, "ErrorString Length incorrect\n"));
    return FALSE;
  }

  return TRUE;
}

/**
  Publish HSTI table in AIP protocol.

  One system should have only one PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE.

  If the Role is NOT PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
  SecurityFeaturesRequired field will be ignored.

  @param Hsti      HSTI data
  @param HstiSize  HSTI size

  @retval EFI_SUCCESS          The HSTI data is published in AIP protocol.
  @retval EFI_ALREADY_STARTED  There is already HSTI table with Role and ImplementationID published in system.
  @retval EFI_VOLUME_CORRUPTED The input HSTI data does not follow HSTI specification.
  @retval EFI_OUT_OF_RESOURCES There is not enough system resource to publish HSTI data in AIP protocol.
**/
EFI_STATUS
EFIAPI
HstiLibSetTable (
  IN VOID                     *Hsti,
  IN UINTN                    HstiSize
  )
{
  EFI_STATUS                       Status;
  EFI_HANDLE                       Handle;
  HSTI_AIP_PRIVATE_DATA            *HstiAip;
  EFI_ADAPTER_INFORMATION_PROTOCOL *Aip;
  UINT32                           Role;
  CHAR16                           *ImplementationID;
  // AMI PORTING BEGIN
  // the Security Features Required field has been removed
#if defined (HSTI_REVISION) && (HSTI_REVISION == 0)
  UINT32                           SecurityFeaturesSize;
  UINT8                            *SecurityFeaturesRequired;
#endif
// AMI_PORTING END

  if (!InternalHstiIsValidTable (Hsti, HstiSize)) {
    return EFI_VOLUME_CORRUPTED;
  }

  Role = ((ADAPTER_INFO_PLATFORM_SECURITY *)Hsti)->Role;
  ImplementationID = ((ADAPTER_INFO_PLATFORM_SECURITY *)Hsti)->ImplementationID;
  Aip = InternalHstiFindAip (Role, ImplementationID, NULL, NULL);
  if (Aip != NULL) {
    return EFI_ALREADY_STARTED;
  }

  HstiAip = AllocateZeroPool (sizeof(HSTI_AIP_PRIVATE_DATA));
  if (HstiAip == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  HstiAip->Hsti = AllocateCopyPool (HstiSize, Hsti);
  if (HstiAip->Hsti == NULL) {
    FreePool (HstiAip);
    return EFI_OUT_OF_RESOURCES;
  }
  // AMI PORTING BEGIN
  // the Security Features Required field has been removed
#if defined (HSTI_REVISION) && (HSTI_REVISION == 0)
  if (Role != PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE) {
    SecurityFeaturesRequired = (UINT8 *)HstiAip->Hsti + sizeof(ADAPTER_INFO_PLATFORM_SECURITY);
    SecurityFeaturesSize = ((ADAPTER_INFO_PLATFORM_SECURITY *)Hsti)->SecurityFeaturesSize;
    ZeroMem (SecurityFeaturesRequired, SecurityFeaturesSize);
  }
#endif
// AMI_PORTING END
  HstiAip->Signature = HSTI_AIP_PRIVATE_SIGNATURE;
  CopyMem (&HstiAip->Aip, &mAdapterInformationProtocol, sizeof(EFI_ADAPTER_INFORMATION_PROTOCOL));
  HstiAip->HstiSize = HstiSize;
  HstiAip->HstiMaxSize = HstiSize;
  
  Handle = NULL;
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &Handle,
                  &gEfiAdapterInformationProtocolGuid,
                  &HstiAip->Aip,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    FreePool (HstiAip->Hsti);
    FreePool (HstiAip);
  }

  return Status;
}

/**
  Search HSTI table in AIP protocol, and return the data.
  This API will return the HSTI table with indicated Role and ImplementationID,
  NULL ImplementationID means to find the first HSTI table with indicated Role.

  @param Role             Role of HSTI data.
  @param ImplementationID ImplementationID of HSTI data.
                          NULL means find the first one match Role.
  @param Hsti             HSTI data. This buffer is allocated by callee, and it
                          is the responsibility of the caller to free it after
                          using it.
  @param HstiSize         HSTI size

  @retval EFI_SUCCESS          The HSTI data in AIP protocol is returned.
  @retval EFI_NOT_FOUND        There is not HSTI table with the Role and ImplementationID published in system.
**/
EFI_STATUS
EFIAPI
HstiLibGetTable (
  IN UINT32                   Role,
  IN CHAR16                   *ImplementationID OPTIONAL,
  OUT VOID                    **Hsti,
  OUT UINTN                   *HstiSize
  )
{
  EFI_ADAPTER_INFORMATION_PROTOCOL *Aip;

  Aip = InternalHstiFindAip (Role, ImplementationID, Hsti, HstiSize);
  if (Aip == NULL) {
    return EFI_NOT_FOUND;
  }
  return EFI_SUCCESS;
}

/**
  Record FeaturesVerified in published HSTI table.
  This API will update the HSTI table with indicated Role and ImplementationID,
  NULL ImplementationID means to find the first HSTI table with indicated Role.

  @param Role             Role of HSTI data.
  @param ImplementationID ImplementationID of HSTI data.
                          NULL means find the first one match Role.
  @param ByteIndex        Byte index of FeaturesVerified of HSTI data.
  @param BitMask          Bit mask of FeaturesVerified of HSTI data.
  @param Set              TRUE means to set the FeaturesVerified bit.
                          FALSE means to clear the FeaturesVerified bit.

  @retval EFI_SUCCESS          The FeaturesVerified of HSTI data updated in AIP protocol.
  @retval EFI_NOT_STARTED      There is not HSTI table with the Role and ImplementationID published in system.
  @retval EFI_UNSUPPORTED      The ByteIndex is invalid.
**/
EFI_STATUS
InternalHstiRecordFeaturesVerified (
  IN UINT32                   Role,
  IN CHAR16                   *ImplementationID, OPTIONAL
  IN UINT32                   ByteIndex,
  IN UINT8                    Bit,
  IN BOOLEAN                  Set
  )
{
  EFI_ADAPTER_INFORMATION_PROTOCOL *Aip;
  ADAPTER_INFO_PLATFORM_SECURITY   *Hsti;
  UINTN                            HstiSize;
  UINT8                            *SecurityFeaturesVerified;
  EFI_STATUS                       Status;

  DEBUG((DEBUG_VERBOSE, "HstiRecordFeaturesVerified: \n\r"));
  
  DEBUG((DEBUG_VERBOSE, "ByteIndex = %X     Bit = %X      Set = %X\n\r", ByteIndex, Bit, Set));

  Aip = InternalHstiFindAip (Role, ImplementationID, (VOID **)&Hsti, &HstiSize);
  if (Aip == NULL) {
      DEBUG((DEBUG_VERBOSE, "Can't find the table: \n\r"));
    return EFI_NOT_STARTED;
  }

  if (ByteIndex >= Hsti->SecurityFeaturesSize) {
      DEBUG((DEBUG_VERBOSE, "Byte index too large: \n\r"));
    return EFI_UNSUPPORTED;
  }
  // AMI PORTING BEGIN
  // the Security Features Required field has been removed
#if defined (HSTI_REVISION) && (HSTI_REVISION == 0)
  SecurityFeaturesVerified = (UINT8 *)((UINTN)Hsti + sizeof(ADAPTER_INFO_PLATFORM_SECURITY) + Hsti->SecurityFeaturesSize * 2);
#elif defined (HSTI_REVISION) && (HSTI_REVISION == 1)
  SecurityFeaturesVerified = (UINT8 *)((UINTN)Hsti + sizeof(ADAPTER_INFO_PLATFORM_SECURITY) + Hsti->SecurityFeaturesSize);
#endif
// AMI PORTING END
  
  if (Set) {
    SecurityFeaturesVerified[ByteIndex] = (UINT8)(SecurityFeaturesVerified[ByteIndex] | (Bit));
  } else {
    SecurityFeaturesVerified[ByteIndex] = (UINT8)(SecurityFeaturesVerified[ByteIndex] & (~Bit));
  }

  Status = Aip->SetInformation (
                  Aip,
                  &gAdapterInfoPlatformSecurityGuid,
                  Hsti,
                  HstiSize
                  );
  return Status;
}

/**
  Set FeaturesVerified in published HSTI table.
  This API will update the HSTI table with indicated Role and ImplementationID,
  NULL ImplementationID means to find the first HSTI table with indicated Role.

  @param Role             Role of HSTI data.
  @param ImplementationID ImplementationID of HSTI data.
                          NULL means find the first one match Role.
  @param ByteIndex        Byte index of FeaturesVerified of HSTI data.
  @param BitMask          Bit mask of FeaturesVerified of HSTI data.

  @retval EFI_SUCCESS          The FeaturesVerified of HSTI data updated in AIP protocol.
  @retval EFI_NOT_STARTED      There is not HSTI table with the Role and ImplementationID published in system.
  @retval EFI_UNSUPPORTED      The ByteIndex is invalid.
**/
EFI_STATUS
EFIAPI
HstiLibSetFeaturesVerified (
  IN UINT32                   Role,
  IN CHAR16                   *ImplementationID, OPTIONAL
  IN UINT32                   ByteIndex,
  IN UINT8                    BitMask
  )
{
  return InternalHstiRecordFeaturesVerified (
           Role,
           ImplementationID,
           ByteIndex,
           BitMask,
           TRUE
           );
}

/**
  Clear FeaturesVerified in published HSTI table.
  This API will update the HSTI table with indicated Role and ImplementationID,
  NULL ImplementationID means to find the first HSTI table with indicated Role.

  @param Role             Role of HSTI data.
  @param ImplementationID ImplementationID of HSTI data.
                          NULL means find the first one match Role.
  @param ByteIndex        Byte index of FeaturesVerified of HSTI data.
  @param BitMask          Bit mask of FeaturesVerified of HSTI data.

  @retval EFI_SUCCESS          The FeaturesVerified of HSTI data updated in AIP protocol.
  @retval EFI_NOT_STARTED      There is not HSTI table with the Role and ImplementationID published in system.
  @retval EFI_UNSUPPORTED      The ByteIndex is invalid.
**/
EFI_STATUS
EFIAPI
HstiLibClearFeaturesVerified (
  IN UINT32                   Role,
  IN CHAR16                   *ImplementationID, OPTIONAL
  IN UINT32                   ByteIndex,
  IN UINT8                    BitMask
  )
{
  return InternalHstiRecordFeaturesVerified (
           Role,
           ImplementationID,
           ByteIndex,
           BitMask,
           FALSE
           );
}



//=======================================================================================
//=======================================================================================
//=======================================================================================
// AMI PORTING BEGIN
// This adds library support functions for the new windows bit field.  The functionality may be generically added by Intel once they support HSTI v2.0
/**
  Record WindowsSecurityFeaturesVerified in published HSTI table.
  This API will update the HSTI table with indicated Role and ImplementationID,
  NULL ImplementationID means to find the first HSTI table with indicated Role.

  @param Role             Role of HSTI data.
  @param ImplementationID ImplementationID of HSTI data.
                          NULL means find the first one match Role.
  @param ByteIndex        Byte index of WindowsSecurityFeaturesVerified of HSTI data.
  @param BitMask          Bit mask of WindowsSecurityFeaturesVerified of HSTI data.
  @param Set              TRUE means to set the WindowsSecurityFeaturesVerified bit.
                          FALSE means to clear the WindowsSecurityFeaturesVerified bit.

  @retval EFI_SUCCESS          The WindowsSecurityFeaturesVerified of HSTI data updated in AIP protocol.
  @retval EFI_NOT_STARTED      There is not HSTI table with the Role and ImplementationID published in system.
  @retval EFI_UNSUPPORTED      The ByteIndex is invalid.
**/
EFI_STATUS
InternalHstiRecordWindowsSecurityFeatureVerified (
  IN UINT32                   Role,
  IN CHAR16                   *ImplementationID, OPTIONAL
  IN UINT32                   ByteIndex,
  IN UINT8                    Bit,
  IN BOOLEAN                  Set
  )
{
  EFI_ADAPTER_INFORMATION_PROTOCOL *Aip;
  ADAPTER_INFO_PLATFORM_SECURITY   *Hsti;
  UINTN                            HstiSize;
  UINT8                            *WindowsSecurityFeaturesVerified;
  EFI_STATUS                       Status;

  DEBUG((DEBUG_VERBOSE, "HstiRecordWindowsSecurityFeatureVerified: \n\r"));

  DEBUG((DEBUG_VERBOSE, "ByteIndex = %X     Bit = %X      Set = %X\n\r", ByteIndex, Bit, Set));
  
  Aip = InternalHstiFindAip (Role, ImplementationID, (VOID **)&Hsti, &HstiSize);
  if (Aip == NULL) {
      DEBUG((DEBUG_VERBOSE, "Error: HSTI IBV table not found\n\r"));
    return EFI_NOT_STARTED;
  }

  if (ByteIndex >= HSTI_WINDOWS_SECURITY_FEATURE_MAX_BYTES) {
      DEBUG((DEBUG_VERBOSE, "Error: Pointing to byte beyond the end of the windows security feature bitmap\n\r"));
      return EFI_UNSUPPORTED;
  }

  WindowsSecurityFeaturesVerified = (UINT8 *)((UINTN)Hsti + sizeof(ADAPTER_INFO_PLATFORM_SECURITY) + Hsti->SecurityFeaturesSize * 2);
  if (Set) {
      WindowsSecurityFeaturesVerified[ByteIndex] = (UINT8)(WindowsSecurityFeaturesVerified[ByteIndex] | (Bit));
  } else {
      WindowsSecurityFeaturesVerified[ByteIndex] = (UINT8)(WindowsSecurityFeaturesVerified[ByteIndex] & (~Bit));
  }

  Status = Aip->SetInformation (
                  Aip,
                  &gAdapterInfoPlatformSecurityGuid,
                  Hsti,
                  HstiSize
                  );
  return Status;
}

/**
  Set WindowsSecurityFeaturesVerified in published HSTI table.
  This API will update the HSTI table with indicated Role and ImplementationID,
  NULL ImplementationID means to find the first HSTI table with indicated Role.

  @param Role             Role of HSTI data.
  @param ImplementationID ImplementationID of HSTI data.
                          NULL means find the first one match Role.
  @param ByteIndex        Byte index of WindowsSecurityFeaturesVerified of HSTI data.
  @param BitMask          Bit mask of WindowsSecurityFeaturesVerified of HSTI data.

  @retval EFI_SUCCESS          The WindowsSecurityFeaturesVerified of HSTI data updated in AIP protocol.
  @retval EFI_NOT_STARTED      There is not HSTI table with the Role and ImplementationID published in system.
  @retval EFI_UNSUPPORTED      The ByteIndex is invalid.
**/
EFI_STATUS
EFIAPI
HstiLibSetWindowsSecurityFeaturesVerified(
  IN UINT32                   Role,
  IN CHAR16                   *ImplementationID, OPTIONAL
  IN UINT32                   ByteIndex,
  IN UINT8                    BitMask
  )
{
    if (HSTI_REVISION == 0)
        return EFI_UNSUPPORTED;
    
  return InternalHstiRecordWindowsSecurityFeatureVerified (
           Role,
           ImplementationID,
           ByteIndex,
           BitMask,
           TRUE
           );
}

/**
  Clear WindowsSecurityFeaturesVerified in published HSTI table.
  This API will update the HSTI table with indicated Role and ImplementationID,
  NULL ImplementationID means to find the first HSTI table with indicated Role.

  @param Role             Role of HSTI data.
  @param ImplementationID ImplementationID of HSTI data.
                          NULL means find the first one match Role.
  @param ByteIndex        Byte index of WindowsSecurityFeaturesVerified of HSTI data.
  @param BitMask          Bit mask of WindowsSecurityFeaturesVerified of HSTI data.

  @retval EFI_SUCCESS          The WindowsSecurityFeaturesVerified of HSTI data updated in AIP protocol.
  @retval EFI_NOT_STARTED      There is not HSTI table with the Role and ImplementationID published in system.
  @retval EFI_UNSUPPORTED      The ByteIndex is invalid.
**/
EFI_STATUS
EFIAPI
HstiLibClearWindowsSecurityFeatureVerified (
  IN UINT32                   Role,
  IN CHAR16                   *ImplementationID, OPTIONAL
  IN UINT32                   ByteIndex,
  IN UINT8                    BitMask
  )
{
    if (HSTI_REVISION == 0)
        return EFI_UNSUPPORTED;

    return InternalHstiRecordWindowsSecurityFeatureVerified (
           Role,
           ImplementationID,
           ByteIndex,
           BitMask,
           FALSE
           );
}

// AMI PORTING END
//=======================================================================================
//=======================================================================================
//=======================================================================================
//=======================================================================================
//=======================================================================================
//=======================================================================================
//=======================================================================================
//=======================================================================================



/**
  Record ErrorString in published HSTI table.
  This API will update the HSTI table with indicated Role and ImplementationID,
  NULL ImplementationID means to find the first HSTI table with indicated Role.

  @param Role             Role of HSTI data.
  @param ImplementationID ImplementationID of HSTI data.
                          NULL means find the first one match Role.
  @param ErrorString      ErrorString of HSTI data.
  @param Append           TRUE means to append the ErrorString to HSTI table.
                          FALSE means to set the ErrorString in HSTI table.

  @retval EFI_SUCCESS          The ErrorString of HSTI data is published in AIP protocol.
  @retval EFI_NOT_STARTED      There is not HSTI table with the Role and ImplementationID published in system.
  @retval EFI_OUT_OF_RESOURCES There is not enough system resource to update ErrorString.
**/
EFI_STATUS
InternalHstiRecordErrorString (
  IN UINT32                   Role,
  IN CHAR16                   *ImplementationID, OPTIONAL
  IN CHAR16                   *ErrorString,
  IN BOOLEAN                  Append
  )
{
  EFI_ADAPTER_INFORMATION_PROTOCOL *Aip;
  ADAPTER_INFO_PLATFORM_SECURITY   *Hsti;
  UINTN                            HstiSize;
  UINTN                            StringSize;
  VOID                             *NewHsti;
  UINTN                            NewHstiSize;
  UINTN                            Offset;
  EFI_STATUS                       Status;

  Aip = InternalHstiFindAip (Role, ImplementationID, (VOID **)&Hsti, &HstiSize);
  if (Aip == NULL) {
    return EFI_NOT_STARTED;
  }

  if (Append) {
    Offset = HstiSize - sizeof(CHAR16);
  } else {
// AMI PORTING BEGIN
      // SecurityFeaturesRequired field was removed from the data structure and WindowsSecurityFeaturesVerified is added
#if defined (HSTI_REVISION) && (HSTI_REVISION == 0)
      Offset = sizeof(ADAPTER_INFO_PLATFORM_SECURITY) + Hsti->SecurityFeaturesSize * 3;
#elif defined (HSTI_REVISION) && (HSTI_REVISION == 1)
      Offset = sizeof(ADAPTER_INFO_PLATFORM_SECURITY) + Hsti->SecurityFeaturesSize * 2 + (4 * sizeof(UINT32));
#endif
// AMI PORTING END
  }
  StringSize = StrSize (ErrorString);

  NewHstiSize = Offset + StringSize;
  NewHsti = AllocatePool (NewHstiSize);
  if (NewHsti == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  CopyMem (NewHsti, Hsti, Offset);
  CopyMem ((UINT8 *)NewHsti + Offset, ErrorString, StringSize);

  Status = Aip->SetInformation (
                  Aip,
                  &gAdapterInfoPlatformSecurityGuid,
                  NewHsti,
                  NewHstiSize
                  );
  return Status;
}

/**
  Append ErrorString in published HSTI table.
  This API will update the HSTI table with indicated Role and ImplementationID,
  NULL ImplementationID means to find the first HSTI table with indicated Role.

  @param Role             Role of HSTI data.
  @param ImplementationID ImplementationID of HSTI data.
                          NULL means find the first one match Role.
  @param ErrorString      ErrorString of HSTI data.

  @retval EFI_SUCCESS          The ErrorString of HSTI data is updated in AIP protocol.
  @retval EFI_NOT_STARTED      There is not HSTI table with the Role and ImplementationID published in system.
  @retval EFI_OUT_OF_RESOURCES There is not enough system resource to update ErrorString.
**/
EFI_STATUS
EFIAPI
HstiLibAppendErrorString (
  IN UINT32                   Role,
  IN CHAR16                   *ImplementationID, OPTIONAL
  IN CHAR16                   *ErrorString
  )
{
  return InternalHstiRecordErrorString (
           Role,
           ImplementationID,
           ErrorString,
           TRUE
           );
}

/**
  Set a new ErrorString in published HSTI table.
  This API will update the HSTI table with indicated Role and ImplementationID,
  NULL ImplementationID means to find the first HSTI table with indicated Role.

  @param Role             Role of HSTI data.
  @param ImplementationID ImplementationID of HSTI data.
                          NULL means find the first one match Role.
  @param ErrorString      ErrorString of HSTI data.

  @retval EFI_SUCCESS          The ErrorString of HSTI data is updated in AIP protocol.
  @retval EFI_NOT_STARTED      There is not HSTI table with the Role and ImplementationID published in system.
  @retval EFI_OUT_OF_RESOURCES There is not enough system resource to update ErrorString.
**/
EFI_STATUS
EFIAPI
HstiLibSetErrorString (
  IN UINT32                   Role,
  IN CHAR16                   *ImplementationID, OPTIONAL
  IN CHAR16                   *ErrorString
  )
{
  return InternalHstiRecordErrorString (
           Role,
           ImplementationID,
           ErrorString,
           FALSE
           );
}
