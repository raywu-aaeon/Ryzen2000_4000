//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  <F81866DxeInit.c>
//
// Description: 1. Port SIO DXE initial table and routine for GenericSio.c
//              2. Define SIO bootscriptable table
//
//<AMI_FHDR_END>
//**********************************************************************
//----------------------------------------------------------------------
//Include Files
//----------------------------------------------------------------------
#include <AmiDxeLib.h>
#include <Library/AmiSioDxeLib.h>
#include <AmiGenericSio.h>
#include "F81866DxeIoTable.h"
//INTERNAL_085_RayWu, ADD 2015/01/28 >>
#include <Token.h>
#include <Setup.h>
//INTERNAL_085_RayWu, ADD 2015/01/28 <<

//INTERNAL_085_RayWu, ADD 2015/01/28 >>
#if defined(F81866_SMF_SUPPORT) && (F81866_SMF_SUPPORT == 1)
extern VOID F81866SmartFunction(VOID);
extern VOID SmartFanBootScript(EFI_S3_SAVE_STATE_PROTOCOL *BootScriptProtocol);
#endif //F81866_SMF_SUPPORT == 1
//INTERNAL_085_RayWu, ADD 2015/01/28 <<

#if !defined(AAEONPOWERMODE_SUPPORT) || (AAEONPOWERMODE_SUPPORT == 0)
#define AAEON_ACLOSS_LAST_STATE  0
#define AAEON_ACLOSS_ALWAYS_ON   1
#define AAEON_ACLOSS_ALWAYS_OFF  2

#if !defined(STATEAFTERG3_MAP)
  #if defined(CRB_USE_VAR_STATEAFTERG3) && (CRB_USE_VAR_STATEAFTERG3 == 1)
    UINT8 MapToACPowerLoss[3] = STATEAFTERG3_MAP {2, 0, 1}
  #else
    UINT8 MapToACPowerLoss[3] = STATEAFTERG3_MAP {2, 1, 0}
  #endif
#endif

#endif

// F81866_ERP_Miles++ >>>>>
#if F81866_ERP_SUPPORT
EFI_STATUS F81866ErpModeCfg(VOID)
{
	EFI_GUID     SetupGuid = SETUP_GUID;
	UINTN        VariableSize = sizeof(SETUP_DATA);  
    EFI_STATUS   Status;
    SETUP_DATA   *SetupData = NULL;
	UINT8 reg8;

	TRACE((TRACE_ALWAYS, "[F81866ErpModeCfg]Enter F81866ErpModeCfg\n"));
	
	Status = GetEfiVariable(L"Setup", &SetupGuid, NULL, &VariableSize, &SetupData);

	IoWrite8(F81866_CONFIG_INDEX, F81866_CONFIG_MODE_ENTER_VALUE);
	IoWrite8(F81866_CONFIG_INDEX, F81866_CONFIG_MODE_ENTER_VALUE);
	
	IoWrite8(F81866_CONFIG_INDEX, F81866_LDN_SEL_REGISTER);
	IoWrite8(F81866_CONFIG_DATA, F81866_LDN_PME);

#if AAEONPOWERMODE_SUPPORT
	if((SetupData->F81866ErpMode != 0x00) && (SetupData->AaeonPowerMode == 0x0))
#else
	if(SetupData->F81866ErpMode != 0x00)
#endif
	{
	    if(SetupData->F81866ErpMode == 1)
	    {
	    	//Intel DSW mode
#if AAEONPOWERMODE_SUPPORT
			if(SetupData->AaeonRestoreACPowerLoss == 2)
#else
#if CRB_USE_VAR_STATEAFTERG3
       		if((SetupData->F81866RestoreACPowerLoss == 0x02) || ((SetupData->F81866RestoreACPowerLoss == 0x03) && (SetupData.StateAfterG3 == MapToACPowerLoss[AAEON_ACLOSS_ALWAYS_OFF])))
#else
    		if((SetupData->F81866RestoreACPowerLoss == 0x02) || ((SetupData->F81866RestoreACPowerLoss == 0x03) && (SetupData->LastState == MapToACPowerLoss[AAEON_ACLOSS_ALWAYS_OFF])))
#endif
#endif
		    {
		    	//Always off: Set ERP on for S5 and AC_Failure
		    	IoWrite8(F81866_CONFIG_INDEX, 0xE1);
		    	reg8 = (IoRead8(F81866_CONFIG_DATA) & 0xF0) | 0x05;
		    	IoWrite8(F81866_CONFIG_DATA, reg8); 
			} else
		    {
		    	//Always on/Last state-on: Set ERP off for AC_Failure, ERP on for S5
		    	IoWrite8(F81866_CONFIG_INDEX, 0xE1);
		    	reg8 = (IoRead8(F81866_CONFIG_DATA) & 0xF0) | 0x04;
		    	IoWrite8(F81866_CONFIG_DATA, reg8); 
			}
		} else
	    {
	    	//ERP mode
#if AAEONPOWERMODE_SUPPORT
			if(SetupData->AaeonRestoreACPowerLoss == 2)
#else
#if CRB_USE_VAR_STATEAFTERG3
       		if((SetupData->F81866RestoreACPowerLoss == 0x02) || ((SetupData->F81866RestoreACPowerLoss == 0x03) && (SetupData->StateAfterG3 == MapToACPowerLoss[AAEON_ACLOSS_ALWAYS_OFF])))
#else
    		if((SetupData->F81866RestoreACPowerLoss == 0x02) || ((SetupData->F81866RestoreACPowerLoss == 0x03) && (SetupData->LastState == MapToACPowerLoss[AAEON_ACLOSS_ALWAYS_OFF])))
#endif
#endif
		    {
		    	//Always off: Set ERP on for S5 and AC_Failure
		    	IoWrite8(F81866_CONFIG_INDEX, 0xE1);
		    	reg8 = (IoRead8(F81866_CONFIG_DATA) & 0xF0) | 0x0F;
		    	IoWrite8(F81866_CONFIG_DATA, reg8); 
			} else
		    {
		    	//Always on/Last state-on: Set ERP off for AC_Failure, ERP on for S5
		    	IoWrite8(F81866_CONFIG_INDEX, 0xE1);
		    	reg8 = (IoRead8(F81866_CONFIG_DATA) & 0xF0) | 0x0C;
		    	IoWrite8(F81866_CONFIG_DATA, reg8); 
			}
		}
		
		IoWrite8(F81866_CONFIG_INDEX, 0xEC);
#if INTEL_DEEP_SX_SUPPORT
	    if(SetupData->F81866ErpMode == 1)
	    	reg8 = (IoRead8(F81866_CONFIG_DATA) & 0x3F) | 0xC0;
	    else
	    	reg8 = IoRead8(F81866_CONFIG_DATA) & 0x3F;
//	    	reg8 = (IoRead8(F81866_CONFIG_DATA) & 0x3F) | 0x40;	    

#else
    	reg8 = IoRead8(F81866_CONFIG_DATA) & 0x3F;
#endif
    	IoWrite8(F81866_CONFIG_DATA, reg8); 

    	IoWrite8(F81866_CONFIG_INDEX, 0xE0);
		reg8 = IoRead8(F81866_CONFIG_DATA) | 0x80;
    	IoWrite8(F81866_CONFIG_DATA, reg8); 
	} else
	{
		IoWrite8(F81866_CONFIG_INDEX, 0xE0);
		reg8 = IoRead8(F81866_CONFIG_DATA) & 0x7F;
    	IoWrite8(F81866_CONFIG_DATA, reg8); 
	}

	IoWrite8(F81866_CONFIG_INDEX, F81866_CONFIG_MODE_EXIT_VALUE);

	if (SetupData) pBS->FreePool(SetupData);
	return EFI_SUCCESS;
}
#endif //F81866_ERP_SUPPORT
// F81866_ERP_Miles++ <<<<<

