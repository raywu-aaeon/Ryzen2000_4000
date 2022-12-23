//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file CrbPei.c
    This file contains code for Chipset Reference Board
    PCIE port initialization in the PEI stage

**/

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------
#include <PiPei.h>
#include <Library/PeiServicesLib.h>
#include <Library/PciLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>

#include <Token.h>
#include <AmiPeiLib.h>
#include <Setup.h>

// Consumed PPIs
#include <Ppi/ReadOnlyVariable2.h>
#include <AmdCpmPei.h>
#include <CrbPcie/CrbPcie.h>
#include <Library/AmdSocBaseLib.h>
//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)
EFI_STATUS
PcieConfiguration(
    IN  EFI_PEI_SERVICES   **PeiServices,
    IN  SETUP_DATA          *SetupData
    );

// GUID Definition(s)
static EFI_GUID gAmdPcieinfoHobGuid = AMD_PCIE_INFO_HOB_GUID; 

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)


// PPI that are installed


EFI_STATUS
CrbPciePeimNotifyCallback(
    IN  EFI_PEI_SERVICES                **PeiServices,
    IN  EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyDesc,
    IN  VOID                            *InvokePpi
);


// PPI that are notified
static EFI_PEI_NOTIFY_DESCRIPTOR  mCrbPciePeimNotify = {
  (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gAmdCpmOverrideTablePpiGuid,
  CrbPciePeimNotifyCallback
};

// External Declaration(s)

// Function Definition(s)

/**
    This function is the entry point for CRB PCIE PEIM.

    @param FileHandle Pointer to the FFS file header.
    @param PeiServices Pointer to the PEI services table.

    @retval EFI_STATUS EFI_SUCCESS

    @note  This routine is called very early, prior to SBPEI and NBPEI.
**/
EFI_STATUS
EFIAPI
CrbPciePeiInit (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
    EFI_STATUS                  Status = EFI_SUCCESS;

    Status = (**PeiServices).NotifyPpi (PeiServices, &mCrbPciePeimNotify);

    return Status;
}

/**
    This function is called after "gAmdCpmOverrideTablePpiGuid".
    It would override the configuration of CPM table.

    @param PeiServices Pointer to PeiServices
    @param NotifyDesc Pointer to NotifyDesc
    @param InvokePpi 

    @retval EFI_STATUS EFI_SUCCESS

**/
EFI_STATUS
CrbPciePeimNotifyCallback(
    IN  EFI_PEI_SERVICES                **PeiServices,
    IN  EFI_PEI_NOTIFY_DESCRIPTOR       *NotifyDesc,
    IN  VOID                            *InvokePpi
)
{
    EFI_STATUS                         Status;
    UINTN                              VariableSize;
    EFI_PEI_READ_ONLY_VARIABLE2_PPI    *ReadOnlyVariable;
    EFI_GUID                           SetupGuid= SETUP_GUID;

    Status = (*PeiServices)->LocatePpi( PeiServices, \
                                        &gEfiPeiReadOnlyVariable2PpiGuid, \
                                        0, \
                                        NULL, \
                                        &ReadOnlyVariable );
                                        
                                        
    if (!EFI_ERROR(Status)) {
        SETUP_DATA                      SetupData;
        VariableSize = sizeof(SETUP_DATA);
        Status = ReadOnlyVariable->GetVariable( ReadOnlyVariable, \
                                                L"Setup", \
                                                &SetupGuid, \
                                                NULL, \
                                                &VariableSize, \
                                                &SetupData );
        if (!EFI_ERROR(Status))   {
            PcieConfiguration (PeiServices,&SetupData);}
        
    }
    
    return  EFI_SUCCESS;
}

/**
    This function would override the PCIE Configuration under CPM table
    by CRB setup items.

    @param PeiServices Pointer to PeiServices
    @param SetupData Pointer to SetupData

    @retval EFI_STATUS EFI_SUCCESS

**/
EFI_STATUS
PcieConfiguration(
    IN  EFI_PEI_SERVICES    **PeiServices,
    IN  SETUP_DATA          *SetupData
    )
{
	EFI_STATUS                         Status;
	UINT16                             HobSize;

    AMD_PCIE_DEVICE_HOB *PcieHob=NULL;

    DEBUG ((DEBUG_INFO|DEBUG_PLATFORM, "CRB PcieConfiguration\n"));
    
    HobSize = sizeof(AMD_PCIE_DEVICE_HOB);
    Status = (*PeiServices)->CreateHob(PeiServices, EFI_HOB_TYPE_GUID_EXTENSION, HobSize, &PcieHob);
  
    PcieHob->Header.Name = gAmdPcieinfoHobGuid;
    
    if (SetupData != NULL) {
        if (SetupData->CrbAmdPcieControl) {
            
            AMD_CPM_TABLE_PPI          *AmdCpmTablePpi;

            Status = (*PeiServices)->LocatePpi (
                           PeiServices,
                           &gAmdCpmTablePpiGuid,
                           0,
                           NULL,
                           (VOID**)&AmdCpmTablePpi
                           );        
            if (EFI_ERROR (Status)) {
                return Status;
            }
            
            // PCIE porting code
            // It will override table "gCpmDxioTopologyTable" under "AmdCpmOemTable.c".
            {
                AMD_CPM_DXIO_TOPOLOGY_TABLE       *DxioTopologyTablePtr;
                DXIO_PORT_DESCRIPTOR              *DxioPort;
                
                AMD_PCIE_SETUP_DATA               *AmdPcieSetup=NULL;
                AMD_PCIE_SETUP_DATA               *TempAmdPcieSetup=NULL;


                UINT8                         Count=0;
                
                Status= (*PeiServices)->AllocatePool(PeiServices,
                                            sizeof(AMD_PCIE_SETUP_DATA)*8, 
                                            &AmdPcieSetup);
                if (EFI_ERROR (Status)) {
                return Status;
                }
                TempAmdPcieSetup = AmdPcieSetup;
                
                AmdPcieSetup->DeviceEnable = SetupData->Device0Enabled;
                AmdPcieSetup->DeviceAspmMode = SetupData->Device0AspmMode;
                AmdPcieSetup->DeviceHotPlug = SetupData->Device0HotPlugMode;
                AmdPcieSetup++;
                
                AmdPcieSetup->DeviceEnable = SetupData->Device1Enabled;
                AmdPcieSetup->DeviceAspmMode = SetupData->Device1AspmMode;
                AmdPcieSetup->DeviceHotPlug = SetupData->Device1HotPlugMode;
                AmdPcieSetup++;
                
                AmdPcieSetup->DeviceEnable = SetupData->Device2Enabled;
                AmdPcieSetup->DeviceAspmMode = SetupData->Device2AspmMode;
                AmdPcieSetup->DeviceHotPlug = SetupData->Device2HotPlugMode;
                AmdPcieSetup++;
                
                AmdPcieSetup->DeviceEnable = SetupData->Device3Enabled;
                AmdPcieSetup->DeviceAspmMode = SetupData->Device3AspmMode;
                AmdPcieSetup->DeviceHotPlug = SetupData->Device3HotPlugMode;
                AmdPcieSetup++;
                
                AmdPcieSetup->DeviceEnable = SetupData->Device4Enabled;
                AmdPcieSetup->DeviceAspmMode = SetupData->Device4AspmMode;
                AmdPcieSetup->DeviceHotPlug = SetupData->Device4HotPlugMode;
                AmdPcieSetup++;
                
                AmdPcieSetup->DeviceEnable = SetupData->Device5Enabled;
                AmdPcieSetup->DeviceAspmMode = SetupData->Device5AspmMode;
                AmdPcieSetup->DeviceHotPlug = SetupData->Device5HotPlugMode;
                AmdPcieSetup++;
                
                AmdPcieSetup->DeviceEnable = SetupData->Device6Enabled;
                AmdPcieSetup->DeviceAspmMode = SetupData->Device6AspmMode;
                AmdPcieSetup->DeviceHotPlug = SetupData->Device6HotPlugMode;
                AmdPcieSetup++;
                
                AmdPcieSetup->DeviceEnable = SetupData->Device7Enabled;
                AmdPcieSetup->DeviceAspmMode = SetupData->Device7AspmMode;
                AmdPcieSetup->DeviceHotPlug = SetupData->Device7HotPlugMode;

                AmdPcieSetup =  TempAmdPcieSetup;

                DxioTopologyTablePtr      = AmdCpmTablePpi->CommonFunction.GetTablePtr (AmdCpmTablePpi, CPM_SIGNATURE_DXIO_TOPOLOGY);
      
                DxioPort = &(DxioTopologyTablePtr->Port[0]);
                
                while(TRUE) {
                    if (DxioPort->EngineData.EngineType == DxioPcieEngine) {

                        if (AmdPcieSetup->DeviceEnable != 0xFF) {
                            DxioPort->Port.PortPresent = AmdPcieSetup->DeviceEnable;
                            if (AmdPcieSetup->DeviceEnable == 0) //DxioPortDisabled
                            {
                                DxioPort->Port.PortPresent = DxioPortDisabled;
                            }
                        }
                        
                        if (AmdPcieSetup->DeviceAspmMode != 0xFF) {
                            DxioPort->Port.LinkAspm = AmdPcieSetup->DeviceAspmMode;
                        }
                        
                        if (AmdPcieSetup->DeviceHotPlug != 0xFF) {
                            DxioPort->Port.LinkHotplug = AmdPcieSetup->DeviceHotPlug;
                        }
                         
                        PcieHob->AmdPcieDeviceList[Count].DeviceNumber   = DxioPort->Port.DeviceNumber;                   
                        PcieHob->AmdPcieDeviceList[Count].FunctionNumber = DxioPort->Port.FunctionNumber;                   
                        PcieHob->AmdPcieDeviceList[Count].LinkAspm       = DxioPort->Port.LinkAspm;                   
                        PcieHob->AmdPcieDeviceList[Count].LinkHotplug    = DxioPort->Port.LinkHotplug;                   
                        PcieHob->AmdPcieDeviceList[Count].PortPresent    = DxioPort->Port.PortPresent;
                         
                        DEBUG ((DEBUG_INFO|DEBUG_PLATFORM, "CRB  DxioPort->EngineData.EngineType = %x\n",DxioPort->EngineData.EngineType));
                        DEBUG ((DEBUG_INFO|DEBUG_PLATFORM, "CRB  DxioPort->DeviceNumber = %x\n",DxioPort->Port.DeviceNumber));
                        DEBUG ((DEBUG_INFO|DEBUG_PLATFORM, "CRB  DxioPort->FunctionNumber = %x\n",DxioPort->Port.FunctionNumber));
                        DEBUG ((DEBUG_INFO|DEBUG_PLATFORM, "CRB  DxioPort->Port.LinkAspm =%x \n",DxioPort->Port.LinkAspm));
                        DEBUG ((DEBUG_INFO|DEBUG_PLATFORM, "CRB  DxioPort->Port.LinkHotplug = %x\n",DxioPort->Port.LinkHotplug));
                        DEBUG ((DEBUG_INFO|DEBUG_PLATFORM, "CRB  DxioPort->Port.PortPresent = %x\n",DxioPort->Port.PortPresent));
                        DEBUG ((DEBUG_INFO|DEBUG_PLATFORM, "CRB  DxioPort->EngineData.StartLane = %x\n",DxioPort->EngineData.StartLane));
                        DEBUG ((DEBUG_INFO|DEBUG_PLATFORM, "CRB  DxioPort->EngineData.EndLane = %x\n",DxioPort->EngineData.EndLane));
                        
                        AmdPcieSetup++;
                        Count++;
                    }
                    if (DxioPort->Flags == DESCRIPTOR_TERMINATE_LIST) break; 
                    DxioPort++;
                }
                
                PcieHob->AmdPcieDeviceCount = Count; //update the total PCIE device
                
                DEBUG ((DEBUG_INFO|DEBUG_PLATFORM, "CRB  AmdPcieDeviceCount = %x\n",PcieHob->AmdPcieDeviceCount));
                
            }
        }
    }
    
    return EFI_SUCCESS;
}
