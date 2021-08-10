/*
 * Intersection_Traffic_Light.c
 *
 * Created: 8/9/2021 12:07:51 AM
 * Author : Andi
 */ 

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 1600000UL;

#define LED_RG_delay 100000			
#define LED_Yellow_delay 20000			

#define Reboot_delay 50000				

typedef struct 
{
	unsigned LED_Red;					//LED_Red pin
	unsigned LED_Yellow;				//LED_Yellow pin
	unsigned LED_Green;					//LED_Green pin
} Traffic_Light_st;

int main(void)
{
    Traffic_Light_st Traffic_Light_1;
	Traffic_Light_st Traffic_Light_2;
	
	DDRD = 0B11111100;					//Sets pins 2 - 7 to output
	
	Traffic_Light_1.LED_Red			=		PIND2;
	Traffic_Light_1.LED_Yellow		=		PIND3;
	Traffic_Light_1.LED_Green		=		PIND4;
	
	Traffic_Light_2.LED_Red			=		PIND5;
	Traffic_Light_2.LED_Yellow		=		PIND6;
	Traffic_Light_2.LED_Green		=		PIND7;
	
	unsigned short rebooted = 1;
	
	DDRD |= 1 << PIND2;
	
    while (1) 
    {
		if (rebooted == 1) 
		{
			_delay_ms(Reboot_delay);
			rebooted = 0;
		}
		
		PORTD |= 1 << Traffic_Light_1.LED_Green;
		PORTD |= 1 << Traffic_Light_2.LED_Red;
		_delay_ms(LED_RG_delay);
		PORTD &= ~(1 << Traffic_Light_1.LED_Green);
		PORTD &= ~(1 << Traffic_Light_2.LED_Red);
		
		PORTD |= 1 << Traffic_Light_1.LED_Yellow;
		PORTD |= 1 << Traffic_Light_2.LED_Yellow;
		_delay_ms(LED_Yellow_delay);
		PORTD &= ~(1 << Traffic_Light_1.LED_Yellow);
		PORTD &= ~(1 << Traffic_Light_2.LED_Yellow);
		
		PORTD |= 1 << Traffic_Light_1.LED_Red;
		PORTD |= 1 << Traffic_Light_2.LED_Green;
		_delay_ms(LED_RG_delay);
		PORTD &= ~(1 << Traffic_Light_1.LED_Red);
		PORTD &= ~(1 << Traffic_Light_2.LED_Green);
		
		PORTD |= 1 << Traffic_Light_1.LED_Yellow;
		PORTD |= 1 << Traffic_Light_2.LED_Yellow;
		_delay_ms(LED_Yellow_delay);
		PORTD &= ~(1 << Traffic_Light_1.LED_Yellow);
		PORTD &= ~(1 << Traffic_Light_2.LED_Yellow);
    }
	
	return 0;
	
}

