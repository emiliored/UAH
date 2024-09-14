	.data 100
n:		.word 6
a:		.word 1,2,3,4,5,6
b:		.word 11,12,13,14,15,16
c:		.space 24

	; a = Lista 1
	; b = Lista 2
	; c = 8*3 Lista C reserva
	; n = Elementos lista

	.text 2000 
	; r1 es contador,
	; r2 es indice, 
	; r3 es elemento de A
	; r4 es elemento de B
	; r6 es indice de c
	
ini: lw r1, n(r0)
	 slli r2, r1, #2 ; Riesgo raw por r1, 1 parada
	 xor r6, r6, r6 ; Establezco el valor de r6 a 0
bucle:	
		lw r3, a-4(r2) 
		lw r4, b-4(r2) 
		add r3, r3, r4 ; Riesgo raw por r4, 1 parada
		addi r6, r6, #4
		sw c-4(r6), r3 ; Riesgo raw por r6, sin parada
		subi r2, r2, #4
		subi r1, r1, #1 
		bnez r1, bucle ; Riesgo raw por r1, 1 parada
		nop
	trap #6
; Calculo ciclos: (3i+1p)+n*(10i+2p)+1i = 71 para n = 6