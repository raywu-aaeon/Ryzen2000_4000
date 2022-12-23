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

Prepare: CBS_XML APCB_RV_FP5_SODIMM

ifeq ($(TOOL_CHAIN_TAG),VS2015)
ifeq ($(USE_EWDK), 1)
#
# EWDK :
#   <RVA9: The 15063 is windows RS2 version (EnterpriseWDK_rs2_release_15063_20170317-1834.zip). It might change depend on EWDK version>
#
Prepare_APCB_BUILD_ENV="$(EWDK_DIR)$(PATH_SLASH)BuildEnv$(PATH_SLASH)SetupBuildEnv.cmd"
export APCB_BUILD_WINDOWS_KIT=$(EWDK_DIR)$(PATH_SLASH)Program Files$(PATH_SLASH)Windows Kits$(PATH_SLASH)10$(PATH_SLASH)Lib$(PATH_SLASH)10.0.15063.0
export LIB:=$(EWDKVSDIR)$(PATH_SLASH)lib;$(APCB_BUILD_WINDOWS_KIT)$(PATH_SLASH)um$(PATH_SLASH)x86;$(APCB_BUILD_WINDOWS_KIT)$(PATH_SLASH)ucrt$(PATH_SLASH)x86
else
# VS2015
Prepare_APCB_BUILD_ENV="$(CCX64DIR)\vcvarsx86_amd64.bat"
endif
else
# WDDK.....
Prepare_APCB_BUILD_ENV=cd 
    export WINDDK_PATH := $(CCX86DIR)\..\..\..
	export PATH:=$(CCX64DIR);$(PATH)
	export INCLUDE:=$(WINDDK_PATH)$(PATH_SLASH)inc$(PATH_SLASH)crt;$(WINDDK_PATH)$(PATH_SLASH)inc$(PATH_SLASH)api:$(INCLUDE)
    export LIB:=$(WINDDK_PATH)$(PATH_SLASH)lib$(PATH_SLASH)Crt$(PATH_SLASH)amd64;$(WINDDK_PATH)$(PATH_SLASH)lib$(PATH_SLASH)win7$(PATH_SLASH)amd64;$(LIB)
endif

#workaround for BATCH .bin setting
export APCB_DATA_OUTPUT_FILE_EXT=exe

ifeq ($(BUILD_OS), $(BUILD_OS_WINDOWS))
	APCB_WORK_DIR := $(subst /,\,$(APCB_WORK_DIR))
endif
export APCB_WORK_DIR

APCB_RV_FP5_SODIMM:
	if exist $(APCB_SCRIPT_RV_FP5_SODIMM_DIR)$(PATH_SLASH)Include$(PATH_SLASH)token.h $(RM) $(APCB_SCRIPT_RV_FP5_SODIMM_DIR)$(PATH_SLASH)Include$(PATH_SLASH)token.h
	$(CP) $(BUILD_DIR)\token.h $(APCB_SCRIPT_RV_FP5_SODIMM_DIR)$(PATH_SLASH)Include
	
	if exist $(APCB_SCRIPT_RV_FP5_SODIMM_DIR)$(PATH_SLASH)Include$(PATH_SLASH)OemApcbCustomizedDefinitionsRavenFp5Sodimm.h $(RM) $(APCB_SCRIPT_RV_FP5_SODIMM_DIR)$(PATH_SLASH)Include$(PATH_SLASH)OemApcbCustomizedDefinitionsRavenFp5Sodimm.h
	$(CP) $(OEM_APCB_CUSTOMIZED_DIR)$(PATH_SLASH)OemApcbCustomizedDefinitionsRavenFp5Sodimm.h $(APCB_SCRIPT_RV_FP5_SODIMM_DIR)$(PATH_SLASH)Include
	
	if exist $(APCB_SCRIPT_RV_FP5_SODIMM_DIR)$(PATH_SLASH)Include$(PATH_SLASH)ApcbAutoGen.h $(RM) $(APCB_SCRIPT_RV_FP5_SODIMM_DIR)$(PATH_SLASH)Include$(PATH_SLASH)ApcbAutoGen.h
	$(CP) $(CBS_APCB_AUTO_GEN_RV_DIR)$(PATH_SLASH)ApcbAutoGenRV.h $(APCB_SCRIPT_RV_FP5_SODIMM_DIR)$(PATH_SLASH)Include$(PATH_SLASH)ApcbAutoGen.h
	
	cd $(APCB_SCRIPT_RV_FP5_SODIMM_DIR) && $(Prepare_APCB_BUILD_ENV) && $(APCB_CREATE_SCRIPT).bat clean build
	
	if not exist $(APCB_WORK_DIR)$(PATH_SLASH)$(RELEASE_RV_FP5_SODIMM) $(MKDIR) $(APCB_WORK_DIR)$(PATH_SLASH)$(RELEASE_RV_FP5_SODIMM)
	if exist $(APCB_WORK_DIR)$(PATH_SLASH)$(RELEASE_RV_FP5_SODIMM)$(PATH_SLASH)APCB_RV_D4.bin $(RM) $(APCB_WORK_DIR)$(PATH_SLASH)$(RELEASE_RV_FP5_SODIMM)$(PATH_SLASH)APCB_RV_D4.bin
	$(CP) $(APCB_WORK_DIR)$(PATH_SLASH)Release$(PATH_SLASH)APCB_RV_D4.bin $(APCB_WORK_DIR)$(PATH_SLASH)$(RELEASE_RV_FP5_SODIMM)$(PATH_SLASH)APCB_RV_D4.bin
	
	if exist $(APCB_SCRIPT_RV_FP5_SODIMM_DIR)$(PATH_SLASH)Include$(PATH_SLASH)token.h $(RM) $(APCB_SCRIPT_RV_FP5_SODIMM_DIR)$(PATH_SLASH)Include$(PATH_SLASH)token.h
	if exist $(APCB_SCRIPT_RV_FP5_SODIMM_DIR)$(PATH_SLASH)Include$(PATH_SLASH)OemApcbCustomizedDefinitionsRavenFp5Sodimm.h $(RM) $(APCB_SCRIPT_RV_FP5_SODIMM_DIR)$(PATH_SLASH)Include$(PATH_SLASH)OemApcbCustomizedDefinitionsRavenFp5Sodimm.h

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