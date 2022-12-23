//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


/** @file SbDxe.c
    This file contains code for Template South bridge initialization
    in the DXE stage

*/

#include <PiDxe.h>
#include <Library/PcdLib.h>
#include <Library/DevicePathLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Guid/GlobalVariable.h>

// Module specific Includes
#include <Token.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <AmiDxeLib.h>
#include <Setup.h>
#include <AmiHobs.h>
#include <Sb.h>
#include <AmiChipsetIoLib.h>
#include <AmiCspLib.h>
#include <Library/SbPolicy.h>
#include <Library/UefiLib.h>
#include <Library/AmiTimerIntLib.h>
// Consumed Protocols
#include <Protocol/SbSataProtocol.h>
#include <Protocol/PciIo.h>
#include <Protocol/Cpu.h>
#include <Protocol/PciRootBridgeIo.h>
#include <Protocol/S3SaveState.h>
#include <Protocol/AmiBoardInfo2.h>
#include <Protocol/FchInitProtocol.h>
#include <Protocol/SocLogicalIdProtocol.h>

#if ACPI_SUPPORT

// The initial protocol defined in the UEFI2.1 spec.
#include <Protocol/AcpiTable.h>

#endif


// Produced Protocols
#include <Protocol/RealTimeClock.h>
#include <Protocol/WatchdogTimer.h>
#include <Protocol/Timer.h>
#include <Protocol/Legacy8259.h>

#if defined AMIUSB_SUPPORT && AMIUSB_SUPPORT == 1
#include <Protocol/AmiUsbController.h>              // (EIP53061+)
#include <Protocol/UsbPolicy.h>
#endif

#if defined(CSM_SUPPORT) && (CSM_SUPPORT == 1)
#include <Protocol/LegacyBiosExt.h>
#endif

#include <Protocol/Timer.h>
#include <AGESA.h>
#include <FchCommonCfg.h>//GDBG+
// Build flag adjustments
#ifndef   SMM_SUPPORT
#define   SMM_SUPPORT     0
#endif

// Constant definitions
#define PCI_CFG_ADDR(bus,dev,func,reg) \
                        ((VOID*)(UINTN) (PcdGet64 (PcdPciExpressBaseAddress) + \
                        ((bus) << 20) + ((dev) << 15) + \
                        ((func) << 12) + reg))

#define NBIO_FIXED_ONCHIP_BUS_A_BRIDGE(reg) SB_PCI_CFG_ADDRESS(0, 8, 1, reg)
#define FIXED_MP2_BUS_SANDSTONE NBIO_FIXED_ONCHIP_BUS_A
//----------------------------------------------------------------------------
//      Timer Constants
//----------------------------------------------------------------------------
#define SYSTEM_TIMER_IRQ 0
// Now using Legacy 8259 protocol to initialize. Remove this line later.
//#define SYSTEM_TIMER_INTR_VECTOR (MASTER_INTERRUPT_BASE + SYSTEM_TIMER_IRQ)

// Timer Period
#define TIMER_TICK        838 //ns

// default duration is 0xffff ticks
#define MAX_TICK_DURATION ((65535 * 838 + 50) / 100)

//8259 PIC defines
#define ICW1            0x11    //Slave exists and ICW4 required.
#define ICW3_M          1<<2    //IRQ 2 connects to slave
#define ICW3_S          2       //IRQ 2 connects to master
#define ICW4            1       //Bit 4 Normal Nested Mode
                                //Bit 3 Non-buffered Mode
                                //Bit 2 Unused with non-buffered mode
                                //Bit 1 Set manual EOI instead of automatic
                                //Bit 0 8086/8088 mode

#define OCW1_M          0xff    //Master Mask
#define OCW1_S          0xff    //Slave Mask

#define EOI_COMMAND     0x20    //EOI Command

#define INTERRUPTS_TRIGGER_REG    0x4d0   //Trigger for Interrupts (Edge or Level).
#define INTERRUPTS_EDGE_TRIGGER   0       //Set all interrupts at edge level.
BOOLEAN
FchRVXhciSmuUsbConfigUpdate (
  IN  UINT32    smn_register,
  IN  UINT32    smn_mask,
  IN  UINT32    smn_data,
  IN  UINT32    smn_group
  );
BOOLEAN FchRVXhciSmuService (IN UINT32 RequestId);
#define SMC_MSG_UsbInit 0x2E
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//          Variable Declaration
//----------------------------------------------------------------------------
#if defined SB_TIMER_ARCH_PROTOCOL_SUPPORT && SB_TIMER_ARCH_PROTOCOL_SUPPORT == 1
EFI_HANDLE  mTimerProtocolHandle        = NULL;
EFI_EVENT   gEvtTimerArch               = NULL;
VOID        *gRegTimerArch              = NULL;
UINT64      mProgrammedTimerValue;
EFI_TIMER_NOTIFY            mNotifyFunction;
EFI_LEGACY_8259_PROTOCOL    *mLegacy8259;
#endif
#if defined SB_WATCHDOG_TIMER_PROTOCOL_SUPPORT && SB_WATCHDOG_TIMER_PROTOCOL_SUPPORT == 1
EFI_EVENT   mWatchdogEvent;
UINT64      mWatchdogPeriod             = 0;
EFI_WATCHDOG_TIMER_NOTIFY   mWatchdogNotifyFunction = NULL;
#endif
EFI_EVENT   SBLegacyBootEvent;

// GUID Definitions
EFI_S3_SAVE_STATE_PROTOCOL      static  *gBootScriptSave = NULL;
//This the number of days in a month - 1. (0 Based)
//### Sync template but move to Sb8259InitLib ###
#define SB_8259_PROTOCOL_LIB_SUPPORT 	1
#if defined SB_8259_PROTOCOL_SUPPORT && SB_8259_PROTOCOL_SUPPORT == 1 && (SB_8259_PROTOCOL_LIB_SUPPORT == 0)
UINT8       gMasterBase, 
            gSlaveBase;
UINT8       gMode                       = 1;                    //Initially in protected mode. (0 = Real, 1 = 32 bit protected)
UINT16      gIrqMask[2]                 = {0xffff,0xffff};      //Initially all Real IRQs masked, protected masked
UINT16      gIrqTrigger[2]              = {0,0};                //Initially all Real IRQs Edge, protected Edge.
#endif
EFI_EVENT       gEvtReadyToBoot;
EFI_EVENT       mEvent;
VOID            *mReg;

SB_SETUP_DATA           *gSbSetupData=NULL ;
#if defined AMIUSB_SUPPORT && AMIUSB_SUPPORT == 1
#if defined CONTROL_ALL_USB_METHOD && CONTROL_ALL_USB_METHOD == 1
BOOLEAN         gDisableAllUsbControllers = FALSE;
#endif
EFI_EVENT       gEvtUsbProtocol  = NULL;
VOID            *gRegUsbProtocol = NULL;

EFI_EVENT       gEvtUsbPolicyProtocol  = NULL;
VOID            *gRegUsbPolicyProtocol = NULL;

EFI_EVENT       gRegisterRestoreEvent = NULL;

typedef struct {
	CHAR16*		FchTypeStr;
	CHAR16*		DevicePathText;
} FCH_USB3_DEVICES;

FCH_USB3_DEVICES CONST gFchUsbDevs[] = {
		{L"Sandstone", 		L"PciRoot(0x0)/Pci(0x8,0x1)/Pci(0x0,0x3)"}, // Raven-Sandstone USB31-1
		{L"Sandstone", 		L"PciRoot(0x0)/Pci(0x8,0x1)/Pci(0x0,0x4)"}, // Raven-Sandstone USB31-2
		{L"Taishan", 		L"PciRoot(0x0)/Pci(0x7,0x1)/Pci(0x0,0x3)"},
		{L"Kern", 			L"PciRoot(0x0)/Pci(0x10,0x0)"},
};

#endif

VOID                                	*gCpuArchNotifyReg;
extern EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL	*gPciRootBridgeIo;

extern VOID SaveRestoreRegisters(BOOLEAN Save);

typedef struct {
	union {
		UINT64                  Address;
		struct {
			UINT64 CONST 	Reg : 8;
			UINT64 CONST 	Fun : 8;
			UINT64 CONST	Dev : 8;
			UINT64 			Bus : 8;
			UINT64 CONST 	Reserved : 32;
		} Addr;
	};
    EFI_BOOT_SCRIPT_WIDTH   Width;
} BOOT_SCRIPT_PCI_REGISTER_SAVE;


EFI_STATUS
GeneratePortNumber(	 
    IN    UINT8    DeviceNumber,
    IN    UINT8    FunctionNumber,
    IN    UINT32   IdeChannel,
    IN    UINT32   IdeDevice,
    OUT   UINT32   *PortNumber
);

//----------------------------------------------------------------------------

UINT8 PATA_PORT_NUM[2][2] = {
    // SATA port4,5 DID=IDE DID
    {4, 5},
    {5, 4}
};

UINT8 SATA_PORT_NUM[3][2] = {
    {0, 2},
    {1, 3},
    {4, 5}
};

BOOT_SCRIPT_PCI_REGISTER_SAVE gFchPciRegScriptTbl[] = {
    //LPC decoding related registers
    SB_REG(0x74),  EfiBootScriptWidthUint32,
    SB_REG(0x64),  EfiBootScriptWidthUint32,
    SB_REG(0x6c),  EfiBootScriptWidthUint32,
    SB_REG(0x90),  EfiBootScriptWidthUint16,
    SB_REG(0x44),  EfiBootScriptWidthUint32,
    SB_REG(0x48),  EfiBootScriptWidthUint32,
};
UINTN gFchPciRegScriptSize = \
        sizeof(gFchPciRegScriptTbl) / sizeof(BOOT_SCRIPT_PCI_REGISTER_SAVE);
 
//----------------------------------------------------------------------------
// Fch Sandstone resource table 
//----------------------------------------------------------------------------
CSP_RES_ITEM CONST gFchSandstoneResTable[] = {
//==============================================================================//
//{UINT64 ResBase, UINTN ResLength, GCD_MEMORY_TYPE ResType, UINT64 Attributes}	//
//==============================================================================//
{ 0xFEDC2000, 0x5000, EfiGcdMemoryTypeMemoryMappedIo,(EFI_MEMORY_UC| EFI_MEMORY_RUNTIME)}, //FCH I2C0-4 Configuration Space
{ 0xFEDC7000, 0x1000, EfiGcdMemoryTypeMemoryMappedIo,(EFI_MEMORY_UC| EFI_MEMORY_RUNTIME)}, //FCH DMA0 Configuration Space
{ 0xFEDC8000, 0x1000, EfiGcdMemoryTypeMemoryMappedIo,(EFI_MEMORY_UC| EFI_MEMORY_RUNTIME)}, //FCH DMA1 Configuration Space
{ 0xFEDC9000, 0x1000, EfiGcdMemoryTypeMemoryMappedIo,(EFI_MEMORY_UC| EFI_MEMORY_RUNTIME)}, //FCH UART3 Configuration Space
{ 0xFEDCA000, 0x1000, EfiGcdMemoryTypeMemoryMappedIo,(EFI_MEMORY_UC| EFI_MEMORY_RUNTIME)}, //FCH UART2 Configuration Space
{ 0xFEDCB000, 0x1000, EfiGcdMemoryTypeMemoryMappedIo,(EFI_MEMORY_UC| EFI_MEMORY_RUNTIME)}, //FCH I2C5 Configuration Space
{ 0xFEDCC000, 0x1000, EfiGcdMemoryTypeMemoryMappedIo,(EFI_MEMORY_UC| EFI_MEMORY_RUNTIME)}, //FCH DMA2 Configuration Space
{ 0xFEDCE000, 0x1000, EfiGcdMemoryTypeMemoryMappedIo,(EFI_MEMORY_UC| EFI_MEMORY_RUNTIME)}, //FCH UART1 Configuration Space
{ 0xFEDCD000, 0x1000, EfiGcdMemoryTypeMemoryMappedIo,(EFI_MEMORY_UC| EFI_MEMORY_RUNTIME)}, //FCH DMA3 Configuration Space
{ 0xFEDCF000, 0x1000, EfiGcdMemoryTypeMemoryMappedIo,(EFI_MEMORY_UC| EFI_MEMORY_RUNTIME)}, //FCH UART0 Configuration Space
{ 0xFEDD4000, 0x1000, EfiGcdMemoryTypeMemoryMappedIo,(EFI_MEMORY_UC| EFI_MEMORY_RUNTIME)}, //FCH ESPI Configuration Space
{ 0xFEDD5000, 0x1000, EfiGcdMemoryTypeMemoryMappedIo,(EFI_MEMORY_UC| EFI_MEMORY_RUNTIME)}, //FCH EMMC Configuration Space
//===========================================================================
};

struct {
    CHAR16*	        CONST FchTypeStr;
    CSP_RES_ITEM    CONST *FchResTable;
    UINTN			CONST TableCount;
} CONST STATIC FchResTblSize, gFchResTbl[] = {
	// Porting required : append other FCH below.
    { L"Sandstone",   gFchSandstoneResTable, sizeof(gFchSandstoneResTable)/sizeof(CSP_RES_ITEM) }
    // { L"Taishan",   gFchTaishanResTable, sizeof(gFchTaishanResTable)/sizeof(CSP_RES_ITEM) }
    // ...
};
UINTN CONST gFchResTblCount = sizeof(gFchResTbl)/sizeof(FchResTblSize);

BOOLEAN                     mIsProcessorTypeFlavor1 = TRUE;


//--------------------------------------------------------------
// Function Prototypes
//--------------------------------------------------------------
EFI_STATUS
SbDxeBoardInit (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  );

VOID SBAfterPciInit(
  IN EFI_EVENT Event,
  IN VOID *Context
  );

VOID SBReadyToBoot(
  IN EFI_EVENT Event,
  IN VOID *Context
  );

VOID USBPrePortDisableCallback(
  IN EFI_EVENT Event,
  IN VOID *Context
  );

VOID EFIAPI EnableDisableSBDevices ();

VOID EFIAPI SBAfterPCIInit(
  IN EFI_EVENT    Event,
  IN VOID       *Context
  );

VOID
UpdateSbIoApicIdToRouteTable (
  IN UINT8   ApicId,
  IN UINT32  ApicAddress
  );

EFI_STATUS CountTime(
    IN  UINTN   DelayTime, 
    IN  UINT16  BaseAddr
);

