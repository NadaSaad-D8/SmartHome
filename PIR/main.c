#include"micro_config.h"

int main(void)
{
	  DDRD = DDRD | (1<<PD6); //configure pin 6 in PORTD as output pin
    PORTD &= (~(1<<PD6)); // LED OFF
    
    DDRC = DDRC & ~((1<<PC0)); //set PA0 as input
    PORTC |= ((1<<PC0)); // activate pull down resistor

   while(1)
    {
    
        if( PINC & (1<<PC0) )
        {
          PORTD = PORTD | (1<<PD6); 
        } 
	   else {	 PORTD = PORTD & (~(1<<PD6));}
        
    }
}



