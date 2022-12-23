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

//**********************************************************************
/** @file SbPeiDebugger.c
    This file contains PEI stage board component code for
    Template SB

**/
//**********************************************************************

#include "Uefi.h"
#include "Pei.h"
#include "Token.h"
#include <AmiPeiLib.h>
#include "Sb.h"
#include "AmiCspLib.h"
#include "AmiDebugPort.h"

#include <Library/AmiChipsetIoLib.h>

#include <Library/PciLib.h>
#include <Library/DebugLib.h>
//####include <Debugger/Include/Library/XhciPei.h> 	// MdePkg\Include\IndustryStandard/Pci22.h(577) : error C2371: 'PCI_CONFIG_ACCESS_CF8' : redefinition; different basic types
//###												// The "Debugger\Include\Library\XhciPei.h" conflict with #include "AmiDebugPort.h"
typedef struct {
    UINT8 Bus;
    UINT8 Device;
    UINT8 Function;
} PCI_BUS_DEV_FUNCTION;

//
// 8259 Hardware definitions
//
#define LEGACY_MODE_BASE_VECTOR_MASTER                    0x08
#define LEGACY_MODE_BASE_VECTOR_SLAVE                     0x10
#define LEGACY_8259_CONTROL_REGISTER_MASTER               0x20
#define LEGACY_8259_MASK_REGISTER_MASTER                  0x21
#define LEGACY_8259_CONTROL_REGISTER_SLAVE                0xA0
#define LEGACY_8259_MASK_REGISTER_SLAVE                   0xA1
#define LEGACY_8259_EDGE_LEVEL_TRIGGERED_REGISTER_MASTER  0x4D0
#define LEGACY_8259_EDGE_LEVEL_TRIGGERED_REGISTER_SLAVE   0x4D1
#define LEGACY_8259_EOI                                   0x20

#define TIMER_CONTROL_PORT          0x43
#define TIMER0_COUNT_PORT           0x40

#define PM_STATUS_CTRL          0x8000
#define PWR_MGT_CAP_ID      1
#define PME_STATUS          0x8000
#define DBG_PRT_CAP_ID      0xA

#if defined(USB_DEBUG_TRANSPORT) && (USB_DEBUG_TRANSPORT == 1)
#if !defined(PCI_EHCI_DEV_FUNC_NUMBER) || !(PCI_EHCI_DEV_FUNC_NUMBER == 0x90 \
        || PCI_EHCI_DEV_FUNC_NUMBER == 0x98 || PCI_EHCI_DEV_FUNC_NUMBER == 0xB0)
    #error portting required for different board layout (EHCI0==0x90,EHCI1==0x98,EHCI2==0xB0)
#endif
#endif

#if USB_3_DEBUG_SUPPORT == 1
EFI_STATUS SbPeiDbgInitXhci (
    IN OUT PEI_DBG_PORT_INFO    *DebugPort
);
#endif
// Function Prototypes
UINT8   ReadPCIRegByte(IN UINT8 RegNum,IN UINT8 BusNum,IN UINT8 DevFunc);
UINT16  ReadPCIRegWord(IN UINT8 RegNum,IN UINT8 BusNum,IN UINT8 DevFunc);
UINT32  ReadPCIRegDWord(IN UINT8 RegNum,IN UINT8 BusNum,IN UINT8 DevFunc);
VOID    WritePCIRegByte(IN UINT8 RegNum,IN UINT8 BusNum,IN UINT8 DevFunc,IN UINT8 val);
VOID    WritePCIRegWord(IN UINT8 RegNum,IN UINT8 BusNum,IN UINT8 DevFunc,IN UINT16 val);
VOID    WritePCIRegDWord(IN UINT8 RegNum,IN UINT8 BusNum,IN UINT8 DevFunc,IN UINT32 val);
UINT32  GetPCIAddrFormat(IN UINT8 RegNum,IN UINT8 BusNum,IN UINT8 DevFunc);
UINT8   FindCapPtrDbg(IN UINT8 Bus,IN UINT8 DevFunc,IN UINT8 CapId);
VOID    PEI8259WriteMask(IN UINT16 Mask,IN UINT16 EdgeLevel);
VOID    PEI8259SetVectorBase (IN UINT8 MasterBase,IN UINT8 SlaveBase);
VOID    Program8254Timer0(IN UINT16 Count);
VOID    InitUsbEhciDebugPort(VOID);

