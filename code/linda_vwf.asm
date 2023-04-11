.psx
.open "cd\linda\LINDA\SUBTITLES.DAT",0x801D0000
	.importobj "code\linda\obj\subtitle.obj"
	.importobj "code\linda\obj\generated_movie.obj"
SubFont:
	.incbin "font\sub_font.bin" ; Font used for subtitles
.close

.open "exe\SCPS_100.39",0x80010800

.definelabel LoadImage, 0x8008200c
.definelabel LoadFile, 0x800203ec
.definelabel GetFileInfo, 0x800205b8
.definelabel strncmp, 0x8007d570

;.org 0x80048be4
	;ORI     800c3364 (v0), 00000000 (r0), 0008 (8),
	;ori v0, r0, 0x01
	
;.org 0x800640b8 ; This modifies the sentence length to display up top
;	;addiu  $v1(800c2050), $a0(0000002c), 0x0010
;	addiu v1, a0, 0x1C

.org 0x80045468
	;andi   $v1(00cc1824), $v0(000000cc), 0x000f
	;addu v1, r0, r0
	xor v1, v1

.org 0x8001677c
	j LoadSubs
	
.org 0x8002313c
	j InitMovieSub
	
.org 0x80022af8
	j StoreFrameNumber
	nop
	
.org 0x8002279c
	j DisplayMovieSubs
	
.org 0x80048c34
	j SetLetterWidthForSmallLetter
	
.org 0x8004ccd8
	jal GetLetWidth
	
.org 0x8004c9e8
	j SetLetterWidthForLargeLetter
	
.org 0x8004c970
	j SetLetterWidthForLargeLetter
	
.org 0x800489d0
	j GetLetterWidthForLargeLetter
	ori a0, r0, 0x0e

.org 0x8004cc60	; Update hardcoded space width to 0x03
	;addiu  $v1(800c2008), $a0(00000086), 0x0008
	addiu v1, a0, 0x04
	
.org 0x8003a004
	;sll    $v1(00000003), $a0(00000003), 0x02
	sll v1, a0, 0x3 ; Up season word length to a max of 12
	
.org 0x80042bcc
	jal ConvertToLower

;.org 0x8004cc60
	; ADDIU   800c2008 (v1), 00000008 (a0), 0008 (8), <- space is hardcoded to 8...
	addiu v1, a0, 3
	
.org 0x80081318 ; Don't be deleting my space!
	nop
	

.org 0x80048ca0 ; Override text wrapping check since its useless
	j 0x80048cb8

.org 0x800B8290	
.importobj "code\linda\obj\font.obj"
.importobj "code\linda\obj\loadfile.obj"
.importobj "code\linda\obj\text.obj"

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
	jal SetLetterWidthNew
	sw v0, 12(sp)
	
	lw ra, 0(sp)
	lw a0, 4(sp)
	lw a1, 8(sp)
	lw v0, 12(sp)
	j 0x800485a0
	addiu sp, sp, 20
	
SetLetterWidthForLargeLetter:
	jal SetLetterWidthNew
	lhu a0, 0x002c(sp)
	j 0x8004ca4c
	nop
	
SetLetterWidthForSmallLetter:
	lw a0, 0x0028(sp)
	addiu sp, sp, -4
	sw ra, 0(sp)
	
	jal GetLetterWidthNew
	nop
	
	lw ra, 0(sp)
	addiu sp, sp, 4
	j 0x80048c3c
	sh v0, 0x0028(sp)
	
GetLetterWidthForLargeLetter:
	addiu sp, sp, -4
	sw ra, 0(sp)
	
	jal GetLetterWidthNew
	nop
	
	lw ra, 0(sp)
	addiu sp, sp, 4
	j 0x800489d8
	sh v0, 0x0028(sp)
	
InitMovieSub:
	addiu sp, sp, -4
	sw a0, 0(sp)
	jal 0x8001417c
	nop
	jal InitMovieSubtitle
	lw a0, 0(sp)
	
	j 0x80023144
	addiu sp, sp, 4
	
StoreFrameNumber:
	;80022af8 : LUI     800c0000 (at), 800c (32780),
	;80022afc : SW      00000021 (v1), 8c34 (800c0000 (at)) [800b8c34]
	la a0, framenum
	lui at, 0x800C
	sw v1, 0x8c34(at)
	j 0x80022b00
	sw v1, 0(a0)
	
DisplayMovieSubs:
	la a2, SubFont
	la a3, framenum
	jal DrawMovieSubtitle
	lw a3, 0(a3)
	
	j 0x800227a4
	nop

framenum:
	.dw 0
curLetWidth:
	.db 0 ; letter width

.close