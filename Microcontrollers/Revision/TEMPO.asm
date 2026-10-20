LIST      p=16F84            ; Définition de processeur
#include <p16F84.inc>        ; Définitions de variables
__CONFIG   _CP_ON & _WDT_OFF & _PWRTE_ON & _HS_OSC
;;;;;;;;;;;;;;;;;;;;;;;
ORG 0x0005 ;;;;adresse de debut de programme
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;DEFINE;;;;;;;;;;;;;;;;
#DEFINE capteur porta,0  ;;;;
#DEFINE rouge portb,0
#DEFINE orange portb,1
#DEFINE verte portb,2
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;MACROS;;;;;;;;;;;;;;;;
b0  macro
bcf status,rp0
endm ;;;;endmacro
b1 macro
bsf status,rp0
endm			
;;;;;;;ZONE DES DECLARATIONS DES VARIABLES;;;;;;;;;;;;;;
CBLOCK 0x00C   				; début de la zone variables	
	cmpt1 : 1					; compteur de boucles 1
	cmpt2 : 1					; compteur de boucles 2
	cmpt3 : 1					; compteur de boucles 3
	ENDC						; Fin de la zone                     
;;;;;;PROGRAMME PRINCIPAL;;;;;;;;;;;;;;;;
;;;;;CONFIGURATION I/O;;;;;;;;;;;;;;;;;;
b1
bsf trisa,0 ;;;;;;;;;;input
clrf trisb,0  ;;;;;;;;;;output

b0
clrf portb

boucle
btfss capteur
GOTO NUIT;f (capteur=0)
GOTO JOUR;V (capteur=1)

JOUR
BSF rouge ;; 1s
bcf orange
bcf verte
call tempo
call tempo
BcF rouge
bsf orange ;; 0.5s
bcf verte
call tempo
BcF rouge
bcf orange
bsf verte  ;; 1s
call tempo 
call tempo
goto boucle
NUIT
BCF rouge               ;;;;; bsf ORANGE  bcf VERT bcf ROUGE 
bSf orange
bcf verte
Call tempo
BcF rouge
bcf orange
bcf verte
call tempo
goto boucle 
;;;;;;;;;;;;;SOUS-ROUTINE D'ATTENTE 0,5s;;;;;;;;;;;;;;;;;
tempo
	movlw	2					; pour 2 boucles
	movwf	cmpt3				; initialiser compteur3
boucle3
	clrf	cmpt2					; effacer compteur2
boucle2
	clrf	cmpt1					; effacer compteur1
boucle1
	nop							; perdre 1 cycle
	decfsz	cmpt1,f				; décrémenter compteur1
	goto	boucle1					; si pas 0, boucler	
	decfsz	cmpt2,f 				; si 0, décrémenter compteur 2
	goto	boucle2					; si cmpt2 pas 0, recommencer boucle1
	decfsz	cmpt3,f				; si 0, décrémenter compteur 3
	goto	boucle3					; si cmpt3 pas 0, recommencer boucle2
	return						; retour de la sous-routine
;;;;;;;;;;;;;;;;;;;;;FIN SOUS-ROUTINE;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;fin du programme;;;;;;;;;;;;;;;;;;;;;;;;;
end

boucle