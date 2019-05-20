#include <18F458.h>
#device ADC=10

#FUSES NOWDT                    /*No Watch Dog Timer*/

#use delay(crystal=20000000)

#define LED PIN_D4
#define DELAY 1000

