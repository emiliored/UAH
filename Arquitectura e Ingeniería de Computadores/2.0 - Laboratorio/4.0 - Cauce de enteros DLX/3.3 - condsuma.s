	.data 100
A: .word 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
B: .word 2,3,4,5,6,7,8,9,10,11,12,13,14,15,16
D: .word 0, 5, 0, 0, 6, 5, 9, 0, 0, 0, 2, 0, 3, 44, 87 
C: .word 4,5,6,7,8,9,10,11,12,13,14,15,16,17,18
S: .space 60
N: .word 15

	.text 2000 
	; Algoritmo suma con condicion
	; Si D(i)=0 entonces S(i) = A(i)+C(i) y si D(i)!=0 entonces S(i)=A(i)+B(i)

	lw r9, N(r0) ; 
	xor r7, r7, r7  ;
	
loop:	
		lw	r1, A(r7) ; Condicion RAW, 0 parada
		lw	r2, B(r7) ;
		lw	r5, D(r7) ;
		bnez r5, contin; salta si r5 != 0, Condicion RAW, 2 parada
		nop
		lw	r2, C(r7) ;
		
contin:
		add r3, r2, r1 ; Condicion RAW, 1 parada
		sw  S(r7), r3 ; Condicion RAW, 0 paradas
		addi r7, r7, #4 ; Condicion RAW, sin parada
		subi r9, r9, #1 ; 
		bnez r9, loop ; salta si r9 != 0, Condicion RAW, 1 parada
		nop
	trap #6