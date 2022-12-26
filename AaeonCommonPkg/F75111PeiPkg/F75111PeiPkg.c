//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------
#include <Token.h>
#include <AmiPeiLib.h>
#include <AmiCspLib.h>
#include <Setup.h>
#include <Ppi/Smbus2.h>

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)

// Macro Definition(s)

// Type Definition(s)

// Function Prototype(s)
//VOID RayDebug80(UINT8 Time, UINT8 Code){
//	UINTN i;
//	
//	i = 0x0FFFF | (Time << 16);
//	while(i != 0){
//		IoWrite8(0x80, Code);
//		i--;
//	}
//}

//---------------------------------------------------------------------------
// Variable and External Declaration(s)
//---------------------------------------------------------------------------
// Variable Declaration(s)
#define		F75111_REG_03	0x03
#define		F75111_REG_04	0x04
#define		F75111_REG_05	0x05
#define		F75111_REG_10	0x10
#define		F75111_REG_11	0x11
#define		F75111_REG_13	0x13
#define		F75111_REG_15	0x15
#define		F75111_REG_1B	0x1B
#define		F75111_REG_20	0x20
#define		F75111_REG_21	0x21
#define		F75111_REG_23	0x23
#define		F75111_REG_25	0x25
#define		F75111_REG_2B	0x2B
#define		F75111_REG_40	0x40
#define		F75111_REG_41	0x41
#define		F75111_REG_43	0x43
// GUID Definition(s)

// PPI Definition(s)

// PPI that are installed

// PPI that are notified

// External Declaration(s)

