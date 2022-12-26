//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2008, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
// ==================== EC Register Define ====================
#define IT851xBramBaseAddress (UINT16)(IT8518_TOTAL_BASE_ADDRESS + 0x04)
#define EcPortIndex		0x284
#define EcPortData		0x285
#define	EcReg_Dev		0x10
#define EcReg_Type		0x11
#define	EcReg_Conf		0x12
#define EcReg_Dat0		0x13
#define EcReg_Dat1		0x14
#define EcReg_Dat2		0x15
#define EcReg_Dat3		0x16
#define EcReg_Dat4		0x17
#define EcReg_Dat5		0x18
#define EcReg_Dat6		0x19
#define EcReg_Dat7		0x1A
#define EcReg_Dat8		0x1B
#define EcReg_Dat9		0x1C
#define EcReg_DatA		0x1D
#define EcReg_DatB		0x1E
#define EcReg_DatC		0x1F
//----------------------------------------------------------------------------------
#define CMD_Read		0x10
#define CMD_Write		0x30
//----------------------------------------------------------------------------------
#define Flag_Fail		0x02
#define Flag_Done		0x01
//----------------------------------------------------------------------------------
#define ApiRead  		0x00
#define ApiWrite 		0x01
//----------------------------------------------------------------------------------
#define Read  			0x00
#define Write 			0x01
//----------------------------------------------------------------------------------
#define DioDir			0x00
#define DioVal			0x01
//------------------------------ Macro ---------------------------------------------
#define EcFwAccess(ReadWrite)		EcApiAccess(0xA1,0x02,ReadWrite)
#define EcDioDirAccess(ReadWrite)	EcApiAccess(0xA2,0x00,ReadWrite)
#define EcDioValAccess(ReadWrite)	EcApiAccess(0xA2,0x01,ReadWrite)
#define EcDioUseSelAccess(ReadWrite)	EcApiAccess(0xA2,0x02,ReadWrite)
#define EcDioIntAccess(ReadWrite)	EcApiAccess(0xA2,0x03,ReadWrite)

#define EcHwmAccess(Num,ReadWrite)	EcApiAccess(0xA5,Num,ReadWrite)
#define EcSmfAccess(Num,ReadWrite)	EcApiAccess(0xA6,Num,ReadWrite)
#define EcWdtAccess(ReadWrite)		EcApiAccess(0xA8,0x00,ReadWrite)
#define EcPmcAccess(ReadWrite)		EcApiAccess(0xA9,0x00,ReadWrite)
#define EcBrightAccess(ReadWrite)	EcApiAccess(0xAA,0x01,ReadWrite)
#define EcBatManageAccess(ReadWrite)	EcApiAccess(0xB0,0x00,ReadWrite)
//----------------------------------------------------------------------------------
extern BOOLEAN API_Check();
extern UINT8 EcReadByte(UINT8 offset);
extern void EcWriteByte(UINT8 offset,UINT8 data);
extern BOOLEAN EcApiAccess(UINT8 LDN,UINT8 Type,BOOLEAN ReadWrite);
extern void EcBramAccess (IN UINT8 Index,IN OUT UINT8 *Data,IN BOOLEAN ReadWrite);	
extern VOID Delay(UINT16 uSec);
//----------------------------------------------------------------------------------





