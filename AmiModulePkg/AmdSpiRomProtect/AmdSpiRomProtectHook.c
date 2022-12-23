//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2021, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


//**********************************************************************
/** @file AmdSpiRomProtectHook.c
    This file contains code for AMD SPI ROM Enable and Disable Protect hook.

**/
//**********************************************************************
//----------------------------------------------------------------------------
// Includes
// Statements that include other files
#include <AmdSpiRomProtect.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/PciLib.h>
#include <Library/IoLib.h>
//----------------------------------------------------------------------------
// Function Externs

//----------------------------------------------------------------------------
// Local prototypes

//----------------------------------------------------------------------------
// Local Variables

 volatile UINT8  *gSPIBASE = (UINT8*)(UINTN)SPI_BASE_ADDRESS;
 volatile UINT8  *gSBAOACBase = (UINT8*)(UINTN)SB_AOAC_BASE;
 
BOOLEAN IsWriteEnabled = FALSE;
UINT32  AOACx94BIT14;

typedef struct {
  OUT UINT32          EAX_Reg;                    ///< CPUID instruction result in EAX
  OUT UINT32          EBX_Reg;                    ///< CPUID instruction result in EBX
  OUT UINT32          ECX_Reg;                    ///< CPUID instruction result in ECX
  OUT UINT32          EDX_Reg;                    ///< CPUID instruction result in EDX
} CPUID_DATA;
//----------------------------------------------------------------------------
// Function Definitions


/**
    GetSpiProtectRule

    @param VOID
    @retval SpiProtectRule

**/
UINT8 GetSpiProtectRule(VOID)
{
    CPUID_DATA CpuId;
    UINT8 Family;
    UINT8 ExtFamily;
    UINT8 Model;
    UINT8 ExtModel;
   // UINT8 Stepping;
    UINT8 SpiProtectRule;
    
    AsmCpuid (
        0x80000001,
        &(CpuId.EAX_Reg),
        &(CpuId.EBX_Reg),
        &(CpuId.ECX_Reg),
        &(CpuId.EDX_Reg)
        );
    Family    = (UINT8) (CpuId.EAX_Reg >> 8) & 0xF;   // bit 11:8
    ExtFamily = (UINT8) (CpuId.EAX_Reg >> 20) & 0xFF; // bit 27:20
    Model     = (UINT8) (CpuId.EAX_Reg >> 4) & 0xF;   // bit 7:4
    ExtModel  = (UINT8) (CpuId.EAX_Reg >> 16) & 0xF;  // bit 19:16
    //Stepping  = (UINT8) (CpuId.EAX_Reg >> 0) & 0xF;   // bit 3:0  
    
    SpiProtectRule = 3;         //assume use SSP,CP,MTS,RN and latest CPU.
    
    if ((Family == 0xF) && (ExtFamily == 0x8) && (ExtModel < 0x3)) {
        //PCO, RV2,RV,Pinnacle, SM, TR ,CF.
        SpiProtectRule = 2;
    } 

    if ((Family == 0xF) && (ExtFamily == 0x6) && ((ExtModel == 0x7) || ((ExtModel == 0x6) && (Model == 0x5)))) {
      //BR and ST
        SpiProtectRule = 1;
    } 
    if ((Family == 0xF) && (ExtFamily == 0x6) && (ExtModel == 0x6)) {
      //CZ
        SpiProtectRule = 1;
    }  
    
    if ((Family == 0xF) && (ExtFamily == 0x7) && (ExtModel == 0x3)) {
         //CZL, ML
           SpiProtectRule = 1;
    }     
    
    if ((Family == 0xF) && (ExtFamily <= 0x6) && (ExtModel < 0x6)) {
       //KV CPU and old CPU.
         SpiProtectRule = 0;
     }  
    
    DEBUG ((DEBUG_INFO, "SpiProtectRule is %x.\n", SpiProtectRule));   
    
    return SpiProtectRule;                      /*
                                                    SpiProtectRule = 0 : Not support program LPC 0x50-0x5F, Not program Spi 0x1D (SB800, Bolton SB)
                                                    SpiProtectRule = 1 : support program LPC 0x50-0x5F , Not program Spi 0x1D , (CZ,BR,ST)
                                                    SpiProtectRule = 2 : support program LPC 0x50-0x5F, program Spi 0x1D. For CPU Not support 24bit/32bit SPI address mode case.
                                                                                                                           (SM,RV1,RV2,Pinnacle, Zen Core)
                                                    SpiProtectRule = 3 : support program LPC 0x50-0x5F, program Spi 0x1D. For CPU support 24bit/32bit SPI address mode case.
                                                                                                                            (SSP, Mts,CP and latest CPU.)
                                                */
    
}



/**
    LpcProtectModeInit

    @param VOID
    @retval VOID

**/

