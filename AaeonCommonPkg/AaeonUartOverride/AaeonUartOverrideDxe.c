//----------------------------------------------------------------------
//Include Files
//----------------------------------------------------------------------
#include <AmiDxeLib.h>
#include <SioSetup.h>
#include <GenericSio.h>
#include <Library/AmiSdlLib.h>
#include <Setup.h>
#include <token.h>
#include <Library/S3BootScriptLib.h>
// Produced Protocols

// Consumed Protocols

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)
#define Enabled 1
#define Disabled 0

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
/**
  Saves an I/O port value to the boot script.

  This internal worker function saves an I/O port value in the S3 script
  to be replayed on S3 resume. 

  If the saving process fails, then ASSERT().

  @param  Width         The width of I/O port.
  @param  Port          The I/O port to write.
  @param  Buffer        The buffer containing value.

**/
VOID
InternalSaveIoWriteValueToBootScript (
  IN S3_BOOT_SCRIPT_LIB_WIDTH  Width,
  IN UINTN                  Port,
  IN VOID                   *Buffer
  )
{
  RETURN_STATUS                Status;
  
  Status = S3BootScriptSaveIoWrite (
             Width,
             Port,
             1,
             Buffer
             );
  ASSERT (Status == RETURN_SUCCESS);
}
  
/**
  Saves an 8-bit I/O port value to the boot script.

  This internal worker function saves an 8-bit I/O port value in the S3 script
  to be replayed on S3 resume. 

  If the saving process fails, then ASSERT().

  @param  Port          The I/O port to write.
  @param  Value         The value saved to boot script.

  @return Value.

**/
UINT8
InternalSaveIoWrite8ValueToBootScript (
  IN UINTN              Port,
  IN UINT8              Value
  )
{
  InternalSaveIoWriteValueToBootScript (S3BootScriptWidthUint8, Port, &Value);

  return Value;
}

/**
  Reads an 8-bit I/O port and saves the value in the S3 script to be replayed
  on S3 resume.

  Reads the 8-bit I/O port specified by Port. The 8-bit read value is returned.
  This function must guarantee that all I/O read and write operations are
  serialized.

  If 8-bit I/O port operations are not supported, then ASSERT().

  @param  Port          The I/O port to read.

  @return The value read.

**/
UINT8
EFIAPI
S3IoRead8 (
  IN UINTN              Port
  )
{
  return InternalSaveIoWrite8ValueToBootScript (Port, IoRead8 (Port));
}

/**
  Writes an 8-bit I/O port and saves the value in the S3 script to be replayed
  on S3 resume.

  Writes the 8-bit I/O port specified by Port with the value specified by Value
  and returns Value. This function must guarantee that all I/O read and write
  operations are serialized.

  If 8-bit I/O port operations are not supported, then ASSERT().

  @param  Port          The I/O port to write.
  @param  Value         The value to write to the I/O port.

  @return The value written the I/O port.

**/
UINT8
EFIAPI
S3IoWrite8 (
  IN UINTN              Port,
  IN UINT8              Value
  )
{
  return InternalSaveIoWrite8ValueToBootScript (Port, IoWrite8 (Port, Value));
}
/**
    This Function provides generic access to the SIO registers
    

    @param SioChipSdlInfo Pointer to the SIO SDL Information
    @param Write Action Selector
    @param Val Pointer to the data byte/buffer 

    @retval VOID
    
    @note This function assumes SIO is in Config Mode and LD has been selected
**/
VOID EFIAPI S3SioRegister(AMI_SDL_SIO_CHIP_INFO *SioChipSdlInfo, BOOLEAN Write, UINT8 Reg, UINT8 *Val)
{
    S3IoWrite8(SioChipSdlInfo->SioIndex, Reg);

    if(Write) S3IoWrite8(SioChipSdlInfo->SioData, *Val);
    else *Val = S3IoRead8(SioChipSdlInfo->SioData);    
}

//==================================================================================
/**
    Routine to transit Sio in/from Config Mode.

    @param Sio Pointer to the SIO Private Data
    @param Enter Action Selector
    
    @retval VOID

**/  
VOID EFIAPI S3SioCfgMode(AMI_SDL_SIO_CHIP_INFO *SioChipSdlInfo, BOOLEAN Enter)
{
    UINTN               i;
    SIO_SCRIPT_LST2     *ScriptLst;
//---------------------------------
    if(Enter)ScriptLst = (SIO_SCRIPT_LST2*)&SioChipSdlInfo->EnterCfgMode[0];
    else ScriptLst = (SIO_SCRIPT_LST2*)&SioChipSdlInfo->EnterCfgMode[0];

    if(ScriptLst == NULL) return;

    for (i = 0; i < ScriptLst->InstrCount; i++)
    {
       SPIO_SCRIPT      *Instr = (SPIO_SCRIPT*) &ScriptLst->Instruction[0];
       SPIO_SCRIPT      *cmd = &Instr[i];
       UINT16           reg;   
    //------------------------
       if(cmd->IdxDat) reg = SioChipSdlInfo->SioIndex;
       else reg = SioChipSdlInfo->SioData;
       
       if (cmd->WrRd) S3IoWrite8(reg, cmd->Value);
    }
    return;
}


