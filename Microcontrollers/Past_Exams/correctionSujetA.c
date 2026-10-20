#define C_P porta.b0
#define Fente portb.b0
#define A_M porta.b1
#define LED porta.b2
#define Buzzer porta.b3
#define LED_G porta.b4

unsigned int array_h[5]= {0xEC,0xF2,0x70,0x70,0x7E}; //Hello
unsigned int array_l[5]= {0x0C,0xBC}; // 1d
unsigned int array_s[5]= {0xDA,0xF0,0xEE,0xA0,0xF0}; //start
unsigned int array_f[5]= {0xe2,0x0C,0x6E}; //fin
unsigned char i,gagnant;
unsigned char cpt;

void main()
{
  //config
    trisb = 0x01;
    trisa = 0x01;
  //config interrupt
    INTCON.GIE=1;  // activation interruption globale
    INTCON.INTE=1;   // activation interruption sur RB0
    OPTION_REG = 0x07;   //choix mode timer + prediviseur utilisé est à son max: 256
    tmr0=0;
    cpt =15;        //76; //    cpt=5000000/(256*256*1)

  //init
    gagnant = 0;
    porta = 0x00;
    for(i=0; i<=4; i++)    //afficher HELLO
    {
        PORTB=array_h[i];
        delay_ms(500);
    }

    while(1)
    {
        if (C_P==1) // en cas de presence
        {
            for(i=0; i<=2; i++)   //afficher 1d
            {
                PORTB=array_l[i];
                delay_ms(500);
            }
            INTCON.T0IE = 1;     //activer le timer  pour commencer l attente de 5s

        }
        else
        {
            for(i=0; i<=4; i++)   //hello
            {
                PORTB=array_h[i];
                delay_ms(500);
            }
        }
    }
}
void interrupt(void)
{

    if(INTCON.INTF == 1 && INTCON.INTE == 1)    // si l'interruption est du au appui sur RB0
    {
        INTCON.INTF = 0;  //remettre le flag à zéro
        //if(cpt>0)
        //{
            INTCON.T0IE == 0; //desactiver le timer car il ya appui avant la fin de 5s
            for(i=0; i<=4; i++)  // afficher start
            {
                PORTB=array_s[i];
                delay_ms(500);
            }
            A_M=1;
            LED=1;
            delay_ms(5000);
            LED=0;
            A_M=0;
            gagnant ++;
            if(gagnant == 2)      //20
            {
                gagnant = 0;
                LED_G=1;
                delay_ms(2000);
                LED_G=0;
            }
            /*for(i=0; i<=3; i++)  //afficher Fin
            {
                PORTB=array_f[i];
                delay_ms(500);
            }
            delay_ms(2000); */
            for(i=0; i<=4; i++)
            {
                PORTB=array_h[i];
                delay_ms(500);
            }

        //}
    }
    else if( INTCON.T0IF == 1 && INTCON.T0IE == 1) // si l'interruption est du au passage de la valeur du timer de 255-->0
    {
        INTCON.T0IF = 0; //remettre le flag à zéro
        cpt --;
        if(cpt == 0)   //apres 5s
        {
            Buzzer = 1;
            delay_ms(2000);
            Buzzer = 0;
            INTCON.T0IE=0;  //désactivation de l'interruption du timer
            tmr0=0;
            cpt = 15;    //76
        }
    }
}