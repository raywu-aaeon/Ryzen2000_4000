#include <Efi.h>
#include <Token.h>
#include <AMIDxeLib.h>
#include <AMICSPLIBInc.h>

#include <Protocol\SMBios.h>
#include <Protocol\AmiSmbios.h>
#include <Protocol\SmbiosDynamicData.h>
#include <PciBus.h>                    

#include "MacToUUID.h"

#ifndef PCI_BAR0
#define PCI_BAR0            0x0010        // Base Address Register 0
#endif


typedef struct
{
    UINT8 BUS;
    UINT8 Dev;
    UINT8 Fun;
}PciBDF;



#define BDS_ALL_DRIVERS_CONNECTED_PROTOCOL_GUID \
    {0xdbc9fd21, 0xfad8, 0x45b0, 0x9e, 0x78, 0x27, 0x15, 0x88, 0x67, 0xcc, 0x93}

EFI_GUID BdsAllDriversConnectedProtocolGuid = BDS_ALL_DRIVERS_CONNECTED_PROTOCOL_GUID;



//----------------------------------------------------------------------------
// Procedure:   GetLanBDF
//
// Description: Get Lan BDF if not SOC Lan
//		
//
// Input:     Pointer to buffer for saving generated Lan Bus/Dev/Fun
//
// Output:     Lan Bus/Dev/Fun in given buffer
//
// Modified:
//
// Notes:
//----------------------------------------------------------------------------
#if defined(SOC_LAN) && (SOC_LAN == 0)
EFI_STATUS
GetLanBDF(IN OUT PciBDF *LanBDF)
{
	
	UINT8	  SecBus, SubBus, BusNum, DevNum, DevFun;
	UINT32    VidDid;
	BOOLEAN     DeviceGetFlag=FALSE;
	SecBus = READ_PCI8(Lan_UPPER_STREAM_PORT_BUS_NUM,Lan_UPPER_STREAM_PORT_DEV_NUM,Lan_UPPER_STREAM_PORT_FUN_NUM,PCI_SBUS);
	SubBus = READ_PCI8(Lan_UPPER_STREAM_PORT_BUS_NUM,Lan_UPPER_STREAM_PORT_DEV_NUM,Lan_UPPER_STREAM_PORT_FUN_NUM,PCI_SUBUS);
	for (BusNum=SecBus; BusNum<=SubBus; BusNum++)
	{	   
	   for (DevNum = 0; DevNum < 32; DevNum++)  //Device max number is 31
	   {	
		for (DevFun = 0; DevFun < 8; DevFun++)  //Function max is 7
		{
		     VidDid=READ_PCI32(BusNum,DevNum,DevFun,0);
		     if(VidDid == LanVidDid)
		     {
			     DeviceGetFlag=TRUE;   //Yes, we get Lan:Bus Dev Fun Number
				break;   //Exit DevFun Loop
		     }
		}
		 if(DeviceGetFlag==TRUE)
			 break;   //Exit DevNum Loop
		
	    }
		 if(DeviceGetFlag==TRUE)
			 break; //Exit Bus Loop
	}
	if (DeviceGetFlag == FALSE)
	    return EFI_NOT_FOUND;
	    
	LanBDF->BUS = BusNum;
	LanBDF->Dev = DevNum;
	LanBDF->Fun = DevFun;
	
	return EFI_SUCCESS;
}
#endif
//----------------------------------------------------------------------------
// Procedure:   GetLanMmioBase
//
// Description: Get Lan Mmio Base which store MAC address.
//		
//
// Input:       Pointer to buffer for saving generated Lan MmioBase
//
// Output:      Lan MmioBase in given buffer
//
// Modified:
//
// Notes:
//----------------------------------------------------------------------------
EFI_STATUS
GetLanMmioBase(IN OUT EFI_PHYSICAL_ADDRESS *LanMmioBase)
{
	UINT8                 Cmd;
	EFI_STATUS           Status;
	
#if defined(SOC_LAN) && (SOC_LAN == 1)
	Cmd = READ_PCI32(REF_LAN_BUS, REF_LAN_DEV, REF_LAN_FUN, PCI_CMD); //Make Sure MEM/IO Sapce is enable
	Cmd |= (PCI_CMD_IO_SPACE + PCI_CMD_MEMORY_SPACE);
	WRITE_PCI8(REF_LAN_BUS, REF_LAN_DEV, REF_LAN_FUN, PCI_CMD,Cmd);
	LanMmioBase = READ_PCI32(REF_LAN_BUS, REF_LAN_DEV, REF_LAN_FUN, PCI_BAR_REG);
#else
	
	PciBDF     LanBDF;	
	Status = GetLanBDF(&LanBDF);
	
	if (EFI_ERROR(Status))
	    return Status;
	   
	Cmd = READ_PCI8(LanBDF.BUS, LanBDF.Dev, LanBDF.Fun, PCI_CMD);  //Make Sure MEM/IO Sapce is enable
	Cmd |= (PCI_CMD_IO_SPACE + PCI_CMD_MEMORY_SPACE);
	WRITE_PCI8(LanBDF.BUS,LanBDF.Dev,LanBDF.Fun,PCI_CMD,Cmd);
	*LanMmioBase = READ_PCI32(LanBDF.BUS, LanBDF.Dev, LanBDF.Fun, PCI_BAR_REG);	
#endif
	
   return EFI_SUCCESS;
}



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
   EFI_STATUS           Status;

  Status = GetLanMmioBase(&GbeTempMmio);
  if (EFI_ERROR(Status))
      return Status;
  
  GbeTempMmio &= ~(0x0F);  //Mask off Bit0~Bit3 
  TRACE((-1, "GbeTempMmio = 0x%x\n",GbeTempMmio ));
    
   // Get GbE mac from GbE MMIO
   GbeMacPtr = (UINT8 *)(GbeTempMmio + MAC_OFFSET);
   
   MemCpy(&(TempAmtUuid.MAC), (VOID *)GbeMacPtr, 6);

   TRACE((-1, "GenerateAmtUuid: MAC=%02X-%02X-%02X-%02X-%02X-%02X\n", \
           TempAmtUuid.MAC[0], TempAmtUuid.MAC[1], TempAmtUuid.MAC[2], TempAmtUuid.MAC[3], TempAmtUuid.MAC[4], TempAmtUuid.MAC[5]
           ));
   
   if (TempAmtUuid.MAC[0] == 0xFF)
	   return EFI_NOT_READY;

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

VOID UpdateMacToUUID(EFI_EVENT Event, VOID *Context)
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

EFI_STATUS MacToUUIDEntryPoint(
    EFI_HANDLE          ImageHandle,
    EFI_SYSTEM_TABLE    *SystemTable )
{
   EFI_STATUS Status = EFI_SUCCESS;
   EFI_EVENT	Event;
   VOID	 	*SmbiosBoardCallbackRegistration;

   InitAmiLib(ImageHandle, SystemTable);
	     
   Status = RegisterProtocolCallback(
				&BdsAllDriversConnectedProtocolGuid,
				UpdateMacToUUID,
				NULL,
				&Event, 
				&SmbiosBoardCallbackRegistration );

   if (EFI_ERROR(Status))
	return Status;

   return EFI_SUCCESS;
}
