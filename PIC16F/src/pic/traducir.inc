;***************************************************************************************;
;											;
;					TRADUCIR.inc					;
;											;
;	Modifica la variable global Contador1						;
;											;
;***************************************************************************************;

;**************************** Subrutina Bin8BCD **************************
;
;   Convierte un n�mero binario de 8 bits almacenado en el registro W 
; en un n�mero BCD de 2 d�gitos.
;
;   El d�gito menos significativo es devuelto en la localizai�n Unidades y
; el m�s significativo en la localizaci�nn Decenas. 
;
;	movlw   63              ; W reg = 63 Hex
;	call    Bin8BCD         ; tras la conversi�n, 	Decenas  = 9
;							Unidades = 9
;*************************************************************************

Bin8BCD 	movwf   Unidades
		clrf    Decenas
gtenth  	movlw   0x0A
		subwf   Unidades,0
		BTFSS   STATUS,C
		goto    over
		movwf   Unidades
		incf    Decenas, 1
		goto    gtenth
over    	return

;**************************** Subrutina BCDBin8 **************************
;
;   Convierte un n�mero BCD de 2 d�gitos en un n�mero binario de 8 bits 
; almacen�ndolo en el registro W.
;
;   El d�gito menos significativo se pasa a trav�s de la localizai�n 
; Unidades y el m�s significativo a trav�s de la localizaci�nn Decenas. 
;
;	movlw   0x09
;	movwf 	Decenas         ; Decenas  = 9
;	movwf	Unidades	; Unidades = 9
;	call    BCDBin8         ; tras la conversi�n W  = 63 Hex
;						
;*************************************************************************

Decenasx10	MOVLW	0x09
		MOVWF	temp
		MOVF	Decenas,0
Loop10		ADDWF	Decenas,0
		DECFSZ	temp,1
		GOTO 	Loop10
		RETURN

BCDBin8		call	Decenasx10
		movf	Unidades,0
		addwf	Decenas, 0	
		return

;************************* Subrutina Bin16BCD ****************************
;
;   Convierte un n�mero binario de 16 bit en un n�mero BCD de 5 d�gitos.
;
;   El n�mero  binario de 16 bit se pasa a trav�s de las variables H_byte
; y L_byte con el byte alto en H_byte.
;   El n�mero BCD de 5 d�gitos es devuelto en R0, R1 y R2. Las decenas de
; millar (MSD) est�n en el nibble de la dcha de R0.
;
;	movlw   0FF
;	movwf   H_byte
;	movwf   L_byte          ; n�mero  binario de 16 bit = FFFF
;	call    Bin16BCD        ; Tras la conversion R0,R1,R2 = 06,55,35
;
;*************************************************************************

Bin16BCD 	bcf     STATUS,0                ; clear the carry bit
		movlw   .16
		movwf   Contador1
		clrf    R0
		clrf    R1
		clrf    R2
loop16  	rlf     L_byte, 1
		rlf     H_byte, 1
		rlf     R2, F
		rlf     R1, F
		rlf     R0, F

		decfsz  Contador1, 1
		goto    adjDEC
		RETLW   0

adjDEC  	movlw   R2
		movwf   FSR
		call    adjBCD

		movlw   R1
		movwf   FSR
		call    adjBCD

		movlw   R0
		movwf   FSR
		call    adjBCD

		goto    loop16

adjBCD  	movlw   3
		addwf   0,0
		movwf   temp
		btfsc   temp,3          ; test if result > 7
		movwf   0
		movlw   30
		addwf   0,0
		movwf   temp
		btfsc   temp,7          ; test if result > 7
		movwf   0               ; save as MSD
		return

;************************** Subrutina BCDBin16 ***************************
;
;  Convierte un n�mero BCD de 5 d�gitos en un n�mero binario de 16 bit.
;
;  Se supone que la entrada de 5 d�gitos BCD est� en las variables R0, R1
; y R2. Las decenas de millar (MSD) est�n en el nibble de la dcha de R0.
;  El n�mero binario de 16 bit es puesto en los registros H_byte & L_byte
; (byte alto y byte bajo repectivamente ).
;
;	movlw   06
;	movwf   R0      	; R0 = 06
;	movlw   55
;	movwf   R1      	; R1 = 55
;	movlw   35
;	movwf   R2      	; R2 = 35
;	call    BCDBin16  ; Tras la conversion H_Byte = FF & L_Byte = FF
;
;*************************************************************************

mpy10b  	andlw   0F
		addwf   L_byte, 1
		btfsc   STATUS,C
		incf    H_byte, 1
mpy10a  	bcf     STATUS,C        ; multiply by 2
		rlf     L_byte,0
		movwf   L_temp
		rlf     H_byte,0        ; (H_temp,L_temp) = 2*N
		movwf   H_temp

		bcf     STATUS,C        ; multiply by 2
		rlf     L_byte, 1
		rlf     H_byte, 1
		bcf     STATUS,C        ; multiply by 2
		rlf     L_byte, 1
		rlf     H_byte, 1
		bcf     STATUS,C        ; multiply by 2
		rlf     L_byte, 1
		rlf     H_byte, 1       ; (H_byte,L_byte) = 8*N

		movf    L_temp,0
		addwf   L_byte, 1
		btfsc   STATUS,C
		incf    H_byte, 1
		movf    H_temp,0
		addwf   H_byte, 1
		return	               ; (H_byte,L_byte) = 10*N

BCDBin16	clrf    H_byte
		movf    R0,0
		andlw   0F
		movwf   L_byte
		call    mpy10a          ; result = 10a+b

		swapf   R1,0
		call    mpy10b          ; result = 10[10a+b]

		movf    R1,0
		call    mpy10b          ; result = 10[10[10a+b]+c]

		swapf   R2,0
		call    mpy10b          ; result = 10[10[10[10a+b]+c]+d]

		movf    R2,0
		andlw   0F
		addwf   L_byte, 1
		btfsc   STATUS,C
		incf    H_byte, 1       ; result = 10[10[10[10a+b]+c]+d]+e
		return              	; BCD to binary conversion done

