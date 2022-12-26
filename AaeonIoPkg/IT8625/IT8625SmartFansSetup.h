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
/** @file IT8625SmartFansSetup.h
    This contains the Data definitions of Smart Fans Control.
**/
#ifndef __IT8625SMARTFANSSETUP__H__
#define __IT8625SMARTFANSSETUP__H__
#ifdef __cplusplus
extern "C" {
#endif
#define IT8625_SMF_GUID {0x2634d369, 0x335d, 0x4312, 0xb2, 0x10, 0x77, 0xe3, 0x13, 0x4a, 0x61, 0xa0}
// >> AAEON_OVERRIDE
#pragma pack (push)
#pragma pack (1)
// << AAEON_OVERRIDE
typedef struct {
    UINT8   FanPolarity;
    //FAN1 Smart Setting--
    UINT8   Fan1SmartMode;
    UINT8   Fan1Type;
    UINT8   Fan1Tempin;
    UINT16  Fan1PwmSlope;
    UINT16  Fan1RpmSlope;
    UINT8   Fan1TempOffLimit;
    UINT8   Fan1TempStartLimit;
    UINT16  Fan1StartPwm;
    UINT16  Fan1StartRpm;
    UINT8   Fan1PwmControl;
    UINT8   Fan1TempFullSpeedLimit;
    UINT8   Fan1TargetZone;
    UINT8   Fan1TempInterval;
    UINT8   Fan1Smooth;
    UINT8   Fan1CurveCount;
    UINT8   Fan1ExtraAStartLimit;
    UINT8   Fan1ExtraATempIn;
    UINT8   Fan1ExtraASlopeType;
    UINT8   Fan1ExtraARange;
    UINT16  Fan1ExtraASlope;
    UINT8   Fan1ExtraBStartLimit;
    UINT8   Fan1ExtraBTempIn;
    UINT8   Fan1ExtraBSlopeType;
    UINT8   Fan1ExtraBRange;
    UINT16  Fan1ExtraBSlope;
    UINT8   Fan1ExtraCStartLimit;
    UINT8   Fan1ExtraCTempIn;
    UINT8   Fan1ExtraCSlopeType;
    UINT8   Fan1ExtraCRange;
    UINT16  Fan1ExtraCSlope;
    //FAN2 Smart Setting--
    UINT8   Fan2SmartMode;
    UINT8   Fan2Type;
    UINT8   Fan2Tempin;
    UINT16  Fan2PwmSlope;
    UINT16  Fan2RpmSlope;
    UINT8   Fan2TempOffLimit;
    UINT8   Fan2TempStartLimit;
    UINT16  Fan2StartPwm;
    UINT16  Fan2StartRpm;
    UINT8   Fan2PwmControl;
    UINT8   Fan2TempFullSpeedLimit;
    UINT8   Fan2TargetZone;
    UINT8   Fan2TempInterval;
    UINT8   Fan2Smooth;
    UINT8   Fan2CurveCount;
    UINT8   Fan2ExtraAStartLimit;
    UINT8   Fan2ExtraATempIn;
    UINT8   Fan2ExtraASlopeType;
    UINT8   Fan2ExtraARange;
    UINT16  Fan2ExtraASlope;
    UINT8   Fan2ExtraBStartLimit;
    UINT8   Fan2ExtraBTempIn;
    UINT8   Fan2ExtraBSlopeType;
    UINT8   Fan2ExtraBRange;
    UINT16  Fan2ExtraBSlope;
    UINT8   Fan2ExtraCStartLimit;
    UINT8   Fan2ExtraCTempIn;
    UINT8   Fan2ExtraCSlopeType;
    UINT8   Fan2ExtraCRange;
    UINT16  Fan2ExtraCSlope;
    //FAN3 Smart Setting--
    UINT8   Fan3SmartMode;
    UINT8   Fan3Type;
    UINT8   Fan3Tempin;
    UINT16  Fan3PwmSlope;
    UINT16  Fan3RpmSlope;
    UINT8   Fan3TempOffLimit;
    UINT8   Fan3TempStartLimit;
    UINT16  Fan3StartPwm;
    UINT16  Fan3StartRpm;
    UINT8   Fan3PwmControl;
    UINT8   Fan3TempFullSpeedLimit;
    UINT8   Fan3TargetZone;
    UINT8   Fan3TempInterval;
    UINT8   Fan3Smooth;
    UINT8   Fan3CurveCount;
    UINT8   Fan3ExtraAStartLimit;
    UINT8   Fan3ExtraATempIn;
    UINT8   Fan3ExtraASlopeType;
    UINT8   Fan3ExtraARange;
    UINT16  Fan3ExtraASlope;
    UINT8   Fan3ExtraBStartLimit;
    UINT8   Fan3ExtraBTempIn;
    UINT8   Fan3ExtraBSlopeType;
    UINT8   Fan3ExtraBRange;
    UINT16  Fan3ExtraBSlope;
    UINT8   Fan3ExtraCStartLimit;
    UINT8   Fan3ExtraCTempIn;
    UINT8   Fan3ExtraCSlopeType;
    UINT8   Fan3ExtraCRange;
    UINT16  Fan3ExtraCSlope;
    //FAN4 Smart Setting--
    UINT8   Fan4SmartMode;
    UINT8   Fan4Type;
    UINT8   Fan4Tempin;
    UINT16  Fan4PwmSlope;
    UINT16  Fan4RpmSlope;
    UINT8   Fan4TempOffLimit;
    UINT8   Fan4TempStartLimit;
    UINT16  Fan4StartPwm;
    UINT16  Fan4StartRpm;
    UINT8   Fan4PwmControl;
    UINT8   Fan4TempFullSpeedLimit;
    UINT8   Fan4TargetZone;
    UINT8   Fan4TempInterval;
    UINT8   Fan4Smooth;
    UINT8   Fan4CurveCount;
    UINT8   Fan4ExtraAStartLimit;
    UINT8   Fan4ExtraATempIn;
    UINT8   Fan4ExtraASlopeType;
    UINT8   Fan4ExtraARange;
    UINT16  Fan4ExtraASlope;
    UINT8   Fan4ExtraBStartLimit;
    UINT8   Fan4ExtraBTempIn;
    UINT8   Fan4ExtraBSlopeType;
    UINT8   Fan4ExtraBRange;
    UINT16  Fan4ExtraBSlope;
    UINT8   Fan4ExtraCStartLimit;
    UINT8   Fan4ExtraCTempIn;
    UINT8   Fan4ExtraCSlopeType;
    UINT8   Fan4ExtraCRange;
    UINT16  Fan4ExtraCSlope;
    //FAN5 Smart Setting--
    UINT8   Fan5SmartMode;
    UINT8   Fan5Type;
    UINT8   Fan5Tempin;
    UINT16  Fan5PwmSlope;
    UINT16  Fan5RpmSlope;
    UINT8   Fan5TempOffLimit;
    UINT8   Fan5TempStartLimit;
    UINT16  Fan5StartPwm;
    UINT16  Fan5StartRpm;
    UINT8   Fan5PwmControl;
    UINT8   Fan5TempFullSpeedLimit;
    UINT8   Fan5TargetZone;
    UINT8   Fan5TempInterval;
    UINT8   Fan5Smooth;
    UINT8   Fan5CurveCount;
    UINT8   Fan5ExtraAStartLimit;
    UINT8   Fan5ExtraATempIn;
    UINT8   Fan5ExtraASlopeType;
    UINT8   Fan5ExtraARange;
    UINT16  Fan5ExtraASlope;
    UINT8   Fan5ExtraBStartLimit;
    UINT8   Fan5ExtraBTempIn;
    UINT8   Fan5ExtraBSlopeType;
    UINT8   Fan5ExtraBRange;
    UINT16  Fan5ExtraBSlope;
    UINT8   Fan5ExtraCStartLimit;
    UINT8   Fan5ExtraCTempIn;
    UINT8   Fan5ExtraCSlopeType;
    UINT8   Fan5ExtraCRange;
    UINT16  Fan5ExtraCSlope;
    //FAN6 Smart Setting--
    UINT8   Fan6SmartMode;
    UINT8   Fan6Type;
    UINT8   Fan6Tempin;
    UINT16  Fan6PwmSlope;
    UINT16  Fan6RpmSlope;
    UINT8   Fan6TempOffLimit;
    UINT8   Fan6TempStartLimit;
    UINT16  Fan6StartPwm;
    UINT16  Fan6StartRpm;
    UINT8   Fan6PwmControl;
    UINT8   Fan6TempFullSpeedLimit;
    UINT8   Fan6TargetZone;
    UINT8   Fan6TempInterval;
    UINT8   Fan6Smooth;
    UINT8   Fan6CurveCount;
    UINT8   Fan6ExtraAStartLimit;
    UINT8   Fan6ExtraATempIn;
    UINT8   Fan6ExtraASlopeType;
    UINT8   Fan6ExtraARange;
    UINT16  Fan6ExtraASlope;
    UINT8   Fan6ExtraBStartLimit;
    UINT8   Fan6ExtraBTempIn;
    UINT8   Fan6ExtraBSlopeType;
    UINT8   Fan6ExtraBRange;
    UINT16  Fan6ExtraBSlope;
    UINT8   Fan6ExtraCStartLimit;
    UINT8   Fan6ExtraCTempIn;
    UINT8   Fan6ExtraCSlopeType;
    UINT8   Fan6ExtraCRange;
    UINT16  Fan6ExtraCSlope;
} IT8625_SMF_CONTROL;
#pragma pack (pop)  // AAEON_OVERRIDE +

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
