del exe\SCPS_100.39
copy exe\orig\SCPS_100.39 exe\SCPS_100.39
tools\armips.exe code\linda_vwf.asm
tools\linda_cube_again_font_build.exe font\font.bmp exe\SCPS_100.39

del exe_error.txt
echo trans\0008F380.txt >> exe_error.txt
tools\atlas exe\SCPS_100.39 trans\0008F380.txt >> exe_error.txt
echo trans\00091F6C.txt >> exe_error.txt
tools\atlas exe\SCPS_100.39 trans\00091F6C.txt >> exe_error.txt


del cd\linda.bin
copy cd\orig\linda.bin cd\linda.bin
tools\psx-mode2.exe cd\linda.bin \LINDA\LINDA.MIC LINDA.MIC
tools\psx-mode2.exe cd\linda.bin /SCPS_100.39 exe\SCPS_100.39