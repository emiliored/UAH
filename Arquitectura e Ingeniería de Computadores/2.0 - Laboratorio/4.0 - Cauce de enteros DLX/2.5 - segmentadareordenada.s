	.data 0
a:	.word 1,2,3,4
b: 	.word 17,18,19,20
c:	.word 0,0,0,0
	.text 100
ini:
	xor r7, r7, r7
	addi r4, r0, b ; que valor hay en r4?
	lw	r2, b(r7)
	lw	r1, 4(r4)
	addi r7, r7, #4
	add r3, r1, r2
	sw 0(r4), r3
	add r3, r1, r7
	subi r2, r7, #4
	sub r4, r4, r3
	bnez r2, ini
	nop
	trap #6