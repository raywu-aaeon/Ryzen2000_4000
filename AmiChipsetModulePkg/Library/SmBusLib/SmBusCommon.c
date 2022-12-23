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
/** @file SmBusCommon.c
    SMBUS driver common functions implementation

**/
//**********************************************************************

//#include <AmiLib.h>
#include "Library/SmBusCommon.h"

UINT8 SmBusSpecReservedAddress[SMBUS_SPEC_RESERVED_ADDRESS] = {
    0x00,      // 0000 000 0 General Call Address
               // 0000 000 1 START byte
    0x01,      // 0000 001 X CBUS address
    0x02,      // 0000 010 X Address reserved for different bus format
    0x03,      // 0000 011 X Reserved for future use
    0x04,      // 0000 1XX X Reserved for future use
    0x05,
    0x06,
    0x07,
    0x28,      // 0101 000 X Reserved for ACCESS.bus host
    0x37,      // 0110 111 X Reserved for ACCESS.bus default address
    0x78,      // 1111 0XX X 10-bit slave addressing
    0x79,
    0x7a,
    0x7b,
    0x7c,      // 1111 1XX X Reserved for future use
    0x7d,
    0x7e,
    0x7f,
    0x08,      // 0001 000 X SMBus Host
    0x0c,      // 0001 100 X SMBus Alert Response Address
    0x61       // 1100 001 X SMBus Device Default Address
};

/**
    This function reads given number of bytes from SMBUS device

    @param SmBusBase SMBUS device IO address base
    @param Offset SMBUS device IO address offset
    @param ByteCount number of bytes to read
    @param Buffer pointer to buffer to store data

    @retval VOID

**/
VOID SmBusRead (
    IN   UINT16 SmBusBase,
    IN   UINT16 Offset,
    IN   UINTN  ByteCount,
    OUT  UINT8  *Buffer
)
{
    UINTN i;
    
    for(i = 0; i < ByteCount; i++)
        Buffer[i] = IoRead8(SmBusBase + Offset);
}

/**
    This function writes given number of bytes to SMBUS device

    @param SmBusBase SMBUS device IO address base
    @param Offset SMBUS device IO address offset
    @param ByteCount number of bytes to write
    @param Buffer pointer to buffer to get data from

    @retval VOID

**/
VOID SmBusWrite (
    IN   UINT16 SmBusBase,
    IN   UINT16 Offset,
    IN   UINTN  ByteCount,
    IN   UINT8  *Buffer
)
{
    UINTN i;
    
    for(i = 0; i < ByteCount; i++)
        IoWrite8(SmBusBase + Offset, Buffer[i]);
}

