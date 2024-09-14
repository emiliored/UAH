	.data 64
a: .double 165.8585849383, 45.67, 52.78, 99.0008, 85.2222224
b: .double 168.2324094432, 98.67, 67.34, 85.45, 55.3457886
K: .double 65.98
c: .space 45

	.text 2000
	; r1 = indice
	; r2 = cantidad
	
	; f0 = a(i)
	; f2 = b(i)
	; f6 = K
	; f8 = a(i) por K+b(i)
	; Algoritmo: c(i) = a(i) por K + b(i)
	
ini:
	xor r1, r1, r1
	addi r2, r0, #5 ; len(a)
	ld f6, K(r0)
bucle:	
		ld f2, b(r1)
		ld f0, a(r1)
		
		addd f8, f6, f2
		
		multd f8, f0, f8 ; WAW 2 paradas
		subi r2, r2, #1 ; REstructural 1 parada
		sd c(r1), f8 ; REstructural 1 parada, RAW 2 paradas
		
		bnez r2, bucle ; REstructural 3 paradas
		addi r1, r1, #8 ; REstructural 2 paradas
	
	trap #6
	
; Num ciclos = 63c
; Ganancia = 83/63 = 32%