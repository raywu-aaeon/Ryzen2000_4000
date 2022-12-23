#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2019, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************


Prepare : BcpBootOrderCountLength

BcpDefaultBootOrderLength := $(subst $(COMMA),$(SPACE),$(BCP_DEFAULT_BOOT_ORDER))
BcpDefaultBootOrderLength := $(words $(BcpDefaultBootOrderLength))

ifeq ($(call __gt, $(BcpDefaultBootOrderLength), 34), yes)
 $(error Items specified in BCP_DEFAULT_BOOT_ORDER token should not be higher than 34.)
endif

ifeq (0 , $(BcpDefaultBootOrderLength))
 $(error Items specified in BCP_DEFAULT_BOOT_ORDER token is 0, please recheck it or make sure the token is overridden with TargetMak attribute set in the SDL. )
endif

BcpBootOrderCountLength : $(BUILD_DIR)/BcpBootOrderElinks.h
	@$(GAWK) "{gsub(/BCP_DEFAULT_BOOT_ORDER_LENGTH [0-9]+/, \"BCP_DEFAULT_BOOT_ORDER_LENGTH $(BcpDefaultBootOrderLength)\"); print}" $(BUILD_DIR)/BcpBootOrderElinks.h \
	   	> $(BUILD_DIR)$(PATH_SLASH)TmpBcpBootOrderElinks.h
	@cat $(BUILD_DIR)$(PATH_SLASH)TmpBcpBootOrderElinks.h > $<
	@$(RM) $(BUILD_DIR)$(PATH_SLASH)TmpBcpBootOrderElinks.h


#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2019, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************
