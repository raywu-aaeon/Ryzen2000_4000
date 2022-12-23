#***********************************************************************
#*                                                                     *
#*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
#*                                                                     *
#*      All rights reserved. Subject to AMI licensing agreement.       *
#*                                                                     *
#***********************************************************************

.PHONY : CLEAR_FVDXE_FILES MAKE_FVDXE_SIG_IMAGE MAKE_FVDXE_SIGN_SCRIPT MAKE_FVDXE_SIG_VERIFY_SCRIPT MOD_FWCAPSULE_HDR_FFS

#---------------------------------------------------------------------------
# Sign FV DXE and insert the signature inside final ROM image
#---------------------------------------------------------------------------

#---------------------------------------------------------------------------
# Clean & Prepare
#---------------------------------------------------------------------------
clean   : CLEAR_FVDXE_FILES
Prepare : CLEAR_FVDXE_FILES

CLEAR_FVDXE_FILES:
ifneq ("$(wildcard  $(ROM_LAYOUT_EX))", "")
	$(call fuss_RM_template,$(ROM_LAYOUT_EX))
endif

#---------------------------------------------------------------------------
# Should be the last step after creating of the ROM image. All fixups to the .ROM must be made prior to this step.
# check END target in the MAIN.MAK and all .MAK files to make sure this step is not overriden
#---------------------------------------------------------------------------
$(FVDXE_BUILD_TARGET): MAKE_FVDXE_SIG_IMAGE
MAKE_FVDXE_SIG_IMAGE: MAKE_FVDXE_SIGN_SCRIPT MAKE_FVDXE_SIG_VERIFY_SCRIPT

#--------------------------------------------------------------------------
# Create file $(ROM_LAYOUT_EX) with BIOS signing descriptor table
#--------------------------------------------------------------------------
ifneq ($(FUSS_FWCAPSULE_SUPPORT),1)
MAKE_FVDXE_SIGN_SCRIPT: $(ROM_LAYOUT_EX)
$(ROM_LAYOUT_EX): $(ROM_FILE_NAME)
	$(call fuss_fwcapsule_misc_template,Build FVDXE extended rom map,$(FWBUILD) $(ROM_FILE_NAME) $(FWBUILD_OPTION_CHAR)s $(FWBUILD_OPTION_CHAR)m $(ROM_LAYOUT_EX))
else
#--------------------------------------------------------------------------
# Secure Flash W/A: Add dependency to FWCAPSULE sign target on FVDXE sign
# Force SecFlash script to update the rom map file with un-signed FwCapsule Hdr range
#--------------------------------------------------------------------------
# Map FwCap region
MAKE_FVDXE_SIGN_SCRIPT: MOD_FWCAPSULE_HDR_FFS
# Sign
$(FWCAPSULE_FILE): MAKE_FVDXE_SIGN_SCRIPT
# Verify
MAKE_FVDXE_SIG_VERIFY_SCRIPT: $(FWCAPSULE_FILE)
endif

ifeq ($(INTEL_FIT_SUPPORT),1)
.PHONY : FVDXE_iFIT_DEPENDENCY Fit FitFirstEnd
Fit FitFirstEnd: FVDXE_iFIT_DEPENDENCY
MAKE_FVDXE_SIG_VERIFY_SCRIPT: Fit FitFirstEnd
FVDXE_iFIT_DEPENDENCY:
	$(call fuss_fwcapsule_misc_template,FVDXE key embed must run BEFORE the build targets: Fit FitFirstEnd)

$(eval $(call fuss_fwcapsule_sig_template,1,FVDXE_iFIT_DEPENDENCY,$(ROM_FILE_NAME),$(ROM_FILE_NAME),$(ROM_LAYOUT_EX),$(FVDXE_CRYPTOCON_CMDLINE),$(FVDXE_CERT_FORMAT),$(FVDXE_HASH),$(FVDXE_SIG_PSS),$(FVDXE_FWKEY_FILE_REPLACE),$(FVDXE_ROOTCAKEY),$(FVDXE_PRIVKEY),$(FVDXE_PUBKEY),$(FVDXE_KEY_PSWD)) )
endif

#---------------------------------------------------------------------------
#  Append script to sign measured FVs inside Aptio binary
#---------------------------------------------------------------------------
$(eval $(call fuss_fwcapsule_sig_template,0,MAKE_FVDXE_SIGN_SCRIPT,$(ROM_FILE_NAME),$(ROM_FILE_NAME),$(ROM_LAYOUT_EX),$(FVDXE_CRYPTOCON_CMDLINE),$(FVDXE_CERT_FORMAT),$(FVDXE_HASH),$(FVDXE_SIG_PSS),$(FVDXE_FWKEY_FILE_REPLACE),$(FVDXE_ROOTCAKEY),$(FVDXE_PRIVKEY),$(FVDXE_PUBKEY),$(FVDXE_KEY_PSWD)) )
#---------------------------------------------------------------------------
#   Append script to verify FVDXE signature in the Aptio binary
#---------------------------------------------------------------------------
ifneq ($(FUSS_FWCAPSULE_SUPPORT),1)
FVDXE_TEST_IMAGE := $(ROM_FILE_NAME)
else
FVDXE_TEST_IMAGE := $(FWCAPSULE_FILE)
endif
$(eval $(call fuss_fwcapsule_sig_template,2,MAKE_FVDXE_SIG_VERIFY_SCRIPT,$(FVDXE_TEST_IMAGE),,,$(FVDXE_CRYPTOCON_CMDLINE),,,,1))
#---------------------------------------------------------------------------
#   Build time warnings
#---------------------------------------------------------------------------
ifneq ($(wildcard $(FWpub)),$(FWpub))
$(warning *** BIOS will not boot unless the FV DXE is signed and verification key is set in IBB(FV_BB->FWKey ffs))
$(warning *** The key must be available at build OR inserted by Cryptocon using command option '-y -c1 -n -k pubkey -f bios.rom -o bios.rom')
endif
ifeq ($(FVDXE_CERT_FORMAT),1)
$(warning *** PKCS#7 Signed Firmare Volume)
ifeq ($(CONFIG_PEI_PKCS7),0)
$(error PKCS#7 certificate parser in PEI is disabled via SDL:CONFIG_PEI_PKCS7)
endif
ifeq ($(FVDXE_VERIFY_BEFORE_MRC),1)
$(error PKCS#7 certificate parser is mot available in SDL:FVDXE_VERIFY_BEFORE_MRC=1 configuration)
endif
endif