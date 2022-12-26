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
// Name:  <IT8518PeiInit.c>
//
// Description: Porting for PEI phase.Just for necessary devices porting.
//
//<AMI_FHDR_END>
//**********************************************************************
//-------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------

#include <AmiPeiLib.h>
#include <IT8518PeiIoTable.h>
#include <Library/AmiSioPeiLib.h>
#include <Setup.h>
#include <AmiCspLib.h>
#include "EcApiProtocol.c"

//-------------------------------------------------------------------------
// internal funtion declare; these funtions are only used by this file.
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
// global funtion declare ; these funtions are used for other files.
//-------------------------------------------------------------------------
VOID IT851xMiscSetupFunction(IN CONST EFI_PEI_SERVICES	**PeiServices)
{
	EFI_STATUS				Status;
	SETUP_DATA				SetupData;
	UINTN           			VariableSize = sizeof( SETUP_DATA );
	EFI_GUID				gSetupGuid = SETUP_GUID;
	EFI_PEI_READ_ONLY_VARIABLE2_PPI 	*ReadOnlyVariable = NULL;

	Status = (*PeiServices)->LocatePpi( PeiServices, &gEfiPeiReadOnlyVariable2PpiGuid, 0, NULL, &ReadOnlyVariable );
	Status = ReadOnlyVariable->GetVariable( ReadOnlyVariable, L"Setup", &gSetupGuid, NULL, &VariableSize, &SetupData );

	//>>Initial gStallPpi	
	{	
		EFI_PEI_STALL_PPI    	*StallPpi = NULL;
		Status = (**PeiServices).LocatePpi(PeiServices, &gEfiPeiStallPpiGuid,0, NULL, &StallPpi);	
		gPeiServices = PeiServices;
		gStallPpi = StallPpi;		
	}
	//<<Initial gStallPpi	


	#if defined(IT851X_BL_CONTROL_SUPPORT) && (IT851X_BL_CONTROL_SUPPORT == 1)
	{
	        UINT8   RegVal;

	        EcBrightAccess(ApiRead);
		
		RegVal = (SetupData.EcBacklightEn) << 7;
		EcBramAccess(EcReg_Dat0, &RegVal, ApiWrite);

		RegVal = (!SetupData.EcBrcMode) << 7|(!SetupData.EcBrcInv) << 6|(SetupData.EcBrcMode) << 3|(!SetupData.EcBrcInv) << 2;
		EcBramAccess(EcReg_Dat1, &RegVal, ApiWrite);	

		RegVal = (SetupData.EcBrcLevel)*255/100 ; 
		EcBramAccess(EcReg_Dat2, &RegVal, ApiWrite);	
		EcBramAccess(EcReg_Dat3, &RegVal, ApiWrite);	
		
		EcBrightAccess(ApiWrite);
	}
	#endif //#if defined(IT851X_BL_CONTROL_SUPPORT) && (IT851X_BL_CONTROL_SUPPORT == 1)	
	
//Restore AC Power Loss control _Begin >>
{
	#if defined (IT85xx_AFTER_G3_SUPPORT)&& (IT85xx_AFTER_G3_SUPPORT == 1)
	{
	    EcPmcAccess(ApiRead);
	    #if defined (AAEONPOWERMODE_SUPPORT)&& (AAEONPOWERMODE_SUPPORT == 1)
			if (SetupData.AaeonPowerMode)
			{	EcWriteByte(EcReg_Dat0,(EcReadByte(EcReg_Dat0)&0xFC)|BIT0);	}
			else
	    #endif	
			{
				EcWriteByte(EcReg_Dat0,(EcReadByte(EcReg_Dat0)&0xFC)|SetupData.AaeonSIO_AfterG3);
			}
			EcPmcAccess(ApiWrite);		    
	}
	#endif		
}
//Restore AC Power Loss control _End <<

#if defined(IT851X_DIO_SUPPORT) && (IT851X_DIO_SUPPORT == 1)			
	{
		UINT8		DdioData;
	
		DdioData = 0xFF;
		
		EcDioUseSelAccess(ApiRead);
		EcBramAccess(EcReg_Dat1, &DdioData, ApiWrite);
		EcDioUseSelAccess(ApiWrite);
				
		DdioData = (SetupData.GPI3Level << 3) | (SetupData.GPI2Level << 2) | (SetupData.GPI1Level << 1) | SetupData.GPI0Level;
		DdioData |= (SetupData.GPO3Level << 7) | (SetupData.GPO2Level << 6) | (SetupData.GPO1Level << 5) | (SetupData.GPO0Level << 4);

		EcDioValAccess(ApiRead);
		EcBramAccess(EcReg_Dat1, &DdioData, ApiWrite);
		
#if defined(IT851X_LVDS1_DIO_ENABLE) && (IT851X_LVDS1_DIO_ENABLE == 1)      
{       
//    EcDioValAccess(ApiRead);            
    EcBramAccess(EcReg_Dat2, &DdioData, ApiRead);
    DdioData &= (~(BIT0<<(IT851X_LVDS1_DIO_NUM%8)));        
    DdioData |= SetupData.PTN3460En1<<(IT851X_LVDS1_DIO_NUM%8);
                   
    #if defined(IT851X_LVDS2_DIO_ENABLE) && (IT851X_LVDS2_DIO_ENABLE == 1)  
        DdioData &= (~(BIT0<<(IT851X_LVDS2_DIO_NUM%8)));        
        DdioData |= SetupData.PTN3460En2<<(IT851X_LVDS2_DIO_NUM%8);
    #endif        
    EcBramAccess(EcReg_Dat2, &DdioData, ApiWrite);
//    EcDioValAccess(ApiWrite);
}
#endif          
	
		EcDioValAccess(ApiWrite);		
		
		DdioData = (SetupData.GPI3Type << 3) | (SetupData.GPI2Type << 2) | (SetupData.GPI1Type << 1) | SetupData.GPI0Type;
		DdioData |= (SetupData.GPO3Type << 7) | (SetupData.GPO2Type << 6) | (SetupData.GPO1Type << 5) | (SetupData.GPO0Type << 4);

		EcDioDirAccess(ApiRead);
		EcBramAccess(EcReg_Dat1, &DdioData, ApiWrite);
		EcDioDirAccess(ApiWrite);		

		DdioData = (SetupData.FLEXIO_INT[0]<<0)|(SetupData.FLEXIO_INT[1]<<1)|(SetupData.FLEXIO_INT[2]<<2)|(SetupData.FLEXIO_INT[3]<<3);
		DdioData |= (SetupData.FLEXIO_INT[4]<<4)|(SetupData.FLEXIO_INT[5]<<5)|(SetupData.FLEXIO_INT[6]<<6)|(SetupData.FLEXIO_INT[7]<<7);

		EcDioIntAccess(ApiRead);
		EcBramAccess(EcReg_Dat1, &DdioData, ApiWrite);
		EcDioIntAccess(ApiWrite);			
	}
#endif	

#if defined(IT851X_FAN1_ENABLE) && (IT851X_FAN1_ENABLE == 1)
{
        UINT8       	TmpData;

        EcSmfAccess(0x00,ApiRead);              
        switch (SetupData.IT851XFan1SmartFanMode) 
	{
        	case 0:         //Full_Mode           	
				EcBramAccess(EcReg_Dat3, &TmpData, ApiRead);	// Read Start
				TmpData &= ~BIT7;
				EcBramAccess(EcReg_Dat3, &TmpData, ApiWrite);	
				TmpData = 0x64;	//Full Mode
				EcBramAccess(EcReg_Dat8, &TmpData, ApiWrite);
	                        break;

	        case 1:         //Manual_Mode
				EcBramAccess(EcReg_Dat3, &TmpData, ApiRead);	// Read Start
				TmpData &= ~BIT7;
				EcBramAccess(EcReg_Dat3, &TmpData, ApiWrite);	
				TmpData = SetupData.Fan1ManualPWM;
				EcBramAccess(EcReg_Dat8, &TmpData, ApiWrite);
	                        break;

	                case 2:         //Auto_Mode_PWM:
				EcBramAccess(EcReg_Dat3, &TmpData, ApiRead);	// Read Start
				TmpData = BIT7|(SetupData.Fan1Invert)<<6|(SetupData.Fan1MonitorTher)<<0;		
				EcBramAccess(EcReg_Dat3, &TmpData, ApiWrite);	
				TmpData = SetupData.Fan1StartTemp;
				EcBramAccess(EcReg_Dat4, &TmpData, ApiWrite);
				TmpData= SetupData.Fan1OffTemp;
				EcBramAccess(EcReg_Dat5, &TmpData, ApiWrite);
				TmpData= SetupData.Fan1StartPWM;
				EcBramAccess(EcReg_Dat6, &TmpData, ApiWrite);
				TmpData= SetupData.Fan1Slope;
				EcBramAccess(EcReg_Dat7, &TmpData, ApiWrite);
	                        break;

	                default:
	                        break;
	                        
	        }
	        EcSmfAccess(0x00,ApiWrite);               
	}
#endif //IT851X_FAN1_ENABLE	


#if defined(IT851X_FAN2_ENABLE) && (IT851X_FAN2_ENABLE == 1)
{
        UINT8       	TmpData;

        EcSmfAccess(0x01,ApiRead);              
        switch (SetupData.IT851XFan2SmartFanMode) 
	{
        	case 0:         //Full_Mode           	
				EcBramAccess(EcReg_Dat3, &TmpData, ApiRead);	// Read Start
				TmpData &= ~BIT7;
				EcBramAccess(EcReg_Dat3, &TmpData, ApiWrite);	
				TmpData = 0x64;	//Full Mode
				EcBramAccess(EcReg_Dat8, &TmpData, ApiWrite);
	                        break;

	        case 1:         //Manual_Mode
				EcBramAccess(EcReg_Dat3, &TmpData, ApiRead);	// Read Start
				TmpData &= ~BIT7;
				EcBramAccess(EcReg_Dat3, &TmpData, ApiWrite);	
				TmpData = SetupData.Fan2ManualPWM;
				EcBramAccess(EcReg_Dat8, &TmpData, ApiWrite);
	                        break;

	                case 2:         //Auto_Mode_PWM:
				EcBramAccess(EcReg_Dat3, &TmpData, ApiRead);	// Read Start
				TmpData = BIT7|(SetupData.Fan2Invert)<<6|(SetupData.Fan2MonitorTher)<<0;		
				EcBramAccess(EcReg_Dat3, &TmpData, ApiWrite);	
				TmpData = SetupData.Fan2StartTemp;
				EcBramAccess(EcReg_Dat4, &TmpData, ApiWrite);
				TmpData= SetupData.Fan2OffTemp;
				EcBramAccess(EcReg_Dat5, &TmpData, ApiWrite);
				TmpData= SetupData.Fan2StartPWM;
				EcBramAccess(EcReg_Dat6, &TmpData, ApiWrite);
				TmpData= SetupData.Fan2Slope;
				EcBramAccess(EcReg_Dat7, &TmpData, ApiWrite);
	                        break;

	                default:
	                        break;
	                        
	        }
	        EcSmfAccess(0x01,ApiWrite);               
	}
#endif //IT851X_FAN2_ENABLE	


{
        UINT8       	TmpData;

        EcBatManageAccess(ApiRead);     
        
        TmpData = SetupData.EcBatteryManagement;    
		  
        EcBramAccess(EcReg_Dat0, &TmpData, ApiWrite);      
		  
        EcBatManageAccess(ApiWrite);      
}

	
//IT851xExitConfigMode();
}

