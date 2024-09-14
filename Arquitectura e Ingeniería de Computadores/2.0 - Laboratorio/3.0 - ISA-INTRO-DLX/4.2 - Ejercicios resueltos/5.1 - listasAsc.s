	.data 100
A:		.word 1,2,3,4,5,6,7,8,9,10,11,12
B:		.word 12,11,10,9,8,7,6,5,4,3,2,1
C:		.space 96
N:		.word 12 
	; A = Lista 1
	; B = Lista 2
	; C = 8*12 Lista C reserva
	; N = Elementos lista

	.text 2000 
	; r1 es contador, 
	; r2 es indice, 
	; r3 es elemento de A
	; r4 es elemento de B
	; r31 es N
	
ini: add r1, r0, r0
	 add r2, r0, r0
	 lw r31, N(r0)
bucle:	
		addi r1, r1, #1
		lw r3, A(r2) ; Obtengo el elemento de A
		lw r4, B(r2) ; Obtengo el elemento de B
		add r3, r3, r4 ; Obtengo el elemento de C
		sw C(r2), r3
		addi r2, r2, #4
		sub r3, r1, r31
		bnez r3, bucle
		nop
	trap #6