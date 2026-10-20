int NB;
void main() {
//configuration
trisa=0;
trisb.rb0=0;
// configuration des interruptions
intcon.gie=1; // activer l'interruption globale
intcon.t0ie=1;// activer la source sur le timer
option_reg= 0b00000111; // on a chosit le mode timer et on a associé un prédiviseur avec un taux de 256
tmr0=0; // initialisation de registre tmr0
NB=15;
// initialisation
porta=0;
portb.rb0=1;
// traitement
do{
porta=10;
}while(1);
}
void interrupt () {
if ((intcon.t0if)&&(intcon.t0ie))
{NB--;
if (NB==0)
{portb.rb0=~portb.rb0; // inverser l'état de la led
NB=15;
tmr0=0;
}
intcon.t0if=0;// remettre le flag à 0
}
}
