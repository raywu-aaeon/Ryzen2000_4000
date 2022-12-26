//**********************************************************************
#include <AmiStatusCodes.h>
#include "AmiModulePkg\AmiStatusCode\StatusCodeInt.h"

#include "AmiModulePkg/Include/Library/AmiBeepLib.h"
#include "MdePkg/Include/Library/TimerLib.h"

extern VOID AaeonPostBeep();
//**********************************************************************
// Checkpoints map
//**********************************************************************
//1    - 0xF : SEC execution
//0x10 - 0x2F: PEI CAR execution
//0x30 - 0x4F: PEI execution after memory detection
//0x50 - 0x5F: PEI errors
//0x60 - 0xCF: DXE execution
//0xD0 - 0xDF: DXE errors
//0xE0 - 0xE8: S3 Resume
//0xE9 - 0xEF: S3 Resume errors
//0xF0 - 0xF8: Recovery
//0xF9 - 0xFF: Recovery errors

STATUS_CODE_TO_BYTE_MAP AaeonErrorBeepMap[] =
{
    { DXE_ARCH_PROTOCOL_NOT_AVAILABLE, 4 },
//    { DXE_NO_CON_OUT, 5 },
//    { DXE_NO_CON_IN, 5 },
    { DXE_INVALID_PASSWORD, 1 },
    { DXE_FLASH_UPDATE_FAILED, 6 },
    { DXE_RESET_NOT_AVAILABLE, 7 },
    { DXE_PCI_BUS_OUT_OF_RESOURCES, 8},

    {0,0}
};

VOID AaeonPostBeep()
{
	AmiBeep(26163*11,40000);
	MicroSecondDelay(100000);
}