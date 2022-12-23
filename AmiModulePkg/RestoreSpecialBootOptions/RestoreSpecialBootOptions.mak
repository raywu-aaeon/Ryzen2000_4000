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

#**********************************************************************
#<AMI_FHDR_START>
#
# Name:	RestoreSpecialBootOptions.mak
#
# Description: Makefile for creating defines from eLinks.	
#
#<AMI_FHDR_END>
#**********************************************************************
Prepare : $(BUILD_DIR)/RestoreSpecialBootOptions.h

RESTORED_BOOT_OPTION_NAMES := $(subst {,L\",$(RESTORED_BOOT_OPTION_NAMES)) #Replace { to L"
RESTORED_BOOT_OPTION_NAMES := $(subst },\",$(RESTORED_BOOT_OPTION_NAMES)) #Replace } to "

$(BUILD_DIR)/RestoreSpecialBootOptions.h : $(BUILD_DIR)/Token.h $(RestoreSpecialBootOptions_DIR)/RestoreSpecialBootOptions.mak
	$(ECHO) \
"#define RESTORED_BOOT_OPTION_NAMES $(RESTORED_BOOT_OPTION_NAMES)"\
>$(BUILD_DIR)/RestoreSpecialBootOptions.h

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
