//**********************************************************************
#include <Token.h>
#include <AmiStatusCodes.h>
#include "AmiModulePkg\AmiStatusCode\StatusCodeInt.h"

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

//Errors
//Regular boot
    { PEI_MEMORY_NOT_DETECTED, PEI_MEMORY_NOT_DETECTED_BEEP_COUNT },
    { PEI_MEMORY_NONE_USEFUL, PEI_MEMORY_NONE_USEFUL_BEEP_COUNT },
    { PEI_MEMORY_NOT_INSTALLED, PEI_MEM_NOT_INSTALLED_BEEP_COUNT },
    { PEI_MEMORY_INSTALLED_TWICE, 1 },
    { PEI_DXEIPL_NOT_FOUND, 3 },
    { PEI_DXE_CORE_NOT_FOUND, 3 },
    { PEI_RESET_NOT_AVAILABLE, 7 },
//Recovery
    { PEI_RECOVERY_FAILED, 4 },
//S3 Resume
    { PEI_S3_RESUME_FAILED, 4 },

    {0,0}
};