#if defined SB_WATCHDOG_TIMER_PROTOCOL_SUPPORT && SB_WATCHDOG_TIMER_PROTOCOL_SUPPORT == 1
EFI_STATUS WatchdogInit (
    IN EFI_HANDLE                 ImageHandle,
    IN EFI_SYSTEM_TABLE           *SystemTable
);

VOID EFIAPI WatchdogHandler (
    IN EFI_EVENT                  Event,
    IN VOID                       *Context
);

EFI_STATUS EFIAPI RegisterHandler(
    IN EFI_WATCHDOG_TIMER_ARCH_PROTOCOL  *This,
    IN EFI_WATCHDOG_TIMER_NOTIFY         NotifyFunction
);

EFI_STATUS EFIAPI WatchdogSetTimerPeriod(
    IN EFI_WATCHDOG_TIMER_ARCH_PROTOCOL  *This,
    IN UINT64                            TimerPeriod
);

EFI_STATUS EFIAPI WatchdogGetTimerPeriod(
    IN EFI_WATCHDOG_TIMER_ARCH_PROTOCOL  *This,
    IN UINT64                            *TimerPeriod
);
#endif

#if defined SB_8259_PROTOCOL_SUPPORT && SB_8259_PROTOCOL_SUPPORT == 1 && (SB_8259_PROTOCOL_LIB_SUPPORT == 0)
EFI_STATUS Initialize8259 (
    IN EFI_HANDLE                 ImageHandle,
    IN EFI_SYSTEM_TABLE           *SystemTable
);
#endif

#if defined SMM_SUPPORT && SMM_SUPPORT == 1
EFI_STATUS SbSmmInit(
    IN EFI_HANDLE                 ImageHandle,
    IN EFI_SYSTEM_TABLE           *SystemTable
);
#endif

EFI_STATUS TimerInit(
    VOID
);

#if defined SB_TIMER_ARCH_PROTOCOL_SUPPORT && SB_TIMER_ARCH_PROTOCOL_SUPPORT == 1
VOID TimerInitWrapper(
    IN EFI_EVENT                Event,
    IN VOID                     *Context
);

EFI_STATUS TimerRegisterHandler(
    EFI_TIMER_ARCH_PROTOCOL     *This, 
    EFI_TIMER_NOTIFY            NotifyFunction
);

EFI_STATUS SetTimerPeriod(
    EFI_TIMER_ARCH_PROTOCOL     *This, 
    UINT64                      TimerPeriod
);

EFI_STATUS GetTimerPeriod(
    EFI_TIMER_ARCH_PROTOCOL     *This, 
    UINT64                      *TimerPeriod
);

EFI_STATUS GenerateSoftIntr(
    EFI_TIMER_ARCH_PROTOCOL     *This
);
#endif
// AVA9 :
// This is part of SbInterfaceDxe.c
// 		Due to architecture change for AGESA V9. There is no ELINK for SbInterfaceDxe
//		Do it here for the moment.
VOID ProgramSBSubId(VOID);

#if defined SB_WATCHDOG_TIMER_PROTOCOL_SUPPORT && SB_WATCHDOG_TIMER_PROTOCOL_SUPPORT == 1
// Architectural Protocol Definitions
EFI_WATCHDOG_TIMER_ARCH_PROTOCOL mWatchdog = {
  RegisterHandler,
  WatchdogSetTimerPeriod,
  WatchdogGetTimerPeriod
};
#endif

#if defined SB_TIMER_ARCH_PROTOCOL_SUPPORT && SB_TIMER_ARCH_PROTOCOL_SUPPORT == 1
EFI_TIMER_ARCH_PROTOCOL mTimerProtocol = {
  TimerRegisterHandler,
  SetTimerPeriod,
  GetTimerPeriod,
  GenerateSoftIntr
};
#endif

SB_HDD_POLICY_PROTOCOL mSbHddPolicy = {
    GeneratePortNumber
};

EFI_STATUS
InstallSbPolicyProtocol (VOID);

#if defined AMIUSB_SUPPORT && AMIUSB_SUPPORT == 1
VOID SbUsbProtocolCallback (
    IN EFI_EVENT        Event,
    IN VOID             *Context
);

VOID RV2SbUsbProtocolCallback (
    IN EFI_EVENT        Event,
    IN VOID             *Context
);
#endif

#if defined SB_TIMER_ARCH_PROTOCOL_SUPPORT && SB_TIMER_ARCH_PROTOCOL_SUPPORT == 1
VOID
EFIAPI
RegisterRestoreCallBack (
    IN  EFI_EVENT  Event,
    IN  VOID       *Context
);
#endif

VOID
EnableDisableUsbPort (VOID);

VOID
RV2EnableDisableUsbPort (VOID);

// Function Definitions

/**
    Check Processor Type is Type2 - Flavor1 or not

    @param VOID 

    @retval    TRUE    Processor Type is Type2 - Flavor1(PCO)
               FALSE   Processor Type is Type2 - Flavor2(RV2)
**/
BOOLEAN
IsProcessorTypeFlavor1 (
  )
{
    AMD_SOC_LOGICAL_ID_PROTOCOL *SocLogicalId;
    SOC_LOGICAL_ID              LogicalId;
    EFI_STATUS                  Status;
    
    Status = gBS->LocateProtocol(&gAmdSocLogicalIdProtocolGuid, NULL, (VOID **) &SocLogicalId);
    if (!EFI_ERROR(Status)) {
        SocLogicalId->GetLogicalIdOnCurrentCore(SocLogicalId, &LogicalId);
        
        DEBUG((EFI_D_INFO, "LogicalId = 0x%X\n", LogicalId.Family));
        if (LogicalId.Family & AMD_FAMILY_RV) return TRUE;
    }
    
    return FALSE;
}

#if defined AMIUSB_SUPPORT && AMIUSB_SUPPORT == 1

/**
    This callback function is called after USB Policy Protocol is 
    installed.

    @param Event Event of callback
    @param Context Context of callback.

    @retval VOID
**/

VOID SbUsbPolicyProtocolCallback (
    IN EFI_EVENT                    Event,
    IN VOID                         *Context )
{
    EFI_STATUS                      Status = EFI_SUCCESS;
    EFI_USB_POLICY_PROTOCOL         *EfiUsbPolicyProtocol;
    CHAR16                          *GetFchTypeStr = (CHAR16*)PcdGetPtr(AmiPcdSbFchTypeString);
    
    Status = gBS->LocateProtocol(&gEfiUsbPolicyProtocolGuid,
                                NULL,
                                &EfiUsbPolicyProtocol);

    ASSERT_EFI_ERROR(Status);

    if (!EFI_ERROR(Status)) {
        UINT8                           HcCount;
        AMI_USB_HW_SMI_HC_CONTEXT       **HcContext;
        EFI_DEVICE_PATH_PROTOCOL        *Usb3Devs[sizeof(gFchUsbDevs)/sizeof(FCH_USB3_DEVICES)];
        UINTN                           i;

        // Default all null.
        HcCount = 0;
        // HcContext = NULL;
        for (i = 0; i < sizeof(gFchUsbDevs)/sizeof(FCH_USB3_DEVICES); i++) Usb3Devs[i] = NULL;

        // check which FCH USB3 device
        for (i = 0; i < sizeof(gFchUsbDevs)/sizeof(FCH_USB3_DEVICES); i++) {
            if (StrCmp(gFchUsbDevs[i].FchTypeStr, GetFchTypeStr) == 0) {

                // Due to some other CPU only support one XHCI controller
                // Skip second XHCI controller first
                if(!mIsProcessorTypeFlavor1) {
                    if(i==1) continue;
                }
                
                DEBUG ((DEBUG_INFO|DEBUG_CHIPSET,"    <SbDxe> : Find %s[%x] USB31 %s\n",
                        gFchUsbDevs[i].FchTypeStr, HcCount, gFchUsbDevs[i].DevicePathText));

                Usb3Devs[HcCount] = ConvertTextToDevicePath(gFchUsbDevs[i].DevicePathText);
                HcCount++;
            }
        }

        // Allocate and assign context.
        HcContext = AllocatePool(HcCount * sizeof(AMI_USB_HW_SMI_HC_CONTEXT * ));
        if (HcContext != NULL) {
            for (i = 0; i < HcCount; i++) {
                HcContext[i] = AllocatePool(sizeof(AMI_USB_HW_SMI_HC_CONTEXT));
                HcContext[i]->Type = USB_HC_XHCI;
                HcContext[i]->HwSmiHandle = NULL;
                HcContext[i]->Device = Usb3Devs[i];
            }
        } else {
            // if some error occur during allocation.
            HcCount = 0;
            HcContext = NULL;
        }
        EfiUsbPolicyProtocol->AmiUsbHwSmiHcTable.HcContext = HcContext;
        EfiUsbPolicyProtocol->AmiUsbHwSmiHcTable.HcCount = HcCount;
    }
    
    if (Event) {
        gBS->CloseEvent(Event);
    }
    
}

/**
    This callback function is called after USB Protocol is 
    installed.

    @param Event Event of callback
    @param Context Context of callback.

    @retval VOID
**/

VOID SbUsbProtocolCallback (
    IN EFI_EVENT                    Event,
    IN VOID                         *Context )
{
    EFI_STATUS          Status = EFI_SUCCESS;
    EFI_USB_PROTOCOL    *SbAmiUsb = NULL;
#if defined OEM_USB_PER_PORT_DISABLE_SUPPORT && OEM_USB_PER_PORT_DISABLE_SUPPORT == 1
    UINT8               dbPortNum = 0;
#endif
	
#if defined CONTROL_ALL_USB_METHOD && CONTROL_ALL_USB_METHOD == 1
    USB_SKIP_LIST SkipAllMassTable[] = { {1, SKIP_FLAG_SKIP_MULTI_LEVEL, 0xff, 0, 0, 0x8},
                                         {0, 0, 0,    0, 0, 0  }
                                       };
#endif
#if defined CONTROL_ALL_USB_METHOD && CONTROL_ALL_USB_METHOD == 1 || defined OEM_USB_PER_PORT_DISABLE_SUPPORT && OEM_USB_PER_PORT_DISABLE_SUPPORT == 1
    UINT8           Size;
#endif
#if defined OEM_USB_PER_PORT_DISABLE_SUPPORT && OEM_USB_PER_PORT_DISABLE_SUPPORT == 1                                     
    UINT8               XhciBus = 0;
    UINT8               Xhci0Dev = 0x03; //XHCI Device number
    UINT8               Xhci1Dev = 0x04; //XHCI1 Device number
    UINT32              Buffer = 0;
    
    USB_SKIP_LIST SkipB2D0F3MassTable[] = {{0, SKIP_FLAG_SKIP_MULTI_LEVEL, 0x3803, 1, 0, 0x8}, // XHCI 0 Port 0(EHCI)
                                           {0, SKIP_FLAG_SKIP_MULTI_LEVEL, 0x3803, 2, 0, 0x8}, // XHCI 0 Port 1(EHCI)
                                           {0, SKIP_FLAG_SKIP_MULTI_LEVEL, 0x3803, 3, 0, 0x8}, // XHCI 0 Port 2(EHCI)
                                           {0, SKIP_FLAG_SKIP_MULTI_LEVEL, 0x3803, 4, 0, 0x8}, // XHCI 0 Port 3(EHCI)
                                           {0, SKIP_FLAG_SKIP_MULTI_LEVEL, 0x3803, 5, 0, 0x8}, // XHCI 0 Port 0(XHCI)
                                           {0, SKIP_FLAG_SKIP_MULTI_LEVEL, 0x3803, 6, 0, 0x8}, // XHCI 0 Port 1(XHCI)
                                           {0, SKIP_FLAG_SKIP_MULTI_LEVEL, 0x3803, 7, 0, 0x8}, // XHCI 0 Port 2(XHCI)
                                           {0, SKIP_FLAG_SKIP_MULTI_LEVEL, 0x3803, 8, 0, 0x8}, // XHCI 0 Port 3(XHCI)
                                          };
    USB_SKIP_LIST SkipB2D0F4MassTable[] = {{0, SKIP_FLAG_SKIP_MULTI_LEVEL, 0x3804, 1, 0, 0x8}, // XHCI 1 Port 0(EHCI)
                                           {0, SKIP_FLAG_SKIP_MULTI_LEVEL, 0x3804, 2, 0, 0x8}, // XHCI 1 Port 1(EHCI)
                                           {0, SKIP_FLAG_SKIP_MULTI_LEVEL, 0x3804, 3, 0, 0x8}, // XHCI 1 Port 0(XHCI)
                                          };
    
    USB_SKIP_LIST SkipOemMassTable[21] = {0};
    UINT8         IndexPort = 0;
    
#endif

    Status = gBS->LocateProtocol( &gEfiUsbProtocolGuid,
                                  NULL,
                                  &SbAmiUsb );
    if (EFI_ERROR(Status)) return;

#if defined CONTROL_ALL_USB_METHOD && CONTROL_ALL_USB_METHOD == 1
    if (gDisableAllUsbControllers)
    {
        Size = sizeof(SkipAllMassTable)/sizeof (USB_SKIP_LIST);
        SbAmiUsb->UsbCopySkipTable(SkipAllMassTable, &Size, FALSE );
    }
#endif

#if defined OEM_USB_PER_PORT_DISABLE_SUPPORT && OEM_USB_PER_PORT_DISABLE_SUPPORT == 1
    //Report SKIP port table by USB port SETUP item.
    {
        //Get Bus number of XHCI controller(Bus A)
        gPciRootBridgeIo->Pci.Read(
                            gPciRootBridgeIo,
                            EfiBootScriptWidthUint32,
                            NBIO_FIXED_ONCHIP_BUS_A_BRIDGE(0x18),
                            1,
                            &Buffer);
        XhciBus = (UINT8)(Buffer >> 8);


    	// XHCI0
		for (dbPortNum = 0; dbPortNum < 4; dbPortNum++){
			if (gSbSetupData->Xhci0PortEn[dbPortNum] == 0) {
			    SkipB2D0F3MassTable[dbPortNum].BDF = (UINT16)((XhciBus << 8)+Xhci0Dev); //Update BDF number
                SkipB2D0F3MassTable[dbPortNum + 4].BDF = (UINT16)((XhciBus << 8)+Xhci0Dev); //Update BDF number
			    SkipOemMassTable[IndexPort++] = SkipB2D0F3MassTable[dbPortNum];
			    SkipOemMassTable[IndexPort++] = SkipB2D0F3MassTable[dbPortNum + 4];
			}
		}

    	// XHCI1
		for (dbPortNum = 0; dbPortNum < 2; dbPortNum++){
			if (gSbSetupData->Xhci1PortEn[dbPortNum] == 0) {
			    SkipB2D0F4MassTable[dbPortNum].BDF = (UINT16)((XhciBus << 8)+Xhci1Dev); //Update BDF number
				SkipOemMassTable[IndexPort++] = SkipB2D0F4MassTable[dbPortNum];
				if(dbPortNum == 0) {
				    SkipB2D0F4MassTable[dbPortNum + 2].BDF = (UINT16)((XhciBus << 8)+Xhci1Dev); //Update BDF number
				    SkipOemMassTable[IndexPort++] = SkipB2D0F4MassTable[dbPortNum + 2];
				}
			}
		}

    }
    Size = sizeof(SkipOemMassTable)/sizeof (USB_SKIP_LIST);
    SbAmiUsb->UsbCopySkipTable(SkipOemMassTable, &Size, FALSE );
#endif
    if (Event) {
        gBS->CloseEvent(Event);
    }
}