#ifdef DBG_PEI_XHCI_CONTROLLER_PCI_ADDRESS
PCI_BUS_DEV_FUNCTION gXhciPciTbl[] = {DBG_PEI_XHCI_CONTROLLER_PCI_ADDRESS {0,0,0}};
UINT16 gXhciPciTblCount = \
    sizeof(gXhciPciTbl) / sizeof(PCI_BUS_DEV_FUNCTION) - 1;
#endif

#if defined(USB_DEBUG_TRANSPORT) && (USB_DEBUG_TRANSPORT == 1)
/**
    This function is used to set USB Hub downstream port for debug
    port mode(on EHCI port 1). While the port from HUB selected
    will be used as debug port, the rest of ports will still be 
    used as normal functional ports.

    @param VOID

    @retval VOID

    @note  PORTING REQUIRED
**/

VOID SbPeiDebugStall (UINTN Usec)
{
    UINTN   Counter = (Usec * 7)/2; // 3.58 count per microsec
    UINTN   i;
    UINT32  Data32;
    UINT32  PrevData;

    PrevData = IoRead32(PM_BASE_ADDRESS + 8);
    for (i=0; i < Counter; ) {
       Data32 = IoRead32(PM_BASE_ADDRESS + 8);
        if (Data32 < PrevData) {        // Reset if there is a overlap
            PrevData=Data32;
            continue;
        }
        i += (Data32 - PrevData);
		PrevData=Data32; // FIX need to find out the real diff betweek different count.
    }
}
/**
    This function is used to set USB Hub downstream port for debug
    port mode(on EHCI port 1). While the port from HUB selected
    will be used as debug port, the rest of ports will still be 
    used as normal functional ports.

    @param VOID

    @retval VOID

    @note  PORTING REQUIRED
**/

VOID
InitUsbEhciDebugPort (VOID)
{
	UINT8 Value, Port;

    if (EHCI_DEBUG_PORT_SELECT != 0) {
        
        Port = EHCI_DEBUG_PORT_SELECT;
        Port--;

        Value = ReadPCIRegByte(0x92, PCI_EHCI_BUS_NUMBER,
                        PCI_EHCI_DEV_FUNC_NUMBER);
        Value &= ~3; // clear BIT[16:17] of 0x90
        Value |= Port;
        Value |= 0x4; // HubMuxDbgEn enable   

        WritePCIRegByte(0x92, PCI_EHCI_BUS_NUMBER,
                PCI_EHCI_DEV_FUNC_NUMBER, Value);
    }
}

/**
    This function is used to set USB Hub downstream port for debug
    port mode(on EHCI port 1). While the port from HUB selected
    will be used as debug port, the rest of ports will still be 
    used as normal functional ports.

    @param VOID

    @retval VOID

    @note  PORTING REQUIRED
**/

VOID
SbPeiInitResetPowerAllDev (
  )
{
  UINT8 DevCount[] = {15, 18, 23, 24, 17, 5, 6, 7, 8, 11, 12};
  UINT8 i;

  for (i = 0; i < sizeof (DevCount); i++) {
    ACPIMMIO8 (FCH_AOACx40_D3_CONTROL + (DevCount[i] << 1)) |= AOAC_PWR_ON_DEV;
  }
  SbPeiDebugStall (1000);
}

/**
    This eLink function is used to initialize the EHCI controller
    debug port for USB PEI Debugging. It also fills the transport
    interface structure with appropriate information

    @param DebugPort Debug transport interface structure

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

    @note  PORTING REQUIRED
**/

