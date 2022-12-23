//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

//**********************************************************************
/** @file AmdSpiRomProtectDxe.c
    This file contains code for AMD SPI ROM Protect DXE entrypoint

**/

//----------------------------------------------------------------------------
// Includes
// Statements that include other files
#include <AmiDxeLib.h>
#include <AmiCspLib.h>
#include <AmdSpiRomProtect.h>
#include <Library/DebugLib.h>


//----------------------------------------------------------------------------
// Function Externs
extern UINT8  GetSpiProtectRule(VOID);
extern VOID   LpcProtectModeInit(VOID);

//----------------------------------------------------------------------------
// Local prototypes

//----------------------------------------------------------------------------
// Local Variables

#define BDS_CONNECT_DRIVERS_PROTOCOL_GUID \
{0x3aa83745, 0x9454, 0x4f7a, 0xa7, 0xc0, 0x90, 0xdb, 0xd0, 0x2f, 0xab, 0x8e}
EFI_GUID  gBdsConnectDriversProtocolGuid = BDS_CONNECT_DRIVERS_PROTOCOL_GUID;



EFI_EVENT gEvtSpiProtect; 
EFI_EVENT gRegSpiProtect; 

EFI_S3_SAVE_STATE_PROTOCOL     	static	*gBootScriptSave = NULL;

#ifndef CSP_BOOT_SCRIPT_SERVICE_EX
#define CSP_BOOT_SCRIPT_SERVICE_EX(macroService) (macroService)
#endif

extern EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL  *gPciRootBridgeIo;

typedef struct {
    union {
        UINT64                  Address;
        struct {
            UINT64 CONST    Reg : 8;
            UINT64 CONST    Fun : 8;
            UINT64 CONST    Dev : 8;
            UINT64          Bus : 8;
            UINT64 CONST    Reserved : 32;
        } Addr;
    };
    EFI_BOOT_SCRIPT_WIDTH   Width;
} BOOT_SCRIPT_PCI_REGISTER_SAVE;


BOOT_SCRIPT_PCI_REGISTER_SAVE gFchPciRegScriptTbl[] = {
    
    SB_REG(LPCRomProtect0),  EfiBootScriptWidthUint32,
    SB_REG(LPCRomProtect1),  EfiBootScriptWidthUint32,
    SB_REG(LPCRomProtect2),  EfiBootScriptWidthUint32,
    SB_REG(LPCRomProtect3),  EfiBootScriptWidthUint32,
};
UINTN gFchPciRegScriptSize = \
        sizeof(gFchPciRegScriptTbl) / sizeof(BOOT_SCRIPT_PCI_REGISTER_SAVE);

//----------------------------------------------------------------------------
// Function Definitions

/**
    This function returns ROM Armor States.
              
    @param VOID

    @retval TRUE Rom Armor Enable, FALSE - otherwise

    

**/
BOOLEAN CheckRomArmor(
    VOID
)
{
    
    UINT8   i, Memdata;       
    BOOLEAN IsRomArmor;
   
   //Must check Rom Armor2 first.
    
#if  defined AMD_PSP_ROM_ARMOR2_SMM_SUPPORT && AMD_PSP_ROM_ARMOR2_SMM_SUPPORT == 1      
        if (PcdGetBool(PcdAmdPspRomArmor2Enabled)){
            return TRUE;                                     
        }
#endif
  //Check SPI controller space health (Rom Armor1)
        IsRomArmor = TRUE;
            i = 0;
            do{
                Memdata = MmioRead8((UINTN)(SPI_BASE_ADDRESS + i)); 
                if ( Memdata  != 0xFF){
                    IsRomArmor = FALSE;
                    break;
                }    
               i++;
            }while(i < 0x10);    
    
    
    return IsRomArmor;
    
}



