//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------

#include <AmiCspLib.h>
#include <token.h>
#include "AaeonCommonPkg\PTN3460Cfg\PTN3460Cfg.h"

// Produced Protocols

// Consumed Protocols
#ifdef PEI_BUILD
#include <Ppi/Smbus2.h>
#endif

#ifdef DXE_BUILD
#include <AmiDxeLib.h>
#include <Protocol\SmbusHc.h>
#include <Protocol\S3SaveState.h>
#endif

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)

// GUID Definition(s)

// Protocol Definition(s)

// External Declaration(s)
#ifdef PEI_BUILD
EFI_PEI_SMBUS2_PPI	 *gSmBus2Ppi;
#endif
#ifdef DXE_BUILD
extern EFI_S3_SAVE_STATE_PROTOCOL  *gBootScriptSave;
extern EFI_SMBUS_HC_PROTOCOL *gSmbusProtocol;
#endif

// Function Definition(s)

//---------------------------------------------------------------------------
void CfgAd5247_2E(AAEON_PTN3460_CFG *CfgPanel)
{
    EFI_STATUS Status = EFI_SUCCESS;
	EFI_SMBUS_DEVICE_ADDRESS	SlaveAddr;
	UINTN Length = 1;
    UINT8 data = 0;

    if (CfgPanel->Enabled == 0)
    {
        return;
    }

    DEBUG((DEBUG_INFO, "[PTN3460] Entering CfgPanel1Ad5247\n"));
    data = (CfgPanel->BacklightType == 0) ? 
        (CfgPanel->BacklightLv == 10 ? 0x7F : 12 * CfgPanel->BacklightLv):
        (CfgPanel->BacklightLv == 0 ? 0x7F : 12 * (10 - CfgPanel->BacklightLv));

    SlaveAddr.SmbusDeviceAddress = 0x2E;
#ifdef PEI_BUILD
    Status = gSmBus2Ppi->Execute(gSmBus2Ppi, SlaveAddr, 0x00, EfiSmbusWriteByte, 0x00, &Length, &data);
#endif
#ifdef DXE_BUILD
    Status = gSmbusProtocol->Execute(gSmbusProtocol, SlaveAddr, 0x00, EfiSmbusWriteByte, FALSE, &Length, &data);
#endif
    DEBUG((DEBUG_INFO, "  Write AD5247@0x%02X = %r\n", SlaveAddr.SmbusDeviceAddress, Status));
	
	return;
}

#if (PTN3460_SUPPORT_NUMBER == 2)
void CfgAd5247_17(AAEON_PTN3460_CFG *CfgPanel)
{
    EFI_STATUS Status = EFI_SUCCESS;
	EFI_SMBUS_DEVICE_ADDRESS	SlaveAddr;
    UINTN Length = 1;
    UINT8 data = 0;
      
    if (CfgPanel->Enabled == 0)
    {
        return;
    }

    data = (CfgPanel->BacklightType == 0) ? 
        (CfgPanel->BacklightLv == 10 ? 0x7F : 12 * CfgPanel->BacklightLv):
        (CfgPanel->BacklightLv == 0 ? 0x7F : 12 * (10 - CfgPanel->BacklightLv));

    SlaveAddr.SmbusDeviceAddress = 0x17;
#ifdef PEI_BUILD
    Status = gSmBus2Ppi->Execute(gSmBus2Ppi, SlaveAddr, 0x00, EfiSmbusWriteByte, 0x00, &Length, &data);
#endif
#ifdef DXE_BUILD
    Status = gSmbusProtocol->Execute(gSmbusProtocol, SlaveAddr, 0x00, EfiSmbusWriteByte, FALSE, &Length, &data);
#endif
    DEBUG((DEBUG_INFO, "  Write AD5247@0x%02X = %r\n", SlaveAddr.SmbusDeviceAddress, Status));
    return;
}
#endif
