	.data 100
A:		.word 1,2,3,4,5,6,7,8,9,10,11,12 
B:		.word 12,11,10,9,8,7,6,5,4,3,2,1
C:		.space 96 
N:		.word 12 
K:		.word 5
	; A = Lista 1
	; B = Lista 2
	; C = 8*12 Lista C reserva
	; N = Elementos lista
	; K = Elemento inicial

	.text 2000 
	; r1 es contador N,
	; r2 es indice,
	; r3 es K, 
	; r4 es elemento de A
	; r5 es elemento de B
	
ini: add r1, r0, r0
	 lw r3, K(r0)
bucle:	
		slli r2, r1, #2
		lw r4, A(r2) ; Obtengo el elemento de A
		lw r5, B(r2) ; Obtengo el elemento de B
		add r5, r3, r5 ; Obtengo el elemento de C
		sw C(r2), r5
		add r3, r3, r4 ; Aumento K
		addi r1, r1, #1
		bnez r1, bucle
		nop
	trap #6