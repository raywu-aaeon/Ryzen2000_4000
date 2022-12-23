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

/** @file NbPciCsp.c
    This file contains generic NB code that is common between
    various components such as NB PEI, DXE etc

**/

#include <Token.h>
#if AMI_ROOT_BRIDGE_SUPPORT == 1
/****** DO NOT WRITE ABOVE THIS LINE *******/

#include "PciHostBridge.h"
#include <Acpi20.h>
#include "Hob.h"
#include "Nb.h"
#include <AmiDxeLib.h>
#include <AmiCspLib.h>
#include <Setup.h>
#if CORE_COMBINED_VERSION >= 0x4028b
#include <Protocol/AcpiTable.h>    // this protocol exists only if CORE_COMBINED_VERSION >= 4.6.5.1
#endif
#if (!defined(BACKWARD_COMPATIBLE_MODE))
#include "Protocol/AcpiSupport.h"
#endif
#include <Protocol/S3SaveState.h>
#include <Protocol/AmdApcbProtocol.h>
#include <Library/DebugLib.h>
#include <Library/AmiPciBusLib.h>
#if PCI_BUS_REVISION >= 16
extern  UINTN AlignFromGranularity(UINTN g);
#else
extern  UINTN AlignFromGra(UINTN g);
#endif
//--------------------------------------------------------------------------
//Global Vars
VOID        *AcpiReg;
UINTN       McfgTblKey = 0;
CHAR16      MemoryCeilingVariable[] = L"MemCeil.";
CHAR16      SetupVariable[] = L"Setup";
BOOLEAN     IsSetupDataValid = FALSE;
SETUP_DATA  SetupData;
EFI_EVENT   AcpiEvent;
EFI_GUID    EfiSetupGuid = SETUP_GUID;

#if CORE_COMBINED_VERSION >= 0x5000a
static  EFI_GUID    AmiGlobalVariableGuid = AMI_GLOBAL_VARIABLE_GUID;
#else
static  EFI_GUID    AmiGlobalVariableGuid = EFI_GLOBAL_VARIABLE;
#endif

PCI_COMMON_SETUP_DATA    *NbPciCommonSetup;

EFI_S3_SAVE_STATE_PROTOCOL *BootScriptSave;

EFI_STATUS
EFIAPI AllocateRbResources (PCI_ROOT_BRG_DATA *RootBrg);

VOID
ClearMemoryMappedIoInfo_Below4Gb_Family15H (IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *RootBridgeIo);

VOID
ClearMemoryMappedIoInfo_Below4Gb_Family17H (IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *RootBridgeIo);

VOID
AddMemoryMappedIoInfo_Family17H (
  IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *RootBridgeIo,
  IN UINT64                          BaseAddress,
  IN UINT64                          Length,
  IN BOOLEAN                         NonPosted
);

EFI_STATUS
LegacyVgaRouting15h (IN PCI_ROOT_BRG_DATA *RbData, IN UINT8 RbNode);

CHAR8
*GetAttributeString(IN UINT64 Code);

typedef struct _PCI64_ADDRESS
{
    union {
        struct {
            UINT64  Register    :8;     // [7:0] Register
            UINT64  Function    :8;     // [15:8] Function
            UINT64  Device      :8;     // [23:16] Device
            UINT64  Bus         :40;    // [63:24] Bus
        } Field;
        UINT64  AllBits;
    };
}PCI64_ADDRESS;

EFI_STATUS
LegacyVgaRouting17h (
  IN    PCI_ROOT_BRG_DATA   *RbData,
  IN    UINT8               RbNode
);

typedef struct _VGA_ENABLE_REGISTER_17h
{
    union {
        struct {
            UINT32  VgaEnable   :1;  // [0] VE: VGA enable
            UINT32  NonPosted   :1;  // [1] NP: non-posted
            UINT32  CpuDis      :1;  // [2] CpuDis: CPU Disable
            UINT32  Reserved    :1;  // [3] Reserved
            UINT32  DstFabricID :8;  // [11:4] Destination Fabric ID
            UINT32  Reserved2   :20;  // [31:11] Reserved
        } Field;
        UINT32  AllBits;
    };
} VGA_ENABLE_REGISTER_17h;

#if (!defined(PORT_TPM_IOMEMBASE))
#define PORT_TPM_IOMEMBASE 0xFED40000
#endif
//--------------------------------------------------------------------------

//WMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWM
//PORTING!!!//PORTING!!!//PORTING!!!//PORTING!!!//PORTING!!!//PORTING!!!//PORTING!!!
//PORTING!!!//PORTING!!!//PORTING!!!//PORTING!!!//PORTING!!!//PORTING!!!//PORTING!!!
//PORTING!!!//PORTING!!!//PORTING!!!//PORTING!!!//PORTING!!!//PORTING!!!//PORTING!!!
//PORTING!!!//PORTING!!!//PORTING!!!//PORTING!!!//PORTING!!!//PORTING!!!//PORTING!!!
//PORTING!!!//PORTING!!!//PORTING!!!//PORTING!!!//PORTING!!!//PORTING!!!//PORTING!!!
//WMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWM

#define PCI_IO_REGSET_COUNT 0x01

#define FLASH_DEVICE_BASE_ADDRESS (0xFFFFFFFF - FLASH_SIZE + 1)
#define FWH_FEATURE_SPACE_BASE (FLASH_DEVICE_BASE_ADDRESS & ~(UINTN)0x400000)

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// For HOST AND ROOT BRIDGE Architectural information 
// see chapter 12.1.1 PCI Root Bridge I/O Overview of EFI 1.1 spec
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//===============================================================================================
//This table will provide information on how many Root Bridges 
//particular Host Bridge will produce.
//The table has NB_NUMBER_OF_HOST_BRG entries.
//(Token NB_NUMBER_OF_HOST_BRG is defined in NB.sdl)
//
//For i945 it will be ONE ROOT UNDER ONE HOST.
//
//If system has more than ONE Host Add more Lines
//-----------------------------------------------------------------------------------------------
UINTN   gRbCountTbl[NB_NUMBER_OF_HOST_BRG] =
{
    1,  //Number of root bridges produced by Host #0
        //Number of root bridges produced by Host #1    
        //Number of root bridges produced by Host #2    
        //Number of root bridges produced by Host #3    
};


//===============================================================================================
//This is the table to provide each host allocation attributes  
// The table has NB_NUMBER_OF_HOST_BRG entries.
//(Token NB_NUMBER_OF_HOST_BRG is defined in NB.sdl)
//Accepted values are:
//  EFI_PCI_HOST_BRIDGE_COMBINE_MEM_PMEM
//  EFI_PCI_HOST_BRIDGE_MEM64_DECODE
//These values can be ORed.
//The values are defined and explained in 
//PCI Host Bridge Resource Allocation Protocol Specification V 0.9
//-----------------------------------------------------------------------------------------------
UINT64 gHbAllocAttribTbl[NB_NUMBER_OF_HOST_BRG] =
{
    0,  //Allocation Attributes of Host #0
        //Allocation Attributes of Host #1  
        //Allocation Attributes of Host #2  
        //Allocation Attributes of Host #3  
        // And so on 
};

//===============================================================================================
//This table will provide PCI Buses Decoding Information
//in form of ACPI QWORD resource descriptor. 
//The only valid fields are:
//  ResourceType,  _MIN, _LEN. 
//  Maximum Bus may be calculated as: _MAX=_MIN+_LEN -1
//
//If system has more then one root bridge, add more lines 
//
//i945 chipset is simple chipset with only one root bridge 
//which decodes all bus ranges from 0 to 0xFF
//
//See definition of QWORD ACPI Resource Descriptor in ACPI 2.0 Spec 
//and "Address Space Resource Descriptor Internal definitions" in AcpiRes.h
// Number of table entries depends on values ported in gRbCountTbl 
//-----------------------------------------------------------------------------------------------
//  Name,  Len, Resource Type,     Flags    _GRA,   _MIN,   _MAX,   _TRA,   _LEN
ASLR_QWORD_ASD  gRbBusesTbl[] =
{
//for Root 0 at Host 0
    {0x8A, 0x2B, ASLRV_SPC_TYPE_BUS, 0,0,    0x1,    0x00,   0xFF,   0,      0x100 }    // Bus
//for Root 1 at Host 0 if any 

//for Root 0 at Host 1 if any
};

//===============================================================================================
//This is the table for the Capabilities Supported by ROOT BRIDGE
// See EFI 1.1 spec for meaning of the Capabilities bits
//
//if system has more than one root bridge add more lines
// Number of table entries depends on values ported in gRbCountTbl
//-----------------------------------------------------------------------------------------------
UINT64  gRbSupportsTbl[] =
{
//for Root 0 at Host 0
    (EFI_PCI_ATTRIBUTE_IDE_PRIMARY_IO | EFI_PCI_ATTRIBUTE_IDE_SECONDARY_IO| \
     EFI_PCI_ATTRIBUTE_ISA_IO | EFI_PCI_ATTRIBUTE_VGA_PALETTE_IO  | \
     EFI_PCI_ATTRIBUTE_VGA_MEMORY | EFI_PCI_ATTRIBUTE_VGA_IO | \
     EFI_PCI_ATTRIBUTE_ISA_MOTHERBOARD_IO),
//for Root 1 at Host 0 if any

//for Root 0 at Host 1 if any

// and so on...
};

// The following code defines strings and routines that can be used to display
// memory attributes (see EFI.h) or Coherence Domain types
// (see EFI_GCD_MEMORY_TYPE enum defined in DXE.h).
//
// UsageExample1:
//    DEBUG((DEBUG_VERBOSE, "Attributes=0x8000000000000001 (%s)\n",
//      getAttributeString(0x8000000000000001) ));
// 
//    Output1:
//      Attributes=0x8000000000000001 (EFI_MEMORY_UC|EFI_MEMORY_RUNTIME)
//  
// UsageExample2:
//    DEBUG((DEBUG_VERBOSE, "Type=(%a)\n",
//      memtype(EfiGcdMemoryTypeMemoryMappedIo) ));  
// 
//    Output2:
//      Type=(EfiGcdMemoryTypeMemoryMappedIo)
//
CHAR8 *MemType[] = 
{
    "   EfiGcdMemoryTypeNonExistent",
    "      EfiGcdMemoryTypeReserved",
    "  EfiGcdMemoryTypeSystemMemory",
    "EfiGcdMemoryTypeMemoryMappedIo",
    "       EfiGcdMemoryTypeMaximum"
};

CHAR8 AttributeString[] = {"EFI_MEMORY_UC | EFI_MEMORY_WC | EFI_MEMORY_WT | \
                           EFI_MEMORY_UCE | EFI_MEMORY_WP | EFI_MEMORY_RP | EFI_MEMORY_XP | EFI_MEMORY_RUNTIME"
                          };

/**
    This function will create the MCFG ACPI table when ACPI
    support protocol is available.

    @param Event Event of callback
    @param Context Context of callback.

    @retval VOID

    @note  Porting required.
**/