/**
    Prepare to for Boot ROM Protect event.

        
    @param VOID

         
    @retval VOID

**/
VOID
EFIAPI
PrepareToBootRomProtectCallBack (
    IN EFI_EVENT        Event, 
    IN VOID             *Context
)
{
        EFI_STATUS    Status; 
        UINT8           Data;
        UINT32          Buffer;
#if  defined LPC50_5C_ROM_PROTECT && LPC50_5C_ROM_PROTECT == 1 
        UINT8           i;        
#endif                        
    volatile UINT8  *SpiBase = (UINT8*)(UINTN)SPI_BASE_ADDRESS;
//Don't touch SPI controller register for Spi protect if AMD Rom Armor states is enable.
  if (!CheckRomArmor()){  
    *(SpiBase + SPIRestrictedCmd2Reg) = SPIRestrictedCmdValue;
    *(volatile UINT32*)SpiBase = *(volatile UINT32*)SpiBase & ~(BIT23 + BIT22);

    //
#if  defined LPC50_5C_ROM_PROTECT && LPC50_5C_ROM_PROTECT == 1
    
    if (GetSpiProtectRule() >= 2){
    //according AMD PPR, Bit3,4 can't change if bit5 is enable with SPI_0x1D,so set bit step by step. 
           Data = *(SpiBase + SPIMMIOReg1D) | BIT3;
           *(SpiBase + SPIMMIOReg1D) = Data;
           Data = *(SpiBase + SPIMMIOReg1D) | BIT5;
           *(SpiBase + SPIMMIOReg1D) = Data;                                       
    }

    LpcProtectModeInit();    
#endif 
    
    if(gBootScriptSave == NULL) {
	        Status = pBS->LocateProtocol(&gEfiS3SaveStateProtocolGuid,NULL, \
	                    &gBootScriptSave);
	        
                 if(!EFI_ERROR(Status)) {                
                       Data = READ_MEM8(SPI_BASE_ADDRESS + SPIRestrictedCmd2Reg);
                       WRITE_MEM8_S3(gBootScriptSave, SPI_BASE_ADDRESS + SPIRestrictedCmd2Reg, Data);

                       Buffer = READ_MEM32(SPI_BASE_ADDRESS);
                       WRITE_MEM32_S3(gBootScriptSave, SPI_BASE_ADDRESS, Buffer);      
                   
#if  defined LPC50_5C_ROM_PROTECT && LPC50_5C_ROM_PROTECT == 1 
    if (GetSpiProtectRule() >= 2){
        Data = READ_MEM8(SPI_BASE_ADDRESS + SPIMMIOReg1D);
        WRITE_MEM8_S3(gBootScriptSave, SPI_BASE_ADDRESS + SPIMMIOReg1D, Data);
    }
                    //save LPC 50 - 5F register 
                    Status = pBS->LocateProtocol(&gEfiPciRootBridgeIoProtocolGuid, NULL, \
                                                 &gPciRootBridgeIo);
                    ASSERT_EFI_ERROR(Status);
            
                     for (i = 0; i < gFchPciRegScriptSize; i++) {
                             gPciRootBridgeIo->Pci.Read(
                                               gPciRootBridgeIo,
                                               gFchPciRegScriptTbl[i].Width,
                                               gFchPciRegScriptTbl[i].Address,
                                               1,
                                               &Buffer);

                                 BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
                                               CSP_BOOT_SCRIPT_SERVICE_EX(gBootScriptSave),
                                               gFchPciRegScriptTbl[i].Width,
                                               gFchPciRegScriptTbl[i].Address,
                                               1,
                                               &Buffer);
                      }
#endif                     
            
                   }
       }

 }
    pBS->CloseEvent(Event);
}


/**
    AmdSpiRomProtect DXE Function

        
    @param VOID

         
    @retval VOID

**/
EFI_STATUS 
EFIAPI
AmdSpiRomProtectEnteyDxePoint(
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
     EFI_STATUS  Status = EFI_SUCCESS;
     InitAmiLib (ImageHandle, SystemTable);     
     

         
#if  (ROM_PROTECT_PHASE == 0)
    Status = RegisterProtocolCallback ( &gBdsConnectDriversProtocolGuid, \
                                        PrepareToBootRomProtectCallBack, \
                                        NULL, \
                                        &gEvtSpiProtect, \
                                        &gRegSpiProtect );
#endif

#if (ROM_PROTECT_PHASE == 1)
     Status = RegisterProtocolCallback ( &gBdsAllDriversConnectedProtocolGuid, \
                                        PrepareToBootRomProtectCallBack, \
                                        NULL, \
                                        &gEvtSpiProtect, \
                                        &gRegSpiProtect );
#endif

#if (ROM_PROTECT_PHASE == 2)
     Status = CreateReadyToBootEvent(TPL_NOTIFY, PrepareToBootRomProtectCallBack, NULL, &gEvtSpiProtect);

#endif
          
    return Status;
 
}

