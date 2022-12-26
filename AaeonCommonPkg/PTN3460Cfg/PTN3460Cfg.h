#ifndef __AAEON_PTN3460CFG_H__
#define __AAEON_PTN3460CFG_H__

#include "PTN3460ElinkFunctions.h"

//---------------------------------------------------------------------------
// Constant, Macro and Type Definition(s)
//---------------------------------------------------------------------------
// Macro Definition(s)
#define DEVICE_CHECK_RETRY 10  //Miles, default to retry 10 times, 20ms between for each retry
// Type Definition(s)
typedef struct _AAEON_PTN3460_CFG
{
	UINT8	SlaveAddr;
    UINT8   Enabled;
    UINT8   PanelType;
    UINT8   PanelMode;
    UINT8   ColorDepth;
    UINT8   BacklightMode;
    UINT8   BacklightType;
    UINT8   BacklightLv;
    UINT8   BacklightPwmFreq;   
} AAEON_PTN3460_CFG;

typedef enum {
  PwmFreq_100H = 0,
  PwmFreq_200H,
  PwmFreq_220H,
  PwmFreq_500H,
  PwmFreq_1KH,
  PwmFreq_2_2KH,
  PwmFreq_6_5KH,
  PwmFreq_Invalid 
} PANEL_PWM_FREQ_T;

typedef EFI_STATUS (PTN3460_CFG_HOOK)(IN AAEON_PTN3460_CFG *CfgPanel);


#endif
