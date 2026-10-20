
;;;;;;;;;;;;;;;;;;;;;;;;;;DEBUT;;;;;;;;;;;;;;;;;;;;;;;;;;;
	LIST      p=16F84            ; Définition de processeur
	#include <p16F84.inc>        ; Définitions de variables

	__CONFIG   _CP_ON & _WDT_OFF & _PWRTE_ON & _HS_OSC


org 0x0005 ; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;Configuration I/O;;;;;;;;;;;;;;;;;;;;;;;
BSF STATUS,RP0 ; je suis dans le bank1
bsf trisa,3    ; la pin RA3 Configurée comme entrée
clrf trisb ;trisb=0b00000000

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;INITIALISATION UNIQUEMENT LES SORTIES
BCF status,rp0  ; je suis dans le bank0
clrf portb


;;;;;;;;;;;;;;;;;;;;;;;;;;;; PROGRAMME PRINCIPAL;;;;;;;;;;;;;
boucle ; etiquette 
btfss PORTA,3   ; tester et sauter une ligne lorsque (RA3==1)
 GOTO allumer_D1D3 
 GOTO allumer_D2D4

allumer_D1D3 
movlw 5 ;w=5
movlw portb ;portb=5
goto boucle ; aller vers l'étiquette boucle

 
allumer_D2D4
 movlw 0x0A 
movwf portb 
 goto boucle ; aller vers l'étiquette test
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;Fin
END