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

/** @file NbSetup.c
    North Bridge Setup Rountines

**/

#include <Setup.h>
#include <AmiDxeLib.h>
#include <Protocol/AmiCpuInfo.h>
#include <AmiHobs.h>
#include <Protocol/AmiSmbios.h>
#include <Protocol/Smbios.h>
#include <Library/DebugLib.h>
#include <Guid/HobList.h>
#include "Guid/AmdMemoryInfoHob.h"

// CPU
#define MSR_SYS_CFG     0x0C0010010
#define MSR_TOP_MEM     0x0C001001A
#define MSR_TOP_MEM2    0x0C001001D

//AMICSPLib Cpu
UINT64 ReadMsr(UINT32 Msr);
VOID WriteMsr(UINT32 Msr, UINT64 Value);

//----------------------------------------------------------------------------
EFI_PHYSICAL_ADDRESS  TotalMemorySize = 0;
EFI_PHYSICAL_ADDRESS  SystemRam = 0;


/**
    Return TOM2 MSR value or zero.

    @param VOID

    @retval UINT64 TOM2 value

**/

UINT64
GetTom2(
  IN    VOID
)
{
    return (ReadMsr(MSR_SYS_CFG)&BIT21) ? ReadMsr(MSR_TOP_MEM2) : 0;
}

/**
    Return TOM MSR value.

    @param VOID

    @retval UINT64 TOM value

**/

UINT64
GetTom(
  IN    VOID
)
{
    return ReadMsr(MSR_TOP_MEM);
}



/**
    This function initializes the NB related setup option values

    @param HiiHandle Handle to HII database
    @param Class Indicates the setup class

    @retval VOID

**/

