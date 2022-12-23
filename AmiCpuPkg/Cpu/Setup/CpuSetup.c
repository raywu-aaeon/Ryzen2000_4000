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

/** @file CpuSetup.c
    CPU Setup Routines

**/

#include <Setup.h>
// #include <SetupStrTokens.h>
#include <AmiDxeLib.h>
#include <Protocol/AmiCpuInfo.h>
#include <AmiHobs.h>
#include <CacheSubClass.h>
#include <CpuBoard.h>
#include <CpuCspLib.h>
#include "AMD.h"
#include "Library/CcxPstatesLib.h"

#define MAX_NODES NNODE
// CPU
#define MSR_PSTATE_LIMIT    0x0C0010061
#define MSR_PSTATE_0        0x0C0010064
//#define	AMD_MSR_NB_CFG      0x0C001001F
#define  PCI_ADDRESS(bus, dev, func, reg) \
            ((UINT64) ( (((UINT8)bus) << 16) + (((UINT8)dev) << 11) + \
            (((UINT8)func) << 8) + ((UINT8)reg) )) & 0x00000000ffffffff

#if (MAX_NODES > 4)
GENERATE BUILD ERROR! Currently more than 4 nodes is not tested!
#endif

EFI_HII_HANDLE  CpuHiiHandle;

UINT64          ReadMsr(UINT32 Msr);

/**
    Read the PCI Register

    @param Address :(UINT32) ( (((UINT32)bus) << 24) + (((UINT32)dev) << 19) \
        + (((UINT32)func) << 16) + ((UINT32)reg) )
    @param ExtAccess : TRUE for extended access, FALSE is for normal access

    @retval UINT32 return value from the PCI Register.

**/

UINT32
NbReadPCI32(
  IN    UINT32  Address,
  IN    BOOLEAN ExtAccess
)
{
    UINT32  Value32;
    UINT32  AddrCf8 = (1 << 31) + (Address & 0xFFFF00) + (Address & 0xFC);

    if (ExtAccess)  // If extended config Access requested then add the extended config address  bit (24 to 27)
        AddrCf8 |= 0x1000000;

    IoWrite32(0xCF8, AddrCf8);
    Value32 = IoRead32(0xCFC);
    return Value32;
}

/**
    Initialize CPU Setup information.

        
    @param Value Cache associativity type
      
         
    @retval UINTN Return value or 0 if it is out of defined range  

**/

UINTN
GetAIndex (
  IN    EFI_CACHE_ASSOCIATIVITY_DATA    Value
)
{
    if (Value >= CacheAssociativityDirectMapped &&
         Value <= CacheAssociativity64Way)
        return (UINTN)Value;
    return 0;
}

/**
    Initialize CPU Setup information.

        
    @param Event 
    @param Context 

         
    @retval VOID

**/

