	.data 100
cte: .double 3
n:	 .word 12
a:	 .double 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12
b: 	 .double 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

	.text 0x1000
	; Factor de desenrollado 4
	; r1 = indice
	; r8 = indice loop
	; f0 = 3
	; f2 = a(i)
	; f4 = a(i) + cte
	; f6 = a(i+1)
	; f8 = a(i+1) + cte
	; f10 = a(i+2)
	; f12 = a(i+2) + cte
	; f14 = a(i+3)
	; f16 = a(i+3) + cte
	
ini4:
	ld f0,cte(r0)
	xor r1,r1,r1
	lw r8,n(r0)
loop4:
	ld f2,a(r1)
	ld f6,a+8(r1)
	ld f10,a+16(r1)
	ld f14,a+24(r1)

	addd f4,f0,f2
	addd f8,f0,f6
	addd f12,f0,f10
	addd f16,f0,f14

	sd b(r1),f4
	sd b+8(r1),f8
	sd b+16(r1),f12
	sd b+24(r1),f16

	addi r1,r1,#32
	subi r8,r8,#4

	bnez r8,loop4
	nop

trap #6

; Desenrollado de 4, pero no optimizado: 12 paradas y 64 ciclos