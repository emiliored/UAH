	.data 100
n:		.word 12
	; N = Variable

	.text 200 
	; r7 es el valor de n
	; r7 es el valor de n

	lw r7, n(r0) 	; r7 = 12
	addi r1, r0, n 	; r1 = 100
	sub r2, r2, r2  ; r2 = basura
	
loop:	
		subi r7, r7, 1 	; r7 -= 1
		add r3, r1, r2 	; r3 = basura
		nop
		add r4, r1, r2 	; r4 = r3		
		bnez r7, loop ; no saltara
		nop
		nop
	trap #6