EFI_STATUS
SBPEIDBG_InitUsbEhci (
    IN OUT  PEI_DBG_PORT_INFO   *DebugPort
)
{
    UINT8               PwrMgtCapReg;
    UINT8               DbgPrtCapReg;
    UINT16              CmdReg;
    UINT16              DbgPrtBaseOffset;
    UINT32              EhciBaseAddress = 0;

#define PWR_MGT_CAP_ID      1
#define PME_STATUS          0x8000
#define DBG_PRT_CAP_ID      0xA
                                                        // (DebugRxPorting-) >

// (P20100326A)>
//#### RW_IO8_PMIO(SB_PMIOA_REGEF,0x7F,0);  //Enable ALL USB Controller
    IoWrite8(0xCD6, 0xEF);
    IoWrite8(0xCD7, 0x7F);
    
    ACPIMMIO32 (FCH_AOACx94S013_CONTROL) &= ~ (FCH_AOACx94S013_CONTROL_ARBITER_DIS + FCH_AOACx94S013_CONTROL_INTERRUPT_DIS);
    SbPeiInitResetPowerAllDev ();
// <(P20100326A)

    InitUsbEhciDebugPort();

    if (DebugPort->UsbDebugPort.USBBaseAddr)
        EhciBaseAddress = DebugPort->UsbDebugPort.USBBaseAddr;
    else
        EhciBaseAddress = EHCI_MMIO_BASE_ADDRESS;

    //First disable the EHCI device by programming PCI command register
    CmdReg = ReadPCIRegWord(0x4, PCI_EHCI_BUS_NUMBER,
                    PCI_EHCI_DEV_FUNC_NUMBER);

    if(CmdReg & 1) {
        WritePCIRegWord(0x4, PCI_EHCI_BUS_NUMBER,
                    PCI_EHCI_DEV_FUNC_NUMBER, 0);
    }

    // Assign MMIO base address register in appropriate PCI register
    WritePCIRegDWord(0x10, PCI_EHCI_BUS_NUMBER, PCI_EHCI_DEV_FUNC_NUMBER,
                    EhciBaseAddress);

    //Set the Power state of the device to D0
    PwrMgtCapReg = FindCapPtrDbg(PCI_EHCI_BUS_NUMBER, PCI_EHCI_DEV_FUNC_NUMBER,
                    PWR_MGT_CAP_ID);

    WritePCIRegWord(PwrMgtCapReg + 4, PCI_EHCI_BUS_NUMBER, PCI_EHCI_DEV_FUNC_NUMBER,
                    PME_STATUS);

    // Enable EHCI register & make it Bus master
    CmdReg = CmdReg | 0x06;
    WritePCIRegWord(0x4, PCI_EHCI_BUS_NUMBER, PCI_EHCI_DEV_FUNC_NUMBER,
                    CmdReg);

    // Locate the Debug port register Interface location
    DbgPrtCapReg = FindCapPtrDbg(PCI_EHCI_BUS_NUMBER, PCI_EHCI_DEV_FUNC_NUMBER,
                                DBG_PRT_CAP_ID);

    DbgPrtBaseOffset = ReadPCIRegWord(DbgPrtCapReg + 2, PCI_EHCI_BUS_NUMBER,
                                        PCI_EHCI_DEV_FUNC_NUMBER);
    DbgPrtBaseOffset &= 0x1fff;

    if (DebugPort->UsbDebugPort.USBBaseAddr == 0) {
        DebugPort->UsbDebugPort.USBBaseAddr = EHCI_MMIO_BASE_ADDRESS;
        DebugPort->UsbDebugPort.MemoryMappedIoSpaceSize = EHCI_MMIO_SIZE;
    }
    DebugPort->UsbDebugPort.USBDebugPortStartAddr = EhciBaseAddress + DbgPrtBaseOffset;
    DebugPort->UsbDebugPort.PciBusNumber = PCI_EHCI_BUS_NUMBER;
    DebugPort->UsbDebugPort.PciDeviceNumber = (PCI_EHCI_DEV_FUNC_NUMBER >> 3);
    DebugPort->UsbDebugPort.PciFunctionNumber = PCI_EHCI_DEV_FUNC_NUMBER & 0x7;
    DebugPort->UsbDebugPort.PciBAROffset = PCI_EHCI_BAR_OFFSET;
    DebugPort->UsbDebugPort.InitUSBEHCI = SBPEIDBG_InitUsbEhci;

    return EFI_SUCCESS;
}
#endif