VOID
CreateNbAcpiTables(
  IN    EFI_EVENT   Event,
  IN    VOID        *Context
)
{
#if ACPI_SUPPORT
    EFI_STATUS              Status = 0;
    MCFG_20                 *Mcfg;
    EFI_ACPI_TABLE_PROTOCOL *AcpiTableProtocol = NULL;
    UINT64                  PcieBaseAddr;

    //--------------------------------
    // It must be only one instance of such protocol
    Status = pBS->LocateProtocol (&gEfiAcpiTableProtocolGuid, NULL, &AcpiTableProtocol);
    DEBUG((DEBUG_VERBOSE, "PciHostCSHooks: LocateProtocol(ACPISupport)=%r\n", Status));
    if (EFI_ERROR(Status))
        return;

    Mcfg = MallocZ (sizeof (MCFG_20));
    ASSERT (Mcfg);
    if (!Mcfg)
        return;

    // Fill Table header;
    Mcfg->Header.Signature = MCFG_SIG;
    Mcfg->Header.Length = sizeof (MCFG_20);
    Mcfg->Header.Revision = 1;
    Mcfg->Header.Checksum = 0;
//    Mcfg->Header.OemId[0]='A';      //"A M I "
//    Mcfg->Header.OemId[1]=0x20;
//    Mcfg->Header.OemId[2]='M';
//    Mcfg->Header.OemId[3]=0x20;
//    Mcfg->Header.OemId[4]='I';
//    Mcfg->Header.OemId[5]=0x20;
//    Mcfg->Header.OemTblId[0]='A'; 	//"OEMMCFG "
//    Mcfg->Header.OemTblId[1]='M';
//    Mcfg->Header.OemTblId[2]='D';
//    Mcfg->Header.OemTblId[3]='O';
//    Mcfg->Header.OemTblId[4]='N';
//    Mcfg->Header.OemTblId[5]='T';
//    Mcfg->Header.OemTblId[6]='P';
//    Mcfg->Header.OemTblId[7]='I';

#ifdef  NB_MCFG_OEM_ID
    // User definition.
    pBS->CopyMem ((VOID*)Mcfg->Header.OemId, CONVERT_TO_STRING(NB_MCFG_OEM_ID),
          sizeof (Mcfg->Header.OemId));
#else
    // Use the definition of ACPI.sdl.
#ifdef T_ACPI_OEM_ID
    pBS->CopyMem ((VOID*)Mcfg->Header.OemId, CONVERT_TO_STRING(T_ACPI_OEM_ID),
          sizeof (Mcfg->Header.OemId));
#endif
#endif

#ifdef NB_MCFG_OEM_TBL_ID
    // User definition.
    pBS->CopyMem ((VOID*)Mcfg->Header.OemTblId, CONVERT_TO_STRING(NB_MCFG_OEM_TBL_ID),
          sizeof (Mcfg->Header.OemTblId));
#else
    // Use the definition of ACPI.sdl.
#ifdef T_ACPI_OEM_TBL_ID
    pBS->CopyMem ((VOID*)Mcfg->Header.OemTblId, CONVERT_TO_STRING(T_ACPI_OEM_TBL_ID),
          sizeof (Mcfg->Header.OemTblId));
#endif
#endif

    Mcfg->Header.OemRev = ACPI_OEM_REV;
    Mcfg->Header.CreatorId = CREATOR_ID_MS;     // "MSFT" 4D 53 46 54
    Mcfg->Header.CreatorRev = CREATOR_REV_MS;   // 0x00010013;

    // Fill MCFG Fields 
    PcieBaseAddr = PcdGet64 (PcdPciExpressBaseAddress);
    Mcfg->BaseAddr = PcieBaseAddr;              // Base address of 256MB extended config space
    Mcfg->PciSeg = 0;                           // Segment # of PCI Bus
    Mcfg->StartBus = 0;                         // Start bus number of PCI segment
    Mcfg->EndBus = (PCIEX_LENGTH >> 20) - 1;    // End bus number of PCI segment

    // Add table 
    Status = AcpiTableProtocol->InstallAcpiTable (AcpiTableProtocol, Mcfg,
                                 Mcfg->Header.Length, &McfgTblKey);
    DEBUG((DEBUG_VERBOSE, "PciHostCSHooks: ACPISupport->InstallAcpiTable(MCFG) = %r\n", Status));
    ASSERT_EFI_ERROR (Status);

    // Free memory used for table image
    pBS->FreePool(Mcfg);
    // Kill the Event
    pBS->CloseEvent (Event);
#endif

    return;
}

//----------------------------------------------------------------------------
// Following functions are HOST BRIDGE Infrastructure Overrides and Porting.
//----------------------------------------------------------------------------
/**
    This procedure will be invoked in PCI Host Bridge Protocol
    when NotifyPhase function is called with phase
    EfiPciHostBridgeBeginEnumeration.

    @param ResAllocProtocol Pointer to Host Bridge Resource
        Allocation Protocol.
    @param RbIoProtocolBuffer Pointer to Root Bridge I/O Protocol.
    @param RbCount Root Bridge counter.

    @retval EFI_STATUS

    @note  Porting required if needed.
**/

EFI_STATUS
HbNotifyCspBeforeEnumeration(
  IN    EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL    *ResAllocProtocol,
  IN    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL                     **RbIoProtocolBuffer,
  IN    UINTN                                               RbCount
)
{
    EFI_STATUS  Status = EFI_SUCCESS;
//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
//Any Additional Variables goes here


//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
    return Status;
}

/**
    This function will be invoked in PCI Host Bridge Driver
    before converting all Non Existant MMIO into PCI MMIO.
    In order to allow CSP code do aome none standard conversion.

    @param ImageHandle - this image Handle
    @param ControllerHandle - Controller(RB) Handle (Optional).

    @retval EFI_STATUS
            EFI_UNSUPPORTED - means use default MMIO convertion.
            EFI_SUCCESS - CSP code has been converted MMIO itself.
            ANYTHING else - ERROR.
            
    @note  Porting required if needed.
**/
EFI_STATUS HbCspConvertMemoryMapIo (
            IN EFI_HANDLE      ImageHandle,
            IN EFI_HANDLE      ControllerHandle)
{
    EFI_STATUS  Status = EFI_UNSUPPORTED;

    // Any Additional Variables goes here
 //---------------------------------------   
    

    return Status;
}

EFI_STATUS HbCspConvertMemoryMapMmio (
            IN EFI_HANDLE      ImageHandle,
            IN EFI_HANDLE      ControllerHandle)
{
    EFI_STATUS  Status = EFI_UNSUPPORTED;

    // Any Additional Variables goes here
 //---------------------------------------   
    

    return Status;
}

/**
    This procedure will be invoked in PCI Host Bridge Protocol
    when NotifyPhase function is called with phase
    EfiPciHostBridgeBeginBusAllocation.

    @param ResAllocProtocol Pointer to Host Bridge Resource
        Allocation Protocol.
    @param RbIoProtocolBuffer Pointer to Root Bridge I/O Protocol.
    @param RbCount Root Bridge counter.

    @retval EFI_STATUS

    @note  Porting required if needed.
**/

EFI_STATUS
HbNotifyCspBeginBusAllocation(
  IN    EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL    *ResAllocProtocol,
  IN    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL                     **RbIoProtocolBuffer,
  IN    UINTN                                               RbCount
)
{
    EFI_STATUS  Status = EFI_SUCCESS;
//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
//Any Additional Variables goes here


//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
    return Status;
}

/**
    This procedure will be invoked in PCI Host Bridge Protocol
    when NotifyPhase function is called with phase
    EfiPciHostBridgeEndBusAllocation

    @param ResAllocProtocol Pointer to Host Bridge Resource
        Allocation Protocol.
    @param RbIoProtocolBuffer Pointer to Root Bridge I/O Protocol.
    @param RbCount Root Bridge counter.

    @retval EFI_STATUS

    @note  Porting required if needed.
**/

EFI_STATUS
HbNotifyCspEndBusAllocation(
  IN    EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL    *ResAllocProtocol,
  IN    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL                     **RbIoProtocolBuffer,
  IN    UINTN                                               RbCount
)
{
    EFI_STATUS  Status = EFI_SUCCESS;
//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
//Any Additional Variables goes here


//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
    return Status;
}


/**
    This procedure will be invoked in PCI Host Bridge Protocol
    when NotifyPhase function is called with phase
    EfiPciHostBridgeBeginResourceAllocation.

    @param ResAllocProtocol Pointer to Host Bridge Resource
        Allocation Protocol.
    @param RbIoProtocolBuffer Pointer to Root Bridge I/O Protocol.
    @param RbCount Root Bridge counter.

    @retval EFI_STATUS

    @note  Porting required if needed.
**/

EFI_STATUS
HbNotifyCspBeginResourceAllocation(
  IN    EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL    *ResAllocProtocol,
  IN    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL                     **RbIoProtocolBuffer,
  IN    UINTN                                               RbCount
)
{
    EFI_STATUS  Status = EFI_SUCCESS;
//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
//Any Additional Variables goes here


//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
    return Status;
}

/**
    This procedure will be invoked in PCI Host Bridge Protocol
    when NotifyPhase function is called with phase
    EfiPciHostBridgeAllocateResources.

    @param ResAllocProtocol Pointer to Host Bridge Resource
        Allocation Protocol.
    @param RbIoProtocolBuffer Pointer to Root Bridge I/O Protocol.
    @param RbCount Root Bridge counter.

    @retval EFI_STATUS

    @note  Porting required if needed.
**/

EFI_STATUS
HbNotifyCspAllocateResources(
  IN    EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL    *ResAllocProtocol,
  IN    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL                     **RbIoProtocolBuffer,
  IN    UINTN                                               RbCount
)
{
    EFI_STATUS  Status = EFI_SUCCESS;
//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
//Any Additional Variables goes here


//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
    return Status;
}

/**
    This procedure will be invoked in PCI Host Bridge Protocol
    when NotifyPhase function is called with phase
    EfiPciHostBridgeSetResources.

    @param ResAllocProtocol Pointer to Host Bridge Resource
        Allocation Protocol.
    @param RbIoProtocolBuffer Pointer to Root Bridge I/O Protocol.
    @param RbCount Root Bridge counter.

    @retval EFI_STATUS

    @note  Porting required if needed.
**/

EFI_STATUS
HbNotifyCspSetResources(
  IN    EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL    *ResAllocProtocol,
  IN    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL                     **RbIoProtocolBuffer,
  IN    UINTN                                               RbCount
)
{
    EFI_STATUS  Status = EFI_SUCCESS;
//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
//Any Additional Variables goes here


//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
    return Status;
}

/**
    This procedure will be invoked in PCI Host Bridge Protocol
    when NotifyPhase function is called with phase
    EfiPciHostBridgeEndResourceAllocation

    @param ResAllocProtocol Pointer to Host Bridge Resource
        Allocation Protocol.
    @param RbIoProtocolBuffer Pointer to Root Bridge I/O Protocol.
    @param RbCount Root Bridge counter.

    @retval EFI_STATUS

    @note  Porting required if needed.
**/

EFI_STATUS
HbNotifyCspEndResourceAllocation(
  IN    EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL    *ResAllocProtocol,
  IN    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL                     **RbIoProtocolBuffer,
  IN    UINTN                                               RbCount
)
{
    EFI_STATUS  Status = EFI_SUCCESS;
//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
//Any Additional Variables goes here


//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
    return Status;
}

/**
    This procedure will be invoked in PCI Host Bridge Protocol
    when NotifyPhase function is called with phase
	EfiPciHostBridgeEndEnumeration.

    @param ResAllocProtocol Pointer to Host Bridge Resource Allocation Protocol.
    @param RbIoProtocolBuffer Pointer to Root Bridge I/O Protocol.
    @param RbCount Root Bridge counter.

    @retval EFI_STATUS

    @note  Porting required if needed.
**/

EFI_STATUS
HbNotifyCspEndEnumeration (
    IN EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL *ResAllocProtocol,
    IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL                  **RbIoProtocolBuffer,
    IN UINTN                                            RbCount )
{
    EFI_STATUS  Status = EFI_SUCCESS;

    // Any Additional Variables goes here

    return Status;
}

/**
    This procedure will be invoked in PCI Host Bridge Protocol
    StartBusEnumeration function, it must prepare initial Bus
    ACPI Resource

    @param HostBrgData Pointer to Host Bridge private structure data.
    @param RootBrgData Pointer to Root Bridge private structure data.
    @param RootBrgIndex Root Bridge index (0 Based).

    @retval EFI_STATUS

    @note  Porting required if needed.
**/

EFI_STATUS
HbCspStartBusEnumeration(
  IN    PCI_HOST_BRG_DATA   *HostBrgData,
  IN    PCI_ROOT_BRG_DATA   *RootBrgData,
  IN    UINTN               RootBrgIndex
)
{
    EFI_STATUS  Status = EFI_SUCCESS;

//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
//Any Additional Variables goes here

//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
    return Status;
}

/**
    This procedure will be invoked in PCI Host Bridge Protocol
    SubmitBusNumbers function.

    @param HostBrgData Pointer to Host Bridge private structure data.
    @param RootBrgData Pointer to Root Bridge private structure data.
    @param RootBrgIndex Root Bridge index (0 Based).

    @retval EFI_STATUS

    @note  Porting required if needed.
**/

