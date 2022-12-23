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

/** @file AmiShadowLib.c
    North Bridge Shadow Library implementation. NOTE: AMD move NB into CPU.

*/

#include <AmiCspLib.h>
#include <Library/AmiShadowLib.h>
#include <Library/IoLib.h>
#include <Library/PciLib.h>
#include <Nb.h>

PAM_STRUCT gPamStruct[] =
{
    {0x68,0x00,0xC0000,0x1000},
    {0x68,0x08,0xC1000,0x1000},
    {0x68,0x10,0xC2000,0x1000},
    {0x68,0x18,0xC3000,0x1000},
    {0x68,0x20,0xC4000,0x1000},
    {0x68,0x28,0xC5000,0x1000},
    {0x68,0x30,0xC6000,0x1000},
    {0x68,0x38,0xC7000,0x1000},

    {0x69,0x00,0xC8000,0x1000},
    {0x69,0x08,0xC9000,0x1000},
    {0x69,0x10,0xCA000,0x1000},
    {0x69,0x18,0xCB000,0x1000},
    {0x69,0x20,0xCC000,0x1000},
    {0x69,0x28,0xCD000,0x1000},
    {0x69,0x30,0xCE000,0x1000},
    {0x69,0x38,0xCF000,0x1000},

    {0x6A,0x00,0xD0000,0x1000},
    {0x6A,0x08,0xD1000,0x1000},
    {0x6A,0x10,0xD2000,0x1000},
    {0x6A,0x18,0xD3000,0x1000},
    {0x6A,0x20,0xD4000,0x1000},
    {0x6A,0x28,0xD5000,0x1000},
    {0x6A,0x30,0xD6000,0x1000},
    {0x6A,0x38,0xD7000,0x1000},

    {0x6B,0x00,0xD8000,0x1000},
    {0x6B,0x08,0xD9000,0x1000},
    {0x6B,0x10,0xDA000,0x1000},
    {0x6B,0x18,0xDB000,0x1000},
    {0x6B,0x20,0xDC000,0x1000},
    {0x6B,0x28,0xDD000,0x1000},
    {0x6B,0x30,0xDE000,0x1000},
    {0x6B,0x38,0xDF000,0x1000},

    {0x6C,0x00,0xE0000,0x1000},
    {0x6C,0x08,0xE1000,0x1000},
    {0x6C,0x10,0xE2000,0x1000},
    {0x6C,0x18,0xE3000,0x1000},
    {0x6C,0x20,0xE4000,0x1000},
    {0x6C,0x28,0xE5000,0x1000},
    {0x6C,0x30,0xE6000,0x1000},
    {0x6C,0x38,0xE7000,0x1000},

    {0x6D,0x00,0xE8000,0x1000},
    {0x6D,0x08,0xE9000,0x1000},
    {0x6D,0x10,0xEA000,0x1000},
    {0x6D,0x18,0xEB000,0x1000},
    {0x6D,0x20,0xEC000,0x1000},
    {0x6D,0x28,0xED000,0x1000},
    {0x6D,0x30,0xEE000,0x1000},
    {0x6D,0x38,0xEF000,0x1000},

    {0x6E,0x00,0xF0000,0x1000},
    {0x6E,0x08,0xF1000,0x1000},
    {0x6E,0x10,0xF2000,0x1000},
    {0x6E,0x18,0xF3000,0x1000},
    {0x6E,0x20,0xF4000,0x1000},
    {0x6E,0x28,0xF5000,0x1000},
    {0x6E,0x30,0xF6000,0x1000},
    {0x6E,0x38,0xF7000,0x1000},

    {0x6F,0x00,0xF8000,0x1000},
    {0x6F,0x08,0xF9000,0x1000},
    {0x6F,0x10,0xFA000,0x1000},
    {0x6F,0x18,0xFB000,0x1000},
    {0x6F,0x20,0xFC000,0x1000},
    {0x6F,0x28,0xFD000,0x1000},
    {0x6F,0x30,0xFE000,0x1000},
    {0x6F,0x38,0xFF000,0x1000}
};
#define NUM_PAM_ENTRIES (sizeof(gPamStruct) / sizeof(PAM_STRUCT))