#if USB_3_DEBUG_SUPPORT == 1
/**
    This eLink function is used to initialize the XHCI controller
    debug port for USB PEI Debugging. It also fills the transport
    interface structure with appropriate information

    @param DebugPort Debug transport interface structure

    @retval EFI_STATUS

    @note  1. xHCI Controllers must be initialized after PEI Memory is installed (Init power state, clock ..etc), ensure USB xHCI Debug Capability is functionality. 
    @note  2. The entries for xHCI controllers in gAmiBadPciDevList of PciBus.c must be removed.
    @note  3. xHCI controllers can't be re-initialized/disabled at DXE.
    @note  PORTING REQUIRED
**/
EFI_STATUS SbPeiDbgInitXhci (
    IN OUT PEI_DBG_PORT_INFO    *DebugPort
)
{
	EFI_STATUS	Status = EFI_SUCCESS;
    UINT32		XhciBaseAddress = (UINT32)PcdGet64(PcdUsbXhciMemorySpaceBase);
	UINTN		Address;
	UINTN		i = 0;
	UINT8 		Bus = (PcdGet32(PcdUsbXhciPciAddress) >> 20) & 0xFF;
	UINT8 		Device = (PcdGet32(PcdUsbXhciPciAddress) >> 15) & 0x1F;
	UINT8 		Function = (PcdGet32(PcdUsbXhciPciAddress) >> 12) & 0x7;
	UINT8     	PwrMgtCapReg;

    if(DebugPort->UsbDebugPort.USBBaseAddr) {
      XhciBaseAddress = DebugPort->UsbDebugPort.USBBaseAddr;
    }


    //
    // For AMD-FCH-Sandstone. The XHCI is behind a bridge. Let's assign bus resource first.
    //
	Address = PCI_LIB_ADDRESS(0, 0x8, 0x1, 0x18);
	PciAndThenOr32(Address, 0, (((FIXED_XHCI_BUS_SANDSTONE<<8)+FIXED_XHCI_BUS_SANDSTONE)<<8));

	// For mmio resource we should consider other device
	Address = PCI_LIB_ADDRESS(0, 0x8, 0x1, 0x20);
	PciAndThenOr16(Address, 0, (XhciBaseAddress >> 16) - 0x10);
	Address = PCI_LIB_ADDRESS(0, 0x8, 0x1, 0x22);
	PciAndThenOr16(Address, 0, (XhciBaseAddress >> 16) + 0x30);
	Address = PCI_LIB_ADDRESS(0, 0x8, 0x1, 0x4);
	PciAndThenOr8(Address, 0, 0x6);

	for (i = 0; i < gXhciPciTblCount; i++) {
		#define MY_PCI_LIB_ADDRESS(MyIndex, MyReg) \
					PCI_LIB_ADDRESS( \
							gXhciPciTbl[MyIndex].Bus, \
							gXhciPciTbl[MyIndex].Device, \
							gXhciPciTbl[MyIndex].Function, \
							MyReg \
					)
		// setup resource depend on PcdUsbXhciPciAddress. support multi-controller later.
		if (!(Bus == gXhciPciTbl[i].Bus
				&& Device == gXhciPciTbl[i].Device
				&& Function == gXhciPciTbl[i].Function)) {
			continue;
		}
		//####// Get VID/DID, see if controller is visible on PCI
		//####Address = MY_PCI_LIB_ADDRESS(i, PCI_VENDOR_ID_OFFSET); // PCI_VID
		//####Vid = PciRead16(Address);
		//####//---if (Vid == 0xffff) continue;    // Controller not present
		//####Address = MY_PCI_LIB_ADDRESS(i, PCI_DEVICE_ID_OFFSET); // PCI_DID
		//####Did = PciRead16(Address);

		Address = MY_PCI_LIB_ADDRESS(i, 0x10);
		PciWrite32(Address, XhciBaseAddress);

		//
		// Set the Power state of the device to D0
		//
		PwrMgtCapReg = FindCapPtr (
						CSP_PCIE_CFG_ADDRESS (gXhciPciTbl[i].Bus, gXhciPciTbl[i].Device, gXhciPciTbl[i].Function, 0),
						PCI_CAP_ID_PMI
						);
		PciWrite16(MY_PCI_LIB_ADDRESS(i, PwrMgtCapReg + 4), PM_STATUS_CTRL);
	}

    if (DebugPort->UsbDebugPort.USBBaseAddr == 0) {
      DebugPort->UsbDebugPort.USBBaseAddr = XhciBaseAddress;
    }
    DebugPort->UsbDebugPort.PciBusNumber          = Bus;
    DebugPort->UsbDebugPort.PciDeviceNumber       = Device;
    DebugPort->UsbDebugPort.PciFunctionNumber     = Function;
    DebugPort->UsbDebugPort.InitUSBEHCI           = SbPeiDbgInitXhci;

    return Status;
}
#endif

