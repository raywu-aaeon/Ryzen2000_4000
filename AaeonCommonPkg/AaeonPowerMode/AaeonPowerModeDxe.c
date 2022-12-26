//**********************************************************************
//<AMI_FHDR_START>
//
// Name:  AaeonPowerModeDxe.c
//
// Description:	Need porting for different board
//
//<AMI_FHDR_END>
//**********************************************************************
#include <Efi.h>
#include <AmiLib.h>
#include <token.h>
#include <AmiDxeLib.h>
#include <Setup.h>
#include <AcpiRes.h>

extern EFI_BOOT_SERVICES   *pBS;
extern UINT32  gSetupAttr;

#define ACLOSS_SRC_SB 0
#define ACLOSS_SRC_SIO 1

#define ACLOSS_LAST_STATE  0
#define ACLOSS_ALWAYS_ON   1
#define ACLOSS_ALWAYS_OFF  2

UINT8 MapToACPowerLoss[3] = STATEAFTERG3_MAP;

//**********************************************************************

EFI_STATUS EFIAPI AaeonPowerModeDxeInit(VOID)
{
	EFI_STATUS Status = EFI_SUCCESS;
   	EFI_GUID	SetupGuid = SETUP_GUID;
   	SETUP_DATA	SetupData;
   	UINTN		VariableSize = sizeof(SetupData);
   	UINT32		Attribute = 0;

	Status = pRS->GetVariable( L"Setup", &SetupGuid, &Attribute, &VariableSize, &SetupData );

	if(SetupData.AaeonPowerMode == 1) //AT power mode
	{
		// Disable BIT24: Power Button Enable (PWRBTN_EN)
    	IoWrite32(PM_BASE_ADDRESS, IoRead32(PM_BASE_ADDRESS) & ~BIT24);	
    }

	if(SetupData.AaeonCommonFeaturesSyncReady == 0)
	{
	    if(SetupData.AaeonPowerMode == 1) //AT power mode
	    {
	    	//sync ac-powerlose item to "Always-on"
#if CRB_USE_VAR_STATEAFTERG3
			SetupData.StateAfterG3 = MapToACPowerLoss[ACLOSS_ALWAYS_ON];
#else
			SetupData.LastState = MapToACPowerLoss[ACLOSS_ALWAYS_ON];
#endif 

			#if defined(F81866_SUPPORT) && (F81866_SUPPORT == 1)
	    		SetupData.F81866RestoreACPowerLoss = 1;
			#endif
			#if defined(F81966_SUPPORT) && (F81966_SUPPORT == 1)
	    		SetupData.F81966RestoreACPowerLoss = 1;
			#endif	
			#if defined(F81804_SUPPORT) && (F81804_SUPPORT == 1)
	    		SetupData.F81804RestoreACPowerLoss = 1;
			#endif				    		
			#if defined(IT8728F_SUPPORT) && (IT8728F_SUPPORT == 1)
	    		SetupData.IT8728FRestoreACPowerLoss = 1;
			#endif
			#if defined(IT8625_SUPPORT) && (IT8625_SUPPORT == 1)
	    		SetupData.IT8625RestoreACPowerLoss = 1;
			#endif
			#if defined(NCT6791D_SUPPORT) && (NCT6791D_SUPPORT == 1)
	    		SetupData.NCT6791D_AC_PWR_LOSS = 1;
			#endif
	    
	    } else
	    {
	    	// sync ac power failure item between PowerMode/SIO/SB
	    	if (SetupData.AaeonRestoreACPowerLossSrc == ACLOSS_SRC_SB)
	    	{
#if CRB_USE_VAR_STATEAFTERG3
				SetupData.StateAfterG3 = MapToACPowerLoss[SetupData.AaeonRestoreACPowerLoss];
#else
				SetupData.LastState = MapToACPowerLoss[SetupData.AaeonRestoreACPowerLoss];
#endif 	    	
	    		//Patch SIO to bypass mode.
	    		//Note: If SIO doesn't support bypass mode, AC power loss function
	    		//      is always controlled by SIO
				#if defined(F81866_SUPPORT) && (F81866_SUPPORT == 1)
					SetupData.F81866RestoreACPowerLoss = 3;
				#endif
				#if defined(F81966_SUPPORT) && (F81966_SUPPORT == 1)
					SetupData.F81966RestoreACPowerLoss = 3;
				#endif	
				#if defined(F81804_SUPPORT) && (F81804_SUPPORT == 1)
					SetupData.F81804RestoreACPowerLoss = 3;
				#endif									
				#if defined(NCT6791D_SUPPORT) && (NCT6791D_SUPPORT == 1)
					SetupData.NCT6791D_AC_PWR_LOSS = 4;
				#endif
				#if defined(IT8728F_SUPPORT) && (IT8728F_SUPPORT == 1)
					SetupData.IT8728FRestoreACPowerLoss = 3;
				#endif
				#if defined(IT8625_SUPPORT) && (IT8625_SUPPORT == 1)
					SetupData.IT8625RestoreACPowerLoss = 3;
				#endif
	    	}
		
	    	if (SetupData.AaeonRestoreACPowerLossSrc == ACLOSS_SRC_SIO)
	    	{
				#if defined(F81866_SUPPORT) && (F81866_SUPPORT == 1)
					switch (SetupData.AaeonRestoreACPowerLoss)
					{
						case ACLOSS_LAST_STATE:
							SetupData.F81866RestoreACPowerLoss = 0;
						break;
						case ACLOSS_ALWAYS_ON:
							SetupData.F81866RestoreACPowerLoss = 1;
						break;
						case ACLOSS_ALWAYS_OFF: default:
							SetupData.F81866RestoreACPowerLoss = 2;
						break;
					}
				#endif
				#if defined(F81966_SUPPORT) && (F81966_SUPPORT == 1)
					switch (SetupData.AaeonRestoreACPowerLoss)
					{
						case ACLOSS_LAST_STATE:
							SetupData.F81966RestoreACPowerLoss = 0;
						break;
						case ACLOSS_ALWAYS_ON:
							SetupData.F81966RestoreACPowerLoss = 1;
						break;
						case ACLOSS_ALWAYS_OFF: default:
							SetupData.F81966RestoreACPowerLoss = 2;
						break;
					}
				#endif					
				#if defined(F81804_SUPPORT) && (F81804_SUPPORT == 1)
					switch (SetupData.AaeonRestoreACPowerLoss)
					{
						case ACLOSS_LAST_STATE:
							SetupData.F81804RestoreACPowerLoss = 0;
						break;
						case ACLOSS_ALWAYS_ON:
							SetupData.F81804RestoreACPowerLoss = 1;
						break;
						case ACLOSS_ALWAYS_OFF: default:
							SetupData.F81804RestoreACPowerLoss = 2;
						break;
					}
				#endif						
				#if defined(IT8728F_SUPPORT) && (IT8728F_SUPPORT == 1)
					switch (SetupData.AaeonRestoreACPowerLoss)
					{
						case ACLOSS_LAST_STATE:
							SetupData.IT8728FRestoreACPowerLoss = 0;
						break;
						case ACLOSS_ALWAYS_ON:
							SetupData.IT8728FRestoreACPowerLoss = 1;
						break;
						case ACLOSS_ALWAYS_OFF: default:
							SetupData.IT8728FRestoreACPowerLoss = 2;
						break;
					}
				#endif
				#if defined(IT8625_SUPPORT) && (IT8625_SUPPORT == 1)
					switch (SetupData.AaeonRestoreACPowerLoss)
					{
						case ACLOSS_LAST_STATE:
							SetupData.IT8625RestoreACPowerLoss = 0;
						break;
						case ACLOSS_ALWAYS_ON:
							SetupData.IT8625RestoreACPowerLoss = 1;
						break;
						case ACLOSS_ALWAYS_OFF: default:
							SetupData.IT8625RestoreACPowerLoss = 2;
						break;
					}
				#endif
				#if defined(NCT6791D_SUPPORT) && (NCT6791D_SUPPORT == 1)
					switch (SetupData.AaeonRestoreACPowerLoss)
					{
						case ACLOSS_LAST_STATE:
							SetupData.NCT6791D_AC_PWR_LOSS = 2;
						break;
						case ACLOSS_ALWAYS_ON:
							SetupData.NCT6791D_AC_PWR_LOSS = 1;
						break;
						case ACLOSS_ALWAYS_OFF: default:
							SetupData.NCT6791D_AC_PWR_LOSS = 0;
						break;
					}
				#endif
					//AAEON_APL_OVERRIDE, Patch Chipset to always on
#if CRB_USE_VAR_STATEAFTERG3
					SetupData.StateAfterG3 = MapToACPowerLoss[ACLOSS_ALWAYS_ON];
#else
					SetupData.LastState = MapToACPowerLoss[ACLOSS_ALWAYS_ON];
#endif 
	    	}

	    	// Sync AAEON Power Saving(ERP) Control item
	    	{
			if (SetupData.AaeonErpMode == 1)
			{
				#if defined(F81866_ERP_SUPPORT) && (F81866_ERP_SUPPORT == 1)
					SetupData.F81866ErpMode = 2;
				#endif
				#if defined(F81966_ERP_SUPPORT) && (F81966_ERP_SUPPORT == 1)
					SetupData.F81966ErpMode = 2;
				#endif		
				#if defined(F81804_ERP_SUPPORT) && (F81804_ERP_SUPPORT == 1)
					SetupData.F81804ErpMode = 2;
				#endif								
				#if defined(NCT6791D_SUPPORT) && (NCT6791D_SUPPORT == 1)
					SetupData.NCT6791DDeepS5 = 1;
				#endif
			}
			else
			{ 
				#if defined(F81866_ERP_SUPPORT) && (F81866_ERP_SUPPORT == 1)
					SetupData.F81866ErpMode = 0;
				#endif
				#if defined(F81966_ERP_SUPPORT) && (F81966_ERP_SUPPORT == 1)
					SetupData.F81966ErpMode = 0;
				#endif	
				#if defined(F81804_ERP_SUPPORT) && (F81804_ERP_SUPPORT == 1)
					SetupData.F81804ErpMode = 0;
				#endif									
				#if defined(NCT6791D_SUPPORT) && (NCT6791D_SUPPORT == 1)
					SetupData.NCT6791DDeepS5 = 0;
				#endif
			}
	    	}
	    }
	    	Status = pRS->SetVariable( L"Setup", &SetupGuid,
			Attribute,
			VariableSize, &SetupData);
	} //if(SetupData.AaeonCommonFeaturesSyncReady == 0)
	return Status;
}

