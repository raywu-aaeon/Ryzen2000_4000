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

/** @file CrbSetup.c
    Chipset Reference Board Setup Routines

**/

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------

#include <AmiLib.h>
#include <AmiDxeLib.h>
#include <Setup.h>
#include <Protocol/PciIo.h>
#include <Protocol/DevicePath.h>
#include <Protocol/PciRootBridgeIo.h>

#if CRB_AMD_PCIE_CONTROL_SUPPORT  
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>

#include <Hob.h>
#include <CrbPcie/CrbPcie.h>
#include <CrbPcie/CrbPcieSetup.h>
#endif

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

// GUID Definition(s)

// Protocol Definition(s)

// External Declaration(s)

// Function Definition(s)

//---------------------------------------------------------------------------

#if CRB_AMD_PCIE_CONTROL_SUPPORT  
UINT16  sDeviceEnabled[] = { 
        STRING_TOKEN(STR_DEVICE0_ENABLED),
        STRING_TOKEN(STR_DEVICE1_ENABLED),
        STRING_TOKEN(STR_DEVICE2_ENABLED),
        STRING_TOKEN(STR_DEVICE3_ENABLED),
        STRING_TOKEN(STR_DEVICE4_ENABLED),
        STRING_TOKEN(STR_DEVICE5_ENABLED),
        STRING_TOKEN(STR_DEVICE6_ENABLED),
        STRING_TOKEN(STR_DEVICE7_ENABLED),
        };


static EFI_GUID gAmdPcieDevcieSetupDataGuid = AMD_PCIE_DEVICE_VARIABLE_GUID; 
static EFI_GUID gAmdPcieinfoHobGuid = AMD_PCIE_INFO_HOB_GUID; 

UINTN
EFIAPI
UnicodeValueToString (
  IN OUT CHAR16  *Buffer,
  IN UINTN       Flags,
  IN INT64       Value,
  IN UINTN       Width
  );

#endif //    #if CRB_AMD_PCIE_CONTROL_SUPPORT  

/**
    Initializes Demo Board Setup String.

    @param HiiHandle Handle to HII database
    @param Class Indicates the setup class

    @retval VOID
**/

VOID InitCrbStrings (
    IN EFI_HII_HANDLE   HiiHandle,
    IN UINT16           Class )
{
    EFI_STATUS          Status = EFI_SUCCESS;

    if (Class == ADVANCED_FORM_SET_CLASS) {
#if CRB_AMD_PCIE_CONTROL_SUPPORT        
    EFI_GUID                        HobListGuid = HOB_LIST_GUID;
    AMD_PCIE_DEVICE_HOB             *PcieInfoHob;
    CHAR16                          *StrBuffer = NULL;
    CHAR16                          *String=NULL;
    CHAR16                          DeviceNumber[4];
    CHAR16                          FunctionNumber[4];
    UINTN                           Index;
    UINT8                           PcieDeviceCount;
    
    Status = pBS->AllocatePool(EfiBootServicesData,
                               sizeof (CHAR16) * 0x30,
                               (VOID*) &StrBuffer);                  
    
    PcieInfoHob=(AMD_PCIE_DEVICE_HOB*)GetEfiConfigurationTable(pST,&HobListGuid);
    if(PcieInfoHob == NULL) Status=EFI_UNSUPPORTED;
    else Status=FindNextHobByGuid(&gAmdPcieinfoHobGuid,(VOID**)&PcieInfoHob);

    PcieDeviceCount = PcieInfoHob->AmdPcieDeviceCount;
    DEBUG ((DEBUG_INFO|DEBUG_PLATFORM, " Setup PcieDeviceCount = %x\n",PcieDeviceCount));
    
    Status = pRS->SetVariable (
                L"AmdPcieDeviceCount",
                &gAmdPcieDevcieSetupDataGuid,
                EFI_VARIABLE_BOOTSERVICE_ACCESS,
                sizeof(UINT8),
                &PcieDeviceCount
                );
             
     for (Index = 0;Index < PcieInfoHob->AmdPcieDeviceCount; Index++){
    	 
    	    ZeroMem (StrBuffer,  sizeof (CHAR16) * 0x30);
            StrCpy(StrBuffer , L"Device ");
            UnicodeValueToString (DeviceNumber,0, PcieInfoHob->AmdPcieDeviceList[Index].DeviceNumber, 0);
            StrCat(StrBuffer ,DeviceNumber);
            StrCat(StrBuffer , L" Fun ");
            UnicodeValueToString (FunctionNumber,0, PcieInfoHob->AmdPcieDeviceList[Index].FunctionNumber, 0);
            StrCat(StrBuffer , FunctionNumber);
            InitString(HiiHandle, sDeviceEnabled[Index], L"%s", StrBuffer);
     }     
#endif //  #if CRB_AMD_PCIE_CONTROL_SUPPORT         

    }
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