/**
    This callback function is called after USB Protocol is 
    installed.(RV2 CPU)

    @param Event Event of callback
    @param Context Context of callback.

    @retval VOID
**/

VOID RV2SbUsbProtocolCallback (
    IN EFI_EVENT                    Event,
    IN VOID                         *Context )
{
    EFI_STATUS          Status = EFI_SUCCESS;
    EFI_USB_PROTOCOL    *SbAmiUsb = NULL;
#if defined OEM_USB_PER_PORT_DISABLE_SUPPORT && OEM_USB_PER_PORT_DISABLE_SUPPORT == 1
    UINT8               dbPortNum = 0;
#endif
    
#if defined CONTROL_ALL_USB_METHOD && CONTROL_ALL_USB_METHOD == 1
    USB_SKIP_LIST SkipAllMassTable[] = { {1, SKIP_FLAG_SKIP_MULTI_LEVEL, 0xff, 0, 0, 0x8},
                                         {0, 0, 0,    0, 0, 0  }
                                       };
#endif
#if defined CONTROL_ALL_USB_METHOD && CONTROL_ALL_USB_METHOD == 1 || defined OEM_USB_PER_PORT_DISABLE_SUPPORT && OEM_USB_PER_PORT_DISABLE_SUPPORT == 1
    UINT8           Size;
#endif
#if defined OEM_USB_PER_PORT_DISABLE_SUPPORT && OEM_USB_PER_PORT_DISABLE_SUPPORT == 1                                     
    UINT8               XhciBus = 0;
    UINT8               Xhci0Dev = 0x03; //XHCI Device number
    //UINT8               Xhci1Dev = 0x04; //XHCI1 Device number
    UINT32              Buffer = 0;
    
    USB_SKIP_LIST SkipB2D0F3MassTable[] = {{0, SKIP_FLAG_SKIP_MULTI_LEVEL, 0x3803,  1, 0, 0x8}, // XHCI 0 Port 0(EHCI)
                                           {0, SKIP_FLAG_SKIP_MULTI_LEVEL, 0x3803,  2, 0, 0x8}, // XHCI 0 Port 1(EHCI)
                                           {0, SKIP_FLAG_SKIP_MULTI_LEVEL, 0x3803,  3, 0, 0x8}, // XHCI 0 Port 2(EHCI)
                                           {0, SKIP_FLAG_SKIP_MULTI_LEVEL, 0x3803,  4, 0, 0x8}, // XHCI 0 Port 3(EHCI)
                                           {0, SKIP_FLAG_SKIP_MULTI_LEVEL, 0x3803,  5, 0, 0x8}, // XHCI 0 Port 4(EHCI)
                                           {0, SKIP_FLAG_SKIP_MULTI_LEVEL, 0x3803,  6, 0, 0x8}, // XHCI 0 Port 5(EHCI)
                                           {0, SKIP_FLAG_SKIP_MULTI_LEVEL, 0x3803,  7, 0, 0x8}, // XHCI 0 Port 0(XHCI)
                                           {0, SKIP_FLAG_SKIP_MULTI_LEVEL, 0x3803,  8, 0, 0x8}, // XHCI 0 Port 1(XHCI)
                                           {0, SKIP_FLAG_SKIP_MULTI_LEVEL, 0x3803,  9, 0, 0x8}, // XHCI 0 Port 2(XHCI)
                                           {0, SKIP_FLAG_SKIP_MULTI_LEVEL, 0x3803, 10, 0, 0x8}, // XHCI 0 Port 3(XHCI)
    };
    //USB_SKIP_LIST SkipB2D0F4MassTable[] = {{0, SKIP_FLAG_SKIP_MULTI_LEVEL, 0x3804, 1, 0, 0x8}, // XHCI 1 Port 0(EHCI)
    //                                       {0, SKIP_FLAG_SKIP_MULTI_LEVEL, 0x3804, 2, 0, 0x8}, // XHCI 1 Port 1(EHCI)
    //                                       {0, SKIP_FLAG_SKIP_MULTI_LEVEL, 0x3804, 3, 0, 0x8}, // XHCI 1 Port 0(XHCI)
    //                                      };
    
    USB_SKIP_LIST SkipOemMassTable[21] = {0};
    UINT8         IndexPort = 0;
    
#endif

    Status = gBS->LocateProtocol( &gEfiUsbProtocolGuid,
                                  NULL,
                                  &SbAmiUsb );
    if (EFI_ERROR(Status)) return;

#if defined CONTROL_ALL_USB_METHOD && CONTROL_ALL_USB_METHOD == 1
    if (gDisableAllUsbControllers)
    {
        Size = sizeof(SkipAllMassTable)/sizeof (USB_SKIP_LIST);
        SbAmiUsb->UsbCopySkipTable(SkipAllMassTable, &Size, FALSE );
    }
#endif

#if defined OEM_USB_PER_PORT_DISABLE_SUPPORT && OEM_USB_PER_PORT_DISABLE_SUPPORT == 1
    //Report SKIP port table by USB port SETUP item.
    {
        //Get Bus number of XHCI controller(Bus A)
        gPciRootBridgeIo->Pci.Read(
                            gPciRootBridgeIo,
                            EfiBootScriptWidthUint32,
                            NBIO_FIXED_ONCHIP_BUS_A_BRIDGE(0x18),
                            1,
                            &Buffer);
        XhciBus = (UINT8)(Buffer >> 8);


        // XHCI0
        for (dbPortNum = 0; dbPortNum < 6; dbPortNum++){
            if (gSbSetupData->Xhci0PortEn[dbPortNum] == 0) {
                SkipB2D0F3MassTable[dbPortNum].BDF = (UINT16)((XhciBus << 8)+Xhci0Dev); //Update BDF number
                if(dbPortNum < 4) SkipB2D0F3MassTable[dbPortNum + 6].BDF = (UINT16)((XhciBus << 8)+Xhci0Dev); //Update BDF number
                SkipOemMassTable[IndexPort++] = SkipB2D0F3MassTable[dbPortNum];
                if(dbPortNum < 4) SkipOemMassTable[IndexPort++] = SkipB2D0F3MassTable[dbPortNum + 6];
            }
        }

        // XHCI1
        //for (dbPortNum = 0; dbPortNum < 2; dbPortNum++){
        //    if (gSbSetupData->Xhci1PortEn[dbPortNum] == 0) {
        //        SkipB2D0F4MassTable[dbPortNum].wBDF = (UINT16)((XhciBus << 8)+Xhci1Dev); //Update BDF number
        //        SkipOemMassTable[IndexPort++] = SkipB2D0F4MassTable[dbPortNum];
        //        if(dbPortNum == 0) {
        //            SkipB2D0F4MassTable[dbPortNum + 2].wBDF = (UINT16)((XhciBus << 8)+Xhci1Dev); //Update BDF number
        //            SkipOemMassTable[IndexPort++] = SkipB2D0F4MassTable[dbPortNum + 2];
        //        }
        //    }
        //}

    }
    Size = sizeof(SkipOemMassTable)/sizeof (USB_SKIP_LIST);
    SbAmiUsb->UsbCopySkipTable(SkipOemMassTable, &Size, FALSE );
#endif
    if (Event) {
        gBS->CloseEvent(Event);
    }
}
#endif

/**
    This function is the entry point for this DXE. This function
    initializes the chipset SB

    @param ImageHandle Image handle
    @param SystemTable Pointer to the system table

             
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/

EFI_STATUS
EFIAPI
SbDxeInit (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
    EFI_STATUS              Status;
    EFI_EVENT               Event;
    EFI_CPU_ARCH_PROTOCOL   *CpuArch = NULL;
    EFI_GUID                CpuInfoHobGuid = AMI_CPUINFO_HOB_GUID;
    EFI_GUID                HobListGuid = HOB_LIST_GUID;
    CPUINFO_HOB             *CpuInfoHob;
    UINTN                   SbSetupSize = sizeof(SB_SETUP_DATA);
    UINT8                   SbIoApicId = 0;
    UINT8                   StartLocalApicId = 0;
    VOID                    *Registration = NULL;
    CHAR16	                *GetFchTypeStr = (CHAR16*)PcdGetPtr(AmiPcdSbFchTypeString);
    UINT8                   i;
    UINT8                   XhciQuestionSwitch;

    InitAmiLib(ImageHandle, SystemTable);

    PROGRESS_CODE(DXE_SB_INIT);

    Status = gBS->AllocatePool(
                            EfiBootServicesData,
                            SbSetupSize,
                            &gSbSetupData);
    ASSERT_EFI_ERROR (Status);
    
    // Update flag for detecting different processor type
    mIsProcessorTypeFlavor1 = IsProcessorTypeFlavor1();

    GetSbSetupData(gRT, gSbSetupData, FALSE);

// (EIP46008.1)>
//    RESET_IO16_PM(ACPI_IOREG_PM1_CNTL, 0x1C01);       // Clear the SLP_TYP and SCI_EN of PmControl
// <(EIP46008.1)

    Status = gBS->LocateProtocol(
                            &gEfiPciRootBridgeIoProtocolGuid,
                            NULL,
                            &gPciRootBridgeIo);
    ASSERT_EFI_ERROR(Status);

    Status = gBS->LocateProtocol(
                            &gEfiS3SaveStateProtocolGuid,
                            NULL,
                            &gBootScriptSave);
    ASSERT_EFI_ERROR(Status);

    // The Event after PciIoProtocol
    Status = gBS->CreateEvent (
                                EFI_EVENT_NOTIFY_SIGNAL,
                                TPL_CALLBACK,
                                SBAfterPciInit,
                                NULL,
                                &mEvent);

    if(EFI_ERROR(Status)) return Status;

    Status = gBS->RegisterProtocolNotify (
                                &gEfiPciIoProtocolGuid,
                                mEvent,
                                &mReg);
    if(EFI_ERROR(Status)) return Status;

    // The Event ready to boot
    Status = EfiCreateEventReadyToBootEx(TPL_NOTIFY, SBReadyToBoot, NULL, &gEvtReadyToBoot);
    
    if(EFI_ERROR(Status)) return Status;

    // Update BIOS setup layout for different XHCI map
    if(mIsProcessorTypeFlavor1) {
        XhciQuestionSwitch = 0; //PCO CPU
    } else {
        XhciQuestionSwitch = 1; //RV2 CPU
    }
    Status = gRT->SetVariable (
                L"AmiSbXhciSwitchSuppressIfSetupData",
                &gAmiSbRaven2XhciQuestionGuid,
                EFI_VARIABLE_BOOTSERVICE_ACCESS,
                sizeof(UINT8),
                &XhciQuestionSwitch
                );
    ASSERT_EFI_ERROR(Status);

    Status = EfiCreateEventReadyToBootEx(TPL_NOTIFY, USBPrePortDisableCallback, NULL, &Event);
    if(EFI_ERROR(Status)) return Status;
    
    // IrConfig had removed from Sandstone
    /*
    if (gSbSetupData->IrConfig != 0) {
        CSP_RES_ITEM    IrResource = {0x550, 2, EfiGcdIoTypeIo, -1};   //IMC IR confirgure
        Status = LibAllocCspResource(&IrResource,
                                    1,
                                    ImageHandle,
                                    NULL);
        ASSERT_EFI_ERROR(Status);
    }
    */
  
    for (i = 0; i < gFchResTblCount; i++) {
    	if (StrCmp(gFchResTbl[i].FchTypeStr, GetFchTypeStr) == 0) {
            Status = LibAllocCspResource(gFchResTbl[i].FchResTable,
            		                     gFchResTbl[i].TableCount,
    	                                 ImageHandle,
    	                                 NULL);

            break;
        }
    }
	
    // Put the I/O APIC in Virtual wire mode

    // CHIPSET PROGRAMMING TO ENABLE IOAPIC GOES HERE

    CpuInfoHob=(CPUINFO_HOB*)GetEfiConfigurationTable(gST,&HobListGuid);
    if(CpuInfoHob == NULL) Status=EFI_UNSUPPORTED;
    else Status=FindNextHobByGuid(&CpuInfoHobGuid,(VOID**)&CpuInfoHob);

    if(!EFI_ERROR(Status)){
        // For systems with >= 16 APICs, put the IO-APICs at 0..n and
        // put the local-APICs at m..z
        // For systems with < 16 APICs, put the Local-APICs at 0..n and
        // put the IO-APICs at (n + 1)..z
        // This is needed because many IO-APIC devices only have 4 bits
        // for their APIC id and therefore must reside at 0..15
        // check the local APIC ID
        StartLocalApicId=CpuInfoHob->Cpuinfo->ApicId;
        if (StartLocalApicId >=16 )
        {
            SbIoApicId = 0;
        } else {
            SbIoApicId = CpuInfoHob->CpuCount+1;
        }
    } else {
        SbIoApicId = NCPU + 1;
    }
    

    // IO APIC index (0)
    WRITE_MEM8_S3(gBootScriptSave, APCB, 0);// MemWrite8(pIOAPIC, 0);
    // New ID (at offset 0x10)
    WRITE_MEM32_S3(gBootScriptSave, APCB + 0x10, SbIoApicId << 24); // MemWrite32(pIOAPIC + 4,SbIoApicId << 24);
    //Update the ApicRoutTable and ApicInfoTable
    UpdateSbIoApicIdToRouteTable(SbIoApicId,APCB);

    // Enable Top of 4GB flash ROM access

    // CHIPSET PROGRAMMING TO ENABLE TOP of 4GB ROM ACCESS GOES HERE

    //### Sync template but move to Sb8259InitLib ###
    #if defined SB_8259_PROTOCOL_SUPPORT && SB_8259_PROTOCOL_SUPPORT == 1 && (SB_8259_PROTOCOL_LIB_SUPPORT == 0)
    // Install 8259 services
    Initialize8259(ImageHandle, SystemTable);
    #endif

    // Install watchdog timer services
    WatchdogInit(ImageHandle, SystemTable);

