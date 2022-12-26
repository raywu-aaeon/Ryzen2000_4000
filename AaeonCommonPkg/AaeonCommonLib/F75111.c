//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------
#include "AaeonCommonLib.h"
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol\SmbusHc.h>
#include <Library/DebugLib.h>

// Produced Protocols

// Consumed Protocols

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

// Function Definition(s)
//---------------------------------------------------------------------------
//		function definition _begin
//---------------------------------------------------------------------------
#if defined(F75111PeiPkg_SUPPORT) && (F75111PeiPkg_SUPPORT == 1)
#ifndef PEI_BUILD
//----------------------------------------------------------------------------
//
// Procedure:   F75111SetGpio
//
// Description: This function is setting the GPIO high/low and input/output
//
// Input:       GpioNum - The number of GPIO, ## for GPIO##
//              GpioVal - The high/low of GPIO, 1 for high, 0 for low
//              GpioType - The input/output of GPIO, 1 for output, 0 for input
//              SETUP_DATA - The pointer of setup item
//              
// Output:      N/A
//
// Notes:       
//----------------------------------------------------------------------------
VOID
F75111SetGpio ( 
	IN UINT8 	GpioNum,
	IN UINT8 	GpioVal,
	IN UINT8 	GpioType,
	IN SETUP_DATA	*SetupData
)	
{
	UINT8	GpioGroup, GpioGroupNum;

	GpioGroup = GpioNum / 10;
	GpioGroupNum = GpioNum % 10;

	switch(GpioGroup)
	{
		case Gpio1x:
			SetupData->F75111Gpio1x_Val[GpioGroupNum] = GpioVal;
			SetupData->F75111Gpio1x_Oe[GpioGroupNum] = GpioType;
			break;	

		case Gpio2x:
			SetupData->F75111Gpio2x_Val[GpioGroupNum] = GpioVal;
			SetupData->F75111Gpio2x_Oe[GpioGroupNum] = GpioType;
			break;

		case Gpio3x:
			SetupData->F75111Gpio3x_Val[GpioGroupNum] = GpioVal;
			SetupData->F75111Gpio3x_Oe[GpioGroupNum] = GpioType;			
			break;														

		default:
			break;

	}	
}
//----------------------------------------------------------------------------
//
// Procedure:   F75111GetGpio
//
// Description: This function is getting the GPIO status
//
// Input:       GpioNum - The number of GPIO, ## for GPIO##
//              
// Output:      RegTmp8 - GPIO status, 1 for high, 0 for low
//
// Notes:       
//----------------------------------------------------------------------------
UINT8 F75111GetGpio(IN UINT8 GpioNum)
{
    //
    //GPIO1x Input Status Register - Index 0x12
    //GPIO2x Input Status Register - Index 0x22
    //GPIO3x Input Status Register - Index 0x42
    //
    UINT8                       F75111StatusIndexList[3] = {0x12, 0x22, 0x42};
    UINT8                       RegTmp8, GpioGroup, GpioGroupNum;
    EFI_STATUS                  Status;
    EFI_SMBUS_HC_PROTOCOL       *SmbusProtocol = NULL;
    EFI_SMBUS_DEVICE_ADDRESS    SlaveAddr;
    UINTN                       DataLength = 1;

    Status = gBS->LocateProtocol (&gEfiSmbusHcProtocolGuid, NULL, (VOID**) &SmbusProtocol);
    ASSERT_EFI_ERROR (Status);
    ASSERT (SmbusProtocol != NULL);

    SlaveAddr.SmbusDeviceAddress = F75111_SLAVE_ADDRESS;

    GpioGroup = GpioNum / 10;
    GpioGroupNum = GpioNum % 10;

    //Read Status Register
    Status = SmbusProtocol->Execute(SmbusProtocol, SlaveAddr, F75111StatusIndexList[GpioGroup - 1], EfiSmbusReadByte, FALSE, &DataLength, &RegTmp8);
    RegTmp8 = RegTmp8 >> GpioGroupNum;  //Move status bit to BIT0
    RegTmp8 &= BIT0;  //Clear no use bit
	
	return RegTmp8;
}	

#endif //PEI_BUILD
#endif //F75111_SUPPORT
