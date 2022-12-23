//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2019, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file GnbEdidOverrideProtocol.c
    Supply a default EdidOverrideProtocol 

*/

//----------------------------------------------------------------------
// Include(s)
//----------------------------------------------------------------------

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Token.h>
#include <Protocol/EdidOverride.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Protocol/DevicePath.h>
#include <Library/DevicePathLib.h>

//----------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//----------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)


// Function Prototype(s)

EFI_STATUS
EFIAPI
GnbEdidOverrideGetEdid (
  IN  EFI_EDID_OVERRIDE_PROTOCOL    *This,
  IN  EFI_HANDLE                    *ChildHandle,
  OUT UINT32                        *Attributes,
  IN OUT UINTN                      *EdidSize,
  IN OUT UINT8                      **Edid
);


//----------------------------------------------------------------------
// Variable and External Declaration(s)
//----------------------------------------------------------------------
// Variable Declaration(s)

// GUID Definition(s)



/**
    Invoke GnbEdidOverrideGetEdid 

    @param *This
    @param *ChildHandle
    @param *Attributes
    @param *EdidSize
    @param ***Edid

    @retval EFI_SUCCESS - Get Oem Override Edid Success.

    @note  None.

**/

EFI_STATUS
EFIAPI
GnbEdidOverrideGetEdid (
  IN      EFI_EDID_OVERRIDE_PROTOCOL  *This,
  IN      EFI_HANDLE                  *ChildHandle,
  OUT     UINT32                      *Attributes,
  IN OUT  UINTN                       *EdidSize,
  IN OUT  UINT8                       **Edid )
{

    EFI_STATUS  Status;
    EFI_DEVICE_PATH_PROTOCOL    *ChildDevPath;
    EFI_DEVICE_PATH_PROTOCOL    *Next;
    UINT8                       *Buffer;
    static UINT8 EdidData[0x80] = {      
            0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x04,0x69,0xFD,0x22,0x03,0x01,0x01,0x01,
            0x12,0x17,0x01,0x03,0x80,0x30,0x1B,0x78,0x2A,0x2A,0xC5,0xA4,0x56,0x4F,0x9E,0x28,
            0x0F,0x50,0x54,0xB7,0xEF,0x00,0xD1,0xC0,0x81,0x40,0x81,0x80,0x95,0x00,0xB3,0x00,
            0x71,0x4F,0x81,0xC0,0x81,0x00,0x02,0x3A,0x80,0x18,0x71,0x38,0x2D,0x40,0x58,0x2C,
            0x45,0x00,0xDC,0x0C,0x11,0x00,0x00,0x1E,0x00,0x00,0x00,0xFF,0x00,0x44,0x34,0x4C,
            0x4D,0x51,0x53,0x31,0x31,0x30,0x31,0x38,0x34,0x0A,0x00,0x00,0x00,0xFD,0x00,0x32,
            0x4B,0x18,0x53,0x11,0x00,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xFC,
            0x00,0x41,0x53,0x55,0x53,0x20,0x56,0x53,0x32,0x32,0x38,0x0A,0x20,0x20,0x01,0x07
    };// Temp EDID table.
 
    Status =  gBS->HandleProtocol (
                     *ChildHandle,
                     &gEfiDevicePathProtocolGuid,
                     (VOID*)&ChildDevPath
                     );
    
    if (!EFI_ERROR(Status)){
        for (Next = ChildDevPath; !IsDevicePathEnd (Next); Next = NextDevicePathNode (Next)) {
            if (DevicePathType (Next) == ACPI_DEVICE_PATH && DevicePathSubType (Next) == ACPI_ADR_DP) {
                DEBUG ((DEBUG_INFO|DEBUG_CHIPSET, "ACPI Adr 0x%x \n", ((ACPI_ADR_DEVICE_PATH *)(Next))->ADR));
                if ((((ACPI_ADR_DEVICE_PATH *)(Next))->ADR) ==  ACPI_DISPLAY_ADR (1, 0, 0, 1, 0, ACPI_ADR_DISPLAY_TYPE_INTERNAL_DIGITAL, 0, 0)){
                    //
                    // porting for LCD
                    //
                    return EFI_UNSUPPORTED;
                }   
                if (((((ACPI_ADR_DEVICE_PATH *)(Next))->ADR)&0xFFFFFF00) ==  ACPI_DISPLAY_ADR (1, 0, 0, 1, 0, ACPI_ADR_DISPLAY_TYPE_EXTERNAL_DIGITAL, 0, 0)){
                    //
                    // porting for DFPx
                    //
                    // It is a sample code.
                    //

                    *EdidSize = sizeof(EdidData);

                    Status = gBS->AllocatePool (
                                  EfiBootServicesData,
                                  sizeof (EdidData),
                                  &Buffer
                                  );

                    if (EFI_ERROR (Status)) return Status;

                    gBS->CopyMem (Buffer, &EdidData, sizeof (EdidData));
                    
                    *Edid = Buffer;
    
                    //EFI_EDID_OVERRIDE_DONT_OVERRIDE != 0
                    //Only use returned override EDID if
                    //the display device has no EDID or the
                    //EDID is incorrect. Otherwise, use the
                    //EDID from the display device

                    *Attributes = EFI_EDID_OVERRIDE_DONT_OVERRIDE;

                    DEBUG ((DEBUG_INFO|DEBUG_CHIPSET, "GnbEdidOverrideGetEdid : Report EDID table and Attributes\n"));
                    
                    return EFI_SUCCESS;
                }
            }
        }
    }

    return EFI_UNSUPPORTED;
}

