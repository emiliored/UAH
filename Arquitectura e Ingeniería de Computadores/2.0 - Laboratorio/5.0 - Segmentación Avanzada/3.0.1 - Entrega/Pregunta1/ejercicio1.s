	.data 0
a: .double 1, 2.0, 3.567, 4.22, 5, 6.78, 7.43, 5.89, 54.34, 78.876, 9.542, 10.44
b: .double 2.7, 3, 4, 1, 5, 56, 33, 69, 5.8, 32.14, 99.76, 69.4
c: .space 8
n: .word 12

	.text 1000
	; r1 = n
	; r2 = indice a y b
	; f0 = a(i)
	; f2 = b(i)
	; f4 = a(i) + b(i)
	; f6 = f6 + f4
	
ini:
	lw r1, n(r0)
	subd f6, f6, f6
	xor r2, r2, r2
loop:	
		ld f0, a(r2) ; 0 paradas RAW
		ld f2, b(r2) ; 0 paradas RAW
		
		multd f4, f0, f2 ; 1 paradas RAW
		
		addd f6, f4, f6 ; 1 paradas RAW
		
		addi r2, r2, #8
		subi r1, r1, #1
		
		bnez r1, loop ; 1 parada RAW
		nop
	
	sd c(r0), f6
	trap #6

; Con 137 ciclos y 36 paradas para n=12