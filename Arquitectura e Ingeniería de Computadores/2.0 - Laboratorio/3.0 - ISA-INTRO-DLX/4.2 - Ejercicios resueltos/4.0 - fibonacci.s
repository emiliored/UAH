	.data 100
nterm:		.word 8
fibo:		.space 32

	.text 2000
ini: add r1, r0, r0
	 addi r2, r0, #1
	 addi r3, r0, #1
	 lw r4, nterm(r0)
	 xor r5, r5, r5
bucle:	add r3, r1, r2
		sw fibo(r5), r3
		add r1, r2, r0
		add r2, r3, r0
		addi r5, r5, #4
		subi r4, r4, #1
		bnez r4, bucle
		nop
	trap #6