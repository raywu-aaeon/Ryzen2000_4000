#**********************************************************************
#*                                                                    *
#*   Copyright (c) 1985-2020, American Megatrends International LLC.  *
#*                                                                    *
#*      All rights reserved. Subject to AMI licensing agreement.      *
#*                                                                    *
#**********************************************************************

FW_VERSION_ERROR_MESSAGE=\
    FW_VERSION_GUID must be valid and unique for each project.\
    Clone FW_VERSION_GUID token to fix the problem

ifeq ("$(FW_VERSION_GUID)","$(ILLEGAL_GUID)")
  ifeq ($(SETUP_PRINT_EVAL_MSG),0)
    $(error $(FW_VERSION_ERROR_MESSAGE))
  else
    $(warning $(FW_VERSION_ERROR_MESSAGE))
  endif
endif