//#if defined HPET_PROTOCOL_SUPPORT && HPET_PROTOCOL_SUPPORT == 1
//   RWSbPmuIo8(0,BIT06,BIT06); // Make sure HpetEn decode is enabled.
//#endif
    
#if defined SB_TIMER_ARCH_PROTOCOL_SUPPORT && SB_TIMER_ARCH_PROTOCOL_SUPPORT == 1
    //Install Legacy timer callback. This is so there is no dependency on
    //Cpu arch protocol.
    // Find the CPU Arch Protocol
    Status = gBS->LocateProtocol (
                                    &gEfiCpuArchProtocolGuid,
                                    NULL,
                                    &CpuArch);
    if (Status == EFI_SUCCESS) {
        TimerInitWrapper(NULL, NULL);
    } else {
        Status = RegisterProtocolCallback(
                                        &gEfiCpuArchProtocolGuid,
                                        TimerInitWrapper,
                                        NULL,
                                        &Event,
                                        &gCpuArchNotifyReg);
        ASSERT_EFI_ERROR(Status);
    }
#else
    TimerInit();
#endif

#if   SMM_SUPPORT
    // Use AMD UEFI SMM Drivers.
#endif

    //
    // Enable or Disable the Devices depending upon the Setup.
    //
    EnableDisableSBDevices();
#if defined AMIUSB_SUPPORT && AMIUSB_SUPPORT == 1
#if defined CONTROL_ALL_USB_METHOD && CONTROL_ALL_USB_METHOD == 1
    if (gSbSetupData->UsbAllEnable == 0){
        gDisableAllUsbControllers = TRUE;
    }
#endif
    
    //USB Policy protocol    
    {
       //EFI_STATUS                      Status = EFI_SUCCESS;
       EFI_USB_POLICY_PROTOCOL         *EfiUsbPolicyProtocol;
       
       Status = gBS->LocateProtocol(&gEfiUsbPolicyProtocolGuid,
                                   NULL,
                                   &EfiUsbPolicyProtocol);
                                   
       if (EFI_ERROR(Status)) {
           Status = RegisterProtocolCallback( &gEfiUsbPolicyProtocolGuid,\
                                              SbUsbPolicyProtocolCallback,\
                                              NULL,\
                                              &gEvtUsbPolicyProtocol,\
                                              &gRegUsbPolicyProtocol );
       } else {
           SbUsbPolicyProtocolCallback(NULL,NULL);
       }
       
    }
#endif
    
#if defined SB_TIMER_ARCH_PROTOCOL_SUPPORT && SB_TIMER_ARCH_PROTOCOL_SUPPORT == 1
    Status = gBS->CreateEvent (
                    EVT_NOTIFY_SIGNAL,
                    TPL_CALLBACK,
                    RegisterRestoreCallBack,
                    NULL,
                    &gRegisterRestoreEvent
                    );
#endif

#if defined EMUL6064_SUPPORT && EMUL6064_SUPPORT == 1
//HCEx50HCE IntrEn  
//BIT4 EmulationSmiEn. Read-write. Reset: 0. 1=Gnerate SMI if emulation interrupt happens
     RW_MEM32(HCEx50_IntrEn,EmulationSmiEn, 0); 
#endif

    //
    // Board specific init
    //
    Status = SbDxeBoardInit (ImageHandle, SystemTable);
	InstallSbPolicyProtocol();

    return Status;
}

/**
    Update the correct Sb IO APCI ID to Route table for Mp table create.

        
    @param ApicId 
    @param ApicAddress 

    @retval VOID

**/

VOID
UpdateSbIoApicIdToRouteTable (
  IN UINT8   ApicId,
  IN UINT32  ApicAddress
  )
{
//### <AAV> make a generic routine later.
#if defined AmiBoardInfo_SUPPORT &&  AmiBoardInfo_SUPPORT == 1
    AMI_BOARD_INFO2_PROTOCOL    *AmiBoardInfo2Protocol = NULL;
    AMI_SDL_PCI_DEV_INFO   		*RouteTable = NULL;
    UINT8                       BuildIoApicId = 1;
    UINT32                      i = 0, j = 0, Count = 0;
    EFI_STATUS                  Status;

    Status = gBS->LocateProtocol(&gAmiBoardInfo2ProtocolGuid, NULL, (VOID**)&AmiBoardInfo2Protocol);
    if (!EFI_ERROR(Status))
    {
        Count = AmiBoardInfo2Protocol->ApicBrdData->IoApicCount;

        // Update Correct APICID to AMI_SDL_IO_APIC_INFO
        //-----------------        
        for(i = 0; i < Count; i++) {
            // Find the SB - IOAPIC
            if (AmiBoardInfo2Protocol->ApicBrdData->IoApicInfo[i].ApicAddress == ApicAddress) {
                BuildIoApicId = AmiBoardInfo2Protocol->ApicBrdData->IoApicInfo[i].ApicIdBuild;
                AmiBoardInfo2Protocol->ApicBrdData->IoApicInfo[i].ApicIdBuild = ApicId;
            }
        } 

        Count = (UINT32)AmiBoardInfo2Protocol->PciBrdData->PciDevCount;
   
        RouteTable = AmiBoardInfo2Protocol->PciBrdData->PciDevices ;
        
        // Update Correct APICID to PCI RouteTable
        for(i = 0; i < Count; i++)
        {
            for(j = 0; j < 4; j++)
            {
			// SB IoApic: 0~23
                if( RouteTable[i].ApicIrq[j].IoApicId == BuildIoApicId && RouteTable[i].ApicIrq[j].IoApicItin < 24 ){
                    RouteTable[i].ApicIrq[j].IoApicId = ApicId;
                }
            }   
        }
        
        
     }
#endif
}


/**
    This function  is a PCIIO call back function ,it will did it
    After PCI

    @param Event 
    @param Context 

    @retval VOID

**/
VOID
SBAfterPciInit(
    IN EFI_EVENT Event,
    IN VOID *Context
)
{


#if (SB_LPC_PORT80_SUPPORT == 0)
    RW_PCI8_S3((PCIB_BUS_DEV_FUN << 16) + FCH_PCIB_REG04, BIT0, 0);
#endif
    //
    // User Disabling Unused SATA Ports
    //

    //
    // Usb port disable function support
    //
#if defined AMIUSB_SUPPORT && AMIUSB_SUPPORT == 1
{
    EFI_USB_PROTOCOL    *SbAmiUsb = NULL;
    EFI_STATUS           Status;
    
    Status = gBS->LocateProtocol(&gEfiUsbProtocolGuid,
                                  NULL,
                                  &SbAmiUsb);

    if (EFI_ERROR(Status)) {
        if(mIsProcessorTypeFlavor1) {
            Status = RegisterProtocolCallback( &gEfiUsbProtocolGuid,\
                                               SbUsbProtocolCallback,\
                                               NULL,\
                                               &gEvtUsbProtocol,\
                                               &gRegUsbProtocol );
        } else {
            Status = RegisterProtocolCallback( &gEfiUsbProtocolGuid,\
                                               RV2SbUsbProtocolCallback,\
                                               NULL,\
                                               &gEvtUsbProtocol,\
                                               &gRegUsbProtocol );
        }
    } else {
        if(mIsProcessorTypeFlavor1) {
            SbUsbProtocolCallback(NULL, NULL);
        } else {
            RV2SbUsbProtocolCallback(NULL, NULL);
        }
    }
}
#endif
    
    // Close Event and don't run it again
    gBS->CloseEvent(Event);
}


// (EIP53061)>
#if CONTROL_ALL_USB_METHOD
/**
    This function is will disable all usb controller

    @param VOID

    @retval VOID
**/
VOID CheckDisableUsbControllers()
{
    EFI_USB_PROTOCOL        *UsbProtocol;
    EFI_STATUS              Status;
    UINT32                  DieBusNum = 0;
    static EFI_GUID UsbProtocolGuid = EFI_USB_PROTOCOL_GUID;

    Status = gBS->LocateProtocol(
                 &UsbProtocolGuid,
                 NULL,
                 &UsbProtocol
             );
    if (EFI_ERROR(Status)) return;

    if (gBootScriptSave == NULL) {
    EFI_STATUS      Status;
        Status = gBS->LocateProtocol(&gEfiS3SaveStateProtocolGuid,NULL, \
                    &gBootScriptSave);
        ASSERT_EFI_ERROR(Status);
    }
    if(gSbSetupData->UsbAllEnable == 0) {
    	UsbProtocol->UsbRtShutDownLegacy();
    	
    	SbSmnRwS3(DieBusNum, FCH_SS_USB_NBIF_STRAP0, ~(UINT32) BIT28, 0);
    	SbSmnRwS3(DieBusNum, FCH_SS_USB1_NBIF_STRAP0, ~(UINT32) BIT28, 0);
    }

}
#endif
// <(EIP53061)

/**
    Due to AMD BTS testing fail, it required to restore FCH registers 
    back while resume from S3.

    @param VOID

    @retval VOID

**/

VOID
RestoreFchS3ForBTS()
{
    UINT8  buffer8 = 0;
    UINT32 buffer32 = 0;
    UINTN  Buffer,i;
    UINT8  Mp2BridgeBus;
    UINTN  FchBtsRegScriptSize;
    
    BOOT_SCRIPT_PCI_REGISTER_SAVE gFchBtsRegScriptTbl[] = {
		// Save NBIO Internal Br0 for MP2 Bus and resource
		NBIO_FIXED_ONCHIP_BUS_A_BRIDGE(0x10),  EfiBootScriptWidthUint32,
		NBIO_FIXED_ONCHIP_BUS_A_BRIDGE(0x14),  EfiBootScriptWidthUint32,
		NBIO_FIXED_ONCHIP_BUS_A_BRIDGE(0x18),  EfiBootScriptWidthUint32,
		NBIO_FIXED_ONCHIP_BUS_A_BRIDGE(0x1C),  EfiBootScriptWidthUint32,
		NBIO_FIXED_ONCHIP_BUS_A_BRIDGE(0x20),  EfiBootScriptWidthUint32,
		NBIO_FIXED_ONCHIP_BUS_A_BRIDGE(0x24),  EfiBootScriptWidthUint32,
		NBIO_FIXED_ONCHIP_BUS_A_BRIDGE(0x04),  EfiBootScriptWidthUint8,
		// Save MP2 controller.
		SB_PCI_CFG_ADDRESS(FIXED_MP2_BUS_SANDSTONE, 0, 7, 0x18),  EfiBootScriptWidthUint32,
		SB_PCI_CFG_ADDRESS(FIXED_MP2_BUS_SANDSTONE, 0, 7, 0x24),  EfiBootScriptWidthUint32,
		SB_PCI_CFG_ADDRESS(FIXED_MP2_BUS_SANDSTONE, 0, 7, 0x0C),  EfiBootScriptWidthUint8,
		SB_PCI_CFG_ADDRESS(FIXED_MP2_BUS_SANDSTONE, 0, 7, 0x04),  EfiBootScriptWidthUint16,
		SB_PCI_CFG_ADDRESS(FIXED_MP2_BUS_SANDSTONE, 0, 7, 0x6C),  EfiBootScriptWidthUint16,
		SB_PCI_CFG_ADDRESS(FIXED_MP2_BUS_SANDSTONE, 0, 7, 0x3C),  EfiBootScriptWidthUint8
    };

    if (gBootScriptSave == NULL) {
    EFI_STATUS      Status;
        Status = gBS->LocateProtocol(&gEfiS3SaveStateProtocolGuid,NULL, \
                    &gBootScriptSave);
        ASSERT_EFI_ERROR(Status);
    }

    // Get Bus# of MP2
    gPciRootBridgeIo->Pci.Read(
                    gPciRootBridgeIo,
                    EfiBootScriptWidthUint32,
                    NBIO_FIXED_ONCHIP_BUS_A_BRIDGE(0x18),
                    1,
                    &Buffer);
    Mp2BridgeBus = (UINT8)(Buffer >> 8);
    
    FchBtsRegScriptSize = sizeof(gFchBtsRegScriptTbl) / sizeof(BOOT_SCRIPT_PCI_REGISTER_SAVE);
    
    for (i = 0; i < FchBtsRegScriptSize; i++) {
    	if (Mp2BridgeBus != FIXED_MP2_BUS_SANDSTONE && gFchBtsRegScriptTbl[i].Addr.Bus == FIXED_MP2_BUS_SANDSTONE) {
    		gFchBtsRegScriptTbl[i].Addr.Bus = Mp2BridgeBus;
    	}

        gPciRootBridgeIo->Pci.Read(
                        gPciRootBridgeIo,
                        gFchBtsRegScriptTbl[i].Width,
                        gFchBtsRegScriptTbl[i].Address,
                        1,
                        &Buffer);

        BOOT_SCRIPT_S3_PCI_CONFIG_WRITE_MACRO(
                        CSP_BOOT_SCRIPT_SERVICE_EX(gBootScriptSave),
                        gFchBtsRegScriptTbl[i].Width,
                        gFchBtsRegScriptTbl[i].Address,
                        1,
                        &Buffer);
    }
    
    //SMIxD0 MemTrapping0
    buffer32 = READ_MEM32(ACPI_MMIO_BASE + SMI_BASE + 0xD0);
    WRITE_MEM32_S3(gBootScriptSave, ACPI_MMIO_BASE + SMI_BASE + 0xD0, buffer32);

    //D14F3xD0
    buffer32 = READ_PCI32_SB(0xD0);
    WRITE_PCI32_SB_S3(gBootScriptSave, 0xD0,buffer32);

    //PMx74
    buffer32 = READ_MEM32(ACPI_MMIO_BASE + PMIO_BASE + 0x74);
    WRITE_MEM32_S3(gBootScriptSave, ACPI_MMIO_BASE + PMIO_BASE + 0x74, buffer32);
    
    //SmiCtl3
    buffer8 = READ_MEM8(ACPI_MMIO_BASE + SMI_BASE + 0xAD);
    WRITE_MEM8_S3(gBootScriptSave, ACPI_MMIO_BASE + SMI_BASE + 0xAD, buffer8);

    //SmiCtl4
    buffer32 = READ_MEM32(ACPI_MMIO_BASE + SMI_BASE + 0xB0);
    WRITE_MEM32_S3(gBootScriptSave, ACPI_MMIO_BASE + SMI_BASE + 0xB0, buffer32);
    
    //#### RVA9 : The XHCI behind bridge no fixed bus. Check BTS later.
    //####//D10F0x4C XHCI OverCurrent
    //####WRITE_PCI32_XHCI0_S3(gBootScriptSave, FCH_XHCI_REG48, FCH_XHCI_IND_REG04);
    //####buffer32 = READ_PCI32_XHCI0(FCH_XHCI_REG4C);
    //####WRITE_PCI32_XHCI0_S3(gBootScriptSave, FCH_XHCI_REG4C, buffer32);
}