/**
    This function programs the SB register to enable the serial
    IRQ

    @param VOID

    @retval VOID

    @note  PORTING REQUIRED
**/

VOID
EnableSerialIRQ (VOID)
{

// (P20100326A)>
//#### RW_IO8_PMIO(SB_PMIOA_REG54,BIT4+BIT6+BIT7,0);  //Enable the Serial IRQ
    IoWrite8(PM_IO_INDEX,0x54);
    IoWrite8(PM_IO_DATA, 0xD0);
// <(P20100326A)
}

/**
    This function programs the SB register to enable the LPC IO
    Decoding ranges to enable the programming of SIO and Serial Port.

    @param VOID

    @retval VOID

    @note  PORTING REQUIRED
**/

VOID
Enable_LPC_IO_Decode (VOID)
{
    UINT32      Buffer;

    //>> AMD SB600 P2P and LPC decode in the SBSECInit.ASM

    //
    // LPC decode (BIT20) 8259 (BIT00) 8254 (BIT01)
    // SB800 default is enabled.

    //----------------------------------------
    // the Usb debugger use PM timer for delay
    //----------------------------------------
// AcpiDecodeEnable
    IoWrite8(PM_IO_INDEX,0x74);
    Buffer = IoRead8(PM_IO_DATA) | BIT00;
    IoWrite8(PM_IO_DATA, Buffer);

// AcpiMMioDecodeEn
    IoWrite8(PM_IO_INDEX,0x04);
    Buffer = IoRead8(PM_IO_DATA) | BIT01;
    IoWrite8(PM_IO_DATA, Buffer);

//Program PM BASE
    IoWrite8(PM_IO_INDEX,0x64);
    IoWrite8(PM_IO_DATA, 0x8);

    IoWrite8(PM_IO_INDEX,0x65);
    IoWrite8(PM_IO_DATA, (PM_BASE_ADDRESS >> 8));

//Program PM2 BASE
//   IoWrite8(PM_IO_INDEX,0x62);
//   IoWrite8(PM_IO_DATA, (PM2_BASE_ADDRESS & 0xFF));

// IoWrite8(PM_IO_INDEX,0x63);
// IoWrite8(PM_IO_DATA, (PM2_BASE_ADDRESS >> 8));

}

