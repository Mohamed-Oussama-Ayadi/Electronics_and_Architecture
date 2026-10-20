sbit LCD_RS at RC4_bit;
sbit LCD_EN at RC5_bit;
sbit LCD_D4 at RC0_bit;
sbit LCD_D5 at RC1_bit;
sbit LCD_D6 at RC2_bit;
sbit LCD_D7 at RC3_bit;
sbit LCD_RS_Direction at TRISC4_bit;
sbit LCD_EN_Direction at TRISC5_bit;
sbit LCD_D4_Direction at TRISC0_bit;
sbit LCD_D5_Direction at TRISC1_bit;
sbit LCD_D6_Direction at TRISC2_bit;
sbit LCD_D7_Direction at TRISC3_bit;

float volt,temp,result;
char display[16]="";
void Sens_horaire_motor()
{   PORTD.RD1=1;
    PORTD.RD2=0;
    delay_ms(1000); }
    void Sens_anti_motor()
{   PORTD.RD1=0;
    PORTD.RD2=1;
    delay_ms(1000); }

void Frein_motor()
{    PORTD.RD1=0;
     PORTD.RD2=0; }

void demarrage (){
  PORTD=0x00;
  Lcd_Cmd(_LCD_CLEAR);
  Lcd_Cmd(_LCD_CURSOR_OFF);
  Lcd_Out(1, 1, "Bienvenue");
  //temperature
  result=adc_read(2);
   volt=result*4.88;
   temp=volt/10;
lcd_out(2,1,"Temp = ");
floattostr(temp,display);
lcd_out_cp(display);
lcd_chr(2,14,223);
lcd_out_cp("C");
delay_ms(1000);
}
void interrupt()
{
    if(INTCON.INTF == 1)
    {
    intcon.INTF=0;
    PORTB.RB5=1;  //  Led rouge allumée
    PORTD.RD0=1;  //  buzzer actif
    // PORTD =0b00010001=0x11 = 17
    delay_ms(2000);
    Sens_horaire_motor();   // tourner moteur
    delay_ms(2000);
    Frein_motor();    // arreter moteur
    PORTD.RD0=0;      // arreter buzzer
    PORTB.RB5=0;      // eteindre led rouge
    // PORTD =0b00000000 = 0 = 0x00
    }
    if (INTCON.RBIF==1)
    {  INTCON.RBIF = 0;
       if (PORTB.RB7==1)
       {PORTB.RB6=1; //  Led verte allumée
        PORTD.RD0=1;  //  buzzer actif
        // PORTD =0b00010001=0x11 = 17
        delay_ms(2000);
        Sens_anti_motor();   // tourner moteur
        delay_ms(2000);
        Frein_motor();    // arreter moteur
        PORTD.RD0=0;      // arreter buzzer
        PORTB.RB6=0;  // eteindre led verte
        // PORTD =0b00000000 = 0 = 0x00
       }
    }
 }

void main() {
//conf I/O
  TRISD=0X00;   //  moteur et buzzer
  TRISB.RB0=1;  // capteur de flamme
  TRISB.RB5=0;  // led rouge
  TRISB.RB6=0;  // led verte
  TRISB.RB7=1;  // capteur de gaz
  // TRISB = 0b10000001 = 0x81 = 128
  TRISA.RA2=1; // capteur temperateur
  adcon1=0x80;

//conf interrupt
  INTCON.GIE=1;         //global interruption
  INTCON.INTE=1;        //INTE=RB0
  INTCON.RBIE=1;        //RBIE=PORTB

//init
  Lcd_Init();
  Lcd_Cmd(_LCD_CLEAR);
  demarrage();

  while(1){
   result=adc_read(2);
   volt=result*4.88;
   temp=volt/10;
   if((temp >16 || temp<2)){
    PORTD.RD0=1;  // activer buzzer
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Out(1,1,"Alerte");
    Lcd_Out(2, 1, "Temperature");
    delay_ms(1000);
   }
    else
    demarrage();
  }
}