// Funciones LCD
// Creadas Por: Rafael Toro Sanchez

// Archivo LCD.h

#ifndef _LCD_H

#define _LCD_H
#include "global.h"
#define LCD_PORT PORTD
#define LCD_DDR DDRD
#define LCD_PIN PIND
#define E  PD1
#define RS  PD0
#define LCD_DDRAM 128
#define LCD_DELAY  asm("nop")

// Funciones

void LcdInit();
void LcdComando8(uint8_t Comando8);
void LcdComando4(uint8_t Comando4);
void LcdDatos4(uint8_t Datos4);
void LcdGotoXY(uint8_t X, uint8_t Y);
void LcdPrintData(prog_char Mensaje[]);
void LcdShowChar(uint8_t caracter);
void LcdShowNum(uint8_t numero);
void LcdMostrarNum8bits(uint8_t num8);
void clc();
void LcdMostrarNum16bits(uint16_t num16);

#endif