/**
    Restore Fch PCI register value for S3 resume.

    @param VOID

    @retval VOID

**/

VOID
RestoreFchPciS3()
{
    EFI_STATUS      Status;
    UINTN           Buffer,i;

    if (gPciRootBridgeIo == NULL) {
        Status = gBS->LocateProtocol(&gEfiPciRootBridgeIoProtocolGuid, NULL, \
                    &gPciRootBridgeIo);
        ASSERT_EFI_ERROR(Status);
    }

    if (gBootScriptSave == NULL) {
        Status = gBS->LocateProtocol(&gEfiS3SaveStateProtocolGuid,NULL, \
                    &gBootScriptSave);
        ASSERT_EFI_ERROR(Status);
    }
    if (gBootScriptSave == NULL && gPciRootBridgeIo == NULL) {
        PROGRESS_CODE(DXE_SB_ERROR);
        EFI_DEADLOOP();
    }

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
}

/**
    This function  is a ready to boot event function ,it will did it
    when ready to boot

    @param Event 
    @param Context 

    @retval VOID

**/
VOID
SBReadyToBoot(
    IN EFI_EVENT Event,
    IN VOID *Context
)
{

    RestoreFchS3ForBTS();

    RestoreFchPciS3();
    
#if PROGRAM_SDIO_SSID_FOR_BBT
    // Due to Sdio controller will still exist after SdConfig disabled.
    // We are still checking this behavior with AMD side.
    if(!PcdGet8(PcdSdConfig)) {
    	UINT32 SdSsid;
    	SdSsid = READ_PCI32(0x00, 0x14, 0x06, 0x2C);
    	WRITE_PCI32(0x00, 0x14, 0x06, 0x2C, SdSsid);
    }
#endif

    // Close Event and don't run it again
    gBS->CloseEvent(Event);
}

/**
    This function  is a ready to boot event function ,it will did it
    when ready to boot

    @param Event 
    @param Context 

    @retval VOID

**/

VOID
USBPrePortDisableCallback(
    IN EFI_EVENT Event,
    IN VOID *Context
)
{
#if defined OEM_USB_PER_PORT_DISABLE_SUPPORT && OEM_USB_PER_PORT_DISABLE_SUPPORT == 1
    UINT16      *BootOrder = NULL;
    UINTN       BootOrderSize = 0;
    EFI_STATUS  Status = EFI_SUCCESS;
#endif 
    
#if CONTROL_ALL_USB_METHOD  
    CheckDisableUsbControllers();
#endif 

#if defined OEM_USB_PER_PORT_DISABLE_SUPPORT && OEM_USB_PER_PORT_DISABLE_SUPPORT == 1
    Status = GetEfiVariable(
        L"BootOrder", &gEfiGlobalVariableGuid, NULL, &BootOrderSize,(VOID**)&BootOrder
    );

    if (!EFI_ERROR(Status) && BootOrderSize != 0) {
        if(mIsProcessorTypeFlavor1) {
            EnableDisableUsbPort();
        } else {
            RV2EnableDisableUsbPort();
        }
    }
#endif

    // Close Event and don't run it again
    gBS->CloseEvent(Event);
}


/**
    Decompress MISCRAID.BIN to conventional memory
    According to legacy BIOS put MISCRAID.BIN to 0x30000
    SB.ASM ==> DecompressSbRaidUiBin_FAR

    @param MiscGuid 

             
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/

EFI_STATUS DecompressMiscUI( IN EFI_GUID *MiscGuid)
{
    EFI_STATUS                      Status = EFI_SUCCESS;
    EFI_PHYSICAL_ADDRESS            MiscLocation;
    EFI_FIRMWARE_VOLUME2_PROTOCOL   *fv;
    EFI_FV_FILE_ATTRIBUTES          Attributes;
    EFI_FV_FILETYPE                 FileType;
    EFI_HANDLE                      *HandleBuffer;
    UINT32                          FvStatus=0;
    UINTN                           Size,i,NumberOfHandles;
    VOID*                           ImgBuf;

    //Locate protocol.
    Status = gBS->LocateHandleBuffer(ByProtocol,
                &gEfiFirmwareVolume2ProtocolGuid,
                NULL,&NumberOfHandles,&HandleBuffer);
    if(EFI_ERROR (Status)) return Status;

    //Look for FV with MiscUI storage file
    for (i = 0; i < NumberOfHandles; i++) {
        // Get the protocol on this handle
        Status = gBS->HandleProtocol(HandleBuffer[i],
                    &gEfiFirmwareVolume2ProtocolGuid,&fv);
        if(EFI_ERROR(Status))return Status;

        Status=fv->ReadFile(fv,
                MiscGuid,NULL,&Size,&FileType,&Attributes,&FvStatus);
        if (Status == EFI_SUCCESS) break;
    }
    gBS->FreePool(HandleBuffer);

    if (Status == EFI_SUCCESS) {
        Size=0;
        ImgBuf=NULL;
        Status=fv->ReadSection(fv,
                        MiscGuid,
                        EFI_SECTION_RAW,
                        0,
                        (VOID**)&ImgBuf,
                        &Size,&FvStatus);
        if(EFI_ERROR(Status)) return Status;
        //
        // according to CORE8
        // SB700/SB750 RAID UI in TEMP_DSEG(0x30000)
        //
        MiscLocation=0x30000;
        Status = gBS->AllocatePages(
                    AllocateAddress,
                    EfiReservedMemoryType,
                    Size/4096+1, // Nomber of 4k pages
                    &MiscLocation);
        gBS->CopyMem((VOID*)MiscLocation,ImgBuf,Size);
        DEBUG ((DEBUG_INFO|DEBUG_CHIPSET,"MISC Radi file in memory location = %4X \n", MiscLocation));

        if(EFI_ERROR(Status)) {
            PROGRESS_CODE(DXE_SB_ERROR);
            EFI_DEADLOOP();
        }
    }
    return Status;
}

#if HPET_SUPPORT

#include <Acpi20.h>
#include <Protocol/AcpiSupport.h>

//========================================================================================
/**
    This function will create HPET acpi Table when ACPI Support Protocol Will be available
    Context will stand for HPET Enable Setup question

    @param Event event that has been signaled
    @param Context 
        if NULL than HPET feature is disabled  and no table need to be created

    @retval VOID

**/
VOID CreateHpetAcpiTable(IN EFI_EVENT Event, IN VOID *Context) {
#if defined (HPET_BASE_ADDRESS) && (HPET_BASE_ADDRESS != 0)
    EFI_STATUS                  Status=0;
    HPET_20                     *AcpiTbl;
    EFI_ACPI_TABLE_PROTOCOL     *At;
    UINTN                       TableKey;
    UINTN                       HpetBase = HPET_BASE_ADDRESS;

    //--------------------------------
    //it must be only one instance of such protocol
    Status = gBS->LocateProtocol( &gEfiAcpiTableProtocolGuid, NULL, &At );
    if(EFI_ERROR(Status)){
        DEBUG ((DEBUG_ERROR|DEBUG_CHIPSET,"HPET LocateProtocol(ACPISupport)- %r Error\n", Status));
        return;
    }DEBUG ((DEBUG_INFO|DEBUG_CHIPSET,"HPET LocateProtocol(ACPISupport)- %r Success\n", Status));

    AcpiTbl=AllocateZeroPool(sizeof(HPET_20));
    ASSERT(AcpiTbl);
    if(AcpiTbl){
        //Fill Table header;
        AcpiTbl->Header.Signature=HPET_SIG;
        AcpiTbl->Header.Length=sizeof(HPET_20);
        AcpiTbl->Header.Revision=1;
        AcpiTbl->Header.Checksum=0;
        gBS->CopyMem((VOID*)AcpiTbl->Header.OemId, \
            CONVERT_TO_STRING(SB_HPET_OEM_ID), \
            sizeof(AcpiTbl->Header.OemId) \
        );
        gBS->CopyMem((VOID*)AcpiTbl->Header.OemTblId, \
            CONVERT_TO_STRING(SB_HPET_OEM_TBL_ID), \
            sizeof(AcpiTbl->Header.OemTblId) \
        );
        AcpiTbl->Header.OemRev=ACPI_OEM_REV;
        //---AcpiTbl->Header.CreatorId=0x2E494D41;//"AMI."
        AcpiTbl->Header.CreatorId=CREATOR_ID_AMI;//"AMI"
        AcpiTbl->Header.CreatorRev=CORE_MAJOR_VERSION;

        //fill HPET Fields
        //The GAS structure
        AcpiTbl->BaseAddress.AddrSpcID=GAS_SYS_MEM;
        AcpiTbl->BaseAddress.RegBitWidth=64;
        AcpiTbl->BaseAddress.RegBitOffs=0;
        ////Base address of 1K HPET RegBlock space
        AcpiTbl->BaseAddress.Address=HpetBase;

        // Decode HPET to get ID.
        //RW_MEM32(ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REG50, HpetBase | BIT0, 0x7FF);
        AcpiTbl->EvtTmrBlockId.TMR_BLK_ID=*(UINT32*)(UINTN)HpetBase;

        AcpiTbl->MinTickPeriod=14318; //approx 1ms

        //Add table
        Status = At->InstallAcpiTable( At, \
                                       AcpiTbl, \
                                       sizeof(HPET_20), \
                                       &TableKey );
        DEBUG ((DEBUG_INFO|DEBUG_CHIPSET,"ACPITable.InstallAcpiTable(AcpiTbl) = %r \n", Status));
        ASSERT_EFI_ERROR(Status);

        //free memory used for table image
        gBS->FreePool(AcpiTbl);
    }
#endif
    
    //Kill the Event
    gBS->CloseEvent(Event);
}

#endif

#if defined WDT_SUPPORT && WDT_SUPPORT == 1
//========================================================================================
/**
    This function will create WDRT acpi Table when ACPI Support Protocol Will be available

    @param Event event that has been signaled
    @param Context 
        if NULL than WDRT feature is disabled  and no table need to be created

    @retval VOID

**/
VOID CreateWdrtAcpiTable(IN EFI_EVENT Event, IN VOID *Context) {
    EFI_STATUS                  Status=0;
    
    EFI_ACPI_TABLE_PROTOCOL     *At;
    UINTN                       TableKey;
    UINTN                       volatile WdrtBase = WDT_BASE_ADDRESS;
//--------------------------------
    if( WdrtBase ) {
        EFI_ACPI_WATCHDOG_RESOURCE_1_0_TABLE                        *AcpiTbl;
        //it must be only one instance of such protocol
        Status = gBS->LocateProtocol( &gEfiAcpiTableProtocolGuid, NULL, &At );
        if(EFI_ERROR(Status)) {
            DEBUG ((DEBUG_INFO|DEBUG_CHIPSET,\
                "WDRT LocateProtocol(ACPISupport)- %r Error\n", Status));
            return;
        }DEBUG ((DEBUG_INFO|DEBUG_CHIPSET,\
            "WDRT LocateProtocol(ACPISupport)- %r Success\n", Status));

        AcpiTbl=AllocateZeroPool(sizeof(EFI_ACPI_WATCHDOG_RESOURCE_1_0_TABLE));
        ASSERT(AcpiTbl);
        if(AcpiTbl) {
            //Fill Table header;
            AcpiTbl->Header.Signature=WDRT_SIG;
            AcpiTbl->Header.Length=sizeof(EFI_ACPI_WATCHDOG_RESOURCE_1_0_TABLE);
            AcpiTbl->Header.Revision=1;
            AcpiTbl->Header.Checksum=0;
            gBS->CopyMem((VOID*)AcpiTbl->Header.OemId, \
                CONVERT_TO_STRING(SB_WDRT_OEM_ID), \
                sizeof(AcpiTbl->Header.OemId) \
            );
            gBS->CopyMem((VOID*)AcpiTbl->Header.OemTableId, \
                CONVERT_TO_STRING(SB_WDRT_OEM_TBL_ID), \
                sizeof(AcpiTbl->Header.OemTableId) \
            );
            AcpiTbl->Header.OemRevision=ACPI_OEM_REV;
            AcpiTbl->Header.CreatorId=CREATOR_ID_AMI;//"AMI"
            AcpiTbl->Header.CreatorRevision=CORE_MAJOR_VERSION;

            //fill WDRT Fields
            //The GAS structure : Control Register
            AcpiTbl->ControlRegisterAddress.AddressSpaceId=GAS_SYS_MEM;
            AcpiTbl->ControlRegisterAddress.RegisterBitWidth=32;
            AcpiTbl->ControlRegisterAddress.RegisterBitOffset=0;
            AcpiTbl->ControlRegisterAddress.Reserved = 0x3;
            //Base address of WDRT Control Register
            AcpiTbl->ControlRegisterAddress.Address = WdrtBase;

            //The GAS structure : Count Register
            AcpiTbl->ControlRegisterAddress.AddressSpaceId=GAS_SYS_MEM;
            AcpiTbl->ControlRegisterAddress.RegisterBitWidth=32;
            AcpiTbl->ControlRegisterAddress.RegisterBitOffset=0;
            AcpiTbl->ControlRegisterAddress.Reserved = 0x3;
            //Base address of WDRT Count Register
            AcpiTbl->ControlRegisterAddress.Address=WdrtBase + 4;

            AcpiTbl->PCIDeviceID = 0xFFFF;            
            AcpiTbl->PCIVendorID = 0xFFFF;        
            AcpiTbl->PCIBusNumber = 0x00;       
            AcpiTbl->PCIDeviceNumber = 0x00;      
            AcpiTbl->PCIFunctionNumber = 0x00;
            AcpiTbl->PCISegment = 0x00;
            AcpiTbl->MaxCount = 0x03FF;
            AcpiTbl->Units = 0x00;

            //Add table
            Status = At->InstallAcpiTable( At, \
                                           AcpiTbl, \
                                           sizeof(EFI_ACPI_WATCHDOG_RESOURCE_1_0_TABLE), \
                                           &TableKey );
            DEBUG ((DEBUG_INFO|DEBUG_CHIPSET,"ACPISupport.SetAcpiTable() = %r \n", Status));
            ASSERT_EFI_ERROR(Status);

            //free memory used for table image
            gBS->FreePool(AcpiTbl);
        }
    }

    //Kill the Event
    gBS->CloseEvent(Event);
}
#endif

