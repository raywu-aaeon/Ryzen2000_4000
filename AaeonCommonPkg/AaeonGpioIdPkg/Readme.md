Table of content
1. [AAEON DXE LIBRARY](#AAEON-DXE-LIBRARY)
2. [FILES NOTE](#FILES-NOTE)
3. [DEPENDENCIES](#DEPENDENCIES)
4. [PROJECT PORTING NOTE](#PROJECT-PORTING-NOTE)
5. [MODULE IMPROVEMENT NOTE](#MODULE-IMPROVEMENT-NOTE)

AAEON GPIO ID
================================

## Goal

* It's goal is to make BOARD ID, PANEL ID, OEM ID functional with minimal porting.

## Use Case

* Use one BIOS to support multiple SKUs of project by hardware BOARD ID.
   * Base on BOARD ID setup item to show/hide setup items.
* Use one BIOS to support multiple panels by hardware PANEL ID.
   * Base on PANEL ID to set default panel type.
* Use one BIOS to support multiple SKUs of ODM project by hardware OEM ID.
   * Base on OEM ID to support OEM feature.
* Use software GPIO ID to change BIOS configuration by software AP like AMI BCP or SCE.

## This module

* Support 3 types of GPIO ID includes BOARD ID, PANEL ID and OEM ID.
* Support hardware GPIO ID preservation for BIOS flash and CMOS battery loss.
* Support software GPIO ID.
* For porting -
   * Support hook function for programing hardware GPIO ID relate function and reset system.
   * Support hardware GPIO ID programing by TOKEN such as chip type and GPIO number.
   * Support hardware GPIO ID calculation and save the result to setup variable.
   * Support dynamic setup menu programing by GPIO ID setup variable.

FILES NOTE
================================

## .sdl
* AaeonGpioIdPkg.sdl - Main configurations to this module.

## .mak
* AaeonGpioIdDxe.mak - Link the hook function from ELINK "AAEON_GPIO_ID_INIT_FUNCTION"

## .c
* AaeonGpioIdDxe.c - Initial all hardware GPIO ID and save the calculation result to setup variable.
* AaeonGpioIdLoadDefaults.c - Restore setup variable from AaeonHwId when load setup default.

## .inf
* AaeonGpioIdDxe.inf - INF file for project with SIO chip
* AaeonNonSioGpioIdDxe.inf - INF file for project without SIO chip

DEPENDENCIES
================================

* gEfiSmbusHcProtocolGuid - SmBus access library

PROJECT PORTING NOTE
================================

## General

* Enable master TOKEN "AAEON_GPIO_ID_SUPPORT".
* Program hardware BOARD ID, PANEL ID and OEM ID by following steps:
   * Enable TOKEN "AAEON_HW_BOARD_ID_SUPPORT" for support Board ID function.
   * Refer the Readme.md of library "AaeonCommonLib" to set TOKEN "BOARD_ID_CHIP_TYPE" for the source chip of Board ID GPIO. 
   * Set TOKEN "BOARD_ID_NUM" by the bit number of Board ID.
      * Ex. 3 means Board ID include 3 bits BoardId_0/BoardId_1/BoardId_2.
   * Set TOKEN "BOARD_ID_GPIO" by the GPIO table of Board ID which contain the GPIO number Board ID.
      * Ex. {50, 52, 54} means BoardId_0 is GPIO50, BoardId_1 is GPIO52 and BoardId_2 is GPIO54.
   * Get the Board ID by setup item "AAEON Hardware BOARD ID"
   * Use the same procedure to program PANEL ID and OEM ID.
* Software GPIO ID is a setup item which should be programed by software AP only.

## (Optional if needed) Hardware GPIO ID hook function.

* Add hardware GPIO ID hook function to the ELINK "AAEON_GPIO_ID_INIT_FUNCTION".
* There is a sample code for hardware Board ID initialization as below:

```c
    BOOLEAN AaeonBoardIdDxeInit(AAEON_SETUP_DATA *AaeonSetupData, AAEON_HW_ID *AaeonHwIdData, BOOLEAN *AaeonSetupUpdateRequire, BOOLEAN *   AaeonHwIdUpdateRequire)
    {
        BOOLEAN             ResetRequire = FALSE;
        EFI_STATUS          Status = EFI_SUCCESS;
        EFI_GUID            SetupGuid = SETUP_GUID;
        SETUP_DATA          SetupData;
        UINTN               VariableSize = sizeof(SetupData);
        UINT32              Attribute = 0;
        
        DEBUG((DEBUG_INFO, "AaeonBoardIdDxeInit Start\n"));
    
        Status = pRS->GetVariable( L"Setup", &SetupGuid, &Attribute, &VariableSize, &SetupData);
        if(EFI_ERROR(Status)){
            ASSERT_EFI_ERROR(Status);
        }
    
        if(*AaeonSetupUpdateRequire == 1)
        {
            BoardIdInit(AaeonSetupData->BoardId, &SetupData);
    
            Status = pRS->SetVariable( L"Setup", &SetupGuid, Attribute, VariableSize, &SetupData);  
            if(EFI_ERROR(Status)){
                ASSERT_EFI_ERROR(Status);
            }
    
            ResetRequire = TRUE;
        }
    
        DEBUG((DEBUG_INFO, "AaeonBoardIdDxeInit End\n"));
    
        return ResetRequire;
    }
```

   * Input parameter AaeonSetupData - Setup variable for GPIO ID.
   * Input parameter AaeonHwIdData - Persistent variable for GPIO ID which won't be clear after BIOS flash or load default.
   * Input parameter AaeonSetupUpdateRequire - It will be TRUE when AaeonSetupData is different as AaeonHwIdData, System could be cleared CMOS.
   * Input parameter AaeonHwIdUpdateRequire - It will be TRUE when AaeonHwIdData is different as physical GPIO value, System GPIO ID could be changed.
   * Output parameter ResetRequire - System will reset in end of function "AaeonGpioIdDxeInit" when it is TRUE.

MODULE IMPROVEMENT NOTE
================================

## TODO: Support GPIO ID initialization in PEI phase (Before Memory Initialization).