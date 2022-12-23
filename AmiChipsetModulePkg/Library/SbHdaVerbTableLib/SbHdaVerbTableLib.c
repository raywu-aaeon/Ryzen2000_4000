//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

/** @file SbHdaVerbTableLib.c
    This file contains code for South bridge HDA Verb Table Override  
    function

*/

// Module specific Includes
#include "Efi.h"
#include "Token.h"
#include <AmiLib.h>
#include <SbElinks.h>
#include <Library/SbHdaVerbTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>

#include <AmiCspLib.h>

OEM_HDA_VERB_TABLE_CONTENT

/**** PORTING REQUIRED ****
    Please port mAzaliaVerbTable per your HW/SW/Chipset design
*/
SB_HDA_VERB_TABLE mAzaliaVerbTable[] = {
    OEM_HDA_VERB_TABLE
    {
      // End of the Verb table
      {-1}, (UINT32*)-1
    },
};

UINTN debCodecTblSize = sizeof(mAzaliaVerbTable);

/**
    This function is to initialize the pointer to the override
    verb table

    @param **VerbTable    Pointer to the override verb table
    @param *VerbTableNum  The number of the override verb table
    @param Pei            If this function is called by PEI driver

    @retval EFI_SUCCESS   Override the verb table
    @retval Others        Do not override the verb table

**/
EFI_STATUS
SbHdaVerbTableOverride (
    IN OUT SB_HDA_VERB_TABLE    **VerbTable,
    IN OUT UINT8                *VerbTableNum,
    IN BOOLEAN                  Pei
    )
{
    *VerbTable    = mAzaliaVerbTable;
    *VerbTableNum = sizeof (mAzaliaVerbTable) / sizeof (SB_HDA_VERB_TABLE) - 1;
    return EFI_SUCCESS;
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
