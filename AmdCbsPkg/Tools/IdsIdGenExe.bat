@set WORKSPACE=%cd%
@set CBS_RES_BUILD=Build\Resource@Token(CBS_SOLUTION_TYPE)
@set GBS_FILE_NAME=
@set CBS_PERL_DIR=%WORKSPACE%\AmdCbsPkg\Tools\Perl\bin\perl.exe

@IF EXIST %CBS_PERL_DIR% goto RunPerlIdsIdGen
@echo  AmdCbsPkg: Run EXE file

@REM call Ids Id headerfile script tool
@IF EXIST %WORKSPACE%\AGESA\AgesaModulePkg\Include (
  @SET AGESA_INC_PATH=%WORKSPACE%\AGESA\AgesaModulePkg\Include
) ELSE (
  @SET AGESA_INC_PATH=%WORKSPACE%\AgesaModulePkg\Include
)

%WORKSPACE%\AmdCbsPkg\Tools\IdsIdGen.exe -i %WORKSPACE%\AmdCbsPkg\Library -o %WORKSPACE%\%CBS_RES_BUILD%\Build
xcopy %WORKSPACE%\%CBS_RES_BUILD%\Build\*.*      %AGESA_INC_PATH% /S /Y

goto EndOfIdsIdGen

:RunPerlIdsIdGen
@echo  AmdCbsPkg: The %CBS_PERL_DIR% exist Run original Perl file
%WORKSPACE%\AmdCbsPkg\Tools\IdsIdGen.bat
goto EndOfIdsIdGen

:EndOfIdsIdGen