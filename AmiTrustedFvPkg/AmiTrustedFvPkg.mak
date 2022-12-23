#***********************************************************************
#*                                                                     *
#*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
#*                                                                     *
#*      All rights reserved. Subject to AMI licensing agreement.       *
#*                                                                     *
#***********************************************************************

.PHONY : CLEAR_FUSS_FILE

#--------------------------------------------------------------------------
# Miscellaneous template definitions
#--------------------------------------------------------------------------
ifneq ($(BUILD_OS), $(BUILD_OS_LINUX))
define fuss_CP_template =
@if not exist [$(2)$(PATH_SLASH)$(notdir $(1))] $(CP) $(1) $(2)

endef
define fuss_RM_template =
@if exist $(1) $(RM) $(1)
endef
define fuss_SET_template =
@if not [\"$(3)\"]==[\"\"] (SET $(1)=$(3)) ELSE (SET $(1)=$(2))
endef
define fuss_SET_choice_template =
@if not [\"$(4)\"]==[\"\"] (if [$(4)]==[0] (SET $(1)=$(2)) ELSE (SET $(1)=$(3))) ELSE (SET $(1)=$(2))
endef
define fuss_IF_choice_template =
@if [\"$(1)\"]==[\"$(2)\"] ($(3))
endef
fuss_error=@IF NOT %%ERRORLEVEL%%==0 (EXIT /b %%ERRORLEVEL%%)
fuss_error2=@IF NOT %%ERRORLEVEL%%==0 (EXIT /b %%ERRORLEVEL%%)
LINUX_BASH=
Set:=@SET
Echo:=@echo
Env2=%%$(1)%%
Env=%%$(1)%%
Arg=%%$(1)
Dollar=$$
InvokeBat:=call
else
define fuss_CP_template =
if [ ! -f $(2)$(PATH_SLASH)$(notdir $(1)) ]; then $(CP) $(1) $(2); fi

endef
define fuss_RM_template =
if [ -f $(1) ]; then $(RM) $(1); fi
endef
define fuss_SET_template =
if [ \"""$(3)""\" ]; then $(Set) $(1)=""$(3)""; else $(Set) $(1)=\"""$(2)""\"; fi
endef
define fuss_SET_choice_template =
if [ \"""$(4)""\" ]; then if [  \"""$(4)""\" = "0" ]; then $(Set) $(1)=\"""$(2)""\" ; else $(Set) $(1)=\"""$(3)""\" ;fi else $(Set) $(1)=\"""$(2)""\" ; fi
endef
define fuss_IF_choice_template =
if [ \"""$(1)""\" = \"""$(2)""\" ]; then $(3); fi
endef
fuss_error= if [ \$$? != 0 ]; then exit \$$?; fi
fuss_error2= if [ \$$$$? != 0 ]; then exit \$$$$?; fi
LINUX_BASH:=\#!/bin/bash
##!/usr/bin/env bash
Set:=export
Echo:=echo
Env2= $$$$"$(1)"
Env= $$"$(1)"
Arg= $$"$(1)"
Dollar=\\$$
#InvokeBat =

endif

#--------------------------------------------------------------------------
# Miscellaneous output template
#--------------------------------------------------------------------------
#1.Job caption text: FVDXE, FVBB etc.
#2.Executed command line1
#3.Executed command line2(opt)
define fuss_fwcapsule_misc_template =
	@$(ECHO) "$(Echo) ----$(1)$(EOL)$(2)$(EOL)$(3)$(EOL)" >> $(AMIROM_FUSS_FILE)

endef
ifeq ($(FUSS_LAUNCH_AT_BUILD),1)
define fuss_fwcapsule_misc_template +=
	$(Echo) ----$(1)
	$(2)
	$(3)

endef
endif

#--------------------------------------------------------------------------
# Sign FwCapsule script
#--------------------------------------------------------------------------
#1.Job: 0-Capsule Sign (-c1 or -c2), 1-Map, 2-Verify
#2.Job caption text(serves as a make target): FVDXE_Sign, FVBB_Verify etc.
#3.Input image
#4.Output image
#5.ROM_LAYOUT file
#6.Custom CRYPTCON_CMDLINE
#7.FwCapsule signed certificate type: 0-PKCS#1(RSA2048_SHA256), 1-PKCS#7
#8.Signature Hash algorithm: sha256, sha384 and sha512
#9.Signature padding schema: 0-RSASSA-PKCS1v1.5, 1-RSASSA-PSS
#10.FWkey embed/replace
#11.Platform RootCA certificate or a key. To be embedded into FWkey store by cryptocon
#12.Signer Private Key identifier: Private Key file or Key Container Name, Key ID, Key Hash etc.
#13.Signer Certificate identifier: Public key file, Certificate Subject Name
#14.(opt)Signer Key password
#15.(opt)Cryptographic Storage Provider(csp) name
#Note: -k with a signer pub key (not RootCA) is required for PKCS#1 signed certificate embed command
FUSS_FWCAP_SERIAL_IMAGE=$(call Env2,INPUT_IMAGE).serial
FUSS_FWCAP_P7_SIG_IMAGE=$(call Env2,INPUT_IMAGE).serial.p7
FUSS_FWCAP_MAP_EMBED=$(call Env2,CRYPTCON) $(call Env2,BIOS_OFFSET) -m -r $(5) $(call Env2,FWCAP_CERT) -k $(call Env2,ROOTCA_CERT) $(call Env2,FWCAP_KEYR) $(call Env2,FWCAP_PSS) $(call Env2,FWCAP_HASH) $(6) -f $(call Env2,INPUT_IMAGE) -o $(call Env2,INPUT_IMAGE)
FUSS_FWCAP_SERIAL=$(call Env2,CRYPTCON) $(call Env2,BIOS_OFFSET) -s $(call Env2,FWCAP_CERT) $(call Env2,FWCAP_HASH) $(6) -f $(call Env2,INPUT_IMAGE) -o $(FUSS_FWCAP_SERIAL_IMAGE)
FUSS_FWCAP_SIG_EMBED=$(call Env2,CRYPTCON) $(call Env2,BIOS_OFFSET) -s -x $(FUSS_FWCAP_P7_SIG_IMAGE) $(call Env2,FWCAP_CERT) -k $(call Env2,PUBKEY_CERT) $(call Env2,FWCAP_HASH) $(6) -f $(call Env2,INPUT_IMAGE) -o $(call Env2,OUTPUT_IMAGE)
FUSS_FWCAP_VERIFY=$(call Env2,CRYPTCON) $(call Env2,BIOS_OFFSET) -v2 $(call Env2,FWCAP_HASH) $(call Env2,FWCAP_KEYR) $(6) -f $(call Env2,INPUT_IMAGE)
define fuss_fwcapsule_sig_template =
$(2): $(2)_job$(1)
$(2)_job$(1): $(AMIROM_FUSS_FILE) $(3) $(5)
	@$(ECHO) \
"$(LINUX_BASH)$(EOL)\
$(Echo) ----Execute Job$(1) for $(2)$(EOL)\
$(call fuss_SET_template,CRYPTCON,$(CRYPTCON),$(call Env2,CRYPTCON))$(EOL)\
$(call fuss_SET_template,INPUT_IMAGE,$(3),$(call Env2,INPUT_IMAGE))$(EOL)\
$(call fuss_SET_template,OUTPUT_IMAGE,$(4),$(call Env2,OUTPUT_IMAGE))$(EOL)\
$(call fuss_IF_choice_template,$(3),$(4),$(Set) OUTPUT_IMAGE=$(call Env2,INPUT_IMAGE))$(EOL)\
$(Set) ROOTCA_CERT=$(11)$(EOL)\
$(Set) PUBKEY_CERT=$(13)$(EOL)\
$(Set) FWCAP_CERT=$(subst 0,-c1,$(subst 1,-c2,$(7)))$(EOL)\
$(Set) FWCAP_HASH=$(subst sha256,-h2,$(subst sha384,-h3,$(subst sha512,-h5,$(8))))$(EOL)\
$(Set) FWCAP_PSS=$(subst 0,,$(subst 1,-p,$(9)))$(EOL)\
$(Set) FWCAP_KEYR=$(subst 0,,$(subst 1,-n,$(10)))$(EOL)"\
> $(BUILD_DIR)$(PATH_SLASH)$(subst $(SPACE),,$(2)).bat
ifeq ($(1), 0)
	@$(ECHO) "\
$(Echo) -----1.Embed Rom Layout and FW root key$(EOL)$(Echo) $(FUSS_FWCAP_MAP_EMBED)$(EOL)$(FUSS_FWCAP_MAP_EMBED)$(EOL)$(fuss_error2)$(EOL)\
$(Echo) -----2.Serialize FW image sections to be signed$(EOL)$(Echo) $(FUSS_FWCAP_SERIAL)$(EOL)$(FUSS_FWCAP_SERIAL)$(EOL)$(fuss_error2)$(EOL)\
$(Echo) -----3.Sign serial image and save signature to $(FUSS_FWCAP_P7_SIG_IMAGE)$(EOL)\
$(InvokeBat) $(AMIROM_FUSS_TOOL_CMDLINE_FILE) $(FUSS_FWCAP_SERIAL_IMAGE) $(FUSS_FWCAP_P7_SIG_IMAGE) $(7) $(8) $(9) $(12) $(13) $(14) $(15)$(EOL)$(fuss_error2)$(EOL)\
$(Echo) -----4.Embed the signature $(FUSS_FWCAP_P7_SIG_IMAGE) to $(call Env2,OUTPUT_IMAGE)$(EOL)$(Echo) $(FUSS_FWCAP_SIG_EMBED)$(EOL)$(FUSS_FWCAP_SIG_EMBED)$(EOL)$(fuss_error2)$(EOL)"\
>> $(BUILD_DIR)$(PATH_SLASH)$(subst $(SPACE),,$(2)).bat
endif
ifeq ($(1), 1)
	@$(ECHO) "$(Echo) -----Embed Rom Layout and FW root key$(EOL)$(Echo) $(FUSS_FWCAP_MAP_EMBED)$(EOL)$(FUSS_FWCAP_MAP_EMBED)$(EOL)$(fuss_error2)$(EOL)" >> $(BUILD_DIR)$(PATH_SLASH)$(subst $(SPACE),,$(2)).bat
endif
ifeq ($(1), 2)
	@$(ECHO) "$(Echo) -----Verify FW signature$(EOL)$(Echo) $(FUSS_FWCAP_VERIFY)$(EOL)$(FUSS_FWCAP_VERIFY)$(EOL)$(fuss_error2)$(EOL)" >> $(BUILD_DIR)$(PATH_SLASH)$(subst $(SPACE),,$(2)).bat
endif
	@$(CAT) $(BUILD_DIR)$(PATH_SLASH)$(subst $(SPACE),,$(2)).bat >> $(AMIROM_FUSS_FILE)
ifeq ($(FUSS_LAUNCH_AT_BUILD),1)
ifeq ($(BUILD_OS), $(BUILD_OS_LINUX))
	chmod +x $(BUILD_DIR)$(PATH_SLASH)$(subst $(SPACE),,$(2)).bat
endif
	$(BUILD_DIR)$(PATH_SLASH)$(subst $(SPACE),,$(2)).bat
endif

endef
#--------------------------------------------------------------------------
# Make build targets
#--------------------------------------------------------------------------
# Clean & Prepare
#--------------------------------------------------------------------------
clean  : CLEAR_FUSS_FILES
Prepare: CLEAR_FUSS_FILES $(AMIROM_FUSS_TOOL_CMDLINE_FILE)

RomPatch: $(AMIROM_FUSS_FILE)

CLEAR_FUSS_FILES:
ifneq ("$(wildcard  $(AMIROM_FUSS_FILE))", "")
	-$(RM) $(AMIROM_FUSS_FILE)
endif
ifneq ("$(wildcard  $(AMIROM_FUSS_TOOL_CMDLINE_FILE))", "")
	-$(RM) $(AMIROM_FUSS_TOOL_CMDLINE_FILE)
endif

#--------------------------------------------------------------------------
#   Define the placeholder for the sign script files
#--------------------------------------------------------------------------
$(AMIROM_FUSS_FILE): $(AMIROM_FUSS_TOOL_CMDLINE_FILE)
	@$(ECHO) \
"$(LINUX_BASH)$(EOL)\
$(Echo)  =====================================================================$(EOL)\
$(Echo)  ---- All-in-one script to sign Aptio FW binary...$(EOL)\
$(Echo)  =====================================================================$(EOL)\
$(Echo)  ----REQUIRED COMPONENTS:$(EOL)\
$(Echo)  ---- Aptio binary '$(ROM_FILE_NAME)'$(EOL)\
$(Echo)  ---- Cryptocon and Sign tools$(EOL)\
$(Echo)  ---- Sign key or a Key ID$(EOL)\
$(Echo)  ----Optional input arguments:$(EOL)\
$(Echo)  ---- 1.Input file name : $(call Arg,1)$(EOL)\
$(Echo)  ---- 2.Output file name: $(call Arg,2)$(EOL)\
$(Echo)  ---- 3.BIOS region offset within the input file: $(call Arg,3)$(EOL)\
$(Echo)  =====================================================================$(EOL)\
$(call fuss_SET_template,CRYPTCON,$(CRYPTCON),$(call Env,CRYPTCON))$(EOL)\
$(call fuss_SET_template,FWBUILD,$(FWBUILD),$(call Env,FWBUILD))$(EOL)\
$(Set) INPUT_IMAGE=$(call Arg,1)$(EOL)\
$(Set) OUTPUT_IMAGE=$(call Arg,2)$(EOL)\
$(call fuss_SET_choice_template,BIOS_OFFSET,,-$(Dollar) $(call Arg,3),$(call Arg,3))$(EOL)"\
> $(AMIROM_FUSS_FILE)
ifeq ($(BUILD_OS), $(BUILD_OS_LINUX))
	@$(ECHO) "chmod +x $(CRYPTCON:-@=)$(EOL)chmod +x $(AMIROM_FUSS_TOOL_CMDLINE_FILE)$(EOL)"\
>> $(AMIROM_FUSS_FILE)
endif

#dbg
#$(eval $(call fuss_fwcapsule_sig_template,1,Prepare,$(ROM_FILE_NAME),$(ROM_FILE_NAME),$(ROM_LAYOUT_EX),$(FVDXE_CRYPTOCON_CMDLINE),$(FVDXE_CERT_FORMAT),$(FVDXE_HASH),$(FVDXE_SIG_PSS),$(FVDXE_FWKEY_FILE_REPLACE),$(FVDXE_ROOTCAKEY),$(FVDXE_PRIVKEY),$(FVDXE_PUBKEY),$(FVDXE_KEY_PSWD)) )
#$(eval $(call fuss_fwcapsule_sig_template,0,Prepare,$(ROM_FILE_NAME),$(ROM_FILE_NAME),$(ROM_LAYOUT_EX),$(FVDXE_CRYPTOCON_CMDLINE),$(FVDXE_CERT_FORMAT),$(FVDXE_HASH),$(FVDXE_SIG_PSS),$(FVDXE_FWKEY_FILE_REPLACE),$(FVDXE_ROOTCAKEY),$(FVDXE_PRIVKEY),$(FVDXE_PUBKEY),$(FVDXE_KEY_PSWD)) )
#$(eval $(call fuss_fwcapsule_sig_template,2,Prepare,$(ROM_FILE_NAME),,,$(FVDXE_CRYPTOCON_CMDLINE),,,,1))
#$(eval $(call fuss_fwcapsule_sig_template,0,Prepare,$(ROM_FILE_NAME),$(ROM_FILE_NAME),$(ROM_LAYOUT_FVBB),$(FV_BB_CRYPTOCON_CMDLINE),$(FVBB_CERT_FORMAT),$(FVBB_HASH),$(FVBB_SIG_PSS),0,$(FVBB_ROOTCAKEY),$(FVBB_PRIVKEY),$(FVBB_PUBKEY)) )
#$(eval $(call fuss_fwcapsule_sig_template,2,Prepare,$(ROM_FILE_NAME),,,$(FV_BB_CRYPTOCON_CMDLINE)) )
#---------------------------------------------------------------------------
#   Define a batch file with the Sign Tool command line
#--------------------------------------------------------------------------
#%1 (req)Image to sign
#%2 (req)Output signature
#%3 (opt)Output Signature type: 0-PKCS#1, 1-PKCS#7
#%4 (opt)Signature Hash algorithm: sha256, sha384 and sha512
#%5 (opt)Signature padding schema: 0-RSASSA-PKCS1v1.5, 1-RSASSA-PSS
#%6 (opt)Signer Private Key identifier. Private Key file or Key Container Name, Key ID, Key Hash etc.
#%7 (opt)Signer Certificate identifier. Public key file, Certificate Subject Name
#%8 (opt)Signer Key password
#%9 (opt)Cryptographic Storage Provider(csp) name
#--------------------------------------------------------------------------
$(AMIROM_FUSS_TOOL_CMDLINE_FILE):
	@$(ECHO) \
"$(LINUX_BASH)$(EOL)\
$(Echo)  =====================================================================$(EOL)\
$(Echo)  ---- Defines a batch script with the Sign Tool command line...$(EOL)\
$(Echo)  =====================================================================$(EOL)\
$(Echo)  ----Required input arguments :$(EOL)\
$(Echo)  ---- 1.Input file name : $(call Arg,1)$(EOL)\
$(Echo)  ---- 2.Output file name: $(call Arg,2)$(EOL)\
$(Echo)  ----Optional input arguments:$(EOL)\
$(Echo)  ---- 3.Output Signature type: 0-PKCS1, 1-PKCS7: $(call Arg,3)$(EOL)\
$(Echo)  ---- 4.Signature Hash algorithm: sha256, sha384 and sha512: $(call Arg,4)$(EOL)\
$(Echo)  ---- 5.Signature padding schema: 0-RSASSA-PKCS1v1.5, 1-RSASSA-PSS: $(call Arg,5)$(EOL)\
$(Echo)  ---- 6.Signer Private Key identifier(Private Key file): $(call Arg,6)$(EOL)\
$(Echo)  ---- 7.Signer Certificate identifier(Public key file) : $(call Arg,7)$(EOL)\
$(Echo)  ---- 8.Signer Key password: $(call Arg,8)$(EOL)\
$(Echo)  ---- 9.Cryptographic Storage Provider(csp) name: $(call Arg,9)$(EOL)\
$(Echo)  =====================================================================$(EOL)\
$(call fuss_SET_template,CRYPTCON,$(CRYPTCON),$(call Env,CRYPTCON))$(EOL)\
$(call fuss_SET_template,SIGNTOOL,signtool.exe,$(call Env,SIGNTOOL))$(EOL)\
$(call fuss_SET_template,OPENSSL,openssl,$(call Env,OPENSSL))$(EOL)\
$(Set) INPUT_FILE=$(call Arg,1)$(EOL)\
$(Set) OUTPUT_SIG=$(call Arg,2)$(EOL)\
$(call fuss_SET_template,SIGN_CERT_FORMAT,$(FUSS_CERT_FORMAT),$(call Arg,3))$(EOL)\
$(call fuss_SET_template,HASH_ALGO,$(FUSS_HASH),$(call Arg,4))$(EOL)\
$(call fuss_SET_template,SIGN_ALGO,$(FUSS_SIG_PSS),$(call Arg,5))$(EOL)\
$(call fuss_SET_template,PRIV_KEY,$(FUSS_PRIVKEY),$(call Arg,6))$(EOL)\
$(call fuss_SET_template,PUBKEY_CERT,$(FUSS_PUBKEY),$(call Arg,7))$(EOL)\
$(call fuss_SET_template,PRIVKEY_PSWD,$(FUSS_KEY_PSWD),$(call Arg,8))$(EOL)\
$(call fuss_SET_template,CSP,$(FUSS_CSP),$(call Arg,9))$(EOL)\
$(Echo) ------------------------$(EOL)\
$(Echo) Output Signature format $(call Env,SIGN_CERT_FORMAT) 0-DER PKCS1, 1-DER PKCS7$(EOL)\
$(Echo) RSA Signature    scheme $(call Env,SIGN_ALGO) 0-RSASSA-PKCS1v1_5, 1-RSASSA-PSS$(EOL)\
$(Echo) ------------------------$(EOL)\
$(call fuss_SET_choice_template,SIGN_ALGO,$(FUSS_SIG_CMD_PKCS1),$(FUSS_SIG_CMD_PSS),$(call Env,SIGN_ALGO))$(EOL)\
$(call fuss_SET_template,SET_PRIVKEY_PSWD,0,$(call Arg,8))$(EOL)\
$(call fuss_SET_choice_template,PRIVKEY_PSWD,,$(FUSS_SIG_CMD_PSWD)\"$(call Env,PRIVKEY_PSWD)\",$(call Env,SET_PRIVKEY_PSWD))$(EOL)\
$(call fuss_IF_choice_template,$(call Env,SIGN_CERT_FORMAT),0,$(Echo) $(FUSS_SIGNTOOL_P1)$(EOL)$(FUSS_SIGNTOOL_P1))$(EOL)\
$(call fuss_IF_choice_template,$(call Env,SIGN_CERT_FORMAT),1,$(Echo) $(FUSS_SIGNTOOL_P7)$(EOL)$(FUSS_SIGNTOOL_P7))$(EOL)\
$(fuss_error)$(EOL)"\
> $(AMIROM_FUSS_TOOL_CMDLINE_FILE)
ifeq ($(BUILD_OS), $(BUILD_OS_LINUX))
	chmod +x $(AMIROM_FUSS_TOOL_CMDLINE_FILE)
endif
