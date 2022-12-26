//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
//----------------------------------------------------------------------
//Include Files
//----------------------------------------------------------------------
#include <AmiDxeLib.h>
#include <AmiCspLib.h>
#include <Token.h>
#include <Setup.h>
#include <Protocol/S3SaveState.h>
#include <Library/AmiSioDxeLib.h>

//extern VOID RayDebug80(UINT8 Time, UINT8 Code);

EFI_STATUS
EFIAPI
F81966OemReadyToBootCallback (
)
{
	EFI_STATUS Status = EFI_SUCCESS;
	EFI_S3_SAVE_STATE_PROTOCOL *s3s;
	EFI_GUID gEfiS3SaveStateProtocolGuid = EFI_S3_SAVE_STATE_PROTOCOL_GUID;
	UINT16	i;
	UINT8	Data8;

	Status = pBS->LocateProtocol(&gEfiS3SaveStateProtocolGuid, NULL, &s3s);

	// Reload LDN BASE ADDRESS
	{
		SioLib_BootScriptIO(F81966_CONFIG_INDEX, F81966_CONFIG_MODE_ENTER_VALUE, s3s);
		SioLib_BootScriptIO(F81966_CONFIG_INDEX, F81966_CONFIG_MODE_ENTER_VALUE, s3s);

		// Reload Hardware Monitor BASE ADDRESS BEGIN >>
		SioLib_BootscriptLdnSel(F81966_CONFIG_INDEX, F81966_CONFIG_DATA, \
						F81966_LDN_SEL_REGISTER, F81966_LDN_HWM, s3s);

		SioLib_BootScriptIO(F81966_CONFIG_INDEX, F81966_BASE1_HI_REGISTER, s3s);
		SioLib_BootScriptIO(F81966_CONFIG_DATA, (F81966_HWM_BASE_ADDRESS >> 8), s3s);

		SioLib_BootScriptIO(F81966_CONFIG_INDEX, F81966_BASE1_LO_REGISTER, s3s);
		SioLib_BootScriptIO(F81966_CONFIG_DATA, (F81966_HWM_BASE_ADDRESS & 0x00FF), s3s);
		// Reload Hardware Monitor BASE ADDRESS END <<

		// Reload GPIO BASE ADDRESS BEGIN >>
		SioLib_BootscriptLdnSel(F81966_CONFIG_INDEX, F81966_CONFIG_DATA, \
						F81966_LDN_SEL_REGISTER, F81966_LDN_GPIO, s3s);

		SioLib_BootScriptIO(F81966_CONFIG_INDEX, F81966_BASE1_HI_REGISTER, s3s);
		SioLib_BootScriptIO(F81966_CONFIG_DATA, (F81966_GPIO_BASE_ADDRESS >> 8), s3s);

		SioLib_BootScriptIO(F81966_CONFIG_INDEX, F81966_BASE1_LO_REGISTER, s3s);
		SioLib_BootScriptIO(F81966_CONFIG_DATA, (F81966_GPIO_BASE_ADDRESS & 0x00FF), s3s);
		// Reload GPIO BASE ADDRESS END <<

		SioLib_BootScriptIO(F81966_CONFIG_INDEX, F81966_CONFIG_MODE_EXIT_VALUE, s3s);
	}
	// Hardware Monitor S3 Resume Save BEGIN >>
	{	
	    // Save only 0x00~0xCF because register offset larger than 0xCF are all reserved and are not described in datasheet.
	    // Fintek FAE suggest us not to write 0xFA for preventing HWM reset. Refer to http://biosbt.aaeon.com.tw/wikie/index.php/HWM_value_be_cleared_when_get_into_OS for more detail.
		for(i = 0; i < 0xCF; i++)
		{
			IoWrite8(F81966_HWM_INDEX_PORT, (UINT8)i);
			Data8 = IoRead8(F81966_HWM_DATA_PORT);
			SioLib_BootScriptIO(F81966_HWM_INDEX_PORT, (UINT8)i, s3s);
			SioLib_BootScriptIO(F81966_HWM_DATA_PORT, Data8, s3s);
		}
	}
	// Hardware Monitor S3 Resume Save END <<

	// GPIO S3 Resume Save BEGIN >>
	{
		SioLib_BootScriptIO(F81966_CONFIG_INDEX, F81966_CONFIG_MODE_ENTER_VALUE, s3s);
		SioLib_BootScriptIO(F81966_CONFIG_INDEX, F81966_CONFIG_MODE_ENTER_VALUE, s3s);

		SioLib_BootScriptIO(F81966_CONFIG_INDEX, F81966_CONFIG_MODE_EXIT_VALUE, s3s);
	}
	// GPIO S3 Resume Save END <<

	return Status;
}
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************