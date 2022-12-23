//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


/** @file
  Internal header to provide AmiHstiLib ....
  

**/
#include <Library/UefiBootServicesTableLib.h>
#include <Token.h>
#include <Base.h>
#include <Uefi/UefiBaseType.h>
#include <Uefi/UefiSpec.h>
#include <IndustryStandard/Hsti.h>
//#include <Library/HstiLib.h>
#include <Library/UefiLib.h>
#include <Library/PrintLib.h>
#include <UefiHii.h>
#include <Library/HiiLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Protocol/HiiUtilities.h>
#include <Library/DebugLib.h>
#include <AmiDxeLib.h>
#include <Guid/AmiHstiPkgTokenSpace.h>

extern EFI_GUID gEfiGlobalVariableGuid;
extern EFI_GUID gEfiEventReadyToBootGuid;



EFI_STATUS ReportError(         
        UINT32 BitNum,
        UINT16 ErrorNum,
        STRING_REF Token);


EFI_STATUS
EFIAPI
HstiLibSetTable (
  IN VOID                     *Hsti,
  IN UINTN                    HstiSize
  );


EFI_STATUS
EFIAPI
HstiLibAppendErrorString (
  IN UINT32                   Role,
  IN CHAR16                   *ImplementationID, OPTIONAL
  IN CHAR16                   *ErrorString
  );

EFI_STATUS
EFIAPI
HstiLibSetFeaturesVerified (
  IN UINT32                   Role,
  IN CHAR16                   *ImplementationID, OPTIONAL
  IN UINT32                   ByteIndex,
  IN UINT8                    BitMask
  );


EFI_STATUS
EFIAPI
HstiLibSetWindowsSecurityFeaturesVerified (
  IN UINT32                   Role,
  IN CHAR16                   *ImplementationID, OPTIONAL
  IN UINT32                   ByteIndex,
  IN UINT8                    BitMask
  );

