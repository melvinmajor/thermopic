#include <testCodeC.h>

/*
   Cette fonction permet d'afficher sur 2 afficheurs 7 segments à cathodes communes un nombre à 2 chiffres décimaux
*/
int temp;
void affiche(int nbr){
   
   int nbr1 = nbr/10;
   int nbr2 = nbr%10;
   output_high(pin_b6);
   output_low(pin_b7);
   output_d(nbr1);
   delay_ms(10);
   output_high(pin_b7);
   output_low(pin_b6);
   output_d(nbr2);
   delay_ms(10);

}

void main()
{
   setup_adc(ADC_CLOCK_DIV_32); //configure analog to digiral converter
   setup_adc_ports(ALL_ANALOG); 
   set_adc_channel(0);
   output_high(pin_e0);
   while(TRUE)
   {
      set_adc_channel(0);//set the pic to read from AN0
      delay_us(10);//delay 20 microseconds to allow PIC to switch to analog channel 0
      temp=read_adc(); //read input from pin AN0: 0<=photo<=255
      output_d(5);
      output_high(pin_b7);
      affiche(temp/2.57);
      delay_ms(10);
   }

}
