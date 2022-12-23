//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2019, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file Dbg2Board.c
    Library Class for Dbg routines.

**/

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------

#include <DebugPortTable2.h>
#include <Protocol/PciIo.h>
#include <Pci.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseLib.h>

/**
  Calculate NumberDbgDeviceInfo.

  @retval  UINT8   NumberDbgDeviceInfo value.
**/
UINT8
EFIAPI
GetNumberDbgDeviceInfo (
    VOID
    )
{
    // NumberDbgDeviceInfo
    UINT8   NumDbgDevInfo = 0;
    
#if SERIAL_DEV_INFO_SUPPORT
    NumDbgDevInfo++;
#endif
    
#if EHCI_DEV_INFO_SUPPORT
    NumDbgDevInfo++;
#endif
    
#if XHCI_DEV_INFO_SUPPORT
    NumDbgDevInfo++;
#endif
    
    DEBUG((DEBUG_INFO, "Debug Port Tables: GetNumberDbgDeviceInfo %d \n", NumDbgDevInfo));
    return NumDbgDevInfo;
}


#if EHCI_DEV_INFO_SUPPORT || XHCI_DEV_INFO_SUPPORT
/**
  Get Capability Registers offset of the BAR.
  
  @param    UsbSubType  Supported SubType:DBG2_SUBTYPE_USB_EHCI, DBG2_SUBTYPE_USB_XHCI

  @retval   Address     Return offset of the BAR.
**/
UINT64
EFIAPI
GetCapRegBar (
  IN UINT8 UsbSubType
  )
{
    EFI_STATUS          Status;
    UINTN               PciDevCount = 0;
    EFI_HANDLE          *PciDevHB;
    UINTN               Index;
    EFI_PCI_IO_PROTOCOL *PciIo;
    UINTN               Seg; 
    UINTN               Bus;
    UINTN               Dev;
    UINTN               Fun;
    UINTN               EhciBDF[] = EHCI_SEG_BUS_DEV_FUN;
    UINTN               XhciBDF[] = XHCI_SEG_BUS_DEV_FUN;
    UINT32              Address;
    UINT64              Address64;

    Status= gBS->LocateHandleBuffer(ByProtocol, &gEfiPciIoProtocolGuid, NULL, &PciDevCount, &PciDevHB);
    DEBUG((DEBUG_INFO, "Debug Port Tables: Locate PCIIO protocol %r \n", Status));
    if (EFI_ERROR(Status)) return 0;
    DEBUG((DEBUG_INFO, "Debug Port Tables: How many PCI devices? Ans:%d. \n", PciDevCount));

    for (Index = 0; Index < PciDevCount; Index++) {
        Status = gBS->HandleProtocol(PciDevHB[Index], &gEfiPciIoProtocolGuid, (VOID**)&PciIo);
        if (EFI_ERROR(Status)) {
            gBS->FreePool(PciDevHB);
            return 0;
        }
        Status = PciIo->GetLocation(PciIo, &Seg, &Bus, &Dev, &Fun);
        if (EFI_ERROR(Status)) break;
        
        if(UsbSubType == DBG2_SUBTYPE_USB_EHCI){
            if ((Seg == EhciBDF[0]) && (Bus == EhciBDF[1]) && \
                    (Dev == EhciBDF[2]) && (Fun == EhciBDF[3])){
                Status = PciIo->Pci.Read(PciIo, EfiPciIoWidthUint32, PCI_BAR0, 1, &Address);
                if (EFI_ERROR(Status)) break;
                if ((Address & (BIT1 | BIT2)) == BIT2) {
                    Status = PciIo->Pci.Read(PciIo, EfiPciIoWidthUint32, PCI_BAR0, sizeof(VOID*)/sizeof(UINT32), &Address64);
                    if (EFI_ERROR(Status)) break;
                    Address64 = Address64 & ~(BIT0 | BIT1 | BIT2 | BIT3); // Clear attributes
                    DEBUG((DEBUG_INFO, "Debug Port Tables: 64bit BAR0 [0x%lx] \n", Address64));
                    
                    gBS->FreePool(PciDevHB);
                    return Address64;
                }
                DEBUG((DEBUG_INFO, "Debug Port Tables: BAR0 [0x%lx] \n", Address));
                gBS->FreePool(PciDevHB);
                return Address;
            }
        } else if (UsbSubType == DBG2_SUBTYPE_USB_XHCI){
            if ((Seg == XhciBDF[0]) && (Bus == XhciBDF[1]) && \
                    (Dev == XhciBDF[2]) && (Fun == XhciBDF[3])){
                Status = PciIo->Pci.Read(PciIo, EfiPciIoWidthUint32, PCI_BAR0, 1, &Address);
                if (EFI_ERROR(Status)) break;
                if ((Address & (BIT1 | BIT2)) == BIT2) {
                    Status = PciIo->Pci.Read(PciIo, EfiPciIoWidthUint32, PCI_BAR0, sizeof(VOID*)/sizeof(UINT32), &Address64);
                    if (EFI_ERROR(Status)) break;
                    Address64 = Address64 & ~(BIT0 | BIT1 | BIT2 | BIT3); // Clear attributes
                    DEBUG((DEBUG_INFO, "Debug Port Tables: 64bit BAR0 [0x%lx] \n", Address64));
                    
                    gBS->FreePool(PciDevHB);
                    return Address64;
                }
                DEBUG((DEBUG_INFO, "Debug Port Tables: BAR0 [0x%lx] \n", Address));
                gBS->FreePool(PciDevHB);
                return Address;
            }
        }
    }
    gBS->FreePool(PciDevHB);
    return 0;
}
#endif

