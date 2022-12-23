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

/** @file NbGeneric.c
    This file contains generic NB code that is common between
    various components such as NB PEI, DXE etc

**/


// Module specific Includes
#include "Efi.h"
#include "Token.h"
#include <AmiLib.h>
#include "Library/NbCspLib.h"
#include <AmiCspLib.h>
#include <AmiDxeLib.h>
#include "Library/NbPolicy.h"
#include <Protocol/PciRootBridgeIo.h>
#include <AmiCpuPkg/Cpu/Include/CpuCspLib.h>
// Produced Protocols

// GUID Definitions

// Portable Constants
EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *gPciRootBridgeIo;

// Function Prototypes

// Function Definition

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
#if		CSM_SUPPORT
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
// Start OF CSM Related Porting Hooks
//----------------------------------------------------------------------------

//
// The following data structure specifies the PCI device/function number of the root
// bridge(s). Number of entries in this table defined by NUMBER_OF_ROOTBRIDGES.
// This table is a missing link between RootBridgeIo and PciIo, which allows to update
// BusNumXlat table with actual bus numbers.
// Each entry in the table is a pair of RootBridge UID (UINT32), provided in RootBridge
// device path, and PCI Dev/Func number (UINT8) that can be used to access Root Bridge on
// PCI bus.
//
ROOT_BRIDGE_MAPPING_ENTRY	RbMap[ROOT_BRIDGE_COUNT] = {
//			RB ID			Device function number
			{ 0,			0xC0}
	};
UINTN						RbCount = ROOT_BRIDGE_COUNT;

EFI_STATUS
NbPamWriteBootScript(
    IN EFI_S3_SAVE_STATE_PROTOCOL    *BootScriptSave
)
{
	return EFI_SUCCESS;
}

//----------------------------------------------------------------------------
#endif          // END OF CSM Related Porting Hooks
//----------------------------------------------------------------------------

/**
    AMD PciConfig read function....Reads Normal and Extended PCI space

        
    @param Address 
    @param ExtAccess use Extended PCI space access if TRUE

         
    @retval UINT32 The value read from the indicated Address.

    @note  
  Supports only 32 bit read only to be used for S3 Feature

**/

UINT32
NbPciConfigRead(
  IN    UINT32 Address,
  IN    BOOLEAN ExtAccess
)
{
    UINT32  PciAddress = ((UINT32)1 << 31) +
             (((EFI_PCI_CONFIGURATION_ADDRESS*) &Address)->Bus << 16) +
             (((EFI_PCI_CONFIGURATION_ADDRESS*) &Address)->Device << 11) +
             (((EFI_PCI_CONFIGURATION_ADDRESS*) &Address)->Function << 8) +
             (((EFI_PCI_CONFIGURATION_ADDRESS*) &Address)->Register);

    PciAddress = PciAddress & 0xFFFFFFFC;   // Dword Align

    if (ExtAccess)  // If extended config Access requested then add the extended config address  bit (24 to 27)
        PciAddress |= 0x1000000;

    IoWrite32(0xCF8, PciAddress);
    return IoRead32(0xCFC);         //Return the read value
}

/**
    Write a value into the PCI register indicated

        
    @param Address 
    @param Value 
    @param ExtAccess 

         
    @retval VOID

**/

VOID
NbPciConfigWrite(
  IN    UINT32  Address,
  IN    UINT32  Value,
  IN    BOOLEAN ExtAccess
)
{
    UINT32  PciAddress = ((UINT32)1 << 31) +
             (((EFI_PCI_CONFIGURATION_ADDRESS*) &Address)->Bus << 16) +
             (((EFI_PCI_CONFIGURATION_ADDRESS*) &Address)->Device << 11) +
             (((EFI_PCI_CONFIGURATION_ADDRESS*) &Address)->Function << 8) +
             (((EFI_PCI_CONFIGURATION_ADDRESS*) &Address)->Register);

    PciAddress &= 0xFFFFFFFC;

    // If extended config Access requested then add the extended config address  bit (24 to 27)
    if (ExtAccess)
        PciAddress |= 0x1000000;

    IoWrite32 (0xCF8, PciAddress);  // Select the register to write
    IoWrite32 (0xCFC, Value);   // Write the Value
}

/**
    Check if the system is Dual Channel or not

    @param MemoryChannelType  0:Symmetric, 1:Interleave, 2:Single

    @retval TRUE  It is Dual Channel
    @retval FALSE It is not Dual Channel
**/

BOOLEAN
NbIsDualChannel (
  IN    UINT8   MemoryChannelType 
)
{
/**** PORTING REQUIRED ****
    Please use registers or other way to check if 
    the system is Dual Channel or not
**** PORTING REQUIRED ****/
    
    UINT64                  MsrRegister = 0;
    UINT32                  Address32 = 0;
    UINT32                  Data32 = 0;
    UINT8                   EnableChannels = 0;

    MsrRegister = ReadMsr(0xC001001F);
    if (!(MsrRegister & Shl64(1, 46)))  // if bit 46 EnableCf8ExtCfg is not then set it for accessing D18F4x15C
    {
        WriteMsr(0xC001001F, MsrRegister | Shl64(1, 46));
        MsrRegister &= ~Shl64(1, 46);
    }
      
    // D18F1x10C 
    Address32 = (UINT32)AMD_PCI_CFG_ADDRESS_S3 (0, 0x18, 1, 0x10C); // Funciton 1, DCT Configuration Select
    Data32 = NbPciConfigRead (Address32, TRUE);
    Data32 = Data32 & ~(0x7);   // [DctCfgSel] = DCT0
    NbPciConfigWrite (Address32, Data32, TRUE);
        
    // Read D18F2x94_dct[0]
    Address32 = (UINT32)AMD_PCI_CFG_ADDRESS_S3 (0, 0x18, AMD_K8_DDR_FUNC,
                         AMD_K8_nF2_CFG_UPR); 
    Data32 = NbPciConfigRead (Address32, FALSE);
    Data32 &= 0x004000;
    if (Data32 == 0x0)
        EnableChannels++;   // Channel A is enabled.
        
    // D18F1x10C
    Address32 = (UINT32)AMD_PCI_CFG_ADDRESS_S3 (0, 0x18, 1, 0x10C); // Funciton 1, DCT Configuration Select
    Data32 = NbPciConfigRead (Address32, TRUE);
    Data32 |= 0x1 ; // [DctCfgSel] = DCT1
    NbPciConfigWrite (Address32, Data32, TRUE);
        
    // Read D18F2x94_dct[3]
    Address32 = (UINT32)AMD_PCI_CFG_ADDRESS_S3 (0, 0x18, AMD_K8_DDR_FUNC,
                         AMD_K8_nF2_CFG_UPR); 
    Data32 = NbPciConfigRead (Address32, FALSE);
    Data32 &= 0x004000;    
    if (Data32 == 0x0)
        EnableChannels++;   // Channel B is enabled.
        
    WriteMsr (0xC001001F, MsrRegister); // Restore the original value to NB_CFG
        
    if (EnableChannels == 2)
        return TRUE;
    else
        return FALSE;
}

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
