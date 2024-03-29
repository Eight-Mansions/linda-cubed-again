.psx
.open "cd\linda\LINDA\SUBTITLE.DAT",0x801D3800
	.importobj "code\linda\obj\subtitle.obj"
	.importobj "code\linda\obj\generated_movie.obj"
	.importobj "code\linda\obj\generated_audio.obj"
	.importobj "code\linda\obj\text.obj"
SubFont:
	.incbin "font\sub_font.bin" ; Font used for subtitles

.importobj "code\linda\obj\font.obj"

SetBabyLetWidth:
	addiu sp, sp, -8
	sw a0, 0(sp)
	jal SetLetter	
	sw a1, 4(sp)
	
	lw a0, 0(sp)
	lw a1, 4(sp)
	jal Katakana2ARomajii
	addiu sp, sp, 8
	
	j 0x8004CCE0
	nop
	
GetBabyLetWidth:
	addiu sp, sp, -4
	sw ra, 0(sp)
	
	jal GetBabyLetterWidth
	addiu a0, r0, 0x08
	
	lw ra, 0(sp)
	addiu sp, sp, 4
	j 0x80048ae4
	sw v0, 0x0028(sp)
	
GetSpecialSpace:
	addiu sp, sp, -12
	sw ra, 0(sp)
	sw a0, 4(sp)
	sw v0, 8(sp)
	
	jal GetSpaceWidth
	nop
	
	lw a0, 4(sp)
	lw ra, 0(sp)
	
	addu v1, a0, v0
	lw v0, 8(sp)
	
	j 0x8004cc64
	addiu sp, sp, 12
	
SetShopBuyCountLetter:
	jal 0x800485a0
	nop
	
	jal SetLetter
	addiu a0, r0, 0x80
	
	j 0x8004ab48
	nop
	
SetBankingLetter:
	jal 0x800485a0
	nop
	
	jal SetLetter
	addiu a0, r0, 0x80
	
	j 0x8004a9f8
	nop
	
ResetVWFStat:
	jal ResetVWFStatus
	nop
	
	jal 0x800150a0
	nop
	
	j 0x80015390
	nop

SetGenderSymbolLetter:
	addiu sp, sp, -8
	sw a0, 0(sp)
	sw a1, 4(sp)
		
	jal SetLetter
	addiu a0, r0, 0x80
	
	lw a0, 0(sp)
	lw a1, 4(sp)
	jal 0x8004b7cc
	addiu sp, sp, 8
	
	j 0x8004c87c
	nop
.close

.open "exe\SCPS_100.39",0x80010800

;.definelabel LoadImage, 0x8008200c
.definelabel LoadFile, 0x800203ec
.definelabel GetFileInfo, 0x800205b8
.definelabel strncmp, 0x8007d570
.definelabel LoadImage, 0x8008356c
.definelabel CdReadSync, 0x8007db78
.definelabel CdSync, 0x8007ddb8
.definelabel CdControl, 0x8007de28
.definelabel CdRead, 0x8007da98
.definelabel CdIntToPos, 0x8007e254
.definelabel CdPause, 0x8002158c
.definelabel LoadSpriteToVRAM, 0x8006ef14
.definelabel RemoveSprite, 0x8001b108
.definelabel RemoveSprite2, 0x8001aca8
.definelabel DisplaySprite, 0x8006f388
.definelabel HideSprite, 0x8006ce9c
.definelabel PlayVoice, 0x80020d9c
.definelabel DrawLetter, 0x800485a0

; .org 0x800201a4 ; Remove comparing of checksums and alwasy act as if its good
	; j 0x800201f4
	
; .org 0x800201c0 ; Remove comparing of checksums and alwasy act as if its good
	; j 0x800201f4
	
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
	
.org 0x80015388
	j ResetVWFStat
	
.org 0x8004cb68
	jal Katakana2ARomajii
	
.org 0x8004bff0
	j TurnOffKana2Romaji

.org 0x8004c25c
	j TurnOnKana2Romaji
	
.org 0x80048c34
	j SetLetterWidthForSmallLetter
	