// <AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure: F81866_ClearDevResource
//
// Description:
//  This function will Clear SIO resource.
//
// Input:
//  SIO_DEV2* Dev
// Output:
//  NONE
//
//----------------------------------------------------------------------
// <AMI_PHDR_END>
VOID F81866_ClearDevResource(
    IN  SIO_DEV2    *Dev
)
{
    //Enter Configuration Mode.
    IoWrite8(F81866_CONFIG_INDEX, F81866_CONFIG_MODE_ENTER_VALUE);
    IoWrite8(F81866_CONFIG_INDEX, F81866_CONFIG_MODE_ENTER_VALUE);
    //Seclect device
    IoWrite8(F81866_CONFIG_INDEX, F81866_LDN_SEL_REGISTER);
    IoWrite8(F81866_CONFIG_DATA, Dev->DeviceInfo->Ldn);
    //Clear Base Address
    IoWrite8(F81866_CONFIG_INDEX, F81866_BASE1_HI_REGISTER);
    IoWrite8(F81866_CONFIG_DATA, 0);
    IoWrite8(F81866_CONFIG_INDEX, F81866_BASE1_LO_REGISTER);
    IoWrite8(F81866_CONFIG_DATA, 0);
    //Clear Interrupt
    IoWrite8(F81866_CONFIG_INDEX, F81866_IRQ1_REGISTER);
    IoWrite8(F81866_CONFIG_DATA, 0);
    //Exit Configuration Mode
    IoWrite8(F81866_CONFIG_INDEX, F81866_CONFIG_MODE_EXIT_VALUE);

    return;
}