EFI_STATUS
HbCspSetBusNnumbers(
  IN    PCI_HOST_BRG_DATA   *HostBrgData,
  IN    PCI_ROOT_BRG_DATA   *RootBrgData,
  IN    UINTN               RootBrgIndex
)
{
#if PCI_BUS_VER_COMBINED > 0x408a // if PciBus version is greater than PciBus_15
	// Starting from PciBus_16, PciHostBridge driver expects EFI_UNSUPPORTED when platform does not support custom bus handling
	EFI_STATUS  Status = EFI_UNSUPPORTED;
#else
	// Prir to PciBus_16, PciHostBridge driver expects EFI_UNSUPPORTED when platform does not support custom bus handling
	EFI_STATUS  Status = EFI_SUCCESS;
#endif
	//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
	//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
	//Any Additional Variables goes here


	//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
	//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
	return Status;
}

/**
    This procedure will be invoked in PCI Host Bridge Protocol
    SubmitResources function.

    @param HostBrgData Pointer to Host Bridge private structure data.
    @param RootBrgData Pointer to Root Bridge private structure data.
    @param RootBrgIndex Root Bridge index (0 Based).

    @retval EFI_STATUS

    @note  Porting required if needed.
**/

EFI_STATUS
HbCspSubmitResources(
  IN    PCI_HOST_BRG_DATA   *HostBrgData,
  IN    PCI_ROOT_BRG_DATA   *RootBrgData,
  IN    UINTN               RootBrgIndex
)
{
    EFI_STATUS  Status = EFI_SUCCESS;
//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
//Any Additional Variables goes here


//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
    return Status;
}

/**
    This procedure will be invoked during PCI bus enumeration,
    it determines the PCI memory base address below 4GB whether
    it is overlapping the main memory, if it is overlapped, then
    updates MemoryCeiling variable and reboot.

    @param HostBrgData Pointer to Host Bridge private structure data.
    @param RootBrgData Pointer to Root Bridge private structure data.
    @param RootBrgIndex Root Bridge index (0 Based).

    @retval EFI_STATUS

    @note  Porting required if needed.
**/

EFI_STATUS
HbCspAdjustMemoryMmioOverlap(
  IN    PCI_HOST_BRG_DATA   *HostBrgData,
  IN    PCI_ROOT_BRG_DATA   *RootBrgData,
  IN    UINTN               RootBrgIndex
)
{
    return EFI_SUCCESS;
}

/**
    This function will be invoked after Initialization of generic
    part of the Host and Root Bridges.
    All Handles for PCIHostBrg and PciRootBrg has been created
    and Protocol Intergaces installed.

    @param HostBrgData Pointer to Host Bridge private structure data.

    @retval EFI_STATUS

    @note  Porting required if needed.
**/

EFI_STATUS
HbCspBasicChipsetInit(
  IN    PCI_HOST_BRG_DATA   *HostBrg0
)
{
    EFI_STATUS      Status;
    DXE_SERVICES    *Dxe;   

    Status = LibGetDxeSvcTbl(&Dxe);
    ASSERT_EFI_ERROR (Status);
    if (EFI_ERROR (Status))
        return Status;

    // Now for New Chipset which has PCI Express support we have to build 
    // MCFG Table to inform OS about PCIE Ext cfg space mapping
    Status = RegisterProtocolCallback (&gEfiAcpiTableProtocolGuid, CreateNbAcpiTables,
              NULL, &AcpiEvent, &AcpiReg);
    ASSERT_EFI_ERROR (Status);

    // If this protocol has been installed we can use it rigth on the way
    CreateNbAcpiTables (AcpiEvent, NULL);

    return EFI_SUCCESS;
}

/**
    This function will be invoked when Pci Host Bridge driver runs  
    out of resources.

    @param HostBrgData Pointer to Host Bridge private structure data.

    @retval EFI_STATUS

    @note  Porting required if needed.
**/

EFI_STATUS
HbCspGetProposedResources (
  IN    PCI_HOST_BRG_DATA   *HostBrgData,
  IN    PCI_ROOT_BRG_DATA   *RootBrgData,
  IN    UINTN               RootBrgNumber
)
{
    EFI_STATUS  Status = EFI_SUCCESS;

    // Any Additional Variables goes here
    return Status;
}

/**
    This function is called for all the PCI controllers that
    the PCI bus driver finds.
    It can be used to Preprogram the controller.

    @param HostBrgData Pointer to Host Bridge private structure data.
    @param RootBrgData Pointer to Root Bridge private structure data.
    @param RootBrgNumber Root Bridge number (0 Based).
    @param PciAddress Address of the controller on the PCI bus.
    @param Phase The phase during enumeration

    @retval EFI_STATUS

    @note  Porting required if needed.
**/

EFI_STATUS
HbCspPreprocessController(
  IN    PCI_HOST_BRG_DATA                               *HostBrgData,
  IN    PCI_ROOT_BRG_DATA                               *RootBrgData,
  IN    UINTN                                           RootBrgNumber,
  IN    EFI_PCI_CONFIGURATION_ADDRESS                   PciAddress,
  IN    EFI_PCI_CONTROLLER_RESOURCE_ALLOCATION_PHASE    Phase
)
{
    EFI_STATUS  Status = EFI_SUCCESS;
//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
//Any Additional Variables goes here


//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
    return Status;
}

/**
    This function is invoked in PCI Host Bridge Driver when time
    to ask GCD for resources. You can overwrite a default
    algorithm used to allocate resources for the Root Bridge.

    @param HostBrgData Pointer to Host Bridge private structure data.
    @param RootBrgData Pointer to Root Bridge private structure data.
    @param RootBrgIndex Root Bridge index (0 Based).

    @retval EFI_STATUS

    @note  Porting required if needed.
**/

