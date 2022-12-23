//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

/** @file SdioBbs.c
 
    Create BBS table for each Sdio mass storage device.

**/

#include <Protocol/SdioInt13Protocol.h>
#include <Library/UefiBootServicesTableLib.h>

/**
  Create BBS table for each Sdio mass storage device.
    
  @Param   VOID
  
  @return  VOID

**/
VOID
CollectSdioBbsDevices (
    VOID
)
{
    EFI_STATUS  Status;
    EFI_SDIO_PROTOCOL         *AmiSdio;

    Status =  gBS->LocateProtocol(&gEfiSdioProtocolGuid, NULL, (VOID **) &AmiSdio);
    if (EFI_ERROR(Status)) {
        return;
    }
    
    AmiSdio->InstallSdioLegacyBootDevices();
}

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2017, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
