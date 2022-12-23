#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2019, American Megatrends, Inc.            **
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
#<AMI_FHDR_START>
#
# Name: AmiPsp.mak
#
# Description: Invokes ROM PSP update before Secure Flash tools
# 
#
#<AMI_FHDR_END>
#*************************************************************************

PrepareComboTable : ClearComboTablePspData
ifeq ($(BR_PSP_SUPPORT),1)
PrepareBr : ClearBrPspData
endif
ifeq ($(SM_PSP_SUPPORT),1)
PrepareSm : ClearSmPspData
endif
ifeq ($(RV_PSP_SUPPORT),1)
PrepareRv : ClearRvPspData
endif

.PHONY : AmiPspUpdate
AmiPspUpdate : $(PSP_MAK)

ifeq ($(SecureMod_SUPPORT),1)
ifeq ($(PSP_USE_HW_AUTH),1)
PsbProcess : $(FWCAPSULE_FILE_NAME)
End : PsbProcess
endif
UNSIGN_BIOS_ROM_FOR_PSP := $(UNSIGNED_BIOS_ROM)
else
UNSIGN_BIOS_ROM_FOR_PSP := $(BUILD_DIR)$(PATH_SLASH)$(PLATFORM_NAME)$(PATH_SLASH)$(TARGET)_$(TOOL_CHAIN_TAG)$(PATH_SLASH)FV$(PATH_SLASH)AMIROM.fd
End : AfterRom
AfterRom : $(UNSIGN_BIOS_ROM_FOR_PSP)
endif

ClearComboTablePspData:
ifeq ($(wildcard $(BUILD_DIR)$(PATH_SLASH)PspDataCombo.xml), $(BUILD_DIR)$(PATH_SLASH)PspDataCombo.xml)
	-$(RM) $(BUILD_DIR)$(PATH_SLASH)PspDataCombo.xml
endif

ClearBrPspData:
ifeq ($(wildcard $(BUILD_DIR)$(PATH_SLASH)PspDataBr.txt), $(BUILD_DIR)$(PATH_SLASH)PspDataBr.txt)
	-$(RM) $(BUILD_DIR)$(PATH_SLASH)PspDataBr.txt
endif

ClearSmPspData:
ifeq ($(wildcard $(BUILD_DIR)$(PATH_SLASH)PspDataSm.xml), $(BUILD_DIR)$(PATH_SLASH)PspDataSm.xml)
	-$(RM) $(BUILD_DIR)$(PATH_SLASH)PspDataSm.xml
endif

ClearRvPspData:
ifeq ($(wildcard $(BUILD_DIR)$(PATH_SLASH)PspDataRv.xml), $(BUILD_DIR)$(PATH_SLASH)PspDataRv.xml)
	-$(RM) $(BUILD_DIR)$(PATH_SLASH)PspDataRv.xml
endif

# DXE SIG relative start -------------------
PSP_SIGPAD := -y -l $(FWCAPSULE_MAX_HDR_SIZE)	
ifeq ($(FWCAPSULE_CERT_FORMAT),0)
# use key "-q" to include FwCap hdr into a signature calculation
# otherwise only Payload and RomMap are signed
PSP_SIGPAD += -q
endif

ifeq ($(strip $(FWSIG_KEY)),)
FWSIG_KEY := $(FWpriv)
endif
# DXE SIG relative end   -------------------

