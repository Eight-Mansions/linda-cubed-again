@echo off
set filename=linda
set working_name=linda
pushd %~dp0

echo Attempting to prepare the original game files.
echo ############################################################################
echo:

if "%~1"=="" goto :NOISO

:: Verify that the included file is a bin file
echo "%~1" | find /i ".bin" >nul
if errorlevel 1 (
    echo Supplied file was not a .bin file!
    goto :NOISO
)

mkdir orig
mkdir %working_name%

echo Normalizing bin name...
ren "%~1" "%filename%_original.bin"
echo:

echo Writing out a new cue file...
echo FILE "%filename%_original.bin" BINARY>"%filename%_original.cue"
echo   TRACK 01 MODE2/2352>>%filename%_original.cue
echo     INDEX 01 00:00:00>>%filename%_original.cue
echo.
echo:

echo Writing out a cue file for the working build...
echo FILE "%filename%_working.bin" BINARY>"%filename%_working.cue"
echo   TRACK 01 MODE2/2352>>%filename%_working.cue
echo     INDEX 01 00:00:00>>%filename%_working.cue
echo.
echo:

echo Extracting files...
..\tools\psximager\psxrip.exe "%filename%_original.cue" %working_name%
echo:

echo Backing up files as the original files...
:: /e - Copies all subdirectories, even if empty. /h - Include hidden and system files. /q - Copy silently
xcopy /e /h /q %working_name% orig
echo:

:: The tool doesn't like it when you specify a name for the catalog, so it defaults
:: to the output directory name. Rename it.
:: echo Fixing catalog image name...
:: ren orig.cat %working_name%.cat
:: ren orig.sys %working_name%.sys
:: echo:

echo Success~!
goto :EXIT

:NOISO
echo To extract your base copy of the game, drop the first bin track here instead of running the bat.
echo Make sure you're not dropping the cue file either!
goto :EXIT

:EXIT
popd
echo Press any key to close this window
pause >nul
exit