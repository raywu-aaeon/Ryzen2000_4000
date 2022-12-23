//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************


/** @file PeiCpuCache.c
    These functions in this file controls the cache in PEI.

**/


#include "CpuPei.h"
#include "CpuCspLib.h"
#include <AmiPeiLib.h>
#include <Token.h>
typedef struct {
    UINT8   Register;
    UINT8   Function;
    UINT8   Device;
    UINT8   Bus;
    UINT32  ExtendedRegister;
} EFI_PCI_CONFIGURATION_ADDRESS;

extern VOID	DisableCpuCar(VOID);
/**
    AMD PciConfig Write function....Writes Normal and Extended PCI space

        
    @param Address 
    @param Value 
    @param ExtAccess 

         
    @retval VOID

**/

VOID
AMDPciConfigWrite(
    IN UINT32 Address,
    IN UINT32 Value,
    IN BOOLEAN ExtAccess)
{
    UINT32  PciAddress = (1 << 31) +
        (((EFI_PCI_CONFIGURATION_ADDRESS*) &Address)->Bus      << 16 )  +
        (((EFI_PCI_CONFIGURATION_ADDRESS*) &Address)->Device   << 11 )  +
        (((EFI_PCI_CONFIGURATION_ADDRESS*) &Address)->Function << 8  )  +
        (((EFI_PCI_CONFIGURATION_ADDRESS*) &Address)->Register       );
    //Dword align
    PciAddress = PciAddress & 0xfffffffc;

    if(ExtAccess)       //If extended config Access requested then add the extended config address  bit (24 to 27)
        PciAddress = PciAddress | 0x1000000;
    IoWrite32(0xcf8, PciAddress);   // Select the register to write
    IoWrite32(0xcfc, Value);        // Write the Value
}

/**
    AMD PciConfig read function....Reads Normal and Extended PCI space

        
    @param Address 
    @param ExtAccess 

         
    @retval UINT32 Value

**/

UINT32
AMDPciConfigRead(
    IN UINT32 Address,
    IN BOOLEAN ExtAccess)
{
    UINT32  PciAddress = (1 << 31) +
        (((EFI_PCI_CONFIGURATION_ADDRESS*) &Address)->Bus      << 16 )  +
        (((EFI_PCI_CONFIGURATION_ADDRESS*) &Address)->Device   << 11 )  +
        (((EFI_PCI_CONFIGURATION_ADDRESS*) &Address)->Function << 8  )  +
        (((EFI_PCI_CONFIGURATION_ADDRESS*) &Address)->Register       );

    PciAddress = PciAddress & 0xFFFFFFFC; //Dword Align

    if(ExtAccess) //If extended config Access requested then add the extended config address  bit (24 to 27)
        PciAddress = PciAddress | 0x1000000;

    IoWrite32(0xCF8, PciAddress);
    return IoRead32(0xCFC);         //Return the read value
}

#define CPU_PCI_CFG_ADDRESS(bus, dev, func, reg)   \
 ((UINT64) ( (((UINTN)bus) << 24) + (((UINTN)dev) << 16) + (((UINTN)func) << 8) + ((UINTN)reg) )) & 0x00000000ffffffff

#define AGESA_PCI_CFG_ADDRESS(bus, dev, func, reg) \
         (UINT32)( (UINT64)CPU_PCI_CFG_ADDRESS(bus, dev, func, (reg & 0xff)))

#define IA32_MTRR_DEF_TYPE      0x2FF

#define IA32_MTRR_PHYSBASE0     0x200
#define IA32_MTRR_PHYSBASE1     0x202
#define IA32_MTRR_PHYSBASE2     0x204

VOID    PeiPreMtrr();
VOID    PeiPostMtrr();

/**
    Get power of two

        
    @param Input 

         
    @retval VOID

**/

UINT64
GetPowerOfTwo (
  IN    UINT64  Input
)
{
    UINT64  Result = 0;

    if (!Input)
        return 0;

    if (Input > 0xFFFFFFFF)
    {
        _asm
        {
            bsr eax, dword ptr Input[4]
            bts dword ptr Result[4], eax
        }
    }
    else
    {
        _asm
        {
            bsr eax, dword ptr Input[0]
            bts dword ptr Result[0], eax
        }
    }
    return  Result;
}

/**
    Set default Fixed Mtrrs and entire memory as write back except maybe some reserved memory.

        
    @param MemoryLength 

         
    @retval VOID

**/

