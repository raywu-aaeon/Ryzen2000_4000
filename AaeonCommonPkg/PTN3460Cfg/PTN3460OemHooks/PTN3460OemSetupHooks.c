//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------

#include <AmiDxeLib.h>
#include <Token.h>
#include "AaeonCommonPkg\PTN3460Cfg\PTN3460Cfg.h"

// Produced Protocols

// Consumed Protocols
#include <Protocol\SmbusHc.h>

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
extern EFI_SMBUS_HC_PROTOCOL *gSmbusProtocol;

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
    Status = gSmbusProtocol->Execute(gSmbusProtocol, SlaveAddr, 0x00, EfiSmbusWriteByte, FALSE, &Length, &data);
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
    Status = gSmbusProtocol->Execute(gSmbusProtocol, SlaveAddr, 0x00, EfiSmbusWriteByte, FALSE, &Length, &data);
    DEBUG((DEBUG_INFO, "  Write AD5247@0x%02X = %r\n", SlaveAddr.SmbusDeviceAddress, Status));
    return;
}
#endif