EFI_STATUS
HbCspAllocateResources(
  IN    PCI_HOST_BRG_DATA   *HostBrgData,
  IN    PCI_ROOT_BRG_DATA   *RootBrgData,
  IN    UINTN               RootBrgIndex
)
{
    UINT32                          PciValue;
    UINT64                          MemoryCeiling = 0;
    UINTN                           DataSize;
    UINTN                           NumberOfDescriptors;
    UINTN                           i;
    UINT64                          NewMemoryCeiling = 0xFFFFFFFF;
    EFI_STATUS                      Status = EFI_SUCCESS;
    ASLR_QWORD_ASD                  *Res;
    PCI_ROOT_BRG_DATA               *RbData;
    EFI_PHYSICAL_ADDRESS            Highest4gMem = 0;
    EFI_PHYSICAL_ADDRESS            LowestMmio = 0xFFFFFFFF;
    EFI_PHYSICAL_ADDRESS            HighestUnder4gMmio = 0x0;
    EFI_PHYSICAL_ADDRESS            LowestAllocMmio = 0xFFFFFFFF;
    // cppcheck-suppress unreadVariable
    EFI_PHYSICAL_ADDRESS            LowestAbove4GMmio = 0xFFFFFFFFFFFFFFFF;
    EFI_PHYSICAL_ADDRESS            HighestAbove4GMmio = 0x0;
    EFI_PHYSICAL_ADDRESS            LowestAbove4GAllocMmio = 0xFFFFFFFFFFFFFFFF;
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *RtBrdg;
    UINTN                           Index;
    EFI_GCD_MEMORY_SPACE_DESCRIPTOR *MemorySpaceMap;
static UINT8                        MmioReg = AMD_K8_nF1_MMIO_B0;
static UINT8                        PciIoReg = AMD_K8_nF1_PCIIO_B0;
static UINT8                        PciCfgReg = AMD_K8_nF1_CFGBASE0;
    BOOLEAN                         ResetNeeded = FALSE;
    ACPI_RES_DATA                   *Ar;
    DXE_SERVICES                    *Dxe;   
    UINT64                          MmioBaseAddress = 0;
    UINT64                          MmioLength = 0;
    UINT32                          SizeInByte;
    UINT64                          Value64;
    AMD_APCB_SERVICE_PROTOCOL       *AmdApcbProtocol = NULL;
    UINT32                          DstFabricId;

    AllocateRbResources(RootBrgData);

//------------------------------------
    Status = LibGetDxeSvcTbl (&Dxe);
    ASSERT_EFI_ERROR (Status);
    if(EFI_ERROR(Status))
        return Status;

    RtBrdg = &RootBrgData->RbIoProtocol;
//------------------------------------
    DataSize = sizeof (MemoryCeiling);
    Status = pRS->GetVariable (MemoryCeilingVariable, &AmiGlobalVariableGuid,
                   NULL, &DataSize, &MemoryCeiling);
    if (Status == EFI_NOT_FOUND)    // If memceil not found, set default value as memoryceiling
    {
#if defined(FIXED_MMIO_RESOURCE) && (FIXED_MMIO_RESOURCE != 0)
        MemoryCeiling = 0xFFFFFFFF - FIXED_MMIO_RESOURCE + 1;   // Minimum is Predefined by BIOS Porting
#else
        MemoryCeiling = (UINT64)MCT_BOTTOM_IO_VALUE << 24;
#endif
    }

    if (!IsFamily15h())
    {
        Status = pBS->LocateProtocol(&gAmdApcbDxeServiceProtocolGuid, NULL, &AmdApcbProtocol);
        if (Status == EFI_SUCCESS)
        {
            SizeInByte = 1;
            Value64 = 0;
            Status = AmdApcbProtocol->ApcbGetConfigParameter(AmdApcbProtocol, APCB_ID_CONFIG_DF_BOTTOMIO, &SizeInByte, &Value64);
            if (Status == EFI_SUCCESS)
            {
                MemoryCeiling = (UINT64)Value64 << 24;
            }
        }
    }
    // Memory sizing uses memory ceiling to set top of memory.
    DEBUG((DEBUG_VERBOSE, "!!! Previously saved  MemoryCeiling:0x%lX !!!\n", MemoryCeiling));

    Status = Dxe->GetMemorySpaceMap (&NumberOfDescriptors, &MemorySpaceMap);
    ASSERT_EFI_ERROR (Status);

    // Find the lowest MMIO and lowest allocated MMIO in GCD.
    DEBUG((DEBUG_VERBOSE, "Finding EFI_GCD_MEMORY_SPACE_DESCRIPTORs:\n"));
    for (i = 0; i < NumberOfDescriptors; ++i)
    {
        EFI_GCD_MEMORY_SPACE_DESCRIPTOR *Descr = &MemorySpaceMap[i];
        EFI_PHYSICAL_ADDRESS            Base = Descr->BaseAddress;
        EFI_PHYSICAL_ADDRESS            Length = Descr->Length;

        DEBUG((DEBUG_VERBOSE, "    Base=%16lXh  Length     = %29lXh\n", Base, Descr->Length)); 
        DEBUG((DEBUG_VERBOSE, "                            Attributes = %29lXh (%a)\n",
         Descr->Attributes, GetAttributeString(Descr->Attributes))); 
        DEBUG((DEBUG_VERBOSE, "                            Type       = %a\n",
         MemType[Descr->GcdMemoryType])); 

        // Find highest system below 4GB memory.
        // Treat any non MMIO as system memory. Not all system memory is reported as system memory,
        // such as SMM.
        if (Descr->GcdMemoryType != EfiGcdMemoryTypeMemoryMappedIo && Base < LowestMmio)
        {
            EFI_PHYSICAL_ADDRESS    EndMem = Base + Descr->Length - 1;

            if (EndMem > Highest4gMem && EndMem <= 0xFFFFFFFF) 
                Highest4gMem = EndMem;

            // Find Lowest and Highest mmio above system memory.
        }
        else if (Descr->GcdMemoryType == EfiGcdMemoryTypeMemoryMappedIo)
        {
            if (Base >= 0x100000)
            {
                if (Base < LowestMmio)
                    LowestMmio = Base;
                else
				{
					// cppcheck-suppress unreadVariable
                    LowestAbove4GMmio = Base;
				}
                if (Base > HighestUnder4gMmio && Base < 0x100000000)
                    HighestUnder4gMmio = Base;
                else if (Base >= HighestAbove4GMmio && Base > 0x100000000)
                    HighestAbove4GMmio = Base + Length;

                // If ImageHandle, then MMIO is allocated.
                if (Base < LowestAllocMmio && Descr->ImageHandle) 
                    LowestAllocMmio = Base;
                else if (Base < LowestAbove4GAllocMmio && Base > 0x100000000 && Descr->ImageHandle)
                    LowestAbove4GAllocMmio = Base;
            }
        }
    }

    DEBUG((DEBUG_VERBOSE, "Highest4gMem = 0x%X  LowestMmio = 0x%X   LowestAllocMmio = 0x%X  HighestUnder4gMmio = 0x%lX\n",
           Highest4gMem, LowestMmio, LowestAllocMmio, HighestUnder4gMmio)); 

    DEBUG((DEBUG_VERBOSE, "LowestAbove4GMmio = 0x%lX   LowestAbove4GAllocMmio = 0x%lX  HighestAbove4GMmio = 0x%lX\n",
           LowestAbove4GMmio, LowestAbove4GAllocMmio, HighestAbove4GMmio)); 

    pBS->FreePool (MemorySpaceMap);

    if (Highest4gMem + 1 != LowestMmio)
        DEBUG((DEBUG_VERBOSE, "PciHostCSHooks: System Memory and MMIO are not consequitive.\n  Top of Below 4G Memory: %lX\n   Bottom of MMIO: %x%x\n",
         Highest4gMem, LowestMmio));

    NewMemoryCeiling = (UINT64)LowestAllocMmio;
#if defined(FIXED_MMIO_RESOURCE) && (FIXED_MMIO_RESOURCE != 0)
    if(MemoryCeiling < LowestAllocMmio)
        NewMemoryCeiling = (UINT64)MemoryCeiling;
#endif

    // Find any MMIO that could not be allocated due to small of MMIO region.
    for (i = 0; i < RootBrgData->ResCount; ++i)
    {
        EFI_PHYSICAL_ADDRESS    NeededBottomMmio;
        Res = RootBrgData->RbRes[i];

        // Any unallocated MMIO will have res->_MIN set to zero for the MMIO type.
        if (Res->Type != ASLRV_SPC_TYPE_MEM || Res->_GRA != 32 || Res->_MIN) 
            continue;

        // Determine new memory ceiling variable needed to allocate this memory.
        NeededBottomMmio = LowestAllocMmio - Res->_LEN;

        // Round down. If resource is not allocated, _MAX contains granularity.
        NeededBottomMmio &= ~Res->_MAX;
        if (NeededBottomMmio < NewMemoryCeiling) 
            NewMemoryCeiling = (UINT64) NeededBottomMmio; 
    }

    //Allocate NbPciCommonSetup buffer
    Status = pBS->AllocatePool(
                            EfiBootServicesData,
                            sizeof(PCI_COMMON_SETUP_DATA),
                            &NbPciCommonSetup);
    if (Status == EFI_SUCCESS)
        pBS->SetMem(NbPciCommonSetup, sizeof(PCI_COMMON_SETUP_DATA), 0);
    else
        ASSERT_EFI_ERROR(Status);

#if (PCI_SETUP_USE_APTIO_4_STYLE == 0)
    Status = AmiPciGetCommonSetupData(NbPciCommonSetup);
#else
    Status = AmiPciGetSetupData(NULL, NbPciCommonSetup, NULL);
#endif

    if (NbPciCommonSetup->Above4gDecode == 1)
    {
        NewMemoryCeiling &= 0xF0000000;     // For Tseg alignment and PT needs resource at 0xF1000000
    }
    else if (!IsFamily15h())
    {
        NewMemoryCeiling &= 0xF0000000;     // Zen only bits [31:28] are usable
    }
    DEBUG((DEBUG_VERBOSE, "NewMemoryCeiling = 0x%lX\n", NewMemoryCeiling)); 
    
#if (NB_DYNAMIC_MEMORY_CEILING != 0)
    if (NewMemoryCeiling < 0xFFFFFFFF)
    {   // Check if a NewMemory Ceiling is needed.
        // if TOM < NewMemoryCeiling, then its going to take too much of our memory space so
        // fix the NewMemoryCeiling in NVRAM.
        // if MemoryCeiling == NewMemoryCeiling, then do nothing.
        // Say if MemoryCeiling > NewMemoryCeiling, then also we have to set the NewMemoryCeiling, since it
        // has been computed dynamically and if we dont consider the NewMemoryCeiling then, some of the devices wont work.
        if (MemoryCeiling != NewMemoryCeiling)
        {
            // Set new memory ceiling variable.
            Status = pRS->SetVariable (L"MemCeil.", &AmiGlobalVariableGuid,
                           EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
                           sizeof (UINT64), &NewMemoryCeiling);

            if (!IsFamily15h())
            {
                if (AmdApcbProtocol)
                {
                    SizeInByte = 1;
                    Value64 = (UINT64)NewMemoryCeiling >> 24;
                    DEBUG ((DEBUG_VERBOSE, "\tSet APCB DF BottomIo to new value: 0x%lx\n", (UINT32)Value64));
                    Status = AmdApcbProtocol->ApcbSetConfigParameter(AmdApcbProtocol, APCB_ID_CONFIG_DF_BOTTOMIO, &SizeInByte, &Value64);
                    DEBUG ((DEBUG_VERBOSE, "\tSet APCB DF BottomIo Status : %x\n", Status));
                    Status = AmdApcbProtocol->ApcbFlushData(AmdApcbProtocol);
                    DEBUG ((DEBUG_VERBOSE, "\tSet APCB DF BottomIo Shadow Copy Status : %x\n", Status));
                }
            }

            DEBUG((DEBUG_VERBOSE, "Adjusting maximum top of RAM.(MemoryCeiling != NewMemoryCeiling)\n Resetting System.\n"));

#if NV_SIMULATION != 1

#if SM_BRINGUP_TEMP == 1
            if (IsFamily15h())
            {
                ResetNeeded = TRUE;
            }
#else
            ResetNeeded = TRUE;
#endif

#endif
        }
    }
#endif  // (NB_DYNAMIC_MEMORY_CEILING != 0)

    if (GetBootMode() != BOOT_IN_RECOVERY_MODE)
    {
        if (ResetNeeded)
            pRS->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);
    }

    Status = pBS->LocateProtocol(&gEfiS3SaveStateProtocolGuid, NULL, &BootScriptSave);

    if (IsFamily15h())
    {
        for (i = 0; i < HostBrgData->RootBridgeCount; i++)
        {
            RbData = HostBrgData->RootBridges[i];
            if (RbData->RbHandle == RootBrgData->RbHandle)
            {
                DEBUG((DEBUG_VERBOSE, "Root No = %X\n", i));
            }
        }

        PciIoReg = AMD_K8_nF1_PCIIO_B0;
        for (Index = 0; Index < RootBrgData->ResCount; Index++)
        {   // Start of Index loop
            Res = RootBrgData->RbRes[Index];
            if (Res->Type == ASLRV_SPC_TYPE_IO)
            {
                Ar = &RootBrgData->AcpiRbRes[raIo];
                PciValue = (UINT32)(Ar->Max & 0xF000);

                RtBrdg->Pci.Write(RtBrdg, EfiPciWidthUint32, 
                        NB_PCI_CFG_ADDRESS (0, (AMD_K8_NODE0_DEV), 
                                AMD_K8_ADRM_FUNC, (PciIoReg + 4)), // 0xC4
                                1, &PciValue);

                // Program the PCI I/O base for node entry
                PciValue = (UINT32)(Res->_MIN & ~0xFFF) | 0x03; 
                if (RootBrgData->Supports & EFI_PCI_ATTRIBUTE_VGA_IO)
					PciValue |= 0x10;

                DEBUG((DEBUG_VERBOSE, 
                        "AMD_K8_ADRM_FUNC: Pci.Write(0x%X, 0x%X, 0x%X{b%x|d%X|f%X|r%X}, 0x%X, 0x%X(=0x%X))\n", 
                        RtBrdg, EfiPciWidthUint32, 
                        NB_PCI_CFG_ADDRESS (0, AMD_K8_NODE0_DEV, AMD_K8_ADRM_FUNC, PciIoReg),
                        0, AMD_K8_NODE0_DEV, AMD_K8_ADRM_FUNC, PciIoReg, 1, &PciValue, PciValue));

                RtBrdg->Pci.Write(RtBrdg, EfiPciWidthUint32, 
                              NB_PCI_CFG_ADDRESS (0, AMD_K8_NODE0_DEV, AMD_K8_ADRM_FUNC, PciIoReg), // 0xC0
                              1, &PciValue);
                PciIoReg += 8;
            }
            else if(ASLRV_SPC_TYPE_BUS == Res->Type)
            {
                PciValue = ((UINT32)Shl64(Res->_MAX, 24)) | ((UINT32)Shl64(Res->_MIN, 16))
                             | 0x03;

                RtBrdg->Pci.Write(RtBrdg, EfiPciWidthUint32, 
                    NB_PCI_CFG_ADDRESS (0, AMD_K8_NODE0_DEV, 
                    AMD_K8_ADRM_FUNC, PciCfgReg), 1, &PciValue);
                PciCfgReg += 4;
            }
        }//end of Index loop                

        ClearMemoryMappedIoInfo_Below4Gb_Family15H(RtBrdg);

        // Programming the root bridge registers
        MmioReg = AMD_K8_nF1_MMIO_B0;

        PciValue = (UINT32)Shr64((HighestUnder4gMmio & ~0xFFFF), 8);
        DEBUG((DEBUG_VERBOSE, "MMIO B0 Limit value 0x%X.\n", PciValue));
                            
        RtBrdg->Pci.Write(RtBrdg, EfiPciWidthUint32, 
                NB_PCI_CFG_ADDRESS (0, (AMD_K8_NODE0_DEV), 
                AMD_K8_ADRM_FUNC, (MmioReg + 4)), 1, &PciValue);
    
        // Program the Memory I/O base for node entry
        PciValue = (UINT32)Shr64((NewMemoryCeiling & ~0xFFFF), 8) | 0x03; 
        DEBUG((DEBUG_VERBOSE, "MMIO B0 Base value 0x%X.\n", PciValue));

        RtBrdg->Pci.Write(RtBrdg, EfiPciWidthUint32, 
                NB_PCI_CFG_ADDRESS (0, (AMD_K8_NODE0_DEV), 
                AMD_K8_ADRM_FUNC, MmioReg),
                1, &PciValue);

        if (NbPciCommonSetup->Above4gDecode == 1)
        {
            // Programming the root bridge MMIO registers above 4GB
            MmioReg = AMD_K8_nF1_MMIO_B1;
            PciValue = (UINT32)Shr64((HighestAbove4GMmio & ~0xFFFF), 8);
            DEBUG((DEBUG_VERBOSE, "MMIO B1 Limit value 0x%X.\n", PciValue));

            RtBrdg->Pci.Write(RtBrdg, EfiPciWidthUint32, 
                    NB_PCI_CFG_ADDRESS (0, (AMD_K8_NODE0_DEV), 
                    AMD_K8_ADRM_FUNC, (MmioReg + 4)), 1, &PciValue);

            PciValue = (UINT32)Shr64((LowestAbove4GAllocMmio & ~0xFFFF), 8) | 0x03; 
            DEBUG((DEBUG_VERBOSE, "MMIO B1 Base value 0x%X.\n", PciValue));

            RtBrdg->Pci.Write(RtBrdg, EfiPciWidthUint32, 
                    NB_PCI_CFG_ADDRESS (0, (AMD_K8_NODE0_DEV), 
                    AMD_K8_ADRM_FUNC, MmioReg),
                    1, &PciValue);
        }
    }
    else
    {
        // It's family 17h
        for (i = 0; i < HostBrgData->RootBridgeCount; i++)
        {
            RbData = HostBrgData->RootBridges[i];
            if (RbData->RbHandle == RootBrgData->RbHandle)
            {
                DEBUG((DEBUG_VERBOSE, "Root No = %X\n", i));
            }
        }

        PciIoReg = AMD_D18_F0_C0;
        PciCfgReg = AMD_D18_F0_A0;
        DEBUG((DEBUG_VERBOSE, "RootBrgData->ResCount = %lX\n", RootBrgData->ResCount));

        RtBrdg->Pci.Read(RtBrdg, EfiPciWidthUint32, 
                NB_PCI_CFG_ADDRESS (0, (AMD_K8_NODE0_DEV),
                        AMD_K8_LDT_FUNC, (PciIoReg + 4)), // 0xC4 - Read DstFabricID
                        1, &DstFabricId);
        DstFabricId &= 0xFF;

        for (Index = 0; Index < RootBrgData->ResCount; Index++)
        {   // Start of Index loop
            Res = RootBrgData->RbRes[Index];
            DEBUG((DEBUG_VERBOSE, "Res->Type = %x\n", Res->Type));
            if (Res->Type == ASLRV_SPC_TYPE_IO)
            {
                Ar = &RootBrgData->AcpiRbRes[raIo];
                PciValue = (UINT32)(Ar->Max & 0x00FFF000 | DstFabricId);
                DEBUG((DEBUG_VERBOSE, "Io limit PciValue = %lx\n", PciValue));
                RtBrdg->Pci.Write(RtBrdg, EfiPciWidthUint32, 
                        NB_PCI_CFG_ADDRESS (0, (AMD_K8_NODE0_DEV),
                                AMD_K8_LDT_FUNC, (PciIoReg + 4)), // 0xC4 - Write back with I/O limit address
                                1, &PciValue);
                BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
                                                    CSP_BOOT_SCRIPT_SERVICE_EX(BootScriptSave),
                                                    EfiPciWidthUint32, EFI_PCI_ADDRESS(0, AMD_K8_NODE0_DEV, AMD_K8_LDT_FUNC, (PciIoReg + 4)), 1, &PciValue);

                // Program the PCI I/O base for node entry
                PciValue = (UINT32)(Res->_MIN & ~0xFFF) | 0x03; 
                if (RootBrgData->Supports & EFI_PCI_ATTRIBUTE_VGA_IO) PciValue |= 0x10;
                DEBUG((DEBUG_VERBOSE, "Io base PciValue = %lx\n", PciValue));
                DEBUG((DEBUG_VERBOSE, 
                        "AMD_K8_ADRM_FUNC: Pci.Write(0x%X, 0x%X, 0x%X{b%x|d%X|f%X|r%X}, 0x%X, 0x%X(=0x%lX))\n", 
                        RtBrdg, EfiPciWidthUint32, 
                        NB_PCI_CFG_ADDRESS (0, AMD_K8_NODE0_DEV, AMD_K8_LDT_FUNC, PciIoReg),
                        0, AMD_K8_NODE0_DEV, AMD_K8_LDT_FUNC, PciIoReg, 
                        1, &PciValue, PciValue));

                RtBrdg->Pci.Write(RtBrdg, EfiPciWidthUint32, 
                              NB_PCI_CFG_ADDRESS (0, AMD_K8_NODE0_DEV, AMD_K8_LDT_FUNC, PciIoReg), // 0xC0
                              1, &PciValue);
                BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
                                                    CSP_BOOT_SCRIPT_SERVICE_EX(BootScriptSave),
                                                    EfiPciWidthUint32, EFI_PCI_ADDRESS(0, AMD_K8_NODE0_DEV, AMD_K8_LDT_FUNC, PciIoReg), 1, &PciValue);

                PciIoReg += 8;
            }
            else if(ASLRV_SPC_TYPE_BUS == Res->Type)
            {
                PciValue = ((UINT32)Shl64 (Res->_MAX, 24)) | ((UINT32)Shl64 (Res->_MIN, 16))
                             | (UINT32)(Shl64 (DstFabricId, 4)) | 0x03; // Destination FabricID[11:4] for die 0, WE/RE[1:0]
                DEBUG((DEBUG_VERBOSE, "Configuration PciValue = %lx\n", PciValue));
                RtBrdg->Pci.Write(RtBrdg, EfiPciWidthUint32, 
                            NB_PCI_CFG_ADDRESS (0, AMD_K8_NODE0_DEV, 
                            AMD_K8_LDT_FUNC, PciCfgReg), 1, &PciValue);
                BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
                                                    CSP_BOOT_SCRIPT_SERVICE_EX(BootScriptSave),
                                                    EfiPciWidthUint32, EFI_PCI_ADDRESS(0, AMD_K8_NODE0_DEV, AMD_K8_LDT_FUNC, PciCfgReg), 1, &PciValue);
                PciCfgReg += 4;
            }
        }//end of Index loop

        // Program legacy VGA register
        LegacyVgaRouting17h(RbData, (UINT8)i);
        
        // Programming the root bridge MMIO registers

        ClearMemoryMappedIoInfo_Below4Gb_Family17H(RtBrdg);
