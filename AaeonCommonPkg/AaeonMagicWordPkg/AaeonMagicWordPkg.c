#include <Token.h>
#include <AmiLib.h>
#include <AmiCspLib.h>
#include <EFI.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol\LegacyRegion2.h>

//VOID RayDebug80(UINT8 Time, UINT8 Code){
//	UINTN i;
//	
//	i = 0x0FFFF | (Time << 16);
//	while(i != 0){
//		IoWrite8(0x80, Code);
//		i--;
//	}
//}

VOID AAEONMagicWordInit(VOID)
{
	EFI_STATUS Status;

	// Code reference from TcgLegacy.c
	EFI_LEGACY_REGION2_PROTOCOL * iRegion;
	UINT32					Granularity;

	CHAR8 MagicWord_buffer[] = {0x22, 0x34, 0x03, 0x98, CONVERT_TO_STRING(AAEON_Signature1)};
	UINT32 MagicWordAddress = AAEON_Signature1_Address;
	CHAR8 MagicWord2_buffer[] = CONVERT_TO_STRING(AAEON_Signature2);
	UINT32 MagicWord2Address = AAEON_Signature2_Address;

	// Code reference from TcgLegacy.c
	Status = gBS->LocateProtocol( &gEfiLegacyRegion2ProtocolGuid, NULL, &iRegion );
	if(EFI_ERROR(Status))
		return;	// Some debug message should be added in future

	Status = iRegion->UnLock( iRegion, 0xE0000, 0x20000,  &Granularity);
	if(EFI_ERROR(Status))
		return;	// Some debug message should be added in future
	pBS->CopyMem((VOID*)MagicWordAddress, MagicWord_buffer, sizeof (MagicWord_buffer) );
	pBS->CopyMem((VOID*)MagicWord2Address, MagicWord2_buffer, sizeof (MagicWord2_buffer) ); 
	iRegion->Lock( iRegion, 0xE0000, 0x20000, &Granularity );
}
