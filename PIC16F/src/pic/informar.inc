;***************************************************************************************;
;											;
;					INFORMAR.inc					;
;											;
;				Librer�a con mensajes de CONFIG.inc			;
;											;
;***************************************************************************************;

Informacion1	ADDWF	PCL,1
		RETLW	'*'
		RETLW	'*'
		RETLW	' '
		RETLW	'C'
		RETLW	'a'
		RETLW	'n'
		RETLW	'c'
		RETLW	'e'
		RETLW	'l'
		RETLW	'a'
		RETLW	'd'
		RETLW	'o'
		RETLW	'r'
		RETLW	'a'
		RETLW	' '
		RETLW	'*'
		RETLW	'*'
		RETLW	' '
		RETLW	'J'
		RETLW	'u'
		RETLW	'a'
		RETLW	'n'
		RETLW	' '
		RETLW	'M'
		RETLW	'.'
		RETLW	' '
		RETLW	'G'
		RETLW	'a'
		RETLW	'g'
		RETLW	'o'
		RETLW	' '
		RETLW	'B'
		RETLW	'e'
		RETLW	'n'
		RETLW	'i'
		RETLW	't'
		RETLW	'e'
		RETLW	'z'
		RETLW	'.'
		RETLW	' '
		RETLW	0		;Marcador de fin de mensaje

Informacion2	ADDWF	PCL,1
		RETLW	'P'
		RETLW	'F'
		RETLW	'C'
		RETLW	' '
		RETLW	'2'
		RETLW	'0'
		RETLW	'0'
		RETLW	'1'
		RETLW	'/'
		RETLW	'2'
		RETLW	'0'
		RETLW	'0'
		RETLW	'2'
		RETLW	'.'
		RETLW	' '
		RETLW	'P'
		RETLW	'u'
		RETLW	'l'
		RETLW	's'
		RETLW	'e'
		RETLW	' '
		RETLW	'O'
		RETLW	'K'
		RETLW	' '
		RETLW	'p'
		RETLW	'a'
		RETLW	'r'
		RETLW	'a'
		RETLW	' '
		RETLW	'v'
		RETLW	'o'
		RETLW	'l'
		RETLW	'v'
		RETLW	'e'
		RETLW	'r'
		RETLW	' '
		RETLW	'.'
		RETLW	'.'
		RETLW	'.'
		RETLW	' '
		RETLW	0		;Marcador de fin de mensaje
