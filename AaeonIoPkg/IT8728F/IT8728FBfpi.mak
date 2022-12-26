#**********************************************************************
#<AAEON_FHDR_START>
#----------------------------------------------------------------------
#
# Name: IT8728FBfpi.mak
#
# Description: SIO module MAK file for AAEON BFPI
#
#----------------------------------------------------------------------
#<AAEON_FHDR_END>
#**********************************************************************
#Include this only for Static Setup 
#ifeq ("$(SIO_SETUP_USE_APTIO_4_STYLE)", "1")) 
#----------------------------------------------------------------------
Prepare : $(BUILD_DIR)/IT8728HwmStrings.uni

#---------------------------------------------------------------------------
#       Generate strings for SIO HWM
#		1. IT8728HwmStrings.uni
#---------------------------------------------------------------------------
$(BUILD_DIR)/IT8728HwmStrings.uni : $(BUILD_DIR)/Token.mak
	$(ECHO) \
"/=# $(EOL)\
//---------------------------------------------------------------------------$(EOL)\
// Auto Generated SIO1 HWM Setup Strings.$(EOL)\
//---------------------------------------------------------------------------$(EOL)\
#include \"VFR.uni\"$(EOL)\
$(EOL)\
// Temperature $(EOL)\
$(if $(IT8728F_TMPIN1_SUPPORT), #string STR_HWM1_SYSTEM_TEMP1         #language eng \"$(IT8728F_TMPIN1_NAME)\"$(EOL))\
$(if $(IT8728F_TMPIN2_SUPPORT), #string STR_HWM1_SYSTEM_TEMP2         #language eng \"$(IT8728F_TMPIN2_NAME)\"$(EOL))\
$(if $(IT8728F_TMPIN3_SUPPORT), #string STR_HWM1_SYSTEM_TEMP3         #language eng \"$(IT8728F_TMPIN3_NAME)\"$(EOL))\
$(if $(FAN_TAC_1), #string STR_HWM1_FAN1_SPEED			      #language eng \"$(IT8728F_FAN_1_NAME)\"$(EOL))\
$(if $(FAN_TAC_2), #string STR_HWM1_FAN2_SPEED			      #language eng \"$(IT8728F_FAN_2_NAME)\"$(EOL))\
$(if $(FAN_TAC_3), #string STR_HWM1_FAN3_SPEED			      #language eng \"$(IT8728F_FAN_3_NAME)\"$(EOL))\
$(if $(FAN_TAC4_EN), #string STR_HWM1_FAN4_SPEED		      #language eng \"$(IT8728F_FAN_4_NAME)\"$(EOL))\
$(if $(FAN_TAC5_EN), #string STR_HWM1_FAN5_SPEED		      #language eng \"$(IT8728F_FAN_5_NAME)\"$(EOL))\
$(if $(IT8728F_VIN0_SUPPORT), #string STR_IT8728F_HMM_VIN0            #language eng \"$(IT8728F_VIN0_NAME)\"$(EOL))\
$(if $(IT8728F_VIN1_SUPPORT), #string STR_HWM1_VIN1                   #language eng \"$(IT8728F_VIN1_NAME)\"$(EOL))\
$(if $(IT8728F_VIN2_SUPPORT), #string STR_HWM1_VIN2                   #language eng \"$(IT8728F_VIN2_NAME)\"$(EOL))\
$(if $(IT8728F_VIN3_SUPPORT), #string STR_HWM1_VIN3                   #language eng \"$(IT8728F_VIN3_NAME)\"$(EOL))\
$(if $(IT8728F_VIN4_SUPPORT), #string STR_HWM1_VIN4                   #language eng \"$(IT8728F_VIN4_NAME)\"$(EOL))\
$(if $(IT8728F_VIN5_SUPPORT), #string STR_HWM1_VIN5                   #language eng \"$(IT8728F_VIN5_NAME)\"$(EOL))\
$(if $(IT8728F_VIN6_SUPPORT), #string STR_HWM1_VIN6                   #language eng \"$(IT8728F_VIN6_NAME)\"$(EOL))\
$(if $(IT8728F_3VSB_SUPPORT), #string STR_HWM1_VIN7                   #language eng \"$(IT8728F_3VSB_NAME)\"$(EOL))\
$(if $(IT8728F_VBAT_SUPPORT), #string STR_HWM1_VBAT                   #language eng \"$(IT8728F_VBAT_NAME)\"$(EOL))\
"\
> $(BUILD_DIR)/TempIT8728HwmStrings.uni
	$(IO_GENUNIFILE) $(BUILD_DIR)/TempIT8728HwmStrings.uni $@
