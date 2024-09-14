	.data 100
n:		.word 12
a:		.word 0,1,2,3,4,5,6,7,8,9,10,11,12
nzval:	.space 8
	; n = Variable
	; a = Lista
	; nzval = Valor retornado

	.text 200 
	; r1 = a(i)
	; r2 = indice de a
	; r3 += r1
	; r7 = Contador

	lw r7, n(r0) 	; r7 = 12
	xor r2, r2, r2  ; limpia r2 = 0
	xor r3, r3, r3  ; limpia r3 = 0
	
loop:	
		lw	r1, a(r2) ; r1 = a(i)
		subi r7, r7, 1 ; r7 -= 1
		addi r2, r2, #4
		beqz r1, xxx ; salta si r1 == 0
		nop
		add r3, r3, r1 ; Se suman los valores de a
xxx:
		bnez r7, loop
		nop
		sw nzval(r0), r3
	trap #6