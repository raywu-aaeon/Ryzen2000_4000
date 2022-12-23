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

/** @file PspSetup.c
    Psp Setup Routines

**/

#include <AmiDxeLib.h>
#include <Setup.h>
#include <AmdPspDirectory.h>
#include <Library/BaseLib.h>
#include <CpuCspLib.h>
#include <PciHostBridge.h>
/*
// PSP RV L1 directory - Fixed region
PSP_DIRECTORY_ENTRY FirmwareVersionL1[] = {
{SMU_OFFCHIP_FW, 0, 0},                 // Type 0x08
{PSP_FW_BOOT_LOADER, 0, 0},             // Type 0x01
{AGESA_BOOT_LOADER_0, 0, 0},            // Type 0x30
{PSP_DIR_LV2, 0, 0}                     // Type 0x40
};

UINTN FirmwareVersionCountL1 = sizeof(FirmwareVersionL1) / sizeof(PSP_DIRECTORY_ENTRY);

// PSP RV L2 directory - Updatable region
PSP_DIRECTORY_ENTRY FirmwareVersionL2[] = {
{PSP_FW_BOOT_LOADER, 0, 0},             // Type 0x01
{PSP_FW_TRUSTED_OS, 0, 0},              // Type 0x02
{SMU_OFFCHIP_FW, 0, 0},                 // Type 0x08
{AGESA_BOOT_LOADER_0, 0, 0}             // Type 0x30
};

UINTN FirmwareVersionCountL2 = sizeof(FirmwareVersionL2) / sizeof(PSP_DIRECTORY_ENTRY);

#if (SOLUTION_TYPE == 1)
// PSP BR directory
PSP_DIRECTORY_ENTRY FirmwareVersionF15[] = {
{PSP_FW_BOOT_LOADER, 0, 0},             // Type 0x01
{PSP_FW_TRUSTED_OS, 0, 0}               // Type 0x02
};

UINTN FirmwareVersionCountF15 = sizeof(FirmwareVersionF15) / sizeof(PSP_DIRECTORY_ENTRY);
#endif

BOOLEAN Layer2Support = FALSE;
*/
/**
    Returns base address of Family 17h PSP Entries

    @param
    @param

    @retval 
**/
/*
EFI_STATUS
GetF17PspEntryBase()
{
    VOID    *RomPtr;
    UINTN   i;
    UINTN   j;
    
    switch(GetCpuRawId()){
        case AMI_F17_RV_RAW_ID:
            RomPtr = (VOID*) PSP_L1_DIRECTORY_ADDRESS_RV;
            FirmwareVersionCountL1--; 
            break;
#if (SOLUTION_TYPE == 1)
        case AMI_F17_SM_RAW_ID:
            RomPtr = (VOID*) PSP_L1_DIRECTORY_ADDRESS_SM;
            Layer2Support = TRUE;
            break;
#endif
    }
    
    if (((PSP_DIRECTORY_HEADER*)RomPtr)->PspCookie != PSP_DIRECTORY_HEADER_SIGNATURE)
        return EFI_NOT_FOUND;
    
    for (i = 0; i < FirmwareVersionCountL1; i++)
    {
        for (j = 0; j < ((PSP_DIRECTORY*)RomPtr)->Header.TotalEntries; j++)
        {
            if (((PSP_DIRECTORY*)RomPtr)->PspEntry[j].Type == FirmwareVersionL1[i].Type)
            {
                FirmwareVersionL1[i].Location = ((PSP_DIRECTORY*)RomPtr)->PspEntry[j].Location;
                break;
            }
        }
    }
    
    if(!Layer2Support) return EFI_SUCCESS;

    RomPtr = (VOID*) FirmwareVersionL1[3].Location; // Type 40 for Sm point to next psp dir
    
    for (i = 0; i < FirmwareVersionCountL2; i++)
    {
        for (j = 0; j < ((PSP_DIRECTORY*)RomPtr)->Header.TotalEntries; j++)
        {
            if (((PSP_DIRECTORY*)RomPtr)->PspEntry[j].Type == FirmwareVersionL2[i].Type)
            {
                FirmwareVersionL2[i].Location = ((PSP_DIRECTORY*)RomPtr)->PspEntry[j].Location;
                break;
            }
        }
    }

    return  EFI_SUCCESS;
}
*/

