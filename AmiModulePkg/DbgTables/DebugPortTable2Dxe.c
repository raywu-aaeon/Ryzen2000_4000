//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2019, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file DebugPortTable2Dxe.c
    Entry point for Debug Port Table 2 module initialization.

**/

//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------

#include "DebugPortTable2.h"
#include <Library/AmiDebugPortTablesLib.h>

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)
static VOID *gDebugPortTable2;

// GUID Definition(s)

// Protocol Definition(s)

// External Declaration(s)
extern EFI_ACPI_SUPPORT_PROTOCOL *gAcpiSupport;
extern UINT8    gAcpiOemId[];     //"ALASKA";  //add 0 at the end.OemId 6 bytes
extern UINT8    gAcpiOemTblId[]; //"A M I";  //add 0 at the end.OemTableId  8 bytes
// Function Definition(s)

//---------------------------------------------------------------------------     

/**
  Setting the default DBGP ACPI header data.

  @param[in]  DbgPortTable2  Point to DbgPortTable2.

  @retval  EFI_SUCCESS  The constructor always returns EFI_SUCCESS.

**/
EFI_STATUS
SetupDbg2HeaderData (
  IN DBG_PORT_2_TABLE *DbgPortTable2
  )
{
    DbgPortTable2->AcpiHeader.Signature = DBG2_SIG;
    DbgPortTable2->AcpiHeader.Length = sizeof(DBG_PORT_2_TABLE);
    DbgPortTable2->AcpiHeader.Revision = 0x0;
    DbgPortTable2->AcpiHeader.Checksum = 0x00;
    DbgPortTable2->AcpiHeader.OemRev = ACPI_OEM_REV;
    DbgPortTable2->AcpiHeader.CreatorId = CREATOR_ID_MS;
    DbgPortTable2->AcpiHeader.CreatorRev = CREATOR_REV_MS;

    //
    // Update OEM ID.
    //
    gBS->CopyMem(((UINT8 *)(DbgPortTable2->AcpiHeader.OemId)), gAcpiOemId , sizeof((DbgPortTable2->AcpiHeader.OemId)));
    gBS->CopyMem(((UINT8 *)(DbgPortTable2->AcpiHeader.OemTblId)), gAcpiOemTblId , sizeof((DbgPortTable2->AcpiHeader.OemTblId)));

    return EFI_SUCCESS;
}

/**
  Event feature, publish DBGP table at ready to boot process.

  @param[in]  Event                 Event whose notification function is being invoked.
  @param[in]  Context               The pointer to the notification function's context,
                                    which is implementation-dependent.

**/
VOID
EFIAPI
Dbg2TableInstallCallback (
  IN EFI_EVENT Event,
  IN VOID *Context
  )
{
    EFI_STATUS          Status;
    UINTN               TblHandle = 0;
    DBG_PORT_2_TABLE    *DebugPortTable2;

    if (gAcpiSupport == NULL) {
        Status = gBS->LocateProtocol (&gEfiAcpiSupportProtocolGuid, NULL, (VOID**) &gAcpiSupport);

        if (EFI_ERROR (Status)) return ;
    }

    Status = gBS->AllocatePool (EfiBootServicesData, sizeof(DBG_PORT_2_TABLE), (VOID **) &DebugPortTable2);
    ASSERT_EFI_ERROR (Status);
    if (EFI_ERROR (Status)) return;
    gBS->SetMem((VOID*)DebugPortTable2,sizeof(DBG_PORT_2_TABLE), 0);

    //Fill ACPI Header
    Status = SetupDbg2HeaderData(DebugPortTable2);
    DEBUG((DEBUG_INFO,"Dbg : Fill ACPI Header %r \n", Status));
    
    //Fill Debug Device information 
    gDebugPortTable2 = SetupDebugDeviceInformationData(DebugPortTable2);
    gBS->FreePool((VOID*)DebugPortTable2);

    Status = gAcpiSupport->SetAcpiTable (gAcpiSupport,
                                gDebugPortTable2, TRUE, 
                                EFI_ACPI_TABLE_VERSION_ALL,
                                &TblHandle
                                );
    DEBUG((DEBUG_INFO,"Dbg : Install DBG2 tbl %r \n", Status));
    ASSERT_EFI_ERROR(Status);

    gBS->FreePool(gDebugPortTable2);
    gBS->CloseEvent(Event);

    return ;
}

/**
  Entry point of the DBG2 driver. Locate ACPI support protocol.
  Call SetupAcpiHeaderData and filled Interface type field and Base Address field. 

  @retval  EFI_SUCCESS  DBGP table install successfully.
**/
EFI_STATUS
EFIAPI
DebugPortTable2Dxe(
  VOID
  )
{
    EFI_STATUS  Status;
    EFI_EVENT   Event;
    VOID        *Registration;
    //
    // Add DBGP Table at ready to boot process.
    //
    Status = gBS->CreateEvent(
                EVT_NOTIFY_SIGNAL,
                TPL_NOTIFY,
                Dbg2TableInstallCallback,
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

    return Status;
}

//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2019, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
