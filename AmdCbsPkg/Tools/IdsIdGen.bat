@REM call Ids Id headerfile script tool
@IF EXIST %WORKSPACE%\AGESA\AgesaModulePkg\Include (
  @SET AGESA_INC_PATH=%WORKSPACE%\AGESA\AgesaModulePkg\Include
) ELSE (
  @SET AGESA_INC_PATH=%WORKSPACE%\AgesaModulePkg\Include
)

%WORKSPACE%\AmdCbsPkg\Tools\Perl\bin\perl.exe -I%WORKSPACE%\AmdCbsPkg\Tools -I%WORKSPACE%\AmdCbsPkg\Tools\Perl\lib %WORKSPACE%\AmdCbsPkg\Tools\IdsIdGen.pl -i %WORKSPACE%\AmdCbsPkg\Library -o %WORKSPACE%\AmdCbsPkg\Build
xcopy %WORKSPACE%\AmdCbsPkg\Build\*.*      %AGESA_INC_PATH% /S /Y
