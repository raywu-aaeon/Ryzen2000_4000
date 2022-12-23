//*************************************************************************
//*************************************************************************
//**                                                                     **
//**          (C)Copyright 1985-2019, American Megatrends, Inc.          **
//**                                                                     **
//**                         All Rights Reserved.                        **
//**                                                                     **
//**        5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093         **
//**                                                                     **
//**                         Phone: (770)-246-8600                       **
//**                                                                     **
//*************************************************************************
//*************************************************************************

/** @file CpuSetupData.h
    CPU setup data header file, define all the CPU setup items
    and a structures in this file. 

**/

#ifndef __CPU_SETUP_DATA_H__ // To Avoid this header get compiled twice
#define __CPU_SETUP_DATA_H__


#ifdef __cplusplus
extern "C" {
#endif

#define BUFFER_SETUP            1
#define BUFFER_AMIAGESASETUP    2

#pragma pack(push, 1)
typedef struct _CPU_CONFIG_DATA
{

	UINT8	  EnhancedDebug;
    UINT8   PNOW_ASL_MODE;
    UINT8   PSTATE_CTRL; // [Fam15 only]
    UINT8   PPC_LIMIT;
    UINT8   PPC_CTRL;
    UINT8   SVM_MODE;
    UINT8   NX_MODE;
    UINT8   CORE_LEVELING;
    UINT8   C6Mode; // [Fam15 only]
    UINT8   CpbMode; // [Fam15 only]

} CPU_CONFIG_DATA;
#pragma pack(pop)


typedef struct _CPU_CONFIG_DATA CPU_SETUP_DATA;

VOID GetCpuSetupData (
    IN VOID                 *Service,
    IN OUT CPU_SETUP_DATA   *CpuSetupData,
    IN BOOLEAN              Pei
);

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif 

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**          (C)Copyright 1985-2019, American Megatrends, Inc.          **
//**                                                                     **
//**                         All Rights Reserved.                        **
//**                                                                     **
//**        5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093         **
//**                                                                     **
//**                         Phone: (770)-246-8600                       **
//**                                                                     **
//*************************************************************************
//*************************************************************************