VOID
InitMtrrFamily15(
  IN    EFI_PEI_SERVICES    **PeiServices
)
{
    BOOLEAN     InterruptState = FALSE;
    UINT32      VarMtrrMsr = 0;
    UINT8       Index = 0;
    MTRR_HOB    *MtrrHob = NULL;
    EFI_STATUS  Status = EFI_SUCCESS;
    VOID        *FirstHob = NULL;           // ptr for HOB

    InterruptState = CPULib_GetInterruptState();
    CPULib_DisableInterrupt();

//### EIP314779 MTRRs not disabled in Memdetect, skip below code
    if (IsFamily15h())
    {
        PeiPreMtrr();
        (*PeiServices)->GetHobList(PeiServices, &FirstHob);
        if (FirstHob != NULL)
        {
            MtrrHob = (MTRR_HOB*) FirstHob;
            Status = FindNextHobByGuid (&gAmiMtrrHobGuid, &MtrrHob);
            if (!EFI_ERROR (Status))
            {
                for (VarMtrrMsr = MTRR_PHYS_BASE_0, Index = 0; VarMtrrMsr < MTRR_PHYS_BASE_7; VarMtrrMsr += 2, Index++)
                {
                    WriteMsr(VarMtrrMsr, MtrrHob->VarMtrrBase[Index]);
                    WriteMsr(VarMtrrMsr + 1, MtrrHob->VarMtrrMask[Index]);
                }
            }
        }
    }
    //Initialize Fixed MTRR for C0000, D0000 and E0000 region
    //This is required for properly initializing the Legacy Memory region by CSM.
    WriteMsr(MTRR_FIX_4K_C0000, 0);
    WriteMsr(MTRR_FIX_4K_C8000, 0);
    WriteMsr(MTRR_FIX_4K_D0000, 0);
    WriteMsr(MTRR_FIX_4K_D8000, 0);
    WriteMsr(MTRR_FIX_4K_E0000, 0);
    WriteMsr(MTRR_FIX_4K_E8000, 0);

    PeiPostMtrr();
    if (InterruptState)
        CPULib_EnableInterrupt();
}

/**
    Program the MTRR for S3 resume.

        
    @param MtrrValues 
    @param IsPspEnabled TRUE, if PSP S3 resume    

         
    @retval VOID

**/

VOID
ProgramS3ResumeMtrrs(
  IN    MTRR_VALUE  *MtrrValues,
  IN    BOOLEAN     IsPspEnabled
)
{
    UINT8 i;
    UINT64              MsrSysCfg64;
    BOOLEAN InterruptState;

    InterruptState = CPULib_GetInterruptState();
    CPULib_DisableInterrupt();

    if (!IsPspEnabled)
        PeiPreMtrr();

    MsrSysCfg64 = ReadMsr (MSR_SYS_CFG);
    WriteMsr (MSR_SYS_CFG, MsrSysCfg64 | (3 << MtrrFixDramEnBit));
    for (i = 0; i < NUM_OF_MTRR_SAVED; i++)
        WriteMsr (MtrrValues[i].Msr, MtrrValues[i].Value);
    WriteMsr (MSR_SYS_CFG, MsrSysCfg64);

    if (!IsPspEnabled)
        PeiPostMtrr();
    if (InterruptState)
        CPULib_EnableInterrupt();
}

/**
    Disable Interrupts, disable cache, flush cache, disable MTRRs,
    and return original interrupts.

    @param VOID

    @retval VOID

    @note  
  Here is the control flow of this function:
  1. Disable Interrupts.
  2. Disable Cache by setting CD and clearing NW.
  3. Flush cache
  4. Disable MTRRs using MSR register.
  5. Intel SDM spec states for P4, flush cache again.

**/

VOID
PeiPreMtrr()
{

    if (IsFamily15h())
    {
        DisableCpuCar();
    
        WriteMsr(IA32_MTRR_DEF_TYPE, 0);       // disable mtrrs
    
        DisableCacheInCR0();
    }
}

/**
    Enable Fixed and Variable MTRRs, enable cache.

    @param VOID

         
    @retval VOID

    @note  
  Here is the control flow of this function:
  1. Enabling Fixed and Variable MTRRs using MSRs.
  2. Enable cache by clearing CD and NW in CR0.

**/

VOID PeiPostMtrr()
{
    WriteMsr(IA32_MTRR_DEF_TYPE, 3 << 10);  //enable Fixed and Variable MTRRs, default UC

	EnableCacheInCR0();

}

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
