/*================================================================

Code from:
- Maxime De Cock
- Melvin Campos
- Hubert Van De Walle
- Guillaume Vanden Herrewegen

Used for Thermopic project with 18f458 microship

==================================================================*/

#include <18F458.h>
#device ADC=10

#FUSES NOWDT

#use delay(crystal=20000000)

#use rs232(baud=57600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)

char buffer[1];

long affTemp;
int temperatureAlerte = 25;   // température maximale

#int_rda
void isr(){
   disable_interrupts(INT_RDA);
}


/*
   Cette fonction permet de sortir un nombre sur 4 pins au lieu de 8
*/
void sortie(int nbr){
   switch(nbr){
         case 0 :  output_low(pin_d0);
                   output_low(pin_d1);
                   output_low(pin_d2);
                   output_low(pin_d3);
                   break;
         case 1 :  output_high(pin_d0);
                   output_low(pin_d1);
                   output_low(pin_d2);
                   output_low(pin_d3);
                   break;
         case 2 :  output_low(pin_d0);
                   output_high(pin_d1);
                   output_low(pin_d2);
                   output_low(pin_d3);
                   break;
         case 3 :  output_high(pin_d0);
                   output_high(pin_d1);
                   output_low(pin_d2);
                   output_low(pin_d3);
                   break;
         case 4 :  output_low(pin_d0);
                   output_low(pin_d1);
                   output_high(pin_d2);
                   output_low(pin_d3);
                   break;
         case 5 :  output_high(pin_d0);
                   output_low(pin_d1);
                   output_high(pin_d2);
                   output_low(pin_d3);
                   break;
         case 6 :  output_low(pin_d0);
                   output_high(pin_d1);
                   output_high(pin_d2);
                   output_low(pin_d3);
                   break;
         case 7 :  output_high(pin_d0);
                   output_high(pin_d1);
                   output_high(pin_d2);
                   output_low(pin_d3);
                   break;
         case 8 :  output_low(pin_d0);
                   output_low(pin_d1);
                   output_low(pin_d2);
                   output_high(pin_d3);
                   break;
         case 9 :  output_high(pin_d0);
                   output_low(pin_d1);
                   output_low(pin_d2);
                   output_high(pin_d3);
                   break;
                   
   }
}

/*
   Cette fonction permet d'afficher sur 2 afficheurs 7 segments à cathodes communes un nombre à 2 chiffres décimaux
*/

void affiche(int nbr){
   
   int nbr1 = nbr/10;
   int nbr2 = nbr%10;
   output_high(pin_d4);
   output_low(pin_d5);
   sortie(nbr1);
   delay_ms(10);
   output_high(pin_d5);
   output_low(pin_d4);
   sortie(nbr2);
   delay_ms(10);
   delay_ms(10);



}

void ledRedOn(){
   output_high(pin_d6);
}

void ledRedOff(){
   output_low(pin_d6);
}

void ledGreenOn(){
   output_high(pin_d7);
}

void ledGreenOff(){
   output_low(pin_d7);
}



char treshstr[3];

boolean flag = 0 ;


void verifieTemperature(){
         if(affTemp > temperatureAlerte){
            ledRedOn();
            ledGreenOff(); 
         }
         else{
            ledRedOff();
            ledGreenOn();
         }
}



void main()
{
   unsigned long temp;
   
   
   setup_adc(ADC_CLOCK_DIV_32); //configure analog to digiral converter
   setup_adc_ports(ALL_ANALOG); 
   set_adc_channel(0);
   output_high(pin_e0);
  
   
   int value = 0;
    
    
   
   
   while(TRUE)
   {
      set_adc_channel(0);//set the pic to read from AN0
      delay_us(10);//delay 10 microseconds to allow PIC to switch to analog channel 0
      temp=read_adc()/10; //read input from pin AN0: 0<=photo<=255
      
      
      affTemp = temp;
      
      if(affTemp != value){
         value = affTemp;
         printf("hello world");    
      }
      printf("hello world \r \n"); 

      if(temp>25 && temp<69){
         affTemp = temp - 1;
         affiche(affTemp);
         verifieTemperature();
      }
      else if(temp>69){
         affTemp = temp - 2;
         affiche(affTemp);
         verifieTemperature();
      }
      else{
         affiche(affTemp);
         verifieTemperature();
      }
      delay_ms(10);
   }

}