/**
  Setting the DBG2 device information data.

  @param  Dbg2Table    Point to Default DBG2 header.

  @retval  VOID*   Point to new DBG2 table address.
**/
VOID *
EFIAPI
SetupDebugDeviceInformationData (
  IN DBG_PORT_2_TABLE *Dbg2Table
  )
{
    EFI_STATUS          Status = EFI_SUCCESS;
    VOID                *IntegrateDebugPort2Table = NULL;
    UINT16              IntegrateDebugPort2TableSize = 0;
    UINT16              TotalDbgDevInfoSize = 0;

#if SERIAL_DEV_INFO_SUPPORT || EHCI_DEV_INFO_SUPPORT || XHCI_DEV_INFO_SUPPORT
    UINT16              SerialDbgDevInfoSize = 0;
    DBG_DEV_INFO_STRUCT *SerialDevInfo = NULL;
#endif

#if EHCI_DEV_INFO_SUPPORT || XHCI_DEV_INFO_SUPPORT
    UINT16              EhciPort0DbgDevInfoSize = 0;
#endif

#if SERIAL_DEV_INFO_SUPPORT
    UINT8               *DefaultNameSpace = NULL;
    UINT8               *SerialNameSpaceStr = NULL;
    UINT16              SizeForDefaultNameSpace = 0;
    UINT32              *SerialAddrSize = NULL;
    GAS_30              *SerialDBaseAddrReg = NULL;
#endif

#if EHCI_DEV_INFO_SUPPORT
    UINT8               *EhciPort0NameSpace = NULL;
    UINT8               *EchiPort0NameSpaceStr = NULL;
    UINT16              SizeForEhciPort0NameSpace = 0;
    UINT32              *EchiPort0AddrSize = NULL;
    DBG_DEV_INFO_STRUCT *EhciPort0DevInfo = NULL;
    GAS_30              *EhciPort0BaseAddrReg = NULL;
#endif
    
#if XHCI_DEV_INFO_SUPPORT
    UINT16              XhciPort0DbgDevInfoSize = 0;
    UINT8               *XhciPort0NameSpace = NULL;
    UINT8               *XchiPort0NameSpaceStr = NULL;
    UINT16              SizeForXhciPort0NameSpace = 0;
    UINT32              *XchiPort0AddrSize = NULL;
    DBG_DEV_INFO_STRUCT *XhciPort0DevInfo = NULL;
    GAS_30              *XhciPort0BaseAddrReg = NULL;
#endif
    //
    // 1. Initialize the number of device and Offset debug device Info for DBG2
    //
    Dbg2Table->NumberDbgDeviceInfo = GetNumberDbgDeviceInfo();
    if (Dbg2Table->NumberDbgDeviceInfo == 0)
        return (VOID*)Dbg2Table;

    Dbg2Table->OffsetDbgDeviceInfo = sizeof(DBG_PORT_2_TABLE);
    //
    // 2. Initialize the DBG2 debug device's name space string and size
    //

#if SERIAL_DEV_INFO_SUPPORT
    
    DefaultNameSpace = (UINT8 *) SERIAL_NAME_SPACE;
    SizeForDefaultNameSpace = (UINT16)AsciiStrSize((CHAR8 *) DefaultNameSpace);
#endif

#if EHCI_DEV_INFO_SUPPORT
    
    EhciPort0NameSpace = (UINT8 *) EHCI_USB_NAME_SPACE;
    SizeForEhciPort0NameSpace = (UINT16)AsciiStrSize((CHAR8 *) EhciPort0NameSpace);
#endif
    
#if XHCI_DEV_INFO_SUPPORT
    
    XhciPort0NameSpace = (UINT8 *) XHCI_USB_NAME_SPACE;
    SizeForXhciPort0NameSpace = (UINT16)AsciiStrSize((CHAR8 *) XhciPort0NameSpace);
#endif
    //
    // 3. Initialize the DBG2 total size, each device info size.
    //
#if SERIAL_DEV_INFO_SUPPORT	
    SerialDbgDevInfoSize = (UINT16)(
                                sizeof(DBG_DEV_INFO_STRUCT) +   // Debug Device Information Structure
                                (SERIAL_NUM_OF_GENERIC_ADDR_REG * sizeof(GAS_30)) +                // Base Address Registe - Assume 1 BAR
                                (SERIAL_NUM_OF_GENERIC_ADDR_REG * ADDRESS_SIZE_LENGTH) +                             // Address Size
                                SizeForDefaultNameSpace +       // Name Space String
                                0                               // Oem Data - Assume none
                            );
    TotalDbgDevInfoSize += SerialDbgDevInfoSize;
#endif

#if EHCI_DEV_INFO_SUPPORT
    EhciPort0DbgDevInfoSize = (UINT16)(
                                sizeof(DBG_DEV_INFO_STRUCT) +   // Debug Device Information Structure
                                (EHCI_NUM_OF_GENERIC_ADDR_REG * sizeof(GAS_30)) +                // Base Address Registe - Assume 1 BAR
                                (EHCI_NUM_OF_GENERIC_ADDR_REG * ADDRESS_SIZE_LENGTH) +                             // Address Size
                                SizeForEhciPort0NameSpace +     // Name Space String
                                0                               // Oem Data - Assume none
                            );
    TotalDbgDevInfoSize += EhciPort0DbgDevInfoSize;
#endif
    
#if XHCI_DEV_INFO_SUPPORT
    XhciPort0DbgDevInfoSize = (UINT16)(
                                sizeof(DBG_DEV_INFO_STRUCT) +   // Debug Device Information Structure
                                (XHCI_NUM_OF_GENERIC_ADDR_REG * sizeof(GAS_30)) +                // Base Address Registe - Assume 1 BAR
                                (XHCI_NUM_OF_GENERIC_ADDR_REG * ADDRESS_SIZE_LENGTH) +                             // Address Size
                                SizeForXhciPort0NameSpace +     // Name Space String
                                0                               // Oem Data - Assume none
                            );
    TotalDbgDevInfoSize += XhciPort0DbgDevInfoSize;
#endif

    IntegrateDebugPort2TableSize = sizeof(DBG_PORT_2_TABLE) + TotalDbgDevInfoSize;

    //
    // 4. Allocate memory for DBG2
    //
    Status = gBS->AllocatePool (EfiBootServicesData, IntegrateDebugPort2TableSize, &IntegrateDebugPort2Table);
    ASSERT_EFI_ERROR (Status);
    if (EFI_ERROR(Status)) return NULL;

    gBS->SetMem (IntegrateDebugPort2Table, IntegrateDebugPort2TableSize, 0);

    //
    // 5. Update total length
    //
    Dbg2Table->AcpiHeader.Length = IntegrateDebugPort2TableSize;

    //
    // 6. Copy Dbg2Table to New table pointer
    //
    gBS->CopyMem((VOID *)IntegrateDebugPort2Table, (VOID *)Dbg2Table, sizeof(DBG_PORT_2_TABLE));

    //  
    // 7. Set pointer to DBG2 Device Info Structure Offset
    //
#if SERIAL_DEV_INFO_SUPPORT || EHCI_DEV_INFO_SUPPORT || XHCI_DEV_INFO_SUPPORT
    SerialDevInfo = (DBG_DEV_INFO_STRUCT*)((UINT8 *)IntegrateDebugPort2Table + Dbg2Table->OffsetDbgDeviceInfo);
#endif

#if EHCI_DEV_INFO_SUPPORT
    EhciPort0DevInfo = (DBG_DEV_INFO_STRUCT*)((UINT8 *)SerialDevInfo + SerialDbgDevInfoSize);
#endif
    
#if XHCI_DEV_INFO_SUPPORT
    XhciPort0DevInfo = (DBG_DEV_INFO_STRUCT*)((UINT8 *)SerialDevInfo + SerialDbgDevInfoSize + EhciPort0DbgDevInfoSize);
#endif

    //
    // 8. Populate DBG2 Device Info Structure
    //
#if SERIAL_DEV_INFO_SUPPORT
    // Serial
    SerialDevInfo->Revision                        = 0x00;
    SerialDevInfo->Length                          = SerialDbgDevInfoSize;
    SerialDevInfo->NumberOfGenericAddressRegisters = SERIAL_NUM_OF_GENERIC_ADDR_REG;
    SerialDevInfo->NameSpaceStringLength           = SizeForDefaultNameSpace;
    SerialDevInfo->NameSpaceStringOffset           = sizeof(DBG_DEV_INFO_STRUCT) + (sizeof(GAS_30)*(SerialDevInfo->NumberOfGenericAddressRegisters)) + (ADDRESS_SIZE_LENGTH*(SerialDevInfo->NumberOfGenericAddressRegisters));
    SerialDevInfo->OemDataLength                   = 0;
    SerialDevInfo->OemDataOffset                   = 0;
    SerialDevInfo->PortType                        = DBG2_TYPE_SERIAL;
    SerialDevInfo->PortSubtype                     = DBG2_SUBTYPE_SERIAL_FULL_16550;
    SerialDevInfo->Reserved[0]                     = 0;
    SerialDevInfo->Reserved[1]                     = 0;
    SerialDevInfo->BaseAddressRegisterOffset       = sizeof(DBG_DEV_INFO_STRUCT);
    SerialDevInfo->AddressSizeOffset               = sizeof(DBG_DEV_INFO_STRUCT) + (sizeof(GAS_30)*(SerialDevInfo->NumberOfGenericAddressRegisters));
#endif

#if EHCI_DEV_INFO_SUPPORT
    // EHCI
    EhciPort0DevInfo->Revision                         = 0x00;
    EhciPort0DevInfo->Length                           = EhciPort0DbgDevInfoSize;
    EhciPort0DevInfo->NumberOfGenericAddressRegisters  = EHCI_NUM_OF_GENERIC_ADDR_REG;
    EhciPort0DevInfo->NameSpaceStringLength            = SizeForEhciPort0NameSpace;
    EhciPort0DevInfo->NameSpaceStringOffset            = sizeof(DBG_DEV_INFO_STRUCT) + (sizeof(GAS_30)*(EhciPort0DevInfo->NumberOfGenericAddressRegisters)) + (ADDRESS_SIZE_LENGTH*(EhciPort0DevInfo->NumberOfGenericAddressRegisters));
    EhciPort0DevInfo->OemDataLength                    = 0;
    EhciPort0DevInfo->OemDataOffset                    = 0;
    EhciPort0DevInfo->PortType                         = DBG2_TYPE_USB;
    EhciPort0DevInfo->PortSubtype                      = DBG2_SUBTYPE_USB_EHCI;
    EhciPort0DevInfo->Reserved[0]                      = 0;
    EhciPort0DevInfo->Reserved[1]                      = 0;
    EhciPort0DevInfo->BaseAddressRegisterOffset        = sizeof(DBG_DEV_INFO_STRUCT);
    EhciPort0DevInfo->AddressSizeOffset                = sizeof(DBG_DEV_INFO_STRUCT) + (sizeof(GAS_30)*(EhciPort0DevInfo->NumberOfGenericAddressRegisters));
#endif
    
#if XHCI_DEV_INFO_SUPPORT
    // XHCI
    XhciPort0DevInfo->Revision                         = 0x00;
    XhciPort0DevInfo->Length                           = XhciPort0DbgDevInfoSize;
    XhciPort0DevInfo->NumberOfGenericAddressRegisters  = XHCI_NUM_OF_GENERIC_ADDR_REG;
    XhciPort0DevInfo->NameSpaceStringLength            = SizeForXhciPort0NameSpace;
    XhciPort0DevInfo->NameSpaceStringOffset            = sizeof(DBG_DEV_INFO_STRUCT) + (sizeof(GAS_30)*(XhciPort0DevInfo->NumberOfGenericAddressRegisters)) + (ADDRESS_SIZE_LENGTH*(XhciPort0DevInfo->NumberOfGenericAddressRegisters));
    XhciPort0DevInfo->OemDataLength                    = 0;
    XhciPort0DevInfo->OemDataOffset                    = 0;
    XhciPort0DevInfo->PortType                         = DBG2_TYPE_USB;
    XhciPort0DevInfo->PortSubtype                      = DBG2_SUBTYPE_USB_XHCI;
    XhciPort0DevInfo->Reserved[0]                      = 0;
    XhciPort0DevInfo->Reserved[1]                      = 0;
    XhciPort0DevInfo->BaseAddressRegisterOffset        = sizeof(DBG_DEV_INFO_STRUCT);
    XhciPort0DevInfo->AddressSizeOffset                = sizeof(DBG_DEV_INFO_STRUCT) + (sizeof(GAS_30)*(XhciPort0DevInfo->NumberOfGenericAddressRegisters));
#endif
    //  
    // 9. Set pointer to DBG2 Device Base Address Offset and populate value
    //

    // Point to First Device information data and fill data
#if SERIAL_DEV_INFO_SUPPORT
    SerialDBaseAddrReg = (GAS_30 *)((UINT8 *)SerialDevInfo + SerialDevInfo->BaseAddressRegisterOffset);
#endif

#if EHCI_DEV_INFO_SUPPORT
    EhciPort0BaseAddrReg = (GAS_30 *)((UINT8 *)EhciPort0DevInfo + EhciPort0DevInfo->BaseAddressRegisterOffset);
#endif
    
#if XHCI_DEV_INFO_SUPPORT
    XhciPort0BaseAddrReg = (GAS_30 *)((UINT8 *)XhciPort0DevInfo + XhciPort0DevInfo->BaseAddressRegisterOffset);
#endif

#if SERIAL_DEV_INFO_SUPPORT
    // Serial
    SerialDBaseAddrReg->AddrSpcID      = SERIAL_DBG2_ADDR_SPC_ID;
    SerialDBaseAddrReg->RegBitWidth    = SERIAL_DBG2_ADDR_BIT_WIDTH;
    SerialDBaseAddrReg->RegBitOffs     = SERIAL_DBG2_ADDR_BIT_OFFSET;
    SerialDBaseAddrReg->AccessSize     = SERIAL_DBG2_ACCESS_SIZE;
    SerialDBaseAddrReg->Address        = PcdGet64 (PcdSerialRegisterBase);
#endif

#if EHCI_DEV_INFO_SUPPORT
    // ECHI
    EhciPort0BaseAddrReg->AddrSpcID    = EHCIPORT0_DBG2_ADDR_SPC_ID;
    EhciPort0BaseAddrReg->RegBitWidth  = EHCIPORT0_DBG2_ADDR_BIT_WIDTH;
    EhciPort0BaseAddrReg->RegBitOffs   = EHCIPORT0_DBG2_ADDR_BIT_OFFSET;
    EhciPort0BaseAddrReg->AccessSize   = EHCIPORT0_DBG2_ACCESS_SIZE;

    // Get Capability Registers offset off the BAR
    EhciPort0BaseAddrReg->Address      = GetCapRegBar(DBG2_SUBTYPE_USB_EHCI);
#endif
    
#if XHCI_DEV_INFO_SUPPORT
    // XCHI
    XhciPort0BaseAddrReg->AddrSpcID    = XHCIPORT0_DBG2_ADDR_SPC_ID;
    XhciPort0BaseAddrReg->RegBitWidth  = XHCIPORT0_DBG2_ADDR_BIT_WIDTH;
    XhciPort0BaseAddrReg->RegBitOffs   = XHCIPORT0_DBG2_ADDR_BIT_OFFSET;
    XhciPort0BaseAddrReg->AccessSize   = XHCIPORT0_DBG2_ACCESS_SIZE;

    // Get Capability Registers offset off the BAR
    XhciPort0BaseAddrReg->Address      = GetCapRegBar(DBG2_SUBTYPE_USB_XHCI);
#endif

    //
    // 10. Set pointer to DBG2 Device Address Size Offset and populate value
    //	
#if SERIAL_DEV_INFO_SUPPORT
    SerialAddrSize = (UINT32 *)((UINT8*)SerialDevInfo + SerialDevInfo->AddressSizeOffset);
    *SerialAddrSize = SERIAL_GENERIC_ADDR_SIZE;
#endif

#if EHCI_DEV_INFO_SUPPORT
    EchiPort0AddrSize = (UINT32 *)((UINT8*)EhciPort0DevInfo + EhciPort0DevInfo->AddressSizeOffset);
    *EchiPort0AddrSize = EHCI_GENERIC_ADDR_SIZE;
#endif
    
#if XHCI_DEV_INFO_SUPPORT
    XchiPort0AddrSize = (UINT32 *)((UINT8*)XhciPort0DevInfo + XhciPort0DevInfo->AddressSizeOffset);
    *XchiPort0AddrSize = XHCI_GENERIC_ADDR_SIZE;    //Address size may be the GAS structure size(EIP244474)
#endif

    //
    // 11. Set pointer to DBG2 Device Name Space Offset and populate value
    //
#if SERIAL_DEV_INFO_SUPPORT
    SerialNameSpaceStr = (UINT8 *)((UINT8 *)SerialDevInfo + SerialDevInfo->NameSpaceStringOffset);
    gBS->CopyMem(SerialNameSpaceStr, DefaultNameSpace, SizeForDefaultNameSpace);
#endif

#if EHCI_DEV_INFO_SUPPORT
    EchiPort0NameSpaceStr = (UINT8 *)((UINT8 *)EhciPort0DevInfo + EhciPort0DevInfo->NameSpaceStringOffset);
    gBS->CopyMem(EchiPort0NameSpaceStr, EhciPort0NameSpace, SizeForEhciPort0NameSpace);
#endif
    
#if XHCI_DEV_INFO_SUPPORT
    XchiPort0NameSpaceStr = (UINT8 *)((UINT8 *)XhciPort0DevInfo + XhciPort0DevInfo->NameSpaceStringOffset);
    gBS->CopyMem(XchiPort0NameSpaceStr, XhciPort0NameSpace, SizeForXhciPort0NameSpace);
#endif

    return IntegrateDebugPort2Table;
}

//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2019, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
