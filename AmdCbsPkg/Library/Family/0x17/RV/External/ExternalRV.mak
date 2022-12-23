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
CBS_XML: RVXML CBSIDSGEN

RVXML: CBS_ENV
##
## Rebuild AMD-XML file and run AMD provided bat file.
##
	$(BUILD_DIR)$(PATH_SLASH)RunXmlParseExe.bat BILBY

ifeq ($(APCB_RV_FP5_UDIMM_BINARY_SUPPORT), 1)
	xcopy /r /y $(CBS_RES_GEN)\ApcbAutoGenRV.h $(APCB_SCRIPT_RV_FP5_UDIMM_DIR)$(PATH_SLASH)Include$(PATH_SLASH)ApcbAutoGen.h
endif
ifeq ($(APCB_RV_FP5_SODIMM_BINARY_SUPPORT), 1)
	xcopy /r /y $(CBS_RES_GEN)\ApcbAutoGenRV.h $(APCB_SCRIPT_RV_FP5_SODIMM_DIR)$(PATH_SLASH)Include$(PATH_SLASH)ApcbAutoGen.h
endif

ifeq ($(APCB_RV_AM4_UDIMM_BINARY_SUPPORT), 1)
	xcopy /r /y $(CBS_RES_GEN)\ApcbAutoGenRV.h $(APCB_SCRIPT_RV_AM4_UDIMM_DIR)$(PATH_SLASH)Include$(PATH_SLASH)ApcbAutoGen.h
endif
ifeq ($(APCB_RV_AM4_SODIMM_BINARY_SUPPORT), 1)
	xcopy /r /y $(CBS_RES_GEN)\ApcbAutoGenRV.h $(APCB_SCRIPT_RV_AM4_SODIMM_DIR)$(PATH_SLASH)Include$(PATH_SLASH)ApcbAutoGen.h
endif

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