/**
    Program 0xc0000 - 0xfffff regions to Lock/Unlock.

        
    @param gBS 
    @param gRS 
    @param StartAddress 
    @param Length 
    @param Setting 
    @param Granularity 

         
    @retval EFI_STATUS return the EFI status

    @note  
  Here is the control flow of this function:
              1. Search the structure for the first entry matching
                 the StartAddress.
              2. If not found, return EFI_INVALID_PARAMETER.
              3. Find the last entry in structure for the region to program,
                 by adding the lengths of the entries.
              4. If not found, return EFI_INVALID_PARAMETER.
              5. Read/Write each register for the entry to set region.
              6. Return the Granularity for the region.
**/

EFI_STATUS
NbProgramPamRegisters (
  IN    EFI_BOOT_SERVICES       *gBS,
  IN    EFI_RUNTIME_SERVICES    *gRS,
  IN    UINT32                  StartAddress,
  IN    UINT32                  Length,
  IN    UINT8                   Setting,
  IN    UINT32                  *Granularity
)
{
    // Note: For this routine to work, the gPamStruct regions must be continuous.
    UINT8               CurrentMsr;
    UINT64              SetValue = 0;
    UINT64              MsrValue;
    UINT64              MsrSave;
    UINTN               StartIndex;
    UINTN               EndIndex;
    UINTN               i;
    UINT32              TotalLength = 0;
    EFI_STATUS          Status = EFI_SUCCESS;

    for (StartIndex = 0; StartIndex < NUM_PAM_ENTRIES; ++StartIndex)
        if (gPamStruct[StartIndex].StartAddress >= StartAddress)
            break;

    if (StartAddress < gPamStruct[StartIndex].StartAddress)
        StartIndex--;

    if (StartIndex == NUM_PAM_ENTRIES)
        return EFI_INVALID_PARAMETER;

    // Adjust the length of the requested region if starting address is
    // out of bounds.
    Length += StartAddress-gPamStruct[StartIndex].StartAddress;

    for(EndIndex = StartIndex; EndIndex < NUM_PAM_ENTRIES; ++EndIndex)
    {
        TotalLength += gPamStruct[EndIndex].Length;
        if (TotalLength >= Length)
            break;
    }
    if (EndIndex == NUM_PAM_ENTRIES)
        return EFI_INVALID_PARAMETER;

    // Set the setting value to appropriate value as per input
    if (Setting == LEGACY_REGION_LOCK)
        SetValue = REGION_LOCK << 4;
    else
        if (Setting == LEGACY_REGION_UNLOCK)
            SetValue = REGION_UNLOCK << 3;
        else
            SetValue = REGION_DECODE_ROM << 3;

//  Setting = (Setting != 2) ? REGION_LOCK : REGION_UNLOCK; // BUG IN THIS CODE

    DisableCacheInCR0 ();
    WriteMsr(MTRR_DEF_TYPE, 0);       //disable mtrrs

    // Program the MSR to enable RD/WR enable bits
    MsrSave = ReadMsr (MSR_SYS_CFG);
    WriteMsr (MSR_SYS_CFG, MsrSave | (3 << MtrrFixDramEnBit));

    for(i = StartIndex; i <= EndIndex; ++i)
    {
        CurrentMsr = gPamStruct[i].Register;
        MsrValue = ReadMsr(CurrentMsr + 0x200);
        while (((i <= EndIndex) && gPamStruct[i].Register == CurrentMsr))
        {
            MsrValue &= ~(Shl64 ((UINT64)0x18, gPamStruct[i].MaskShift));
            MsrValue |= Shl64 (SetValue, gPamStruct[i].MaskShift);
            i++;
        }
        i--;
        WriteMsr (CurrentMsr + 0x200, MsrValue);
    }

    WriteMsr (MSR_SYS_CFG, MsrSave);

    WriteMsr(MTRR_DEF_TYPE,3<<10);  //enable Fixed and Variable MTRRs, default UC
    EnableCacheInCR0 ();

    if (Granularity)
        *Granularity = 0x1000;

    //
    // Synchronize MTRRs from BSP to all APs
    //
//-    Status = SynchronizeMtrrs(gBS);

    return Status;
}

/**
    Program 0xc0000 - 0xfffff regions to Lock/Unlock.

        
    @param PeiServices 
    @param StartAddress 
    @param Length 
    @param Setting 
    @param Granularity 

    @retval EFI_STATUS return EFI status

**/

