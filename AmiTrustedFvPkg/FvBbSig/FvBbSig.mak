#***********************************************************************
#*                                                                     *
#*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
#*                                                                     *
#*      All rights reserved. Subject to AMI licensing agreement.       *
#*                                                                     *
#***********************************************************************

.PHONY : CLEAR_FVBB_FILES MAKE_FVBB_SIG_IMAGE MAKE_FVBB_SIGN_SCRIPT MAKE_FVBB_SIG_VERIFY_SCRIPT

#---------------------------------------------------------------------------
# Sign FV BB and insert the signature inside FVBB in ROM image
#---------------------------------------------------------------------------

#---------------------------------------------------------------------------
#        Prepare FVBB files
#---------------------------------------------------------------------------
clean   : CLEAR_FVBB_FILES
Prepare : CLEAR_FVBB_FILES

CLEAR_FVBB_FILES:
ifneq ("$(wildcard  $(ROM_LAYOUT_FVBB))", "")
	-$(RM) $(ROM_LAYOUT_FVBB)
endif

#---------------------------------------------------------------------------
# Should be the last step after creating of the ROM image. All fixups to the .ROM must be made prior to this step.
# check END target in the MAIN.MAK and all .MAK files to make sure this step is not overriden
#---------------------------------------------------------------------------
$(FVBB_BUILD_TARGET): MAKE_FVBB_SIG_IMAGE
MAKE_FVBB_SIG_IMAGE: MAKE_FVBB_SIGN_SCRIPT MAKE_FVBB_SIG_VERIFY_SCRIPT

#---------------------------------------------------------------------------
# Should be the last step after creating of the ROM image.
# All fixups to the .ROM must be made prior to this step.
#---------------------------------------------------------------------------
# Set up dependency on AMD PSB, iBootGuard and Secure Flash build targets
#--------------------------------------------------------------------------
ifeq ($(FvDxeSig_SUPPORT),1)
MAKE_FVDXE_SIGN_SCRIPT: MAKE_FVBB_SIGN_SCRIPT
endif

ifeq ($(FUSS_FWCAPSULE_SUPPORT),1)
$(FWCAPSULE_FILE): MAKE_FVBB_SIGN_SCRIPT
MAKE_FVBB_SIG_VERIFY_SCRIPT: $(FWCAPSULE_FILE)
endif

ifeq ($(INTEL_FIT_SUPPORT),1)
.PHONY : FVBB_iFIT_DEPENDENCY Fit FitFirstEnd

MAKE_FVBB_SIGN_SCRIPT MAKE_FVBB_SIG_VERIFY_SCRIPT: FVBB_iFIT_DEPENDENCY
FVBB_iFIT_DEPENDENCY: Fit FitFirstEnd
	$(call fuss_fwcapsule_misc_template,FVBB sign should run AFTER the build targets: Fit FitFirstEnd)

endif
#--------------------------------------------------------------------------
# Create file $(ROM_LAYOUT_FVBB) with BIOS signing descriptor table
#--------------------------------------------------------------------------
MAKE_FVBB_SIGN_SCRIPT: $(ROM_LAYOUT_FVBB)
$(ROM_LAYOUT_FVBB): $(ROM_FILE_NAME)
	$(call fuss_fwcapsule_misc_template,Build FvBB extended rom map,$(FWBUILD) $(ROM_FILE_NAME) $(FWBUILD_OPTION_CHAR)s $(FWBUILD_OPTION_CHAR)mbb $(ROM_LAYOUT_FVBB))

#--------------------------------------------------------------------------
#   Append script to sign FV BB inside Aptio binary
#---------------------------------------------------------------------------
$(eval $(call fuss_fwcapsule_sig_template,0,MAKE_FVBB_SIGN_SCRIPT,$(ROM_FILE_NAME),$(ROM_FILE_NAME),$(ROM_LAYOUT_FVBB),$(FV_BB_CRYPTOCON_CMDLINE),$(FVBB_CERT_FORMAT),$(FVBB_HASH),$(FVBB_SIG_PSS),0,$(FVBB_ROOTCAKEY),$(FVBB_PRIVKEY),$(FVBB_PUBKEY),$(FVBB_KEY_PSWD)) )

#--------------------------------------------------------------------------
#   Append script to verify FVBB signature in the Aptio binary 
#--------------------------------------------------------------------------
ifneq ($(FUSS_FWCAPSULE_SUPPORT),1)
FVBB_TEST_IMAGE := $(ROM_FILE_NAME)
else
FVBB_TEST_IMAGE := $(FWCAPSULE_FILE)
endif
$(eval $(call fuss_fwcapsule_sig_template,2,MAKE_FVBB_SIG_VERIFY_SCRIPT,$(FVBB_TEST_IMAGE),,,$(FV_BB_CRYPTOCON_CMDLINE)) )