//*************************************************************************
// belows are functions defined
//*************************************************************************

// <AMI_PHDR_START>
//-------------------------------------------------------------------------
//
// Procedure: IT8518PeiInitEntryPoint
//
// Description:
//  This function provide PEI phase SIO initialization
//
// Input:
//  IN  EFI_FFS_FILE_HEADER    *FfsHeader - Logical Device's information
//  IN  EFI_PEI_SERVICES       **PeiServices  - Read/Write PCI config space
//
// Output:    None
//
// Modified:  Nothing
//
// Referrals: None
//
// Note:
//-------------------------------------------------------------------------
// <AMI_PHDR_END>
EFI_STATUS IT8518PeiInitEntryPoint(
    IN       EFI_PEI_FILE_HANDLE  FileHandle,
    IN CONST EFI_PEI_SERVICES     **PeiServices
)
{
//>>
//    UINT8 index;
//
//    for(index=0; index<sizeof(IT8518PeiDecodeTable)/sizeof(IO_DECODE_DATA); index++)
//        AmiSioLibSetLpcDeviceDecoding(NULL, IT8518PeiDecodeTable[index].BaseAdd, IT8518PeiDecodeTable[index].UID, IT8518PeiDecodeTable[index].Type);
//
//    ProgramRtRegisterTable(0, IT8518PeiInitTable, sizeof(IT8518PeiInitTable)/sizeof(SIO_DEVICE_INIT_DATA));
//<<

	
	IT851xMiscSetupFunction(PeiServices);
    return EFI_SUCCESS;
}

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