/**
    This function assign address to specific or all devices connected to SMBUS

    @param Context SMBUS device private data
    @param ArpAll Enumerate all devices flag
    @param SmbusUdid pointer to device ID to assign new address
    @param SlaveAddress pointer to return assigned address

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS ArpDevice (
    IN     SMBUS_PRIVATE            *Context,
    IN     BOOLEAN                  ArpAll,
    IN     EFI_SMBUS_UDID           *SmbusUdid, OPTIONAL
    IN OUT EFI_SMBUS_DEVICE_ADDRESS *SlaveAddress OPTIONAL
)
{
    if(ArpAll)
        return ArpDeviceFull(Context);
    else
        return ArpDeviceDirected(Context, SmbusUdid, SlaveAddress);
}

/**
    This function returns list of enumerated devices connected to SMBUS

    @param Context SMBUS device private data
    @param Length pointer to store size of address map
    @param SmbusDeviceMap pointer to store pointer to address map

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS GetArpMap (
    IN     SMBUS_PRIVATE        *Context,
    IN OUT UINTN                *Length,
    IN OUT EFI_SMBUS_DEVICE_MAP **SmbusDeviceMap
    )
{
//####    *Length = Context->ArpDeviceCount;                                // (P20111124A)>
    *Length = Context->ArpDeviceCount * sizeof (EFI_SMBUS_DEVICE_MAP);      // <(P20111124A)
    *SmbusDeviceMap = Context->ArpDeviceList;
    return EFI_SUCCESS;
}

/**
    This function sends PREPARE_TO_ARP command to devices connected to SMBUS

    @param Context SMBUS device private data

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS PrepareToArp (
    IN SMBUS_PRIVATE *Context
)
{
    EFI_SMBUS_DEVICE_ADDRESS  SlaveAddress;
    EFI_STATUS                Status;
    UINTN                     Length;
    UINT8                     Buffer;

    SlaveAddress.SmbusDeviceAddress = SMBUS_ADDRESS_ARP;
    Length = 1;
    Buffer = SMBUS_DATA_PREPARE_TO_ARP;

    Status = Execute (
                    Context,
                    SlaveAddress,
                    SMBUS_DATA_PREPARE_TO_ARP,
                    EfiSmbusSendByte,
                    TRUE,
                    &Length,
                    &Buffer );
    return Status;
}

/**
    This function checks if given address is available

    @param Context SMBUS device private data
    @param Address address to check

    @retval TRUE address is available
    @retval FALSE address is not available

**/
BOOLEAN IsAddressAvailable (
    IN SMBUS_PRIVATE *Context,
    IN UINT8         Address
)
{
    UINTN Index;

    for(Index = 0; Index < Context->ArpDeviceCount; Index++)
        if(Address == Context->ArpDeviceList[Index].SmbusDeviceAddress.SmbusDeviceAddress)
            return FALSE;

    for(Index = 0; Index < Context->BoardReservedAddressCount; Index++)
        if(Address == Context->BoardReservedAddressList[Index])
            return FALSE;

    for(Index = 0; Index < SMBUS_SPEC_RESERVED_ADDRESS; Index++)
        if(Address == SmBusSpecReservedAddress[Index])
            return FALSE;

    return TRUE;
}

/**
    This function returns available address

    @param Context SMBUS device private data

    @retval UINT8 address

**/
UINT8 GetAvailableAddress (
    IN SMBUS_PRIVATE *Context
)
{
    UINT8 Address;

    for(Address = SMBUS_LOWEST_AVAILABLE_ADDRESS; 
        Address <= SMBUS_HIGHEST_AVAILABLE_ADDRESS;
        Address++)
        if(IsAddressAvailable(Context, Address))
            return Address;

    return 0xff;
}

