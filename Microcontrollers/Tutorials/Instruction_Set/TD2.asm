;;;;;;;;;;;;;;Debut;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
LIST p=16F84           ;;;;;;definition de processeur
#include <p16F84.inc> ;;;;;;;definition des variables
__CONFIG   _CP_ON & _WDT_OFF & _PWRTE_ON & _HS_OSC
org 0x005
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;  
#DEFINE rouge porta,3            
      #DEFINE blue porta,2
#DEFINE vert portb,0
BSF status,rp0
bsf trisa,0
bsf trisa,1
bcf trisa,2
bcf trisa,3
clrf trisb

bcf status,rp0
bcf blue
bcf rouge
clrf portb 

boucle
movlw 0x03;w=3
andwf porta,w;w=porta&&3
sublw 2;w=2-w

test btfss status,z
goto inegalite
goto egalite

inegalite btfss status,c
goto inf
goto sup

inf
bsf rouge
bcf blue
bcf vert
movlw 0x0C
movwf portb
goto boucle

sup
bsf blue
bcf rouge
bcf vert
movlw 0xDA
movwf portb
goto boucle

egalite
bsf vert
bcf blue
bcf rouge
movlw 0xF3
movwf portb
goto boucle
END