VOID 
InitCpuInfo(
  IN    EFI_EVENT   Event, 
  IN    VOID        *Context
)
{
	EFI_STATUS                      Status;
	AMI_CPU_INFO                    *GetCpuInfo = NULL;
	AMI_CPU_INFO_PROTOCOL           *Cpu;
	CPUINFO_HOB					    *CpuInfoHob;
	EFI_GUID                        HobListGuid	= HOB_LIST_GUID;
    EFI_GUID                        CpuInfoHobGuid = AMI_CPUINFO_HOB_GUID;
    UINT8                           CurSocket;
    UINT8                           CurCpu;
    UINT8                           a = 0;
    UINT8                           i;
    UINT8                           StringIndex;
    UINT32                          RegValue;
    UINT32                          PsLimit;
    UINT8                           CurFid;
    UINT8                           CurDid;
    STRING_REF                      CacheName;
    UINT64                          Buffer64;
    UINT32                          MsrValue32;
    REGISTER_TABLE                  Reg;
    UINT8                           ExtFamily;
    UINT8                           BaseFamily;
    UINT8                           ExtModel;
    UINT8                           BaseModel;
    UINT16                          CacheSize = 0;
    UINT32                          CpuId;
    UINTN                           Frequency;
    UINTN                           VoltageInuV;
    UINTN                           PowerInmW;
    BOOLEAN                         PstateEn;
    UINT16                          NumCores;


    // ===================================================
    // The following intializes string arrays to allow
    // a simple algorithm for setting values. To support
    // additional nodes, simply modify MAX_NODES and
    // add additional string values.
	UINT16	ProcessorName[] = {
		STRING_TOKEN(STR_PROCESSOR_VERSION_VALUE)
//		STRING_TOKEN(STR_PROCESSOR_VERSION_VALUE1),
//		STRING_TOKEN(STR_PROCESSOR_VERSION_VALUE2),
//		STRING_TOKEN(STR_PROCESSOR_VERSION_VALUE3),
	};
	UINT16	NumberOfCores[] = {
		STRING_TOKEN(STR_PROCESSOR_CORE_VALUE)
//		STRING_TOKEN(STR_PROCESSOR_CORE_VALUE1),
//		STRING_TOKEN(STR_PROCESSOR_CORE_VALUE2),
//		STRING_TOKEN(STR_PROCESSOR_CORE_VALUE3),
	};
	UINT16	ProcessorSpeed[] = {
		STRING_TOKEN(STR_PROCESSOR_SPEED_VALUE)
//		STRING_TOKEN(STR_PROCESSOR_SPEED_VALUE1),
//		STRING_TOKEN(STR_PROCESSOR_SPEED_VALUE2),
//		STRING_TOKEN(STR_PROCESSOR_SPEED_VALUE3),
	};
	UINT16	MicrocodeVersion[] = {
		STRING_TOKEN(STR_PROCESSOR_MICROCODE_VALUE)
//		STRING_TOKEN(STR_PROCESSOR_MICROCODE_VALUE1),
//		STRING_TOKEN(STR_PROCESSOR_MICROCODE_VALUE2),
//		STRING_TOKEN(STR_PROCESSOR_MICROCODE_VALUE3),
	};

#if CACHE_INFO_MODEL == 0
	UINT16	L1DataCache[] = {
		STRING_TOKEN(STR_PROCESSOR_L1_DCACHE_VALUE)
//		STRING_TOKEN(STR_PROCESSOR_L1_DCACHE_VALUE1),
//		STRING_TOKEN(STR_PROCESSOR_L1_DCACHE_VALUE2),
//		STRING_TOKEN(STR_PROCESSOR_L1_DCACHE_VALUE3),
	};
	UINT16	L1InstructionCache[] = {
		STRING_TOKEN(STR_PROCESSOR_L1_ICACHE_VALUE)
//		STRING_TOKEN(STR_PROCESSOR_L1_ICACHE_VALUE1),
//		STRING_TOKEN(STR_PROCESSOR_L1_ICACHE_VALUE2),
//		STRING_TOKEN(STR_PROCESSOR_L1_ICACHE_VALUE3),
	};
	UINT16	L2DataCache[] = {
		STRING_TOKEN(STR_PROCESSOR_L2_CACHE_VALUE)
//		STRING_TOKEN(STR_PROCESSOR_L2_CACHE_VALUE1),
//		STRING_TOKEN(STR_PROCESSOR_L2_CACHE_VALUE2),
//		STRING_TOKEN(STR_PROCESSOR_L2_CACHE_VALUE3),
	};
	UINT16	L3DataCache[] = {
		STRING_TOKEN(STR_PROCESSOR_L3_CACHE_VALUE)
//		STRING_TOKEN(STR_PROCESSOR_L3_CACHE_VALUE1),
//		STRING_TOKEN(STR_PROCESSOR_L3_CACHE_VALUE2),
//		STRING_TOKEN(STR_PROCESSOR_L3_CACHE_VALUE3),
	};
#else
    UINT16  L1DataCache[] = {
        STRING_TOKEN(STR_PROCESSOR_L1_DCACHE_VALUE)
    };
    UINT16  L2DataCache[] = {
        STRING_TOKEN(STR_PROCESSOR_L2_CACHE_VALUE)
    };
    UINT16  L3DataCache[] = {
        STRING_TOKEN(STR_PROCESSOR_L3_CACHE_VALUE)
    };
#endif

	UINT16	ProcessorFamily[] = {
		STRING_TOKEN(STR_PROCESSOR_FAMILY_VALUE)
//		STRING_TOKEN(STR_PROCESSOR_FAMILY_VALUE1),
//		STRING_TOKEN(STR_PROCESSOR_FAMILY_VALUE2),
//		STRING_TOKEN(STR_PROCESSOR_FAMILY_VALUE3),
	};

	UINT16	ProcessorModel[] = {
		STRING_TOKEN(STR_PROCESSOR_MODEL_VALUE)
//		STRING_TOKEN(STR_PROCESSOR_MODEL_VALUE1),
//		STRING_TOKEN(STR_PROCESSOR_MODEL_VALUE2),
//		STRING_TOKEN(STR_PROCESSOR_MODEL_VALUE3),
	};
	UINT16	ProcessorId[] = {
		STRING_TOKEN(STR_PROCESSOR_ID_VALUE)
	};
    CHAR16 *Associativity[] = {
        L"??-way  ",
        L"??-way  ", 
        L"??-way  ",
        L"Direct  ",    // CacheAssociativityDirectMapped = 3
        L"2-way   ",    // CacheAssociativity2Way = 4
        L"3-way   ",    // CacheAssociativity3Way = 5
        L"4-way   ",    // CacheAssociativity4Way = 6
        L"Full-way",    // CacheAssociativityFully = 7
        L"8-way   ",    // CacheAssociativity8Way = 8
        L"16-way  ",    // CacheAssociativity16Way = 9
        L"??-way  ",    // A
        L"??-way  ",    // B
		L"32-way  ",    // CacheAssociativity32Way = C
		L"48-way  ",    // CacheAssociativity48Way = D
		L"64-way  "     // CacheAssociativity64Way = E
    };

#if CACHE_INFO_MODEL == 0
    CHAR16 *CacheString[] = {
        L"       L1 Data Cache",
        L"L1 Instruction Cache",
        L"            L2 Cache",
        L" Total L3 Cache per Socket"
    };
#else
    CHAR16 *CacheString[] = {
        L" L1 Cache",
        L" L2 Cache",
        L" Total L3 Cache per Socket"
    };
#endif

    // ===================================================
	//Find the Cpu information in CPUINFO_HOB
	CpuInfoHob = (CPUINFO_HOB*)GetEfiConfigurationTable(pST, &HobListGuid);
	if (CpuInfoHob == NULL) 
        Status = EFI_UNSUPPORTED;
	else 
        Status = FindNextHobByGuid(&CpuInfoHobGuid, (VOID**)&CpuInfoHob);

    if (EFI_ERROR (Status)) 
        return;

    // ===================================================
	// Find AMI_CPU_INFO_PROTOCOL protocol 
	Status = pBS->LocateProtocol (&gAmiCpuInfoProtocolGuid, NULL, &Cpu);
    ASSERT_EFI_ERROR (Status);
    if (EFI_ERROR (Status))
        return;

    // ===================================================
    // Common CPU Information
    InitString (CpuHiiHandle, STRING_TOKEN (STR_MODULE_VERSION), L"Module Version: PiccasoCpu %s",
                CONVERT_TO_WSTRING(PICASSO_CPU_VERSION));
    InitString (CpuHiiHandle, STRING_TOKEN (STR_AGESA_VERSION), L"AGESA Version : Embedded-FP5 PI %s",
                CONVERT_TO_WSTRING(RAVEN_PI_VERSION));

    // ===================================================
    //  Node X Information
    //
    //  Notes: 
    //
    //  Information is obtained for core 0 of each node
    //  with the assumption that each core on one chip has 
    //  the same configuration (i.e., same cache size, 
    //  same speed, ...).
    //
    //  The CPU number of Core0 of nodeX is 
    //  calculated as:
    // 
    //      cpu# = X*(AMI_CPU_INFO.NumCores)
    //
    //  This assumes that each node has the same core count.
    // ===================================================
    CurSocket = 0;
    CurCpu = 0;
//    for (CurNode = 0, CurCpu = 0; 
//         CurNode < MAX_NODES && CurNode < CpuInfoHob->NodeCount; 
//        CurNode++, CurCpu = GetCpuInfo->NumCores * CurNode)
//    {
    Cpu->GetCpuInfo (Cpu, CurCpu, &GetCpuInfo);
    InitString(CpuHiiHandle,	ProcessorName[CurSocket], L"Socket%d: %a", 
               CurSocket, GetCpuInfo->BrandString);

    if (IsFamily15h())
    {
        InitString (CpuHiiHandle, NumberOfCores[CurSocket],
                        L"%d Core(s) Running @ %d MHz  %d mV", GetCpuInfo->NumCores, GetCpuInfo->ActualFreq,
                        GetCpuInfo->Voltage);
    }
    else
    {
        // Get the core number
        NumCores = GetCpuInfo->NumCores;
        CPULib_CpuID (0x8000001E, &Reg[EAX], &Reg[EBX], &Reg[ECX], &Reg[EDX]);
        // [15:8]ThreadsPerCore: The number of threads per core is ThreadsPerCore+1
        // 0 : no thread per core, 1 : two threads per core
        Reg[EBX] = (Reg[EBX] >> 8) & 0x0F;
        NumCores >>= (UINT8)Reg[EBX];
        InitString (CpuHiiHandle, NumberOfCores[CurSocket],
                        L"%d Core(s) Running @ %d MHz  %d mV", NumCores, GetCpuInfo->ActualFreq,
                        GetCpuInfo->Voltage);
    }


    if (IsFamily15h())
    {
        Buffer64 = ReadMsr(AMD_MSR_NB_CFG);
        if (!(Buffer64 & Shl64(1, 46)))  // if bit 46 EnableCf8ExtCfg is not then set it for accessing D18F4x15C
        {
            WriteMsr(AMD_MSR_NB_CFG, Buffer64 | Shl64(1, 46));
            Buffer64 &= ~Shl64(1, 46);
        }
        RegValue = NbReadPCI32(PCI_ADDRESS(0, 0x18, 4, 0x15C), TRUE);
        WriteMsr(AMD_MSR_NB_CFG, Buffer64); // restore the original value to NB_CFG
        RegValue = (UINT32)(Shr64(RegValue, 2) & 0x7);  // Get NumBoostStates

        MsrValue32 = (UINT32)ReadMsr(MSR_PSTATE_LIMIT);
        MsrValue32 = RegValue + (UINT32)(Shr64(MsrValue32, 4) & 7);

        // Find the lowest pstate msr
        // Extract the fid and DID.
        // Frequency = ((fid + 10h) * 100) / (2 ^ DID)
        PsLimit = (UINT32)MSR_PSTATE_0 + MsrValue32;
        RegValue = (UINT32)ReadMsr (PsLimit);   // The lowest pstate msr
        CurFid = (UINT8)RegValue & 0x3F;    // Get bit CPU FID[5:0]
        CurDid = (UINT8)(Shr64 (RegValue, 6) & 7);
        CurDid = (UINT8)Shl64 (1, CurDid);  // 2 ^ DID
        RegValue = (UINT32)((CurFid + 0x10) * 100) / CurDid;
	}
    else
    {
        for (i = 0; i <= 7; i++)
        {
            PstateEn = CcxGetPstateInfo (0, i, &Frequency, &VoltageInuV, &PowerInmW, NULL);
            if (!PstateEn)
            {
                CcxGetPstateInfo (0, i - 1, &Frequency, &VoltageInuV, &PowerInmW, NULL);
                RegValue = (UINT32)Frequency;
                break;
            }
        }
    }

    // Get Cpuid information
    CPULib_CpuID (1, &Reg[EAX], &Reg[EBX], &Reg[ECX], &Reg[EDX]);
    ExtFamily = (UINT8)(Reg[EAX] >> 20 & 0xFF);
    BaseFamily = (UINT8)(Reg[EAX] >> 8 & 0xF);
    ExtModel = (UINT8)(Reg[EAX] >> 16 & 0xF);
    BaseModel = (UINT8)(Reg[EAX] >> 4 & 0xF);
    CpuId = (UINT32)(Reg[EAX]);

    InitString (CpuHiiHandle, ProcessorFamily[CurSocket], L"Processor Family: %xh",
                ExtFamily + BaseFamily);
    InitString (CpuHiiHandle, ProcessorModel[CurSocket], L"Processor Model: %x0h-%xFh",
                ExtModel, ExtModel);
    InitString (CpuHiiHandle, ProcessorId[CurSocket], L"CPUID: %08X",CpuId);

    // Report Max Frequency and Min Frequency
    InitString (CpuHiiHandle, ProcessorSpeed[CurSocket],
     L"Max Speed:%d MHZ", GetCpuInfo->IntendedFreq);

    InitString (CpuHiiHandle, STRING_TOKEN(STR_PROCESSOR_SPEED_VALUE_MIN),
     L"Min Speed:%d MHZ", RegValue);

#if CACHE_INFO_MODEL == 0
    for (i = 0; i < NUMBER_OF_CACHES; i++)
    {
        switch (GetCpuInfo->CacheInfo[i].Level)
        {   
            case EFI_CACHE_L1:
                if (GetCpuInfo->CacheInfo[i].Type == EfiCacheTypeData)
                {
                    // L1 data cache is per core
                    CacheSize = GetCpuInfo->CacheInfo[i].Size;
                    CacheName = L1DataCache[CurSocket];
                    StringIndex = 0;
                }
                else
                {
                    // L1 instruction cache is per core
                    CacheSize = GetCpuInfo->CacheInfo[i].Size;
                    CacheName = L1InstructionCache[CurSocket];
                    StringIndex = 1;
                }
                break;
            case EFI_CACHE_L2:
                // L2 cache is always 512KB per core
                CacheSize = 512;
                CacheName = L2DataCache[CurSocket];
                StringIndex = 2;
                break;
            case EFI_CACHE_L3:
                // L3 cache is shared by all cores
                CacheSize = GetCpuInfo->CacheInfo[i].Size;
                CacheName = L3DataCache[CurSocket];
                StringIndex = 3;
        }
        a = GetCpuInfo->CacheInfo[i].Associativity;

        if (StringIndex == 3) 
		{
			if (IsFamily15h())
			{
			    // Family 15h doesn't have L3
			    InitString (CpuHiiHandle, CacheName, L"No L3 Cache Present");
			}
			else
			{
		        InitString( CpuHiiHandle, CacheName, L"%s: %d MB/%s",
                        CacheString[StringIndex], CacheSize, Associativity[GetAIndex(a)]);
			}
		}
        else
            InitString (CpuHiiHandle, CacheName, L"%s: %d KB/%s",
                        CacheString[StringIndex], CacheSize, Associativity[GetAIndex(a)]);
    }
#else
    for (i = 0; i < NUMBER_OF_CACHES; i++)
    {
        // The order of cache type is defined in Cache(CPU_CACHE_TABLE) of CpuBoard.c.
        // i = 0, L1 instruction cache is per core in EDX[31:24] of CPUID 8000_0005 
        if (i == 0)
        {
            CacheSize = GetCpuInfo->CacheInfo[i].Size;
            continue;
        }

        // i = 1, L1 data cache is per Core in ECX[31:24] of CPUID 8000_0005 
        if (i == 1)
        {
            // L1 total size is L1 instruction + L1 data
            CacheSize += GetCpuInfo->CacheInfo[i].Size;
            if (IsFamily15h())
            {
                CacheSize *= GetCpuInfo->NumCores;
            }
            else
            {
                CacheSize *= (GetCpuInfo->NumCores / 2);
            }
            CacheName = L1DataCache[CurSocket];
            StringIndex = 0;
        }

        // i = 2, L2 total cache size is 512KB * NumCores
        if (i == 2)
        {
            if (IsFamily15h())
            {
                CacheSize = 512 * GetCpuInfo->NumCores;
            }
            else
            {
                CacheSize = 512 * (GetCpuInfo->NumCores / 2);
            }
            CacheName = L2DataCache[CurSocket];
            StringIndex = 1;
        }

        // i = 3, L3 cache is shared by all cores in EDX[31:18] of CPUID 8000_0006
        // We can get it from GetCpuInfo->CacheInfo[i].Size for L3 cache.
        if (i == 3)
        {
            CacheSize = GetCpuInfo->CacheInfo[i].Size;
            CacheName = L3DataCache[CurSocket];
            StringIndex = 2;
        }

        if (StringIndex == 2)
        {
            if (IsFamily15h())
            {
                InitString (CpuHiiHandle, CacheName, L"No L3 Cache Present");
            }
            else
            {
                InitString (CpuHiiHandle, CacheName, L"%s: %d MB",
                 CacheString[StringIndex], CacheSize);
            }
        }
        else
            InitString (CpuHiiHandle, CacheName, L"%s: %d KB",
             CacheString[StringIndex], CacheSize);
    }   // for (i = 0; i < NUMBER_OF_CACHES; i++)
#endif

    if (GetCpuInfo->MicroCodeVers != 0)
        InitString (CpuHiiHandle,	MicrocodeVersion[CurSocket],
         L"Microcode Patch Level: %x", GetCpuInfo->MicroCodeVers);
//    }
}

/**
    Initialize CPU strings.

        
    @param HiiHandle 
    @param Class 

         
    @retval VOID

**/

VOID
InitCpuStrings(
  IN    EFI_HII_HANDLE  HiiHandle,
  IN    UINT16          Class
)
{
  EFI_EVENT                       Event;
  EFI_STATUS                      Status;
  VOID                            *CpuNotifyReg;
  AMI_CPU_INFO_PROTOCOL           *Cpu;

    if (Class == ADVANCED_FORM_SET_CLASS)
    {
        CpuHiiHandle = HiiHandle;
        Status = pBS->LocateProtocol (&gAmiCpuInfoProtocolGuid, NULL, &Cpu);
        if (Status == EFI_SUCCESS)
            InitCpuInfo (NULL, NULL);
        else
        {
            Status = RegisterProtocolCallback (&gAmiCpuInfoProtocolGuid,
                      InitCpuInfo, NULL, &Event, &CpuNotifyReg);
            ASSERT_EFI_ERROR (Status);
        }
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
