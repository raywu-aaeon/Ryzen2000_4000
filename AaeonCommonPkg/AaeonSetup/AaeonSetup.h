//<AMI_FHDR_START>
//----------------------------------------------------------------------------
//
//  Name:           AaeonSetup.h
//
//  Description:    
//
//----------------------------------------------------------------------------
//<AMI_FHDR_END>

#ifndef _AAEON_SETUP_H_
#define _AAEON_SETUP_H_

#define AAEON_VAR_GUID \
    {0x9ADE22C1, 0x477F, 0x41CC, 0x91, 0x83, 0x72, 0xD6, 0x6F, 0xA3, 0xEE, 0xCC}

#ifndef TYPEDEF_AAEON_SETUP_DATA
#define TYPEDEF_AAEON_SETUP_DATA
typedef struct {
    UINT8	EgrMode;
    UINT8   BoardId;
    UINT8   PanelId;
    UINT8   OemId;
    UINT8   SwBoardId;
    UINT8   SwPanelId;
    UINT8   SwOemId;
} AAEON_SETUP_DATA;
#endif

typedef struct {
    UINT8   HwBoardId;
    UINT8   HwPanelId;
    UINT8   HwOemId;
} AAEON_HW_ID;

#define SIO_FORM_SET_GUID {0x941BC855, 0xBF7E, 0x4fcb, 0x88, 0x2F, 0x7A, 0xEA, 0xD1, 0x5C, 0x9D, 0x47}
#define SIO_MAIN_FORM_ID 	1

extern VOID AaeonHandleSaveExitKey( VOID *app, VOID *hotkey, VOID *cookie );	// 2016/03/17 Eric +
//20171031 Carson-Fix issue Os Indications Support-add >>
extern VOID AaeonOsIndicationsSupportHook();
//20171031 Carson-Fix issue Os Indications Support-add <<

#endif