// AaeonPowerModeCfg
EFI_STATUS AaeonPowerModeCfg(VOID)
{
    EFI_STATUS              Status;
    EFI_GUID                SetupGuid = SETUP_GUID;
    UINTN                   VariableSize = sizeof(SETUP_DATA);
    SETUP_DATA              *SetupData = NULL;
    ACPI_HDR                *dsdt;
    EFI_PHYSICAL_ADDRESS    addr;
    ASL_OBJ_INFO	        obj={0};

	TRACE((TRACE_ALWAYS, "[AaeonPowerModeCfg]Enter AaeonPowerModeCfg\n"));
	Status = LibGetDsdt(&addr, EFI_ACPI_TABLE_VERSION_ALL);
    if(EFI_ERROR(Status))
    {  
        ASSERT_EFI_ERROR(Status);
        return EFI_SUCCESS;
    } else dsdt=(ACPI_HDR*)addr;
      
    Status = GetEfiVariable(L"Setup", &SetupGuid, NULL, &VariableSize, &SetupData);
    if(EFI_ERROR(Status))
    {  
        ASSERT_EFI_ERROR(Status);
        return Status;
    }
    
    if(SetupData->AaeonPowerMode == 1) //AT power mode
    {
        // destory Sx package
     	//Status = GetAslObj((UINT8*)dsdt+sizeof(ACPI_HDR), dsdt->Length-sizeof(ACPI_HDR)-1, "_S5", otName, &obj);
        //if (!EFI_ERROR(Status))
        //{
        //    ((UINT8 *)(obj.ObjName))[1] = 'X';
        //}

     	Status = GetAslObj((UINT8*)dsdt+sizeof(ACPI_HDR), dsdt->Length-sizeof(ACPI_HDR)-1, "_S4", otName, &obj);
        if (!EFI_ERROR(Status))
        {
            ((UINT8 *)(obj.ObjName))[1] = 'X';
        }

    	Status = GetAslObj((UINT8*)dsdt+sizeof(ACPI_HDR), dsdt->Length-sizeof(ACPI_HDR)-1, "_S3", otName, &obj);
        if (!EFI_ERROR(Status))
        {
            ((UINT8 *)(obj.ObjName))[1] = 'X';
        }

        Status = GetAslObj((UINT8*)dsdt+sizeof(ACPI_HDR), dsdt->Length-sizeof(ACPI_HDR)-1, "_S1", otName, &obj);
        if (!EFI_ERROR(Status))
        {
            ((UINT8 *)(obj.ObjName))[1] = 'X';
        }

        //Checksum
        dsdt->Checksum = 0;
        dsdt->Checksum = ChsumTbl((UINT8*)dsdt, dsdt->Length);
    } else
    {
        // ATX mode
        if(SetupData->AcpiSleepState == 2) //Sleep to S3
        {
        	Status = GetAslObj((UINT8*)dsdt+sizeof(ACPI_HDR), dsdt->Length-sizeof(ACPI_HDR)-1, "_S1", otName, &obj);
            if (!EFI_ERROR(Status))
    	    {
    	        ((UINT8 *)(obj.ObjName))[1] = 'X';
    	    }

            //Checksum
            dsdt->Checksum = 0;
            dsdt->Checksum = ChsumTbl((UINT8*)dsdt, dsdt->Length);
        }
    }
        
    if (SetupData) pBS->FreePool(SetupData);
    return EFI_SUCCESS;
}