/**
    This function Enables or Disables the USB Port depending upon
    the Setup Questions.

    @param VOID

    @retval VOID

**/
VOID
EnableDisableUsbPort (VOID)
{
    UINT32  DieBusNum=0;
    UINT8                   dbPortNum=0;
    
    UINT32 Xhci0PortBit = 0;
    UINT32 Xhci1PortBit = 0;
    static BOOLEAN      AllPortDisable=FALSE;
    static BOOLEAN      DisablePortFunc=FALSE;
    
    if(DisablePortFunc) {
        return;
    }
    
    //XHCI0 Program
    for (dbPortNum = 0; dbPortNum < 4; dbPortNum++)
        Xhci0PortBit |= (gSbSetupData->Xhci0PortEn[dbPortNum] ? 0 : 1) << dbPortNum;
    //XHCI1 Program
    for (dbPortNum = 0; dbPortNum < 2; dbPortNum++)
        Xhci1PortBit |= (gSbSetupData->Xhci1PortEn[dbPortNum] ? 0 : 1) << dbPortNum;
    
#if defined OEM_USB_PER_PORT_DISABLE_SUPPORT && OEM_USB_PER_PORT_DISABLE_SUPPORT == 1  
    // If all the Ports are disabled, Disable the Port in the readytobootEvent Callback.
    if((Xhci0PortBit == 0xF) && (Xhci1PortBit == 0x3) && (AllPortDisable== FALSE)) {
        AllPortDisable=TRUE;
        return;
    }
#endif      
    
    DisablePortFunc = TRUE;
    
    if (Xhci0PortBit != 0) {
        //if ((Xhci0PortBit & BIT0)){
        //    Xhci0PortBit |= 0x0F ;//  Port0 (either USB3 or USB2) can only be disabled if all other ports (USB2 and USB3 port 1-3) are disabled.
        //}
        Xhci0PortBit |= Xhci0PortBit << 0x10;
        SbSmnRw (DieBusNum, 0x16D8012C, 0x00, Xhci0PortBit);
    }

    if (Xhci1PortBit != 0) {
        //if ((Xhci1PortBit & BIT0)){
        //    Xhci1PortBit |= 0x03 ;//  Port0 (either USB3 or USB2) can only be disabled if all other ports (USB2 and USB3 port) are disabled.
        //}
        Xhci1PortBit |= Xhci1PortBit << 0x10;
        
        SbSmnRw (DieBusNum, 0x16F8012C, 0x00, Xhci1PortBit);
    }    
}

/**
    This function Enables or Disables the USB Port depending upon
    the Setup Questions.(RV2 CPU)

    @param VOID

    @retval VOID

**/
VOID
RV2EnableDisableUsbPort (VOID)
{
    UINT32  DieBusNum=0;
    UINT8                   dbPortNum=0;
    static BOOLEAN      AllPortDisable1=FALSE;
    static BOOLEAN      DisablePortFunc1=FALSE;
    
    UINT32 Xhci0PortBit = 0;
    //UINT32 Xhci1PortBit = 0;
    
    if(DisablePortFunc1) {
        return;
    }
    
    //XHCI0 Program
    for (dbPortNum = 0; dbPortNum < 6; dbPortNum++)
        Xhci0PortBit |= (gSbSetupData->Xhci0PortEn[dbPortNum] ? 0 : 1) << dbPortNum;
    //XHCI1 Program
    //for (dbPortNum = 0; dbPortNum < 2; dbPortNum++)
    //    Xhci1PortBit |= (gSbSetupData->Xhci1PortEn[dbPortNum] ? 0 : 1) << dbPortNum;
    
#if defined OEM_USB_PER_PORT_DISABLE_SUPPORT && OEM_USB_PER_PORT_DISABLE_SUPPORT == 1  
    // If all the Ports are disabled, Disable the Port in the readytobootEvent Callback.
    if((Xhci0PortBit == 0x3F) && (AllPortDisable1== FALSE)) {
        AllPortDisable1=TRUE;
        return;
    }
#endif    
    
    DisablePortFunc1 = TRUE;
    
    if (Xhci0PortBit != 0) {
        //if ((Xhci0PortBit & BIT0)){
        //    Xhci0PortBit |= 0x0F ;//  Port0 (either USB3 or USB2) can only be disabled if all other ports (USB2 and USB3 port 1-3) are disabled.
        //}
        Xhci0PortBit |= Xhci0PortBit << 0x10;
        //SbSmnRw (DieBusNum, 0x16D8012C, 0x00, Xhci0PortBit);
        FchRVXhciSmuUsbConfigUpdate (0x16D80128, 0x000F003F, Xhci0PortBit, 0x01000001);
        FchRVXhciSmuService (SMC_MSG_UsbInit);
    }

    //if (Xhci1PortBit != 0) {
    //    //if ((Xhci1PortBit & BIT0)){
    //    //    Xhci1PortBit |= 0x03 ;//  Port0 (either USB3 or USB2) can only be disabled if all other ports (USB2 and USB3 port) are disabled.
    //    //}
    //    Xhci1PortBit |= Xhci1PortBit << 0x10;
    //    
    //    SbSmnRw (DieBusNum, 0x16F8012C, 0x00, Xhci1PortBit);
    //}    
}

/**
    This function Enables or Disables the Devices depending upon
    the Setup Questions.

    @param VOID

    @retval VOID

**/
VOID
EFIAPI
EnableDisableSBDevices (VOID)
{
//--------------------------------------------------------------------------
//            NO PORTING REQUIRED FOR THIS CHIPSET
//--------------------------------------------------------------------------
#if HPET_SUPPORT
    BOOLEAN                 HpetEn;

    HpetEn = gSbSetupData->HpetTimer ? TRUE : FALSE;
    if (HpetEn) {
        EFI_STATUS  Status = EFI_SUCCESS;
        EFI_EVENT   mAcpiEvent;
        VOID        *mAcpiReg;
        Status=RegisterProtocolCallback(
                                        &gEfiAcpiTableProtocolGuid,
                                        CreateHpetAcpiTable,
                                        NULL,
                                        &mAcpiEvent,
                                        &mAcpiReg);
        ASSERT_EFI_ERROR(Status);
        gBS->SignalEvent(mAcpiEvent);
    }
#endif

    if (gBootScriptSave == NULL) {
        EFI_STATUS  Status = EFI_SUCCESS;
        Status = gBS->LocateProtocol(&gEfiS3SaveStateProtocolGuid,NULL, \
             &gBootScriptSave);
        ASSERT_EFI_ERROR(Status);
    }
#if defined WDT_SUPPORT && WDT_SUPPORT == 1
    // Create ACPI table - WDRT
    {
        EFI_STATUS  Status = EFI_SUCCESS;
        EFI_EVENT   mWdrtAcpiEvent;
        VOID        *mWdrtAcpiReg;
        Status=RegisterProtocolCallback(
                                        &gEfiAcpiTableProtocolGuid,
                                        CreateWdrtAcpiTable,
                                        NULL,
                                        &mWdrtAcpiEvent,
                                        &mWdrtAcpiReg);
        ASSERT_EFI_ERROR(Status);
        gBS->SignalEvent(mWdrtAcpiEvent);
    }
#else
    // Disabled Watchdog timer memory decoding.
    RW_MEM8_S3 (gBootScriptSave,ACPI_MMIO_BASE + PMIO_BASE, 0, BIT7);
#endif

    if(mIsProcessorTypeFlavor1) {
        EnableDisableUsbPort();
    } else {
        RV2EnableDisableUsbPort();
    }
    
#if defined SET_I2C23_D0_UNINITIALIZED && SET_I2C23_D0_UNINITIALIZED == 1
    {
    	EFI_STATUS  Status = EFI_SUCCESS;
    	UINT32      PcdSata32 = PcdGet32(FchRTDeviceEnableMap);
    	
    	// MMIO of I2C under windows environment would be hidden when OS I2C driver installed.
    	// But related MMIO would still be hidden during POST after system "cold boot" or "S4", 
    	// that would cause I2C function can't work under BIOS setup.
    	// Set TargetedDeviceSatae of I2C as "D0 un-initialized" can fix this issue.
    	
    	DEBUG ((DEBUG_INFO,"[I2C] Check FchRTDeviceEnableMap status\n"));
    	
    	// When I2C2 enabled, set TargetedDeviceSatae of I2C 2 as D0 un-initialized
    	if (PcdSata32 & BIT7) {
    		RESET_MMIO8(0xFED81E4E, BIT0+BIT1); 
        	DEBUG ((DEBUG_INFO,"[I2C] AOAC status of I2C2 = 0x%x\n",READ_MEM8(0xFED81E4E)));
    	}
    	
    	// When I2C3 enabled, set TargetedDeviceSatae of I2C 3 as D0 un-initialized
    	if (PcdSata32 & BIT8) {
    		RESET_MMIO8(0xFED81E50, BIT0+BIT1); 
    		DEBUG ((DEBUG_INFO,"[I2C] AOAC status of I2C3 = 0x%x\n",READ_MEM8(0xFED81E50)));
    	}
    	
    }
#endif


}


//----------------------------------------------------------------------------
//   USUALLY NO PORTING REQUIRED FOR THE FOLLOWING ROUTINES
//----------------------------------------------------------------------------

#if defined SB_WATCHDOG_TIMER_PROTOCOL_SUPPORT && SB_WATCHDOG_TIMER_PROTOCOL_SUPPORT == 1
/**
    This function is called when the watchdog timer event is 
    signalled.  It calls the registered handler and then
    resets the system

    @param Event   - Watchdog event
    @param Context - Context pointer

    @retval VOID
**/
VOID EFIAPI WatchdogHandler (
    IN EFI_EVENT                  Event,
    IN VOID                       *Context
)
{
    //
    // Call the registered handler if there is one
    //
    if (mWatchdogNotifyFunction != NULL) {
        mWatchdogNotifyFunction (mWatchdogPeriod);
    }
    //
    // Reset the system
    //
    gRT->ResetSystem( EfiResetCold, EFI_TIMEOUT, 0, NULL );
}

/**
    This function registers a handler that is called when the Timer
    event has been signalled

    @param This - Pointer to the instance of the Architectural Protocol
    @param NotifyFunction - The function to call when the interrupt fires

    @retval EFI_STATUS
            EFI_SUCCESS   When new handle is registered
            EFI_ALREADY_STARTEd If notify function is already defined

**/
EFI_STATUS EFIAPI RegisterHandler (
    IN EFI_WATCHDOG_TIMER_ARCH_PROTOCOL *This,
    IN EFI_WATCHDOG_TIMER_NOTIFY        NotifyFunction
)
{
    //
    // only register the handler if it is still NULL
    //
    if (NotifyFunction && mWatchdogNotifyFunction) return EFI_ALREADY_STARTED;
    if (!NotifyFunction && !mWatchdogNotifyFunction) return EFI_INVALID_PARAMETER;

    mWatchdogNotifyFunction = NotifyFunction;

    return EFI_SUCCESS;
}

/**
    This function sets the timer period before the watchdog goes off
    every TimerPeriod number of 100ns intervals, if the period is set to 0 the
    timer event is cancelled

    @param This - Pointer to the instance of the Architectural Protocol
    @param TimerPeriod - The number of 100ns intervals to which the watchdog
                         will be programmed.

    @retval EFI_SUCCESS

**/
EFI_STATUS EFIAPI WatchdogSetTimerPeriod (
    IN EFI_WATCHDOG_TIMER_ARCH_PROTOCOL *This,
    IN UINT64                           TimerPeriod
)
{
    EFI_TIMER_DELAY  TimerDelayType;

    //
    // store new timer length
    //
    mWatchdogPeriod = TimerPeriod;
    //
    // cancel timer event if Timer Period is 0
    //
    TimerDelayType = (TimerPeriod) ? TimerRelative : TimerCancel;
    //
    // set the timer for the event
    //
    return gBS->SetTimer(mWatchdogEvent, TimerDelayType, mWatchdogPeriod);
}


/**
    This function returns the current watchdog timer period

    @param This - Pointer to the instance of the Architectural Protocol
    @param TimerPeriod - Pointer to a memory location to load the current 
                         Timer period into

    @retval TimerPeriod Current Timer Period if function returns EFI_SUCCESS

**/
EFI_STATUS EFIAPI WatchdogGetTimerPeriod(
    IN EFI_WATCHDOG_TIMER_ARCH_PROTOCOL *This,
    IN UINT64                           *TimerPeriod
)
{
    //
    // return the current Watchdog period
    //
    *TimerPeriod = mWatchdogPeriod;

    return EFI_SUCCESS;
}


/**
    This function installs the the Watchdog Timer protocol on its
    handle, and initializes the Watchdog timer.

    @param ImageHandle - ImageHandle of the loaded driver
    @param SystemTable - Pointer to the System Table

    @retval EFI_SUCCESS The Watchdog Timer protocol was
                        installed.
    @retval EFI_OUT_OF_RESOURCES Space for a new handle could not
                                 be allocated.
    @retval EFI_INVALID_PARAMETER One of the parameters has an 
                                  invalid value.
**/
EFI_STATUS WatchdogInit (
    IN EFI_HANDLE                 ImageHandle,
    IN EFI_SYSTEM_TABLE           *SystemTable
)
{
    EFI_STATUS  Status;
    EFI_HANDLE  WatchdogHandle = NULL;

    //
    // Use the Timer event to trigger the Watchdog.  No specific hardware
    // exists for this
    //
    Status = gBS->CreateEvent (
                    EVT_TIMER | EVT_NOTIFY_SIGNAL,
                    TPL_NOTIFY,
                    WatchdogHandler,
                    NULL,
                    &mWatchdogEvent
                    );
    //
    // Create a handle for the ArchProtocol and install Watchdog Arch
    // Protocol on the handle
    //
    Status = gBS->InstallProtocolInterface (
                    &WatchdogHandle,
                    &gEfiWatchdogTimerArchProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    &mWatchdog
                    );

    return Status;
}
#endif


