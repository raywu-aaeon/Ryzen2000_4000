#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2017, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
#<AMI_FHDR_START>
#----------------------------------------------------------------------
#
# Name: F81804.mak
#
# Description: SIO module MAK file.
#
#----------------------------------------------------------------------
#<AMI_FHDR_END>
#**********************************************************************
#Include this only for Static Setup 
#ifeq ("$(SIO_SETUP_USE_APTIO_4_STYLE)", "1")) 
#----------------------------------------------------------------------
Prepare : BuildSioElink $(BUILD_DIR)/Sio1HwmStrings.uni

#----------------------------------------------------------------------
#       Generate SIO elink table
#		1. SIO init string table for SioSetup.c
#----------------------------------------------------------------------
BuildSioElink : $(BUILD_DIR)/Token.mak
	$(ECHO) \
"\
#ifndef _SIO_ELINK_H_$(EOL)\
#define _SIO_ELINK_H_$(EOL)\
$(EOL)\
#define SIO_Init_Str_LIST $(SetupStrTableList)$(EOL)\
#endif$(EOL)\
"> $(BUILD_DIR)/SIOElink.h
#---------------------------------------------------------------------------
#       Generate strings for SIO HWM
#		1. Sio1HwmStrings.uni
#---------------------------------------------------------------------------
$(BUILD_DIR)/Sio1HwmStrings.uni : $(BUILD_DIR)/Token.mak
	$(ECHO) \
"/=# $(EOL)\
//---------------------------------------------------------------------------$(EOL)\
// Auto Generated SIO1 HWM Setup Strings.$(EOL)\
//---------------------------------------------------------------------------$(EOL)\
#include \"VFR.uni\"$(EOL)\
$(EOL)\
// Temperature - Start from SYSTEM_TEMP2 because SYSTEM_TEMP1 is left for CPU DTS.$(EOL)\
$(if $(F81804_TEMPERATURE_1_SUPPORT), #string STR_HWM1_SYSTEM_TEMP1         #language eng \"$(F81804_TEMPERATURE_1_NAME)\"$(EOL))\
$(if $(F81804_TEMPERATURE_2_SUPPORT), #string STR_HWM1_SYSTEM_TEMP2         #language eng \"$(F81804_TEMPERATURE_2_NAME)\"$(EOL))\
$(if $(F81804_TEMPERATURE_3_SUPPORT), #string STR_HWM1_SYSTEM_TEMP3         #language eng \"$(F81804_TEMPERATURE_3_NAME)\"$(EOL))\
$(if $(F81804_TEMPERATURE_1_SUPPORT), #string STR_F81804_SMARTFAN_TMPSRC_T1         #language eng \"$(F81804_TEMPERATURE_1_NAME)\"$(EOL))\
$(if $(F81804_TEMPERATURE_2_SUPPORT), #string STR_F81804_SMARTFAN_TMPSRC_T2         #language eng \"$(F81804_TEMPERATURE_2_NAME)\"$(EOL))\
$(if $(F81804_TEMPERATURE_3_SUPPORT), #string STR_F81804_SMARTFAN_TMPSRC_T3         #language eng \"$(F81804_TEMPERATURE_3_NAME)\"$(EOL))\
$(if $(F81804_FAN_1_SUPPORT), #string STR_HWM1_FAN1_SPEED         #language eng \"$(F81804_FAN_1_NAME)\"$(EOL))\
$(if $(F81804_FAN_2_SUPPORT), #string STR_HWM1_FAN2_SPEED         #language eng \"$(F81804_FAN_2_NAME)\"$(EOL))\
$(if $(F81804_VCORE_SUPPORT), #string STR_F81804_HWM1_VCORE        #language eng \"$(F81804_VCORE_NAME)\"$(EOL))\
$(if $(F81804_VIN0_SUPPORT), #string STR_F81804_HWM1_VIN0         #language eng \"$(F81804_VIN0_NAME)\"$(EOL))\
$(if $(F81804_VIN1_SUPPORT), #string STR_HWM1_VIN1         #language eng \"$(F81804_VIN1_NAME)\"$(EOL))\
$(if $(F81804_VIN2_SUPPORT), #string STR_HWM1_VIN2         #language eng \"$(F81804_VIN2_NAME)\"$(EOL))\
$(if $(F81804_VIN3_SUPPORT), #string STR_HWM1_VIN3         #language eng \"$(F81804_VIN3_NAME)\"$(EOL))\
$(if $(F81804_VCC3_SUPPORT), #string STR_HWM1_VCC3V        #language eng \"$(F81804_VCC3_NAME)\"$(EOL))\
$(if $(F81804_AVCC_SUPPORT), #string STR_F81804_HWM1_VACC         #language eng \"$(F81804_AVCC_NAME)\"$(EOL))\
$(if $(F81804_VSB3_SUPPORT), #string STR_HWM1_VSB3V        #language eng \"$(F81804_VSB3_NAME)\"$(EOL))\
$(if $(F81804_VBAT_SUPPORT), #string STR_HWM1_VBAT         #language eng \"$(F81804_VBAT_NAME)\"$(EOL))\
"\
> $(BUILD_DIR)/TempSio1HwmStrings.uni
	$(IO_GENUNIFILE) $(BUILD_DIR)/TempSio1HwmStrings.uni $@

#----------------------------------------------------------------------
#endif
#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2017, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

