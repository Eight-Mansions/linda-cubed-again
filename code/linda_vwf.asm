.psx
.open "exe\SCPS_100.39",0x80010800

;.org 0x80048be4
	;ORI     800c3364 (v0), 00000000 (r0), 0008 (8),
	;ori v0, r0, 0x01
	
.org 0x80048c34
	j GetCurLetWidth
	
.org 0x8004ccd8
	jal GetLetWidth

.org 0x8004cc60
	; ADDIU   800c2008 (v1), 00000008 (a0), 0008 (8), <- space is hardcoded to 8...
	addiu v1, a0, 4
	
.org 0x80081318 ; Don't be deleting my space!
	nop

.org 0x800B8290	
.importobj "code\linda\obj\font.obj"

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
	
GetCurLetWidth:
	la t1, curLetWidth
	lb t1, 0(t1)
	j 0x80048c3c
	sh t1, 0x0028(sp)

curLetWidth:
	.db 0 ; letter width

.close