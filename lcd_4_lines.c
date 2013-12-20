/******************************************************************************
 * FileName:   lcd_7_lines.c
 * Purpose:    Librería de funciones para controlar un display LCD 
 *			   mediante 7 lineas.
 * Processor:  ATmel AVR
 * Compiler:   AVR IAR C y AVR GCC (WinAVR)
 * Author:     Joam Manuel Rincon Zuluagaom.
 *
 *
 * License:    Se permiten el uso y la redistribución de este código con 
 *             modificaciones o sin ellas, siempre que se mantengan esta 
 *             licencia y las notas de autor y copyright de arriba.
 *****************************************************************************/

//****************************************************************************
//    DECLARACION DE LIBRERIAS
//****************************************************************************
#include "lcd_7_lines.h"

//****************************************************************************
//    DECLARACION DE FUNCIONES
//****************************************************************************

PROGMEM const char mensaje []=							//se define un mensaje que pueda ser considerable en extension
{														// no se como ponerlo como argumento ??
	"....::::ESTE ES EL MENSAJE EN DESPLAZAMIENTO::::...."
};

unsigned char read_data_lcd_7(void)
{
	/* Declaracion de Variables */
	unsigned char HIGH,LOW;	// Se utilizan para recibir la parte alta y baja proveniente de la LCD
	
	/* Ajuste de Puerto y Señales de control para la LCD */
	DDR_LCD = 0x00|(DDR_LCD & 0x0F);	// Se coloca la parte alta del puerto B como entrada para recibir el dato de la LCD
	PORT_LCD |= (1<<LCD_RS);	//Se selecciona el registro de intrucciones de dato de la LCD
	PORT_LCD |= (1<<LCD_RW);	//Se habilita la opcion de leer de la LCD
	
	/* Lectura del Dato */
	_delay_us(2);
	PORT_LCD |= (1<<LCD_EN);	//Activa la LCD para la lectura
	_delay_us(2);
	HIGH = (PIN_LCD & 0xF0);	//Lee el nibble alto proveniente de la LCD
	PORT_LCD &= ~(1<<LCD_EN);	//Finaliza la lectura de la LCD
	_delay_us(2);
	PORT_LCD |= (1<<LCD_EN);	//Activa la LCD para la lectura
	_delay_us(2);
	LOW = (PIN_LCD & 0xF0);		//Lee el nibble bajo proveniente de la LCD
	PORT_LCD &= ~(1<<LCD_EN);	//Finaliza la lectura de la LCD
	_delay_us(2);
	
	return (HIGH & 0xF0)|((LOW>>4) & 0x0F);	//Se retorna el dato concatenado de la LCD
}

void send_command_lcd_7(unsigned char command, unsigned char RS) //1 para datos, 0 para comandos
{
	_delay_ms(3);
	//unsigned char q=read_data_lcd_7();
	//while((q & 0x80)!=0)
	//{
		
	//};
	/* Ajuste de Puerto y Señales de control para la LCD */
	DDR_LCD = 0xF0|(DDR_LCD & 0x0F);	// Se coloca la parte alta del puerto B como salida para enviar el dato a la LCD
	PORT_LCD &= ~(1<<LCD_RW);	//Se habilita la opcion de escribir de la LCD
	if (RS)
	{
		PORT_LCD |= (1<<LCD_RS);	//Se selecciona el registro de intrucciones de dato de la LCD
	}
	else
	{
		PORT_LCD &= ~(1<<LCD_RS);	//Se selecciona el registro de intrucciones de comados de la LCD
	}
	
	/* Escritura del comando */
	_delay_us(2);
	PORT_LCD = (0xF0 & command)|(PORT_LCD & 0x0F);	//coloca la parte alta del dato a escribir en la parte alta del puerto B
	_delay_us(2);
	PORT_LCD |= (1<<LCD_EN);		//Activa la LCD para la escritura
	_delay_us(2);
	PORT_LCD &= ~(1<<LCD_EN);	//Finaliza la escritura de la LCD
	_delay_us(2);
	PORT_LCD = (0xF0 & (command<<4))|(PORT_LCD & 0x0F);	//coloca la parte baja del dato a escribir en la parte alta del puerto B
	_delay_us(2);
	PORT_LCD |= (1<<LCD_EN);		//Activa la LCD para la escritura
	_delay_us(2);
	PORT_LCD &= ~(1<<LCD_EN);	//Finaliza la escritura de la LCD
	_delay_us(2);
	DDR_LCD = 0x00|(DDR_LCD & 0x0F);	// Se coloca la parte alta del puerto B como entrada
		
}

void init_lcd_7(void)
{
	/* CONFIGURACION E INICIALIZACION DE PUERTOS */
	DDR_LCD = (1<<LCD_EN)|(1<<LCD_RW)|(1<<LCD_RS);	// Configracion de los Pines 2,1 y 0 como salida de las señales EN, R/W y Rs respectivamente
	
	/* Ajuste de Puerto y Señales de control para la LCD */
	DDR_LCD = 0xF0|(DDR_LCD & 0x0F);	// Se coloca la parte alta del puerto B como salida para enviar el dato a la LCD
	PORT_LCD &= ~(1<<LCD_RS);	//Se selecciona el registro de intrucciones de comados de la LCD
	PORT_LCD &= ~(1<<LCD_RW);	//Se habilita la opcion de escribir de la LCD
	PORT_LCD &= ~(1<<LCD_EN);	//No se activa
	
	/* Secuencia de inicialización del LCD en modo de 4 bits */
	_delay_ms(45);	//Tiempo de organizacion del reset del LCD
	send_command_lcd_7(0x30,0);
	_delay_ms(5);
	send_command_lcd_7(0x30,0);
	_delay_ms(1);
	send_command_lcd_7(0x30,0);
	_delay_ms(1);
	send_command_lcd_7(0x02,0); //Se envia la instruccion que sea de 4 lineas de datos
	_delay_ms(1);
	send_command_lcd_7(0x28,0); //Se ajusta el LCD a dos lineas con caracteres de 5x7
	send_command_lcd_7(0x0F,0); // se prende el LCD y se pone el cursor titilante
	send_command_lcd_7(0x01,0); //limpia el LCD y deja el cursor en la posicion 1,0
	send_command_lcd_7(0x06,0); // se ajusta el avance del puntero
}

void send_string_lcd_7(char *string)
{
	/* Declaracion de Variables */
	unsigned char i=0;
	
	/* Escritura del dato */
	while(string[i]!=0)
	{
		send_command_lcd_7(string[i],1);
		i++;
	}
	
}

void send_dir_lcd_7(unsigned char fil,unsigned char col)
{
	if(fil==1)
	{
		fil = LCD_LINE1;
	}
	else
	{
		fil = LCD_LINE2;
	}
	send_command_lcd_7(fil+col, 0);         // Instrucción 'Set DDRAM Address'
}


int escribir(char c, FILE * stream)
{
	/*if (c=='\n')
	{
		escribir('\r', stream);
	}*/
	send_command_lcd_7(c,1);

	return 0;
}

void scrolling_text(unsigned char linea)
{
	/* Declaracion de Variables */
	unsigned char exit=1;
	unsigned char frame;    // Manjea el frame actual a mostrar
	unsigned char indice;	  // Se desplaza por el frame
	char dato;				  //obtiene el dato temporal a mostrar
	
	retorno:				 //etiqueta para interrupcion del ciclo infino for, Cambia el flujo del programa
	frame=0;				 //reinicia el frame
	do
	{
		send_dir_lcd_7(linea,0);      // Posiciona el cursor en la linea que se quiera el desplazamiento
		for(indice=0; indice<LCD_LINEAS-1; indice++)
		{
			dato = pgm_read_byte(&mensaje[frame+indice]);  // se obtiene el dato del mensaje 
			if(dato)				  // mientras el dato sea diferente del null se envia
			{
				send_command_lcd_7(dato,1);      // se envia a la LCD, el 1 indica que es un dato
			}                 
			else
			{
				goto retorno;       // Cambia el flujo del programa retornando a la etiqueta retorno
			}                  
			
		}
		_delay_ms(200);			//controla la velocidad del desplazamiento 
		frame++;
		
	}
	while(exit==1);
}
