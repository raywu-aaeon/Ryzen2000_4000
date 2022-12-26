#**********************************************************************
#<AAEON_FHDR_START>
#----------------------------------------------------------------------
#
# Name: IT8625HwmStrings.mak
#
# Description: SIO module MAK file for AAEON BFPI
#
#----------------------------------------------------------------------
#<AAEON_FHDR_END>
#**********************************************************************
#Include this only for Static Setup 
#ifeq ("$(SIO_SETUP_USE_APTIO_4_STYLE)", "1")) 
#----------------------------------------------------------------------
Prepare : $(BUILD_DIR)/IT8625HwmStrings.uni

#---------------------------------------------------------------------------
#       Generate strings for SIO HWM
#		1. IT8625HwmStrings.uni
#---------------------------------------------------------------------------
$(BUILD_DIR)/IT8625HwmStrings.uni : $(BUILD_DIR)/Token.mak
	$(ECHO) \
"/=# $(EOL)\
//---------------------------------------------------------------------------$(EOL)\
// Auto Generated SIO1 HWM Setup Strings.$(EOL)\
//---------------------------------------------------------------------------$(EOL)\
#include \"VFR.uni\"$(EOL)\
$(EOL)\
// Temperature $(EOL)\
$(if $(IT8625_TMPIN1_SUPPORT), #string STR_HWM1_SYSTEM_TEMP1	#language eng \"$(IT8625_TMPIN1_NAME)\"$(EOL))\
$(if $(IT8625_TMPIN2_SUPPORT), #string STR_HWM1_SYSTEM_TEMP2	#language eng \"$(IT8625_TMPIN2_NAME)\"$(EOL))\
$(if $(IT8625_TMPIN3_SUPPORT), #string STR_HWM1_SYSTEM_TEMP3	#language eng \"$(IT8625_TMPIN3_NAME)\"$(EOL))\
$(if $(IT8625_TMPIN4_SUPPORT), #string STR_HWM1_SYSTEM_TEMP4	#language eng \"$(IT8625_TMPIN4_NAME)\"$(EOL))\
$(if $(IT8625_TMPIN5_SUPPORT), #string STR_HWM1_SYSTEM_TEMP5	#language eng \"$(IT8625_TMPIN5_NAME)\"$(EOL))\
$(if $(IT8625_TMPIN6_SUPPORT), #string STR_HWM1_SYSTEM_TEMP6	#language eng \"$(IT8625_TMPIN6_NAME)\"$(EOL))\
$(if $(FAN_TAC1), #string STR_HWM1_FAN1_SPEED			#language eng \"$(IT8625_FAN_1_NAME)\"$(EOL))\
$(if $(FAN_TAC2), #string STR_HWM1_FAN2_SPEED			#language eng \"$(IT8625_FAN_2_NAME)\"$(EOL))\
$(if $(FAN_TAC3), #string STR_HWM1_FAN3_SPEED			#language eng \"$(IT8625_FAN_3_NAME)\"$(EOL))\
$(if $(FAN_TAC4), #string STR_HWM1_FAN4_SPEED			#language eng \"$(IT8625_FAN_4_NAME)\"$(EOL))\
$(if $(FAN_TAC5), #string STR_HWM1_FAN5_SPEED			#language eng \"$(IT8625_FAN_5_NAME)\"$(EOL))\
$(if $(FAN_TAC6), #string STR_HWM1_FAN6_SPEED			#language eng \"$(IT8625_FAN_6_NAME)\"$(EOL))\
$(if $(IT8625_VIN0_SUPPORT), #string STR_IT8625_HMM_VIN0	#language eng \"$(IT8625_VIN0_NAME)\"$(EOL))\
$(if $(IT8625_VIN1_SUPPORT), #string STR_HWM1_VIN1		#language eng \"$(IT8625_VIN1_NAME)\"$(EOL))\
$(if $(IT8625_VIN2_SUPPORT), #string STR_HWM1_VIN2		#language eng \"$(IT8625_VIN2_NAME)\"$(EOL))\
$(if $(IT8625_VIN3_SUPPORT), #string STR_HWM1_VIN3		#language eng \"$(IT8625_VIN3_NAME)\"$(EOL))\
$(if $(IT8625_VIN4_SUPPORT), #string STR_HWM1_VIN4		#language eng \"$(IT8625_VIN4_NAME)\"$(EOL))\
$(if $(IT8625_VIN5_SUPPORT), #string STR_HWM1_VIN5		#language eng \"$(IT8625_VIN5_NAME)\"$(EOL))\
$(if $(IT8625_VIN6_SUPPORT), #string STR_HWM1_VIN6		#language eng \"$(IT8625_VIN6_NAME)\"$(EOL))\
$(if $(IT8625_3VSB_SUPPORT), #string STR_HWM1_VIN7		#language eng \"$(IT8625_3VSB_NAME)\"$(EOL))\
$(if $(IT8625_VBAT_SUPPORT), #string STR_HWM1_VBAT		#language eng \"$(IT8625_VBAT_NAME)\"$(EOL))\
$(if $(IT8625_AVCC3_SUPPORT), #string STR_HWM1_VCC3V		#language eng \"$(IT8625_AVCC3_NAME)\"$(EOL))\
"\
> $(BUILD_DIR)/TempIT8625HwmStrings.uni
	$(IO_GENUNIFILE) $(BUILD_DIR)/TempIT8625HwmStrings.uni $@
