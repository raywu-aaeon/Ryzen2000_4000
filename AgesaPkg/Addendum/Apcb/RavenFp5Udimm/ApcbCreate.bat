@ECHO OFF
REM ============================================================================
REM ============================================================================
REM ============================================================================
REM Start of customization section
REM ============================================================================
REM ============================================================================
REM ============================================================================

REM ============================================================================
REM Customize the APCB output binary and input data files
REM ============================================================================

REM ----------------------------------------------------------------------------
REM First thing, setup ApcbToolV2.exe
REM ----------------------------------------------------------------------------
IF NOT DEFINED TOOL_DIR SET TOOL_DIR=%CD%\..\..\..\..\AgesaModulePkg\AMDTools\ApcbToolV2\Tools

REM ----------------------------------------------------------------------------
REM Target APCB binary will be put in RELEASE_DIR
REM ----------------------------------------------------------------------------
SET APCB_BIN_FILE_BASE_NAME=APCB_RV_D4

REM ----------------------------------------------------------------------------
REM Reset variable then start adding APCB data source C files (base name only)
REM ----------------------------------------------------------------------------
SET APCB_DATA_DIR=ApcbData
SET APCB_DATA_TYPE_FILE_LIST=

SET APCB_DATA_TYPE_FILE_LIST=%APCB_DATA_TYPE_FILE_LIST% ApcbData_RV_GID_0x1706_Type_ExtDefParams
SET APCB_DATA_TYPE_FILE_LIST=%APCB_DATA_TYPE_FILE_LIST% ApcbData_RV_GID_0x1706_Type_ExtParams
SET APCB_DATA_TYPE_FILE_LIST=%APCB_DATA_TYPE_FILE_LIST% ApcbData_RV_GID_0x1704_Type_SpdInfo
SET APCB_DATA_TYPE_FILE_LIST=%APCB_DATA_TYPE_FILE_LIST% ApcbData_RV_GID_0x1703_Type_ExtDefParams
SET APCB_DATA_TYPE_FILE_LIST=%APCB_DATA_TYPE_FILE_LIST% ApcbData_RV_GID_0x1703_Type_ExtParams
SET APCB_DATA_TYPE_FILE_LIST=%APCB_DATA_TYPE_FILE_LIST% ApcbData_RV_GID_0x1704_Type_ConsoleOutControl
SET APCB_DATA_TYPE_FILE_LIST=%APCB_DATA_TYPE_FILE_LIST% ApcbData_RV_GID_0x1704_Type_DimmInfoSpd
SET APCB_DATA_TYPE_FILE_LIST=%APCB_DATA_TYPE_FILE_LIST% ApcbData_RV_GID_0x1704_Type_ErrorOutControl
SET APCB_DATA_TYPE_FILE_LIST=%APCB_DATA_TYPE_FILE_LIST% ApcbData_RV_GID_0x1704_Type_ExtDefParams
SET APCB_DATA_TYPE_FILE_LIST=%APCB_DATA_TYPE_FILE_LIST% ApcbData_RV_GID_0x1704_Type_ExtParams
SET APCB_DATA_TYPE_FILE_LIST=%APCB_DATA_TYPE_FILE_LIST% ApcbData_RV_GID_0x1704_Type_ExtVoltageControl
SET APCB_DATA_TYPE_FILE_LIST=%APCB_DATA_TYPE_FILE_LIST% ApcbData_RV_GID_0x1704_Type_PsoOverride
SET APCB_DATA_TYPE_FILE_LIST=%APCB_DATA_TYPE_FILE_LIST% ApcbData_RV_GID_0x1704_Type_PsOdtPatUDIMMDdr4
SET APCB_DATA_TYPE_FILE_LIST=%APCB_DATA_TYPE_FILE_LIST% ApcbData_RV_GID_0x1704_Type_PsCadBusUDIMMDdr4 
SET APCB_DATA_TYPE_FILE_LIST=%APCB_DATA_TYPE_FILE_LIST% ApcbData_RV_GID_0x1704_Type_PsDataBusUDIMMDdr4 
SET APCB_DATA_TYPE_FILE_LIST=%APCB_DATA_TYPE_FILE_LIST% ApcbData_RV_GID_0x1704_Type_PsMaxFreqUDIMMDdr4
SET APCB_DATA_TYPE_FILE_LIST=%APCB_DATA_TYPE_FILE_LIST% ApcbData_RV_GID_0x1704_Type_PsStretchFreqUDIMMDdr4
SET APCB_DATA_TYPE_FILE_LIST=%APCB_DATA_TYPE_FILE_LIST% ApcbData_RV_GID_0x1707_Type_IntDefParams
SET APCB_DATA_TYPE_FILE_LIST=%APCB_DATA_TYPE_FILE_LIST% ApcbData_RV_GID_0x1707_Type_IntParams

