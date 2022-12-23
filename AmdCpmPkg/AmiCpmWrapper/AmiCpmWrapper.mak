#*************************************************************************
#*************************************************************************
#**                                                                     **
#**        (C)Copyright 1985-2013, American Megatrends, Inc.            **
#**                                                                     **
#**                       All Rights Reserved.                          **
#**                                                                     **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
#**                                                                     **
#**                       Phone: (770)-246-8600                         **
#**                                                                     **
#*************************************************************************
#*************************************************************************

#*************************************************************************
# $Header: $
#
# $Revision: $
#
# $Date: $
#*************************************************************************

#*************************************************************************
#<AMI_FHDR_START>
#
# Name:         AmiCpmWrapper.mak
#
# Description:
#
#<AMI_FHDR_END>
#*************************************************************************
Prepare : CopyAodOemFile

CopyAodOemFile:
	$(ECHO) cd AmdCpmPkg\Features\AOD\Asl
	$(ECHO) $(CP) /b /y $(AOD_OEM_ASI_DIR)\AodOem.asi $(AOD_OEM_ASI_DIR)\AodOem.asi.bak
	$(ECHO) $(CP) /b /y $(AOD_OEM_ASI_DIR)\AodOem.cfg $(AOD_OEM_ASI_DIR)\AodOem.cfg.bak	
    $(ECHO)	cd $(AOD_OEM_ASI_OVERRIDE_DIR)	
	$(ECHO) $(CP) /b /y $(AOD_OEM_ASI_OVERRIDE_DIR)\AodOem.asi $(AOD_OEM_ASI_DIR)\AodOem.asi
	$(ECHO) $(CP) /b /y $(AOD_OEM_ASI_OVERRIDE_DIR)\AodOem.cfg $(AOD_OEM_ASI_DIR)\AodOem.cfg

End : RestoreAodOemFile

RestoreAodOemFile:
	$(ECHO) cd $(AOD_OEM_ASI_DIR)
	$(ECHO) $(CP) /b /y $(AOD_OEM_ASI_DIR)\AodOem.asi.bak $(AOD_OEM_ASI_DIR)\AodOem.asi
	$(ECHO) $(CP) /b /y $(AOD_OEM_ASI_DIR)\AodOem.cfg.bak $(AOD_OEM_ASI_DIR)\AodOem.cfg
#**********************************************************************
#**********************************************************************
#**                                                                  **
#**        (C)Copyright 1985-2013, American Megatrends, Inc.         **
#**                                                                  **
#**                       All Rights Reserved.                       **
#**                                                                  **
#**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
#**                                                                  **
#**                       Phone: (770)-246-8600                      **
#**                                                                  **
#**********************************************************************
#**********************************************************************