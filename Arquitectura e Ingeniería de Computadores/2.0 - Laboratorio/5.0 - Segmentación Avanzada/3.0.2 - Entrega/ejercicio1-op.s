	.data 100
n:	 .word 32
pe:	 .space 16
a:	 .double 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32
b: 	 .double 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1

	.text 0x1000
	; r1 = indice
	; r2 = indice loop (n)
	; f0 = pe
	; f2 = a(i)
	; f10 = b(i)
	
ini1:
	xor r1,r1,r1
	lw r2,n(r0)
	subd f0, f0, f0
loop1:
	ld f2,a(r1)
	ld f10,b(r1)
	
	subi r2, r2, #1

	multd f2, f2, f10
	addi r1, r1, #8
	
	bnez r2,loop1
	addd f0, f0, f2 ; 1 parada RAW
	
	sd pe(r0),f0
trap #6
; Desenrollado de 1 y optimizado: 230 ciclos con 1 parada