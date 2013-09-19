/*
* lcd.h
*
*  Author: LUISM
*/


#ifndef LCD_H_
#define LCD_H_

#include <stdio.h>

#include "lcdconfig.h"

/* ---- Macros de propósito general ---- */

#define LCD_CONCAT(a, b)            a ## b

#define LCD_OUTPORT(name)           LCD_CONCAT(PORT, name)
#define LCD_INPORT(name)            LCD_CONCAT(PIN, name)
#define LCD_DDRPORT(name)           LCD_CONCAT(DDR, name)

/* ---- Definición puertos entrada y salida ---- */
#ifndef LCD_DATA_PORTNAME
#error "Se debe definir el macro LCD_DATA_PORTNAME"
#endif

#ifndef LCD_CTRL_PORTNAME
#error "Se debe definir el macro LCD_CTRL_PORTNAME"
#endif

#define LCDDATAOUT          LCD_OUTPORT(LCD_DATA_PORTNAME)
#define LCDDATAIN           LCD_INPORT(LCD_DATA_PORTNAME)
#define LCDDATADDR          LCD_DDRPORT(LCD_DATA_PORTNAME)

#define LCDCTRLOUT          LCD_OUTPORT(LCD_CTRL_PORTNAME)
#define LCDCTRLIN           LCD_INPORT(LCD_CTRL_PORTNAME)
#define LCDCTRLDDR          LCD_DDRPORT(LCD_CTRL_PORTNAME)

/* ------------------------------------ */

#define E  LCD_E
#define RS  LCD_RS

#define sbi(port,bit) port|=(1<<bit)
#define cbi(port,bit) port&=~(1<<bit)

void initLCD(void);
void _command(uint8_t cmd);
void _command8(uint8_t cmd);
void _command4(uint8_t cmd);
void _data(uint8_t data);
void _data4(uint8_t data);
void _data8(uint8_t data);
void setCursor(uint8_t pos);
void clearLCD(void);
int  lcd_putchar(uint8_t c, FILE *stream);

#endif /* LCD_H_ */
