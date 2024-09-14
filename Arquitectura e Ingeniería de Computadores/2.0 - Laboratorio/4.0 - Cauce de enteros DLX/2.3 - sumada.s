	.data 100
a:		.word 4
b:		.word 5
c:		.word 6
result:		.space 4

	.text 200 
	; cargar las primeras variables
	lw r1, a(r0)
	lw r2, b(r0)
	add r1, r1, r2
	lw r3, c(r0)
	add r1, r1, r3
	sw result(r0), r1
	trap #6