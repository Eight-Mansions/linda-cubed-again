@echo off
set filename=Linda-English
set file_type=BIN
set patch_file=patch.xdelta
set patch_file_other=patch-other.xdelta

pushd %~dp0
if "%~1"=="" goto :NOISO

echo Patching %file_type%...

patch_data\xdelta.exe -d -f -s "%~1" patch_data\%patch_file% %filename%.bin > nul 2>&1
if not errorlevel 1 (
        goto :FIN
    )

patch_data\xdelta.exe -d -f -s "%~1" patch_data\%patch_file_other% %filename%.bin > nul 2>&1
if not errorlevel 1 (
        goto :FIN
    )


if errorlevel 1 goto :XDELTAERR
goto :FIN

:NOISO
echo To patch %file_type% don't run this bat file.
echo Simply drag and drop %file_type% on it and the patch process will start.
:EXIT

:XDELTAERR
echo.
echo Something went wrong while patching files.
echo You might be trying to patch the wrong %file_type%, try using a different one.
goto :EXIT

:FIN
echo FILE "%filename%.bin" BINARY>%filename%.cue
echo   TRACK 01 MODE2/2352>>%filename%.cue
echo     INDEX 01 00:00:00>>%filename%.cue
echo.

echo Success!
echo Patched %file_type% was saved to %filename%.bin and .cue next to this bat file
goto :EXIT

:EXIT
popd
echo Press any key to close this window
pause >nul
exit