#if NV_SIMULATION != 1
        MmioBaseAddress = NewMemoryCeiling;
#else
//        MmioBaseAddress = (UINT64)(Shl64(MCT_BOTTOM_IO_VALUE, 24));
        MmioBaseAddress = (UINT64)(Shl64(0xE0, 24));
#endif
        MmioLength = HighestUnder4gMmio - MmioBaseAddress;

        DEBUG((DEBUG_VERBOSE, "MMIO Base Address = %lX\n", MmioBaseAddress));
        DEBUG((DEBUG_VERBOSE, "MMIO Length = %lX\n", MmioLength));

        AddMemoryMappedIoInfo_Family17H(RtBrdg, MmioBaseAddress, MmioLength, 0);

    }

    return EFI_SUCCESS;
}

//----------------------------------------------------------------------------
// Following functions are ROOT BRIDGE Infrastructure Overrides and Porting.
//----------------------------------------------------------------------------
/**
    Chipset Specific function to Map Internal Device address
    residing ABOVE 4G to the BELOW 4G address space for DMA.
    MUST BE IMPLEMENTED if CHIPSET supports address space
    decoding ABOVE 4G.

    @param RbData Root Bridge private structure data
    @param Operation Operation to provide Mapping for
    @param HostAddress HostAddress of the Device
    @param NumberOfBytes Number of Byte in Mapped Buffer.
    @param DeviceAddress Mapped Device Address.
    @param Mapping Mapping Info Structure this function must
        allocate and fill.

        EFI_STATUS
    @retval EFI_SUCCESS Successful.
    @retval EFI_UNSUPPORTED The Map function is not supported.
    @retval EFI_INVALID_PARAMETER One of the parameters has an
        invalid value.

    @note  Porting is required for chipsets that supports Decoding
              of the PCI Address Space ABOVE 4G.
**/

EFI_STATUS
RbCspIoPciMap(
  IN        PCI_ROOT_BRG_DATA                           *RbData,
  IN        EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_OPERATION   Operation,
  IN        EFI_PHYSICAL_ADDRESS                        HostAddress,
  IN OUT    UINTN                                       *NumberOfBytes,
  OUT       EFI_PHYSICAL_ADDRESS                        *DeviceAddress,
  OUT       VOID                                        **Mapping
)
{
    EFI_STATUS  Status = EFI_SUCCESS;
//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
//Porting is required for chipsets that supports Decoding of the PCI Address Space ABOVE 4G.

// Any Additional Variables goes here

// LakePort DOES NOT support decoding of the PCI resources ABOVE 4G. 
// So return EFI_UNSUPPORTED;
    *Mapping = NULL;
    Status = EFI_UNSUPPORTED;

// For Chipsets which DOES support decoding of the PCI resources ABOVE 4G.
// Here must be something like that. 
/*
    PCI_ROOT_BRIDGE_MAPPING *mapping;
//------------------------------
        //Common buffer operations can not be remapped because in such
        // operations the same buffer will be accessed by CPU and PCI hardware
        if(Operation==EfiPciOperationBusMasterCommonBuffer || Operation==EfiPciOperationBusMasterCommonBuffer64)
            return EFI_UNSUPPORTED;

        mapping =Malloc(sizeof(PCI_ROOT_BRIDGE_MAPPING));
        if(mapping==NULL) return EFI_OUT_OF_RESOURCES;
        
        mapping->Signature  = EFI_PCI_RB_MAPPING_SIGNATURE;
        mapping->Resrved    = 0;
        mapping->Operation  = Operation;
        mapping->NumPages   = EFI_SIZE_TO_PAGES(*NumberOfBytes);
        mapping->HostAddr   = HostAddress;
        mapping->DeviceAddr = 0x00000000ffffffff;

        Status = pBS->AllocatePages(AllocateMaxAddress,EfiBootServicesData,mapping->NumPages,&mapping->DeviceAddr);
        if (EFI_ERROR(Status))
        {
            pBS->FreePool(mapping);
            return Status;
        }
        *Mapping=(VOID*)mapping;

        //Here must be a way to copy context of HostDevice buffer to the Mapped one.
        //This code given as example only you might need to do some chipset programming to 
        //access PCI Address Space Above 4G

        if(Operation==EfiPciOperationBusMasterRead||Operation==EfiPciOperationBusMasterRead64)
            pBS->CopyMem( (VOID*)(UINTN)mapping->DeviceAddr,
                        (VOID*)(UINTN)mapping->HostAddr,
                        mapping->NumBytes);

        *DeviceAddress = mapping->DeviceAddr;
*/
//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
    return Status;
}

/**
    Chipset Specific function to Unmap previousely Mapped
    buffer for DMA.
    MUST BE IMPLEMENTED if CHIPSET supports address space
    decoding ABOVE 4G.

    @param RbData Root Bridge private structure data
    @param Mapping Mapping Info Structure this function must free.

        EFI_STATUS
    @retval EFI_SUCCESS Successful.
    @retval EFI_UNSUPPORTED The Unmap function is not supported.
    @retval EFI_INVALID_PARAMETER One of the parameters has an
        invalid value.

    @note  Porting required if needed.
**/

EFI_STATUS
RbCspIoPciUnmap(
  IN    PCI_ROOT_BRG_DATA       *RbData,
  OUT   PCI_ROOT_BRIDGE_MAPPING *Mapping
)
{
    EFI_STATUS  Status = EFI_SUCCESS;
//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//

// Any Additional Variables goes here

// LakePort DOES NOT support decoding of the PCI resources ABOVE 4G. 
// and for corresponded Mapping call we will return NULL as Mapping
// So return EFI_UNSUPPORTED if we get back something different;
    if (Mapping != NULL)
        return EFI_INVALID_PARAMETER;
    // For all other conditions we would return EFI_UNSUPPORTED.
    Status = EFI_UNSUPPORTED;

//for Chipsets which DOES support decoding of the PCI resources ABOVE 4G.
//And provides corresponded mapping for the host address 
//here must be something like that. 
/*
    if(Mapping->Signature!=EFI_PCI_RB_MAPPING_SIGNATURE)Status=EFI_INVALID_PARAMERTER;
    
    if(!EFI_ERROR(Status)){ 

        if (Mapping->Operation == EfiPciOperationBusMasterWrite || Mapping->Operation == EfiPciOperationBusMasterWrite64) 

        //Here must be a way to copy context of the Unmapped buffer to HostDevice.
        //This code given as example only you might need to do some chipset programming to 
        //access PCI Address Space Above 4G
        pBS->CopyMem((VOID*)(UINTN)Mapping->HostAddr,(VOID*)(UINTN)Mapping->DeviceAddr,Mapping->NumBytes);
            
        pBS->FreePages(Mapping->DeviceAddr, Mapping->NumPages);
        pBS->FreePool(Mapping);
    }
*/
//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
    return Status;
}

/**
    Chipset Specific function to do PCI RB Attributes releated
    programming.

    @param RbData Pointer to Root Bridge private structure.
    @param Attributes The Root Bridge attributes to be programming.
    @param ResourceBase Pointer to the resource base. (OPTIONAL)
    @param ResourceLength Pointer to the resource Length. (OPTIONAL)

        EFI_STATUS
    @retval EFI_SUCCESS Successful.
    @retval EFI_INVALID_PARAMETER One of the parameters has an
        invalid value.
**/

EFI_STATUS
RbCspIoPciAttributes(
  IN        PCI_ROOT_BRG_DATA   *RbData,
  IN        UINT64              Attributes,
  IN OUT    UINT64              *ResourceBase OPTIONAL,
  IN OUT    UINT64              *ResourceLength OPTIONAL
)
{
    EFI_STATUS  Status = EFI_SUCCESS;
//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
    UINT8                           RbIndex;
    STATIC UINT32                   RootCount = 0 ;
    PCI_HOST_BRG_DATA               *HostBrgData = RbData->Owner;
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *RtBrdg;

    RtBrdg = &RbData->RbIoProtocol;

    // AMD Northbridge Multi-Rootbridge Legacy PCI Express VGA Support
    DEBUG((DEBUG_VERBOSE, "RbCspIoPciAttributes: Attributes = 0x%lX !!!\n", 
        Attributes));

    if ( Attributes & (EFI_PCI_IO_ATTRIBUTE_VGA_MEMORY | EFI_PCI_IO_ATTRIBUTE_VGA_IO) )
    {
        DEBUG((DEBUG_VERBOSE, 
                "RbCspIoPciAttributes: setting legacy VGA routing\n"));
        
        // Determine the index of this root bridge
        for (RbIndex = 0; RbIndex < RbData->Owner->RootBridgeCount; RbIndex++)
        {
            if ( RbData == RbData->Owner->RootBridges[RbIndex] )
            {
                DEBUG((DEBUG_VERBOSE, "    Root No = %X\n", RbIndex));
                break;
            }
        }
        if (IsFamily15h())
//        {
            Status = LegacyVgaRouting15h (RbData, RbIndex);
//        }
//        else
//        {
//            Status = LegacyVgaRouting17h (RbData, RbIndex);
//        }
        if ( EFI_ERROR(Status) )
            DEBUG((DEBUG_VERBOSE, "LegacyVgaRouting: Failed !!!\n" ));
    }

// Support ends

//PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING////PORTING//
    return Status;
}

