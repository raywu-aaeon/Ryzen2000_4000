#***********************************************************************
#*                                                                     *
#*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
#*                                                                     *
#*      All rights reserved. Subject to AMI licensing agreement.       *
#*                                                                     *
#***********************************************************************
## @file
#	Includes main build module for Secure sub-components
#   Create extended Rom layout map file RomLayoutEx.bin
#   Update FwCapsuleHdr ffs file inside BIOS.ROM with RomLayoutEx map
#   Create signed BIOS image (Aptio FW Capsule)
#   Create a batch file with instructions to sign Fw Capsule
##

.PHONY : CLEAR_FWCAPSULE_FILES MAKE_FWCAPSULE MAKE_FWCAPSULE_VERIFY MOD_FWCAPSULE_HDR_FFS

#---------------------------------------------------------------------------
# Only for PKCS1v2.1 Key files the FWpub(public key part) can be derived 
# from FWpriv(full RSA key) if FWpub file is not available
#---------------------------------------------------------------------------
ifeq ($(FWCAPSULE_CERT_FORMAT),0)
ifneq ($(wildcard $(FWpub)), $(FWpub))
ifeq ($(wildcard $(FWpriv)),$(FWpriv))
FWpub := $(FWpriv)
endif
endif
endif

FWCAPSULE_MAKE_BAT := make_signed_capsule.bat
#---------------------------------------------------------------------------
#        Prepare Signed Capsule : FWCAPSULE_FILE
#---------------------------------------------------------------------------
clean  : CLEAR_FWCAPSULE_FILES
Prepare: CLEAR_FWCAPSULE_FILES

CLEAR_FWCAPSULE_FILES:
ifneq ("$(wildcard  $(FWCAPSULE_FILE))", "")
	-$(RM) $(FWCAPSULE_FILE)
endif
ifneq ("$(wildcard  $(ROM_LAYOUT_EX))", "") 
	-$(RM) $(ROM_LAYOUT_EX)
endif
ifneq ("$(wildcard  $(FWCAPSULE_MAKE_BAT))", "") 
	-$(RM) $(FWCAPSULE_MAKE_BAT)
endif

#--------------------------------------------------------------------------
# Create file $(ROM_LAYOUT_EX) with FwCapsule signing descriptor table
#--------------------------------------------------------------------------
$(ROM_LAYOUT_EX): $(UNSIGNED_BIOS_ROM)
ifneq ($(AmiTrustedFv_Support),1)
	@echo ---- FwCapsule: Build extended rom map '$(notdir $@)'
	$(FWBUILD) $< $(FWBUILD_OPTION_CHAR)s $(FWBUILD_OPTION_CHAR)m $@
	@$(ECHO) "@echo ---- FwCapsule: build extended rom map '$(notdir $@)':$(EOL)\
$(FWBUILD) $< $(FWBUILD_OPTION_CHAR)s $(FWBUILD_OPTION_CHAR)m $@$(EOL)"\
>> $(FWCAPSULE_MAKE_BAT)
else
	$(call fuss_fwcapsule_misc_template,FwCapsule: Build extended rom map,$(FWBUILD) $(ROM_FILE_NAME) $(FWBUILD_OPTION_CHAR)s $(FWBUILD_OPTION_CHAR)m $@)
endif
#---------------------------------------------------------------------------
# Embed Signing descriptor table "$(ROM_LAYOUT_EX)" inside "$(UNSIGNED_BIOS_ROM)"
#--------------------------------------------------------------------------
ifneq ($(AmiTrustedFv_Support),1)
MOD_FWCAPSULE_HDR_FFS: $(ROM_LAYOUT_EX) $(UNSIGNED_BIOS_ROM)
	@echo ----$@: update '$(notdir $(UNSIGNED_BIOS_ROM))' with extended rom map '$(notdir $(ROM_LAYOUT_EX))'
ifeq ($(BUILD_OS), $(BUILD_OS_LINUX))
	chmod +x $(CRYPTCON:-@=)