#if defined SB_TIMER_ARCH_PROTOCOL_SUPPORT && SB_TIMER_ARCH_PROTOCOL_SUPPORT == 1
/**
    This function registers a handler that is called every time the
    timer interrupt fires

    @param This - Pointer to the instance of the 
                  Architectural Protocol
    @param NotifyFunction - The function to call when the interrupt fires

    @retval EFI_SUCCESS new handle registered
    @retval EFI_ALREADY_STARTED if Notify function is already defined

**/
EFI_STATUS TimerRegisterHandler(
    IN  EFI_TIMER_ARCH_PROTOCOL *This,
    IN  EFI_TIMER_NOTIFY        NotifyFunction
)
{
    // check to see if the handler has already been installed
  if (NotifyFunction != NULL && mNotifyFunction != NULL) {
    return EFI_ALREADY_STARTED;
  }

    // if not install it
    mNotifyFunction = NotifyFunction;
    return EFI_SUCCESS;
}

/**
    This function sets the timer to create an Interrupt on IRQ0
    every TimerPeriod number of 100ns intervals

    @param This - Pointer to the instance of the Architectural Protocol
    @param TimerPeriod - The number of 100ns intervals to which the timer
                         will be programmed. This value will be rounded up 
                         to the nearest timer interval

    @retval EFI_SUCCESS

**/
EFI_STATUS SetTimerPeriod (
    IN EFI_TIMER_ARCH_PROTOCOL      *This,
    IN UINT64                       TimerPeriod
)
{

    UINT32					NumberOfTicks;
    UINT8                   Value8;

    // If timer period is 0 then disable the Timer interrupt
	if (TimerPeriod == 0) {
        mLegacy8259->DisableIrq(mLegacy8259,SYSTEM_TIMER_IRQ);
        //DisableIrq(SYSTEM_TIMER_IRQ);

	} else {
        if (TimerPeriod>MAX_TICK_DURATION) TimerPeriod=MAX_TICK_DURATION;

        // since TimerPeriod in 100ns units and TIMER_TICK in ns
        // we have to multiple TimerPeriod by 100
        // To round up result:

        NumberOfTicks = ((UINT32)TimerPeriod * 100 + TIMER_TICK / 2)
                                                                / TIMER_TICK;
        //write to port 0x43 to setup the timer
        IoWrite8 ( TIMER_CTRL, 0x36 );
        // write to port 0x40 to set the time
        IoWrite8 ( TIMER_0_COUNT, (UINT8)NumberOfTicks);
        IoWrite8 ( TIMER_0_COUNT, *(((UINT8*)&NumberOfTicks)+1) );
        Value8 = 0x36;
        //### Template ###BOOT_SCRIPT_S3_IO_WRITE_MACRO(gBootScript, EfiBootScriptWidthUint8, TIMER_CTRL, 1, &Value8);
        //### Template ###Value8 = (UINT8)NumberOfTicks;
        //### Template ###BOOT_SCRIPT_S3_IO_WRITE_MACRO(gBootScript, EfiBootScriptWidthUint8, TIMER_0_COUNT, 1, &Value8);
        //### Template ###Value8 = *(((UINT8*)&NumberOfTicks)+1);
        //### Template ###BOOT_SCRIPT_S3_IO_WRITE_MACRO(gBootScript, EfiBootScriptWidthUint8, TIMER_0_COUNT, 1, &Value8);
        // Now enable the interrupt
        //EnableIrq(SYSTEM_TIMER_IRQ);
        mLegacy8259->EnableIrq(mLegacy8259,SYSTEM_TIMER_IRQ,FALSE);

    }

    mProgrammedTimerValue = TimerPeriod;

    return EFI_SUCCESS;
}

/**
    This function returns the current timer period

    @param This - Pointer to the instance of the Architectural Protocol
    @param TimerPeriod - pointer to a memory location to load the current
                         Timer period into

    @retval EFI_STATUS

**/
EFI_STATUS GetTimerPeriod(
    IN      EFI_TIMER_ARCH_PROTOCOL *This,
    IN OUT  UINT64                  *TimerPeriod
)
{
    *TimerPeriod = mProgrammedTimerValue;

    return EFI_SUCCESS;
}

/**
    This function generates a soft timer interrupt

    @param This - Pointer to the instance of the Architectural Protocol

    @retval EFI_UNSUPPORTED

**/
EFI_STATUS GenerateSoftIntr(
    IN EFI_TIMER_ARCH_PROTOCOL      *This
)
{
    return EFI_UNSUPPORTED;
}

/**
    This function is called when the Timer reaches 0.  It raises
    the TPL and then calls the registered notify function

    @param InterruptType Interrupt type
    @param SystemContext System context

    @retval VOID

**/
VOID TimerInterruptHandler (
    IN EFI_EXCEPTION_TYPE   InterruptType,
    IN EFI_SYSTEM_CONTEXT   SystemContext
)
{
    EFI_TPL                 OldTpl;
    EFI_TPL                 CurrentTpl;

    SaveRestoreRegisters(TRUE);

    OldTpl = gBS->RaiseTPL (TPL_HIGH_LEVEL);

    // clear the interrupt flag
    //SendEoi(SYSTEM_TIMER_IRQ);
    mLegacy8259->EndOfInterrupt(mLegacy8259,SYSTEM_TIMER_IRQ);

    // This checks for the existence of a registered notify function and if it exists
    //  it calls the function with the current programmed Timer Period
    if (mNotifyFunction)
    {
        mNotifyFunction (mProgrammedTimerValue);
    }

    gBS->RestoreTPL (OldTpl);

    //
    // The user's EVT_TIMER is not within TimerInterruptHandler.
    // If CurrentTpl is greater than TPL_NOTIFY, the user's EVT_TIMER will haven't
    // been executed yet.
    // Signal gRegisterRestoreEvent to restore the register in RegisterRestoreCallBack()
    // after user's event.
    //
    CurrentTpl = EfiGetCurrentTpl();
    if (CurrentTpl > TPL_NOTIFY) {
      gBS->SignalEvent (gRegisterRestoreEvent);
    } else {
      SaveRestoreRegisters(FALSE);
    }   
}

/**
    Calls TimerInit when the Legacy8259 Protocol
    becomes available. 

    @param Event   - Event of callback
    @param Context - Context of callback.
    
    @retval VOID

**/    
VOID TimerInitWrapper(
    IN EFI_EVENT                Event,
    IN VOID                     *Context
)
{
    EFI_STATUS    Status;

    Status = gBS->LocateProtocol (&gEfiLegacy8259ProtocolGuid, NULL, &mLegacy8259);
    if(EFI_ERROR(Status)) return;

    TimerInit();

    //Kill the Event
    gBS->CloseEvent(Event);
}

/**
    This function installs the the timer protocol on its handle,
    and initializes the timer.

    @param ImageHandle ImageHandle of the loaded driver
    @param SystemTable Pointer to the System Table

    @retval EFI_STATUS

**/
EFI_STATUS TimerInit (
    VOID
)
{
    EFI_STATUS  Status;
    EFI_CPU_ARCH_PROTOCOL           *CpuArch;
    UINT8 Value;
    //TimerVector must be initialized to 0, since GetVector only modifies the lowest byte,
    //and RegisterInterruptHandler requires TimerVector to be 4 bytes.
    UINT32      TimerVector = 0;
    UINT32                  Irq0TimerVector = 0;


    // Disable timer, make sure no interrupt will be created
    Status = SetTimerPeriod (&mTimerProtocol, 0);
    ASSERT_EFI_ERROR(Status);

    // Find the CPU Arch Protocol
    Status = gBS->LocateProtocol (&gEfiCpuArchProtocolGuid, NULL, &CpuArch);
    ASSERT_EFI_ERROR(Status);

    Status = mLegacy8259->GetVector ( mLegacy8259,
                                      Efi8259Irq0,
                                      (UINT8 *)&TimerVector );
    ASSERT_EFI_ERROR(Status);

    Status = CpuArch->RegisterInterruptHandler ( CpuArch,
                                                 TimerVector,
                                                 TimerInterruptHandler );
    ASSERT_EFI_ERROR(Status);
    // Initialize the handle pointer
    mNotifyFunction = NULL;

    // Force the timer to be enabled at its default period
    Status = SetTimerPeriod (&mTimerProtocol, MAX_TICK_DURATION);
    ASSERT_EFI_ERROR (Status);

    //Program Timer1 to pass certain customer's test
    IoWrite8( TIMER_CTRL, 0x54 );
    IoWrite8( TIMER_1_COUNT, 0x12 );
    //add boot script programming
    Value = 0x54;
    //### Template ###BOOT_SCRIPT_S3_IO_WRITE_MACRO(gBootScript, EfiBootScriptWidthUint8, TIMER_CTRL, 1, &Value);
    //### Template ###Value = 0x12;
    //### Template ###BOOT_SCRIPT_S3_IO_WRITE_MACRO(gBootScript, EfiBootScriptWidthUint8, TIMER_1_COUNT, 1, &Value);


  // Install the Timer Architectural Protocol onto a new handle
    Status = gBS->InstallProtocolInterface (
                    &mTimerProtocolHandle,
                    &gEfiTimerArchProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    &mTimerProtocol
                    );
    ASSERT_EFI_ERROR(Status);

  return Status;
}
#else
/**
    This function installs the the timer protocol on its handle,
    and initializes the timer.

    @param ImageHandle ImageHandle of the loaded driver
    @param SystemTable Pointer to the System Table

    @retval EFI_STATUS

**/
EFI_STATUS TimerInit (
    VOID
)
{
    //### Template ###   UINT8   Value;

    // Init default for Timer 1
    IoWrite8( TIMER_CTRL, 0x36 );
    IoWrite8( TIMER_0_COUNT, 0 );
    IoWrite8( TIMER_0_COUNT, 0 );
    // Add boot script programming
    //### Template ###     Value = 0x36;
    //### Template ###  BOOT_SCRIPT_S3_IO_WRITE_MACRO(gBootScript, EfiBootScriptWidthUint8, TIMER_CTRL, 1, &Value);
    //### Template ### Value = 0x0;
    //### Template ### BOOT_SCRIPT_S3_IO_WRITE_MACRO(gBootScript, EfiBootScriptWidthUint8, TIMER_0_COUNT, 1, &Value);
    //### Template ### BOOT_SCRIPT_S3_IO_WRITE_MACRO(gBootScript, EfiBootScriptWidthUint8, TIMER_0_COUNT, 1, &Value);
    //Program Timer1 to pass certain customer's test
    IoWrite8( TIMER_CTRL, 0x54 );
    IoWrite8( TIMER_1_COUNT, 0x12 );
    //add boot script programming
//### Template ###    Value = 0x54;
    //### Template ###BOOT_SCRIPT_S3_IO_WRITE_MACRO(gBootScript, EfiBootScriptWidthUint8, TIMER_CTRL, 1, &Value);
    //### Template ###Value = 0x12;
    //### Template ###BOOT_SCRIPT_S3_IO_WRITE_MACRO(gBootScript, EfiBootScriptWidthUint8, TIMER_1_COUNT, 1, &Value);

    return EFI_SUCCESS;
}
#endif

//###  RVA9 : The following part sync chipset template (AmiChipsetModulePkg_08) EIP310737
//###			but move to Sb8259InitLib
#if defined SB_8259_PROTOCOL_SUPPORT && SB_8259_PROTOCOL_SUPPORT == 1 && (SB_8259_PROTOCOL_LIB_SUPPORT == 0)
/**
    Program the IRQ Mask and Trigger.

    @param VOID

    @retval VOID

    @note  Here is the control flow of this function:
     1. Program Master IRQ Mask.
     2. Program Slave IRQ Mask.
     3. Program Trigger Level.

**/
VOID ProgramIrqMaskTrigger (
    VOID
)
{
    IoWrite8(0x21, (UINT8)gIrqMask[gMode]);
    IoWrite8(0xa1, (UINT8)(gIrqMask[gMode] >> 8));
    //
    // 4d0 can not be accessed as by IoWrite16, we have to split
    //
    IoWrite8(0x4d0, (UINT8)gIrqTrigger[gMode]);
    IoWrite8(0x4d1, (UINT8)(gIrqTrigger[gMode] >> 8));
}

/**
    Initializes the interrupt controller and program the IRQ
    Master and Slave Vector Base.

    @param This - Pointer to this object
    @param MasterBase - IRQ base for the master 8259 controller
    @param SlaveBase - IRQ base for the slave 8259 controller

    @retval EFI_SUCCESS Interrupt on the interrupt controllers was enabled.

    @note  Here is the control flow of this function:
           1. If Master base is changed, initialize master 8259 setting
              the interrupt offset.
           2. If Slave base is changed, initialize slave 8259 setting
              the interrupt offset.
           3. Return EFI_SUCCESS.
**/
EFI_STATUS SetVectorBase (
    IN EFI_LEGACY_8259_PROTOCOL   *This,
    IN UINT8                      MasterBase,
    IN UINT8                      SlaveBase
)
{
    //
    // 8259 Master
    //
    if (MasterBase != gMasterBase)
    {
        //
        // Start 8259 Master Initialization.
        //
        IoWrite8(LEGACY_8259_CONTROL_REGISTER_MASTER, ICW1);
        //
        // Set Interrupt Offset
        //
        IoWrite8(LEGACY_8259_MASK_REGISTER_MASTER, MasterBase);
        //
        // Set Slave IRQ.
        //
        IoWrite8(LEGACY_8259_MASK_REGISTER_MASTER, ICW3_M);
        //
        // Set 8259 mode. See ICW4 comments with #define.
        //
        IoWrite8(LEGACY_8259_MASK_REGISTER_MASTER, ICW4);
        gMasterBase = MasterBase;
    }
    //
    // 8259 Slave
    //
    if (SlaveBase != gSlaveBase)
    {
        //
        // Start 8259 Slave  Initialization.
        //
        IoWrite8(LEGACY_8259_CONTROL_REGISTER_SLAVE, ICW1);
        //
        // Set Interrupt Offset
        //
        IoWrite8(LEGACY_8259_MASK_REGISTER_SLAVE, SlaveBase);
        //
        // Set Slave IRQ.
        //
        IoWrite8(LEGACY_8259_MASK_REGISTER_SLAVE, ICW3_S);
        //
        // Set 8259 mode. See ICW4 comments with #define.
        //
        IoWrite8(LEGACY_8259_MASK_REGISTER_SLAVE, ICW4);
        gSlaveBase = SlaveBase;
    }

    return EFI_SUCCESS;
}

