:: *****************************************************************************
:: *
:: * Copyright 2008 - 2021 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
:: *
:: * AMD is granting You permission to use this software and documentation (if
:: * any) (collectively, the "Software") pursuant to the terms and conditions of
:: * the Software License Agreement included with the Software. If You do not have
:: * a copy of the Software License Agreement, contact Your AMD representative for
:: * a copy.
:: *
:: * You agree that You will not reverse engineer or decompile the Software, in
:: * whole or in part, except as allowed by applicable law.
:: *
:: * WARRANTY DISCLAIMER: THE SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
:: * KIND. AMD DISCLAIMS ALL WARRANTIES, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
:: * BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, QUALITY,
:: * FITNESS FOR A PARTICULAR PURPOSE, TITLE, NON-INFRINGEMENT AND WARRANTIES
:: * ARISING FROM CUSTOM OF TRADE OR COURSE OF USAGE WITH RESPECT TO THE SOFTWARE,
:: * INCLUDING WITHOUT LIMITATION, THAT THE SOFTWARE WILL RUN UNINTERRUPTED OR
:: * ERROR-FREE. THE ENTIRE RISK ASSOCIATED WITH THE USE OF THE SOFTWARE IS
:: * ASSUMED BY YOU. Some jurisdictions do not allow the exclusion of implied
:: * warranties, so the above exclusion may not apply to You, but only to the
:: * extent required by law.
:: *
:: * LIMITATION OF LIABILITY AND INDEMNIFICATION: TO THE EXTENT NOT PROHIBITED BY
:: * APPLICABLE LAW, AMD AND ITS LICENSORS WILL NOT, UNDER ANY CIRCUMSTANCES BE
:: * LIABLE TO YOU FOR ANY PUNITIVE, DIRECT, INCIDENTAL, INDIRECT, SPECIAL OR
:: * CONSEQUENTIAL DAMAGES ARISING FROM POSSESSION OR USE OF THE SOFTWARE OR
:: * OTHERWISE IN CONNECTION WITH ANY PROVISION OF THIS AGREEMENT EVEN IF AMD AND
:: * ITS LICENSORS HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES. THIS
:: * INCLUDES, WITHOUT LIMITATION, DAMAGES DUE TO LOST OR MISAPPROPRIATED DATA,
:: * LOST PROFITS OR CONFIDENTIAL OR OTHER INFORMATION, FOR BUSINESS INTERRUPTION,
:: * FOR PERSONAL INJURY, FOR LOSS OF PRIVACY, FOR FAILURE TO MEET ANY DUTY
:: * INCLUDING OF GOOD FAITH OR REASONABLE CARE, FOR NEGLIGENCE AND FOR ANY OTHER
:: * PECUNIARY OR OTHER LOSS WHTSOEVER. In no event shall AMD's total liability to
:: * You for all damages, losses, and causes of action (whether in contract, tort
:: * (including negligence) or otherwise) exceed the amount of $50 USD. You agree
:: * to defend, indemnify and hold harmless AMD, its subsidiaries and affiliates
:: * and their respective licensors, directors, officers, employees, affiliates or
:: * agents from and against any and all loss, damage, liability and other
:: * expenses (including reasonable attorneys' fees), resulting from Your
:: * possession or use of the Software or violation of the terms and conditions of
:: * this Agreement.
:: *
:: * U.S. GOVERNMENT RESTRICTED RIGHTS: Notice to U.S. Government End Users. The
:: * Software and related documentation are "commercial items", as that term is
:: * defined at 48 C.F.R. Section 2.101, consisting of "commercial computer
:: * software" and "commercial computer software documentation", as such terms are
:: * used in 48 C.F.R. Section 12.212 and 48 C.F.R. Section 227.7202,
:: * respectively. Consistent with 48 C.F.R. Section 12.212 or 48 C.F.R. Sections
:: * 227.7202-1 through 227.7202-4, as applicable, the commercial computer
:: * software and commercial computer software documentation are being licensed to
:: * U.S. Government end users: (a) only as commercial items, and (b) with only
:: * those rights as are granted to all other end users pursuant to the terms and
:: * conditions set forth in this Agreement. Unpublished rights are reserved under
:: * the copyright laws of the United States.
:: *
:: * EXPORT RESTRICTIONS:  You shall adhere to all applicable U.S. import/export
:: * laws and regulations, as well as the import/export control laws and
:: * regulations of other countries as applicable. You further agree You will not
:: * export, re-export, or transfer, directly or indirectly, any product,
:: * technical data, software or source code received from AMD under this license,
:: * or the direct product of such technical data or software to any country for
:: * which the United States or any other applicable government requires an export
:: * license or other governmental approval without first obtaining such licenses
:: * or approvals, or in violation of any applicable laws or regulations of the
:: * United States or the country where the technical data or software was
:: * obtained. You acknowledges the technical data and software received will not,
:: * in the absence of authorization from U.S. or local law and regulations as
:: * applicable, be used by or exported, re-exported or transferred to: (i) any
:: * sanctioned or embargoed country, or to nationals or residents of such
:: * countries; (ii) any restricted end-user as identified on any applicable
:: * government end-user list; or (iii) any party where the end-use involves
:: * nuclear, chemical/biological weapons, rocket systems, or unmanned air
:: * vehicles.  For the most current Country Group listings, or for additional
:: * information about the EAR or Your obligations under those regulations, please
:: * refer to the website of the U.S. Bureau of Industry and Security at
:: * http://www.bis.doc.gov/.
:: ******************************************************************************

:: BuildPspImage InputBiosFile rtmfile PspDirectoryCfg OutputBiosFile KeyMode

@echo off
::Flag to control use python script or executable file generate from python
::TRUE:   Script file
::FALSE:  Executable file
IF "%USE_PYTHON_SCRIPT%" == "" (
  @set USE_PYTHON_SCRIPT=FALSE
)

::Input parameter check
IF /I "%5" == "" GOTO HELP
::System variable Check
SETLOCAL EnableDelayedExpansion

IF /I "%USE_PYTHON_SCRIPT%" == "TRUE" (
  IF EXIST "%PYTHON_PATH%\python.exe" (
    @set BUILDPSPDIRECTORY=%PYTHON_PATH%\python.exe BuildPspDirectory.py
  )ELSE IF EXIST "%PYTHON_PATH%\bin\python.exe" (
    @set BUILDPSPDIRECTORY=%PYTHON_PATH%\bin\python.exe BuildPspDirectory.py
  )ELSE (
    @echo !!!PYTHON_PATH system variable is NOT set correctly!!
    goto ERROR
  )
)ELSE (
  @set BUILDPSPDIRECTORY=BuildPspDirectory.exe
)

IF "%PSPKIT_PATH%" == "" (
  SET PSPKIT_PATH=%cd%
)
::CHECK_PATH
IF NOT EXIST %PSPKIT_PATH%\BuildPspImage.bat (
  @echo !!!PSPKIT_PATH system variable is NOT set correctly!!
  goto ERROR
)

IF "%PSP_FW_PATH%" == "" (
  SET PSP_FW_PATH=%cd%
)


IF "%TEMP_PATH%" == "" (
  @SET TEMP_PATH=%PSPKIT_PATH%\Temp
)

:START
::BIOS images
@set InputBiosFile=%1
@set RTM_FILE=%2
@set PspDirectoryCfg=%3
@set FINAL_BIOS=%4

::Related PATH
@SET PSP_DIR_TOOL_PATH=%PSPKIT_PATH%\PspDirectoryTool

::Create Temporary folder, and copy all files to it
@echo rd    %TEMP_PATH% /S /Q
IF EXIST %TEMP_PATH% rd    %TEMP_PATH% /S /Q
@echo mkdir %TEMP_PATH%
mkdir %TEMP_PATH%
@echo copy  %PSP_DIR_TOOL_PATH%\*.*  %TEMP_PATH% /Y
copy  %PSP_DIR_TOOL_PATH%\*.*  %TEMP_PATH% /Y
@echo copy  %PSP_FW_PATH%\*.*        %TEMP_PATH% /Y
copy  %PSP_FW_PATH%\*.*        %TEMP_PATH% /Y
@echo copy  %PSPKIT_PATH%\*.*       %TEMP_PATH% /Y
copy  %PSPKIT_PATH%\*.*       %TEMP_PATH% /Y
IF NOT "%CUSTOM_APCB_PATH%" == "" (
  @echo copy  %CUSTOM_APCB_PATH%\*.*   %TEMP_PATH% /Y
  copy  %CUSTOM_APCB_PATH%\*.*   %TEMP_PATH% /Y
)

if /I NOT "%5" == "NOSIGN" (
@echo copy  %RTM_FILE%               %TEMP_PATH% /Y
  IF EXIST %RTM_FILE% copy  %RTM_FILE%               %TEMP_PATH% /Y
)

::TOOLS
@set OPENSSL=bin\openssl.exe
::BINARYS
@set RTM_PRIVATE_KEY=TestRtmPrivateKey.pem
@set BIOS_L1_DIR_FILE=Output\BiosDirHeaderL1.bin
@set BIOS_L2_DIR_FILE=Output\BiosDirHeaderL2.bin
@set RTM_BIOSDIRL1_COMBINE_FILE=BiosRtmBiosL1Combine.bin
@set RTM_BIOSDIRL1_L2_COMBINE_FILE=BiosRtmBiosL1L2Combine.bin
@set RTM_FILE_L1_SIGNATURE=RTMSignature.bin
@set RTM_FILE_L1_L2_SIGNATURE=RTMSignatureL1L2.bin

pushd %TEMP_PATH%
::delete pyd & python27.dll which may cause the compatible issue with python installed on the machine when USE_PYTHON_SCRIPT=TRUE
IF /I "%USE_PYTHON_SCRIPT%" == "TRUE" (
  IF EXIST *.pyd del  *.pyd /F /Q
  IF EXIST python27.dll del  python27.dll /F /Q
)

@echo.
@echo [Generate PSP ^& BIOS Directory]
::Build without embed RTMSignature
if /I "%5" == "NOSIGN" goto BLDBIOS

:BLDBIOS


@echo.
@echo [Finally build the Final BiosImage]
@echo %BUILDPSPDIRECTORY% bb %InputBiosFile% %PspDirectoryCfg% %FINAL_BIOS%
%BUILDPSPDIRECTORY% bb %InputBiosFile% %PspDirectoryCfg% %FINAL_BIOS%

if %ERRORLEVEL% NEQ 0 goto ERROR
@echo copy Output\%FINAL_BIOS% ..\
copy Output\%FINAL_BIOS% ..\
popd
::rd %TEMP_PATH% /S /Q
@echo.
@echo PSP contents have been embed to %FINAL_BIOS%

GOTO END

:ERROR
@echo **** Build PSP Image Fail ****
@exit /B 2
GOTO END

:HELP
@echo Embed PSP contents to Specific BIOS image
@echo.
@echo BuildPspImage.bat rtmfile PspDirectoryCfg OutputBiosFile
@echo   Positional parameters:
@echo     rtmfile           The Root trunk module of BIOS, commonly it is the SEC,PEI combined FV image
@echo     PspDirectoryCfg   Config file which describe PSP directory layout, and input bios informations
@echo     OutputBiosFile    The output bios image after embed the PSP contents
@echo     KeyMode           Only "NOSIGN" allowed
goto END
:END