REM ----------------------------------------------------------------------------
REM BoardIdGettingMethod applies to multiple APCB only, please remove it if 
REM only 1 APCB instance is needed
REM ----------------------------------------------------------------------------
REM SET APCB_DATA_TYPE_FILE_LIST=%APCB_DATA_TYPE_FILE_LIST% ApcbData_RV_GID_0x1704_Type_BoardIdGettingMethod

GOTO START_MAIN_FLOW

REM ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
REM End of customization section
REM ============================================================================
REM ============================================================================
REM ============================================================================


REM ============================================================================
REM Environment Checks
REM ============================================================================
:ENV_CHECK
	SET APCB_TOOL_NAME=ApcbToolV2.exe
	IF NOT DEFINED TOOL_DIR ECHO
	IF NOT EXIST %TOOL_DIR%\%APCB_TOOL_NAME%  GOTO ERROR_TOOLDIR&& EXIT /B 10
	IF EXIST %TOOL_DIR%\%APCB_TOOL_NAME%  ECHO Found %APCB_TOOL_NAME% at "%TOOL_DIR%".
	GOTO :EOF

REM ============================================================================
REM ============================================================================
REM ============================================================================
REM Start of main flow
REM ============================================================================
REM ============================================================================
REM ============================================================================
:START_MAIN_FLOW
CALL :DISP_HEADER
REM cls
CALL :ENV_CHECK
CALL :GET_WORK_DIR
CALL :GET_SYS_TIME
IF /I "%1" == "--HELP" CALL :DISP_HELP && GOTO END
IF /I "%1" == "-H"     CALL :DISP_HELP && GOTO END
IF /I "%1" == ""       CALL :DISP_HELP && GOTO END

SET BUILD_DIR=Build
SET RELEASE_DIR=Release
SET LOG_DIR=Log

:PARSE_PARAM
IF /I "%1" == "CLEAN"  CALL :CLEAN_OUTPUT
REM Force to use parameter to continue the build
IF /I "%1" == "BUILD"  GOTO START_BUILDING
IF /I "%1" == ""       GOTO END
REM Parse the next parameter
SHIFT
GOTO PARSE_PARAM
GOTO END

REM ============================================================================
REM Start building if input proper parameter
REM ============================================================================
:START_BUILDING

REM ============================================================================
@ECHO.
@ECHO Building APCB data ...
REM ============================================================================
CALL :BUILD_ALL_C_SOURCES || GOTO ERR_END

REM ============================================================================
@ECHO.
@ECHO Prepare APCB data for building ...
REM ============================================================================

REM ============================================================================
REM Prepare parameter for data files from APCB_DATA_TYPE_FILE_LIST
REM ============================================================================
CALL :PREPARE_DATA_FILE_LIST_IN_TOOL_PARAM_FORM

REM ============================================================================
@ECHO.
@ECHO APCB binary generation ...
REM ============================================================================
SET APCB_BIN_FILE=%APCB_LOCAL_WORK_DIR%\%RELEASE_DIR%\%APCB_BIN_FILE_BASE_NAME%.bin
REM File extension .txt will be added
SET APCB_EXE_LOG=ApcbBuild_ExeLog
CALL :RUN_APCB_TOOL_WITH_EXE_LOG || GOTO ERR_END

GOTO END
REM ============================================================================
REM ============================================================================
REM ============================================================================
REM End of main flow
REM ============================================================================
REM ============================================================================
REM ============================================================================






REM ============================================================================
REM Local functions
REM ============================================================================

REM ----------------------------------------------------------------------------
REM Display header
REM ----------------------------------------------------------------------------
:DISP_HEADER
	SET BAT_TOOL_NAME=%~n0
	@ECHO.
	@ECHO **************************
	@ECHO  Start %BAT_TOOL_NAME%
	@ECHO **************************
	@ECHO.
	GOTO :EOF


