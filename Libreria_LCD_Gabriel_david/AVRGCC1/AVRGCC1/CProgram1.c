/*
 * CProgram1.c
 *
 * Created: 26/08/2013 11:03:06 a.m.
 *  Author: admin
 */ 

# include "libreria1.h"
# include <avr/io.h>
# include <util/delay.h>

void inicializacion ()
{
	DDRC=0xFF;
	DDRD=0x03;
	
	_delay_ms(20);
	
	PORTC=0x30;
	PORTD=1;
	PORTD=0;
	_delay_ms(6);
	
	PORTC=0x30;
	PORTD=1;
	PORTD=0;
	_delay_ms(1);
	
	PORTC=0x30;
	PORTD=1;
	PORTD=0;
	_delay_ms(4);
	
	PORTC=0x30;
	PORTD=1;
	PORTD=0;
	_delay_ms(4);
	
	PORTC=0x08;
	PORTD=1;
	PORTD=0;
	_delay_ms(4);
	
	PORTC=0x01;
	PORTD=1;
	PORTD=0;
	_delay_ms(4);
	
	PORTC=0x06;
	PORTD=1;
	PORTD=0;
	_delay_ms(4);
	
	PORTC=0x0C;
	PORTD=1;
	PORTD=0;
	_delay_ms(4);
}

void escribir_caracter(char caracter)
{
	PORTC=caracter;
	PORTD=3;
	PORTD=2;
	PORTD=0;
	_delay_ms(4);
}	

void limpiar_pantalla()
{
	PORTC=1;
	PORTD=1;
	PORTD=0;
	_delay_ms(4);
}	

void escribir_numero(char numero)
{	
	
	PORTC=numero+48;
	PORTD=3;
	PORTD=2;
	PORTD=0;
	_delay_ms(4);
		
}