/**
    This function enumerates all devices connected to SMBUS

    @param Context SMBUS device private data

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS ArpDeviceFull (
    IN SMBUS_PRIVATE *Context
)
{
    EFI_SMBUS_DEVICE_MAP DeviceMap;
    EFI_STATUS Status;

    Status = PrepareToArp(Context);
    if(EFI_ERROR(Status))
        return (Status == EFI_DEVICE_ERROR) ? EFI_SUCCESS : Status;

    do
    {
        Status = GetUdidGeneral(Context, &DeviceMap);
        if(EFI_ERROR(Status))
            break;

        if(DeviceMap.SmbusDeviceAddress.SmbusDeviceAddress == 0x7f)     //0xff >> 1
        {
            DeviceMap.SmbusDeviceAddress.SmbusDeviceAddress = GetAvailableAddress(Context);
            if(DeviceMap.SmbusDeviceAddress.SmbusDeviceAddress == 0xff)
                return EFI_OUT_OF_RESOURCES;
        }
        else
        {
            if((DeviceMap.SmbusDeviceUdid.DeviceCapabilities & 0xC0) != 0 && \
                !IsAddressAvailable(Context, (UINT8)DeviceMap.SmbusDeviceAddress.SmbusDeviceAddress))
            {
                DeviceMap.SmbusDeviceAddress.SmbusDeviceAddress = GetAvailableAddress(Context);
                if(DeviceMap.SmbusDeviceAddress.SmbusDeviceAddress == 0xff)
                    return EFI_OUT_OF_RESOURCES;
            }
        }

        Status = AssignAddress(Context, &DeviceMap);
        if(EFI_ERROR(Status))
            return Status;

    //save assigned address to our database
        Context->ArpDeviceList[Context->ArpDeviceCount] = DeviceMap;
        Context->ArpDeviceCount++;
    } while(Context->ArpDeviceCount < Context->MaxDevices);

    return EFI_SUCCESS;
}

/**
    This function assign given address to given device

    @param Context SMBUS device private data
    @param SmbusUdid pointer to device ID
    @param SlaveAddress pointer to return assigned address

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS ArpDeviceDirected (
    IN     SMBUS_PRIVATE            *Context,
    IN     EFI_SMBUS_UDID           *SmbusUdid,
    IN OUT EFI_SMBUS_DEVICE_ADDRESS *SlaveAddress
)
{
    UINT8                AssignedAddress;
    EFI_SMBUS_DEVICE_MAP DeviceMap;
    EFI_STATUS           Status;

    if(Context->ArpDeviceCount > Context->MaxDevices)
        return EFI_OUT_OF_RESOURCES;

    AssignedAddress = GetAvailableAddress(Context);
    if(AssignedAddress == 0xff)
        return EFI_OUT_OF_RESOURCES;

    DeviceMap.SmbusDeviceAddress.SmbusDeviceAddress = AssignedAddress;
    DeviceMap.SmbusDeviceUdid = *SmbusUdid;

    Status = AssignAddress(Context, &DeviceMap);
    if(EFI_ERROR(Status))
        return Status;

//save assigned address to our database
    Context->ArpDeviceList[Context->ArpDeviceCount] = DeviceMap;
    Context->ArpDeviceCount++;

    *SlaveAddress = DeviceMap.SmbusDeviceAddress;
    return EFI_SUCCESS;
}

/**
    This function sends ASSIGN_ADDRESS command via SMBUS

    @param Context SMBUS device private data
    @param DeviceMap pointer to device Udid/Address pair

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS AssignAddress (
    IN SMBUS_PRIVATE        *Context,
    IN EFI_SMBUS_DEVICE_MAP *DeviceMap
    )
{
    UINT8                    Buffer[GET_UDID_BUFFER_SIZE];
    UINTN                    Length;
    EFI_STATUS               Status;
    EFI_SMBUS_DEVICE_ADDRESS SlaveAddress;

    ConvertMapToBuffer(DeviceMap, Buffer);

    Length = GET_UDID_BUFFER_SIZE;
    SlaveAddress.SmbusDeviceAddress = SMBUS_ADDRESS_ARP;

    Status = Execute (
                    Context,
                    SlaveAddress,
                    SMBUS_DATA_ASSIGN_ADDRESS,
                    EfiSmbusWriteBlock,
                    TRUE,
                    &Length,
                    Buffer );
    return Status;
}

/**
    This function sends GET_UDID_GENERAL command via SMBUS

    @param Context SMBUS device private data
    @param DeviceMap pointer to store device Udid/Address pair

               
    @retval EFI_SUCCESS Module initialized successfully
    @retval EFI_ERROR Initialization failed (see error for more details)

**/
EFI_STATUS GetUdidGeneral (
    IN  SMBUS_PRIVATE        *Context,
    OUT EFI_SMBUS_DEVICE_MAP *DeviceMap
)
{
    UINT8                    Buffer[GET_UDID_BUFFER_SIZE];
    UINTN                    Length;
    EFI_STATUS               Status;
    EFI_SMBUS_DEVICE_ADDRESS SlaveAddress;

    Length = GET_UDID_BUFFER_SIZE;
    SlaveAddress.SmbusDeviceAddress = SMBUS_ADDRESS_ARP;

    Status = Execute (
                    Context,
                    SlaveAddress,
                    SMBUS_DATA_GET_UDID_GENERAL,
                    EfiSmbusReadBlock,
                    TRUE,
                    &Length,
                    Buffer );

    if(EFI_ERROR(Status) || Length != GET_UDID_BUFFER_SIZE)
        return EFI_DEVICE_ERROR;

    ConvertBufferToMap(DeviceMap, Buffer);
    return Status;
}