VOID
InitNbStrings(
  IN    EFI_HII_HANDLE  HiiHandle,
  IN    UINT16          Class
)
{
    static BOOLEAN                      Enumerate = FALSE;
    UINT8                               CurDimm;
    EFI_STATUS                          Status = EFI_DEVICE_ERROR;
    EFI_PHYSICAL_ADDRESS                Tom1;
    EFI_PHYSICAL_ADDRESS                Tom2;
    EFI_SMBIOS_PROTOCOL                 *EfiSmbios;
    EFI_SMBIOS_HANDLE                   SmbiosHandle;
    EFI_SMBIOS_TYPE                     SmbiosType;
    EFI_SMBIOS_TABLE_HEADER             *SmbiosTable;
    SMBIOS_MEM_ARRAY_MAP_ADDR_INFO      *Type19;
    SMBIOS_MEMORY_DEVICE_INFO           *Type17;
    UINT32                              Type17Speed;
    UINT32                              CurrentSpeed;
    BOOLEAN                             IsVauleNeedDouble = TRUE;

    UINT16                  ArrayStart[] = {
        STRING_TOKEN(STR_MEMORY_SCKT0_START_ADDRESS_VALUE)  // Array0
    };
    UINT16                  ArrayEnd[] = {
        STRING_TOKEN(STR_MEMORY_SCKT0_END_ADDRESS_VALUE)    // Array0
    };
    UINT16  DimmSize[] = {
        STRING_TOKEN(STR_MEMORY_SIZE_SCKT0_SLOT0_VALUE),    // Array0 Dimm0
        STRING_TOKEN(STR_MEMORY_SIZE_SCKT0_SLOT1_VALUE),
        STRING_TOKEN(STR_MEMORY_SIZE_SCKT0_SLOT2_VALUE),
        STRING_TOKEN(STR_MEMORY_SIZE_SCKT0_SLOT3_VALUE)
    };

    if (!Enumerate)
    {
        Tom2 = Shr64 (GetTom2(), 20);
        Tom1 = Shr64 (GetTom(), 20);
        SystemRam = (Tom2) ? (Tom2 - 0x1000) : 0;
        SystemRam += Tom1;
        Enumerate = TRUE;
    }

    // Get DIMM information from Smbios protocol
    Status = pBS->LocateProtocol (&gEfiSmbiosProtocolGuid, NULL, (VOID **) &EfiSmbios);
    if (EFI_ERROR (Status))
    {
        DEBUG ((DEBUG_ERROR , "InitNBStrings: pBS->LocateProtocol(EfiSmbiosProtocol... ERROR\n"));
        return;
    }

    SmbiosHandle = 0xFFFE;
    SmbiosType = 19;
    Status = EfiSmbios->GetNext(EfiSmbios, &SmbiosHandle, &SmbiosType, &SmbiosTable, NULL);
    DEBUG ((DEBUG_INFO, "InitNBStrings: Get type 19 status = %r \n", Status));

    if (Status == EFI_SUCCESS)
    {
        Type19 = (SMBIOS_MEM_ARRAY_MAP_ADDR_INFO*)SmbiosTable;
        DEBUG ((DEBUG_INFO, "InitNBStrings: Type19 Starting address = %lx \n", Type19->StartingAddress));
        DEBUG ((DEBUG_INFO, "InitNBStrings: Type19 Ending address = %lx \n", Type19->EndingAddress));
        // Array-Level Information
        InitString (HiiHandle, ArrayStart[0], L"  Starting Address: %d KB",
                    Type19->StartingAddress);
        InitString (HiiHandle, ArrayEnd[0], L"    Ending Address: %d KB",
                    Type19->EndingAddress);
    }

    SmbiosHandle = 0xFFFE;
    SmbiosType = 17;
    if((EfiSmbios->MajorVersion > 3) ||\
       (EfiSmbios->MajorVersion == 3 && EfiSmbios->MinorVersion >=1)
       ){
        IsVauleNeedDouble = FALSE;
    }
    for (CurDimm = 0; CurDimm < DIMM_SLOTS_PER_SCKT; CurDimm++)
    {
        DEBUG ((DEBUG_INFO, "InitNBStrings: CurDimm = %lx \n", CurDimm));
        Status = EfiSmbios->GetNext(EfiSmbios, &SmbiosHandle, &SmbiosType, &SmbiosTable, NULL);
        if (Status == EFI_SUCCESS)
        {
            Type17 = (SMBIOS_MEMORY_DEVICE_INFO*)SmbiosTable;
            DEBUG ((DEBUG_INFO, "InitNBStrings: Type17 size = %lx \n", Type17->Size));

            Type17Speed = (IsVauleNeedDouble) ? ((UINT32)(Type17->Speed)*2) : (UINT32)(Type17->Speed);
            if (Type17Speed == 2134)
            {
                Type17Speed = 2133;
            }
            else if (Type17Speed == 1334)
            {
                Type17Speed = 1333;
            }
            else if (Type17Speed == 2934)
            {
                Type17Speed = 2933;
            }
            CurrentSpeed = (IsVauleNeedDouble) ? ((UINT32)(Type17->ConfMemClkSpeed)*2) : ((UINT32)(Type17->ConfMemClkSpeed));
            if (CurrentSpeed == 2134)
            {
                CurrentSpeed = 2133;
            }
            else if (CurrentSpeed == 1334)
            {
                CurrentSpeed = 1333;
            }
            else if (CurrentSpeed == 2934)
            {
                CurrentSpeed = 2933;
            }
            
            //If no dimm, show "Dimm#: Not Present.
            if(Type17->Size > 0){
                InitString(HiiHandle, DimmSize[CurDimm],
                            L"Dimm%d: size=%d MB\n       Current speed=%d MHz\n       Max speed=%d MHz", 
                            CurDimm, Type17->Size, CurrentSpeed, Type17Speed);
        
            }
        }
    }

    if (Class == MAIN_FORM_SET_CLASS)
    {
        InitString (HiiHandle, STRING_TOKEN(STR_MEMORY_SIZE_VALUE),
         L" %4d MB (DDR4)", SystemRam);
    }

    if (Class == CHIPSET_FORM_SET_CLASS)
    {
        InitString (HiiHandle, STRING_TOKEN(STR_MEMORY_SIZE_VALUE),
         L"Total Memory: %4d MB (DDR4)", SystemRam);
    }
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
