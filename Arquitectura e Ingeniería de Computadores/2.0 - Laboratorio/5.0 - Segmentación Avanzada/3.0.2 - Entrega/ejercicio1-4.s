	.data 100
n:	 .word 32
pe:	 .space 16
a:	 .double 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32
b: 	 .double 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1
	.text 0x1000
	; Factor de desenrollado 4
	; r1 = indice
	; r2 = indice loop (n)
	; f0 = pe
	; f2 = a(i)
	; f4 = a(i+1)
	; f6 = a(i+2)
	; f8 = a(i+3)
	; f10 = b(i)
	; f12 = b(i+1)
	; f14 = b(i+2)
	; f16 = b(i+3)
ini4:
	xor r1,r1,r1
	lw r2,n(r0)
	subd f0, f0, f0
loop4:
	ld f2,a(r1)
	ld f10,b(r1)
	ld f4,a+8(r1)
	multd f2, f2, f10
	ld f12,b+8(r1)
	ld f6,a+16(r1)
	multd f4, f4, f12
	addd f0, f0, f2
	ld f14,b+16(r1)
	ld f8,a+24(r1)
	multd f6, f6, f14
	addd f0, f0, f4
	ld f16,b+24(r1)
	subi r2, r2, #4
	multd f8, f8, f16
	addd f0, f0, f6
	addi r1,r1,#32
	bnez r2,loop4
	addd f0, f0, f8
	
	sd pe(r0),f0 ;1 parada RAW
trap #6
; Desenrollado de 4 y optimizado: 158 ciclos con 1 parada
; Ciclos = 3i + 8 * (19i) + 1p + 2i = 158 ciclos