/**
    This function programs the SB register to disable
    the TCO timer. If this timer is not disabled the system
    will shutdown or reset as soon as the timer is expired

    @param VOID

    @retval VOID

    @note  PORTING REQUIRED
**/
VOID ProgramACPIBaseToDisableTCO (VOID)
{
    UINT8 Value8;
// (P20100326A)>
//#### RW_IO8_PMIO(SB_PMIOA_REG4C,BIT0,0); //disable the watchdog function
//#### RW_IO8_PMIO(SB_PMIOA_REG44+3,BIT7,0); //disable NB boot timer function.
  //  IoWrite8(PM_IO_INDEX,0x4C);
  //  IoWrite8(PM_IO_DATA, 0x01);
//PMx00 DecodeEn
//27:26 WatchDogOptions. Read-write. Reset: 00b. 00b=Enable WatchDogTimer.
//25:24 WatchDogFreq. Read-write. Reset: 11b. Defines the clock frequency used by the WatchDogTimer.
    
     IoWrite8(PM_IO_INDEX,0x03); 
     Value8=IoRead8(PM_IO_DATA);
     IoWrite8(PM_IO_DATA, (Value8 & 0xF3) | 0x04); //disable watchdog timer
  
    IoWrite8(PM_IO_INDEX,0x47);
    IoWrite8(PM_IO_DATA, 0x80);
// <(P20100326A)
}

/**
    This eLink function is used to initialize the South Bridge
    for PEI Debugger support

    @param DebugPort Debug transport interface structure

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

    @note  Normally no PORTING REQUIRED
**/

EFI_STATUS SBPEIDBG_Initialize (
    IN OUT  PEI_DBG_PORT_INFO   *DebugPort
)
{

    // Stop SB800 WatchDog
    ProgramACPIBaseToDisableTCO();

    // Init 8259 Controller
    PEI8259SetVectorBase (LEGACY_MODE_BASE_VECTOR_MASTER, LEGACY_MODE_BASE_VECTOR_SLAVE ); //testing

    // Set all 8259 Interrupts to edge triggered and disabled
    PEI8259WriteMask (0xffff , 0x0000);

    Enable_LPC_IO_Decode();

    EnableSerialIRQ();
    // (CSP_EIP_33808) >
    //  >> A problem here...
    // I need to clear 0x62[2] when I use Source Level Debugger in Pei
    //   else IRQ0 will be trigger immediately after Program8254Timer0.
    // It happened on some CRB board. (Shiner SB700 A12)
    // CIMx will set this bit back.
    // CIMx [SBPor.c] -> RPR 2.1 Enabling Legacy Interrupt Smbus_PCI_Config 0x62[2]=1.

    IoWrite8(0xCD6, 0x8);
    IoWrite8(0xCD7, IoRead8(0xCD7) & ~BIT04);
    // (CSP_EIP_33808) <

    Program8254Timer0(0);

    return EFI_SUCCESS;
}

/**
//----------------------------------------------------------------------------
    NO PORTING IS GENERALLY REQUIRED FOR THE ROUTINES BELOW.
//----------------------------------------------------------------------------
 **/


/**
    Converts the provided bus, device, function and register
    number of a PCI register into 32bit PCI access format

    @param RegNum PCI Register number
    @param BusNum PCI Bus number
    @param DevFunc PCI Device and function number

        UINT32 
    @retval addr Converted 32 bit PCI register access value

**/
UINT32 GetPCIAddrFormat(
    IN UINT8    RegNum,
    IN UINT8    BusNum,
    IN UINT8    DevFunc
)
{
    UINT32  addr;

    addr = ((UINT32) (( (UINT16) BusNum ) << 8) +  DevFunc) << 8;
    addr += (RegNum & 0xfc);
    addr |= 0x80000000;
    return addr;
}

/**
    Reads a byte value from the PCI address space

    @param RegNum PCI Register number
    @param BusNum PCI Bus number
    @param DevFunc PCI Device and function number

        UINT8 
    @retval value Byte read
**/

UINT8 ReadPCIRegByte(
    IN UINT8    RegNum,
    IN UINT8    BusNum,
    IN UINT8    DevFunc
)
{
    UINT32 PciAddr = GetPCIAddrFormat(RegNum,BusNum,DevFunc);

    IoWrite32(0xcf8, PciAddr);
    return IoRead8(0xcfc +(RegNum & 0x3));
}