// <AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure: F81866_FDC_Init
//
// Description:
//  This function provide each initial routine in genericsio.c
//
// Input:
// IN  AMI_BOARD_INIT_PROTOCOL      *This - AMI Board Int Protocol.
// IN  UINTN                        *Function - AMI Sdl SIO Init Routine.
// IN  OUT VOID                     *ParameterBlock - SIO Component Initialization Routine Parameters Block...
//
// Output:
//  EFI_SUCCESS - Initial step sucessfully
//  EFI_INVALID_PARAMETER - not find the initial step
//
// Modified: Nothing
//
// Referrals: None
//
// Notes:
//----------------------------------------------------------------------
// <AMI_PHDR_END>
#if F81866_FLOPPY_PORT_PRESENT
EFI_STATUS F81866_FDC_Init(
    IN AMI_BOARD_INIT_PROTOCOL      *This,
    IN UINTN                        *Function,
    IN OUT VOID                     *ParameterBlock
)
{
    //Update Standard parameter block
    AMI_BOARD_INIT_PARAMETER_BLOCK  *Args=(AMI_BOARD_INIT_PARAMETER_BLOCK*)ParameterBlock;
    SIO_INIT_STEP                   InitStep=(SIO_INIT_STEP)Args->InitStep;
    AMI_SIO_PROTOCOL                *AmiSio=(AMI_SIO_PROTOCOL*)Args->Param1;
    EFI_PCI_IO_PROTOCOL             *PciIo=(EFI_PCI_IO_PROTOCOL*)Args->Param2;

    EFI_STATUS                      Status=EFI_SUCCESS;
    SIO_DEV2                        *Dev=(SIO_DEV2*)AmiSio;
    UINT8                           rv; //FdcMode Register
    //Check if parameters passed are VALID and
    if(Args->Signature != AMI_SIO_PARAM_SIG) return EFI_INVALID_PARAMETER;

    switch (InitStep) {
    case isGetSetupData:
        //Clear Device Resource?
        if((!Dev->DeviceInfo->Implemented) || (!Dev->NvData.DevEnable)) {
            F81866_ClearDevResource(Dev);
        }
        break;

    case isPrsSelect:
        break;

    case isBeforeActivate:
#if !defined(SecDecodePkg_SUPPORT) || (SecDecodePkg_SUPPORT == 0)
        //Decode?
        if(Dev->DeviceInfo->Implemented && Dev->NvData.DevEnable) {
            AmiSioLibSetLpcDeviceDecoding(PciIo,Dev->VlData.DevBase1, Dev->DeviceInfo->Uid, Dev->DeviceInfo->Type);
        } else {
            AmiSioLibSetLpcDeviceDecoding(PciIo,0, Dev->DeviceInfo->Uid, Dev->DeviceInfo->Type);
        }
#endif
        //AMI_TODO: please check the register define and program FDC mode
        //Read FDC Mode register
        Status=AmiSio->Access(AmiSio,FALSE,FALSE,0xF0,&rv);
        ASSERT_EFI_ERROR(Status);
        if(EFI_ERROR(Status))return Status;
        if(Dev->NvData.DevMode)rv |= 0x10; //Bit00 set = FDD is Write Protect
        else rv &= (UINT8)(~0x10);
        Status=AmiSio->Access(AmiSio,TRUE,FALSE,0xF0,&rv);
        ASSERT_EFI_ERROR(Status);
        break;

    case isGetModeData: {
        //FDC Has 2 possible modes
        //Make sure Device Mode Strings are Static VAR!
        //Otherwise The string will gone after control flow leave this function
        static CHAR16 FdcModeStr1[] = L"Read Write";
        static CHAR16 FdcModeStr2[] = L"Write Protect";
        static CHAR16 FdcModeHelp[] = L"Change mode of Floppy Disk Controller. Select 'Read Write' for normal operation. Select 'Write Protect' mode for read only operation.";
        //---------------------------------------------------
        Dev->DevModeCnt=2;
        //Make room for 2 floppy modes + Help String...
        Dev->DevModeStr=MallocZ(sizeof(CHAR16*)*(Dev->DevModeCnt+1));
        if(Dev->DevModeStr==NULL) {
            Status=EFI_OUT_OF_RESOURCES;
            ASSERT_EFI_ERROR(Status);
            return Status;
        }
        Dev->DevModeStr[0]=&FdcModeStr1[0];
        Dev->DevModeStr[1]=&FdcModeStr2[0];
        Dev->DevModeStr[2]=&FdcModeHelp[0];
    }
    break;

    case isAfterActivate:
        break;

    case isAfterBootScript:
        break;

#if  AMI_SIO_MINOR_VERSION >= 6     
    case isAfterSmmBootScript:      
        break;
#endif

    default:
        Status=EFI_INVALID_PARAMETER;
    } //switch

    return Status;
}
#endif

