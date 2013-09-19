/*
 * prueba.c
 *
 *  Author: LUISM
 */ 


#include <avr/io.h>
#include <util/delay.h>

#include "lcd.h"

FILE mystream = FDEV_SETUP_STREAM(lcd_putchar, NULL,_FDEV_SETUP_WRITE);

int main(void)
{
	uint8_t a = 250;
	
	initLCD();
	
	stdout = &mystream;
		
    while(1)
    {
		setCursor(0);
		printf("Numero: %d\n", a);   
		_delay_ms(100);
		a++;
    }
}