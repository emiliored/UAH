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
		ld f0, a(r1)
		ld f2, b(r1)
		
		addd f8, f6, f2 ; RAW 1 parada
		multd f8, f0, f8 ; RAW 1 parada, WAW 2 paradas
		
		sd c(r1), f8 ; RAW 4 paradas, REstructural 1 parada
		
		addi r1, r1, #8 ; REstructural 4 paradas
		
		subi r2, r2, #1 ; REstructural 2 paradas
	
		bnez r2, bucle ; RAW 1 parada
		nop			; REstructural 1 parada
	
	trap #6
	
; Num ciclos = 3c + 5 * (2c + (1cadd + 1p) + (1cmul + 3p) + (1c + 5p) + (1c + 4p) + (1c + 2p)+ (1c + 1p) + (1 HR + 1p) ) + 1c = 134c
; Num ciclos = 83c