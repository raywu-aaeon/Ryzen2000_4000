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
# Name: IT8518.mak
#
# Description: SIO module MAK file.
#
#-----------------------------------------------------------------------
#<AMI_FHDR_END>
#**********************************************************************
#Include this only for Static Setup 
#ifeq ("$(SIO_SETUP_USE_APTIO_4_STYLE)", "1")) 
#---------------------------------------------------------------------------
Prepare : BuildPeiInitTable BuildSioElink 

#---------------------------------------------------------------------------
#       Generate SIO Pei elink table
#       1. Generate SIO PEI "IO Decode table"
#       2. Generate SIO PEI "IO initialization table"
#       3. Generate SIO PEI "Debug IO Decode table"
#       4. Generate SIO PEI "Debug IO initialization table"
#---------------------------------------------------------------------------
BuildPeiInitTable : $(SIO_PEI_TABLE_DEFINITIONS) $(BUILD_DIR)/token.mak
	$(ECHO) \
"$(if $(SIO_PEI_TABLE_DEFINITIONS), $(foreach S_DEF, $(SIO_PEI_TABLE_DEFINITIONS),#include<$(S_DEF)>$(EOL)))"\
>$(BUILD_DIR)/PrivateSioPeiInitTable.h

#---------------------------------------------------------------------------
#       Generate SIO elink table
#		1. SIO init string table for SioSetup.c
#---------------------------------------------------------------------------
BuildSioElink : $(BUILD_DIR)/token.mak
	$(ECHO) \
"\
#ifndef _SIO_ELINK_H_$(EOL)\
#define _SIO_ELINK_H_$(EOL)\
$(EOL)\
#define SIO_Init_Str_LIST $(SetupStrTableList)$(EOL)\
#endif$(EOL)\
"> $(BUILD_DIR)\SIOElink.h

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