/**
    Read Pci Registers into buffer.
    Csp Function which actualy access PCI Config Space.
    Chipsets that capable of having PCI EXPRESS Ext Cfg Space
    transactions.
    Must Implement this access routine here.

    @param RbData Root Bridge private structure.
    @param Width PCI Width.
    @param Address PCI Address.
    @param Count Number of width reads/writes.
    @param Buffer Buffer where read/written.
    @param Write Set if write.

        EFI_STATUS
    @retval EFI_SUCCESS Successful read.
    @retval EFI_INVALID_PARAMETER One of the parameters has an
**/

EFI_STATUS
RootBridgeIoPciRW(
  IN        VOID                                    *RbData,
  IN        EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH   Width,
  IN        UINT64                                  Address,
  IN        UINTN                                   Count,
  IN OUT    VOID                                    *Buffer,
  IN        BOOLEAN                                 Write
)
{
    static UINT64 *MultiSegPcieBaseAddressArray = NULL;
    static UINT32 MaxSegment = 1;
    
    BOOLEAN ValidCfg = TRUE;
    UINT64 PciExpressBaseAddress = 0;
    UINT8   IncrementValue = 1 << (Width & 3); // 1st 2 bits currently define
                                               // width.
                                               // Other bits define type.
    UINTN  PciAddress = (((EFI_PCI_CONFIGURATION_ADDRESS*) &Address)->Bus << 20 ) +
        (((EFI_PCI_CONFIGURATION_ADDRESS*) &Address)->Device << 15 ) +
        (((EFI_PCI_CONFIGURATION_ADDRESS*) &Address)->Function << 12);
//-------------------------------------------

    PciAddress +=
        ((EFI_PCI_CONFIGURATION_ADDRESS*) &Address)->ExtendedRegister ?
            ((EFI_PCI_CONFIGURATION_ADDRESS*) &Address)->ExtendedRegister :
            ((EFI_PCI_CONFIGURATION_ADDRESS*) &Address)->Register;

    // To read 64bit values, reduce Increment Value (by half) and
    // double the count value (by twice)
    if (IncrementValue > 4) {
        IncrementValue >>= 1;
        Count <<= 1;
    }

    if (Width >= EfiPciWidthMaximum || IncrementValue > 4)
        return EFI_INVALID_PARAMETER;

    // If MultiSegment Array pointer is NULL, Get it from PCD.
    if(MultiSegPcieBaseAddressArray == NULL){
        MultiSegPcieBaseAddressArray = PcdGetPtr(AmiPcdPcieBaseAddressBuffer);
        MaxSegment = PcdGet32(AmiPcdMaxSegmentSupported);
        ASSERT(MultiSegPcieBaseAddressArray!=NULL);
        ASSERT(MaxSegment>=1);
        if (MultiSegPcieBaseAddressArray==NULL || MaxSegment<1){
            MultiSegPcieBaseAddressArray=NULL;
            return EFI_UNSUPPORTED;
        }
        // If Segment 0 base address is 0, we're dealing with a single-segment system.
        // Get PCI-E base address from PCD.
        if(MultiSegPcieBaseAddressArray[0] == 0){
            MultiSegPcieBaseAddressArray[0] = PcdGet64(PcdPciExpressBaseAddress);
        }
    }

    ASSERT(MaxSegment > ((EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL*)RbData)->SegmentNumber);
    if (MaxSegment <= ((EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL*)RbData)->SegmentNumber){
        return EFI_UNSUPPORTED;
    }
    // MultiSegment with Valid offset.Fetch value
    PciExpressBaseAddress = MultiSegPcieBaseAddressArray[((EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL*)RbData)->SegmentNumber];

    while (Count--) {
		//Check if Access address falls into PCIExpress Config Address range
        //Range check and and Number of Buses checked on PCI Bus Driver level.
        if (PciAddress & 0xF0000000) ValidCfg = FALSE;
        if (Write) {
            switch(IncrementValue) {
                case 1:
                            if (ValidCfg)
                                MmioWrite8((UINTN) (PciAddress + PciExpressBaseAddress), *(UINT8*)Buffer);
                            break;
                            
                          case 2: 
                            if (ValidCfg)
                                MmioWrite16((UINTN) (PciAddress + PciExpressBaseAddress), *(UINT16*)Buffer);
                            break;
                            
                          default:
                            if (ValidCfg)
                                MmioWrite32((UINTN) (PciAddress + PciExpressBaseAddress), *(UINT32*)Buffer);
                            break;
                 }
             } else {
                 switch(IncrementValue) {
                          case 1: 
                            *(UINT8*)Buffer = (ValidCfg) ? MmioRead8((UINTN) (PciAddress + PciExpressBaseAddress)) : -1;
                             break;
                             
                          case 2: 
                            *(UINT16*)Buffer = (ValidCfg) ? MmioRead16((UINTN) (PciAddress + PciExpressBaseAddress)) : -1;
                            break;
                             
                          default:
                            *(UINT32*)Buffer = (ValidCfg) ? MmioRead32((UINTN) (PciAddress + PciExpressBaseAddress)) : -1;
                             break;  
                 }    
              }
     
             if (Width <= EfiPciWidthFifoUint64) {
                 Buffer = ((UINT8 *)Buffer + IncrementValue);
                 // Buffer is increased for only EfiPciWidthUintxx and
            // EfiPciWidthFifoUintxx
        }

        // Only increment the PCI address if Width is not a FIFO.
        if ((Width & 4) == 0) {
            PciAddress += IncrementValue;
        }
    }

    return EFI_SUCCESS;
}

/**
    The following code defines strings and routines that can be used to display
    memory attributes (see EFI.h) or Coherencey Domain types
    (see EFI_GCD_MEMORY_TYPE enum defined in DXE.h).

        
    @param code 

         
    @retval CHAR8 string

**/

CHAR8
*GetAttributeString(
  IN    UINT64  Code
)
{
    CHAR8 Connector[] = {"|"};
    UINT8 Count = 0;
    UINT8 Csz = sizeof (Connector);

    AttributeString[Count] = '\0';

#define ADDCONNECTOR MemCpy (&AttributeString[Strlen(AttributeString)], &Connector, Csz)
#define ADDATTRIBUTE(a) MemCpy (&AttributeString[Strlen(AttributeString)], (a), sizeof (a))

    if ((UINT64)EFI_MEMORY_UC & Code)
    {
        if (Count++)
            ADDCONNECTOR;
        ADDATTRIBUTE("EFI_MEMORY_UC");
    }
    if ((UINT64)EFI_MEMORY_WC & Code)
    {
        if (Count++)
            ADDCONNECTOR;
        ADDATTRIBUTE("EFI_MEMORY_WC");
    }
    if ((UINT64)EFI_MEMORY_WT & Code)
    {
        if (Count++)
            ADDCONNECTOR;
        ADDATTRIBUTE("EFI_MEMORY_WT");
    }
    if ((UINT64)EFI_MEMORY_UCE & Code)
    {
        if (Count++)
            ADDCONNECTOR;
        ADDATTRIBUTE("EFI_MEMORY_UCE");
    }
    if ((UINT64)EFI_MEMORY_WP & Code)
    {
        if (Count++)
            ADDCONNECTOR;
        ADDATTRIBUTE("EFI_MEMORY_WP");
    }
    if ((UINT64)EFI_MEMORY_RP & Code)
    {
        if (Count++)
            ADDCONNECTOR;
        ADDATTRIBUTE("EFI_MEMORY_RP");
    }
    if ((UINT64)EFI_MEMORY_XP & Code)
    {
        if (Count++)
            ADDCONNECTOR;
        ADDATTRIBUTE("EFI_MEMORY_XP");
    }
    if ((UINT64)EFI_MEMORY_RUNTIME & Code)
    {
        if (Count++)
            ADDCONNECTOR;
        ADDATTRIBUTE("EFI_MEMORY_RUNTIME");
    }
    return AttributeString;
  }

/**
  To clear memory mapped IO information below 4GB.

  @param[in]   RootBridgeIo      A pointer to the EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.

  @retval      VOID              None.
**/

VOID
ClearMemoryMappedIoInfo_Below4Gb_Family15H (
        IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *RootBridgeIo
)
{
    UINT8               MmioReg = AMD_K8_nF1_MMIO_B0;
    UINT32              PciValue = 0;
    UINT8               Index = 0;

    // Clearing the root bridge MMIO registers

    for (Index = 0; Index < 8; Index++)
    {
        //Clear base
        RootBridgeIo->Pci.Write(RootBridgeIo, EfiPciWidthUint32, 
                NB_PCI_CFG_ADDRESS (0, (AMD_K8_NODE0_DEV), 
                AMD_K8_ADRM_FUNC, MmioReg), 1, &PciValue);
        //Clear limit
        RootBridgeIo->Pci.Write(RootBridgeIo, EfiPciWidthUint32, 
                NB_PCI_CFG_ADDRESS (0, (AMD_K8_NODE0_DEV), 
                AMD_K8_ADRM_FUNC, (MmioReg + 4)), 1, &PciValue);
        MmioReg += 8;
    }

}

/**
  To clear memory mapped IO information below 4GB.

  @param[in]   RootBridgeIo      A pointer to the EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.

  @retval      VOID              None.
**/

VOID
ClearMemoryMappedIoInfo_Below4Gb_Family17H (
  IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *RootBridgeIo
)
{
    UINT32 Reg;
    UINT32 MmioCtrl;
    UINT32 Value32;
    UINT32 Keyhole;
    UINT64 PciAddress;

    PciAddress = 0;
    //
    // Find MMIO pair that is below 4GB and then clear it.
    //
    for (Keyhole = 0x200; Keyhole <= 0x2F0; Keyhole += 0x10)
    {
        PciAddress = EFI_PCI_ADDRESS (0, 0x18, 0x04, 0x60);
        RootBridgeIo->Pci.Write (
                         RootBridgeIo,
                         EfiPciWidthUint32,
                         PciAddress,
                         1,
                         &Keyhole
                         );

        PciAddress = EFI_PCI_ADDRESS (0, 0x18, 0x04, 0xA0);
        RootBridgeIo->Pci.Read (
                         RootBridgeIo,
                         EfiPciWidthUint32,
                         PciAddress,
                         1,
                         &Value32
                         );
        if (Value32 < 0x10000)
        {
            //This MMIO pair is below 4GB

            // Clear WE/RE first
            Reg = Keyhole + 8;
            PciAddress = EFI_PCI_ADDRESS (0, 0x18, 0x04, 0x60);
            RootBridgeIo->Pci.Write (
                             RootBridgeIo,
                             EfiPciWidthUint32,
                             PciAddress,
                             1,
                             &Reg
                             );
            BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
                                                CSP_BOOT_SCRIPT_SERVICE_EX(BootScriptSave),
                                                EfiPciWidthUint32, PciAddress, 1, &Reg);

            PciAddress = EFI_PCI_ADDRESS (0, 0x18, 0x04, 0xA0);
            RootBridgeIo->Pci.Read (
                             RootBridgeIo,
                             EfiPciWidthUint32,
                             PciAddress,
                             1,
                             &MmioCtrl
                             );

            MmioCtrl &= 0xFFFFFFFC;
            RootBridgeIo->Pci.Write (
                             RootBridgeIo,
                             EfiPciWidthUint32,
                             PciAddress,
                             1,
                             &MmioCtrl
                             );
            BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
                                                CSP_BOOT_SCRIPT_SERVICE_EX(BootScriptSave),
                                                EfiPciWidthUint32, PciAddress, 1, &MmioCtrl);

            // Clear Limit
            Reg = Keyhole + 4;
            PciAddress = EFI_PCI_ADDRESS (0, 0x18, 0x04, 0x60);
            RootBridgeIo->Pci.Write (
                             RootBridgeIo,
                             EfiPciWidthUint32,
                             PciAddress,
                             1,
                             &Reg
                             );
            BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
                                                CSP_BOOT_SCRIPT_SERVICE_EX(BootScriptSave),
                                                EfiPciWidthUint32, PciAddress, 1, &Reg);

            Value32 = 0;
            PciAddress = EFI_PCI_ADDRESS (0, 0x18, 0x04, 0xA0);
            RootBridgeIo->Pci.Write (
                             RootBridgeIo,
                             EfiPciWidthUint32,
                             PciAddress,
                             1,
                             &Value32
                             );
            BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
                                                CSP_BOOT_SCRIPT_SERVICE_EX(BootScriptSave),
                                                EfiPciWidthUint32, PciAddress, 1, &Value32);

            // Clear Base
            Reg = Keyhole;
            PciAddress = EFI_PCI_ADDRESS (0, 0x18, 0x04, 0x60);
            RootBridgeIo->Pci.Write (
                             RootBridgeIo,
                             EfiPciWidthUint32,
                             PciAddress,
                             1,
                             &Reg
                             );
            BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
                                                CSP_BOOT_SCRIPT_SERVICE_EX(BootScriptSave),
                                                EfiPciWidthUint32, PciAddress, 1, &Reg);

            Value32 = 0;
            PciAddress = EFI_PCI_ADDRESS (0, 0x18, 0x04, 0xA0);
            RootBridgeIo->Pci.Write (
                             RootBridgeIo,
                             EfiPciWidthUint32,
                             PciAddress,
                             1,
                             &Value32
                             );
            BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
                                                CSP_BOOT_SCRIPT_SERVICE_EX(BootScriptSave),
                                                EfiPciWidthUint32, PciAddress, 1, &Value32);
        
        }
    }

    return;
}

