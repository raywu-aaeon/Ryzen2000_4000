//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**         5555 Oakbrook Pkwy, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
/** @file F81866SmartFansSetup.h
    This contains the Data definitions of Smart Fans Control.
**/
#ifndef __F81866SMARTFANSSETUP__H__
#define __F81866SMARTFANSSETUP__H__
#ifdef __cplusplus
extern "C" {
#endif
#define F81866_SMF_GUID {0x2634d369, 0x335d, 0x4312, 0xb2, 0x10, 0x77, 0xe3, 0x13, 0x4a, 0x61, 0xa0}
typedef struct {
    //FAN1 Smart Setting--
    UINT8   Fan1SmartMode;
    UINT8   Fan1Type;
    UINT8   Fan1Tempin;
    UINT16  Fan1ManualControl;
    UINT8   Fan1Hysteresis;
    UINT8   Fan1Boundary[4];
    UINT8   Fan1Segment[5];
    BOOLEAN MultiTemp;
    UINT8   Fan1Tb;
    UINT8   Fan1Ta;
    UINT8   Fan1Ctup;
    UINT8   Fan1Ctdn;
    //FAN2 Smart Setting--
    UINT8   Fan2SmartMode;
    UINT8   Fan2Type;
    UINT8   Fan2Tempin;
    UINT16  Fan2ManualControl;
    UINT8   Fan2Hysteresis;
    UINT8   Fan2Boundary[4];
    UINT8   Fan2Segment[5];
    //FAN3 Smart Setting--
    UINT8   Fan3SmartMode;
    UINT8   Fan3Type;
    UINT8   Fan3Tempin;
    UINT16  Fan3ManualControl;
    UINT8   Fan3Hysteresis;
    UINT8   Fan3Boundary[4];
    UINT8   Fan3Segment[5];
} F81866_SMF_CONTROL;

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif
//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
