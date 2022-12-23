#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************

#/** @file Sb.mak
#    This make file builds south bridge SEC,PEI & DXE components and 
#    link them to respective binary. 
#
#*/

Prepare : $(BUILD_DIR)/SbDxeInitElink.h $(BUILD_DIR)/SbRunInitElink.h

$(BUILD_DIR)/SbDxeInitElink.h :  $(BUILD_DIR)/Token.mak
	$(ECHO) \
"#define SAVE_RESTORE_CALLBACK_LIST $(SbTimerSaveRestoreRegistersCallbacks)$(EOL)"\
> $@

$(BUILD_DIR)/SbRunInitElink.h : $(BUILD_DIR)/Token.mak
	$(ECHO) \
"#define SB_RUN_RESET_CALLBACK_LIST $(SB_RUN_RESET_CALLBACK_LIST)$(EOL)\
#define SB_OEM_S3_WARMRESET_CALLBACK_LIST $(SB_OEM_S3_WARMRESET_CALLBACK_LIST)$(EOL)"\
> $@

AMI_CSP_LIB_INCLUDE_FILES := \
 $(SB_INCLUDE_DIR)$(PATH_SLASH)Sb.h \
 $(SB_LIBRARY_INCLUDE_DIR)$(PATH_SLASH)SbCspLib.h \
 $(SB_LIBRARY_INCLUDE_DIR)$(PATH_SLASH)SbAmiCompatibility.h \
 $(SB_LIBRARY_INCLUDE_DIR)$(PATH_SLASH)AmiCmosLib.h \
 $(SB_LIBRARY_INCLUDE_DIR)$(PATH_SLASH)AmiPirqRouterLib.h \
 $(AmiChipsetPkg_Include_Library_DIR)$(PATH_SLASH)AmiChipsetIoLib.h \
$(AMI_CSP_LIB_INCLUDE_FILES)


#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2018, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
