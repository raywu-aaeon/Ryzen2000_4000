@REM call CBS XML parse tool
@SET CBS_LIB_FAMILY_PATH=Library\Family\0x17\RV\External
@SET CBS_AGESA_PATH=%WORKSPACE%\AgesaModulePkg\Include
IF NOT EXIST %CBS_AGESA_PATH% @SET CBS_AGESA_PATH=%WORKSPACE%\AGESA\AgesaModulePkg\Include
@SET FIRMWARE_PATH=%WORKSPACE%\AgesaPkg\Addendum\Apcb\Inc\RV
IF NOT EXIST %FIRMWARE_PATH% @SET FIRMWARE_PATH=%WORKSPACE%\AGESA\AgesaPkg\Addendum\Apcb\Inc\RV

@if /I "%1" == "" (
  rem save previous AmdCbsVariable.h as base
  @copy /Y %WORKSPACE%\AmdCbsPkg\%CBS_LIB_FAMILY_PATH%\ResourceRVFP5\AmdCbsVariable.h %WORKSPACE%\AmdCbsPkg\%CBS_LIB_FAMILY_PATH%\ResourceRVFP5\AmdCbsVariable.h.Ori
  %WORKSPACE%\AmdCbsPkg\Tools\Perl\bin\perl.exe -I%WORKSPACE%\AmdCbsPkg\Tools -I%WORKSPACE%\AmdCbsPkg\Tools\Perl\lib %WORKSPACE%\AmdCbsPkg\Tools\CBSgenerate.pl -i %WORKSPACE%\AmdCbsPkg\%CBS_LIB_FAMILY_PATH%\Raven\eSetupRaven.xml -s %WORKSPACE%\AmdCbsPkg\%CBS_LIB_FAMILY_PATH%\Raven\eRavenSetting.xml --apcbfile %FIRMWARE_PATH%\APCB.h -o %WORKSPACE%\AmdCbsPkg\%CBS_LIB_FAMILY_PATH%\ResourceRVFP5 --version external -b enable -t 1  --variable-file %WORKSPACE%\AmdCbsPkg\%CBS_LIB_FAMILY_PATH%\ResourceRVFP5\AmdCbsVariable.h.Ori
  @REM Only copy files if they differ.  Prevents needless rebuild of files.
  fc %WORKSPACE%\AmdCbsPkg\%CBS_LIB_FAMILY_PATH%\ResourceRVFP5\AmdCbsVariable.h %WORKSPACE%\AmdCbsPkg\Include\Library\AmdCbsVariableRVFP5.h > nul 2>&1 || @copy /y %WORKSPACE%\AmdCbsPkg\%CBS_LIB_FAMILY_PATH%\ResourceRVFP5\AmdCbsVariable.h %WORKSPACE%\AmdCbsPkg\Include\Library\AmdCbsVariableRVFP5.h
  fc %WORKSPACE%\AmdCbsPkg\%CBS_LIB_FAMILY_PATH%\ResourceRVFP5\IdsNvDefRV.h %CBS_AGESA_PATH%\IdsNvDefRV.h > nul 2>&1  || @copy /y %WORKSPACE%\AmdCbsPkg\%CBS_LIB_FAMILY_PATH%\ResourceRVFP5\IdsNvDefRV.h %CBS_AGESA_PATH%
) else if /I "%1" == "RVAM4" (
  rem save previous AmdCbsVariable.h as base
  @copy /Y %WORKSPACE%\AmdCbsPkg\%CBS_LIB_FAMILY_PATH%\ResourceRVAM4\AmdCbsVariable.h %WORKSPACE%\AmdCbsPkg\%CBS_LIB_FAMILY_PATH%\ResourceRVAM4\AmdCbsVariable.h.Ori
  %WORKSPACE%\AmdCbsPkg\Tools\Perl\bin\perl.exe -I%WORKSPACE%\AmdCbsPkg\Tools -I%WORKSPACE%\AmdCbsPkg\Tools\Perl\lib %WORKSPACE%\AmdCbsPkg\Tools\CBSgenerate.pl -i %WORKSPACE%\AmdCbsPkg\%CBS_LIB_FAMILY_PATH%\Raven\eSetupRavenAm4.xml -s %WORKSPACE%\AmdCbsPkg\%CBS_LIB_FAMILY_PATH%\Raven\eRavenSetting.xml --apcbfile %FIRMWARE_PATH%\APCB.h -o %WORKSPACE%\AmdCbsPkg\%CBS_LIB_FAMILY_PATH%\ResourceRVAM4 --version external -b enable -t 1 --variable-file %WORKSPACE%\AmdCbsPkg\%CBS_LIB_FAMILY_PATH%\ResourceRVAM4\AmdCbsVariable.h.Ori 
  @REM Only copy files if they differ.  Prevents needless rebuild of files.
  fc %WORKSPACE%\AmdCbsPkg\%CBS_LIB_FAMILY_PATH%\ResourceRVAM4\AmdCbsVariable.h %WORKSPACE%\AmdCbsPkg\Include\Library\AmdCbsVariableRVAM4.h > nul 2>&1 || @copy /y %WORKSPACE%\AmdCbsPkg\%CBS_LIB_FAMILY_PATH%\ResourceRVAM4\AmdCbsVariable.h %WORKSPACE%\AmdCbsPkg\Include\Library\AmdCbsVariableRVAM4.h
  fc %WORKSPACE%\AmdCbsPkg\%CBS_LIB_FAMILY_PATH%\ResourceRVAM4\IdsNvDefRV.h %CBS_AGESA_PATH%\IdsNvDefRV.h > nul 2>&1  || @copy /y %WORKSPACE%\AmdCbsPkg\%CBS_LIB_FAMILY_PATH%\ResourceRVAM4\IdsNvDefRV.h %CBS_AGESA_PATH%
) else if /I "%1" == "BILBY" (
rem save previous AmdCbsVariable.h as base
  @copy /Y %WORKSPACE%\AmdCbsPkg\%CBS_LIB_FAMILY_PATH%\ResourceRVFP5\AmdCbsVariable.h %WORKSPACE%\%CBS_RES_BUILD%\AmdCbsVariable.h.Ori
  %WORKSPACE%\AmdCbsPkg\Tools\CBSgenerate.exe -i %WORKSPACE%\AmdCbsPkg\%CBS_LIB_FAMILY_PATH%\Raven\eSetupRavenBilby.xml -s %WORKSPACE%\AmdCbsPkg\%CBS_LIB_FAMILY_PATH%\Raven\eRavenSetting.xml --apcbfile %FIRMWARE_PATH%\APCB.h -o %WORKSPACE%\%CBS_RES_BUILD% --version external -b enable -t 1  --variable-file %WORKSPACE%\%CBS_RES_BUILD%\AmdCbsVariable.h.Ori
  @REM Only copy files if they differ.  Prevents needless rebuild of files.
  fc %WORKSPACE%\%CBS_RES_BUILD%\AmdCbsVariable.h %WORKSPACE%\AmdCbsPkg\Include\Library\AmdCbsVariableRVFP5.h > nul 2>&1 || @copy /y %WORKSPACE%\%CBS_RES_BUILD%\AmdCbsVariable.h %WORKSPACE%\AmdCbsPkg\Include\Library\AmdCbsVariableRVFP5.h
  fc %WORKSPACE%\%CBS_RES_BUILD%\IdsNvDefRV.h %CBS_AGESA_PATH%\IdsNvDefRV.h > nul 2>&1  || @copy /y %WORKSPACE%\%CBS_RES_BUILD%\IdsNvDefRV.h %CBS_AGESA_PATH%
)
