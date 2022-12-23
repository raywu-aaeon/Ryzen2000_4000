#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2018, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************

#*************************************************************************
# $Header: $
#
# $Revision: $
#
# $Date: $
#*************************************************************************

#*************************************************************************
#<AMI_FHDR_START>
#
# Name:         Crb.mak
#
# Description:
#
#<AMI_FHDR_END>
#*************************************************************************
#Prepare : CreateDecFile

AMI_CSP_LIB_INCLUDE_FILES := \
$(CRB_DIR)/Include/Library/CrbLib.h \
$(AMI_CSP_LIB_INCLUDE_FILES)

CreateDecFile:
	$(ECHO) \
	"{$(EOL)\
	gsub(/DEFINE REF_CODE_PATH = ./,\"DEFINE REF_CODE_PATH = ../$(PLATFORM_RC_PACKAGE)\",$(DOUBLEDOLLAR)0)$(EOL)\
	print $(DOUBLEDOLLAR)0$(EOL)\
	}"$(EOL)\
> $(BUILD_DIR)/CrbPatchfile.txt
	$(GAWK) -f $(BUILD_DIR)/CrbPatchfile.txt $(CHIPSET_REF_DEC_PATH) > $(BUILD_DIR)$(PATH_SLASH)$(CHIPSET_REF_DEC_NAME)


End : CopyRomFile

.PHONY : CopyRomFile
CopyRomFile:
ifeq ($(SecureMod_SUPPORT),1)
ifneq ($(wildcard $(FWpriv)),$(FWpriv))
	$(ECHO) $(CP) $(UNSIGNED_BIOS_ROM) $(AMI_ROM)
	$(CP) $(UNSIGNED_BIOS_ROM) $(AMI_ROM)
else
ifeq ($(FWCAPSULE_FILE_FORMAT),0)
	$(ECHO) $(CP) $(FWCAPSULE_FILE) $(AMI_ROM)
	$(CP) $(FWCAPSULE_FILE) $(AMI_ROM)
endif
ifeq ($(FWCAPSULE_FILE_FORMAT),1)
	$(ECHO) $(CP) $(UNSIGNED_BIOS_ROM) $(AMI_ROM)
	$(CP) $(UNSIGNED_BIOS_ROM) $(AMI_ROM)
endif	
endif
else
	$(ECHO) $(CP) $(BUILD_DIR)$(PATH_SLASH)$(PLATFORM_NAME)$(PATH_SLASH)$(TARGET)_$(TOOL_CHAIN_TAG)$(PATH_SLASH)FV$(PATH_SLASH)AMIROM.fd  $(AMI_ROM)
	$(CP) $(BUILD_DIR)$(PATH_SLASH)$(PLATFORM_NAME)$(PATH_SLASH)$(TARGET)_$(TOOL_CHAIN_TAG)$(PATH_SLASH)FV$(PATH_SLASH)AMIROM.fd $(AMI_ROM)
endif

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