/**
  To add memroy mapped IO infomation.

  @param[in]   RootBridgeIo      A pointer to the EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.
  @param[in]   BaseAddress       BaseAddress.
  @param[in]   Length            Length.
  @param[in]   NonPosted         NonPosted or Posted.

  @retval      VOID              None.
**/

VOID
AddMemoryMappedIoInfo_Family17H (
  IN EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *RootBridgeIo,
  IN UINT64                          BaseAddress,
  IN UINT64                          Length,
  IN BOOLEAN                         NonPosted
  )
{
  	UINT32        Reg;
  	UINT32        MmioCtrl;
  	UINT32        Value32;
  	UINT32        Keyhole;
  	UINT64        PciAddress;
  	EFI_STATUS    Status = EFI_SUCCESS;

  	PciAddress = 0;
  	//
  	// Find Next Empty Address to set.
  	//
  	for (Keyhole = 0x208; Keyhole <= 0x2F8; Keyhole += 0x10)
  	{
    	PciAddress = EFI_PCI_ADDRESS (0, 0x18, 0x04, 0x60);
    	RootBridgeIo->Pci.Write (
    	                     RootBridgeIo,
    	                     EfiPciWidthUint32,
    	                     PciAddress,
    	                     1,
    	                     &Keyhole
    	                     );

    	PciAddress = EFI_PCI_ADDRESS (0, 0x18, 0x04, 0xA0);
    	RootBridgeIo->Pci.Read (
        	                 RootBridgeIo,
            	             EfiPciWidthUint32,
                	         PciAddress,
                    	     1,
                        	 &MmioCtrl
                         	);
    	if ((MmioCtrl & 0x3) == 0)
		    break;
  	}
  	if (Keyhole >= 0x2F8) return;

  	Value32 = (UINT32)(BaseAddress + Length - 0x100) >> 16;
  	Reg = Keyhole - 4;
  	PciAddress = EFI_PCI_ADDRESS (0, 0x18, 0x04, 0x60);
  	RootBridgeIo->Pci.Write (
  	                     RootBridgeIo,
  	                     EfiPciWidthUint32,
  	                     PciAddress,
  	                     1,
  	                     &Reg
  	                     );

  	BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
                                        CSP_BOOT_SCRIPT_SERVICE_EX(BootScriptSave),
                                        EfiPciWidthUint32, PciAddress, 1, &Reg);
/*	S3BootScriptSavePciCfgWrite (
    S3BootScriptWidthUint32,
    PciAddress,
    1,
    &Reg
    );
*/
  	PciAddress = EFI_PCI_ADDRESS (0, 0x18, 0x04, 0xA0);
  	RootBridgeIo->Pci.Write (
    	                   RootBridgeIo,
    	                   EfiPciWidthUint32,
    	                   PciAddress,
    	                   1,
    	                   &Value32
    	                   );
  	BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
                                        CSP_BOOT_SCRIPT_SERVICE_EX(BootScriptSave),
                                        EfiPciWidthUint32, PciAddress, 1, &Value32);
 /* S3BootScriptSavePciCfgWrite (
    S3BootScriptWidthUint32,
    PciAddress,
    1,
    &Value32
    );
*/
  	Value32 = (UINT32)(BaseAddress) >> 16;
  	Reg = Keyhole - 8;
  	PciAddress = EFI_PCI_ADDRESS (0, 0x18, 0x04, 0x60);
  	RootBridgeIo->Pci.Write (
  	                     RootBridgeIo,
  	                     EfiPciWidthUint32,
  	                     PciAddress,
  	                     1,
  	                     &Reg
  	                     );
  	BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
                                        CSP_BOOT_SCRIPT_SERVICE_EX(BootScriptSave),
                                        EfiPciWidthUint32, PciAddress, 1, &Reg);
/*  S3BootScriptSavePciCfgWrite (
    S3BootScriptWidthUint32,
    PciAddress,
    1,
    &Reg
    );
*/
  	PciAddress = EFI_PCI_ADDRESS (0, 0x18, 0x04, 0xA0);
  	RootBridgeIo->Pci.Write (
  	                     RootBridgeIo,
  	                     EfiPciWidthUint32,
  	                     PciAddress,
  	                     1,
  	                     &Value32
  	                     );
  	BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
                                        CSP_BOOT_SCRIPT_SERVICE_EX(BootScriptSave),
                                        EfiPciWidthUint32, PciAddress, 1, &Value32);
/*  S3BootScriptSavePciCfgWrite (
    S3BootScriptWidthUint32,
    PciAddress,
    1,
    &Value32
    );
*/
  	if (NonPosted) {
  	  MmioCtrl |= 0x1000;
  	}
  	MmioCtrl |= 0x3;
  	PciAddress = EFI_PCI_ADDRESS (0, 0x18, 0x04, 0x60);
  	RootBridgeIo->Pci.Write (
  	                     RootBridgeIo,
  	                     EfiPciWidthUint32,
  	                     PciAddress,
  	                     1,
  	                     &Keyhole
  	                     );
  	BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
                                        CSP_BOOT_SCRIPT_SERVICE_EX(BootScriptSave),
                                        EfiPciWidthUint32, PciAddress, 1, &Keyhole);
/*  S3BootScriptSavePciCfgWrite (
    S3BootScriptWidthUint32,
    PciAddress,
    1,
    &Keyhole
    );
*/
  	PciAddress = EFI_PCI_ADDRESS (0, 0x18, 0x04, 0xA0);
  	RootBridgeIo->Pci.Write (
  	                     RootBridgeIo,
  	                     EfiPciWidthUint32,
  	                     PciAddress,
  	                     1,
  	                     &MmioCtrl
  	                     );
  	BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
                                        CSP_BOOT_SCRIPT_SERVICE_EX(BootScriptSave),
                                        EfiPciWidthUint32, PciAddress, 1, &MmioCtrl);
/*  S3BootScriptSavePciCfgWrite (
    S3BootScriptWidthUint32,
    PciAddress,
    1,
    &MmioCtrl
    );
*/
  	return;
}

/**
    This function will try to Allocate from GCD set of resources requested by 
    PCI BUS driver in "*Resources" buffer.

        
    @param RootBrg Pointer to ROOT Bridge private data

        EFI_STATUS
    @retval EFI_SUCCESS Success
    @retval EFI_OUT_OF_RESOURCES If could not allocate resources
    @retval EFI_DEVICE_ERROR failed due to HW error.
**/

