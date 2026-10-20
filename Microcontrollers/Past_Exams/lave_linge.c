#define verte PORTB.RB1
#define rouge PORTB.RB2
#define bleue PORTB.RB6
#define sechant PORTB.RB0
#define lavage PORTB.RB4
#define clean PORTB.RB5
void main() {
 //config
 TRISA=0b00010000;
 TRISB=0b00110001;
 INTCON.GIE=1;
 INTCON.RBIE=1;
 INTCON.INTE=1;
 OPTION_REG.INTEDG=0;
 
 //init
  verte=1;
  rouge=0;
  bleue=0;
  PORTA=10;
  
  //trait
  while(1){
  }
}

void interrupt(){
   if(INTCON.INTF==1){
      INTCON.INTF=0;
      rouge=1;
      verte=0;
      PORTA=5;
      delay_ms(1000);
      PORTA=10;
      rouge=0;
      verte=1;
   }
   if(INTCON.RBIF==1){
       INTCON.RBIF=0;
       if(lavage==1){
        PORTA=11;
        INTCON.T0IE=1;
        OPTION_REG.T0CS=1;
        OPTION_REG.T0SE=0;
        TMR0=254;
        INTCON.INTE=0;
        INTCON.RBIE=0;
       }
       if(clean==1){
         PORTA=12;
         bleue=1;
		 verte=0;
         delay_ms(200);
         PORTA=10;
         bleue=0;
         verte=1;
       }
   }
   if(INTCON.T0IF==1){
       INTCON.T0IF=0;
       PORTA=13;
       delay_ms(500);
       INTCON.T0IE=0;
       INTCON.INTE=1;
       INTCON.RBIE=1;
       PORTA=10;
       rouge=0;
       bleue=0;
       verte=1;
   }
}