#**********************************************************************
#<AAEON_FHDR_START>
#----------------------------------------------------------------------
#
# Name: IT85XX_EC1_Bfpi.mak
#
# Description: SIO module MAK file for AAEON BFPI
#
#----------------------------------------------------------------------
#<AAEON_FHDR_END>
#**********************************************************************
#**********************************************************************
#Include this only for Static Setup 
#----------------------------------------------------------------------
Prepare : $(BUILD_DIR)/It85xxEc1HwmStrings.uni
#---------------------------------------------------------------------------
#       Generate strings for SIO HWM
#		1. It85xxEc1HwmStrings.uni
#---------------------------------------------------------------------------
$(BUILD_DIR)/It85xxEc1HwmStrings.uni : $(BUILD_DIR)/Token.mak
	$(ECHO) \
"/=# $(EOL)\
//---------------------------------------------------------------------------$(EOL)\
// Auto Generated EC1 HWM Setup Strings.$(EOL)\
//---------------------------------------------------------------------------$(EOL)\
#include \"VFR.uni\"$(EOL)\
$(EOL)\
// Temperature - Start from SYSTEM_TEMP2 because SYSTEM_TEMP1 is left for CPU DTS.$(EOL)\
$(if $(IT851X_PECI_ENABLE), #string STR_EC1_IT85XX_THRM_SEN0         #language eng \"$(EC1_IT85XX_THRM_SEN0_NAME)\"$(EOL))\
$(if $(IT851X_TEMP1_ENABLE), #string STR_EC1_IT85XX_THRM_SEN1         #language eng \"$(EC1_IT85XX_THRM_SEN1_NAME)\"$(EOL))\
$(if $(IT851X_TEMP2_ENABLE), #string STR_EC1_IT85XX_THRM_SEN2         #language eng \"$(EC1_IT85XX_THRM_SEN2_NAME)\"$(EOL))\
$(if $(IT851X_TACH1_ENABLE), #string STR_EC1_IT85XX_FAN0         #language eng \"$(EC1_IT85XX_FAN0_NAME)\"$(EOL))\
$(if $(IT851X_TACH2_ENABLE), #string STR_EC1_IT85XX_FAN1         #language eng \"$(EC1_IT85XX_FAN1_NAME)\"$(EOL))\
$(if $(IT851X_VIN0_ENABLE), #string STR_EC1_IT85XX_VIN0         #language eng \"$(EC1_IT85XX_VIN0_NAME)\"$(EOL))\
$(if $(IT851X_VIN1_ENABLE), #string STR_EC1_IT85XX_VIN1         #language eng \"$(EC1_IT85XX_VIN1_NAME)\"$(EOL))\
$(if $(IT851X_VIN2_ENABLE), #string STR_EC1_IT85XX_VIN2         #language eng \"$(EC1_IT85XX_VIN2_NAME)\"$(EOL))\
$(if $(IT851X_VIN3_ENABLE), #string STR_EC1_IT85XX_VIN3         #language eng \"$(EC1_IT85XX_VIN3_NAME)\"$(EOL))\
$(if $(IT851X_VIN4_ENABLE), #string STR_EC1_IT85XX_VIN4         #language eng \"$(EC1_IT85XX_VIN4_NAME)\"$(EOL))\
$(if $(IT851X_VIN5_ENABLE), #string STR_EC1_IT85XX_VIN5         #language eng \"$(EC1_IT85XX_VIN5_NAME)\"$(EOL))\
$(if $(IT851X_VIN6_ENABLE), #string STR_EC1_IT85XX_VIN6         #language eng \"$(EC1_IT85XX_VIN6_NAME)\"$(EOL))\
$(if $(IT851X_VIN7_ENABLE), #string STR_EC1_IT85XX_VIN7         #language eng \"$(EC1_IT85XX_VIN7_NAME)\"$(EOL))\
"\
> $(BUILD_DIR)/TempIt85xxEc1HwmStrings.uni
	$(IO_GENUNIFILE) $(BUILD_DIR)/TempIt85xxEc1HwmStrings.uni $@
#---------------------------------------------------------------------------