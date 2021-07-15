@echo off
pushd %~dp0
if "%~1"=="" goto :NOISO

echo.
echo Patching ISO...

tools\xdelta.exe -d -f -s "%~1" patch\patch.xdelta3 yarudora_1-patched.iso

echo. 
echo.
echo.
echo All done!
echo ISO was saved to yarudora_1-patched.iso next to this bat file
goto :FIN

:NOISO
echo To patch ISO don't run this bat file
echo Simply drag and drop ISO on it and the patch process will start
goto :FIN

:FIN
popd
echo Press any key to close this window
pause >nul
exit