endif
	$(CRYPTCON) $(CRYPTOCON_CMDLINE_MAP) -f $(UNSIGNED_BIOS_ROM) -o $(UNSIGNED_BIOS_ROM)
	@$(ECHO) "@echo ----$@: update '$(notdir $(UNSIGNED_BIOS_ROM))' with extended rom map '$(notdir $(ROM_LAYOUT_EX))':$(EOL)\
$(CRYPTCON) $(CRYPTOCON_CMDLINE_MAP) -f $(UNSIGNED_BIOS_ROM) -o $(UNSIGNED_BIOS_ROM)$(EOL)"\
>> $(FWCAPSULE_MAKE_BAT)
else
$(eval $(call fuss_fwcapsule_sig_template,1,MOD_FWCAPSULE_HDR_FFS,$(UNSIGNED_BIOS_ROM),$(UNSIGNED_BIOS_ROM),$(ROM_LAYOUT_EX),$(subst 0,-y,$(subst 1,,$(FWCAPSULE_FILE_FORMAT))),$(FWCAPSULE_CERT_FORMAT),sha256,$(FWSIG_PADDING),$(FWKEY_FILE_REPLACE),$(FUSS_ROOTCAKEY),$(FUSS_PRIVKEY),$(FUSS_PUBKEY),$(FUSS_KEY_PSWD)) )
endif
#---------------------------------------------------------------------------
# Invoke cryptocon.exe to create Signed FwCapsule if CREATE_FWCAPSULE == 1
#---------------------------------------------------------------------------
# Should be the last step after creating of the ROM image. All fixups to the .ROM must be made prior to this step.
# check END target in the MAIN.MAK and all .MAK files to make sure this step is not overriden
#---------------------------------------------------------------------------
$(FWCAPSULE_BUILD_TARGET): MAKE_FWCAPSULE MAKE_FWCAPSULE_VERIFY
MAKE_FWCAPSULE: $(FWCAPSULE_FILE)

ifeq ($(INTEL_FIT_SUPPORT),1) 
.PHONY : Fit FitFirstEnd
$(FWCAPSULE_FILE): Fit FitFirstEnd
endif

$(FWCAPSULE_FILE): $(UNSIGNED_BIOS_ROM) $(ROM_LAYOUT_EX) MOD_FWCAPSULE_HDR_FFS
ifneq ($(CREATE_FWCAPSULE),1)
	$(CP) $(UNSIGNED_BIOS_ROM) $(FWCAPSULE_FILE)
endif #ifeq ($(CREATE_FWCAPSULE),1)
ifneq ($(AmiTrustedFv_Support),1)
	@echo ---- Create signed BIOS image '$(FWCAPSULE_FILE)'
	-$(CRYPTCON) $(CRYPTOCON_CMDLINE_SIG) -f $(UNSIGNED_BIOS_ROM) -o $(FWCAPSULE_FILE)
	@echo ---- Verify signed BIOS image '$(FWCAPSULE_FILE)'
	-$(CRYPTCON) -v2 -n -f $(FWCAPSULE_FILE)