FV_BB_FILE = $(subst /,$(PATH_SLASH),$(OUTPUT_DIRECTORY))$(PATH_SLASH)$(TARGET)_$(TOOL_CHAIN_TAG)$(PATH_SLASH)FV$(PATH_SLASH)FV_BB.fv
FV_BB_HEADER = $(subst /,$(PATH_SLASH),$(OUTPUT_DIRECTORY))$(PATH_SLASH)$(TARGET)_$(TOOL_CHAIN_TAG)$(PATH_SLASH)FV$(PATH_SLASH)FV_BB_Header.raw
FV_BB_FILE_COMPRESS = $(subst /,$(PATH_SLASH),$(OUTPUT_DIRECTORY))$(PATH_SLASH)$(TARGET)_$(TOOL_CHAIN_TAG)$(PATH_SLASH)FV$(PATH_SLASH)FV_BB_Compress.fv
FV_BB_AMD_FEATURE_FV = $(subst /,$(PATH_SLASH),$(OUTPUT_DIRECTORY))$(PATH_SLASH)$(TARGET)_$(TOOL_CHAIN_TAG)$(PATH_SLASH)FV$(PATH_SLASH)FV_BB_AMD_FEATURE_FV.fv
FD_WITHOUT_BB = $(subst /,$(PATH_SLASH),$(OUTPUT_DIRECTORY))$(PATH_SLASH)$(TARGET)_$(TOOL_CHAIN_TAG)$(PATH_SLASH)FV$(PATH_SLASH)FdWithoutBB.fd
ORG_FV_BB_FILE = $(subst /,$(PATH_SLASH),$(OUTPUT_DIRECTORY))$(PATH_SLASH)$(TARGET)_$(TOOL_CHAIN_TAG)$(PATH_SLASH)FV$(PATH_SLASH)ORG_FV_BB.fv
MOD_FV_BB_FILE = $(subst /,$(PATH_SLASH),$(OUTPUT_DIRECTORY))$(PATH_SLASH)$(TARGET)_$(TOOL_CHAIN_TAG)$(PATH_SLASH)FV$(PATH_SLASH)MOD_FV_BB.fv
SPLIT_FILE_TMP = $(subst /,$(PATH_SLASH),$(OUTPUT_DIRECTORY))$(PATH_SLASH)$(TARGET)_$(TOOL_CHAIN_TAG)$(PATH_SLASH)FV$(PATH_SLASH)Tmp000.raw
AMIROM_ORG_FILE = $(subst /,$(PATH_SLASH),$(OUTPUT_DIRECTORY))$(PATH_SLASH)$(TARGET)_$(TOOL_CHAIN_TAG)$(PATH_SLASH)FV$(PATH_SLASH)ORG.fd

$(UNSIGN_BIOS_ROM_FOR_PSP) : AmiPspUpdate
ifeq ($(PSP_USE_HW_AUTH),0)
	$(PSPTOOL) -o . bb $(UNSIGN_BIOS_ROM_FOR_PSP) $(BUILD_DIR)\PspDataCombo.xml $(BUILD_DIR)\Psp_tempCombo.rom
	$(CP) $(BUILD_DIR)\Psp_tempCombo.rom $(UNSIGN_BIOS_ROM_FOR_PSP)
ifeq ($(BR_PSP_SUPPORT), 1)
	$(PSPTOOL_BR) bb $(BUILD_DIR)\PspDataBr.txt $(BUILD_DIR)\Psp_tempBr.rom
	$(CP) $(BUILD_DIR)\Psp_tempBr.rom $(UNSIGN_BIOS_ROM_FOR_PSP)
endif
ifeq ($(SM_PSP_SUPPORT), 1)
	$(PSPTOOL) -o . bb $(UNSIGN_BIOS_ROM_FOR_PSP) $(BUILD_DIR)\PspDataSm.xml $(BUILD_DIR)\Psp_tempSm.rom
	$(CP) $(BUILD_DIR)\Psp_tempSm.rom $(UNSIGN_BIOS_ROM_FOR_PSP)
endif
ifeq ($(RV_PSP_SUPPORT), 1)
	$(PSPTOOL) -o . bb $(UNSIGN_BIOS_ROM_FOR_PSP) $(BUILD_DIR)\PspDataRv.xml $(BUILD_DIR)\Psp_tempRv.rom
	$(CP) $(BUILD_DIR)\Psp_tempRv.rom $(UNSIGN_BIOS_ROM_FOR_PSP)
endif
endif #ifeq ($(PSP_USE_HW_AUTH),0)
ifeq ($(PSP_USE_DXE_AUTH),1)
	$(AMIPSPTOOL) $(UNSIGN_BIOS_ROM_FOR_PSP) -m $(DXE_SIG_ROM_LAYOUT) -mi $(ROM_LAYOUT_EX)
	$(CRYPTCON) -c $(FWpriv) -k $(FWSIG_KEY) $(PSP_SIGPAD) -g $(DXE_SIG_SECTION_MAK_GUID) -r $(DXE_SIG_ROM_LAYOUT) -f $(UNSIGN_BIOS_ROM_FOR_PSP) -o $(UNSIGN_BIOS_ROM_FOR_PSP)