// <AMI_PHDR_START>
//----------------------------------------------------------------------
//
// Procedure: F81866_COM_Init
//
// Description:
//  This function provide each initial routine in genericsio.c
//
// Input:
// IN  AMI_BOARD_INIT_PROTOCOL      *This - AMI Board Int Protocol.
// IN  UINTN                        *Function - AMI Sdl SIO Init Routine.
// IN  OUT VOID                     *ParameterBlock - SIO Component Initialization Routine Parameters Block...
//
// Output:
//  EFI_SUCCESS - Initial step sucessfully
//  EFI_INVALID_PARAMETER - not find the initial step
//
// Modified:  Nothing
//
// Referrals: None
//
// Notes:
//----------------------------------------------------------------------
// <AMI_PHDR_END>
//#if F81866_SERIAL_PORT1_PRESENT | F81866_SERIAL_PORT2_PRESENT
EFI_STATUS F81866_COM_Init(
    IN AMI_BOARD_INIT_PROTOCOL      *This,
    IN UINTN                        *Function,
    IN OUT VOID                     *ParameterBlock
)
{
    //Update Standard parameter block
    AMI_BOARD_INIT_PARAMETER_BLOCK  *Args=(AMI_BOARD_INIT_PARAMETER_BLOCK*)ParameterBlock;
    SIO_INIT_STEP                   InitStep=(SIO_INIT_STEP)Args->InitStep;
    AMI_SIO_PROTOCOL                *AmiSio=(AMI_SIO_PROTOCOL*)Args->Param1;
    EFI_PCI_IO_PROTOCOL             *PciIo=(EFI_PCI_IO_PROTOCOL*)Args->Param2;

    EFI_STATUS                      Status=EFI_SUCCESS;
    SIO_DEV2                        *Dev=(SIO_DEV2*)AmiSio;
//    UINT8                           rv; //ComMode Register //RayWu, REMOVE 2015/04/14
    //Check if parameters passed are VALID and
    if(Args->Signature != AMI_SIO_PARAM_SIG) return EFI_INVALID_PARAMETER;

    switch (InitStep) {
    case isGetSetupData:
        //Clear Device Resource?
        if((!Dev->DeviceInfo->Implemented) || (!Dev->NvData.DevEnable)) {
            F81866_ClearDevResource(Dev);
        }
        break;

    case isPrsSelect:
        break;

    case isBeforeActivate:
        //Only decode UART1/UART2. More others UART port is decode in PEI
        //Attention! Remove the more com ports to PEI decode.
#if !defined(SecDecodePkg_SUPPORT) || (SecDecodePkg_SUPPORT == 0)
        if(Dev->DeviceInfo->Uid < 0x02) {
            //Decode?
            if(Dev->DeviceInfo->Implemented && Dev->NvData.DevEnable) {
                AmiSioLibSetLpcDeviceDecoding(PciIo,Dev->VlData.DevBase1, Dev->DeviceInfo->Uid, Dev->DeviceInfo->Type);
            } else {
                AmiSioLibSetLpcDeviceDecoding(PciIo,0, Dev->DeviceInfo->Uid, Dev->DeviceInfo->Type);
            }
        }
#endif
//RayWu, REMOVE 2015/04/14 >>
//        //Program COM RS485/RS232 Mode Registers.
//        if(F81866_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid].AndData8 == 0xFF) {
//            rv=F81866_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid].OrData8;
//        } else {
//            Status=AmiSio->Access(AmiSio, FALSE, FALSE, F81866_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid].Reg8,&rv);
//            ASSERT_EFI_ERROR(Status);
//            rv &= F81866_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid].AndData8;
//            rv |= F81866_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid].OrData8;
//        }
//        Status=AmiSio->Access(AmiSio,TRUE,FALSE,F81866_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid].Reg8,&rv);
//        ASSERT_EFI_ERROR(Status);
//        //Program COM Clock Source Registers.
//        if(F81866_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid+6].AndData8 == 0xFF) {
//            rv=F81866_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid+6].OrData8;
//        } else {
//            Status=AmiSio->Access(AmiSio, FALSE, FALSE, F81866_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid+6].Reg8,&rv);
//            ASSERT_EFI_ERROR(Status);
//            rv &= F81866_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid+6].AndData8;
//            rv |= F81866_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid+6].OrData8;
//        }
//        Status=AmiSio->Access(AmiSio,TRUE,FALSE,F81866_DXE_COM_Mode_Init_Table[Dev->DeviceInfo->Uid+6].Reg8,&rv);
//        ASSERT_EFI_ERROR(Status);
//        //Programm Device Mode register here(if NEEDED)use AmiSioProtocol
//        //AMI_TODO: You can program device mode as follow:
//        if(Dev->DeviceInfo->Uid == 0x05) {
//            //if(Dev->DeviceInfo->Uid == 0x01)    {
//            Status=AmiSio->Access(AmiSio,FALSE,FALSE,0xF1,&rv);
//            ASSERT_EFI_ERROR(Status);
//            if(EFI_ERROR(Status))return Status;
//            //clear Bit4~3 where COM Port mode is:
//            rv &= 0xE7;
//            switch (Dev->NvData.DevMode) {
//            case 0:
//                rv |= 0x00;    //Bit4~3 = 000, Disable IR1 function
//                break;
//            case 1:
//                rv |= 0x10;    //Bit4~3 = 010, Enable IR1 function, active pulse is 1.6uS
//                break;
//            case 2:
//                rv |= 0x18;    //Bit4~3 = 011, Enable IR1 function, active pulse is 3/16 bit time
//                break;
//            default:
//                return EFI_INVALID_PARAMETER;
//            }
//            Status=AmiSio->Access(AmiSio,TRUE,FALSE,0xF1,&rv);
//            ASSERT_EFI_ERROR(Status);
//            if (Dev->NvData.DevMode > 0) {
//                //Get DSDT.. we have to update it.
//                ACPI_HDR                        *dsdt;
//                EFI_PHYSICAL_ADDRESS            a;
//
//                Status=LibGetDsdt(&a,EFI_ACPI_TABLE_VERSION_ALL);
//                if(EFI_ERROR(Status)) {
//                    SIO_TRACE((TRACE_SIO,"F81866_COM_Init: Fail to Get DSDT - returned %r\n", Status));
//                    ASSERT_EFI_ERROR(Status);
//                } else dsdt=(ACPI_HDR*)a;
//                Status=UpdateAslNameOfDevice(dsdt, Dev->DeviceInfo->AslName, "_HID", 0x1005D041);
//                ASSERT_EFI_ERROR(Status);
//                //Checksum
//                dsdt->Checksum = 0;
//                dsdt->Checksum = ChsumTbl((UINT8*)dsdt, dsdt->Length);
//            }
//        }
//RayWu, REMOVE 2015/04/14 <<
//RayWu, REMOVE 2015/04/14 >> Transfer to PEI phase
////RayWu, ADD 2014/12/05 >>
//        // All UART default as 128 byte FIFO
//        {
//        	UINT8	Value8;
//
//        	Status = AmiSio->Access(AmiSio, FALSE, FALSE, 0xF6, &Value8);
//        	Value8 |= (BIT0 + BIT1);
//        	Status = AmiSio->Access(AmiSio, TRUE, FALSE, 0xF6, &Value8);
//        }
////RayWu, ADD 2014/12/05 <<
//RayWu, REMOVE 2015/04/14 <<
//RayWu, REMOVE 2014/12/05 >>
//        //Programm Device to PCI IRQ shanre mode
//        if((Dev->DeviceInfo->Flags & SIO_SHR_IRQ1) && Dev->ResOwner) {
//            //Programm ResOwner
//            //1. Config the share bit
//            Status=AmiSio->Access((AMI_SIO_PROTOCOL *)Dev->ResOwner,FALSE,FALSE,0xF0,&rv);
//            ASSERT_EFI_ERROR(Status);
//            rv &= 0xFC;
//            rv |= 0x01; //Bit0: 1: IRQ is ahring with other device
//                        //Bit1: 0: Sharing IRQ active low level mode
//            Status=AmiSio->Access((AMI_SIO_PROTOCOL *)Dev->ResOwner,TRUE,FALSE,0xF0,&rv);
//            ASSERT_EFI_ERROR(Status);
//            //Programm Device
//            //1. Config the share bit
//            Status=AmiSio->Access(AmiSio,FALSE,FALSE,0xF0,&rv);
//            ASSERT_EFI_ERROR(Status);
//            rv &= 0xFC;
//            rv |= 0x01; //Bit0: 1: IRQ is ahring with other device
//                        //Bit1: 1: Sharing IRQ active low level mode
//            Status=AmiSio->Access(AmiSio,TRUE,FALSE,0xF0,&rv);
//            ASSERT_EFI_ERROR(Status);
//            //2. Config the IRQ resource
//            //Status=AmiSio->Access(AmiSio,FALSE,FALSE,0x70,&rv);
//            //ASSERT_EFI_ERROR(Status);
//            //rv = Dev->ResOwner->VlData.DevIrq1; //Get the IRQ from the ResOwner
//            //Status=AmiSio->Access(AmiSio,TRUE,FALSE,0x70,&rv);
//            //ASSERT_EFI_ERROR(Status);
//            //3. Update the Device Private Data
//            //Dev->VlData.DevIrq1 = Dev->ResOwner->VlData.DevIrq1;
//        }
//RayWu, REMOVE 2014/12/05 <<
        break;

    case isGetModeData:
//RayWu, REMOVE 2015/04/14 >>
//        if(Dev->DeviceInfo->Uid == 0x05) {
//            //COM6 Has 3 possible modes
//            //Make sure Device Mode Strings are Static VAR!
//            //Otherwise The string will gone after control flow leave this function
//            static CHAR16 Com6ModeStr1[] = L"Disable IR1";
//            static CHAR16 Com6ModeStr2[] = L"Enable IR1 (pulse 1.6uS)";
//            static CHAR16 Com6ModeStr3[] = L"Enable IR1 (pulse 3/16 bit time)";
//            static CHAR16 Com6ModeHelp[] = L"Change the Serial Port mode. Enable, Disable and Configure IR function.";
//            //---------------------------------------------------
//            Dev->DevModeCnt=3;
//            //Make room for 2 floppy modes + Help String...
//            Dev->DevModeStr=MallocZ(sizeof(CHAR16*)*(Dev->DevModeCnt+1));
//            if(Dev->DevModeStr==NULL) {
//                Status=EFI_OUT_OF_RESOURCES;
//                ASSERT_EFI_ERROR(Status);
//                return Status;
//            }
//            Dev->DevModeStr[0]=&Com6ModeStr1[0];
//            Dev->DevModeStr[1]=&Com6ModeStr2[0];
//            Dev->DevModeStr[2]=&Com6ModeStr3[0];
//            Dev->DevModeStr[3]=&Com6ModeHelp[0];
//        }
//RayWu, REMOVE 2015/04/14 <<
        break;

    case isAfterActivate:
        break;

    case isAfterBootScript:
        break;

#if  AMI_SIO_MINOR_VERSION >= 6     
    case isAfterSmmBootScript:      
        break;
#endif

    default:
        Status=EFI_INVALID_PARAMETER;
    }//switch
    return Status;
}
//#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
//Procedure: F81866_LPT_Init
//
//Description:
// This function provide each initial routine in genericsio.c
//
//Input:
// IN  AMI_BOARD_INIT_PROTOCOL      *This - AMI Board Int Protocol.
// IN  UINTN                        *Function - AMI Sdl SIO Init Routine.
// IN  OUT VOID                     *ParameterBlock - SIO Component Initialization Routine Parameters Block...
//
//Output:
// EFI_SUCCESS - Initial step sucessfully
// EFI_INVALID_PARAMETER - not find the initial step
//
//Modified:  Nothing
//
//Referrals: None
//
//Notes:
//----------------------------------------------------------------------
//<AMI_PHDR_END>
#if F81866_PARALLEL_PORT_PRESENT
EFI_STATUS F81866_LPT_Init(
    IN AMI_BOARD_INIT_PROTOCOL      *This,
    IN UINTN                        *Function,
    IN OUT VOID                     *ParameterBlock
)
{
    //Update Standard parameter block
    AMI_BOARD_INIT_PARAMETER_BLOCK  *Args=(AMI_BOARD_INIT_PARAMETER_BLOCK*)ParameterBlock;
    SIO_INIT_STEP                   InitStep=(SIO_INIT_STEP)Args->InitStep;
    AMI_SIO_PROTOCOL                *AmiSio=(AMI_SIO_PROTOCOL*)Args->Param1;
    EFI_PCI_IO_PROTOCOL             *PciIo=(EFI_PCI_IO_PROTOCOL*)Args->Param2;

    EFI_STATUS                      Status=EFI_SUCCESS;
    SIO_DEV2                        *Dev=(SIO_DEV2*)AmiSio;
    UINT8                           rv; //LptMode Register
    //Check if parameters passed are VALID and
    if(Args->Signature != AMI_SIO_PARAM_SIG) return EFI_INVALID_PARAMETER;

    switch (InitStep) {
    case isGetSetupData:
        //Clear Device Resource?
        if((!Dev->DeviceInfo->Implemented) || (!Dev->NvData.DevEnable)) {
            F81866_ClearDevResource(Dev);
        }
        break;

    case isPrsSelect:
        //depend on LPT Mode it may or may not use a DMA channel
        //Strcpy(&Dev->DeviceInfo->AslName[0],"LPTE");
        //EFI_DEADLOOP();
        if(Dev->NvData.DevMode >3 ) {  //7 mode
            //if(Dev->NvData.DevMode&0x02) { //4 mode
            ACPI_HDR                        *dsdt;
            EFI_PHYSICAL_ADDRESS            a;

            if(ACPI_SUPPORT) {
                //if ACPI is Supported get _PRS for Extended Parallel Port from DSDT
                //last parameter is 0-based index in F81866_DevLst[] table.
                Status=SioDxeLibGetPrsFromAml(Dev,"EPPR", 1);
            } else {
                //if ACPI is not supported use corresponded Function seting
                //"UseDma" parameter to TRUE for Extended Parallel Port
                Status=SioDxeLibSetLptPrs(Dev, TRUE);
            }
            //Get DSDT.. we have to update it.
            Status=LibGetDsdt(&a,EFI_ACPI_TABLE_VERSION_ALL);
            if(EFI_ERROR(Status)) {
                SIO_TRACE((TRACE_SIO,"F81866_LPT_Init: Fail to Get DSDT - returned %r\n", Status));
                ASSERT_EFI_ERROR(Status);
            } else dsdt=(ACPI_HDR*)a;
            Status=UpdateAslNameOfDevice(dsdt, Dev->DeviceInfo->AslName, "_HID", 0x0104D041);
            //Checksum
            dsdt->Checksum = 0;
            dsdt->Checksum = ChsumTbl((UINT8*)dsdt, dsdt->Length);
        } else {
            if(ACPI_SUPPORT) {
                //if ACPI is Supported get _PRS for Standard Parallel Port from DSDT
                //last parameter is 0-based index in WPCD376I_DevLst[] table.
                Status=SioDxeLibGetPrsFromAml(Dev,"LPPR", 1);
            } else {
                //if ACPI is not supported use corresponded Function seting
                //"UseDma" parameter to FALSE for Standard Parallel Port
                Status=SioDxeLibSetLptPrs(Dev, FALSE);
            }
        }
        ASSERT_EFI_ERROR(Status);
        break;

    case isBeforeActivate:
#if !defined(SecDecodePkg_SUPPORT) || (SecDecodePkg_SUPPORT == 0)

        //Decode?
        if(Dev->DeviceInfo->Implemented && Dev->NvData.DevEnable) {
            AmiSioLibSetLpcDeviceDecoding(PciIo,Dev->VlData.DevBase1, Dev->DeviceInfo->Uid, Dev->DeviceInfo->Type);
        } else {
            AmiSioLibSetLpcDeviceDecoding(PciIo,0, Dev->DeviceInfo->Uid, Dev->DeviceInfo->Type);
        }
#endif
        //Programm Device Mode register here(if NEEDED)use AmiSioProtocol
        //AMI_TODO: You can program device mode as follow:
        Status=AmiSio->Access(AmiSio,FALSE,FALSE,0xF0,&rv);    //LPT Configuration Reg, Read the reg value
        ASSERT_EFI_ERROR(Status);
        if(EFI_ERROR(Status))return Status;
        //Program Lpt Mode register following SIO Specification instructions.
        //Set mode:Bit2-0 set = LPT mode
        //clear lowest 3 bits where LPT mode is:
        rv&=0xF8;
        switch (Dev->NvData.DevMode) {
        case 0:
            rv|=4; //STD Printer Mode
            break;
        case 1:
            rv|=0; //SPP Mode
            break;
        case 2:
            rv|=1; //EPP-1.9 and SPP Mode
            break;
        case 3:
            rv|=5; //EPP-1.7 and SPP Mode
            break;
        case 4:
            rv|=2; //ECP Mode
            break;
        case 5:
            rv|=3; //ECP and EPP-1.9 Mode
            break;
        case 6:
            rv|=7; //ECP and EPP-1.7 Mode
            break;
        default:
            return EFI_INVALID_PARAMETER;
        }
        //Program back Device Mode register
        Status=AmiSio->Access(AmiSio,TRUE,FALSE,0xF0,&rv);
        ASSERT_EFI_ERROR(Status);
        break;

    case isGetModeData: {
        //LPT Has 7 possible modes
        //Make sure Device Mode Strings are Static VAR!
        //Otherwise The string will gone after control flow leave this function
        static CHAR16 LptModeStr1[] = L"STD Printer Mode";
        static CHAR16 LptModeStr2[] = L"SPP Mode";
        static CHAR16 LptModeStr3[] = L"EPP-1.9 and SPP Mode";
        static CHAR16 LptModeStr4[] = L"EPP-1.7 and SPP Mode";
        static CHAR16 LptModeStr5[] = L"ECP Mode";
        static CHAR16 LptModeStr6[] = L"ECP and EPP 1.9 Mode";
        static CHAR16 LptModeStr7[] = L"ECP and EPP 1.7 Mode";
        static CHAR16 LptModeHelp[] = L"Change Parallel Port mode. Some of the Modes required a DMA resource. After Mode changing, Reset the System to reflect actual device settings.";
        //---------------------------------------------------
        Dev->DevModeCnt=7;
        //Make room for 2 floppy modes + Help String...
        Dev->DevModeStr=MallocZ(sizeof(CHAR16*)*(Dev->DevModeCnt+1));
        if(Dev->DevModeStr==NULL) {
            Status=EFI_OUT_OF_RESOURCES;
            ASSERT_EFI_ERROR(Status);
            return Status;
        }
        Dev->DevModeStr[0]=&LptModeStr1[0];
        Dev->DevModeStr[1]=&LptModeStr2[0];
        Dev->DevModeStr[2]=&LptModeStr3[0];
        Dev->DevModeStr[3]=&LptModeStr4[0];
        Dev->DevModeStr[4]=&LptModeStr5[0];
        Dev->DevModeStr[5]=&LptModeStr6[0];
        Dev->DevModeStr[6]=&LptModeStr7[0];
        Dev->DevModeStr[7]=&LptModeHelp[0];
    }
    break;

    case isAfterActivate:
        break;

    case isAfterBootScript:
        break;

#if  AMI_SIO_MINOR_VERSION >= 6     
    case isAfterSmmBootScript:      
        break;
#endif

    default:
        Status=EFI_INVALID_PARAMETER;
    } //switch

    return Status;
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
//Procedure: F81866_KBC_Init
//
//Description:
// This function provide each initial routine in genericsio.c
//
//Input:
// IN  AMI_BOARD_INIT_PROTOCOL      *This - AMI Board Int Protocol.
// IN  UINTN                        *Function - AMI Sdl SIO Init Routine.
// IN  OUT VOID                     *ParameterBlock - SIO Component Initialization Routine Parameters Block...
//
//Output:
// EFI_SUCCESS - Initial step sucessfully
// EFI_INVALID_PARAMETER - not find the initial step
//
//Modified:  Nothing
//
//Referrals: None
//
//Notes:
//----------------------------------------------------------------------
//<AMI_PHDR_END>
#if F81866_KEYBOARD_PRESENT
EFI_STATUS F81866_KBC_Init(
    IN AMI_BOARD_INIT_PROTOCOL      *This,
    IN UINTN                        *Function,
    IN OUT VOID                     *ParameterBlock
)
{
    //Update Standard parameter block
    AMI_BOARD_INIT_PARAMETER_BLOCK  *Args=(AMI_BOARD_INIT_PARAMETER_BLOCK*)ParameterBlock;
    SIO_INIT_STEP                   InitStep=(SIO_INIT_STEP)Args->InitStep;
    AMI_SIO_PROTOCOL                *AmiSio=(AMI_SIO_PROTOCOL*)Args->Param1;
    EFI_PCI_IO_PROTOCOL             *PciIo=(EFI_PCI_IO_PROTOCOL*)Args->Param2;
    SIO_DEV2                        *Dev=(SIO_DEV2*)AmiSio;

    EFI_STATUS                      Status=EFI_SUCCESS;
    //Check if parameters passed are VALID and
    if(Args->Signature != AMI_SIO_PARAM_SIG) return EFI_INVALID_PARAMETER;

    switch (InitStep) {
    case isGetSetupData:
    case isPrsSelect:
    case isAfterActivate:
    case isAfterBootScript:
    case isGetModeData:
        break;

    case isBeforeActivate:
#if !defined(SecDecodePkg_SUPPORT) || (SecDecodePkg_SUPPORT == 0)
        //Decode?
        if(Dev->DeviceInfo->Implemented && Dev->NvData.DevEnable) {
            AmiSioLibSetLpcDeviceDecoding(PciIo,Dev->VlData.DevBase1, Dev->DeviceInfo->Uid, Dev->DeviceInfo->Type);
        } else {
            AmiSioLibSetLpcDeviceDecoding(PciIo,0, Dev->DeviceInfo->Uid, Dev->DeviceInfo->Type);
        }
#endif
        break;

#if  AMI_SIO_MINOR_VERSION >= 6     
    case isAfterSmmBootScript:      
        break;
#endif

    default:
        Status=EFI_INVALID_PARAMETER;
    } //switch

    return Status;
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
//Procedure: F81866_PME_Init
//
//Description:
// This function provide each initial routine in genericsio.c
//
//Input:
// IN  AMI_BOARD_INIT_PROTOCOL      *This - AMI Board Int Protocol.
// IN  UINTN                        *Function - AMI Sdl SIO Init Routine.
// IN  OUT VOID                     *ParameterBlock - SIO Component Initialization Routine Parameters Block...
//
//Output:
// EFI_SUCCESS - Initial step sucessfully
// EFI_INVALID_PARAMETER - not find the initial step
//
//Modified:  Nothing
//
//Referrals: None
//
//Notes:
//----------------------------------------------------------------------
//<AMI_PHDR_END>
#if F81866_PME_CONTROLLER_PRESENT
EFI_STATUS F81866_PME_Init(
    IN AMI_BOARD_INIT_PROTOCOL      *This,
    IN UINTN                        *Function,
    IN OUT VOID                     *ParameterBlock
)
{
    //Update Standard parameter block
    AMI_BOARD_INIT_PARAMETER_BLOCK  *Args=(AMI_BOARD_INIT_PARAMETER_BLOCK*)ParameterBlock;
    SIO_INIT_STEP                   InitStep=(SIO_INIT_STEP)Args->InitStep;
    AMI_SIO_PROTOCOL                *AmiSio=(AMI_SIO_PROTOCOL*)Args->Param1;
    EFI_PCI_IO_PROTOCOL             *PciIo=(EFI_PCI_IO_PROTOCOL*)Args->Param2;

    EFI_STATUS                      Status=EFI_SUCCESS;
    //Check if parameters passed are VALID and
    if(Args->Signature != AMI_SIO_PARAM_SIG) return EFI_INVALID_PARAMETER;

    switch (InitStep) {
    case isGetSetupData:
        break;

    case isPrsSelect:
        break;

    case isBeforeActivate:
        //PME registers initial if needed.
        //OEM_TODO: You need to fill DXE_PME_Init_Table_Before_Active[] first.
        ProgramIsaRegisterTable(F81866_CONFIG_INDEX, F81866_CONFIG_DATA,\
                                DXE_PME_Init_Table_Before_Active,sizeof(DXE_PME_Init_Table_Before_Active)/(sizeof(SIO_DEVICE_INIT_DATA)));

        break;

    case isAfterActivate:
    	// F81866_ERP_Miles++ >>>>>
    	#if F81866_ERP_SUPPORT
    		F81866ErpModeCfg(); 
    	#endif //F81866_ERP_SUPPORT
    	// F81866_ERP_Miles++ <<<<<
    	break;

    case isAfterBootScript:
    case isGetModeData:
        break;

#if  AMI_SIO_MINOR_VERSION >= 6     
    case isAfterSmmBootScript:      
        break;
#endif

    default:
        Status=EFI_INVALID_PARAMETER;
    } //switch

    return Status;
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
//Procedure: F81866_HWM_Init
//
//Description:
// This function provide each initial routine in genericsio.c
//
//Input:
// IN  AMI_BOARD_INIT_PROTOCOL      *This - AMI Board Int Protocol.
// IN  UINTN                        *Function - AMI Sdl SIO Init Routine.
// IN  OUT VOID                     *ParameterBlock - SIO Component Initialization Routine Parameters Block...
//
//Output:
// EFI_SUCCESS - Initial step sucessfully
// EFI_INVALID_PARAMETER - not find the initial step
//
//Modified:  Nothing
//
//Referrals: None
//
//Notes:
//----------------------------------------------------------------------
//<AMI_PHDR_END>
#if F81866_HWM_PRESENT
EFI_STATUS F81866_HWM_Init(
    IN AMI_BOARD_INIT_PROTOCOL      *This,
    IN UINTN                        *Function,
    IN OUT VOID                     *ParameterBlock
)
{
    //Update Standard parameter block
    AMI_BOARD_INIT_PARAMETER_BLOCK  *Args=(AMI_BOARD_INIT_PARAMETER_BLOCK*)ParameterBlock;
    SIO_INIT_STEP                   InitStep=(SIO_INIT_STEP)Args->InitStep;
    AMI_SIO_PROTOCOL                *AmiSio=(AMI_SIO_PROTOCOL*)Args->Param1;
    EFI_PCI_IO_PROTOCOL             *PciIo=(EFI_PCI_IO_PROTOCOL*)Args->Param2;

    EFI_STATUS                      Status=EFI_SUCCESS;
    SIO_DEV2                        *Dev=(SIO_DEV2*)AmiSio;
    EFI_S3_SAVE_STATE_PROTOCOL      *BootScriptProtocol = Dev->Owner->SaveState;
    //Check if parameters passed are VALID and
    if(Args->Signature != AMI_SIO_PARAM_SIG) return EFI_INVALID_PARAMETER;

    switch (InitStep) {
    case isGetSetupData:
        break;

    case isPrsSelect:
    case isGetModeData:
        break;

    case isBeforeActivate:
        break;

    case isAfterActivate:
        //HWM registers initial if needed.
        //OEM_TODO: You need to fill DXE_HWM_Init_Table_After_Active[] first.
        ProgramIsaRegisterTable(F81866_HWM_INDEX_PORT, F81866_HWM_DATA_PORT,\
                                DXE_HWM_Init_Table_After_Active,sizeof(DXE_HWM_Init_Table_After_Active)/(sizeof(SIO_DEVICE_INIT_DATA)));
        //INTERNAL_085_RayWu, ADD 2015/01/28 >>
	#if defined(F81866_SMF_SUPPORT) && (F81866_SMF_SUPPORT == 1)
	F81866SmartFunction();
	#endif
	//INTERNAL_085_RayWu, ADD 2015/01/28 <<
        break;

    case isAfterBootScript:
        //Restore HWM registers after Sx resume, if needed.
        //Below HWM read/write interface is LPC/ISA interface,
        //if other interface, please re-program it.
        //This, Width, Address, Count, Buffer
        BootScriptProtocol = (EFI_S3_SAVE_STATE_PROTOCOL*)Dev->Owner->SaveState;
        SioLib_BootScriptSioS3SaveTable(F81866_HWM_INDEX_PORT, F81866_HWM_DATA_PORT, \
                                        DXE_HWM_Init_Table_After_Active,sizeof(DXE_HWM_Init_Table_After_Active)/(sizeof(SIO_DEVICE_INIT_DATA)), BootScriptProtocol);
		//F81866_SMF_Miles++ >>>>>
		#if defined(F81866_SMF_SUPPORT) && (F81866_SMF_SUPPORT == 1)
        	SmartFanBootScript(BootScriptProtocol);
		#endif
		//F81866_SMF_Miles++ <<<<<
        break;

#if  AMI_SIO_MINOR_VERSION >= 6     
    case isAfterSmmBootScript:      
        break;
#endif
        
    default:
        Status=EFI_INVALID_PARAMETER;
    } //switch

    return Status;
}
#endif

//<AMI_PHDR_START>
//----------------------------------------------------------------------
//
//Procedure: F81866_GPIO_Init
//
//Description:
// This function provide each initial routine in genericsio.c
//
//Input:
// IN  AMI_BOARD_INIT_PROTOCOL      *This - AMI Board Int Protocol.
// IN  UINTN                        *Function - AMI Sdl SIO Init Routine.
// IN  OUT VOID                     *ParameterBlock - SIO Component Initialization Routine Parameters Block...
//
//Output:
// EFI_SUCCESS - Initial step sucessfully
// EFI_INVALID_PARAMETER - not find the initial step
//
//Modified:  Nothing
//
//Referrals: None
//
//Notes:
//----------------------------------------------------------------------
//<AMI_PHDR_END>
//#if F81866_GPIO_PORT_PRESENT
EFI_STATUS F81866_GPIO_Init(
    IN AMI_BOARD_INIT_PROTOCOL      *This,
    IN UINTN                        *Function,
    IN OUT VOID                     *ParameterBlock
)
{
    //Update Standard parameter block
    AMI_BOARD_INIT_PARAMETER_BLOCK  *Args=(AMI_BOARD_INIT_PARAMETER_BLOCK*)ParameterBlock;
    SIO_INIT_STEP                   InitStep=(SIO_INIT_STEP)Args->InitStep;
    AMI_SIO_PROTOCOL                *AmiSio=(AMI_SIO_PROTOCOL*)Args->Param1;
    EFI_PCI_IO_PROTOCOL             *PciIo=(EFI_PCI_IO_PROTOCOL*)Args->Param2;

    EFI_STATUS                      Status=EFI_SUCCESS;
    //Check if parameters passed are VALID and
    if(Args->Signature != AMI_SIO_PARAM_SIG) return EFI_INVALID_PARAMETER;

    switch (InitStep) {
    case isGetSetupData:
        break;

    case isPrsSelect:
    case isGetModeData:
        break;

    case isBeforeActivate:
        //Initial GPIO register if you need.
        //OEM_TODO: You need to fill DXE_GPIO_Init_Table_Before_Active[] first.
        ProgramIsaRegisterTable(F81866_CONFIG_INDEX, F81866_CONFIG_DATA,\
                                DXE_GPIO_Init_Table_Before_Active,sizeof(DXE_GPIO_Init_Table_Before_Active)/(sizeof(SIO_DEVICE_INIT_DATA)));

        break;

    case isAfterActivate:
        break;

    case isAfterBootScript:
        break;

#if  AMI_SIO_MINOR_VERSION >= 6     
    case isAfterSmmBootScript:      
        break;
#endif
       
    default:
        Status=EFI_INVALID_PARAMETER;
    } //switch

    return Status;
}
//#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