REM ----------------------------------------------------------------------------
REM Display help info
REM ----------------------------------------------------------------------------
:DISP_HELP
	@ECHO.
	@ECHO %~n0 help info
	@ECHO.
	@ECHO USAGE: 
	@ECHO       For clean up output directories (Release, Build and Log directoies)
	@ECHO		%~n0  CLEAN    
	@ECHO.
	@ECHO       For build APCB data and tool
	@ECHO		%~n0  BUILD    
	@ECHO.
	@ECHO       You may combine both
	@ECHO		%~n0  CLEAN BUILD    
	@ECHO.
	GOTO :EOF

REM ----------------------------------------------------------------------------
REM This is a "function" to do common Error tasks
REM ----------------------------------------------------------------------------
:GOT_ERROR
  ECHO:**** BUILD FAILED ****
  EXIT /B 1

REM ----------------------------------------------------------------------------
REM Get current working director and set variable APCB_LOCAL_WORK_DIR for later use
REM ----------------------------------------------------------------------------
:GET_WORK_DIR
	SET APCB_LOCAL_WORK_DIR=%CD%
  IF DEFINED APCB_WORK_DIR SET APCB_LOCAL_WORK_DIR=%APCB_WORK_DIR%
	GOTO :EOF

REM ----------------------------------------------------------------------------
REM Clean up output folder
REM ----------------------------------------------------------------------------
:CLEAN_OUTPUT
	for %%O IN (%APCB_LOCAL_WORK_DIR%\%BUILD_DIR% %APCB_LOCAL_WORK_DIR%\%LOG_DIR% %APCB_LOCAL_WORK_DIR%\%RELEASE_DIR%) DO (
		IF EXIST  %%O ECHO Deleting directory "%%O"...
		IF EXIST  %%O rd /s /q %%O
	)
	GOTO :EOF

REM ----------------------------------------------------------------------------
REM Prepare data file list in tool parameter form
REM ----------------------------------------------------------------------------
:PREPARE_DATA_FILE_LIST_IN_TOOL_PARAM_FORM
	SET APCB_DATA_TYPE_FILE_LIST_TOOL_PARAM=
	for %%D IN ( %APCB_DATA_TYPE_FILE_LIST%) DO (
		CALL :APPEND_DATA_FILE_LIST_IN_TOOL_PARAM_FORM %%D
	)
	GOTO :EOF

REM ----------------------------------------------------------------------------
REM Append data file list in tool parameter form
REM ----------------------------------------------------------------------------
:APPEND_DATA_FILE_LIST_IN_TOOL_PARAM_FORM
	REM Specify the build data file extension
	SET APCB_DATA_OUTPUT_FILE_EXT=exe
	SET APCB_DATA_TYPE_FILE_LIST_TOOL_PARAM=%APCB_DATA_TYPE_FILE_LIST_TOOL_PARAM% -I %1.%APCB_DATA_OUTPUT_FILE_EXT%
	GOTO :EOF

REM ----------------------------------------------------------------------------
REM Get system time
REM 
REM OUTPUT: Environment varibles SysTime, SysTimeHour, SysTimeMin and SysDate
REM ----------------------------------------------------------------------------
: GET_SYS_TIME
	REM Get the system date and time
	FOR /F "tokens=1-4 delims=/ " %%a IN ("%date%") DO (
	  SET SysDate=%%a%%b%%c
	)
	FOR /F "tokens=1-4 delims=:. " %%a IN ("%time%") DO (
	  SET SysTimeHour=%%a
	  SET SysTimeMin=%%b%%c
	)
	set SysTime=%SysTimeHour%%SysTimeMin%
	GOTO :EOF