endif #ifeq ($(PSP_USE_HW_AUTH),0)

####
#### FV_BB rebase with FV_BB compress
####
ifeq ($(PSP_FV_BB_COMPRESS),1)
	$(CP) $(UNSIGN_BIOS_ROM_FOR_PSP) $(AMIROM_ORG_FILE)
	$(EFI_TOOLS_DIR)\Split.exe -f $(UNSIGN_BIOS_ROM_FOR_PSP) -s $(FV_BB_OFFSET) -o $(FD_WITHOUT_BB) -t $(ORG_FV_BB_FILE)
	$(PSP_FV_BB_COMPRESS_COMMAND) $(FV_BB_FILE) $(FV_BB_FILE_COMPRESS) $(PSP_FV_BB_COMPRESSED_SIZE)
	$(EFI_TOOLS_DIR)\Split.exe -f $(ORG_FV_BB_FILE) -s $(PSP_FV_BB_FVH_SIZE) -o $(FV_BB_HEADER) -t $(SPLIT_FILE_TMP)
	$(CP) $(FD_WITHOUT_BB) /B + $(FV_BB_HEADER) /B + $(FV_BB_FILE_COMPRESS) /B $(UNSIGN_BIOS_ROM_FOR_PSP) /B
	$(CP) $(FV_BB_HEADER) /B + $(FV_BB_FILE_COMPRESS) /B $(MOD_FV_BB_FILE) /B
	$(ECHO) Process PSP AMD Firmware Feature, the original BB size is "$(PSP_FV_BB_ORIGINAL_SIZE)".
	$(ECHO) The compressed size is "$(PSP_FV_BB_COMPRESSED_SIZE)" and occupy "$(PSP_FV_BB_AMD_FEATURE_SIZE)" in AMI ROM.
	$(ECHO) The following is the content of original FV_BB.
	$(FWBUILD) $(FV_BB_FILE) $(FWBUILD_OPTION_CHAR)v
endif

PRE_PSB_FWCAPSULE_FILE_NAME := $(FWCAPSULE_FILE_NAME)
PSB_PATH_IN_BUILD_DIR = $(BUILD_DIR)$(PATH_SLASH)PSB

PsbProcess : AmiPspUpdate
	-$(RMDIR) PSB
	-$(RMDIR) $(PSB_PATH_IN_BUILD_DIR)
	if not exist PSB $(MKDIR) PSB
	if not exist $(PSB_PATH_IN_BUILD_DIR) $(MKDIR) $(PSB_PATH_IN_BUILD_DIR)
	$(RM) PSB\*.*
	$(RM) $(PSB_PATH_IN_BUILD_DIR)\*.*
# Get FV_BB
	$(EFI_TOOLS_DIR)\Split.exe -f $(PRE_PSB_FWCAPSULE_FILE_NAME) -s $(PSP_FV_BB_OFFSET) -o $(BUILD_DIR)$(PATH_SLASH)FV_NO_BB.bin -t $(BUILD_DIR)$(PATH_SLASH)Psp_Tmp1.bin
	$(EFI_TOOLS_DIR)\Split.exe -f $(BUILD_DIR)$(PATH_SLASH)Psp_Tmp1.bin -s $(PSP_FV_BB_SIZE) -o $(PSB_PATH_IN_BUILD_DIR)$(PATH_SLASH)PSP_FV_BB.bin -t $(BUILD_DIR)$(PATH_SLASH)Psp_Tmp2.bin
