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

#**********************************************************************
# $Header: $
#
# $Revision: $
#
# $Date: $
#**********************************************************************
#<AMI_FHDR_START>
#
# Name:			RsdpPlus.mak
#
# Description:	
#
#<AMI_FHDR_END>
#**********************************************************************

#RSDPPLUS_CFLAGS=$(CFLAGS) \
#       -I $(TSEBIN_DIR)\Inc \
#       -I $(TSEBIN_DIR)

#AMITSEBin : $(BUILD_DIR)\RsdpPlusLink.obj $(BUILD_DIR)\RsdpPlus.obj

#$(BUILD_DIR)\RsdpPlusLink.obj : $(RsdpPlus_DIR)\RsdpPlusLink.c
#       $(CC) $(RSDPPLUS_CFLAGS) /Fo$(BUILD_DIR)\RsdpPlusLink.obj $(RsdpPlus_DIR)\RsdpPlusLink.c

#$(BUILD_DIR)\RsdpPlus.obj : $(RsdpPlus_DIR)\RsdpPlus.c
#       $(CC) $(RSDPPLUS_CFLAGS) /Fo$(BUILD_DIR)\RsdpPlus.obj $(RsdpPlus_DIR)\RsdpPlus.c

#CORE_DXEBin : $(BUILD_DIR)\ManageShadowRam.obj

#$(BUILD_DIR)\ManageShadowRam.obj : $(RsdpPlus_DIR)\ManageShadowRam.c
#    $(CC) $(CFLAGS) \
#       /D\"UPDATE_E000_SHADOW_RAM_HOOK_LIST=$(UpdateE000ShadowRamHook)\" \
#       /D\"UPDATE_F000_SHADOW_RAM_HOOK_LIST=$(UpdateF000ShadowRamHook)\" \
        /D\"CSM_ON_LINK_HOOK_LIST=$(CsmOnLinkHook)\" \
#       /Fo$(BUILD_DIR)\ManageShadowRam.obj $(RsdpPlus_DIR)\ManageShadowRam.c

Prepare : RsdpPluseElink

RsdpPluseElink : $(BUILD_DIR)/RsdpPlusElink.h

$(BUILD_DIR)/RsdpPlusElink.h : $(BUILD_DIR)/Token.h
	$(ECHO) \
"#define UPDATE_E000_SHADOW_RAM_HOOK_LIST $(UpdateE000ShadowRamHook)$(EOL)\
#define UPDATE_F000_SHADOW_RAM_HOOK_LIST $(UpdateF000ShadowRamHook)$(EOL)\
#define CSM_ON_LINK_HOOK_LIST $(CsmOnLinkHook)$(EOL)\
#define ENABLE_RUNTIME_SHADOW_WRITE_HOOK_LIST $(EnableRuntimeShadowWriteHook)"\
>$(BUILD_DIR)/RsdpPlusElink.h

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