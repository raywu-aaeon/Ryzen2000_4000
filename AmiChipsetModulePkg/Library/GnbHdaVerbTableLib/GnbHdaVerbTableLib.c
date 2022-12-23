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

/** @file GnbHdaVerbTableLib.c
    This file contains code for North bridge HDA Verb Table Override  
    function

*/

// Module specific Includes
#include "Efi.h"
#include "Token.h"
#include <AmiLib.h>
#include <GnbElinks.h>
#include <Library/GnbHdaVerbTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>

#include <AmiCspLib.h>

#if GNB_HDA_VERBTABLE
OEM_HDA_VERB_TABLE_CONTENT


/**** PORTING REQUIRED ****
    Please port mAzaliaVerbTable per your HW/SW/Chipset design
*/
GNB_CODEC_VERB_TABLE_LIST mAzaliaVerbTable[] = {
    OEM_HDA_VERB_TABLE
    // End of the Verb table
    { (UINT32) 0xFFFFFFFF, (UINT64)0x0FFFFFFFFul}
};

VOID*
GnbHdaVerbTableOverride(
)
{

    return  &mAzaliaVerbTable;
}
#endif //GNB_HDA_VERBTABLE

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
