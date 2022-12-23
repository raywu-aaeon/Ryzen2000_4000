@SET CBS_LIB_FAMILY_PATH=\Library\CbsSetupLibNull

@if /I "%1" == "" (
  @copy /y %WORKSPACE%\AmdCbsPkg\AmdCbsPkg.dsc %WORKSPACE%\AmdCbsPkg\Package.dsc
  @copy /y %WORKSPACE%\AmdCbsPkg\%CBS_LIB_FAMILY_PATH%\AmdCbsVariable.h %WORKSPACE%\AmdCbsPkg\Include\Library
  @copy /y %WORKSPACE%\AmdCbsPkg\%CBS_LIB_FAMILY_PATH%\AmdCbsFormID.h %WORKSPACE%\AmdCbsPkg\Include\Library
) else if /I "%1" == "POSTBUILD" (
  @if exist %WORKSPACE%\AmdCbsPkg\Include\Library\AmdCbsVariable.h del %WORKSPACE%\AmdCbsPkg\Include\Library\AmdCbsVariable.h
  @if exist %WORKSPACE%\AmdCbsPkg\Include\Library\AmdCbsFormID.h del %WORKSPACE%\AmdCbsPkg\Include\Library\AmdCbsFormID.h
  @if exist %WORKSPACE%\AmdCbsPkg\Package.dsc del %WORKSPACE%\AmdCbsPkg\Package.dsc
)