// Function Definition(s)
EFI_STATUS F75111PeiPkg_Init (
	IN EFI_FFS_FILE_HEADER      *FfsHeader,
	IN EFI_PEI_SERVICES         **PeiServices )
{
	EFI_STATUS	Status;
	// Pei ReadOnlyVariable2 PPI locate
	//{
		SETUP_DATA				SetupData;
		UINTN           			VariableSize = sizeof( SETUP_DATA );
		EFI_GUID				gSetupGuid = SETUP_GUID;
		EFI_PEI_READ_ONLY_VARIABLE2_PPI 	*ReadOnlyVariable = NULL;
        	
		Status = (*PeiServices)->LocatePpi( PeiServices, &gEfiPeiReadOnlyVariable2PpiGuid, 0, NULL, &ReadOnlyVariable );
		Status = ReadOnlyVariable->GetVariable( ReadOnlyVariable, L"Setup", &gSetupGuid, NULL, &VariableSize, &SetupData );
	//}

	{
		EFI_PEI_SMBUS2_PPI		*SmBus2Ppi;
		EFI_SMBUS_DEVICE_ADDRESS	SlaveAddr;
		EFI_GUID			gEfiPeiSmbus2PpiGuid = EFI_PEI_SMBUS2_PPI_GUID;
		UINTN				DataLength = 1;
		UINT8				i, Data8;
		Status = (*PeiServices)->LocatePpi( PeiServices, &gEfiPeiSmbus2PpiGuid, 0, NULL, &SmBus2Ppi );

		SlaveAddr.SmbusDeviceAddress = F75111_SLAVE_ADDRESS;

		// F75111_REG_03
		Status = SmBus2Ppi->Execute( SmBus2Ppi, SlaveAddr, F75111_REG_03, EfiSmbusReadByte, FALSE, &DataLength, &Data8 );
		// GPIO10_EN ~ GPIO12_EN
		// 0: GPIO, 1: Native LED
		Data8 &= ~(BIT0 + BIT1 + BIT2 + BIT3 + BIT4);
		for(i=0; i<=2; i++){
			switch(i)
			{
				case 0:
					Data8 |= SetupData.F75111Gpio1x_En[i];
					break;
				case 1:
					Data8 |= (SetupData.F75111Gpio1x_En[i] << 2);
					break;
				case 2:
					Data8 |= (SetupData.F75111Gpio1x_En[i] << 3);
					break;
				default:
					break;
			}
		}
		Status = SmBus2Ppi->Execute( SmBus2Ppi, SlaveAddr, F75111_REG_03, EfiSmbusWriteByte, FALSE, &DataLength, &Data8 );
		// F75111_REG_04
		Status = SmBus2Ppi->Execute( SmBus2Ppi, SlaveAddr, F75111_REG_04, EfiSmbusReadByte, FALSE, &DataLength, &Data8 );
		// GPIO14_EN ~ GPIO17_EN
		// 0: GPIO, 1: Native LED
		Data8 &= ~(BIT0 + BIT1 + BIT5 + BIT6);
		for(i=4; i<=7; i++){
			if(SetupData.F75111Gpio1x_En[i] == 1)
				Data8 |= ((i <= 5) ? (1 << (i+1)) : (1 << (i-6)));
		}
		// GPIO20_EN ~ GPIO22_EN, GPIO27_EN
		// 0: GPIO, 1: Native LED
		Data8 &= ~(BIT2 + BIT3 + BIT4 + BIT7);
		for(i=0; i<=2; i++){
			if(SetupData.F75111Gpio2x_En[i] == 1)
				Data8 |= (1 << (i+2));
		}
		if(SetupData.F75111Gpio2x_En[7] == 1)
			Data8 |= (1 << 7);
		Status = SmBus2Ppi->Execute( SmBus2Ppi, SlaveAddr, F75111_REG_04, EfiSmbusWriteByte, FALSE, &DataLength, &Data8 );
		// F75111_REG_05
		Status = SmBus2Ppi->Execute( SmBus2Ppi, SlaveAddr, F75111_REG_05, EfiSmbusReadByte, FALSE, &DataLength, &Data8 );
		// GPIO23_EN ~ GPIO26_EN
		// 0: GPIO, 1: Native LED
		Data8 &= ~(BIT0 + BIT1 + BIT2 + BIT3);
		for(i=3; i<=6; i++){
			if(SetupData.F75111Gpio2x_En[i] == 1)
			Data8 |= (BIT3 >> (i-3));
		}
		Status = SmBus2Ppi->Execute( SmBus2Ppi, SlaveAddr, F75111_REG_05, EfiSmbusWriteByte, FALSE, &DataLength, &Data8 );

		// GPIO10_OE ~ GPIO17_OE, GPIO10_VAL ~ GPIO17_VAL, GPIO10_OMODE ~ GPIO17_OMODE, GPIO10_PU ~ GPIO17_PU
		// F75111_REG_10
		Data8 = 0;
		//Status = SmBus2Ppi->Execute( SmBus2Ppi, SlaveAddr, F75111_REG_10, EfiSmbusReadByte, FALSE, &DataLength, &Data8 );
		for(i=0; i<=7; i++){
			if(SetupData.F75111Gpio1x_Oe[i] == 1) // OUTPUT
				Data8 |= (1 << i);
		}
		Status = SmBus2Ppi->Execute( SmBus2Ppi, SlaveAddr, F75111_REG_10, EfiSmbusWriteByte, FALSE, &DataLength, &Data8 );
		// F75111_REG_11
		Data8 = 0;
		//Status = SmBus2Ppi->Execute( SmBus2Ppi, SlaveAddr, F75111_REG_11, EfiSmbusReadByte, FALSE, &DataLength, &Data8 );
		for(i=0; i<=7; i++){
			if(SetupData.F75111Gpio1x_Val[i] == 1) // HIGH
				Data8 |= (1 << i);
		}
		Status = SmBus2Ppi->Execute( SmBus2Ppi, SlaveAddr, F75111_REG_11, EfiSmbusWriteByte, FALSE, &DataLength, &Data8 );
		// F75111_REG_13
		Data8 = 0;
		//Status = SmBus2Ppi->Execute( SmBus2Ppi, SlaveAddr, F75111_REG_13, EfiSmbusReadByte, FALSE, &DataLength, &Data8 );
		for(i=0; i<=7; i++){
			if(SetupData.F75111Gpio1x_Omode[i] == 1) // PULSE
				Data8 |= (1 << i);
		}
		Status = SmBus2Ppi->Execute( SmBus2Ppi, SlaveAddr, F75111_REG_13, EfiSmbusWriteByte, FALSE, &DataLength, &Data8 );
		// F75111_REG_15
		Data8 = 0;
		//Status = SmBus2Ppi->Execute( SmBus2Ppi, SlaveAddr, F75111_REG_15, EfiSmbusReadByte, FALSE, &DataLength, &Data8 );
		for(i=0; i<=7; i++){
			if(SetupData.F75111Gpio1x_Pu[i] == 1) // Internal Pull Up
				Data8 |= (1 << i);
		}
		Status = SmBus2Ppi->Execute( SmBus2Ppi, SlaveAddr, F75111_REG_15, EfiSmbusWriteByte, FALSE, &DataLength, &Data8 );
		// F75111_REG_1B
		Data8 = 0;
		//Status = SmBus2Ppi->Execute( SmBus2Ppi, SlaveAddr, F75111_REG_1B, EfiSmbusReadByte, FALSE, &DataLength, &Data8 );
		for(i=0; i<=7; i++){
			if(SetupData.F75111Gpio1x_Obuf[i] == 1) // I/O pin
				Data8 |= (1 << i);
		}
		Status = SmBus2Ppi->Execute( SmBus2Ppi, SlaveAddr, F75111_REG_1B, EfiSmbusWriteByte, FALSE, &DataLength, &Data8 );

		// GPIO20_OE ~ GPIO27_OE, GPIO20_VAL ~ GPIO27_VAL, GPIO20_OMODE ~ GPIO27_OMODE, GPIO20_PU ~ GPIO27_PU
		// F75111_REG_20
		Data8 = 0;
		//Status = SmBus2Ppi->Execute( SmBus2Ppi, SlaveAddr, F75111_REG_20, EfiSmbusReadByte, FALSE, &DataLength, &Data8 );
		for(i=0; i<=7; i++){
			if(SetupData.F75111Gpio2x_Oe[i] == 1) // OUTPUT
				Data8 |= (1 << i);
		}
		Status = SmBus2Ppi->Execute( SmBus2Ppi, SlaveAddr, F75111_REG_20, EfiSmbusWriteByte, FALSE, &DataLength, &Data8 );
		// F75111_REG_21
		Data8 = 0;
		//Status = SmBus2Ppi->Execute( SmBus2Ppi, SlaveAddr, F75111_REG_21, EfiSmbusReadByte, FALSE, &DataLength, &Data8 );
		for(i=0; i<=7; i++){
			if(SetupData.F75111Gpio2x_Val[i] == 1) // HIGH
				Data8 |= (1 << i);
		}
		Status = SmBus2Ppi->Execute( SmBus2Ppi, SlaveAddr, F75111_REG_21, EfiSmbusWriteByte, FALSE, &DataLength, &Data8 );
		// F75111_REG_23
		Data8 = 0;
		//Status = SmBus2Ppi->Execute( SmBus2Ppi, SlaveAddr, F75111_REG_23, EfiSmbusReadByte, FALSE, &DataLength, &Data8 );
		for(i=0; i<=7; i++){
			if(SetupData.F75111Gpio2x_Omode[i] == 1) // PULSE
				Data8 |= (1 << i);
		}
		Status = SmBus2Ppi->Execute( SmBus2Ppi, SlaveAddr, F75111_REG_23, EfiSmbusWriteByte, FALSE, &DataLength, &Data8 );
		// F75111_REG_25
		Data8 = 0;
		//Status = SmBus2Ppi->Execute( SmBus2Ppi, SlaveAddr, F75111_REG_25, EfiSmbusReadByte, FALSE, &DataLength, &Data8 );
		for(i=0; i<=7; i++){
			if(SetupData.F75111Gpio2x_Pu[i] == 1) // Internal Pull Up
				Data8 |= (1 << i);
		}
		Status = SmBus2Ppi->Execute( SmBus2Ppi, SlaveAddr, F75111_REG_25, EfiSmbusWriteByte, FALSE, &DataLength, &Data8 );
		// F75111_REG_2B
		Data8 = 0;
		//Status = SmBus2Ppi->Execute( SmBus2Ppi, SlaveAddr, F75111_REG_2B, EfiSmbusReadByte, FALSE, &DataLength, &Data8 );
		for(i=0; i<=7; i++){
			if(SetupData.F75111Gpio2x_Obuf[i] == 1) // I/O pin
				Data8 |= (1 << i);
		}
		Status = SmBus2Ppi->Execute( SmBus2Ppi, SlaveAddr, F75111_REG_2B, EfiSmbusWriteByte, FALSE, &DataLength, &Data8 );

		// GPIO30_OE ~ GPIO37_OE, GPIO30_VAL ~ GPIO37_VAL, GPIO30_OMODE ~ GPIO37_OMODE
		// F75111_REG_40
		Data8 = 0;
		//Status = SmBus2Ppi->Execute( SmBus2Ppi, SlaveAddr, F75111_REG_40, EfiSmbusReadByte, FALSE, &DataLength, &Data8 );
		for(i=0; i<=3; i++){
			if(SetupData.F75111Gpio3x_Oe[i] == 1) // OUTPUT
				Data8 |= (1 << i);
		}
		Status = SmBus2Ppi->Execute( SmBus2Ppi, SlaveAddr, F75111_REG_40, EfiSmbusWriteByte, FALSE, &DataLength, &Data8 );
		// F75111_REG_41
		Data8 = 0;
		//Status = SmBus2Ppi->Execute( SmBus2Ppi, SlaveAddr, F75111_REG_41, EfiSmbusReadByte, FALSE, &DataLength, &Data8 );
		for(i=0; i<=3; i++){
			if(SetupData.F75111Gpio3x_Val[i] == 1) // HIGH
				Data8 |= (1 << i);
		}
		Status = SmBus2Ppi->Execute( SmBus2Ppi, SlaveAddr, F75111_REG_41, EfiSmbusWriteByte, FALSE, &DataLength, &Data8 );
		// F75111_REG_43
		Data8 = 0;
		//Status = SmBus2Ppi->Execute( SmBus2Ppi, SlaveAddr, F75111_REG_43, EfiSmbusReadByte, FALSE, &DataLength, &Data8 );
		for(i=0; i<=3; i++){
			if(SetupData.F75111Gpio3x_Omode[i] == 1) // PULSE
				Data8 |= (1 << i);
		}
		Status = SmBus2Ppi->Execute( SmBus2Ppi, SlaveAddr, F75111_REG_43, EfiSmbusWriteByte, FALSE, &DataLength, &Data8 );

#if SECOND_F75111_SLAVE_ADDRESS
#endif //SECOND_F75111_SLAVE_ADDRESS
	}

	return EFI_SUCCESS;
}
