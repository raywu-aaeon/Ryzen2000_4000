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

/** @file AmiSmmLib.c
    South Bridge SMM Library implementation

*/

#include <Library/AmiSmmLib.h>
#include <Library/IoLib.h>
#include <Library/PciLib.h>
#include <Guid/Rtc.h>
#include <Sb.h>


//---------------------------------------------------------------------------
#if SMM_SUPPORT
//---------------------------------------------------------------------------

/**
    This hook is called in the very SMI entry and exit.
    Save/Restore chipset data if needed.

    @param Save - TRUE = Save / FALSE = Restore

    @retval EFI_SUCCESS
**/

EFI_STATUS SbSmmSaveRestoreStates (
    IN BOOLEAN                      Save )
{
    UINT32  static dStoreCF8;
    UINT8   static bStoreCMOS,bStoreExtCMOS;
    UINT8   static StoreIoCD6, StoreIoCD8, StoreIoC00;
    UINT32  static dStoreIoHcNbSmnIndex2B8;

    //### RTC_IO_INDEX                0x70    // RTC I/O Index Port
    //### PIRQ_IO_INDEX               0xC00   // PCI Interrupt I/O Index Port
    //### CM_INDEX_PORT               0xC50
    //### GPM_PORT                    0xC52
    //### BIOSRAM_INDEX_PORT          0xCD4
    //### PM2_IO_INDEX                0xCD0
    //### PM_IO_INDEX                 0xCD6
    //### ALINK_ACCESS_INDEX          0xCD8
    //### ALINK_ACCESS_DATA           ALINK_ACCESS_INDEX + 4

    if (Save) {
        dStoreCF8 = IoRead32(0xcf8);    // Store CF8 (PCI index)
        bStoreCMOS = IoRead8(CMOS_ADDR_PORT);     // Save CMOS
        bStoreExtCMOS = IoRead8(CMOS_IO_EXT_INDEX);  // Store extended CMOS index
        // SB700
        StoreIoCD6 = IoRead8(PM_IO_INDEX);
        StoreIoCD8 = IoRead8(ALINK_ACCESS_INDEX);

        StoreIoC00 = IoRead8(0xC00);

        dStoreIoHcNbSmnIndex2B8 = PciRead32(PCI_LIB_ADDRESS(0, 0, 0, 0xB8)); // IOHC_NB_SMN_INDEX_2_BIOS

    } else {
    	PciWrite32(PCI_LIB_ADDRESS(0, 0, 0, 0xB8), dStoreIoHcNbSmnIndex2B8); // IOHC_NB_SMN_INDEX_2_BIOS

        IoWrite32(0xcf8, dStoreCF8);    // Restore 0xCF8 (PCI index)
        IoWrite8(CMOS_ADDR_PORT, bStoreCMOS);     // Restore 0x70(CMOS index)
        IoWrite8(CMOS_IO_EXT_INDEX, bStoreExtCMOS);  // Restore 0x72(EXT-CMOS index)
        // SB700
        IoWrite8(PM_IO_INDEX, StoreIoCD6);
        IoWrite8(ALINK_ACCESS_INDEX, StoreIoCD8);

        IoWrite8(0xC00, StoreIoC00);

    }
    return EFI_SUCCESS;
}

//---------------------------------------------------------------------------
#endif  // END OF SMM Related Porting Hooks
//---------------------------------------------------------------------------

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
