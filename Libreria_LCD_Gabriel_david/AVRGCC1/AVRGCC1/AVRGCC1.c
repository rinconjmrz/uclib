/*
 * AVRGCC1.c
 *
 * Created: 26/08/2013 10:33:54 a.m.
 *  Author: admin
 */ 

#include <avr/io.h>

int main(void)
{
	uint8_t var, num;
	
	
    while(1)
    {
		inicializacion();
		var='a';
		escribir_caracter(var);
		escribir_numero(num);
		limpiar_pantalla();
        //TODO:: Please write your application code 
    }
}