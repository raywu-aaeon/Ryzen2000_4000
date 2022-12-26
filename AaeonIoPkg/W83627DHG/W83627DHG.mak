#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
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
#-----------------------------------------------------------------------
#
# Name:  <W83627DHG.mak>
#
# Description:	
#				
#
#-----------------------------------------------------------------------
#<AMI_FHDR_END>
#**********************************************************************
#Include this only for Static Setup 
#ifeq ("$(SIO_SETUP_USE_APTIO_4_STYLE)", "1")) 
#---------------------------------------------------------------------------
Prepare : BuildPeiInitTable BuildSioElink $(BUILD_DIR)/W83627HwmStrings.uni

#---------------------------------------------------------------------------
#       Generate SIO Pei elink table
#       1. Generate SIO PEI "IO Decode table"
#       2. Generate SIO PEI "IO initialization table"
#       3. Generate SIO PEI "Debug IO Decode table"
#       4. Generate SIO PEI "Debug IO initialization table"
#---------------------------------------------------------------------------
BuildPeiInitTable : $(SIO_PEI_TABLE_DEFINITIONS) $(BUILD_DIR)/Token.mak
	$(ECHO) \
"$(if $(SIO_PEI_TABLE_DEFINITIONS), $(foreach S_DEF, $(SIO_PEI_TABLE_DEFINITIONS),#include<$(S_DEF)>$(EOL)))"\
>$(BUILD_DIR)/PrivateSioPeiInitTable.h

#---------------------------------------------------------------------------
#       Generate SIO elink table
#		1. SIO init string table for SioSetup.c
#---------------------------------------------------------------------------
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
#		1. W83627HwmStrings.uni
#---------------------------------------------------------------------------
$(BUILD_DIR)/W83627HwmStrings.uni : $(BUILD_DIR)/Token.mak
	$(ECHO) \
"/=# $(EOL)\
//---------------------------------------------------------------------------$(EOL)\
// Auto Generated SIO1 HWM Setup Strings.$(EOL)\
//---------------------------------------------------------------------------$(EOL)\
#include \"VFR.uni\"$(EOL)\
$(EOL)\
// Temperature - Start from SYSTEM_TEMP2 because SYSTEM_TEMP1 is left for CPU DTS.$(EOL)\
$(if $(W83627DHG_SYSTIN_SUPPORT), #string STR_HWM1_SYSTEM_TEMP1         #language eng \"$(W83627DHG_SYSTIN_NAME)\"$(EOL))\
$(if $(W83627DHG_CPUTIN_SUPPORT), #string STR_HWM1_SYSTEM_TEMP2         #language eng \"$(W83627DHG_CPUTIN_NAME)\"$(EOL))\
$(if $(W83627DHG_AUXTIN_SUPPORT), #string STR_HWM1_SYSTEM_TEMP3         #language eng \"$(W83627DHG_AUXTIN_NAME)\"$(EOL))\
$(if $(W83627DHG_SYSFANIN_SUPPORT), #string STR_HWM1_FAN1_SPEED         #language eng \"$(W83627DHG_SYSFANIN_NAME)\"$(EOL))\
$(if $(W83627DHG_CPUFANIN0_SUPPORT), #string STR_HWM1_FAN2_SPEED         #language eng \"$(W83627DHG_CPUFANIN0_NAME)\"$(EOL))\
$(if $(W83627DHG_AUXFANIN0_SUPPORT), #string STR_HWM1_FAN3_SPEED         #language eng \"$(W83627DHG_AUXFANIN0_NAME)\"$(EOL))\
$(if $(W83627DHG_CPUFANIN1_SUPPORT), #string STR_HWM1_FAN4_SPEED         #language eng \"$(W83627DHG_CPUFANIN1_NAME)\"$(EOL))\
$(if $(W83627DHG_AUXFANIN1_SUPPORT), #string STR_HWM1_FAN5_SPEED         #language eng \"$(W83627DHG_AUXFANIN1_NAME)\"$(EOL))\
$(if $(W83627DHG_VCORE_SUPPORT), #string STR_W83627DHG_HWM1_VCORE        #language eng \"$(W83627DHG_VCORE_NAME)\"$(EOL))\
$(if $(W83627DHG_VIN0_SUPPORT), #string STR_W83627DHG_HWM1_VIN0         #language eng \"$(W83627DHG_VIN0_NAME)\"$(EOL))\
$(if $(W83627DHG_VIN1_SUPPORT), #string STR_HWM1_VIN1         #language eng \"$(W83627DHG_VIN1_NAME)\"$(EOL))\
$(if $(W83627DHG_VIN2_SUPPORT), #string STR_HWM1_VIN2         #language eng \"$(W83627DHG_VIN2_NAME)\"$(EOL))\
$(if $(W83627DHG_VIN3_SUPPORT), #string STR_HWM1_VIN3         #language eng \"$(W83627DHG_VIN3_NAME)\"$(EOL))\
$(if $(W83627DHG_VCC3_SUPPORT), #string STR_HWM1_VCC3V        #language eng \"$(W83627DHG_VCC3_NAME)\"$(EOL))\
$(if $(W83627DHG_AVCC_SUPPORT), #string STR_W83627DHG_HWM1_VACC         #language eng \"$(W83627DHG_AVCC_NAME)\"$(EOL))\
$(if $(W83627DHG_VSB3_SUPPORT), #string STR_HWM1_VSB3V        #language eng \"$(W83627DHG_VSB3_NAME)\"$(EOL))\
$(if $(W83627DHG_VBAT_SUPPORT), #string STR_HWM1_VBAT         #language eng \"$(W83627DHG_VBAT_NAME)\"$(EOL))\
"\
> $(BUILD_DIR)/TempW83627HwmStrings.uni
	$(IO_GENUNIFILE) $(BUILD_DIR)/TempW83627HwmStrings.uni $@

#---------------------------------------------------------------------------
#endif
#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
