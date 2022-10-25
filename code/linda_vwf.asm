.psx
.open "cd\linda\LINDA\SUBTITLES.DAT",0x801D0000
	.importobj "code\linda\obj\subtitle.obj"
	.importobj "code\linda\obj\generated_movie.obj"
SubFont:
	.incbin "font\sub_font.bin" ; Font used for subtitles
.close

.open "exe\SCPS_100.39",0x80010800

.definelabel LoadImage, 0x80062394
.definelabel LoadFile, 0x800203ec
.definelabel GetFileInfo, 0x800205b8

;.org 0x80048be4
	;ORI     800c3364 (v0), 00000000 (r0), 0008 (8),
	;ori v0, r0, 0x01

.org 0x8001677c
	j LoadSubs
	
.org 0x80022af8
	j StoreFrameNumber
	nop
	
.org 0x80048c34
	j GetCurLetWidth
	
.org 0x8004ccd8
	jal GetLetWidth
	
.org 0x8004c9e8
	j GetLetWidthForLargeLetter
	
.org 0x8004c970
	j GetLetWidthForLargeLetterSJIS
	
.org 0x800489d0
	j GetCurWidthForLargeLetter
	nop
	
.org 0x80045418 ; Updates x position for next letter for text
	;80045418 : SUBU    00000014 (v0), 00000014 (v0), 00000000 (a0),
	;8004541c : SW      00000014 (v0), 0028 (801ffef0 (sp)) [801fff18]
;	nop
;	nop

.org 0x8004cc60
	; ADDIU   800c2008 (v1), 00000008 (a0), 0008 (8), <- space is hardcoded to 8...
	addiu v1, a0, 3
	
.org 0x80081318 ; Don't be deleting my space!
	nop

.org 0x800B8290	
.importobj "code\linda\obj\font.obj"
.importobj "code\linda\obj\loadfile.obj"

LoadSubs:
	jal 0x8001bebc
	nop
	jal LoadSubtitles
	la a0, 0x801D0000
	j 0x80016784
	nop
	

GetLetWidth:
	addiu sp, sp, -20
	sw ra, 0(sp)
	sw a0, 4(sp)
	sw a1, 8(sp)
	jal GetLetterWidth
	sw v0, 12(sp)
	
	la t0, curLetWidth
	sb v0, 0(t0)
	
	lw ra, 0(sp)
	lw a0, 4(sp)
	lw a1, 8(sp)
	lw v0, 12(sp)
	j 0x800485a0
	addiu sp, sp, 20
	
GetLetWidthForLargeLetter:
	lhu a0, 0x002c(sp)
	nop
	jal GetLetterWidth
	nop
	
	la t0, curLetWidth
	j 0x8004ca4c
	sb v0, 0(t0)
	
GetLetWidthForLargeLetterSJIS:
	lhu a0, 0x002e(sp)
	nop
	jal GetLetterWidth
	nop
	
	la t0, curLetWidth
	j 0x8004ca4c
	sb v0, 0(t0)
	
GetCurLetWidth:
	la t1, curLetWidth
	lb t1, 0(t1)
	j 0x80048c3c
	sh t1, 0x0028(sp)
	
GetCurWidthForLargeLetter:
	la t1, curLetWidth
	lb t1, 0(t1)
	j 0x800489d8
	sw t1, 0x0028(sp)
	
InitMovieSub:
	addiu sp, sp, -4
	sw a1, 4(sp)
	jal 0x8001417c
	nop
	jal InitMovieSubtitle
	lw a0, 4(sp)
	
	j 0x80023144
	nop
	
StoreFrameNumber:
	;80022af8 : LUI     800c0000 (at), 800c (32780),
	;80022afc : SW      00000021 (v1), 8c34 (800c0000 (at)) [800b8c34]
	la a0, framenum
	lui at, 0x800C
	sw v1, 0x8c34(at)
	j 0x80022b00
	sw v1, 0(a0)

framenum:
	.dw 0
curLetWidth:
	.db 0 ; letter width

.close