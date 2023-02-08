//---------------------------------------------------------------------------
// Include(s)
//---------------------------------------------------------------------------
#include <Token.h>
#include <AmiPeiLib.h>
#include <AmiCspLib.h>
#include <Setup.h>
#include <Ppi/Smbus2.h>
#include <Ppi/Stall.h>

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Constant Definition(s)
//UINT8	MagicCode[4] = PTN3460_MAGIC_CODE;
UINT8	MagicNumber[4] = PTN3460_MAGIC_CODE;
UINT8	MagicOffset[4] = PTN3460_MAGIC_OFFSET;

UINT8	Ptn3460ConfigTable[128] = { \
        0x00, 0x23, 0x03, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0xFE, 0x00, 0x00, 0x08, 0x00, 0x00, 0x0C,\
        0x07, 0xFF, 0x00, 0x0A, 0x14, 0x00, 0x01, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,\
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,\
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,\
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,\
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,\
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x34, 0x56, 0x78,\
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF\
};
UINT8	Ptn3460EdidTable[14][128] = { \
	{\
	// 0_640x480_60Hz
	//	000h, 001h, 002h, 003h, 004h, 005h, 006h, 007h, 008h, 009h, 00Ah, 00Bh, 00Ch, 00Dh, 00Eh, 00Fh
	//    ------------------------------------------------------------------------------------------------
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x04, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,\
		0x12, 0x17, 0x01, 0x03, 0x80, 0x32, 0x28, 0x00, 0x0A, 0x07, 0xF5, 0x9A, 0x57, 0x4E, 0x87, 0x26,\
		0x1E, 0x50, 0x54, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,\
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xD5, 0x09, 0x80, 0xE0, 0x21, 0x58, 0x2D, 0x20, 0x08, 0x60,\
		0x22, 0x00, 0x2C, 0xC8, 0x10, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00,\
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,\
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10,\
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2D\
	},\
	{\
	// 1_800x480_60Hz
	//	000h, 001h, 002h, 003h, 004h, 005h, 006h, 007h, 008h, 009h, 00Ah, 00Bh, 00Ch, 00Dh, 00Eh, 00Fh
	//    ------------------------------------------------------------------------------------------------
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x04, 0x2E, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,\
		0x12, 0x17, 0x01, 0x03, 0x80, 0x32, 0x28, 0x00, 0x0A, 0x07, 0xF5, 0x9A, 0x57, 0x4E, 0x87, 0x26,\
		0x1E, 0x50, 0x54, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,\
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xFE, 0x0C, 0x20, 0x00, 0x31, 0xE0, 0x2D, 0x10, 0x28, 0x80,\
		0x22, 0x00, 0x2C, 0xC8, 0x10, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00,\
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,\
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10,\
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78\
	},\
	{\
	// 2_800x600_60Hz
	//	000h, 001h, 002h, 003h, 004h, 005h, 006h, 007h, 008h, 009h, 00Ah, 00Bh, 00Ch, 00Dh, 00Eh, 00Fh
	//    ------------------------------------------------------------------------------------------------
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x04, 0x2E, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,\
		0x12, 0x17, 0x01, 0x03, 0x80, 0x32, 0x28, 0x00, 0x0A, 0x07, 0xF5, 0x9A, 0x57, 0x4E, 0x87, 0x26,\
		0x1E, 0x50, 0x54, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,\
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xA0, 0x0F, 0x20, 0x00, 0x31, 0x58, 0x1C, 0x20, 0x28, 0x80,\
		0x14, 0x00, 0x2C, 0xC8, 0x10, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00,\
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,\
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10,\
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x69\
	},\
	{\
	// 3_1024x600_60Hz
	//	000h, 001h, 002h, 003h, 004h, 005h, 006h, 007h, 008h, 009h, 00Ah, 00Bh, 00Ch, 00Dh, 00Eh, 00Fh
	//    ------------------------------------------------------------------------------------------------
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x04, 0x2E, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,\
		0x12, 0x17, 0x01, 0x03, 0x80, 0x32, 0x28, 0x00, 0x0A, 0x07, 0xF5, 0x9A, 0x57, 0x4E, 0x87, 0x26,\
		0x1E, 0x50, 0x54, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,\
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xC8, 0x13, 0x00, 0x40, 0x41, 0x58, 0x1C, 0x20, 0x18, 0x88,\
		0x14, 0x00, 0x2C, 0xC8, 0x10, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00,\
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,\
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10,\
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14\
	},\
	{\
	// 4_1024x768_60Hz
	//	000h, 001h, 002h, 003h, 004h, 005h, 006h, 007h, 008h, 009h, 00Ah, 00Bh, 00Ch, 00Dh, 00Eh, 00Fh
	//    ------------------------------------------------------------------------------------------------
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x04, 0x2E, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00,\
		0x12, 0x17, 0x01, 0x03, 0x80, 0x32, 0x28, 0x00, 0x0A, 0x07, 0xF5, 0x9A, 0x57, 0x4E, 0x87, 0x26,\
		0x1E, 0x50, 0x54, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,\
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x64, 0x19, 0x00, 0x40, 0x41, 0x00, 0x26, 0x30, 0x18, 0x88,\
		0x36, 0x00, 0x2C, 0xC8, 0x10, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00,\
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,\
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10,\
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8D\
	},\
	{\
	// 5_1024x768_60Hz
	//	000h, 001h, 002h, 003h, 004h, 005h, 006h, 007h, 008h, 009h, 00Ah, 00Bh, 00Ch, 00Dh, 00Eh, 00Fh
	//    ------------------------------------------------------------------------------------------------
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x04, 0x2E, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00,\
		0x12, 0x17, 0x01, 0x03, 0x80, 0x32, 0x28, 0x00, 0x0A, 0x07, 0xF5, 0x9A, 0x57, 0x4E, 0x87, 0x26,\
		0x1E, 0x50, 0x54, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,\
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x64, 0x19, 0x00, 0x40, 0x41, 0x00, 0x26, 0x30, 0x18, 0x88,\
		0x36, 0x00, 0x2C, 0xC8, 0x10, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00,\
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,\
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10,\
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8D\
	},\
	{\
	// 6_1280x768_60Hz
	//	000h, 001h, 002h, 003h, 004h, 005h, 006h, 007h, 008h, 009h, 00Ah, 00Bh, 00Ch, 00Dh, 00Eh, 00Fh
	//    ------------------------------------------------------------------------------------------------
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x04, 0x2E, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00,\
		0x12, 0x17, 0x01, 0x03, 0x80, 0x32, 0x28, 0x00, 0x0A, 0x07, 0xF5, 0x9A, 0x57, 0x4E, 0x87, 0x26,\
		0x1E, 0x50, 0x54, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,\
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x0E, 0x1F, 0x00, 0x98, 0x51, 0x00, 0x1E, 0x30, 0x40, 0x80,\
		0x37, 0x00, 0x2C, 0xC8, 0x10, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00,\
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,\
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10,\
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5A\
	},\
	{\
	// 7_1280x1024_60Hz
	//	000h, 001h, 002h, 003h, 004h, 005h, 006h, 007h, 008h, 009h, 00Ah, 00Bh, 00Ch, 00Dh, 00Eh, 00Fh
	//    ------------------------------------------------------------------------------------------------
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x04, 0x2E, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,\
		0x12, 0x17, 0x01, 0x03, 0x80, 0x32, 0x28, 0x00, 0x0A, 0x07, 0xF5, 0x9A, 0x57, 0x4E, 0x87, 0x26,\
		0x1E, 0x50, 0x54, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,\
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x30, 0x2A, 0x00, 0x98, 0x51, 0x00, 0x2A, 0x40, 0x30, 0x70,\
		0x13, 0x00, 0x2C, 0xC8, 0x10, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00,\
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,\
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10,\
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x54\
	},\
	{\
	// 8_1366x768_60Hz
	//	000h, 001h, 002h, 003h, 004h, 005h, 006h, 007h, 008h, 009h, 00Ah, 00Bh, 00Ch, 00Dh, 00Eh, 00Fh
	//    ------------------------------------------------------------------------------------------------
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x04, 0x2E, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00,\
		0x12, 0x17, 0x01, 0x03, 0x80, 0x32, 0x28, 0x00, 0x0A, 0x07, 0xF5, 0x9A, 0x57, 0x4E, 0x87, 0x26,\
		0x1E, 0x50, 0x54, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,\
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x80, 0x21, 0x56, 0xB0, 0x51, 0x00, 0x1B, 0x30, 0x40, 0x70,\
		0x36, 0x00, 0x2C, 0xC8, 0x10, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00,\
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,\
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10,\
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8A\
	},\
	{\
	// 9_1440x900_60Hz
	//	000h, 001h, 002h, 003h, 004h, 005h, 006h, 007h, 008h, 009h, 00Ah, 00Bh, 00Ch, 00Dh, 00Eh, 00Fh
	//    ------------------------------------------------------------------------------------------------
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x04, 0x2E, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00,\
		0x12, 0x17, 0x01, 0x03, 0x80, 0x32, 0x28, 0x00, 0x0A, 0x07, 0xF5, 0x9A, 0x57, 0x4E, 0x87, 0x26,\
		0x1E, 0x50, 0x54, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,\
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x9A, 0x29, 0xA0, 0xD0, 0x51, 0x84, 0x22, 0x30, 0x50, 0x98,\
		0x36, 0x00, 0x2C, 0xC8, 0x10, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00,\
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,\
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10,\
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3A\
	},\
	{\
	// A_1600x1200_60Hz
	//	000h, 001h, 002h, 003h, 004h, 005h, 006h, 007h, 008h, 009h, 00Ah, 00Bh, 00Ch, 00Dh, 00Eh, 00Fh
	//    ------------------------------------------------------------------------------------------------
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x04, 0x2E, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,\
		0x12, 0x17, 0x01, 0x03, 0x80, 0x32, 0x28, 0x00, 0x0A, 0x07, 0xF5, 0x9A, 0x57, 0x4E, 0x87, 0x26,\
		0x1E, 0x50, 0x54, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,\
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x48, 0x3F, 0x40, 0x30, 0x62, 0xB0, 0x32, 0x40, 0x40, 0xC0,\
		0x13, 0x00, 0x2C, 0xC8, 0x10, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00,\
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,\
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10,\
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1D\
	},\
	{\
	// B_1920x1080_60Hz
	//	000h, 001h, 002h, 003h, 004h, 005h, 006h, 007h, 008h, 009h, 00Ah, 00Bh, 00Ch, 00Dh, 00Eh, 00Fh
	//    ------------------------------------------------------------------------------------------------
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x04, 0x2E, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00,\
		0x12, 0x17, 0x01, 0x03, 0x80, 0x32, 0x28, 0x00, 0x0A, 0x07, 0xF5, 0x9A, 0x57, 0x4E, 0x87, 0x26,\
		0x1E, 0x50, 0x54, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,\
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x3A, 0x80, 0x18, 0x71, 0x38, 0x2D, 0x40, 0x58, 0x2D,\
		0x36, 0x00, 0x2C, 0xC8, 0x10, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00,\
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,\
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10,\
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05\
	},\
	{\
	// C_1920x1200_60Hz
	//	000h, 001h, 002h, 003h, 004h, 005h, 006h, 007h, 008h, 009h, 00Ah, 00Bh, 00Ch, 00Dh, 00Eh, 00Fh
	//    ------------------------------------------------------------------------------------------------
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x04, 0x2E, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00,\
		0x12, 0x17, 0x01, 0x03, 0x80, 0x32, 0x28, 0x00, 0x0A, 0x07, 0xF5, 0x9A, 0x57, 0x4E, 0x87, 0x26,\
		0x1E, 0x50, 0x54, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,\
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x7D, 0x4B, 0x80, 0xA0, 0x72, 0xB0, 0x2D, 0x40, 0x88, 0xC8,\
		0x36, 0x00, 0x2C, 0xC8, 0x10, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00,\
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,\
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10,\
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAC\
	},\
	{\
	// D_1280x800
	//	000h, 001h, 002h, 003h, 004h, 005h, 006h, 007h, 008h, 009h, 00Ah, 00Bh, 00Ch, 00Dh, 00Eh, 00Fh
	//    ------------------------------------------------------------------------------------------------
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x04, 0x2E, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,\
		0x12, 0x17, 0x01, 0x03, 0x80, 0x32, 0x28, 0x00, 0x0A, 0x07, 0xF5, 0x9A, 0x57, 0x4E, 0x87, 0x26,\
		0x1E, 0x50, 0x54, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,\
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xED, 0x1A, 0x00, 0xA8, 0x50, 0x20, 0x10, 0x30, 0x30, 0x70,\
		0x13, 0x00, 0x2C, 0xC8, 0x10, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00,\
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,\
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10,\
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA2\
	},\

};
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

