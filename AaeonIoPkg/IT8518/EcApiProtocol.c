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
#include "EcApiProtocol.h"

//#include "Silicon\BroxtonSiPkg\SouthCluster\Include\ScRegs\RegsPcu.h"
#include <Library/TimerLib.h>

//>>CSKA_009_Elflo 20150903
#ifdef PEI_BUILD
#include <Ppi/Stall.h>
EFI_PEI_STALL_PPI    		*gStallPpi = NULL;
EFI_PEI_SERVICES     		**gPeiServices = NULL;
#endif
//----------------------------------------------------------------------------
VOID uSecDelay (UINT16 uSec)
{
//uSecDelay(uSec);
//	CountTime(uSec, PM_BASE_ADDRESS); //
/*
#ifdef PEI_BUILD
	if (gStallPpi != NULL)
	{gStallPpi->Stall(gPeiServices, gStallPpi, uSec*1000);}
#endif
#ifdef  DXE_BUILD
	pBS->Stall(uSec*1000);	//(uSecond)
#endif
*/	

    IoWrite8(0x80, 0xec);
    IoWrite8(0x80, 0xec);
    IoWrite8(0x80, 0xec);
}


//----------------------------------------------------------------------------
VOID Debug80(UINT8 Time, UINT8 Code){ 
	IoWrite8(0x80, Code);
	while(Time != 0){
	uSecDelay(1500);
	Time--;
	}
}

//----------------------------------------------------------------------------

BOOLEAN EcApiAccess(UINT8 LDN,UINT8 Type,BOOLEAN ReadWrite)
{
	BOOLEAN status = 0;
	
	EcWriteByte(EcReg_Dev, LDN);
	EcWriteByte(EcReg_Type,Type);
	EcWriteByte(EcReg_Conf,CMD_Read|(ReadWrite<<5));	
	status = API_Check();
	return status;
}

UINT8 EcReadByte(UINT8 offset)
{
	UINT8 temp;
	IoWrite8(IT851xBramBaseAddress, offset);
	uSecDelay(1);
	temp = IoRead8(IT851xBramBaseAddress+1);
	uSecDelay(1);	
	return temp;
}	

void EcWriteByte(UINT8 offset,UINT8 data)
{
	IoWrite8(IT851xBramBaseAddress, offset);
	uSecDelay(1);
	IoWrite8(IT851xBramBaseAddress+1, data);	
	uSecDelay(1);
}

BOOLEAN API_Check()
{
  UINT16 timeout;
  UINT8  value;
  BOOLEAN status = 0;

  for (timeout = 0; timeout < 2000; timeout++)		
  {
        value = EcReadByte(EcReg_Conf);
	uSecDelay(1);				
	if (value&(Flag_Fail|Flag_Done))
	{
		if (value&Flag_Done) { status = 1; }	
		return status;
	}
  }
  return status;
}
	
void EcBramAccess (IN UINT8 Index,IN OUT UINT8 *Data,IN BOOLEAN ReadWrite)
{
        IoWrite8(IT851xBramBaseAddress, Index);
        if(ReadWrite)   // 0: Read 1:Write
        { IoWrite8(IT851xBramBaseAddress + 1, *Data); }
        else
        { *Data = IoRead8(IT851xBramBaseAddress + 1); }     		//Input/Output
        uSecDelay(1);						
}

//----------------------------------------------------------------------------

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
//*************************************************************************