REM ----------------------------------------------------------------------------
REM Build all C source files in APCB_DATA_TYPE_FILE_LIST
REM ----------------------------------------------------------------------------
:BUILD_ALL_C_SOURCES
	SET C_FLAGS=/nologo
	SET C_INCLUDE_PATH_FLAG=/I Include /I ..\Inc /I ..\..\Inc
	REM --------------------------------------------------------------------
	IF NOT EXIST %APCB_LOCAL_WORK_DIR%\%BUILD_DIR% md %APCB_LOCAL_WORK_DIR%\%BUILD_DIR%
	IF NOT EXIST %APCB_LOCAL_WORK_DIR%\%RELEASE_DIR% md %APCB_LOCAL_WORK_DIR%\%RELEASE_DIR%
	IF NOT EXIST %APCB_LOCAL_WORK_DIR%\%LOG_DIR% md %APCB_LOCAL_WORK_DIR%\%LOG_DIR%
	REM --------------------------------------------------------------------
	REM Build APCB data files
	REM --------------------------------------------------------------------
	for %%F IN (%APCB_DATA_TYPE_FILE_LIST%) DO (
		@ECHO Compiling ...
		cl %C_FLAGS% %APCB_DATA_DIR%\%%F.c  %C_INCLUDE_PATH_FLAG% /Fo%APCB_LOCAL_WORK_DIR%\%BUILD_DIR%\%%F.obj /Fe%APCB_LOCAL_WORK_DIR%\%BUILD_DIR%\ /Fm%APCB_LOCAL_WORK_DIR%\%BUILD_DIR%\%%F.map
		IF ERRORLEVEL 1 EXIT /B 1
		@ECHO.
	)
	GOTO :EOF


REM ----------------------------------------------------------------------------
REM Run APCB Tool and generate log
REM 
REM INPUT:
REM        BUILD_DIR
REM        APCB_BIN_FILE
REM        APCB_DATA_TYPE_FILE_LIST_TOOL_PARAM
REM        APCB_EXE_LOG
REM OUTPUT:
REM        APCB_BIN_FILE - APCB binary file specified
REM        APCB_EXE_LOG  - Execution log specified (create a new file)
REM ----------------------------------------------------------------------------
:RUN_APCB_TOOL_WITH_EXE_LOG
	SET APCB_EXE_LOG_INPUT=%APCB_EXE_LOG%
	REM --------------------------------------------------------------------
	SET APCB_EXE_LOG=%APCB_LOCAL_WORK_DIR%\%LOG_DIR%\%APCB_EXE_LOG_INPUT%.txt
	@ECHO Run APCB tool with log ...      (Log:%APCB_EXE_LOG%)
	PUSHD %APCB_LOCAL_WORK_DIR%\%BUILD_DIR%
	CALL :APCB_TOOL || EXIT /B 1
	POPD
	REM --------------------------------------------------------------------
	REM Restor variable
	SET APCB_EXE_LOG=%APCB_EXE_LOG_INPUT%
	SET APCB_EXE_LOG_INPUT=
	GOTO :EOF

REM ----------------------------------------------------------------------------
REM Run APCB Generator tool V2 by ApcbToolV2
REM 
REM INPUT:
REM        BUILD_DIR
REM        APCB_BIN_FILE
REM        APCB_DATA_TYPE_FILE_LIST_TOOL_PARAM
REM        APCB_EXE_LOG
REM OUTPUT:
REM        APCB_BIN_FILE - APCB binary file specified
REM        APCB_EXE_LOG  - Execution log specified (create a new file)
REM ----------------------------------------------------------------------------
:APCB_TOOL
	%TOOL_DIR%\%APCB_TOOL_NAME% --outputfile %APCB_BIN_FILE% %APCB_DATA_TYPE_FILE_LIST_TOOL_PARAM% > %APCB_EXE_LOG% || EXIT /B 1
	GOTO :EOF
	

REM ============================================================================
:ERROR_TOOLDIR
	ECHO.
	ECHO.
	ECHO ***********************************************************************
	ECHO  ERROR : %APCB_TOOL_NAME% cannot be found at "%TOOL_DIR%" (TOOL_DIR)
    SET TOOL_DIR
	ECHO.
	ECHO  Environment variable TOOL_DIR should be set properly.
	ECHO  %APCB_TOOL_NAME% should be found under folder of "AgesaModulePkg\AMDTools\ApcbToolV2\Tools".
	ECHO ***********************************************************************
	ECHO.
	ECHO.
	PAUSE
	GOTO :EOF

REM ============================================================================
:ERR_END
	@ECHO.
	@ECHO **************************
	@ECHO  Exit with error!
	@ECHO **************************
	EXIT /B 1

:END
	@ECHO.
	@ECHO **************************
	@ECHO  %BAT_TOOL_NAME% completed!
	@ECHO **************************
	@ECHO.