/**
    Get the Master/Slave IRQ Mask, IRQ Level for Legacy real
    mode and protected mode.

    @param This - Pointer to this object
    @param LegacyMask - Legacy mode interrupt mask
    @param LegacyEdgeLevel - Legacy mode edge/level trigger value
    @param ProtectedMask - Protected mode interrupt mask
    @param ProtectedEdgeLevel - Protected mode edge/level trigger value

    @retval EFI_SUCCESS Returned iRQ mask/level.

    @note  Here is the control flow of this function:
           1. If *LegacyMask not NULL, get legacy Mask.
           2. If *LegacyEdgeLevel not NULL, get legacy Trigger Level.
           3. If *ProtectedMask not NULL, get protected Mask.
           4. If *ProtectedEdgeLevel not NULL, get protected trigger level.
           5. Return EFI_SUCCESS.

**/
EFI_STATUS GetMask (
    IN EFI_LEGACY_8259_PROTOCOL   *This,
    OUT UINT16                    *LegacyMask   OPTIONAL,
    OUT UINT16                    *LegacyEdgeLevel OPTIONAL,
    OUT UINT16                    *ProtectedMask  OPTIONAL,
    OUT UINT16                    *ProtectedEdgeLevel OPTIONAL
)
{
    if (LegacyMask)   *LegacyMask   = gIrqMask[0];
    if (LegacyEdgeLevel) *LegacyEdgeLevel = gIrqTrigger[0];
    if (ProtectedMask)  *ProtectedMask  = gIrqMask[1];
    if (ProtectedEdgeLevel) *ProtectedEdgeLevel = gIrqTrigger[1];

    return EFI_SUCCESS;
}

/**
    Set the Master/Slave IRQ Mask, IRQ Level for Legacy real mode
    and protected mode.

    @param This - Pointer to this object
    @param LegacyMask - Legacy mode interrupt mask
    @param LegacyEdgeLevel - Legacy mode edge/level trigger value
    @param ProtectedMask - Protected mode interrupt mask
    @param ProtectedEdgeLevel - Protected mode edge/level trigger value

    @retval EFI_SUCCESS Set IRQ mask/level.

    @note  Here is the control flow of this function:
           1. If *LegacyMask not NULL, set legacy mask variable.
           2. If *LegacyEdgeLevel not NULL, set legacy Trigger Level variable.
           3. If *ProtectedMask not NULL, set protected mask variable.
           4. If *ProtectedEdgeLevel not NULL, set protected trigger level variable.
           5. Call function to program 8259 with mask/trigger of current mode.
           6. Return EFI_SUCCESS.

**/
EFI_STATUS SetMask (
    IN EFI_LEGACY_8259_PROTOCOL   *This,
    IN UINT16                     *LegacyMask   OPTIONAL,
    IN UINT16                     *LegacyEdgeLevel OPTIONAL,
    IN UINT16                     *ProtectedMask  OPTIONAL,
    IN UINT16                     *ProtectedEdgeLevel OPTIONAL
)
{
    if (LegacyMask)   gIrqMask[0]  = *LegacyMask;
    if (LegacyEdgeLevel) gIrqTrigger[0] = *LegacyEdgeLevel;
    if (ProtectedMask)  gIrqMask[1]  = *ProtectedMask;
    if (ProtectedEdgeLevel) gIrqTrigger[1] = *ProtectedEdgeLevel;

    ProgramIrqMaskTrigger();

    return EFI_SUCCESS;
}

/**
    Sets the interrupt mode operation to legacy or protected.
    New mask and edge/level status can be provided as input

    @param This - Pointer to this object
    @param Mode - Interrupt mode setting
    @param Mask - New interrupt mask for this mode
    @param EdgeLevel - New edge/level trigger value for this mode

    @retval EFI_SUCCESS Set mode was successful

    @note  Here is the control flow of this function:
           1. If invalid mode, return EFI_INVALID_PARAMETER.
           2. If *Mask not NULL, set mode mask variable.
           3. If *EdgeLevel not NULL, set mode trigger level variable.
           4. Call function to program 8259 with mask/trigger of current mode.
           5. Return EFI_SUCCESS.

**/
EFI_STATUS SetMode (
    IN EFI_LEGACY_8259_PROTOCOL   *This,
    IN EFI_8259_MODE              Mode,
    IN UINT16                     *Mask   OPTIONAL,
    IN UINT16                     *EdgeLevel OPTIONAL
)
{
    if (Mode >= Efi8259MaxMode) return EFI_INVALID_PARAMETER;

    gMode = Mode;
    if (Mask) gIrqMask[Mode] = *Mask;
    if (EdgeLevel) gIrqTrigger[Mode] = *EdgeLevel;

    ProgramIrqMaskTrigger();

    return EFI_SUCCESS;
}

/**
    Returns the vector number for the requested IRQ

    @param This - Legacy8259 protocol object
    @param Irq - IRQ number for which vector is needed
    @param Vector - Vector value is returned in this pointer

    @retval EFI_SUCCESS Get IRQ Vector for IRQ.

    @note  Here is the control flow of this function:
           1. If invalid IRQ, return EFI_INVALID_PARAMETER.
           2. If Set *Vector to IRQ base + interrupt offset.
           3. Return EFI_SUCCESS.

**/
EFI_STATUS GetVector (
    IN EFI_LEGACY_8259_PROTOCOL   *This,
    IN EFI_8259_IRQ               Irq,
    OUT UINT8                     *Vector
)
{
    if ((UINT8)Irq >= (UINT8)Efi8259IrqMax) return EFI_INVALID_PARAMETER;
    *Vector = (Irq <= Efi8259Irq7) ? gMasterBase + Irq : gSlaveBase + Irq - 8;

    return EFI_SUCCESS;
}

/**
    Enable the Interrupt controllers to respond in a specific IRQ.

    @param This - Legacy8259 protocol object
    @param Irq - IRQ that has to be enabled
    @param LevelTriggered - Trigger mechanism (level or edge) for this IRQ

    @retval EFI_SUCCESS Interrupt on the interrupt controllers was enabled.
    @retval EFI_INVALID_PARAMETER Interrupt not existent. The 8259
                                  master/slave supports IRQ 0-15.

    @note  Here is the control flow of this function:
           1. Check if IRQ is valid. If not, return EFI_INVALID_PARAMETER.
           2. Clear interrupt mask bit in variable of current mode.
           3. Set/Clear bit of trigger level variable of current mode.
           4. Program mask/trigger.
           5. Return EFI_SUCCESS.

**/
EFI_STATUS EnableIrq (
    IN EFI_LEGACY_8259_PROTOCOL   *This,
    IN EFI_8259_IRQ               Irq,
    IN BOOLEAN                    LevelTriggered
)
{
    if ((UINT8)Irq > (UINT8)15) return EFI_INVALID_PARAMETER;
    //
    // Clear mask for the IRQ.
    //
    gIrqMask[gMode] &= ~(1 << Irq);
    //
    // Mask IRQ to change.
    //
    gIrqTrigger[gMode] &= ~(1 << Irq);
    //
    // Change IRQ bit, 0 = edge, 1 = level.
    //
    if (LevelTriggered) gIrqTrigger[gMode] |= (1 << Irq);

    ProgramIrqMaskTrigger();
    return EFI_SUCCESS;
}


/**
    Disable the Interrupt controllers to stop responding to
    a specific IRQ.

    @param This - Legacy8259 protocol object
    @param Irq - IRQ that has to be disabled

    @retval EFI_SUCCESS Interrupt on the interrupt controllers was enabled.
    @retval EFI_INVALID_PARAMETER Interrupt not existent. The 8259
                                  master/slave supports IRQ 0-15.

    @note  Here is the control flow of this function:
           1. Check if IRQ is valid. If not, return EFI_INVALID_PARAMETER.
           2. Set interrupt mask bit in variable of current mode.
           3. Program mask/trigger.
           4. Return EFI_SUCCESS.

**/
EFI_STATUS DisableIrq (
    IN EFI_LEGACY_8259_PROTOCOL   *This,
    IN EFI_8259_IRQ               Irq
)
{
    if ((UINT8)Irq > (UINT8)15) return EFI_INVALID_PARAMETER;
    //
    // Set mask for the Irq.
    //
    gIrqMask[gMode] |= 1 << Irq;

    ProgramIrqMaskTrigger();
    return EFI_SUCCESS;
}

/**
    Get IRQ vector assigned to PCI card.

    @param This - Pointer to this object
    @param PciHandle - PCI handle for this device
    @param Vector - Interrupt vector this device

    @retval EFI_SUCCESS Vector returned.
    @retval EFI_INVALID_PARAMETER Invalid PciHandle.

    @note  Here is the control flow of this function:
           1. Get Handle of PciIo installed on PciHandle.
           2. If PciIo not installed, return EFI_INVALID_DEVICE.
           3. Set *vector to IRQ vector programmed into card.
           4. Return EFI_SUCCESS.

**/
EFI_STATUS GetInterruptLine (
    IN EFI_LEGACY_8259_PROTOCOL   *This,
    IN EFI_HANDLE                 PciHandle,
    OUT UINT8                     *Vector
)
{
    EFI_STATUS    Status;
    EFI_PCI_IO_PROTOCOL  *PciIo;
    UINT8     InterruptLine;

    Status = gBS->HandleProtocol(
                    PciHandle,
                    &gEfiPciIoProtocolGuid,
                    &PciIo
                    );
    if (EFI_ERROR(Status)) return EFI_INVALID_PARAMETER;
    //
    // Read vector from card.
    //
    PciIo->Pci.Read(
            PciIo,
            EfiPciIoWidthUint8,
            PCI_INTLINE,
            1,
            &InterruptLine
            );

    *Vector = InterruptLine;

    return EFI_SUCCESS;
}

/**
    Send end of interrupt command to interrupt controller(s).

    @param This - Pointer to this object
    @param Irq - IRQ number for this EOI has to be sent

    @retval EFI_SUCCESS EOI command sent to controller(s)
    @retval EFI_INVALID_PARAMETER Interrupt not existent. The 8259
                                  master/slave supports IRQ 0-15.

    @note  Here is the control flow of this function:
           1. Check if IRQ is valid. If not, return EFI_INVALID_PARAMETER.
           2. If IRQ >= 8, then Send EOI to slave controller.
           3. Send EOI to master controller. (This is for both master/slave IRQs)
           4. Return EFI_SUCCESS.

**/
EFI_STATUS EndOfInterrupt (
    IN EFI_LEGACY_8259_PROTOCOL   *This,
    IN EFI_8259_IRQ               Irq
)
{
    if (Irq > 15) return EFI_INVALID_PARAMETER;
    //
    // If Slave, send EOI to slave first.
    //
    if (Irq >= 8)
    {
        //
        // Send Slave EOI
        //
        IoWrite8(LEGACY_8259_CONTROL_REGISTER_SLAVE, EOI_COMMAND);
    }
    //
    // Send Master EOI
    //
    IoWrite8(LEGACY_8259_CONTROL_REGISTER_MASTER, EOI_COMMAND);

    return EFI_SUCCESS;
}

EFI_LEGACY_8259_PROTOCOL gLegacy8259Protocol =
{
    SetVectorBase,
    GetMask,
    SetMask,
    SetMode,
    GetVector,
    EnableIrq,
    DisableIrq,
    GetInterruptLine,
    EndOfInterrupt
};

/**
    Program the IRQ Mask and Trigger.

    @param ImageHandle  Image handle for this driver
    @param SystemTable  Pointer to the system table

    @retval EFI_STATUS

    @note  Here is the control flow of this function:
           1. Initialize AMI Library.
           2. Install Legacy 8259 Interface. If error, return error.
           3. Initialize the CPU setting vector bases.
           4. Set CPU Mode, mask, and trigger level.
           5. Return EFI_SUCCESS.

**/
EFI_STATUS Initialize8259 (
    IN EFI_HANDLE                 ImageHandle,
    IN EFI_SYSTEM_TABLE           *SystemTable
)
{
    EFI_STATUS    Status;
    UINT16        Mask  = 0xffff;     //Mask all interrupts.
    UINT16        EdgeLevel = 0x00;   //Set all edge.

    SetVectorBase (0, MASTER_INTERRUPT_BASE, SLAVE_INTERRUPT_BASE);
    SetMode (0, Efi8259ProtectedMode, &Mask, &EdgeLevel);

    Status = gBS->InstallMultipleProtocolInterfaces(
                    &ImageHandle,
                    &gEfiLegacy8259ProtocolGuid,
                    &gLegacy8259Protocol,
                    NULL
                    );

    return Status;
}
#endif

/**
    This Function Installs the SB HDD Policy Protocol      

    @param VOID
           
    @retval EFI_SUCCESS      

**/
EFI_STATUS
InstallSbPolicyProtocol()
{
    EFI_HANDLE  Handle=NULL;
    EFI_STATUS  Status;

    Status = gBS->InstallMultipleProtocolInterfaces (
                  &Handle,
                  &gAmiSbHddPolicyProtocolGuid,
                  &mSbHddPolicy,
                  NULL
                  );

    return Status;

}

/**
    This function returns the Port Number to which the Hard Disk
    is connected.

    @param ControllerNumber
    @param PrimarySecondary
    @param MasterSlave
    @param PortNumber

    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS
GeneratePortNumber(
    IN    UINT8    DeviceNumber,
    IN    UINT8    FunctionNumber,
    IN    UINT32   IdeChannel,
    IN    UINT32   IdeDevice,
    OUT   UINT32   *PortNumber
)
{
    UINT8                  CONST SataClass = PcdGet8(PcdSataClass);
    BOOLEAN                CONST SataSata6AhciCap = PcdGetBool(PcdSataSata6AhciCap);

    // Is Pata or Sata controller ?
    if (DeviceNumber == FCH_IDE_DEV) {
        if (SataSata6AhciCap == 0) {
            // SATA as primary
            *PortNumber = PATA_PORT_NUM[IdeChannel][IdeDevice];
        }else{
            // SATA as secondary
            *PortNumber = PATA_PORT_NUM[IdeChannel ^ 1][IdeDevice];
        }
    } else  {
        if (SataClass == 1 || SataClass == 2 || SataClass == 5) {
            // RAID / AHCI / AHCI as 7804
            *PortNumber = IdeChannel;
        } else {
            // others
            *PortNumber = SATA_PORT_NUM[IdeChannel][IdeDevice];
        }
    }

    return  EFI_SUCCESS;
}

#if defined SB_TIMER_ARCH_PROTOCOL_SUPPORT && SB_TIMER_ARCH_PROTOCOL_SUPPORT == 1
/**
    Restore registers value saved in timer interrupt routine.
    
    @param  Event    The instance of EFI_EVENT.
    @param  Context  The parameter passed in.
**/
VOID
EFIAPI
RegisterRestoreCallBack (
    IN  EFI_EVENT  Event,
    IN  VOID       *Context
    )
{
    SaveRestoreRegisters(FALSE);
}
#endif

