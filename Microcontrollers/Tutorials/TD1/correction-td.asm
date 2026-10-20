;;;;;;;;;;;;;;;;;;;;;;;;;;DEBUT;;;;;;;;;;;;;;;;;;;;;;;;;;;
	LIST      p=16F84            ; Définition de processeur
	#include <p16F84.inc>        ; Définitions de variables

	__CONFIG   _CP_ON & _WDT_OFF & _PWRTE_ON & _HS_OSC


org 0x0005 ; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;declaration des variables
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

CBLOCK 0x0E
Var :1
endC
;;;;;;;;;;;;;;;;;;;;;;;;;;;;questions;;;;;;;;;;;;;;;;;;;;;;;;
movlw 0x05
movwf Var

END