/**
    Reads a word value from the PCI address space

    @param RegNum PCI Register number
    @param BusNum PCI Bus number
    @param DevFunc PCI Device and function number

        UINT16 
    @retval value Word read

**/

UINT16 ReadPCIRegWord(
    IN UINT8    RegNum,
    IN UINT8    BusNum,
    IN UINT8    DevFunc
)
{
    UINT32 PciAddr = GetPCIAddrFormat(RegNum,BusNum,DevFunc);

    IoWrite32(0xcf8, PciAddr);
    return IoRead16(0xcfc +(RegNum & 0x3));
}

/**
    Reads a double word value from the PCI address space

    @param RegNum PCI Register number
    @param BusNum PCI Bus number
    @param DevFunc PCI Device and function number

        UINT32 
    @retval value Double word read

**/
UINT32 ReadPCIRegDWord(
    IN UINT8    RegNum,
    IN UINT8    BusNum,
    IN UINT8    DevFunc
)
{
    UINT32 PciAddr = GetPCIAddrFormat(RegNum,BusNum,DevFunc);

    IoWrite32(0xcf8, PciAddr);
    return IoRead32(0xcfc +(RegNum & 0x3));
}

/**
    Writes a byte value to the PCI address space

    @param RegNum PCI Register number
    @param BusNum PCI Bus number
    @param DevFunc PCI Device and function number
    @param Val Value to write to the PCI address space

    @retval VOID

**/
VOID WritePCIRegByte(
    IN UINT8    RegNum,
    IN UINT8    BusNum,
    IN UINT8    DevFunc,
    IN UINT8    val
)
{
    UINT32 PciAddr = GetPCIAddrFormat(RegNum,BusNum,DevFunc);

    IoWrite32(0xcf8, PciAddr);
    IoWrite8(0xcfc +(RegNum & 0x3), val);
}


/**
    Writes a word value to the PCI address space

    @param RegNum PCI Register number
    @param BusNum PCI Bus number
    @param DevFunc PCI Device and function number
    @param Val Value to write to the PCI address space

    @retval VOID

**/
VOID WritePCIRegWord(
    IN UINT8    RegNum,
    IN UINT8    BusNum,
    IN UINT8    DevFunc,
    IN UINT16   val
)
{
    UINT32 PciAddr = GetPCIAddrFormat(RegNum,BusNum,DevFunc);

    IoWrite32(0xcf8, PciAddr);
    IoWrite16(0xcfc +(RegNum & 0x3), val);
}

/**
    Writes a double word value to the PCI address space

    @param RegNum PCI Register number
    @param BusNum PCI Bus number
    @param DevFunc PCI Device and function number
    @param Val Value to write to the PCI address space

    @retval VOID

**/
VOID WritePCIRegDWord(
    IN UINT8    RegNum,
    IN UINT8    BusNum,
    IN UINT8    DevFunc,
    IN UINT32   val
)
{
    UINT32 PciAddr = GetPCIAddrFormat(RegNum,BusNum,DevFunc);

    IoWrite32(0xcf8, PciAddr);
    IoWrite32(0xcfc +(RegNum & 0x3), val);
}

/**
    This function searches the PCI address space for the PCI
    device specified for a particular capability ID and returns
    the offset in the PCI address space if one found

    @param Bus PCI Bus number
    @param DevFunc PCI Device and function number
    @param CapId Capability ID to look for

        UINT8
    @retval value Capability ID location if one found Otherwise returns 0

**/
UINT8 FindCapPtrDbg(
    IN UINT8    Bus,
    IN UINT8    DevFunc,
    IN UINT8    CapId
)
{
    UINT8  Value;
    UINT8  Reg;

    Value = ReadPCIRegByte(6, Bus, DevFunc);

    if (Value == 0xff) return 0;            //No device.
    if (!(Value & (1 << 4))) return 0;      // Check if capabilities list.

    Reg = 0x34;         // Register to First capabilities pointer
                                            //if 0, then capabilities
    for(;;)
    {
        Value = ReadPCIRegByte(Reg, Bus, DevFunc);
        if (!Value) return 0;

        Reg = Value;        // ptr to CapID
        Value = ReadPCIRegByte(Reg, Bus, DevFunc);      //If capablity ID, return register that points to it.
        if (Value == CapId) return (UINT8)Reg;

        ++Reg;          //equals to next capability pointer.
    }
}