//#if (SOLUTION_TYPE == 1)
/**
    Returns base address of Family15 PSP Entries

    @param
    @param

    @retval 
**/
/*
EFI_STATUS
GetF15PspEntryBase()
{
    VOID    *RomPtr;
    UINTN   i;
    UINTN   j;

    RomPtr = (VOID*) PSP_FIXED_FV_ADDRESS_BR;
    if (((PSP_DIRECTORY_HEADER*)RomPtr)->PspCookie != PSP_DIRECTORY_HEADER_SIGNATURE)
        return EFI_NOT_FOUND;
    
    for (i = 0; i < FirmwareVersionCountF15; i++)
    {
        for (j = 0; j < ((PSP_DIRECTORY*)RomPtr)->Header.TotalEntries; j++)
        {
            if (((PSP_DIRECTORY*)RomPtr)->PspEntry[j].Type == FirmwareVersionF15[i].Type)
            {
                FirmwareVersionF15[i].Location = ((PSP_DIRECTORY*)RomPtr)->PspEntry[j].Location;
                break;
            }
        }
    }
    return  EFI_SUCCESS;
}
*/
//#endif

/**
    Initializes PSP FW Version String.

    @param HiiHandle Handle to HII database
    @param Class Indicates the setup class

    @retval VOID
**/
/*
VOID InitPspStrings (
    IN EFI_HII_HANDLE   HiiHandle,
    IN UINT16           Class )
{
    EFI_STATUS                          Status = EFI_SUCCESS;
    UINT8                               *p;
#if (SOLUTION_TYPE == 1)
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL     *PciRootBridgeIo;
    UINTN                               PciAddress;
    UINT32                              Buffer;
#endif

    if (Class == ADVANCED_FORM_SET_CLASS) {
        if (!IsFamily15h())
        {
            Status = GetF17PspEntryBase();
            if (Status != EFI_SUCCESS)
                return;

    // PSP directory Level 1 Fixed region
            if(GetCpuRawId() == AMI_F17_SM_RAW_ID)
                p = (UINT8 *)(FirmwareVersionL1[0].Location + 0x60); // SM SMU FW Version
            else
                p = (UINT8 *)(FirmwareVersionL1[0].Location + 0x04); // RV SMU FW Version
            InitString(HiiHandle, STRING_TOKEN(STR_SMU_FW_VER_VALUE_L1), L"%d.%d.%d", *(p + 2), *(p + 1), *p);

            p = (UINT8 *)(FirmwareVersionL1[1].Location + 0x60); // PSP Boot Loader Version
            InitString(HiiHandle, STRING_TOKEN(STR_PSP_BOT_VER_VALUE_L1), L"%x.%x.%x.%x", *(p + 3), *(p + 2), *(p + 1), *p);

            p = (UINT8 *)(FirmwareVersionL1[2].Location + 0x60); // ABL Version
            InitString(HiiHandle, STRING_TOKEN(STR_ABL_VER_VALUE_L1), L"%02x%02x%02x%02x", *(p + 3), *(p + 2), *(p + 1), *p);

            p = (UINT8 *)(FirmwareVersionL1[2].Location + 0xA0); // APCB Version
            InitString(HiiHandle, STRING_TOKEN(STR_APCB_VER_VALUE_L1), L"%02x%02x", *(p + 1), *p);

            p = (UINT8 *)(FirmwareVersionL1[2].Location + 0xA4); // APOB Version
            InitString(HiiHandle, STRING_TOKEN(STR_APOB_VER_VALUE_L1), L"%02x%02x", *(p + 1), *p);

            p = (UINT8 *)(FirmwareVersionL1[2].Location + 0xA8); // APPB Version
            InitString(HiiHandle, STRING_TOKEN(STR_APPB_VER_VALUE_L1), L"%02x%02x", *(p + 1), *p);
            
            if(!Layer2Support) return;
			
   // PSP directory Level 2 Updatable region
            p = (UINT8 *)(FirmwareVersionL2[0].Location + 0x60); // PSP BootLoader Version
            InitString(HiiHandle, STRING_TOKEN(STR_PSP_BOT_VER_VALUE_L2), L"%x.%x.%x.%x", *(p + 3), *(p + 2), *(p + 1), *p);

            p = (UINT8 *)(FirmwareVersionL2[1].Location + 0x60); // PSP Secure OS Version
            InitString(HiiHandle, STRING_TOKEN(STR_PSP_SEC_OS_VER_VALUE), L"%x.%x.%x.%x", *(p + 3), *(p + 2), *(p +1 ), *p);

            p = (UINT8 *)(FirmwareVersionL2[2].Location + 0x60); // SMU FW Version
            InitString(HiiHandle, STRING_TOKEN(STR_SMU_FW_VER_VALUE_L2), L"%d.%d.%d", *(p + 2), *(p + 1), *p);

            p = (UINT8 *)(FirmwareVersionL2[3].Location + 0x60); // ABL Version
            InitString(HiiHandle, STRING_TOKEN(STR_ABL_VER_VALUE_L2), L"%02x%02x%02x%02x", *(p + 3), *(p + 2), *(p + 1), *p);

            p = (UINT8 *)(FirmwareVersionL2[3].Location + 0xA0); // APCB Version
            InitString(HiiHandle, STRING_TOKEN(STR_APCB_VER_VALUE_L2), L"%02x%02x", *(p + 1), *p);

            p = (UINT8 *)(FirmwareVersionL2[3].Location + 0xA4); // APOB Version
            InitString(HiiHandle, STRING_TOKEN(STR_APOB_VER_VALUE_L2), L"%02x%02x", *(p + 1), *p);

            p = (UINT8 *)(FirmwareVersionL2[3].Location + 0xA8); // APPB Version
            InitString(HiiHandle, STRING_TOKEN(STR_APPB_VER_VALUE_L2), L"%02x%02x", *(p + 1), *p);

        }
        else
        {
#if (SOLUTION_TYPE == 1)
            Status = GetF15PspEntryBase();
            if (Status != EFI_SUCCESS)
                return;

            p = (UINT8 *)(FirmwareVersionF15[0].Location + 0x60); // PSP BootLoader Version
            InitString(HiiHandle, STRING_TOKEN(STR_PSP_BOT_VER_VALUE_L1), L"%x.%x.%x.%x", *(p+3), *(p+2), *(p+1), *p);

            p = (UINT8 *)(FirmwareVersionF15[1].Location + 0x60); // PSP Secure OS Version
            InitString(HiiHandle, STRING_TOKEN(STR_PSP_SEC_OS_VER_VALUE), L"%x.%x.%x.%x", *(p+3), *(p+2), *(p+1), *p);

            Status = pBS->LocateProtocol (&gEfiPciRootBridgeIoProtocolGuid, NULL, &PciRootBridgeIo);
            if (Status != EFI_SUCCESS)
                return;

            PciAddress = EFI_PCI_CFG_ADDRESS (0, 0, 0, 0xB8); // SMU Index Address
            Buffer = 0x1001FF80; // SMU firmware version
            PciRootBridgeIo->Pci.Write (PciRootBridgeIo, EfiBootScriptWidthUint32, PciAddress, 1, (VOID*)&Buffer);

            PciAddress = EFI_PCI_CFG_ADDRESS (0, 0, 0, 0xBC); // SMU Index Data
            PciRootBridgeIo->Pci.Read (PciRootBridgeIo, EfiBootScriptWidthUint32, PciAddress, 1, &Buffer);

            InitString(HiiHandle, STRING_TOKEN(STR_SMU_FW_VER_VALUE), L"%d.%d.%d.%d", (UINT8)(Buffer >> 24), (UINT8)(Buffer >> 16), (UINT8)(Buffer >> 8), (UINT8)Buffer);
#endif
        }
        return;
    }
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
