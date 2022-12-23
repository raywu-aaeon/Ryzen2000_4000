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

/** @file CrbLib.c
    This file contains Chipset Reference Board related code that
    is needed for both PEI & DXE stage. 
    To avoid code duplication this file is made as a library and
    linked both in PEI & DXE CRB FFS.

    @note  MAKE SURE NO PEI OR DXE SPECIFIC CODE IS NEEDED

**/

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------

#include <Uefi.h>
#include <Library/DebugLib.h>
#include <Ppi/ReadOnlyVariable2.h>

#include <Token.h>
#include <AmiCspLib.h>
#include <Setup.h>
#include <Library/SbPolicy.h>
#include <Protocol/PIDEController.h>

// Produced Protocols

// Consumed Protocols
#include <Protocol/PciIo.h>

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

// All routines in this file will be added into CSP library.

UINT32 CrbHdaVerbTbl0[] = {
    //Realtek HD Audio Codec : ALC288
    //PCI PnP ID : PCI\VEN_1022&DEV_780D&SUBSYS_C7511022
    //HDA Codec PnP ID : HDAUDIO\FUNC_01&VEN_10EC&DEV_0286&SUBSYS_1022C751
    //The number of verb command block : 15
    //    NID 0x12 : 0xB7A60150
    //    NID 0x13 : 0x40000000
    //    NID 0x14 : 0x90170110
    //    NID 0x17 : 0x411111F0
    //    NID 0x18 : 0x04A11040
    //    NID 0x19 : 0x411111F0
    //    NID 0x1A : 0x411111F0
    //    NID 0x1D : 0x4067A52D
    //    NID 0x1E : 0x04451130
    //    NID 0x21 : 0x04211020

    //===== HDA Codec Subsystem ID Verb-table =====
    0x00172050, 0x001721C9, 0x00172222, 0x00172310,    // HDA Codec Subsystem ID  : 0x1022C950
    0x0017FF00, 0x0017FF00, 0x0017FF00, 0x0017FF00,    // Widget node 0x01 :
    0x01171C00, 0x01171D00, 0x01171E33, 0x01171F40,    // Pin widget 0x11 - S/PDIF-OUT2
    0x01271CF0, 0x01271D11, 0x01271E11, 0x01271F41,    // Pin widget 0x12 - DMIC
    0x01471C10, 0x01471D40, 0x01471E01, 0x01471F01,    // Pin widget 0x14 - FRONT (Port-D)
    0x01571C14, 0x01571D10, 0x01571E01, 0x01571F01,    // Pin widget 0x15 - SURR (Port-A)
    0x01671C11, 0x01671D60, 0x01671E01, 0x01671F01,    // Pin widget 0x16 - CEN/LFE (Port-G)
    0x01771CF0, 0x01771D11, 0x01771E11, 0x01771F41,    // Pin widget 0x17 - SIDESURR (Port-H)
    0x01871C40, 0x01871D90, 0x01871EA1, 0x01871F01,    // Pin widget 0x18 - MIC1 (Port-B)
    0x01971C50, 0x01971D10, 0x01971EA1, 0x01971F02,    // Pin widget 0x19 - MIC2 (Port-F)
    0x01A71C60, 0x01A71D30, 0x01A71E81, 0x01A71F01,    // Pin widget 0x1A - LINE1 (Port-C)
    0x01B71C20, 0x01B71D10, 0x01B71E21, 0x01B71F02,    // Pin widget 0x1B - LINE2 (Port-E)
    0x01C71CF0, 0x01C71D11, 0x01C71E11, 0x01C71F41,    // Pin widget 0x1C - CD-IN
    0x01D71C01, 0x01D71DF6, 0x01D71E26, 0x01D71F40,    // Pin widget 0x1D - BEEP-IN
    0x01E71C30, 0x01E71D11, 0x01E71E45, 0x01E71F01,    // Pin widget 0x1E - S/PDIF-OUT1
    0x01F71CF0, 0x01F71D11, 0x01F71E11, 0x01F71F41,    // Pin widget 0x1F - S/PDIF-IN
    0x02050007, 0x02040180, 0x02050001, 0x0204C7AA,    // Widget node 0x20 :
    0x02050015, 0x0204026A, 0x02050008, 0x02040071,    // Widget node 0x20 - 1 :
     
     0xffffffff   //End of Verb Table flag
};