# Bristol
ifeq ($(BR_PSP_SUPPORT), 1)
	if not exist PSB\BR $(MKDIR) PSB\BR
	if not exist $(PSB_PATH_IN_BUILD_DIR)\BR $(MKDIR) $(PSB_PATH_IN_BUILD_DIR)\BR
	$(RM) PSB\BR\*.*
	$(RM) $(PSB_PATH_IN_BUILD_DIR)\BR\*.*
	$(PSPTOOL_BR) bd $(BUILD_DIR)\PspDataBr.txt $(PSB_PATH_IN_BUILD_DIR)\BR\BiosDirHeader.bin
	$(CP) /b $(PSB_PATH_IN_BUILD_DIR)\PSP_FV_BB.bin+$(PSB_PATH_IN_BUILD_DIR)\BR\BiosDirHeader.bin $(PSB_PATH_IN_BUILD_DIR)\BR\RTM.bin
	$(CP) $(PSB_PATH_IN_BUILD_DIR)\BR\RTM.bin PSB\BR\RTM.bin
	$(ECHO) "Wait user send $(PSB_PATH_IN_BUILD_DIR)\BR\RTM.bin to AMD server to sign their BIOS image."
	@$(AmiPspPkg_DIR)\WaitStart.cmd BR
	if exist $(BIOS_RTM_SIGNATURE_FILENAME_BR) $(RM) $(BIOS_RTM_SIGNATURE_FILENAME_BR)
	$(CP) PSB\BR\RTM.sig $(BIOS_RTM_SIGNATURE_FILENAME_BR)
endif
# Summit
ifeq ($(SM_PSP_SUPPORT), 1)
	if not exist PSB\SM $(MKDIR) PSB\SM
	if not exist $(PSB_PATH_IN_BUILD_DIR)\SM $(MKDIR) $(PSB_PATH_IN_BUILD_DIR)\SM
	$(RM) PSB\SM\*.*
	$(RM) $(PSB_PATH_IN_BUILD_DIR)\SM\*.*
	$(PSPTOOL) -o $(PSB_PATH_IN_BUILD_DIR)\SM bd $(PRE_PSB_FWCAPSULE_FILE_NAME) $(BUILD_DIR)\PspDataSm.xml
	$(CP) /b $(PSB_PATH_IN_BUILD_DIR)\PSP_FV_BB.bin+$(PSB_PATH_IN_BUILD_DIR)\SM\BiosDirHeaderL1.bin $(PSB_PATH_IN_BUILD_DIR)\SM\RTM_L1.bin
	$(CP) /b $(PSB_PATH_IN_BUILD_DIR)\SM\RTM_L1.bin+$(PSB_PATH_IN_BUILD_DIR)\SM\BiosDirHeaderL2.bin $(PSB_PATH_IN_BUILD_DIR)\SM\RTM_L1_L2.bin
	$(CP) $(PSB_PATH_IN_BUILD_DIR)\SM\RTM_L1.bin PSB\SM\RTM_L1.bin
	$(CP) $(PSB_PATH_IN_BUILD_DIR)\SM\RTM_L1_L2.bin PSB\SM\RTM_L1_L2.bin
	$(ECHO) "Wait user send $(PSB_PATH_IN_BUILD_DIR)\SM\RTM_L1.sig and RTM_L1_L2.sig to AMD server to sign their BIOS image."
	@$(AmiPspPkg_DIR)\WaitStart.cmd SM
	if exist $(BIOS_LEVEL_1_RTM_SIGNATURE_FILENAME_ZP) $(RM) $(BIOS_LEVEL_1_RTM_SIGNATURE_FILENAME_ZP)
	if exist $(BIOS_LEVEL_2_RTM_SIGNATURE_FILENAME_ZP) $(RM) $(BIOS_LEVEL_2_RTM_SIGNATURE_FILENAME_ZP)
	$(CP) PSB\SM\RTM_L1.sig $(BIOS_LEVEL_1_RTM_SIGNATURE_FILENAME_ZP)
	$(CP) PSB\SM\RTM_L1_L2.sig $(BIOS_LEVEL_2_RTM_SIGNATURE_FILENAME_ZP)
