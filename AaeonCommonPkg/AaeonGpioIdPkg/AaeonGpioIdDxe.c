//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------
#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>

#include <token.h>
#include <AmiDxeLib.h> // Optional. should use Mde Library instead.
#include <Setup.h> // Optional. should use Mde Library instead.
#include <AaeonCommonLib.h>

#include <Protocol/AmiSio.h>
#include <AmiGenericSio.h>

#include <AaeonGpioIdFunctions.h>

// Produced Protocols

// Consumed Protocols

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)
typedef BOOLEAN (AAEON_GPIO_ID_INIT_HOOK)(AAEON_SETUP_DATA *AaeonSetupData, AAEON_HW_ID *AaeonHwIdData, BOOLEAN *AaeonSetupUpdateRequire, BOOLEAN *AaeonHwIdUpdateRequire);

extern AAEON_GPIO_ID_INIT_HOOK AAEON_GPIO_ID_INIT_FUNCTION EndOfAaeonGpioIdInitFunctions;
AAEON_GPIO_ID_INIT_HOOK *AaeonGpioIdInitFun[] = { AAEON_GPIO_ID_INIT_FUNCTION NULL };

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

//----------------------------------------------------------------------------
//
// Procedure:   GpioIdInit
//
// Description: This function is use for initial GPIO ID.
//
// Input:       AaeonSetupData - Setup variable use for save GPIO ID
//              AaeonHwIdData - A variable which is consist of GPIO ID
//              AaeonSetupUpdateRequire - Assert to request AaeonSetupData variable update 
//              AaeonHwIdUpdateRequire - Assert to request AaeonHwIdData variable update
//              
// Output:      ResetRequire - system reset requirement
//
//----------------------------------------------------------------------------
BOOLEAN HwGpioIdInit(AAEON_SETUP_DATA *AaeonSetupData, AAEON_HW_ID *AaeonHwIdData, BOOLEAN *AaeonSetupUpdateRequire, BOOLEAN *AaeonHwIdUpdateRequire)
{
    BOOLEAN		ResetRequire = FALSE;

#if defined(AAEON_HW_BOARD_ID_SUPPORT) && (AAEON_HW_BOARD_ID_SUPPORT == 1)
	{
		UINT8 BoardId_GPIO[BOARD_ID_NUM] = BOARD_ID_GPIO;
		UINT8 GpioId = 0, index;

		//Calculate Board ID by GPIO value
		for(index = 0; index < BOARD_ID_NUM; index++)
			GpioId += AaeonGetGpio(BOARD_ID_CHIP_TYPE, BoardId_GPIO[index]) << index;

        // If Variable "AaeonHwId" does not exist, update it with GPIO ID and reset.
        // Variable "AaeonHwId" is preserved except FPT or off-line flash.
 		if (AaeonHwIdData->HwBoardId != GpioId) {
            AaeonHwIdData->HwBoardId = GpioId;
            *AaeonHwIdUpdateRequire = TRUE;
            ResetRequire = TRUE;
 		}

        // Sync Variable "AaeonHwId" to setup if need, but no need to reset. Used to affect BIOS setup behavior.
        if (AaeonSetupData->BoardId != AaeonHwIdData->HwBoardId) {
            AaeonSetupData->BoardId = AaeonHwIdData->HwBoardId;
            *AaeonSetupUpdateRequire = TRUE;
        }   
	}				
#endif //AAEON_BOARD_ID_SUPPORT

#if defined(AAEON_HW_PANEL_ID_SUPPORT) && (AAEON_HW_PANEL_ID_SUPPORT == 1)
	{
		UINT8 PanelID_GPIO[PANEL_ID_NUM] = PANEL_ID_GPIO;
		UINT8 GpioId = 0, index;

        // If Variable "AaeonHwId" does not exist, update it with GPIO ID and reset.
        // Variable "AaeonHwId" is preserved except FPT or off-line flash.
		for(index = 0; index < PANEL_ID_NUM; index++)
			GpioId += AaeonGetGpio(PANEL_ID_CHIP_TYPE, PanelID_GPIO[index]) << index;

        // If Variable "AaeonHwId" does not exist, update it with GPIO ID and reset.
 		if (AaeonHwIdData->HwPanelId != GpioId) {
            AaeonHwIdData->HwPanelId = GpioId;
            *AaeonHwIdUpdateRequire = TRUE;
            ResetRequire = TRUE;
 		}

        // Sync Variable "AaeonHwId" to setup if need, but no need to reset. Used to affect BIOS setup behavior.
        if (AaeonSetupData->PanelId != AaeonHwIdData->HwPanelId) {
            AaeonSetupData->PanelId = AaeonHwIdData->HwPanelId;
            *AaeonSetupUpdateRequire = TRUE;
        }   
	}				
#endif //AAEON_PANEL_ID_SUPPORT 	

#if defined(AAEON_HW_OEM_ID_SUPPORT) && (AAEON_HW_OEM_ID_SUPPORT == 1)
	{
		UINT8 OemID_GPIO[OEM_ID_NUM] = OEM_ID_GPIO;
		UINT8 GpioId = 0, index;

		//Calculate OEM ID by GPIO value
		for(index = 0; index < OEM_ID_NUM; index++)
			GpioId += AaeonGetGpio(OEM_ID_CHIP_TYPE, OemID_GPIO[index]) << index;

        // If Variable "AaeonHwId" does not exist, update it with GPIO ID and reset.
        // Variable "AaeonHwId" is preserved except FPT or off-line flash.
 		if (AaeonHwIdData->HwOemId != GpioId) {
            AaeonHwIdData->HwOemId = GpioId;
            *AaeonHwIdUpdateRequire = TRUE;
            ResetRequire = TRUE;
 		}

        // Sync Variable "AaeonHwId" to setup if need, but no need to reset. Used to affect BIOS setup behavior.
        if (AaeonSetupData->OemId != AaeonHwIdData->HwOemId) {
            AaeonSetupData->OemId = AaeonHwIdData->HwOemId;
            *AaeonSetupUpdateRequire = TRUE;
        }   
	}	 	
#endif //AAEON_OEM_ID_SUPPORT 	 	

    return ResetRequire;
}
//----------------------------------------------------------------------------
//
// Procedure:   AaeonGpioIdDxeInit
//
// Description: This function is the entry point for AAEON GPIO ID 
//				initialization in DXE phase.
//
// Input:       ImageHandle - Image handle
//              SystemTable - Pointer to the system table
//
// Output:      EFI_SUCCESS
//
//----------------------------------------------------------------------------
EFI_STATUS
EFIAPI
AaeonGpioIdDxeInit (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
	EFI_STATUS 			Status = EFI_SUCCESS;
    EFI_GUID			AaeonSetupGuid = AAEON_VAR_GUID;
    EFI_GUID            AaeonHwIdGuid = AAEON_VAR_GUID;
    AAEON_SETUP_DATA	AaeonSetupData;
    AAEON_HW_ID	        *AaeonHwIdData;
    UINTN				i, AaeonSetupVariableSize = sizeof(AaeonSetupData), AaeonHwIdVariableSize = sizeof(AAEON_HW_ID);
	BOOLEAN			AaeonSetupUpdateRequire = FALSE, AaeonHwIdUpdateRequire = FALSE, ResetRequire = FALSE, SystemReset = FALSE, AaeonHwIdNotFound = FALSE;
    UINT32				SetupAttribute = 0, HwIdAttribute = 0; 

	InitAmiLib(ImageHandle, SystemTable);

	DEBUG((DEBUG_INFO, "AaeonGpioIdDxeInit Start\n"));

	Status = pRS->GetVariable( L"AaeonSetup", &AaeonSetupGuid, &SetupAttribute, &AaeonSetupVariableSize, &AaeonSetupData );
	if (EFI_ERROR(Status)) return Status;

    AaeonHwIdData = AllocateZeroPool (AaeonHwIdVariableSize);

	Status = pRS->GetVariable( L"AaeonHwId", &AaeonHwIdGuid, &HwIdAttribute, &AaeonHwIdVariableSize, AaeonHwIdData);
    if (Status == EFI_NOT_FOUND) {
        // AaeonHwId variable does not exist so assign variable attribute.
        HwIdAttribute = EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE;
		AaeonHwIdNotFound = TRUE;
    }

    //Initial H/W GPIO ID
    ResetRequire = HwGpioIdInit(&AaeonSetupData, AaeonHwIdData, &AaeonSetupUpdateRequire, &AaeonHwIdUpdateRequire);
    SystemReset |= ResetRequire;

    //Execute all AaeonGpioIdInitFun with GPIO ID 
	for(i = 0; AaeonGpioIdInitFun[i] != NULL; i++)
	{
	    ResetRequire = AaeonGpioIdInitFun[i](&AaeonSetupData, AaeonHwIdData, &AaeonSetupUpdateRequire, &AaeonHwIdUpdateRequire);

	    SystemReset |= ResetRequire;
	}			

    if(AaeonSetupUpdateRequire){
		Status = pRS->SetVariable( L"AaeonSetup", &AaeonSetupGuid, SetupAttribute, AaeonSetupVariableSize, &AaeonSetupData);
		if (EFI_ERROR(Status)) {
        	DEBUG((DEBUG_ERROR, "SetVariable AaeonSetup failed, status %r\n", Status));
            return Status;  
		}
    }

	if(AaeonHwIdUpdateRequire || AaeonHwIdNotFound){
		Status = pRS->SetVariable( L"AaeonHwId", &AaeonHwIdGuid, HwIdAttribute, AaeonHwIdVariableSize, AaeonHwIdData);
		if (EFI_ERROR(Status)) {
        	DEBUG((DEBUG_ERROR, "SetVariable AaeonHwId failed, status %r\n", Status));
            return Status;  
		}
    }

    FreePool (AaeonHwIdData);

	if(SystemReset)
	{
		//Reset system
		IoWrite8(0x80, 0xDD);  	//Report Debug code
      	DEBUG((DEBUG_ERROR, "System Reset requested!\n"));
		IoWrite8(0xCF9, 0x06); 	//System reset
        // Create a CPU dead loop here to make sure CPU doens't run unexpected code.
		while (1);
	}

    DEBUG((DEBUG_INFO, "AaeonGpioIdDxeInit End\n"));

    return Status;
}