EFI_STATUS
NbPeiProgramPamRegisters (
  IN    EFI_PEI_SERVICES    **PeiServices,
  IN    UINT32              StartAddress,
  IN    UINT32              Length,
  IN    UINT8               Setting,
  IN    UINT32              *Granularity OPTIONAL
)
{
    EFI_STATUS  Status = EFI_SUCCESS;

    return Status;
}

/**
    This function provides runtime interface to enable/disable
    writing in E000-F000 segment

    @param Enable if TRUE - enable writing, if FALSE - disable

    @retval VOID
**/
VOID
NbRuntimeShadowRamWrite (
  IN BOOLEAN Enable
  )
{
    UINT64  MsrValue = 0;
    UINT64  MsrSave = 0;
    static  UINT64  MsrF000Save = 0;
    static  UINT64  MsrF800Save = 0;
    static  UINT64  MsrE000Save = 0;
    static  UINT64  MsrE800Save = 0;

    MsrSave = ReadMsr (MSR_SYS_CFG);    // Save original value for restore
    WriteMsr (MSR_SYS_CFG, MsrSave | (3 << MtrrFixDramEnBit));   // Enable RW for fixed MTRRs

    if (Enable)
    {
        // F000 Memory R/W en
        MsrValue = ReadMsr (0x26E);
        MsrF000Save = MsrValue;
        MsrValue = 0x1818181818181818;
        WriteMsr (0x26E, MsrValue);

        // F800 Memory R/W en
        MsrValue = ReadMsr (0x26F);
        MsrF800Save = MsrValue;
        MsrValue = 0x1818181818181818;
        WriteMsr (0x26F, MsrValue);

#if (SMBIOS_TABLE_LOCATION)
        // E000 Memory R/W en
        MsrValue = ReadMsr (0x26C);
        MsrE000Save = MsrValue;
        MsrValue = 0x1818181818181818;
        WriteMsr (0x26C, MsrValue);

        // E800 Memory R/W en
        MsrValue = ReadMsr (0x26D);
        MsrE800Save = MsrValue;
        MsrValue = 0x1818181818181818;
        WriteMsr (0x26D, MsrValue);
#endif
    }
    else
    {
        // F000 Restore
        WriteMsr(0x26E, MsrF000Save);
        // F800 Restore
        WriteMsr(0x26F, MsrF800Save);

#if (SMBIOS_TABLE_LOCATION)
        // E000 Restore
        WriteMsr(0x26C, MsrE000Save);
        // E800 Restore
        WriteMsr(0x26D, MsrE800Save);
#endif
    }

    WriteMsr (MSR_SYS_CFG, MsrSave);    // Restore the original value
}

/**

     This function provides runtime interface to enable/disable
              writing in C000-F000 segment

     @param   Attribute   The shadowing attributes of the BIOS range
     @param   Range       The BIOS range which is going to be shadowed

     @retval  EFI_STATUS return EFI status

**/

EFI_STATUS
NbRuntimeShadowRamWriteExt (
    IN SHADOW_ARRTIBUTE   Attribute,
    IN SHADOW_BIOS_RANGE  Range
)
{
    UINT32  StartAddress;
    UINT32  Length;
    UINT8   Setting;

    switch (Attribute)
    {
    	case AmiShadowDisabled:
            Setting = 0x3;
            break;
    	case AmiShadowReadOnly:
            Setting = LEGACY_REGION_LOCK;
            break;
    	case AmiShadowWriteOnly:
            Setting = LEGACY_REGION_UNLOCK;
            break;
    	case AmiShadowReadWrite:
            Setting = LEGACY_REGION_UNLOCK;
            break;
        default:
            return EFI_INVALID_PARAMETER;
    }

    // The start address should be 0xC0000 at beginning
    StartAddress = 0xC0000;
    // The Length is 16k as a base except the F0000 is 64k as a base
    Length = 0x4000;

    if (Range <= 11)
        StartAddress += (Length * Range);
    else if (Range == 12)
    {
        Length = 0x10000;
        StartAddress = 0xF0000;
    }
    else
        return EFI_INVALID_PARAMETER;

    return NbProgramPamRegisters (NULL, NULL, StartAddress, Length, Setting, NULL);
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
