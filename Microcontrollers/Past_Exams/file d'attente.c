int i,NB;
void main() {
 //config
 TRISA=0;
 TRISB=0b01110001;
 INTCON.GIE=1;
 INTCON.INTE=1;
 OPTION_REG.INTEDG=0;

 //init

 // traite
 while(1){
  PORTB=0;
 PORTA=5;
 delay_ms(1000);
 PORTA=13;
 delay_ms(1000);
 PORTA=3;
 delay_ms(1000);
 }

}
void interrupt(){
 if(INTCON.INTF==1){
   INTCON.INTF=0;
   INTCON.RBIE=1;
   INTCON.T0IE=1;
   TMR0=0;
   NB=228;
   OPTION_REG=0b00000111;
   PORTA=11;
   delay_ms(3000);
 }
 if(INTCON.RBIF==1){
    INTCON.RBIF=0;
    if(PORTB.RB4==1){
     PORTB.RB1=1;
     PORTA=2;
     delay_ms(3000);
    }
    if(PORTB.RB5==1){
     PORTB.RB2=1;
     PORTA=10;
     delay_ms(3000);
    }
    if(PORTB.RB6==1){
     PORTB.RB3=1;
     PORTA=6;
     delay_ms(3000);
    }
 }
 if(INTCON.T0IF==1){
    INTCON.T0IF=0;
    NB--;
    if(NB==0){
      INTCON.T0IE=0;
      INTCON.RBIE=0;
      PORTA=15;
      delay_ms(5000);
    }
 }
}