#if  defined LPC50_5C_ROM_PROTECT && LPC50_5C_ROM_PROTECT == 1
VOID  LpcProtectModeInit(VOID)
{
    UINT32 LPCRomProtect0Value = 0;
    UINT32 LPCRomProtect1Value = 0;
    UINT32 LPCRomProtect2Value = 0;
    UINT32 LPCRomProtect3Value = 0;
    
#if LPCREG50_PROTECT_VALUE == 0 &&  LPCREG54_PROTECT_VALUE == 0 && LPCREG58_PROTECT_VALUE == 0 && LPCREG5C_PROTECT_VALUE == 0 
//PCO, RV2,RV,Pinnacle, SM, TR ,CF only 24bit(gSPIBASE + 0x50[0] = 0).   
    if (*(volatile UINT8*)( gSPIBASE + 0x50) & BIT0){
     //32bit case:     
    LPCRomProtect0Value =  0xFF0005FF;
    LPCRomProtect1Value =  0xFC0005FF;
    LPCRomProtect2Value =  0xFE0005FF;
    LPCRomProtect3Value =  0xFD0005FF;
    }else{
//For indirect write, Host address will reserve add[25,24] = 00b, so we need to enable protect range 0xFC000000-0xFCFFFFFF(it only takes [23:0], 
//higher bits is ignored) in 24 bit addressing mode(High 6 bits is unnecessary).
      LPCRomProtect0Value =  0xFC0005FF;   
    }
#else
    LPCRomProtect0Value =  LPCREG50_PROTECT_VALUE;
    LPCRomProtect1Value =  LPCREG54_PROTECT_VALUE;
    LPCRomProtect2Value =  LPCREG58_PROTECT_VALUE;
    LPCRomProtect3Value =  LPCREG5C_PROTECT_VALUE;
#endif    
      
       PciWrite32 (PCI_LIB_ADDRESS(SB_LPC_BUS, SB_LPC_DEV, SB_LPC_FUNC, LPCRomProtect0), LPCRomProtect0Value);
       PciWrite32 (PCI_LIB_ADDRESS(SB_LPC_BUS, SB_LPC_DEV, SB_LPC_FUNC, LPCRomProtect1), LPCRomProtect1Value);
       PciWrite32 (PCI_LIB_ADDRESS(SB_LPC_BUS, SB_LPC_DEV, SB_LPC_FUNC, LPCRomProtect2), LPCRomProtect2Value);
       PciWrite32 (PCI_LIB_ADDRESS(SB_LPC_BUS, SB_LPC_DEV, SB_LPC_FUNC, LPCRomProtect3), LPCRomProtect3Value);
    
        
}
#endif 

/**
    This function returns SMI state
              
    @param VOID

    @retval TRUE SMI enabled, FALSE - otherwise

    @note  This function must work at runtime. Do not use boot time services/protocols

**/
BOOLEAN SpiProtectGetSbSmiState(
    VOID
)
{

    BOOLEAN     IsSmiEn=FALSE;
#if SMM_SUPPORT
    UINT8   Buffer;
    Buffer = MmioRead8((UINTN)(SB_SMI_BASE + SmiReg98 + 3));
    if (!(Buffer & BIT7)) IsSmiEn = TRUE; // Yes, Global was enabled.
#endif // #if SMM_SUPPORT
    return IsSmiEn;

}

/**
    This function disables SMI
              
    @param VOID

    @retval VOID

    @note  This function should be used ONLY in critical parts of code
           This function must work at runtime. Do not use boot time services/protocols

**/
VOID SpiprotectSbSmiDisable(
    VOID
)
{
    

#if SMM_SUPPORT
    // Disable SMICmdPort
    MmioAndThenOr8((UINTN)(SB_SMI_BASE + SmiRegB2), (UINT8)~BIT6, 0);
    // Disable Global SMI
     MmioAndThenOr8((UINTN)(SB_SMI_BASE + SmiReg98 + 3), (UINT8)~BIT7, (UINT8)BIT7);      
#endif


}

/**
    This function enables SMI
              
    @param VOID

    @retval VOID

    @note  This function should be used ONLY in critical parts of code
           This function must work at runtime. Do not use boot time services/protocols

**/
VOID SpiprotectSbSmiEnable(
    VOID
)
{

    
#if SMM_SUPPORT
    // Enable SMICmdPort
    MmioAndThenOr8((UINTN)(SB_SMI_BASE + SmiRegB2), (UINT8)~BIT6, (UINT8)BIT6);
    // Enable Global SMI
    MmioAndThenOr8((UINTN)(SB_SMI_BASE + SmiReg98 + 3), (UINT8)~BIT7, 0); 
#endif // #if SMM_SUPPORT

    
}



