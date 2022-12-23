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
CBSIDSGEN: CBS_ENV
##
## Rebuild AMD-XML file and run AMD provided bat file.
##
	$(BUILD_DIR)$(PATH_SLASH)RunIdsIdGenExe.bat

CBS_RES_GEN=$(CBS_RES_BUILD)
CBS_RES_ORG=$(AmdCbsPkg_DIR)$(PATH_SLASH)Library$(PATH_SLASH)Family$(PATH_SLASH)0x17$(PATH_SLASH)RV$(PATH_SLASH)External$(PATH_SLASH)Resource$(CBS_SOLUTION_TYPE)
CBS_RES_BUILD=$(BUILD_DIR)$(PATH_SLASH)Resource$(CBS_SOLUTION_TYPE)
CBS_INC_LIB=$(AmdCbsPkg_DIR)$(PATH_SLASH)Include$(PATH_SLASH)Library$(PATH_SLASH)
CBS_AGESA_M_PKG_INC=AgesaModulePkg$(PATH_SLASH)Include$(PATH_SLASH)
AMD_IDS_ID_GEN=$(AmdCbsPkg_DIR)$(PATH_SLASH)Tools$(PATH_SLASH)IdsIdGen.bat


CBS_ENV:
	ATTRIB -r $(WORKSPACE)$(PATH_SLASH)AmdCbsPkg$(PATH_SLASH)Include$(PATH_SLASH)Library$(PATH_SLASH)AmdCbsFormID.h
	ATTRIB -r $(WORKSPACE)$(PATH_SLASH)AmdCbsPkg$(PATH_SLASH)Include$(PATH_SLASH)Library$(PATH_SLASH)AmdCbsVariable.h
	ATTRIB -r $(WORKSPACE)$(PATH_SLASH)AmdCbsPkg$(PATH_SLASH)Library$(PATH_SLASH)Family$(PATH_SLASH)0x17$(PATH_SLASH)RV$(PATH_SLASH)External$(PATH_SLASH)ResourceRVFP5$(PATH_SLASH)AmdCbsDefault.c
	ATTRIB -r $(WORKSPACE)$(PATH_SLASH)AmdCbsPkg$(PATH_SLASH)Library$(PATH_SLASH)Family$(PATH_SLASH)0x17$(PATH_SLASH)RV$(PATH_SLASH)External$(PATH_SLASH)ResourceRVFP5$(PATH_SLASH)AmdCbsFormID.h
	ATTRIB -r $(WORKSPACE)$(PATH_SLASH)AmdCbsPkg$(PATH_SLASH)Library$(PATH_SLASH)Family$(PATH_SLASH)0x17$(PATH_SLASH)RV$(PATH_SLASH)External$(PATH_SLASH)ResourceRVFP5$(PATH_SLASH)AmdCbsVariable.h
	ATTRIB -r $(WORKSPACE)$(PATH_SLASH)AmdCbsPkg$(PATH_SLASH)Library$(PATH_SLASH)Family$(PATH_SLASH)0x17$(PATH_SLASH)RV$(PATH_SLASH)External$(PATH_SLASH)ResourceRVFP5$(PATH_SLASH)ApcbAutoGenRV.h
	ATTRIB -r $(WORKSPACE)$(PATH_SLASH)AmdCbsPkg$(PATH_SLASH)Library$(PATH_SLASH)Family$(PATH_SLASH)0x17$(PATH_SLASH)RV$(PATH_SLASH)External$(PATH_SLASH)ResourceRVFP5$(PATH_SLASH)ApcbSetDataRV.c
	ATTRIB -r $(WORKSPACE)$(PATH_SLASH)AmdCbsPkg$(PATH_SLASH)Library$(PATH_SLASH)Family$(PATH_SLASH)0x17$(PATH_SLASH)RV$(PATH_SLASH)External$(PATH_SLASH)ResourceRVFP5$(PATH_SLASH)CbsIdsNvRV.c
	ATTRIB -r $(WORKSPACE)$(PATH_SLASH)AmdCbsPkg$(PATH_SLASH)Library$(PATH_SLASH)Family$(PATH_SLASH)0x17$(PATH_SLASH)RV$(PATH_SLASH)External$(PATH_SLASH)ResourceRVFP5$(PATH_SLASH)CbsSetAgesaPcdLibRV.c
	ATTRIB -r $(WORKSPACE)$(PATH_SLASH)AmdCbsPkg$(PATH_SLASH)Library$(PATH_SLASH)Family$(PATH_SLASH)0x17$(PATH_SLASH)RV$(PATH_SLASH)External$(PATH_SLASH)ResourceRVFP5$(PATH_SLASH)CbsSetAgesaPcdLibRV.inf
	ATTRIB -r $(WORKSPACE)$(PATH_SLASH)AmdCbsPkg$(PATH_SLASH)Library$(PATH_SLASH)Family$(PATH_SLASH)0x17$(PATH_SLASH)RV$(PATH_SLASH)External$(PATH_SLASH)ResourceRVFP5$(PATH_SLASH)IdsNvDefRV.h
	ATTRIB -r $(WORKSPACE)$(PATH_SLASH)AmdCbsPkg$(PATH_SLASH)Library$(PATH_SLASH)Family$(PATH_SLASH)0x17$(PATH_SLASH)RV$(PATH_SLASH)External$(PATH_SLASH)ResourceRVFP5$(PATH_SLASH)IdsNvIntDefRV.h
	ATTRIB -r $(WORKSPACE)$(PATH_SLASH)AmdCbsPkg$(PATH_SLASH)Library$(PATH_SLASH)Family$(PATH_SLASH)0x17$(PATH_SLASH)RV$(PATH_SLASH)External$(PATH_SLASH)ResourceRVFP5$(PATH_SLASH)IdsSampleRV.c
	ATTRIB -r $(WORKSPACE)$(PATH_SLASH)AmdCbsPkg$(PATH_SLASH)Library$(PATH_SLASH)Family$(PATH_SLASH)0x17$(PATH_SLASH)RV$(PATH_SLASH)External$(PATH_SLASH)ResourceRVFP5$(PATH_SLASH)AmdCbsForm.vfr
	ATTRIB -r $(WORKSPACE)$(PATH_SLASH)AmdCbsPkg$(PATH_SLASH)Library$(PATH_SLASH)Family$(PATH_SLASH)0x17$(PATH_SLASH)RV$(PATH_SLASH)External$(PATH_SLASH)ResourceRVFP5$(PATH_SLASH)AmdCbsStrings.uni
	ATTRIB -r $(WORKSPACE)$(PATH_SLASH)AmdCbsPkg$(PATH_SLASH)Library$(PATH_SLASH)Family$(PATH_SLASH)0x17$(PATH_SLASH)RV$(PATH_SLASH)External$(PATH_SLASH)ResourceRVFP5$(PATH_SLASH)AmdCbsVariable.h.Ori
	ATTRIB -r $(WORKSPACE)$(PATH_SLASH)AgesaModulePkg$(PATH_SLASH)Include$(PATH_SLASH)IdsNvIntIdRV.h
	ATTRIB -r $(WORKSPACE)$(PATH_SLASH)AgesaModulePkg$(PATH_SLASH)Include$(PATH_SLASH)IdsNvIdRV.h
	ATTRIB -r $(WORKSPACE)$(PATH_SLASH)AgesaModulePkg$(PATH_SLASH)Include$(PATH_SLASH)IdsNvDefRV.h

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