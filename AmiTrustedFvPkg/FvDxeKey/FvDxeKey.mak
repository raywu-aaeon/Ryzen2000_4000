#***********************************************************************
#*                                                                     *
#*   Copyright (c) 1985-2019, American Megatrends International LLC.   *
#*                                                                     *
#*      All rights reserved. Subject to AMI licensing agreement.       *
#*                                                                     *
#***********************************************************************

#*************************************************************************
#<AMI_FHDR_START>
#
# Name: FvDxeKey.mak
#
# Description: Include FvDxeKey ffs with Root Platform key into the BIOS FV_BB
# 
#<AMI_FHDR_END>
#*************************************************************************
Prepare: $(BUILD_DIR)$(PATH_SLASH)FWKey.inf
#-------------------------------------------------------------------------
#   Include Platform Firmware Root Key (FWKey) .FFS
#-------------------------------------------------------------------------
###########################################################################
###	Creating FWKey.inf file
###########################################################################
$(BUILD_DIR)$(PATH_SLASH)FWKey.inf:
	@$(ECHO) \
"## @file$(EOL)\
#   This file is auto-generated from FvDxeKey.mak$(EOL)\
##$(EOL)\
[Defines]$(EOL)\
  INF_VERSION                    = 0x00010005$(EOL)\
  BASE_NAME                      = FWKey$(EOL)\
  FILE_GUID                      = $(FWKEY_FILE_GUID)$(EOL)\
  MODULE_TYPE                    = USER_DEFINED$(EOL)\
$(EOL)\
[Packages]$(EOL)\
  AmiCompatibilityPkg/AmiCompatibilityPkg.dec$(EOL)\
  MdePkg/MdePkg.dec$(EOL)"\
> $@
ifneq ($(wildcard $(FWpub)), $(FWpub))
#-------------------------------------------------------------------------
#   Create a dummy key placeholder file that will be updated with the 
#   real pub key at the time of signing the BIOS image
#-------------------------------------------------------------------------
	@$(ECHO) "\
#pragma pack(1)$(EOL)\
char pad[$(FWKEY_FILE_SIZE)] = {'$$','B','A','D','K','E','Y','$$'};"\
> $(basename $@).cbin
	@$(ECHO) \
"[Sources]$(EOL)\
  FWKey.cbin"\
>> $@
else
#-------------------------------------------------------------------------
#   FWpub key is present
#   Prepare Platform Firmware Root Key (FWKey) bin file
#-------------------------------------------------------------------------
	@$(ECHO) \
"[Binaries]$(EOL)\
  BIN|FWKey.bin|*"\
>> $@
ifeq ($(BUILD_OS), $(BUILD_OS_LINUX))
	chmod +x $(CRYPTCON:-@=)
endif
ifneq ($(FWKEY_FILE_FORMAT),1)
# n-modulus of RSA2048
$(error  *** Unsupported FWKEY_FILE_FORMAT. Only one type is supported: 1 - SHA256 Hash of RSA public key)
endif
ifeq ($(FWCAPSULE_CERT_FORMAT),1)
#get SHA256 Hash of x509 Tbs cert section. Supported from Cryptocon.exe v4.7.31.2014
	$(CRYPTCON) -h2 -x $(FWpub) -o $(basename $@).bin
else #$(FWCAPSULE_CERT_FORMAT),0)
#Extract 256byte n-modulus from either X.509 DER or PKCS#1v2 ASN.1 encoded RSA Key certificate file
# n-modulus of RSA2048
	$(CRYPTCON) -w -k $(FWpub) -o $(basename $@).bin
#get SHA256 Hash of n-modulus of RSA Key
	$(CRYPTCON) -h2 -f $(basename $@).bin -o $(basename $@).bin
endif
endif