EFI_STATUS EFIAPI
AllocateRbResources (IN PCI_ROOT_BRG_DATA   *RootBrg)
{
    EFI_STATUS          Status;
    EFI_STATUS          ReturnStatus = 0;
    UINTN               i;
    ASLR_QWORD_ASD      *res;
    ACPI_RES_DATA       *ar;
    UINT64              a = 0;
    DXE_SERVICES        *dxe;   
// OUT_OF_RES HANDLING++ must be added in Custom Res allocate function.
#if BoardPciRes_SUPPORT
    AMI_OUT_OF_RES_VAR  OutOfResVar;
//--------------------------------------
    // Check if OUT_OF_RES_VAR was already created.
    Status = AmiPciOutOfRes (&OutOfResVar, TRUE);
    if (EFI_ERROR (Status))
        pBS->SetMem (&OutOfResVar, sizeof (AMI_OUT_OF_RES_VAR), 0);
    else
        OutOfResVar.Count++;
#endif
// OUT_OF_RES HANDLING-- must be added in Custom Res allocate function.

    Status = LibGetDxeSvcTbl(&dxe);
    if (EFI_ERROR (Status))
        return Status;
 
    for (i = 0; i < RootBrg->ResCount; i++)
    {
        res = RootBrg->RbRes[i];
        if(res->Type == ASLRV_SPC_TYPE_BUS)
            continue;
        // Check if Alignment
        if (!IsPowerOfTwo (res->_MAX + 1))
            return EFI_INVALID_PARAMETER;
        switch (res->_GRA)
        {
            case 16 :   a = 0xFFFF;//-res->_LEN;
                break;
            case 32 :   a = 0xFFFFFFFF;//-res->_LEN;
                break;
            case 64 :   a = 0xFFFFFFFFFFFFFFFF;//-res->_LEN+1;
                break;
            default :ASSERT(0); return EFI_INVALID_PARAMETER;
        }
        
        DEBUG((DEBUG_VERBOSE,"PciRB: AllocateResources In -> _MIN=0x%lX; _MAX=0x%lX; _LEN=0x%lX; _GRA=0x%lX\n",
        res->_MIN,res->_MAX,res->_LEN,res->_GRA));

        // Allocate IO
        if(res->Type == ASLRV_SPC_TYPE_IO)
        {
            ar = &RootBrg->AcpiRbRes[raIo];
            ar->AddrUsed = a;
            ar->AllocType = EfiGcdAllocateMaxAddressSearchTopDown;
#if PCI_BUS_REVISION >= 16
            Status = dxe->AllocateIoSpace (EfiGcdAllocateMaxAddressSearchTopDown,
                              EfiGcdIoTypeIo,
                              AlignFromGranularity((UINTN)res->_MAX),
                              res->_LEN,
                              &a,
                              RootBrg->ImageHandle, RootBrg->RbHandle);
#else
            Status = dxe->AllocateIoSpace (EfiGcdAllocateMaxAddressSearchTopDown,
                              EfiGcdIoTypeIo,
                              AlignFromGra((UINTN)res->_MAX),
                              res->_LEN,
                              &a,
                              RootBrg->ImageHandle, RootBrg->RbHandle);
#endif
            if(EFI_ERROR(Status))
            {
                ReturnStatus = Status;
                DEBUG((DEBUG_VERBOSE,"PciRB: IO Allocation Failed: Length: %lX\n",res->_LEN));
// ++OUT_OF_RES!! IO                
#if BoardPciRes_SUPPORT
                OutOfResVar.Resource = *res;
                Status = AmiPciOutOfRes (&OutOfResVar, FALSE);                
                return ReturnStatus;
// --OUT_OF_RES!! IO                
#else
                continue;
#endif
            }
        }
        // Allocate MMIO
        else if (res->Type == ASLRV_SPC_TYPE_MEM)
        {
            if (res->_GRA == 32)
                ar = &RootBrg->AcpiRbRes[raMmio32];
            else
                ar = &RootBrg->AcpiRbRes[raMmio64];
            ar->AddrUsed = a;
            ar->AllocType = EfiGcdAllocateMaxAddressSearchTopDown;
//(EIP45278)>
#if PCI_MMIO_RES_TOP_ALLIGN == 1
            Status = AllocateMemoryResource (
#if PCI_BUS_REVISION >= 16
            		AlignFromGranularity((UINTN)res->_MAX),
                     res->_LEN,
                     &a,
                     RootBrg->ImageHandle,
                     RootBrg->RbHandle);
#else
            		AlignFromGra((UINTN)res->_MAX),
                     res->_LEN,
                     &a,
                     RootBrg->ImageHandle,
                     RootBrg->RbHandle);
#endif
#else
#if PCI_BUS_REVISION >= 16
            Status = dxe->AllocateMemorySpace (EfiGcdAllocateMaxAddressSearchTopDown,
                              EfiGcdMemoryTypeMemoryMappedIo,
                              AlignFromGranularity((UINTN)res->_MAX),
                              res->_LEN,
                              &a,
                              RootBrg->ImageHandle, RootBrg->RbHandle);
#else
            Status = dxe->AllocateMemorySpace (EfiGcdAllocateMaxAddressSearchTopDown,
                              EfiGcdMemoryTypeMemoryMappedIo,
                              AlignFromGra((UINTN)res->_MAX),
                              res->_LEN,
                              &a,
                              RootBrg->ImageHandle, RootBrg->RbHandle);
#endif
#endif
//<(EIP45278)

            if (EFI_ERROR (Status))
            {
                ReturnStatus = Status;
                DEBUG((DEBUG_VERBOSE,"PciRB: Memory Allocation Failed: Length: %lX\n",res->_LEN));
// ++OUT_OF_RES!! MEM                
#if BoardPciRes_SUPPORT
                OutOfResVar.Resource = *res;
                Status = AmiPciOutOfRes (&OutOfResVar, FALSE);                
                return ReturnStatus;
#else
// --OUT_OF_RES!! MEM                
                continue;
#endif
            }

            // Set this region as WT cache if it is PREFETCHABLE 
            if (res->TFlags.MEM_FLAGS._MEM != ASLRV_MEM_UC) 
            {
//                Status = gDxeSvcTbl->SetMemorySpaceAttributes (a, res->_LEN, EFI_MEMORY_WT | EFI_MEMORY_RUNTIME);
                Status = dxe->SetMemorySpaceAttributes (a, res->_LEN, EFI_MEMORY_WT);
                // If attempt to set WT attributes has filed, let's try UC
                if (EFI_ERROR (Status))
                {
                	DEBUG((DEBUG_VERBOSE, "PciRB: Setting of WT attributes for prefetchable memory has failed(%r). UC is used.\n",Status));
//                    Status = gDxeSvcTbl->SetMemorySpaceAttributes (a, res->_LEN, EFI_MEMORY_UC | EFI_MEMORY_RUNTIME);
                    Status = dxe->SetMemorySpaceAttributes (a, res->_LEN, EFI_MEMORY_UC);
                }
            }
            else
                Status = dxe->SetMemorySpaceAttributes (a, res->_LEN, EFI_MEMORY_UC);
//                Status = gDxeSvcTbl->SetMemorySpaceAttributes (a, res->_LEN, EFI_MEMORY_UC | EFI_MEMORY_RUNTIME);
            ASSERT_EFI_ERROR (Status);
            if (EFI_ERROR(Status))
                return Status;
        }
        res->_MIN = a;

        DEBUG((DEBUG_VERBOSE,"PciRB: AllocateResources Out-> _MIN=0x%lX; _MAX=0x%lX; _LEN=0x%lX; _GRA=0x%lX\n",
               res->_MIN,res->_MAX,res->_LEN,res->_GRA));

        // Do some calculation for ACPI _CRS update.        
        if (ar->Min == 0)
            ar->Min = res->_MIN;
        else
            if(ar->Min > res->_MIN)
			    ar->Min = res->_MIN;

//(EIP45278+)>
#if PCI_MMIO_RES_TOP_ALLIGN == 1
        ar->Gra = 0;
#else
        if (ar->Gra == 0)
            ar->Gra = res->_MAX;
        else
            if (ar->Gra < res->_MAX)
			    ar->Gra = res->_MAX;
#endif
//<(EIP45278+)
        if (ar->Len == 0)
        {
            ar->Len = res->_LEN;
            if (ar->Len & ar->Gra)
			    ar->Len = (ar->Len | ar->Gra) + 1;
            ar->Max = ar->Min + ar->Len - 1; 
        }
        else
        {
            UINT64  max;
        //--------
            max = res->_MIN + res->_LEN - 1;
            if (max > ar->Max)
			    ar->Max = max; 
            ar->Len = ar->Max - ar->Min + 1;
            if (ar->Len & ar->Gra)
			    ar->Len = (ar->Len | ar->Gra) + 1;
            ar->Max = ar->Min + ar->Len - 1; 
        }
        DEBUG((DEBUG_VERBOSE,"PciRB: AcpiResources Min=0x%lX; Max=0x%lX; Len=0x%lX; Gra=0x%lX, AdrUsed=0x%lX\n\n",
               ar->Min,ar->Max,ar->Len,ar->Gra, ar->AddrUsed));

        // Don't need to set this to actual value it could be calculated using commented formula.
        // More important to preserve alignment requirements of the resource window.
//        res->_MAX = res->_MIN + res->_LEN - 1;
    }
    return ReturnStatus;
}

//###<AAV> Core5.005 compliance ### #if (PCI_BUS_MAJOR_VER >= 2) && (PCI_BUS_MINOR_VER >=2)
// The following Structures and functions are used for
//  AMD Northbridge Multi-Rootbridge Legacy PCI Express VGA Support
// Structures declaration starts
typedef struct _CONFIGURATION_MAP_REGISTER
{
    union {
        struct {
            UINT32  ReadEnable  :1;  // [0] RE: read enable
            UINT32  WriteEnable :1;  // [1] WE: write enable
            UINT32  DevCmpEn    :1;  // [2] device number compare mode enable
            UINT32  Reserved1   :1;  // [3] Reserved
            UINT32  DstNode     :3;  // [6:4] Destination node ID bits
            UINT32  Reserved2   :1;  // [7] Reserved
            UINT32  DstLink     :2;  // [9:8] Destination link ID
            UINT32  DstSubLink  :1;  // [10] Destination sublink
            UINT32  Reserved3   :5;  // [15:11] Reserved
            UINT32  BusNumBase  :8;  // [23:16] Bus number base bits
            UINT32  BusNumLimit :8;  // [31:24] bus number limit bits
        } Field;
        UINT32  AllBits;
    };
} CONFIGURATION_MAP_REGISTER;

typedef struct _DEVICE_VENDOR_ID_REGISTER
{
    union {
        struct {
            UINT32  VendorId    :16;    // [15:0] Vendor ID
            UINT32  DeviceId    :16;    // [31:16] Device ID
        } Field;
        UINT32  AllBits;
    };
} DEVICE_VENDOR_ID_REGISTER;

typedef struct _VGA_ENABLE_REGISTER_15h
{
    union {
        struct {
            UINT32  VgaEnable   :1;  // [0] VE: VGA enable
            UINT32  NonPosted   :1;  // [1] NP: non-posted
            UINT32  CpuDis      :1;  // [2] CpuDis: CPU Disable
            UINT32  Lock        :1;  // [3] Lock
            UINT32  DstNode     :3;  // [6:4] DstNode[2:0]: destination node ID
            UINT32  Reserved2   :5;  // [11:7] Reserved
            UINT32  DstLink     :2;  // [13:12] Destination link ID
            UINT32  DstSubLink  :1;  // [14] Destination sublink
            UINT32  Reserved3   :17; // [31:15] Reserved
        } Field;
        UINT32  AllBits;
    };
} VGA_ENABLE_REGISTER_15h;

// Structures declaration ends

/**
    Pci Config Read         

        
    @param Root Bridge private structure
    @param Address 

         
    @retval UINT32 Contains data read from PCI register    
**/

// Functions support AMD Northbridge Multi-Rootbridge Legacy PCI Express VGA
UINT32
PciConfigRead(
  IN    PCI_ROOT_BRG_DATA   *RbData,
  IN    PCI64_ADDRESS       Address
)
{
    UINT32  PciValue;

    RbData->RbIoProtocol.Pci.Read(&RbData->RbIoProtocol,
                              EfiPciWidthUint32, Address.AllBits, 1, &PciValue);
            
    return PciValue;    // Return the read value
}

/**
    Pci Config Write

        
    @param Root Bridge private structure
    @param Address 
    @param PciValue 

         
    @retval VOID
**/

VOID
PciConfigWrite(
  IN    PCI_ROOT_BRG_DATA   *RbData,
  IN    PCI64_ADDRESS       Address,
  IN    UINT32              PciValue
)
{
    RbData->RbIoProtocol.Pci.Write(&RbData->RbIoProtocol,
                              EfiPciWidthUint32, Address.AllBits, 1, &PciValue);

    return; // Return the read value
}

/**
    Legacy VGA Routing for family15h

        
    @param RbData 
    @param RbNode 

         
    @retval EFI_STATUS return EFI status
**/

EFI_STATUS
LegacyVgaRouting15h (
  IN    PCI_ROOT_BRG_DATA   *RbData,
  IN    UINT8               RbNode
)
{
    PCI64_ADDRESS                   PciAddress;

    VGA_ENABLE_REGISTER_15h         VgaEnableReg;
//Enable VGA For Slots behind Device 24
    PciAddress.AllBits = 0;
    PciAddress.Field.Bus = 0;
    PciAddress.Field.Device = 0x18;
    PciAddress.Field.Function = 1;
    PciAddress.Field.Register = 0xF4;
    VgaEnableReg.AllBits = PciConfigRead(RbData, PciAddress);
    VgaEnableReg.Field.DstNode = 0;
    VgaEnableReg.Field.DstLink = 0;
    VgaEnableReg.Field.VgaEnable = TRUE;
    PciConfigWrite(RbData, PciAddress, VgaEnableReg.AllBits);
    return EFI_SUCCESS;

}

/**
    Legacy VGA Routing for family 17h

        
    @param RbData 
    @param RbNode 

         
    @retval EFI_STATUS return EFI status
**/

EFI_STATUS
LegacyVgaRouting17h (
  IN    PCI_ROOT_BRG_DATA   *RbData,
  IN    UINT8               RbNode
)
{
    PCI64_ADDRESS           PciAddress;
    VGA_ENABLE_REGISTER_17h VgaEnableReg;
    UINT32                  DstFabricId;

    if (BootScriptSave == NULL)
    {
        pBS->LocateProtocol(&gEfiS3SaveStateProtocolGuid, NULL, &BootScriptSave);
    }

    PciAddress.AllBits = 0;
    PciAddress.Field.Bus = 0;
    PciAddress.Field.Device = 0x18;
    PciAddress.Field.Function = 0;
    PciAddress.Field.Register = 0xC4;
    DstFabricId = PciConfigRead(RbData, PciAddress);
    DstFabricId &= 0xFF;

    PciAddress.AllBits = 0;
    PciAddress.Field.Bus = 0;
    PciAddress.Field.Device = 0x18;
    PciAddress.Field.Function = 0;
    PciAddress.Field.Register = 0x80;
    VgaEnableReg.AllBits = PciConfigRead(RbData, PciAddress);
    VgaEnableReg.Field.DstFabricID = DstFabricId;
    VgaEnableReg.Field.VgaEnable = TRUE;
    PciConfigWrite(RbData, PciAddress, VgaEnableReg.AllBits);
    BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
                                        CSP_BOOT_SCRIPT_SERVICE_EX(BootScriptSave),
                                        EfiPciWidthUint32, EFI_PCI_ADDRESS(0, AMD_K8_NODE0_DEV, AMD_K8_LDT_FUNC, 0x80), 1, &VgaEnableReg.AllBits);
    DEBUG((DEBUG_VERBOSE, "VGA Fabric Id = %X\n", DstFabricId));
    return EFI_SUCCESS;

}
//###<AAV> Core5.005 compliance ### #endif

/****** DO NOT WRITE BELOW THIS LINE *******/
#endif  //#if AMI_ROOT_BRIDGE_SUPPORT == 1

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