VOID EFIAPI S3ClearDevResources(AMI_SDL_SIO_CHIP_INFO *SioChipSdlInfo)
{
    UINT8   Val = 0;
//------------------------
    S3SioRegister(SioChipSdlInfo, TRUE, SioChipSdlInfo->Base1HiReg, &Val);
    S3SioRegister(SioChipSdlInfo, TRUE, SioChipSdlInfo->Base1LoReg, &Val);
    S3SioRegister(SioChipSdlInfo, TRUE, SioChipSdlInfo->Irq1Reg, &Val);
}
//----------------------------------------------------------------------------
//
// Procedure:   UartDisabled
//
// Description: This function is disabling target UART by setting LDEVICE 
//              parameter Implemented/HasSetup/Flags
//
// Input:       AMI_SDL_SIO_CHIP_INFO - SIO info for target UART source chip
//              AMI_SDL_LOGICAL_DEV_INFO - logic device info for target UART
//              
// Output:      None
//
// Notes:       
//----------------------------------------------------------------------------
VOID EFIAPI UartDisabled(AMI_SDL_SIO_CHIP_INFO *SioChipSdlInfo, AMI_SDL_LOGICAL_DEV_INFO *LdSdlInfo)
{
    //Set target UART to not present
    //Enter config mode
    S3SioCfgMode(SioChipSdlInfo, TRUE);
    //Select LDN
    S3SioRegister(SioChipSdlInfo, TRUE, SioChipSdlInfo->DevSelReg, &LdSdlInfo->Ldn);
    //Deactivate target device
    S3SioRegister(SioChipSdlInfo, TRUE, SioChipSdlInfo->ActivateReg, &SioChipSdlInfo->DeactivateVal);
    //Clear Resource
    S3ClearDevResources(SioChipSdlInfo);
    //Exit config mode
    S3SioCfgMode(SioChipSdlInfo, FALSE);
    
    //Set target device as no implemented
    LdSdlInfo->Implemented = FALSE;
    //Set target device as no setup item
    LdSdlInfo->HasSetup = FALSE;
    //Set target device as no resource
    LdSdlInfo->Flags = SIO_NO_RES;    
}
//----------------------------------------------------------------------------
//
// Procedure:   AaeonUartOverride
//
// Description: This function is checking setup item and disabling the target 
//              UART
//
// Input:       AMI_SDL_SIO_CHIP_INFO - SIO info for target UART source chip
//              AMI_SDL_LOGICAL_DEV_INFO - logic device info for target UART
//              
// Output:      None
//
// Notes:       
//----------------------------------------------------------------------------
VOID EFIAPI AaeonUartOverride(AMI_SDL_SIO_CHIP_INFO *SioChipSdlInfo, AMI_SDL_LOGICAL_DEV_INFO *LdSdlInfo)
{
    EFI_STATUS                  Status = EFI_NOT_FOUND;
    EFI_GUID                    SetupGuid = SETUP_GUID;
    SETUP_DATA                  SetupData;
    UINTN                       VariableSize = sizeof(SETUP_DATA);
    UINT32                      Attribute = 0;    
    UINT8                       UartOverrideIndex;

    Status = pRS->GetVariable( L"Setup", &SetupGuid, &Attribute, &VariableSize, &SetupData);

    for(UartOverrideIndex = 0; UartOverrideIndex < MAX_UART_OVERRIDE_ITEM; UartOverrideIndex++)
    {
        if( SetupData.AaeonUartOverrideSupport[UartOverrideIndex] == Enabled &&
            SetupData.AaeonUartOverrideUid[UartOverrideIndex] == LdSdlInfo->Uid)
        {
            if(SetupData.AaeonUartPresent[UartOverrideIndex] == Disabled)
            {    
                UartDisabled(SioChipSdlInfo, LdSdlInfo);
            }
        }
    }    
}
//----------------------------------------------------------------------------
//
// Procedure:   AaeonUartOverrideInit
//
// Description: This function is getting all UART info and setting the LEDVICE
//              parameter for disabling UART
//
// Input:       EFI_HANDLE
//              EFI_SYSTEM_TABLE
//              
// Output:      EFI_STATUS
//
// Notes:       
//----------------------------------------------------------------------------
EFI_STATUS
EFIAPI
AaeonUartOverrideInit (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
    EFI_STATUS                  Status = EFI_NOT_FOUND;
    UINTN                       i, j;
    AMI_SDL_SIO_CHIP_INFO       *SioChipSdlInfo;

    InitAmiLib(ImageHandle, SystemTable);

    Status = AmiSdlInitBoardInfo();
    SioChipSdlInfo=&gSdlSioData->SioDev[0];

    TRACE((-1,"AaeonUartOverrideInit: Get %d SIO Chip.\n", gSdlSioData->SioCount));
    for(j=0; j<gSdlSioData->SioCount; j++)
    {
        AMI_SDL_LOGICAL_DEV_INFO    *LdSdlInfo;
        TRACE((-1,"AaeonUartOverrideInit: Get %d LD on SIO Chip %d.\n", SioChipSdlInfo->LogicalDevCount, gSdlSioData->SioCount));
        //--------------------------------
        for(i=0; i<SioChipSdlInfo->LogicalDevCount; i++)
        {
            LdSdlInfo = &SioChipSdlInfo->LogicalDev[i];
            if(LdSdlInfo->Type == dsUART)
            {
                TRACE((-1,"SIO_LD[%d]; AslName[%s]; Implemented = %d; FLAGS = %X\n", i, LdSdlInfo->AslName, LdSdlInfo->Implemented, LdSdlInfo->Flags));

                AaeonUartOverride(SioChipSdlInfo, LdSdlInfo);
            }
        }
        //Advance to the next SIO CHIP in Multiple Sio case.
        SioChipSdlInfo = (AMI_SDL_SIO_CHIP_INFO*)(LdSdlInfo + 1);
    }

    return Status;
}