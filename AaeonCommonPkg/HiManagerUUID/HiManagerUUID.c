#include <Efi.h>
#include <Token.h>
#include <AMIDxeLib.h>
#include <AMICSPLIBInc.h>

#include <Protocol\SMBios.h>
#include <Protocol\AmiSmbios.h>
#include <Protocol\SmbiosDynamicData.h>

#include "HiManagerUUID.h"

#ifndef PCI_BAR0
#define PCI_BAR0            0x0010        // Base Address Register 0
#endif

extern MemRead32(IN UINT32 *Address);     //Vaquero+ Fix compiler 

#define BDS_ALL_DRIVERS_CONNECTED_PROTOCOL_GUID \
    {0xdbc9fd21, 0xfad8, 0x45b0, 0x9e, 0x78, 0x27, 0x15, 0x88, 0x67, 0xcc, 0x93}

EFI_GUID BdsAllDriversConnectedProtocolGuid = BDS_ALL_DRIVERS_CONNECTED_PROTOCOL_GUID;

//----------------------------------------------------------------------------
// Procedure:   GenerateAmtUuid
//
// Description: Generate AMT UUID. Data will be as following -
//		{Param[0]Param[1]--Param[3]--Param[4]--Param[5]--MAC}
//
// Input:       Pointer to buffer for saving generated AMT UUID
//
// Output:     Generated AMT UUID in given buffer
//
// Modified:
//
// Notes:
//----------------------------------------------------------------------------
EFI_STATUS
GenerateAmtUuid(
	IN OUT EFI_GUID	*AmtUuid
)
{
   CHAR8 AAEON_SIGNATURE1[] = {0x22, 0x34, 0x03, 0x98, "AAEON Technology Inc."};
   CHAR8 PRODUCT_NAME[] = CONVERT_TO_STRING(UUID_SYSTEM_PRODUCT_NAME);	// = 'Prduct_name', 0x00...   0x00: End of string.
   CHAR8 AAEON_SIGNATURE2[sizeof(PRODUCT_NAME)+1];	// Add some chars in case that product name is too short.
   UINT16 Param[5];	// ParamA~E
   EFI_PHYSICAL_ADDRESS		GbeTempMmio;
   UINT8 *GbeMacPtr , k;
   UINTN i, j;
   AMT_UUID	TempAmtUuid;
   UINT8 *SrcPtr, *DesPtr;
   UINT32 Data32;
   UINT8 RegOffset4TempValue;
    
   //Patch: Enable PCH LAN IO Memory Space temporarily or it won't get MAC value 
   RegOffset4TempValue = READ_PCI8(REF_LAN_BUS, REF_LAN_DEV, REF_LAN_FUN, 0x04);
   WRITE_PCI8(REF_LAN_BUS, REF_LAN_DEV, REF_LAN_FUN, 0x04 , RegOffset4TempValue | 0x02);
   
   GbeTempMmio = READ_PCI32(REF_LAN_BUS, REF_LAN_DEV, REF_LAN_FUN, PCI_BAR0);
	
   // Get GbE mac from GbE MMIO
   GbeMacPtr = (UINT8 *)GbeTempMmio;
   GbeMacPtr += 0x40;
// Use DWORD access for MMIO to avoid unexpected result
//   MemCpy(&(TempAmtUuid.MAC), (VOID *)GbeMacPtr, 6);
   Data32 = MemRead32((UINT32*)GbeMacPtr);
   MemCpy(&(TempAmtUuid.MAC), (UINT8 *)&Data32, 4);
   GbeMacPtr += 4;
   Data32 = MemRead32((UINT32*)GbeMacPtr);
   MemCpy(&(TempAmtUuid.MAC[4]), (UINT8 *)&Data32, 2);
   
   TRACE((-1, "GenerateAmtUuid:Get LAN B%02X/D%02X/F%02X MAC=%02X-%02X-%02X-%02X-%02X-%02X\n", \
		   REF_LAN_BUS, REF_LAN_DEV, REF_LAN_FUN, \
		   TempAmtUuid.MAC[0], TempAmtUuid.MAC[1], TempAmtUuid.MAC[2], TempAmtUuid.MAC[3], TempAmtUuid.MAC[4], TempAmtUuid.MAC[5]
		   ));

   if (TempAmtUuid.MAC[0] == 0xFF)
       return EFI_NOT_READY;
   
   //Restore Register Offset 04 Value.
   WRITE_PCI8(REF_LAN_BUS, REF_LAN_DEV, REF_LAN_FUN, 0x04 , RegOffset4TempValue);

// Preparing ParamA~F.
// ParamA: Pick two bytes from MAC, according to MAC[5]
// ParamB: Pick two bytes from MAC, according to MAC[4]
// ParamC: Pick two bytes from MAC, according to MAC[3]
// ParamD: Pick two bytes from MAC, according to MAC[2]
// ParamE: Pick two bytes from MAC, according to MAC[1]
   for (j=0;j<5;j++)
   {
	i = TempAmtUuid.MAC[(j+1)]%5;
	Param[j] = ((UINT32)TempAmtUuid.MAC[i]+1) * ((UINT32)TempAmtUuid.MAC[(i+1)]+1);		// Add 1 for avoid mutiplying 0
   }

// Add calculated AAEON Signage into ParamA~F
// Pick 5 chars from AAEON_SIGNATURE1
   i = Param[4] % (sizeof(AAEON_SIGNATURE1)-5);

   // Pick 5 chars from AAEON_SIGNATURE2
   for (k=0;k<sizeof(PRODUCT_NAME);k++)
       AAEON_SIGNATURE2[k+1] = PRODUCT_NAME[k];

   AAEON_SIGNATURE2[0] = 0x5F;					// add '_'
   AAEON_SIGNATURE2[(sizeof(AAEON_SIGNATURE2)-1)] = 0x5F;	// replace 0x00 as '_'

   j = Param[4] % (sizeof(AAEON_SIGNATURE2)-4);
	
// Add picked AAEON_SIGNATURE1, and AAEON_SIGNATURE2, to ParamA~F... one by one
   for (k=0;k<5;k++)
       Param[k]+= (AAEON_SIGNATURE1[i+k] + AAEON_SIGNATURE2[j+k]);

// Finalize AMT UUID
   Param[0] = (Param[0] << 8) | (Param[0] >> 8);
   Param[1] = (Param[1] << 8) | (Param[1] >> 8);
   Param[2] = (Param[2] << 8) | (Param[2] >> 8);
   Param[3] = (Param[3] << 8) | (Param[3] >> 8);
   Param[4] = (Param[4] << 8) | (Param[4] >> 8);
	
// Calculate segment1
// ParamA appended with ParamB
   TempAmtUuid.Segment1 = (UINT32)(Param[1] << 16) + (UINT32) Param[0];

// Calculate segment2
   TempAmtUuid.Segment2 = Param[2];

// Calculate segment3
   TempAmtUuid.Segment3 = Param[3];

// Calculate segment4
   TempAmtUuid.Segment4 = Param[4];

// Generate AMT UUID
   SrcPtr = (UINT8 *)&TempAmtUuid;
   DesPtr = (UINT8 *)AmtUuid;

   MemCpy((VOID*)DesPtr, (VOID*)SrcPtr, 16);

   return EFI_SUCCESS;
}

