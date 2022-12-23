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

#include <AmiLib.h>
#include <AcpiRes.h>
#include <Setup.h>

#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Acpi50.h>
#include <Dxe/AmdPbsSetupDxe/AmdPbsConfig.h>
#include <Library/AmdPbsConfigLib/AmdPbsConfigLib.h>
#include <IndustryStandard/Acpi.h>
#include <Protocol/AcpiSystemDescriptionTable.h>
#include <Protocol/AcpiTable.h>

#include <Library/AmiFchIoAccessLib.h>
#include <AgesaModulePkg/Fch/Sandstone/FchSandstoneCore/Fch.h> 


/**
  Callback function executed when the Exit Boot Service event group is signaled.

  @param[in] Event      Event whose notification function is being invoked.
  @param[in] Context    The pointer to the notification function's context, which
                        is implementation-dependent.
**/
VOID
EFIAPI
MsBootOnExitBootService (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
{
	// Clear Smicontrol51 
    AmdFchMmioAndThenOr8 (AMD_FCH_SMI_MMIO, FCH_SMI_REGAC, ~(BIT6+BIT7)  , 0);  
    gBS->CloseEvent(Event);
}
/**
  Callback function executed when the EndOfDxe event group is signaled.

  @param[in] Event      Event whose notification function is being invoked.
  @param[in] Context    The pointer to the notification function's context, which
                        is implementation-dependent.
**/
VOID
EFIAPI
AmiUpdateFacpTable (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
{
    EFI_STATUS                    Status = EFI_SUCCESS;
    EFI_ACPI_TABLE_PROTOCOL       *gAcpiTable = NULL;
    EFI_ACPI_SDT_PROTOCOL         *gAcpiSdtProtocol = NULL;
    EFI_ACPI_SDT_HEADER           *Table = NULL;
    PFACP_50                      FadtPointer = NULL;
    AMD_PBS_SETUP_OPTION          AmdPbsConfiguration;
    UINTN                         Handle = 0;
    UINTN                         Index = 0;
    EFI_ACPI_TABLE_VERSION        Version;
    EFI_ACPI_TABLE_VERSION        DoneVersion[2] = {0, 0};
    EFI_GUID                      SetupGuid = SETUP_GUID;
    UINTN                         SetupDataSize = sizeof(SETUP_DATA);    
    SETUP_DATA                    SetupData;
    UINT32                        Attributes;
    
    Status = gBS->LocateProtocol(&gEfiAcpiTableProtocolGuid, NULL, &gAcpiTable);
    if (!EFI_ERROR(Status)) {
        Status = gBS->LocateProtocol(&gEfiAcpiSdtProtocolGuid, NULL, &gAcpiSdtProtocol);
        if (!EFI_ERROR(Status)) {
            do {
                  Status = gAcpiSdtProtocol->GetAcpiTable(Index, &Table, &Version, &Handle);
                  if (Status == EFI_NOT_FOUND){
                      DEBUG((DEBUG_INFO, "AcpiPlatform: Not Found FACP table breaking search loop...\n"));
                      break;
                  }
                  if (Table->Signature == FACP_SIG){
                      DEBUG((DEBUG_INFO, "AcpiPlatform: Find FACP table version:%x | Handle: %x\n", Table->Revision, Handle));
                      FadtPointer = (PFACP_50) Table;
                      Status = GetAmdPbsConfiguration(&AmdPbsConfiguration);
                      
                      Status = gRT->GetVariable(
                                              L"Setup", 
                                              &SetupGuid, 
                                              &Attributes, 
                                              &SetupDataSize, 
                                              &SetupData);
                       if (PcdGetBool(PcdModernStandbyEnable)){
                              FadtPointer->FLAGS |= BIT21;
                              FadtPointer->IAPC_BOOT_ARCH |= BIT0;         
                              SetupData.AcpiSleepState = 0;  // do not support s3    
                      } else {
                              FadtPointer->FLAGS &=~BIT21;
                              SetupData.AcpiSleepState = 2;  // support s3
                      }
                          
                      Status = gRT->SetVariable(
                                              L"Setup", 
                                              &SetupGuid,
                                              Attributes,
                                              SetupDataSize, 
                                              &SetupData);                   

                      if (PcdGetBool(PcdReduceHardwareEnable)){
                              FadtPointer->FLAGS |= BIT20; // Set HW_REDUCED_ACPI flag
                              FadtPointer->FLAGS |= BIT4;  // Set PWR_BUTTON flag to 1 to use Control method power button
                              FadtPointer->FLAGS &=~BIT14; // PCI_EXP_WAK = 0
                      } else {
                              FadtPointer->FLAGS &=~BIT20; // Reset HW_REDUCED_ACPI flag
                              FadtPointer->FLAGS &=~BIT4;  // Set PWR_BUTTON flag to 0 to use Fixed hardware power button
                              FadtPointer->FLAGS |= BIT14; // PCI_EXP_WAK = 1
                      }

                      if ((Table->Revision == EFI_ACPI_TABLE_VERSION_1_0B && DoneVersion[0] == 0) || 
                          (Table->Revision != EFI_ACPI_TABLE_VERSION_1_0B && DoneVersion[1] == 0))
                      {
                           if (Table->Revision == EFI_ACPI_TABLE_VERSION_1_0B) DoneVersion[0] = 1;
                           if (Table->Revision != EFI_ACPI_TABLE_VERSION_1_0B) DoneVersion[1] = 1;
                           
                           //
                           // Remove previous table
                           //                 
                           Status = gAcpiTable->UninstallAcpiTable (gAcpiTable,
                                                                    Handle );                                   
                           //
                           // Add new table
                           //
                           Handle = 0;
                           
                           Status = gAcpiTable->InstallAcpiTable (gAcpiTable,
                                                                  Table,
                                                                  Table->Length,
                                                                  &Handle );
                           Index = 0;
                      } else 
                           Index++;
                                          
                      if (DoneVersion[0] && DoneVersion[1]) break;
           
                  } else Index++;
            } while(1);
        }
    }

    
    Status = gBS->CloseEvent (Event);

    return;
}

/**
    This function  is a ready to boot event function ,it will did it
    when ready to boot

    @param Event 
    @param Context 

    @retval VOID

**/
VOID 
AmiMsUpdateAsl(
    IN EFI_EVENT Event, 
    IN VOID *Context
)
{
    EFI_STATUS                  Status;
    EFI_PHYSICAL_ADDRESS        Dsdtaddr = 0;
    UINT8                      *Pointer = NULL;
    ACPI_HDR                   *Dsdt;
    AMD_PBS_SETUP_OPTION        AmdPbsSetup;
    UINT32                      MmioAddr;                 
    
    Status = LibGetDsdt(&Dsdtaddr, EFI_ACPI_TABLE_VERSION_ALL);
    
    Dsdt = (ACPI_HDR*)Dsdtaddr;
    
    Status = GetAmdPbsConfiguration(&AmdPbsSetup);
    if(!EFI_ERROR(Status)){
            // Update GPP2 mmio address
          MmioAddr = PCIEX_BASE_ADDRESS + 0xB000;  // bus 0 dev 1 fun 3
          UpdateAslNameObject((ACPI_HDR*)Dsdtaddr, "CRBB", MmioAddr);
          
    	  if (PcdGetBool(PcdReduceHardwareEnable)){
            // Power button SMI disabled
            AmdFchMmioAndThenOr8 (AMD_FCH_SMI_MMIO, FCH_SMI_REGAC, ~(BIT4+BIT5)  , 0);  // Clear Smicontrol50 
            AmdFchMmioAndThenOr32(AMD_FCH_SMI_MMIO, FCH_SMI_REGB0, ~(BIT20+BIT21), 0);  // Clear Smicontrol74 
            // Update RDHW asl value to 1
            UpdateAslNameObject((ACPI_HDR*)Dsdtaddr, "RDHW", 1);
            
            // Update _PRW ASL method to RHRW
            do{
                Pointer = FindAslObjectName((UINT8*)Dsdt+sizeof(ACPI_HDR),"_PRW",Dsdt->Length-sizeof(ACPI_HDR)-1);
                if (Pointer!=NULL){             
                    DEBUG(( DEBUG_INFO," Mandolin update Object name  %c%c%c%c  to",Pointer[0],Pointer[1],Pointer[2],Pointer[3]));
                    Pointer[0]='R';  //RHRW
                    Pointer[1]='H';  //RHRW
                    DEBUG(( DEBUG_INFO,"  %c%c%c%c  \n",Pointer[0],Pointer[1],Pointer[2],Pointer[3]));
                }
            }while(Pointer);
            
            // Update MPRW ASL method for hardware-reduce and power manager  
            //do{
            //    Pointer = FindAslObjectName((UINT8*)Dsdt+sizeof(ACPI_HDR),"MPRW",Dsdt->Length-sizeof(ACPI_HDR)-1);
            //    if (Pointer!=NULL){             
            //        DEBUG(( DEBUG_INFO," Mandolin update Object name  %c%c%c%c  to",Pointer[0],Pointer[1],Pointer[2],Pointer[3]));
            //        Pointer[0]='_';  //_PRW
            //        DEBUG(( DEBUG_INFO,"  %c%c%c%c  \n",Pointer[0],Pointer[1],Pointer[2],Pointer[3]));
            //   }
            //}while(Pointer);
            
            // Update RHRS ASL method to _CRS
            do{
                Pointer = FindAslObjectName((UINT8*)Dsdt+sizeof(ACPI_HDR),"RHRS",Dsdt->Length-sizeof(ACPI_HDR)-1);
                if (Pointer!=NULL){             
                    DEBUG(( DEBUG_INFO," Mandolin update Object name  %c%c%c%c  to",Pointer[0],Pointer[1],Pointer[2],Pointer[3]));
                    Pointer[0]='_';  //_CRS
                    Pointer[1]='C';  //_CRS
                    DEBUG(( DEBUG_INFO,"  %c%c%c%c  \n",Pointer[0],Pointer[1],Pointer[2],Pointer[3]));
                }
            }while(Pointer);            
                                    
        } else 
        {
            // Update EC _GPE name for non hw-reduce
            Pointer = FindAslObjectName((UINT8*)Dsdt+sizeof(ACPI_HDR),"XGPE",Dsdt->Length-sizeof(ACPI_HDR)-1);
            if (Pointer!=NULL){
                
                DEBUG(( DEBUG_INFO," Mandolin update Object name  %c%c%c%c  to",Pointer[0],Pointer[1],Pointer[2],Pointer[3]));
                Pointer[0]='_';
                DEBUG(( DEBUG_INFO,"  %c%c%c%c  \n",Pointer[0],Pointer[1],Pointer[2],Pointer[3]));
            } 

        }
        if (PcdGetBool(PcdModernStandbyEnable)){
        	  // Update CNSB asl value to 1
            UpdateAslNameObject((ACPI_HDR*)Dsdtaddr, "CNSB", 1);
        }
        
        if (AmdPbsSetup.WakeOnPME == 0 && AmdPbsSetup.ReduceHardwareEn == 0) { 
                        
            // Update _PRW ASL method to RHRW
            do{
                Pointer = FindAslObjectName((UINT8*)Dsdt+sizeof(ACPI_HDR),"_PRW",Dsdt->Length-sizeof(ACPI_HDR)-1);
                if (Pointer!=NULL){             
                    DEBUG(( DEBUG_INFO," Mandolin update Object name  %c%c%c%c  to",Pointer[0],Pointer[1],Pointer[2],Pointer[3]));
                    Pointer[0]='R';  //RHRW
                    Pointer[1]='H';  //RHRW
                    DEBUG(( DEBUG_INFO,"  %c%c%c%c  \n",Pointer[0],Pointer[1],Pointer[2],Pointer[3]));
                }
            }while(Pointer);
            
            // Update MPRW ASL method for hardware-reduce and power manager  
            do{
                Pointer = FindAslObjectName((UINT8*)Dsdt+sizeof(ACPI_HDR),"MPRW",Dsdt->Length-sizeof(ACPI_HDR)-1);
                if (Pointer!=NULL){             
                    DEBUG(( DEBUG_INFO," Mandolin update Object name  %c%c%c%c  to",Pointer[0],Pointer[1],Pointer[2],Pointer[3]));
                    Pointer[0]='_';  //_PRW
                    DEBUG(( DEBUG_INFO,"  %c%c%c%c  \n",Pointer[0],Pointer[1],Pointer[2],Pointer[3]));
                }
            }while(Pointer);
        }
        
        Dsdt->Checksum = 0;
        Dsdt->Checksum = ChsumTbl((UINT8*)Dsdt, Dsdt->Length);
    }

    // Close Event and don't run it again
    gBS->CloseEvent(Event);
}

/**
   The entry function of the modern standby platform driver.

   This function updates facp and asl code for modern standby .

   @param[in] ImageHandle  The firmware allocated handle for the EFI image.
   @param[in] SystemTable  A pointer to the EFI System Table.

   @retval EFI_SUCCESS     The entry point is executed successfully.
   @retval other           Some error occurs when executing this entry point.

**/
EFI_STATUS
EFIAPI
CrbMsInit (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
    EFI_STATUS    Status;
    EFI_EVENT     EndOfDxeEvent;
    EFI_EVENT     EventUpdateAsl;  
    EFI_EVENT     ExitBootServiceEvent;
    
    InitAmiLib(ImageHandle, SystemTable);
            
    Status = gBS->CreateEventEx (
                        EVT_NOTIFY_SIGNAL,
                        TPL_CALLBACK,
                        AmiUpdateFacpTable,
                        NULL,
                        &gEfiEndOfDxeEventGroupGuid,
                        &EndOfDxeEvent
                        );    
    
    Status = EfiCreateEventReadyToBootEx(TPL_NOTIFY, AmiMsUpdateAsl, NULL, &EventUpdateAsl);        
    
    if (PcdGetBool(PcdReduceHardwareEnable)){
    	
        Status = gBS->CreateEvent (EVT_SIGNAL_EXIT_BOOT_SERVICES, TPL_CALLBACK, MsBootOnExitBootService,
                              (VOID *)TRUE, &ExitBootServiceEvent);
    }
    return Status;
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
