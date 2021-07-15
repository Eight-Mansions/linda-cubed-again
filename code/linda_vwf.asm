.psx
.open "exe\SCPS_100.39",0x80010800

min_ascii: equ 0x20
max_ascii: equ 0x80 ; +1 from what our actual table is

;.org 0x80048be4
	;ORI     800c3364 (v0), 00000000 (r0), 0008 (8),
	;ori v0, r0, 0x01
	
.org 0x80048c34
	j load_width
	
.org 0x8004ccd8
	jal do_vwf

.org 0x8004cc60
	; ADDIU   800c2008 (v1), 00000008 (a0), 0008 (8), <- space is hardcoded to 8...
	addiu v1, a0, 4
	
.org 0x80081318 ; Don't be deleting my space!
	nop

.org 0x800B8290	
do_vwf:
	la t1, storeme	; Load up address for width table

	addiu t0, r0, max_ascii
	andi t0, t0, 0x0000FFFF
	sltu t0, a0, t0	; see if were in range of eng table...
	beq zero, t0, not_eng_vwf

	addiu t0, r0, min_ascii
	andi t0, t0, 0x0000FFFF
	sltu t0, a0, t0
	bne zero, t0, not_eng_vwf

	addi t0, a0, -0x20	; Magic #, should be first letter we use...
	andi t0, t0, 0x00FF
	addu t0, t0, t1
	lbu t0, 1(t0)
	b done_vwf
	nop
not_eng_vwf:
	addiu t0, r0, 0x08	; Poor not ascii...
done_vwf:
	j 0x800485a0
	sb t0, 0(t1)
	
load_width:
	la t1, storeme
	nop
	lb t1, 0(t1)
	j 0x80048c3c
	sh t1, 0x0028(sp)
	
storeme:
	.db 0 ; letter width
	
widths:
	.db 0x04 ;space
	.db 0x02 ;!
	.db 0x04 ;"
	.db 0x08 ;#
	.db 0x06 ;$
	.db 0x07 ;%
	.db 0x06 ;&
	.db 0x02 ;'
	.db 0x04 ;(
	.db 0x04 ;)
	.db 0x04 ;*
	.db 0x06 ;+
	.db 0x03 ;,
	.db 0x06 ;-
	.db 0x02 ;.
	.db 0x05 ;/
	.db 0x08 ;0
	.db 0x04 ;1
	.db 0x08 ;2
	.db 0x08 ;3
	.db 0x08 ;4
	.db 0x08 ;5
	.db 0x08 ;6
	.db 0x08 ;7
	.db 0x08 ;8
	.db 0x08 ;9
	.db 0x03 ;:
	.db 0x03 ;;
	.db 0x05 ;<
	.db 0x06 ;=
	.db 0x05 ;>
	.db 0x08 ;?
	.db 0x08 ;@
	.db 0x05 ;A
	.db 0x05 ;B
	.db 0x05 ;C
	.db 0x05 ;D
	.db 0x05 ;E
	.db 0x05 ;F
	.db 0x05 ;G
	.db 0x06 ;H
	.db 0x04 ;I
	.db 0x05 ;J
	.db 0x06 ;K
	.db 0x05 ;L
	.db 0x06 ;M
	.db 0x06 ;N
	.db 0x05 ;O
	.db 0x05 ;P
	.db 0x05 ;Q
	.db 0x05 ;R
	.db 0x05 ;S
	.db 0x06 ;T
	.db 0x06 ;U
	.db 0x06 ;V
	.db 0x06 ;W
	.db 0x06 ;X
	.db 0x06 ;Y
	.db 0x06 ;Z
	.db 0x04 ;[
	.db 0x08 ;\
	.db 0x06 ;]
	.db 0x08 ;^
	.db 0x07 ;_
	.db 0x0C ;`
	.db 0x05 ;a
	.db 0x05 ;b
	.db 0x05 ;c
	.db 0x05 ;d
	.db 0x05 ;e
	.db 0x04 ;f
	.db 0x05 ;g
	.db 0x05 ;h
	.db 0x02 ;i
	.db 0x03 ;j
	.db 0x05 ;k
	.db 0x02 ;l
	.db 0x06 ;m
	.db 0x05 ;n
	.db 0x05 ;o
	.db 0x05 ;p
	.db 0x05 ;q
	.db 0x05 ;r
	.db 0x05 ;s
	.db 0x04 ;t
	.db 0x05 ;u
	.db 0x05 ;v
	.db 0x06 ;w
	.db 0x06 ;x
	.db 0x05 ;y
	.db 0x05 ;z
	.db 0x04 ;{
	.db 0x02 ;|
	.db 0x04 ;}
	.db 0x08 ;~	
.close