#if CMOS_MANAGER_SUPPORT
/**
    @param PeiServices 
    @param ReadVariablePpi 
    @retval BOOLEAN TRUE or FALSE
**/
BOOLEAN OemIsResetConfigMode(
    IN EFI_PEI_SERVICES **PeiServices, 
    IN CONST EFI_PEI_READ_ONLY_VARIABLE2_PPI *ReadVariablePpi
  )
{


#ifdef CLEAR_NVRAM_IF_CMOS_BAD
  #if CLEAR_NVRAM_IF_CMOS_BAD
    /*
    IoWrite8(CMOS_ADDR_PORT, CMOS_DIAGNOSTIC_STATUS_REGISTER);
    if (IoRead8(CMOS_DATA_PORT) & (BIT06 + BIT07)) return TRUE; 
    */
	IoWrite8(CMOS_BANK1_INDEX, CMOS_BAD_CHECK_ADDRESS);
    if (IoRead8(CMOS_BANK1_DATA) ==0x55)  return TRUE;
  #endif
#endif
    return FALSE;
}
#endif //CMOS_MANAGER_SUPPORT

#if CMOS_MANAGER_SUPPORT
/**
    This function determines if the system should boot with the default configuration.
    This function is called by NVRAM code. 
    If boot with default configuration is detected, default values for NVRAM variables are used.

    @param PeiServices pointer to a pointer to the PEI Services Table.
    @param ReadVariablePpi pointer to EFI_PEI_READ_ONLY_VARIABLE2_PPI PPI. The pointer can be used to
        read and enumerate existing NVRAM variables.

               
    @retval TRUE Boot with default configuration is detected
    @retval FALSE Boot with default configuration is not detected

    @note  This routine is called very early, prior to SBPEI and NBPEI.
**/

BOOLEAN OemIsDefaultConfigMode(
    IN EFI_PEI_SERVICES **PeiServices, 
    IN CONST EFI_PEI_READ_ONLY_VARIABLE2_PPI *ReadVariablePpi
){

#ifdef LOAD_DEFAULTS_IF_CMOS_BAD
  #if LOAD_DEFAULTS_IF_CMOS_BAD
    // IoWrite8(CMOS_ADDR_PORT, CMOS_DIAGNOSTIC_STATUS_REGISTER);
    // if (IoRead8(CMOS_DATA_PORT) & (BIT06 + BIT07)) return TRUE; 
    IoWrite8(CMOS_BANK1_INDEX, CMOS_BAD_CHECK_ADDRESS);
    if (IoRead8(CMOS_BANK1_DATA) ==0x55)  return TRUE;
  #endif
#endif 

    return FALSE;
}
#endif // CMOS_MANAGER_SUPPORT

//CRB Board for Sourth bridge.
//---------------------------------------------------------------------------
/**
        
    @param Controller 
    @param ControllerInfo 
    @param SetupData 
         
        IN OUT CONTROLLER_INFO  *ControllerInfo
    @retval VOID
**/
VOID
OEM_AcousticManagement(
    IN EFI_HANDLE           Controller,
    IN OUT CONTROLLER_INFO  *ControllerInfo,
    IN SETUP_DATA           *SetupData
  )
{
}

/**
    This function could override the Sb setup data

    @param Services 
    @param SbSetupData 
    @param SetupData 
    @param Pei 

        IN OUT SB_SETUP_DATA    *SbSetupData
    @retval VOID

    @note  This routine is called very early, prior to SBPEI and NBPEI.
**/
VOID
CrbSbSetupOverride (
    IN VOID                 *Services,
    IN OUT SB_SETUP_DATA    *SbSetupData,
    IN SETUP_DATA           *SetupData,
    IN BOOLEAN              Pei
 )
{
    //porting here
}

/**
    CRBRuntimeResetOverride

    @param ResetType 

    @retval EFI_STATUS EFI_SUCCESS

**/
EFI_STATUS
CRBRuntimeResetOverride (
  IN  EFI_RESET_TYPE  ResetType
 )
{
      //CRB board changes
      EFI_STATUS                      Status=EFI_SUCCESS;

      IoWrite8(0x80, ResetType);
      return (Status); 
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