#---------------------------------------------------------------------------
#   Build batch file with instructions to generate signed Aptio FW Capsule
#---------------------------------------------------------------------------
	@$(ECHO) "@echo ---- Create signed BIOS image '$(FWCAPSULE_FILE)':$(EOL)\
$(CRYPTCON) $(CRYPTOCON_CMDLINE_SIG) -f $(UNSIGNED_BIOS_ROM) -o $(FWCAPSULE_FILE)$(EOL)$(EOL)\
@echo ---- Verify BIOS signature:$(EOL)\
$(CRYPTCON) -v2 -n -f $(FWCAPSULE_FILE)$(EOL)"\
>> $(FWCAPSULE_MAKE_BAT)
else
$(eval $(call fuss_fwcapsule_sig_template,0,$(FWCAPSULE_FILE),$(UNSIGNED_BIOS_ROM),$(FWCAPSULE_FILE),$(ROM_LAYOUT_EX),$(subst 0,-y,$(subst 1,,$(FWCAPSULE_FILE_FORMAT))),$(FWCAPSULE_CERT_FORMAT),sha256,$(FWSIG_PADDING),$(FWKEY_FILE_REPLACE),$(FUSS_ROOTCAKEY),$(FUSS_PRIVKEY),$(FUSS_PUBKEY),$(FUSS_KEY_PSWD)) )
$(eval $(call fuss_fwcapsule_sig_template,2,MAKE_FWCAPSULE_VERIFY,$(FWCAPSULE_FILE),,,,,,,1))
endif #$(AmiTrustedFv_Support
#---------------------------------------------------------------------------
#   Build time warnings
#---------------------------------------------------------------------------
ifneq ($(wildcard $(FWpub)),$(FWpub))
$(warning *** '$(FWpub)' file with RSA public key not found)
$(warning *** BIOS image will include the dummy key as a Platform Key placeholder)
$(warning *** The flash updates will fail, unless the valid key is set in FV_BB(FWKey.ffs))
$(warning *** The Key must be provided at a time of build OR inserted by Cryptocon using command option '-y -c2 -n -k key -f bios.rom -o bios.rom')
endif
ifeq ($(CONFIG_PEI_PKCS7),0)
$(warning *** PKCS#7 Signed Firmware Volume)
$(warning *** PKCS#7 certificate parser in PEI is disabled through SDL in AmiCryptoPkg:CONFIG_PEI_PKCS7.)
ifeq ($(FWCAPSULE_CERT_FORMAT),1)
$(error The 'Capsule' and 'Recovery' flash updates will fail on PKCS#7 Signed images)
endif
endif

#---------------------------------------------------------------------------
# Generic Cryptocon commands to build signed Aptio FW Capsule
#---------------------------------------------------------------------------
# cryptocon [options] <-f input_file> [-o output_file]
#
#-c'FWrootPriv' -k'FWsignPriv' Make PKCS#1v1.5 signed FwCapsule(Note1)
#-c2 -x 'FWpriv'[,'pswd']      Make PKCS#7 signed FwCapsule(Note2,Note3)
#-f'file' input, un-signed BIOS image
#-o'file' output, signed FwCapsule image
#-y use embedded FwCapsule header to insert the signature
#-l'value' max size of a FwCapsule Header (or Hdr alignment)
#-p RSASSA-PSS signature padding scheme (replaces default PKCS#1v1.5)
#-n -k'key' insert Signer's public key inside of the signed image
#-r'rom.map' use a rom map from the external file
#-m -r'rom.map' embed a rom map from the external file to FwCapsule Hdr 
#-r1 ignore the embedded rom map - calculate hash of entire ROM image
#-$$[Offs] offset within the file to adjust the RomMap ranges by
#-h2(3,5) Select hash algorithm to be used for signed digest
#         Supported hash types: sha256(-h2), sha384(-h3) and sha512(-h5)
#---------------------------------------------------------------------------
#Note1. -c'key1'-k'key2'         :use PKCS#1v2.1 DER(PEM) encoded RSA2048 keys
#Note2. -c2 -x'key1,[pswd]'-k'key2':key1-PKCS#12(PFX) with optional PFX password;
#                                 key2-X.509(DER) public key of 'key1'
#Note3. -c2 -x command will invoke MS signtool.exe or openSSL(-*) as external process
#---------------------------------------------------------------------------
# Extended Cryptocon commands to generate FwCapsule using external sign process
#---------------------------------------------------------------------------
#Example of generating Fw Capsule signed with PKCS#7 certificate using 3rd party sign tools.
#Note, in order to use RSA-PKCS#1v1.5 signed certificate in FwCap Hdr, replace all instances of "-c2" with "-c $(FWpub)"
#1. Embed RomLayout table to FvCap Hdr and Embed signer verification key $(FWpub) into the BIOS image
#   $(CRYPTCON) -c2 -y -r $(ROM_LAYOUT_EX) -n -k $(FWpub) -f $(UNSIGNED_BIOS_ROM) -o $(UNSIGNED_BIOS_ROM)
#2. Serialize all BIOS regions to be signed
#   $(CRYPTCON) -s -c2 -y -f $(UNSIGNED_BIOS_ROM) -o serial.bin
#3. Sign serial image and store a signature in DER encoded PKCS#7 signed certificate file format (serial.bin.p7)
#   The choice of supported hash algorithms: sha256, sha384, sha512
#   Examples of using Microsoft Signtool.exe or openSSL(MS or Linux) with local access to sign keys:
#    signtool.exe sign /fd sha256 /p7 . /p7co 1.2.840.113549.1.7.1 /p7ce DetachedSignedData /p FW_PFX_Password /f FWpriv serial.bin
#    openssl smime -sign -md sha256 -binary -noattr -in serial.bin -out serial.bin.p7 -outform DER -inkey FWpriv -signer FWpub -passin pass:FW_PFX_Password
#   Examples of signing with externally managed sign keys:
#    -A computer store is specified for the certification authority (CA) store. Certificate is identified by a Subject Name "My High Value Certificate"
#     signtool.exe sign /fd sha256 /p7 .\ /p7co 1.2.840.113549.1.7.1 /p7ce DetachedSignedData /sm /n "My High Value Certificate" serial.bin
#    -A private key is protected by a hardware cryptography module (e.g. HSM)
#     signtool.exe sign /fd sha256 /p7 .\ /p7co 1.2.840.113549.1.7.1 /p7ce DetachedSignedData /csp 'Hardware Cryptography Module' /f SigCert.cer /kc KeyContainerName serial.bin
#    -The HSM managed sign key is referenced in the certificate store by its SHA1 hash.
#     signtool.exe sign /fd sha256 /p7 .\ /p7co 1.2.840.113549.1.7.1 /p7ce DetachedSignedData /a /sha1 "db314da0d0ef87d42b42f74b9c38a1f9173ef7a2" /sm serial.bin
#    -OpenSSL script to access sign key protected by HSM (output signature created in Pkcs1v1.5 padding):
#     openssl pkeyutl -engine pkcs11 -keyform engine -sign -inkey id_55AA -pkeyopt digest:sha256 -out serial.bin.p7 -in serial.bin
#4. Insert signature from "serial.bin.p7" into a target BIOS image
# Embedd signed PKCS#7 certificate
#   $(CRYPTCON)) -s -x serial.bin.p7 -c2 -y -f $(UNSIGNED_BIOS_ROM) -o $(FWCAPSULE_FILE)