endif
# Raven
ifeq ($(RV_PSP_SUPPORT), 1)
	if not exist PSB\RV $(MKDIR) PSB\RV
	if not exist $(PSB_PATH_IN_BUILD_DIR)\RV $(MKDIR) $(PSB_PATH_IN_BUILD_DIR)\RV
	$(RM) PSB\RV\*.*
	$(RM) $(PSB_PATH_IN_BUILD_DIR)\RV\*.*
	$(PSPTOOL) -o $(PSB_PATH_IN_BUILD_DIR)\RV bd $(PRE_PSB_FWCAPSULE_FILE_NAME) $(BUILD_DIR)\PspDataRv.xml
	$(CP) /b $(PSB_PATH_IN_BUILD_DIR)\PSP_FV_BB.bin+$(PSB_PATH_IN_BUILD_DIR)\RV\BiosDirHeaderL1.bin $(PSB_PATH_IN_BUILD_DIR)\RV\RTM_L1.bin
	$(CP) /b $(PSB_PATH_IN_BUILD_DIR)\RV\RTM_L1.bin+$(PSB_PATH_IN_BUILD_DIR)\RV\BiosDirHeaderL2.bin $(PSB_PATH_IN_BUILD_DIR)\RV\RTM_L1_L2.bin
	$(CP) $(PSB_PATH_IN_BUILD_DIR)\RV\RTM_L1.bin PSB\RV\RTM_L1.bin
	$(CP) $(PSB_PATH_IN_BUILD_DIR)\RV\RTM_L1_L2.bin PSB\RV\RTM_L1_L2.bin
	$(ECHO) "Wait user send $(PSB_PATH_IN_BUILD_DIR)\RV\RTM_L1.sig and RTM_L1_L2.sig to AMD server to sign their BIOS image."
	@$(AmiPspPkg_DIR)\WaitStart.cmd RV
	if exist $(BIOS_LEVEL_1_RTM_SIGNATURE_FILENAME_RV) $(RM) $(BIOS_LEVEL_1_RTM_SIGNATURE_FILENAME_RV)
	if exist $(BIOS_LEVEL_2_RTM_SIGNATURE_FILENAME_RV) $(RM) $(BIOS_LEVEL_2_RTM_SIGNATURE_FILENAME_RV)
	$(CP) PSB\RV\RTM_L1.sig $(BIOS_LEVEL_1_RTM_SIGNATURE_FILENAME_RV)
	$(CP) PSB\RV\RTM_L1_L2.sig $(BIOS_LEVEL_2_RTM_SIGNATURE_FILENAME_RV)
endif
# Build signed PSP BIOS
	$(PSPTOOL) -o . bb $(PRE_PSB_FWCAPSULE_FILE_NAME) $(BUILD_DIR)\PspDataCombo.xml $(BUILD_DIR)\Psp_tempCombo.rom
	$(CP) $(BUILD_DIR)\Psp_tempCombo.rom $(PRE_PSB_FWCAPSULE_FILE_NAME)
ifeq ($(BR_PSP_SUPPORT), 1)
	$(CP) $(PRE_PSB_FWCAPSULE_FILE_NAME) $(UNSIGN_BIOS_ROM_FOR_PSP)
	$(PSPTOOL_BR) bb $(BUILD_DIR)\PspDataBr.txt $(BUILD_DIR)\Psp_tempBr.rom
	$(CP) $(BUILD_DIR)\Psp_tempBr.rom $(PRE_PSB_FWCAPSULE_FILE_NAME)
endif
ifeq ($(SM_PSP_SUPPORT), 1)
	$(PSPTOOL) -o . bb $(PRE_PSB_FWCAPSULE_FILE_NAME) $(BUILD_DIR)\PspDataSm.xml $(BUILD_DIR)\Psp_tempSm.rom
	$(CP) $(BUILD_DIR)\Psp_tempSm.rom $(PRE_PSB_FWCAPSULE_FILE_NAME)
endif
ifeq ($(RV_PSP_SUPPORT), 1)
	$(PSPTOOL) -o . bb $(PRE_PSB_FWCAPSULE_FILE_NAME) $(BUILD_DIR)\PspDataRv.xml $(BUILD_DIR)\Psp_tempRv.rom
	$(CP) $(BUILD_DIR)\Psp_tempRv.rom $(PRE_PSB_FWCAPSULE_FILE_NAME)
endif
	-$(CRYPTCON) $(CRYPTOCON_CMDLINE_SIG) -f $(PRE_PSB_FWCAPSULE_FILE_NAME) -o $(PRE_PSB_FWCAPSULE_FILE_NAME)

#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2019, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************
