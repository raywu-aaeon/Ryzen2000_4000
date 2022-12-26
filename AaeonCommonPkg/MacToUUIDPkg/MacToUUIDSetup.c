//-------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------
#include <AmiDxeLib.h>
#include <Setup.h>
#include <AutoId.h>
#include <TimeStamp.h>
#include <Protocol/AmiSmbios.h>			

#define STR CONVERT_TO_WSTRING

VOID AAInitString(EFI_HII_HANDLE HiiHandle, STRING_REF StrRef, CHAR16 *sFormat, ...)
{
    CHAR16 s[1024];
    VA_LIST  ArgList;
    VA_START(ArgList,sFormat);
    Swprintf_s_va_list(s,sizeof(s),sFormat,ArgList);
    VA_END(ArgList);
    HiiLibSetString(HiiHandle, StrRef, s);
}


VOID AaeonInitSetupStrings(
    IN    EFI_HII_HANDLE HiiHandle,
    IN    UINT16         Class)
{

	UINT16	i=0;
	AMI_SMBIOS_PROTOCOL *gAmiSmbiosProtocol;
	EFI_GUID            gAmiSmbiosProtocolGuid = AMI_SMBIOS_PROTOCOL_GUID;
	EFI_STATUS  		Status;
	UINT8				*Type1Data = NULL;
	UINT16				Type1DataSize;
	UINT8				*Type1DataPtr;
	// only first 4 strings we interest.
	UINT8				*Type1StrPtr[4] = {NULL, NULL, NULL, NULL};

	
	TRACE((-1, "AaeonInitSetupStrings start\n"));


        Status = pBS->LocateProtocol(&gAmiSmbiosProtocolGuid, NULL, &gAmiSmbiosProtocol);
    	ASSERT_EFI_ERROR(Status);
    	if (Status == EFI_SUCCESS) 
    	{
    		//find interested string
    		Status = gAmiSmbiosProtocol->SmbiosReadStrucByType(1, 1, &Type1Data, &Type1DataSize);		
    		ASSERT_EFI_ERROR(Status);
   		
            Type1DataPtr = Type1Data + sizeof(SMBIOS_SYSTEM_INFO);  //start of string area
    		for (i = 0; i < 4; i++)
    		{
    			if (Strlen(Type1StrPtr[i]) != 0)
    			{
    				Type1StrPtr[i] = Type1DataPtr;
    				Type1DataPtr += Strlen(Type1StrPtr[i])+1;	// to next string
    			} else                   
    				break;
    		}

    		// Update string
    		// UUID
            Type1DataPtr = Type1Data + ((UINT8 *)&(((SMBIOS_SYSTEM_INFO *) Type1Data)->Uuid) - (UINT8 *)&(((SMBIOS_SYSTEM_INFO *) Type1Data)->StructureType));
            TRACE((-1, "Get UUID - %02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X\n",
    				Type1DataPtr[0], Type1DataPtr[1], Type1DataPtr[2], Type1DataPtr[3], 
    				Type1DataPtr[4], Type1DataPtr[5], Type1DataPtr[6], Type1DataPtr[7], 
    				Type1DataPtr[8], Type1DataPtr[9], Type1DataPtr[10], Type1DataPtr[11], 
    				Type1DataPtr[12], Type1DataPtr[13], Type1DataPtr[14], Type1DataPtr[15]		
    		));
    		AAInitString(HiiHandle,STRING_TOKEN(AAEON_STR_SMBIOS_SYS_UUID_VAL), 
    				L"    %02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X",
    				Type1DataPtr[0], Type1DataPtr[1], Type1DataPtr[2], Type1DataPtr[3], 
    				Type1DataPtr[4], Type1DataPtr[5], Type1DataPtr[6], Type1DataPtr[7], 
    				Type1DataPtr[8], Type1DataPtr[9], Type1DataPtr[10], Type1DataPtr[11], 
    				Type1DataPtr[12], Type1DataPtr[13], Type1DataPtr[14], Type1DataPtr[15]		
    		);
    	}
    	pBS->FreePool(Type1Data); 
}