/**
    This function converts EFI_SMBUS_DEVICE_MAP structure into UINT8[] buffer

    @param DeviceMap pointer to structure to convert from
    @param Buffer pointer buffer to convert to

    @retval VOID

**/
VOID ConvertMapToBuffer (
    IN EFI_SMBUS_DEVICE_MAP *DeviceMap,
    OUT UINT8               *Buffer
)
{
    Buffer[0] = DeviceMap->SmbusDeviceUdid.DeviceCapabilities;
    Buffer[1] = DeviceMap->SmbusDeviceUdid.VendorRevision;
    Buffer[2] = (UINT8)(DeviceMap->SmbusDeviceUdid.VendorId >> 8);
    Buffer[3] = (UINT8)(DeviceMap->SmbusDeviceUdid.VendorId);
    Buffer[4] = (UINT8)(DeviceMap->SmbusDeviceUdid.DeviceId >> 8);
    Buffer[5] = (UINT8)(DeviceMap->SmbusDeviceUdid.DeviceId);
    Buffer[6] = (UINT8)(DeviceMap->SmbusDeviceUdid.Interface >> 8);
    Buffer[7] = (UINT8)(DeviceMap->SmbusDeviceUdid.Interface);
    Buffer[8] = (UINT8)(DeviceMap->SmbusDeviceUdid.SubsystemVendorId >> 8);
    Buffer[9] = (UINT8)(DeviceMap->SmbusDeviceUdid.SubsystemVendorId);
    Buffer[10] = (UINT8)(DeviceMap->SmbusDeviceUdid.SubsystemDeviceId >> 8);
    Buffer[11] = (UINT8)(DeviceMap->SmbusDeviceUdid.SubsystemDeviceId);
    Buffer[12] = (UINT8)(DeviceMap->SmbusDeviceUdid.VendorSpecificId >> 24);
    Buffer[13] = (UINT8)(DeviceMap->SmbusDeviceUdid.VendorSpecificId >> 16);
    Buffer[14] = (UINT8)(DeviceMap->SmbusDeviceUdid.VendorSpecificId >> 8);
    Buffer[15] = (UINT8)(DeviceMap->SmbusDeviceUdid.VendorSpecificId);
    Buffer[16] = (UINT8)(DeviceMap->SmbusDeviceAddress.SmbusDeviceAddress << 1);
}

/**
    This function converts UINT8[] buffer into EFI_SMBUS_DEVICE_MAP structure

    @param DeviceMap pointer to structure to convert to
    @param Buffer pointer buffer to convert from

    @retval VOID

**/
VOID ConvertBufferToMap (
    OUT EFI_SMBUS_DEVICE_MAP *DeviceMap,
    IN UINT8                 *Buffer
    )
{
    DeviceMap->SmbusDeviceUdid.DeviceCapabilities = Buffer[0];
    DeviceMap->SmbusDeviceUdid.VendorRevision = Buffer[1];
    DeviceMap->SmbusDeviceUdid.VendorId = (UINT16)((Buffer[2] << 8) + Buffer[3]);
    DeviceMap->SmbusDeviceUdid.DeviceId = (UINT16)((Buffer[4] << 8) + Buffer[5]);
    DeviceMap->SmbusDeviceUdid.Interface = (UINT16)((Buffer[6] << 8) + Buffer[7]);
    DeviceMap->SmbusDeviceUdid.SubsystemVendorId = (UINT16)((Buffer[8] << 8) + Buffer[9]);
    DeviceMap->SmbusDeviceUdid.SubsystemDeviceId = (UINT16)((Buffer[10] << 8) + Buffer[11]);
    DeviceMap->SmbusDeviceUdid.VendorSpecificId = (UINT32)((Buffer[12] << 24) + (Buffer[13] << 16) + (Buffer[14] << 8) + Buffer[15]);
    DeviceMap->SmbusDeviceAddress.SmbusDeviceAddress = (UINT8)(Buffer[16] >> 1);
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