// GUID Definition(s)

// PPI Definition(s)

// PPI that are installed

// PPI that are notified

// External Declaration(s)

// Function Definition(s)
EFI_STATUS Ptn3460PeiPkg_Init (
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
		EFI_PEI_STALL_PPI			*StallPpi;
        	
		Status = (*PeiServices)->LocatePpi( PeiServices, &gEfiPeiReadOnlyVariable2PpiGuid, 0, NULL, &ReadOnlyVariable );
		Status = ReadOnlyVariable->GetVariable( ReadOnlyVariable, L"Setup", &gSetupGuid, NULL, &VariableSize, &SetupData );
		(**PeiServices).LocatePpi(PeiServices, &gEfiPeiStallPpiGuid, 0, NULL, &StallPpi);
	//}

	{
		EFI_PEI_SMBUS2_PPI		*SmBus2Ppi;
		EFI_SMBUS_DEVICE_ADDRESS	SlaveAddr;
		EFI_GUID			gEfiPeiSmbus2PpiGuid = EFI_PEI_SMBUS2_PPI_GUID;
		UINTN				DataLength = 1;
		UINT8				i, Data8;
		Status = (*PeiServices)->LocatePpi( PeiServices, &gEfiPeiSmbus2PpiGuid, 0, NULL, &SmBus2Ppi );

		SlaveAddr.SmbusDeviceAddress = PTN3460_SLAVE_ADDRESS;

		StallPpi->Stall(PeiServices, StallPpi, 100000); 	// Add 100ms delay for PTN3460 maximum initial time.

        //If PTN3460_MAGIC_OFFSET = 0xE9~0xEB: Flash command containing Flash magic number
        //Else PTN3460_MAGIC_OFFSET = 0xEC~0xEF: Configuration magic number
		for (i = 0; i < 0x04; i++)
		{
			Data8 = MagicNumber[i];
			Status = SmBus2Ppi->Execute(SmBus2Ppi, SlaveAddr, MagicOffset[i], EfiSmbusWriteByte, 0x00, &DataLength, &Data8);
		}

        //Offset 0x85: EDID ROM access control
		Data = 0x00;    // Mapping to EDID table '0'.
		Status = SmBus2Ppi->Execute(SmBus2Ppi, SlaveAddr, 0x85, EfiSmbusWriteByte, 0x00, &DataLength, &Data8);
		
		//Offset 0x00~0x7F: EDID registers
		for (i = 0; i < 0x80; i++)  //Programming EDID table.
		{
			Data8 = Ptn3460ConfigTable[i];
			Status = SmBus2Ppi->Execute(SmBus2Ppi, SlaveAddr, 0x80+i, EfiSmbusWriteByte, 0x00, &DataLength, &Data8);
		}
		
		//Offset 0x84: EDID emulation: 0: Read from DDC bus. 1: Read from internal flash.
		Data = 0x01;
		Status = SmBusPpi->Execute(SmBusPpi, SlaveAddr, 0x84, EfiSmbusWriteByte, 0x00, &DataLength, &Data);

//- 		StallPpi->Stall(PeiServices, StallPpi, 100000); // patched initialization failed on some motherboard
//- 		// Configuration Table
//- 		for (i = 0; i < 0x80; ++i)
//- 		{
//- 			Data8 = Ptn3460ConfigTable[i];
//- 			Status = SmBus2Ppi->Execute(SmBus2Ppi, SlaveAddr, 0x80+i, EfiSmbusWriteByte, 0x00, &DataLength, &Data8);
//- 		}
//- 
//- 		// Panel resolution support
//- 		Data8 = 0x00;
//- 		Status = SmBus2Ppi->Execute(SmBus2Ppi, SlaveAddr, 0x85, EfiSmbusWriteByte, 0x00, &DataLength, &Data8);
//- 		for (i = 0; i < 0x80; i++)
//- 		{
//- 			Data8 = Ptn3460EdidTable[SetupData.PTN3460PanelType][i];
//- 			Status = SmBus2Ppi->Execute(SmBus2Ppi, SlaveAddr, i, EfiSmbusWriteByte, 0x00, &DataLength, &Data8);
//- 		}
//- 		for (i = 0; i < 0x04; i++)
//- 		{
//- 			Data8 = MagicCode[i];
//- 			Status = SmBus2Ppi->Execute(SmBus2Ppi, SlaveAddr, MagicOffset[i], EfiSmbusWriteByte, 0x00, &DataLength, &Data8);
//- 		}
//- //		CountTime(500000, PM_BASE_ADDRESS); //delay 500ms
//- 		StallPpi->Stall(PeiServices, StallPpi, 500000);
//- 
//- 		Data8 = 0x01;
//- 		Status = SmBus2Ppi->Execute(SmBus2Ppi, SlaveAddr, 0x84, EfiSmbusWriteByte, 0x00, &DataLength, &Data8);
//- 		for (i = 0; i < 0x04; i++)
//- 		{
//- 			Data8 = MagicCode[i];
//- 			Status = SmBus2Ppi->Execute(SmBus2Ppi, SlaveAddr, MagicOffset[i], EfiSmbusWriteByte, 0x00, &DataLength, &Data8);
//- 		}
//- //		CountTime(500000, PM_BASE_ADDRESS); //delay 500ms
//- 		StallPpi->Stall(PeiServices, StallPpi, 500000);

    	// Offset 0x81: LVDS interface control 1
		Data8 = 0x0B; // Chipset default value.
		{
			{
				Data8 &= ~BIT3;
				if(SetupData.PTN3460PanelMode) //Daul channel
					Data8 |= BIT3;
			}
			{
				Data8 &= ~BIT2;
				if(SetupData.PTN3460DataEnable) //Active high
					Data8 |= BIT2;
			}
			{
				Data8 &= ~(BIT4 + BIT5);
				switch(SetupData.PTN3460ColorDepth)
				{
					case 0: // 24bit
						break;
					case 1:
						Data8 |= BIT4;
						break;
					case 2: // 18bit
						Data8 |= BIT5;
						break;
					case 3:
					default:
						break;
				}
			}
		}
		Status = SmBus2Ppi->Execute(SmBus2Ppi, SlaveAddr, 0x81, EfiSmbusWriteByte, 0x00, &DataLength, &Data8);

		{
			UINT8	Ptn3460BackLight, Ptn3460BackLightInvert;
			UINT16	Data16;

			Ptn3460BackLightInvert = SetupData.Ptn3460Bl_CtrlType;
			Ptn3460BackLight = Ptn3460BackLightInvert == 2 ? SetupData.Ptn3460Bl_Control : (10 - SetupData.Ptn3460Bl_Control) ;
			switch(Ptn3460BackLight)
			{
				// Offset 0x90‐91: PWM value
				case 0:
					Data8 = 0x0F;
					Status = SmBus2Ppi->Execute(SmBus2Ppi, SlaveAddr, 0x90, EfiSmbusWriteByte, 0x00, &DataLength, &Data8);
					Data8 = 0xFF;
					Status = SmBus2Ppi->Execute(SmBus2Ppi, SlaveAddr, 0x91, EfiSmbusWriteByte, 0x00, &DataLength, &Data8);
					break;
				case 10:
					Data8 = 0x00;
					Status = SmBus2Ppi->Execute(SmBus2Ppi, SlaveAddr, 0x90, EfiSmbusWriteByte, 0x00, &DataLength, &Data8);
					Status = SmBus2Ppi->Execute(SmBus2Ppi, SlaveAddr, 0x91, EfiSmbusWriteByte, 0x00, &DataLength, &Data8);
					break;
				default:
					Data16 = (UINT16)((~(0x19A * Ptn3460BackLight)) & 0x0FFF) ;
					Data8 = (UINT8)(Data16 >> 8);
					Status = SmBus2Ppi->Execute(SmBus2Ppi, SlaveAddr, 0x90, EfiSmbusWriteByte, 0x00, &DataLength, &Data8);
					Data8 = (UINT8)(Data16 & 0x0FF);
					Status = SmBus2Ppi->Execute(SmBus2Ppi, SlaveAddr, 0x91, EfiSmbusWriteByte, 0x00, &DataLength, &Data8);
					break;
			}
		}

#if SECOND_PTN3460_SLAVE_ADDRESS
#endif //SECOND_PTN3460_SLAVE_ADDRESS
	}

	return EFI_SUCCESS;
}