VOID UpdateHiManagerUUID(EFI_EVENT Event, VOID *Context)
{
   EFI_GUID	    	AmtUuid;
   EFI_STATUS      	Status;
   UINT8           	*Buffer;
   UINT16          	BSize, Handle;
   AMI_SMBIOS_PROTOCOL  *gAmiSmbiosProtocol;

   Status = pBS->LocateProtocol(&gAmiSmbiosProtocolGuid, NULL, &gAmiSmbiosProtocol);
   if (EFI_ERROR(Status))
	return;

   // Read System structure
   Status = gAmiSmbiosProtocol->SmbiosReadStrucByType(1, 1, &Buffer, &BSize);
   if (EFI_ERROR(Status))
	return;

   // Update UUID and write it back, overwriting old data
   Status = GenerateAmtUuid(&AmtUuid);
   if (EFI_ERROR(Status))
	   return;

   MemCpy( &(((SMBIOS_SYSTEM_INFO*)Buffer)->Uuid), &AmtUuid, sizeof(EFI_GUID) );
   Handle = ((SMBIOS_STRUCTURE_HEADER*)Buffer)->Handle;
   Status = gAmiSmbiosProtocol->SmbiosWriteStructure(Handle, Buffer, BSize);

   // Free memory allocated by the earlier gSmbiosProtocol->SmbiosReadStrucByType call
   pBS->FreePool(Buffer);
   
   pBS->CloseEvent(Event);
}

EFI_STATUS HiManagerUUIDEntryPoint(
    EFI_HANDLE          ImageHandle,
    EFI_SYSTEM_TABLE    *SystemTable )
{
   EFI_STATUS Status = EFI_SUCCESS;
   EFI_EVENT	Event;
   VOID	 	*SmbiosBoardCallbackRegistration;

   InitAmiLib(ImageHandle, SystemTable);
	     
   Status = RegisterProtocolCallback(
				&BdsAllDriversConnectedProtocolGuid,
				UpdateHiManagerUUID,
				NULL,
				&Event, 
				&SmbiosBoardCallbackRegistration );

   if (EFI_ERROR(Status))
	return Status;

   return EFI_SUCCESS;
}
