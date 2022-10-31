del cd\linda_working.bin
del /s /q cd\linda\*
xcopy /s cd\orig\* cd\linda

del exe\SCPS_100.39
copy exe\orig\SCPS_100.39 exe\SCPS_100.39

tools\linda_generate_movie_subtitles.exe trans\movie_subs tools\movie_mapping.txt

echo Building Linda Cube Again PSX code
pushd code\linda
pmake -e RELMODE=DEBUG clean
mkdir Debug
pmake -e RELMODE=DEBUG -e OUTFILE=main -e OPTIMIZE=2
popd

tools\linda_cube_again_big_font_build.exe exe\orig\SCPS_100.39 exe\SCPS_100.39 font\big_font.bmp font\big_font.tbl
tools\linda_cube_again_font_build.exe font\font.bmp exe\SCPS_100.39

del exe_error.txt
echo trans\0008F380.txt >> exe_error.txt
tools\atlas exe\SCPS_100.39 trans\0008F380.txt >> exe_error.txt
echo trans\00091F6C.txt >> exe_error.txt
tools\atlas exe\SCPS_100.39 trans\00091F6C.txt >> exe_error.txt

copy /y NUL cd\linda\LINDA\SUBTITLES.DAT >NUL
tools\armips.exe code\linda_vwf.asm

del cd\linda\LINDA\LINDA.MIC
copy LINDA.MIC cd\linda\LINDA\LINDA.MIC

del cd\linda\SCPS_100.39
copy exe\SCPS_100.39 cd\linda\SCPS_100.39

::Build files
echo Building final bin file...
pushd cd
del /q linda_working.bin
..\tools\psximager\psxbuild.exe "linda.cat" "linda_working.bin">> build.log
popd
echo:


REM tools\psx-mode2.exe cd\linda_working.bin \LINDA\LINDA.MIC LINDA.MIC
REM tools\psx-mode2.exe cd\linda_working.bin /SCPS_100.39 exe\SCPS_100.39

echo Build complete!
echo: