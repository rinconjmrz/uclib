/******************************************************************************
 * FileName:   lcd_4_lines.h
 * Purpose:    Librería de funciones para controlar un display LCD 
 *			   mediante 7 lineas.
 * Processor:  ATmel AVR
 * Compiler:   AVR IAR C y AVR GCC (WinAVR)
 * Author:     Joam Manuel Rincon Zuluaga
 *
 *
 * License:    Se permiten el uso y la redistribución de este código con 
 *             modificaciones o sin ellas, siempre que se mantengan esta 
 *             licencia y las notas de autor y copyright de arriba.
 *****************************************************************************/

//****************************************************************************
//    DECLARACION DE LIBRERIAS
//****************************************************************************
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdio.h>

//****************************************************************************
//    DECLARACION DE DEFINICIONES
//****************************************************************************
/* Se define todo el puerto B para el manejo del LCD */
#define  PORT_LCD	  PORTB   // Salida de datos al LCD
#define  PIN_LCD      PINB    // Entrada de datos al LCD
#define  DDR_LCD	  DDRB    // Configuracion del puerto de la LCD
/* La parte baja del puerto B sera el control de la LCD */
#define  LCD_EN       PINB2   // Pin Enable
#define  LCD_RW       PINB1   // Pin Read/Write
#define  LCD_RS       PINB0   // Pin Register Select
/* Comando usuales */
#define  LCD_CLEAR    0x01    // Limpiar Display
#define  LCD_RETHOM   0x02    // Cursor a inicio de línea 1
#define  LCD_LINE1    0x80    // Línea 1 posición 0
#define  LCD_LINE2    0xC0    // Línea 2 posición 0
#define  LCD_DDRAM    0x80    // Dirección 0x00 de DDRAM
#define  LCD_CGRAM    0x40    // Dirección 0x00 de CGRAM
#define  LCD_CURSOR   0x0E    // Mostrar solo Cursor
#define  LCD_BLINK    0x0D    // Mostrar solo Blink
#define  LCD_CURBLK   0x0F    // Mostrar Cursor + Blink
#define  LCD_NOCURBLK 0x0C    // No mostrar ni Cursor ni Blink
#define  DES_IZQ      0X1C	  // Desplazar hacia la izquierda
#define  DES_DER      0X18	  // Desplazar hacia la derecha
#define  LCD_LINEAS   16      // Para LCD de 2×16


//****************************************************************************
//    PROTOTIPOS DE FUNCIONES
//****************************************************************************
int escribir(char c, FILE * stream);
unsigned char read_data_lcd_7(void);
void send_command_lcd_7(unsigned char, unsigned char);
void init_lcd_7(void);
void send_string_lcd_7(char *);
void send_dir_lcd_7(unsigned char,unsigned char);
void scrolling_text(unsigned char);