/**
    Writes PC 8259 interrupt Controller mask register

    @param Mask Mask to write
    @param EdgeLevel Edge/level trigger to be programmed

    @retval VOID

**/
VOID PEI8259WriteMask (
    IN UINT16 Mask,
    IN UINT16 EdgeLevel)
{
    IoWrite8 (LEGACY_8259_MASK_REGISTER_MASTER, (UINT8)Mask);
    IoWrite8 (LEGACY_8259_MASK_REGISTER_SLAVE,  (UINT8)(Mask >> 8));
    IoWrite8 (LEGACY_8259_EDGE_LEVEL_TRIGGERED_REGISTER_MASTER, (UINT8)EdgeLevel);
    IoWrite8 (LEGACY_8259_EDGE_LEVEL_TRIGGERED_REGISTER_SLAVE,  (UINT8)(EdgeLevel >> 8));
}


/**
    Set up the 8259 interrupt controller master and slave base values

    @param MasterBase Master base to be programmed
    @param SlaveBase Slave base to be programmed

    @retval VOID

**/
VOID PEI8259SetVectorBase (
    IN UINT8 MasterBase,
    IN UINT8 SlaveBase
)
{
    UINT8           Mask;

    // Initialize Slave interrupt controller.
    Mask = IoRead8 (LEGACY_8259_MASK_REGISTER_SLAVE);
    IoWrite8 (LEGACY_8259_CONTROL_REGISTER_SLAVE, 0x11);
    IoWrite8 (LEGACY_8259_MASK_REGISTER_SLAVE,    SlaveBase);
    IoWrite8 (LEGACY_8259_MASK_REGISTER_SLAVE,    0x02);
    IoWrite8 (LEGACY_8259_MASK_REGISTER_SLAVE,    0x01);
    IoWrite8 (LEGACY_8259_MASK_REGISTER_SLAVE,    Mask);

    // Initialize Master interrupt controller.
    Mask = IoRead8 (LEGACY_8259_MASK_REGISTER_MASTER);
    IoWrite8 (LEGACY_8259_CONTROL_REGISTER_MASTER, 0x11);
    IoWrite8 (LEGACY_8259_MASK_REGISTER_MASTER,    MasterBase);
    IoWrite8 (LEGACY_8259_MASK_REGISTER_MASTER,    0x04);
    IoWrite8 (LEGACY_8259_MASK_REGISTER_MASTER,    0x01);
    IoWrite8 (LEGACY_8259_MASK_REGISTER_MASTER,    Mask);

    IoWrite8 (LEGACY_8259_CONTROL_REGISTER_SLAVE,  LEGACY_8259_EOI);
    IoWrite8 (LEGACY_8259_CONTROL_REGISTER_MASTER, LEGACY_8259_EOI);
}

/**
    Programs the 8254 Timer channel 0

    @param Count Timer tick count

    @retval VOID

**/
VOID Program8254Timer0(
    IN UINT16 Count
)
{
    UINT8   LCntbyte,HCntbyte;

    LCntbyte = (UINT8)Count;
    HCntbyte = (UINT8)(Count >> 8);

    //Write the timer control port to select timer 0 and set to mode 3
    IoWrite8(TIMER_CONTROL_PORT, 0x36);

    //Write the Counter 0 with initial count value
    IoWrite8(TIMER0_COUNT_PORT, LCntbyte);
    IoWrite8(TIMER0_COUNT_PORT, HCntbyte);

    //Enable the IRQ0 interrupt for this timer 0 in USB Xport module
    //......
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
