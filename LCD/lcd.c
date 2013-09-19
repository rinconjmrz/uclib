/*
 * lcd.c
 *
 *  Author: LUISM
 */ 

// Librerías AVRLIBC
#include <avr/io.h>
#include <util/delay.h>

// Declaración de funciones y macros
#include "lcd.h"


// Función para la inicialización del LCD
void initLCD()
{
	//Datos
	LCDDATADDR = 0xFF;
	
	//Enable y RS como salida
	LCDCTRLDDR |= (1<<E) |(1<<RS) ;
	
	cbi(LCDCTRLOUT,RS);
	sbi(LCDCTRLOUT,E);
	
	_delay_ms(15);
	_command8(0x30);
	_delay_ms(5);
	_command8(0x30);
	_delay_ms(4);
	_command8(0x30);
	#if LCD_DATA == 4
		_command8(0x20);
	#endif	
	_delay_ms(4);
	
	#if LCD_DATA == 8
		_command8(0x38);
	#elif LCD_DATA == 4
		_command4(0x28);	
	#endif
	_command(0x8);
	_command(0x1);
	_command(0x04);
	
	_delay_ms(4);
	_command(0x0C);
	
	sbi(LCDCTRLOUT,RS);
	cbi(LCDCTRLOUT,E);
	
}

void _command8(uint8_t cmd)
{
	LCDDATAOUT = cmd;

	asm("nop");
	cbi(LCDCTRLOUT,RS);
	asm("nop");
	sbi(LCDCTRLOUT,E);
	asm("nop");
	cbi(LCDCTRLOUT,E);
	asm("nop");
	sbi(LCDCTRLOUT,RS);
	_delay_us(40);
}

void _command4(uint8_t cmd)
{
	LCDDATAOUT = cmd&0xF0;

	asm("nop");
	cbi(LCDCTRLOUT,RS);
	asm("nop");
	sbi(LCDCTRLOUT,E);
	asm("nop");
	cbi(LCDCTRLOUT,E);
	asm("nop");
	sbi(LCDCTRLOUT,RS);
	_delay_us(40);
	
	LCDDATAOUT = cmd<<4;

	asm("nop");
	cbi(LCDCTRLOUT,RS);
	asm("nop");
	sbi(LCDCTRLOUT,E);
	asm("nop");
	cbi(LCDCTRLOUT,E);
	asm("nop");
	sbi(LCDCTRLOUT,RS);
	_delay_us(40);
}	

void _command(uint8_t cmd)
{
	#if LCD_DATA == 8
		_command8(cmd);
	#elif LCD_DATA == 4
		_command4(cmd);
	#else
		#error "El tamaño de datos es incorrecto"
	#endif	
}

void _data(uint8_t data)
{
	#if LCD_DATA == 8
		_data8(data);
	#elif LCD_DATA == 4
		_data4(data);
	#else
		#error "El tamaño de datos es incorrecto"
	#endif
}

void _data8(uint8_t data)
{
	LCDDATAOUT = data;

	asm("nop");
	sbi(LCDCTRLOUT,RS);
	asm("nop");
	sbi(LCDCTRLOUT,E);
	asm("nop");
	cbi(LCDCTRLOUT,E);
	asm("nop");
	cbi(LCDCTRLOUT,RS);
	_delay_us(40);
}

void _data4(uint8_t data)
{
	LCDDATAOUT = data&0xF0;

	asm("nop");
	sbi(LCDCTRLOUT,RS);
	asm("nop");
	sbi(LCDCTRLOUT,E);
	asm("nop");
	cbi(LCDCTRLOUT,E);
	asm("nop");
	cbi(LCDCTRLOUT,RS);
	_delay_us(40);
	
	LCDDATAOUT = data<<4;

	asm("nop");
	sbi(LCDCTRLOUT,RS);
	asm("nop");
	sbi(LCDCTRLOUT,E);
	asm("nop");
	cbi(LCDCTRLOUT,E);
	asm("nop");
	cbi(LCDCTRLOUT,RS);
	_delay_us(40);
}

void setCursor(uint8_t pos)
{
	_command(pos|0x80);
}

void clearLCD(void)
{
	_command(1);
}

int lcd_putchar(uint8_t c, FILE *stream){

	if (c == '\n')
		lcd_putchar('\r', stream);

	_data(c);

	return 0;
}