/**
    Spi Rom Protect Enable Hook

    @param VOID
    @retval VOID

**/
VOID AmdSpiRomProtectWriteEnable (VOID)
{

    UINT8           Data, IsSmiEnabled;

    if ((*(gSPIBASE + SPIRestrictedCmd2Reg) != SPIRestrictedCmdValue) || (*(gSPIBASE + 2) & (BIT7 | BIT6))) return;
    IsWriteEnabled = TRUE;    
       IsSmiEnabled = SpiProtectGetSbSmiState();
    // AMD Specification - To enable SpiHostAccesRomEn bit, the Global SMI 
    // MUST be enable state.   
       if (!IsSmiEnabled) SpiprotectSbSmiEnable();
    //If AOAC 0x94[14]=1 will make SPI_BASE[22:23] can't unlock, so clear AOAC 0x94[14]=0 if we found it is 1,

       AOACx94BIT14 = *(volatile UINT32*)(gSBAOACBase + AOACReg94) & (BIT14);              
       if (AOACx94BIT14 != 0) {       
           DEBUG ((DEBUG_INFO, "Found AOAC94 bit14 is enable, AOACReg94 data = %x\n",*(volatile UINT32*)(gSBAOACBase + AOACReg94))); 
           *(volatile UINT32*)(gSBAOACBase + AOACReg94) &=  ~(BIT14);
       }

#if  defined LPC50_5C_ROM_PROTECT && LPC50_5C_ROM_PROTECT == 1
       
       {  //clear all LPC protect setting.
          UINT8 i;              
          for (i = LPCRomProtect0; i <= LPCRomProtect3 ; i = i + 4)    PciWrite32 (PCI_LIB_ADDRESS(SB_LPC_BUS, SB_LPC_DEV, SB_LPC_FUNC, i), 0x0);
       }
     
     if (GetSpiProtectRule() >= 2){
         Data = *(gSPIBASE + SPIMMIOReg1D);
         Data = Data & ~BIT5;
         *(gSPIBASE + SPIMMIOReg1D) = Data;
         Data = Data & ~BIT3;
         //cppcheck-suppress redundantAssignment 
         *(gSPIBASE + SPIMMIOReg1D) = Data;
     }
     

#endif
    Data = *(volatile UINT8*)(gSPIBASE + 2) | (BIT7 | BIT6);    
    *(volatile UINT8*)(gSPIBASE + 2) = Data;
    *(gSPIBASE + SPIRestrictedCmd2Reg) = 0;    
    DEBUG ((DEBUG_INFO, "AmdSpiRomProtectWriteEnable. ROM had unlock.\n"));   
       if (!IsSmiEnabled) SpiprotectSbSmiDisable();

    
}
/**
    Spi Rom Protect Disable Hook.

    @param VOID
    @retval VOID

**/
VOID AmdSpiRomProtectWriteDisable (VOID)
{

    UINT8           Data;
#if defined LPC50_5C_ROM_PROTECT && LPC50_5C_ROM_PROTECT == 1
        UINT8           IsSmiEnabled;
#endif    


#if defined LPC50_5C_ROM_PROTECT && LPC50_5C_ROM_PROTECT == 1
    if (!IsWriteEnabled || !(*(gSPIBASE + 2) & (BIT7 | BIT6))) return;
    IsWriteEnabled = FALSE;  
       IsSmiEnabled = SpiProtectGetSbSmiState();
       if (!IsSmiEnabled) SpiprotectSbSmiEnable();
    *(gSPIBASE + SPIRestrictedCmd2Reg) = SPIRestrictedCmdValue;    
    Data = *(gSPIBASE + 2) & ~(BIT7 | BIT6);    
    *(gSPIBASE + 2) = Data;
  
    
    if (GetSpiProtectRule() >= 2){
        Data = *(gSPIBASE + SPIMMIOReg1D);
        Data = Data | BIT3;
           *(gSPIBASE + SPIMMIOReg1D) = Data;
           Data = Data | BIT5;
           //cppcheck-suppress redundantAssignment
          *(gSPIBASE + SPIMMIOReg1D) = Data;
    }
        
    LpcProtectModeInit();
    
        if (!IsSmiEnabled) SpiprotectSbSmiDisable();
#else
    if (!IsWriteEnabled || !(*(gSPIBASE + 2) & (BIT7 | BIT6))) return;
    IsWriteEnabled = FALSE;    
    *(gSPIBASE + SPIRestrictedCmd2Reg) = SPIRestrictedCmdValue;    
    Data = *(gSPIBASE + 2) & ~(BIT7 | BIT6);    
    *(gSPIBASE + 2) = Data;


#endif   
    
    //We need restore AOAC 0x94[14]=1 if it is 1 in AmdSpiRomProtectWriteEnable.

    if (AOACx94BIT14 != 0) {            
        *(volatile UINT32*)(gSBAOACBase + AOACReg94) |= (BIT14);
         DEBUG ((DEBUG_INFO, "AmdSpiRomProtectWriteDisable- Found AOAC94_b14 is 1 in AmdSpiRomProtectWriteEnable and must rollback it to 1 now \n"));     
    }
    
    DEBUG ((DEBUG_INFO, "AmdSpiRomProtectWriteDisable.ROM had lock\n"));   

}