.org 0x8004c9e8
	j SetLetterWidthForLargeLetter
	
.org 0x8004c970
	j SetLetterWidthForLargeLetter
	
.org 0x800489d0
	j GetLetterWidthForLargeLetter
	ori a0, r0, 0x0e
	
.org 0x8004ccd8 ; Run code to get baby letter width
	j SetBabyLetWidth
	nop
	
.org 0x8004ab40
	j SetShopBuyCountLetter
	
.org 0x8004a9f0
	j SetBankingLetter
	
.org 0x8004c874
	j SetGenderSymbolLetter
	
.org 0x80048adc	; Get current baby letter width
	j GetBabyLetWidth
	nop

.org 0x8004cc5c	; Update harcoded space to either 8 or 4 (if vwf on)
	j GetSpecialSpace
	nop
	
.org 0x8003a004
	;sll    $v1(00000003), $a0(00000003), 0x02
	sll v1, a0, 0x3 ; Up season word length to a max of 12
	
.org 0x80038e44
	;move   $v1(ffffffff), 0x0062
	addiu v1, 0x75 ; This pushes out the stats on the main stat screen
	
.org 0x80042bcc
	jal ConvertToLower
	
.org 0x80081318 ; Don't be deleting my space!
	nop
	
.org 0x80048ca0 ; Override text wrapping check since its useless
	j 0x80048cb8
	
; Testing for loading live audio subs
; 8006b2b0 00402021: move   $a0(000066ea), $v0(800d0b4c)
; 8006b2b4 00602821: move   $a1(0000000d), $v1(800ee59e)
; 8006b2b8 0c00f6f9: jal    0x8003dbe4

;.org 0x800214c8
;	j LoadAudioSubsTest

.org 0x8002e884
	j CanLoadAudioSub

.org 0x8001693c
	j DrawAudioSub

.org 0x8002107c
	jal InitAudioSubtitle
	
.org 0x8002158c
	j ResetAudioSub


.org 0x800B8290	
.importobj "code\linda\obj\loadfile.obj"
CanLoadAudioSub:
	jal CanLoadAudioSubtitle
	lw     a0, 0x003c(sp)
	
	lui a0, 0x8001
	jal    0x800205b8
	addiu a0, 0x12e0
	
	j 0x8002e88c
	nop
	


DrawAudioSub:
	jal 0x8001f7c4
	nop

	jal DrawAudioSubtitle
	nop
	
	j 0x80016944
	nop

LoadSubs:
	jal 0x8001bebc
	nop
	jal LoadSubtitles
	la a0, 0x801D0000
	j 0x80016784
	nop
	
ResetAudioSub:
	jal 0x8007de28
	nop
	jal ResetAudioSubtitle
	nop
	j 0x80021594
	nop
	
SetLetterWidthForLargeLetter:
	jal SetLetter
	lhu a0, 0x002c(sp)
	
	j 0x8004ca4c
	nop
	
SetLetterWidthForSmallLetter:
	lw a0, 0x0028(sp)
	addiu sp, sp, -8
	sw ra, 0(sp)
	sw a0, 4(sp)
	
	jal GetRegularLetterWidth
	addiu a0, r0, 0x08
	
	lw ra, 0(sp)
	lw a0, 4(sp)
	addiu sp, sp, 8
	j 0x80048c3c
	sh v0, 0x0028(sp)
	
GetLetterWidthForLargeLetter:
	addiu sp, sp, -8
	sw ra, 0(sp)
	sw a0, 4(sp)
	
	jal GetRegularLetterWidth
	addiu a0, r0, 0xC
	
	lw ra, 0(sp)
	lw a0, 4(sp)
	addiu sp, sp, 8
	j 0x800489d8
	sh v0, 0x0028(sp)
	
TurnOffKana2Romaji:
	jal TurnOffKatakana2Romaji
	nop
	jal 0x80048cdc
	nop
	j 0x8004bff8
	nop

TurnOnKana2Romaji:
	jal TurnOnKatakana2Romaji
	nop
	j 0x8004c8a0
	nop

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