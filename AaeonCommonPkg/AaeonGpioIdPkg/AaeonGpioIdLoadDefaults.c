//----------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------
#include <AmiDxeLib.h>
#include <Library/AmiSdlLib.h>
#include <Setup.h>
#include <token.h>
#include <AaeonCommonLib.h>

extern BOOLEAN gBrowserCallbackEnabled;
extern BOOLEAN gEnableDrvNotification;

//----------------------------------------------------------------------------
//
// Procedure:   AaeonGpioIdDefaultInit
//
// Description: This function is restore setup variable AaeonSetupData from 
//              persistent variable AaeonHwIdData
//
// Input:       AaeonHwIdData - Persistent variable of GPIO ID
//              
// Output:      N/A
//
// Notes:       
//----------------------------------------------------------------------------
EFI_STATUS
EFIAPI
AaeonGpioIdDefaultInit ( AAEON_HW_ID *AaeonHwIdData )
{
	EFI_STATUS 			Status = EFI_SUCCESS;
	EFI_GUID			AaeonSetupGuid = AAEON_VAR_GUID;
	UINTN				AaeonSetupVariableSize = sizeof(AAEON_SETUP_DATA);
	AAEON_SETUP_DATA	AaeonSetupData;

    Status = HiiLibGetBrowserData(&AaeonSetupVariableSize, &AaeonSetupData, &AaeonSetupGuid, L"AaeonSetup");

    if(Status == EFI_SUCCESS)
    {
#if defined(AAEON_HW_BOARD_ID_SUPPORT) && (AAEON_HW_BOARD_ID_SUPPORT == 1)
        // Sync Variable "AaeonHwId" to setup if need, but no need to reset. Used to affect BIOS setup behavior.
        if (AaeonSetupData.BoardId != AaeonHwIdData->HwBoardId) {
            AaeonSetupData.BoardId = AaeonHwIdData->HwBoardId;
            Status = HiiLibSetBrowserData(AaeonSetupVariableSize, &AaeonSetupData, &AaeonSetupGuid, L"AaeonSetup");
        }
#endif //AAEON_BOARD_ID_SUPPORT

#if defined(AAEON_HW_PANEL_ID_SUPPORT) && (AAEON_HW_PANEL_ID_SUPPORT == 1)
        // Sync Variable "AaeonHwId" to setup if need, but no need to reset. Used to affect BIOS setup behavior.
        if (AaeonSetupData.PanelId != AaeonHwIdData->HwPanelId) {
            AaeonSetupData.PanelId = AaeonHwIdData->HwPanelId;
            Status = HiiLibSetBrowserData(AaeonSetupVariableSize, &AaeonSetupData, &AaeonSetupGuid, L"AaeonSetup");
        }
#endif //AAEON_PANEL_ID_SUPPORT     

#if defined(AAEON_HW_OEM_ID_SUPPORT) && (AAEON_HW_OEM_ID_SUPPORT == 1)
        // Sync Variable "AaeonHwId" to setup if need, but no need to reset. Used to affect BIOS setup behavior.
        if (AaeonSetupData.OemId != AaeonHwIdData->HwOemId) {
            AaeonSetupData.OemId = AaeonHwIdData->HwOemId;
            Status = HiiLibSetBrowserData(AaeonSetupVariableSize, &AaeonSetupData, &AaeonSetupGuid, L"AaeonSetup");
        }   
#endif //AAEON_OEM_ID_SUPPORT       
    }

	return Status;
}
//----------------------------------------------------------------------------
//
// Procedure:   AaeonGpioIdLoadDefaults
//
// Description: This function is restore all GPIO ID setup item when load BIOS 
//              setup default
//
// Input:       *defaults - VOID
//              data - To avoid draw MessageBox when data is passed as NULL 
//              
// Output:      N/A
//
// Notes:       
//----------------------------------------------------------------------------
VOID AaeonGpioIdLoadDefaults (VOID *defaults, UINTN data )
{
	EFI_STATUS          Status = EFI_SUCCESS;
    EFI_GUID            AaeonHwIdGuid = AAEON_VAR_GUID;
    AAEON_HW_ID         AaeonHwIdData;
    UINTN               AaeonHwIdVariableSize = sizeof(AAEON_HW_ID);
    UINT32              HwIdAttribute = 0; 

//---------------------		
	gBrowserCallbackEnabled = TRUE;
	gEnableDrvNotification = TRUE;

    Status = pRS->GetVariable( L"AaeonHwId", &AaeonHwIdGuid, &HwIdAttribute, &AaeonHwIdVariableSize, &AaeonHwIdData);

    Status = AaeonGpioIdDefaultInit(&AaeonHwIdData);

    gBrowserCallbackEnabled = FALSE;
	gEnableDrvNotification = FALSE;	
}
