//*************************************************************************
//<AMI_FHDR_START>
//
// Name:        BiosInfoPei.c
//
// Description: This file contains the functions used for ASUS certification
//
//<AMI_FHDR_END>
//*************************************************************************

//-------------------------------------------------------------------------
// Include(s)
//-------------------------------------------------------------------------

#include <Library/BaseLib.h>
#include <Uefi/UefiBaseType.h>

//-------------------------------------------------------------------------
// Variable and External Declaration(s)
//-------------------------------------------------------------------------
// Variable Declaration(s)


//<AMI_PHDR_START>
//----------------------------------------------------------------------------
//
// Procedure:   BiosInfoPeiEntryPoint
//
// Description: This function is the entry point for this PEI.
//
// Input:       FfsHeader   - Pointer to the FFS file header
//              PeiServices - Pointer to the PEI services table
//
// Output:      EFI_SUCCESS
//
//----------------------------------------------------------------------------
//<AMI_PHDR_END>

EFI_STATUS
EFIAPI
BiosInfoPeiEntryPoint(
    IN        EFI_PEI_FILE_HANDLE   FileHandle,
    IN CONST  EFI_PEI_SERVICES      **PeiServices
)
{
    return EFI_SUCCESS;
}