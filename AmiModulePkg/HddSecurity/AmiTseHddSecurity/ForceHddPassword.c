//***********************************************************************
//*                                                                     *
//*                  Copyright (c) 1985-2021, AMI.                      *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file ForceHddPassword.c
    Send Disable Software Preservation command when the 
    FORCE_HDD_PASSWORD_PROMPT token is set to 1

**/

#include <AmiTseHddSecurity.h>

/** @internal
    Send the Disable software Preservation 

    @param VOID

    @return VOID
    @endinternal
**/
VOID
DisableSoftwarePreservation (
)
{
#if FORCE_HDD_PASSWORD_PROMPT
#if ( defined(AHCI_SUPPORT) && (AHCI_SUPPORT != 0) )
    UINTN                    HandleCount;
    EFI_HANDLE              *HandleBuffer;
    UINT8                   i;
    AMI_AHCI_BUS_PROTOCOL   *AhciBusInterface;
    SATA_DEVICE_INTERFACE   *SataDeviceInterface;
    DLINK                   *dlink;
    COMMAND_STRUCTURE       CommandStructure = {0};
    EFI_STATUS              Status;    


    Status = gBS->LocateHandleBuffer (
                                      ByProtocol,
                                      &gAmiAhciBusProtocolGuid,
                                      NULL,
                                      &HandleCount,
                                      &HandleBuffer
                                      );

    if(EFI_ERROR(Status) || HandleCount == 0 ) {
        return;
    }

    //
    // Issue Disable Software Preservation command all the Sata Devices connected.
    //
    for (i = 0; i < HandleCount; i++) {
        Status = gBS->HandleProtocol (HandleBuffer[i], &gAmiAhciBusProtocolGuid, (VOID**)&AhciBusInterface);
        if (!EFI_ERROR(Status)) {
            dlink = AhciBusInterface->SataDeviceList.pHead; 
            if (dlink){ 
                do {
                    SataDeviceInterface = BASE_CR(dlink, SATA_DEVICE_INTERFACE, SataDeviceLink);
 
                    if ((SataDeviceInterface->IdentifyData.Reserved_76_79[0] != 0xFFFF )&&
                        (SataDeviceInterface->IdentifyData.Reserved_76_79[2] & 0x0040)&&           // Software Preservation support
                        (SataDeviceInterface->IdentifyData.Security_Status_128 & 0x0002)&&         // Security enabled
                        (!(SataDeviceInterface->IdentifyData.Security_Status_128 & 0x0004))) {     // Security not locked
 
                            //
                            // Send Disable Software Preservation command.
                            //
                            CommandStructure.Features = DISABLE_SATA2_SOFTPREV;
                            CommandStructure.SectorCount = 6;
                            CommandStructure.Command = SET_FEATURE_COMMAND;
                            Status = AhciBusInterface->ExecuteNonDataCommand(SataDeviceInterface, CommandStructure);
                            ASSERT_EFI_ERROR(Status);
                    }
                    dlink = dlink-> pNext;
                }while (dlink);    
            }
         }
     }
#endif
#endif
    return;
}
