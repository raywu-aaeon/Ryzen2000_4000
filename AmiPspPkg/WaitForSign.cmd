@ECHO OFF
IF %1 == BR (
	ECHO.  
	ECHO      Please sign "%2" with your OEM BIOS Signing key.
	ECHO. 
	ECHO      Place generated signature of "%2" to "%3"
	ECHO.
	ECHO      After the above steps are complete, press any key to complete BIOS build.
	ECHO.
) else (
	ECHO.  
	ECHO      Please sign "%2" and "%3" with your OEM BIOS Signing key.
	ECHO. 
	ECHO      Place generated signature of "%2" to "%4" and signature of "%3" to "%5" 
	ECHO.
	ECHO      After the above steps are complete, press any key to complete BIOS build.
	ECHO.
)
@PAUSE
@EXIT