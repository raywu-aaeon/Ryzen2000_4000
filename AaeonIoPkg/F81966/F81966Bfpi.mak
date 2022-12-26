#**********************************************************************
#<AAEON_FHDR_START>
#----------------------------------------------------------------------
#
# Name: F81966Bfpi.mak
#
# Description: SIO module MAK file for AAEON BFPI
#
#----------------------------------------------------------------------
#<AAEON_FHDR_END>
#**********************************************************************
#Include this only for Static Setup 
#ifeq ("$(SIO_SETUP_USE_APTIO_4_STYLE)", "1")) 
#----------------------------------------------------------------------
Prepare : $(BUILD_DIR)/F81966HwmStrings.uni

#---------------------------------------------------------------------------
#       Generate strings for SIO HWM
#		1. F81966HwmStrings.uni
#---------------------------------------------------------------------------
$(BUILD_DIR)/F81966HwmStrings.uni : $(BUILD_DIR)/Token.mak
	$(ECHO) \
"/=# $(EOL)\
//---------------------------------------------------------------------------$(EOL)\
// Auto Generated SIO1 HWM Setup Strings.$(EOL)\
//---------------------------------------------------------------------------$(EOL)\
#include \"VFR.uni\"$(EOL)\
$(EOL)\
// Temperature - Start from SYSTEM_TEMP2 because SYSTEM_TEMP1 is left for CPU DTS.$(EOL)\
$(if $(F81966_TEMPERATURE_1_SUPPORT),#string STR_HWM1_SYSTEM_TEMP1		#language eng \"$(F81966_TEMPERATURE_1_NAME)\"$(EOL))\
$(if $(F81966_TEMPERATURE_2_SUPPORT),#string STR_HWM1_SYSTEM_TEMP2		#language eng \"$(F81966_TEMPERATURE_2_NAME)\"$(EOL))\
$(if $(F81966_TEMPERATURE_3_SUPPORT),#string STR_HWM1_SYSTEM_TEMP3		#language eng \"$(F81966_TEMPERATURE_3_NAME)\"$(EOL))\
$(if $(F81966_TEMPERATURE_4_SUPPORT),#string STR_HWM1_SYSTEM_TEMP4		#language eng \"$(F81966_TEMPERATURE_4_NAME)\"$(EOL))\
$(if $(F81966_TEMPERATURE_5_SUPPORT),#string STR_HWM1_SYSTEM_TEMP5		#language eng \"$(F81966_TEMPERATURE_5_NAME)\"$(EOL))\
$(if $(F81966_FAN_1_SUPPORT),#string STR_HWM1_FAN1_SPEED			#language eng \"$(F81966_FAN_1_NAME)\"$(EOL))\
$(if $(F81966_FAN_2_SUPPORT),#string STR_HWM1_FAN2_SPEED			#language eng \"$(F81966_FAN_2_NAME)\"$(EOL))\
$(if $(F81966_FAN_3_SUPPORT),#string STR_HWM1_FAN3_SPEED			#language eng \"$(F81966_FAN_3_NAME)\"$(EOL))\
$(if $(F81966_3VCC_SUPPORT),#string STR_HWM1_VCC3V				#language eng \"$(F81966_3VCC_NAME)\"$(EOL))\
$(if $(F81966_VIN1_VCORE_SUPPORT),#string STR_HWM1_VIN1				#language eng \"$(F81966_VIN1_VCORE_NAME)\"$(EOL))\
$(if $(F81966_VIN2_SUPPORT),#string STR_HWM1_VIN2				#language eng \"$(F81966_VIN2_NAME)\"$(EOL))\
$(if $(F81966_VIN3_SUPPORT),#string STR_HWM1_VIN3				#language eng \"$(F81966_VIN3_NAME)\"$(EOL))\
$(if $(F81966_VIN4_SUPPORT),#string STR_HWM1_VIN4				#language eng \"$(F81966_VIN4_NAME)\"$(EOL))\
$(if $(F81966_VSB3V_SUPPORT),#string STR_HWM1_VSB3V				#language eng \"$(F81966_VSB3V_NAME)\"$(EOL))\
$(if $(F81966_VBAT_SUPPORT),#string STR_HWM1_VBAT				#language eng \"$(F81966_VBAT_NAME)\"$(EOL))\
$(if $(F81966_5VSB_SUPPORT),#string STR_HWM1_VSB5V				#language eng \"$(F81966_5VSB_NAME)\"$(EOL))\
"\
> $(BUILD_DIR)/TempF81966HwmStrings.uni
	$(IO_GENUNIFILE) $(BUILD_DIR)/TempF81966HwmStrings.uni $@
