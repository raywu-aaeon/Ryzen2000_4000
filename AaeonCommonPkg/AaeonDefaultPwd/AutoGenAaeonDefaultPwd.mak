#;******************************************************************************
#;* Copyright (c) 2018, Aaeon Corporation. All Rights Reserved.
#;*
#;* You may not reproduce, distribute, publish, display, perform, modify, adapt,
#;* transmit, broadcast, present, recite, release, license or otherwise exploit
#;* any part of this publication in any form, by any means, without the prior
#;* written permission of Aaeon Corporation.
#;*
#;******************************************************************************
#; ModuleName:
#;
#;   AutoGenAaeonDefaultPwd.mak
#;
#;------------------------------------------------------------------------------
#;
#; Abstract:
#;
#;   Involve AutoGenAaeonDefaultPwd.gawk to produce Build/AutoGenAaeonDefaultPwd.uni automatically
#;
Prepare : $(BUILD_DIR)/AutoGenAaeonDefaultPwd.uni PatchPwd

Quotation := \"

ifeq ($(TSE_ADMIN_PASSWORD), "EMPTY_DATA")
  TSE_ADMIN_PASSWORD :=
endif

ifeq ($(TSE_USER_PASSWORD), "EMPTY_DATA")
  TSE_USER_PASSWORD :=
endif

$(BUILD_DIR)/AutoGenAaeonDefaultPwd.uni :  $(BUILD_DIR)/token.mak \
                								           $(AaeonDefaultPwd_DIR)/AutoGenAaeonDefaultPwd.gawk
	gawk -f $(AaeonDefaultPwd_DIR)/AutoGenAaeonDefaultPwd.gawk \
		-v TYPE=UEFI_GROUP_FORM -v DEVICE=$(GAWK_UEFI_DEVICE) -v TSE_ADMIN_PASSWORD=$(TSE_ADMIN_PASSWORD) -v TSE_USER_PASSWORD=$(TSE_USER_PASSWORD)

PatchPwd : $(BUILD_DIR)/token.mak
	$(ECHO) \
"$(EOL)\
#string STR_AAEON_DEFAULT_ADMIN_PWD_VALUE                  #language eng $(Quotation)$(TSE_ADMIN_PASSWORD)$(Quotation)$(EOL)\
#string STR_AAEON_DEFAULT_USER_PWD_VALUE                  #language eng $(Quotation)$(TSE_USER_PASSWORD)$(Quotation)$(EOL)\
">> $(BUILD_DIR)\AutoGenAaeonDefaultPwd.uni
