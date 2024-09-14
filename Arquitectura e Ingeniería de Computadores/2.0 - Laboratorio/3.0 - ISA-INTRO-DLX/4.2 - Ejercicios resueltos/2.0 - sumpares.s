	.data 100
n:		.word 9
suma:	.space 4

	.text 1000
ini: lw	r7,n(r0)	; esto es UN COMENTARIO R7<-- M(r0+n) = M(0+100)=10 r7 tendra un 10
	 xor r1, r1, r1
	 slli r7, r7, #1
loop:	add r1, r1, r7
		subi r7, r7, #2
		bnez r7, loop
		nop
		sw	suma(r0),r1
	trap #6