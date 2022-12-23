//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

/** @file NbPeiRamBootLib.c
    This file contains the hook for PeiRamBoot Package.

**/

#include "Token.h"
#include <AmiLib.h>
#include "Library/NbCspLib.h"
#include <AmiCspLib.h>
#include <AmiDxeLib.h>
#include "Library/NbPolicy.h"

/**
    Check if PeiFvCopyTo Ram is needed or not.

    @param PeiServices 

        PeiFvCopyToRam
    @retval FALSE Warm boot, so skip PeiFvCopyToRam
    @retval TRUE Cold boot, so PeiFvCopyToRam is needed

    @note  None

**/
/* Use for E-Link. But E-link head in PEI Ram Boot has removed.
BOOLEAN
CheckPeiFvCopyToRam (
IN EFI_PEI_SERVICES **PeiServices
)
{
    UINT8           Value8;
    BOOLEAN         PeiFvCopyToRam = TRUE;
    NB_SETUP_DATA   NbSetupData;

    // Read warm boot status from CMOS
    IoWrite8 (0x72, PcdGet8(PcdCmosAgesaSpecified));
    Value8 = IoRead8 (0x73);
    if ((Value8 & BIT0) != 0)
    {
        GetNbSetupData(PeiServices, &NbSetupData, TRUE);
        if ((NbSetupData.MemClr == 0) && (NbSetupData.MemClrFlag == 1))
            PeiFvCopyToRam = FALSE; // Warm boot, so skip PeiFvCopyToRam
        else
            PeiFvCopyToRam = TRUE; // Cannot promise if memory is safe so PeiFvCopyToRam is needed
    }
    else
        PeiFvCopyToRam = TRUE; // Cold boot, so PeiFvCopyToRam is needed
    return PeiFvCopyToRam;
}
*/
//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
