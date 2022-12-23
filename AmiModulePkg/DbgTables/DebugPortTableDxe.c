//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2019, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file DebugPortTableDxe.c
    Entry point for Debug Port Table module initialization.

**/

#include "DebugPortTable.h"

//
// Global Variables
//
static DBG_PORT_TABLE       gDebugPortTable;
EFI_ACPI_SUPPORT_PROTOCOL   *gAcpiSupport = NULL;

UINT8 gAcpiOemId[]    = DBG_ACPI_OEM_ID;     //"ALASKA"; //add 0 at the end.OemId 6 bytes
UINT8 gAcpiOemTblId[] = DBG_ACPI_OEM_TBL_ID; //"A M I";  //add 0 at the end.OemTableId  8 byte
  
/**
  Setting the default DBGP ACPI header data.

**/
VOID
SetupDbgpHeaderData (
  VOID
  )
{
    gDebugPortTable.AcpiHeader.Signature = DEBUG_PORT_SIG;
    gDebugPortTable.AcpiHeader.Length = sizeof(DBG_PORT_TABLE);
    gDebugPortTable.AcpiHeader.Revision = 0x1;
    gDebugPortTable.AcpiHeader.Checksum = 0x00;
    gDebugPortTable.AcpiHeader.OemRev = ACPI_OEM_REV;
    gDebugPortTable.AcpiHeader.CreatorId = CREATOR_ID_MS;
    gDebugPortTable.AcpiHeader.CreatorRev = CREATOR_REV_MS;

    //
    // Update OEM ID.
    //
    gBS->CopyMem(((UINT8 *)(gDebugPortTable.AcpiHeader.OemId)), gAcpiOemId , sizeof((gDebugPortTable.AcpiHeader.OemId)));
    gBS->CopyMem(((UINT8 *)(gDebugPortTable.AcpiHeader.OemTblId)), gAcpiOemTblId , sizeof((gDebugPortTable.AcpiHeader.OemTblId)));
}

/**
  Event feature, publish DBGP table at ready to boot process.

  @param[in]  Event                 Event whose notification function is being invoked.
  @param[in]  Context               The pointer to the notification function's context,
                                    which is implementation-dependent.

**/
VOID
EFIAPI
DbgpTableInstallCallback (
  IN EFI_EVENT Event,
  IN VOID *Context
  )
{
    EFI_STATUS  Status;
    UINTN       TblHandle = 0;

    Status = gBS->LocateProtocol (&gEfiAcpiSupportProtocolGuid, NULL, (VOID**) &gAcpiSupport);

    if (EFI_ERROR (Status)) return ;

    Status = gAcpiSupport->SetAcpiTable (gAcpiSupport,
                                        &gDebugPortTable,
                                        TRUE,
                                        EFI_ACPI_TABLE_VERSION_ALL,
                                        &TblHandle
                                        );
    if (EFI_ERROR(Status))
        DEBUG((DEBUG_INFO, "Dbg : Install DBGP tbl %r \n", Status));

    gBS->CloseEvent(Event);
    return ;
}

/**
  Entry point of the DBGP driver. Locate ACPI support protocol.
  Call SetupAcpiHeaderData and filled Interface type field and Base Address field. 

  @param  ImageHandle    The firmware allocated handle for the EFI image.
  @param  SystemTable    A pointer to the EFI System Table.

  @retval  EFI_SUCCESS   DBGP table install successfully.
  @retval  Other         Function executed unsuccessfully.
**/
EFI_STATUS
EFIAPI
DebugPortTableDxeEntryPoint (
  IN EFI_HANDLE ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
    EFI_STATUS  Status;
    EFI_EVENT   Event = NULL;
    VOID        *Registration = NULL;
    EFI_GUID    SetupVariableGuid = SETUP_GUID;
    SETUP_DATA  SetupData;
    UINTN       Size = sizeof(SETUP_DATA);

    Status = gRT->GetVariable(L"Setup", &SetupVariableGuid, NULL, &Size, &SetupData);
    
    if (EFI_ERROR(Status))
        return Status;
    if (SetupData.DBGPEnable) {
        //
        // Fill ACPI Header.
        //
        SetupDbgpHeaderData();

        //
        // Fill DBGP fields.
        //
        gDebugPortTable.InterfaceType = DBGP_INTERFACE_TYPE;
        gDebugPortTable.BaseAddress.AddrSpcID = DBGP_ADDR_SPC_ID;
        gDebugPortTable.BaseAddress.RegBitWidth = DBGP_ADDR_BIT_WIDTH;
        gDebugPortTable.BaseAddress.RegBitOffs = DBGP_ADDR_BIT_OFFSET;
        gDebugPortTable.BaseAddress.AccessSize = DBGP_ACCESS_SIZE;
        gDebugPortTable.BaseAddress.Address = PcdGet64 (PcdSerialRegisterBase);

        DEBUG((DEBUG_INFO,"Dbg1 : DBGP signature [%lx] \n",gDebugPortTable.AcpiHeader.Signature));

        //
        // Add DBGP Table at ready to boot process.
        //
        Status = gBS->CreateEvent(
                    EVT_NOTIFY_SIGNAL,
                    TPL_NOTIFY,
                    DbgpTableInstallCallback,
                    NULL,
                    &Event
                    );

        if (EFI_ERROR(Status)) 
            return Status;

        Status = gBS->RegisterProtocolNotify(
                    &gEfiConsoleControlProtocolGuid,
                    Event,
                    &Registration
                    );
        if (EFI_ERROR(Status))
            return Status;
    }
    //
    // Create DBG2 Table
    //
    if (SetupData.DBG2Enable)
        Status = DebugPortTable2Dxe();
    
    return Status;
}

//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2019, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
