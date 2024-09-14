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
	
ini: lw r1, N(r0)
bucle:	
		subi r1, r1, #1
		slli r2, r1, #2
		lw r3, A(r2) ; Obtengo el elemento de A
		lw r4, B(r2) ; Obtengo el elemento de B
		add r3, r3, r4 ; Obtengo el elemento de C
		sw C(r2), r3
		bnez r1, bucle
		nop
	trap #6