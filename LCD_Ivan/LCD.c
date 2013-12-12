// Funciones LCD
// Creadas Por: Rafael Toro Sanchez

// Archivo LCD.c

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "lcd.h"

void LcdInit()
{
 LCD_DDR = 0xF0; // D4...D7(Salida)
 sbi(LCD_DDR,RS); //RS (Salida)
 sbi(LCD_DDR,E); //E (Salida)

 cbi(LCD_PORT,RS); // RS=0
 cbi(LCD_PORT,E);  // E=0
 sbi(LCD_PORT,RS); // RS=1
 _delay_ms(15);

 LcdComando8(0x38);
 _delay_us(4100);
 LcdComando8(0x38);
 _delay_us(4100);

 LcdComando8(0x28);
 _delay_us(4100);
 LcdComando4(0x28);
 _delay_us(4100);

 LcdComando4(0x08);
 LcdComando4(0x01);
 _delay_us(4100);
 
 LcdComando4(0x0c);
 cbi(LCD_PORT,RS); 
 cbi(LCD_PORT,E); 
}

void LcdComando8(uint8_t Comando8)
{
 sbi(LCD_PORT,RS); // RS=1

 LCD_PORT = Comando8 & 0xF0;
 LCD_DELAY;

 cbi(LCD_PORT,RS); // RS=0
 LCD_DELAY;
 sbi(LCD_PORT,E);  // E=1
 LCD_DELAY;
 cbi(LCD_PORT,E);  // E=0 
 LCD_DELAY;
 sbi(LCD_PORT,RS); // RS=1
 
 _delay_us(40);
}

void LcdComando4(uint8_t Comando4)
{
 sbi(LCD_PORT,RS); // RS=1

 LCD_PORT = Comando4&0xF0;
 LCD_DELAY;

 cbi(LCD_PORT,RS); // RS=0
 LCD_DELAY;
 sbi(LCD_PORT,E);  // E=1
 LCD_DELAY;
 cbi(LCD_PORT,E);  // E=0
 LCD_DELAY;
 sbi(LCD_PORT,RS); // RS=1
 LCD_DELAY;

 LCD_PORT = ((Comando4&0x0F)<<4);
 _delay_ms(1);

 cbi(LCD_PORT,RS); // RS=0
 LCD_DELAY;
 sbi(LCD_PORT,E);  // E=1
 LCD_DELAY;
 cbi(LCD_PORT,E);  // E=0
 LCD_DELAY;
 sbi(LCD_PORT,RS); // RS=1
 
 _delay_us(40); 
}

void LcdDatos4(uint8_t Datos4)
{
 LCD_PORT = Datos4&0xF0;
 LCD_DELAY;
 
 sbi(LCD_PORT,RS); // RS=1
 LCD_DELAY;
 sbi(LCD_PORT,E);  // E=1
 LCD_DELAY;
 cbi(LCD_PORT,E);  // E=0
 LCD_DELAY;
 cbi(LCD_PORT,RS); // RS=0

 LCD_PORT = ((Datos4&0x0F)<<4);
 _delay_ms(1);

 sbi(LCD_PORT,RS); // RS=1
 LCD_DELAY;
 sbi(LCD_PORT,E);  // E=1
 LCD_DELAY;
 cbi(LCD_PORT,E);  // E=0
 LCD_DELAY;
 cbi(LCD_PORT,RS); // RS=0

 _delay_us(40);
}

void LcdGotoXY(uint8_t X, uint8_t Y)
{
 uint8_t posicion;
 
 switch(X)
 {
   case 0:
          posicion=Y;
   break;

   case 1:
          posicion=0x40+Y;
   break;

   default:
          posicion=0x40+Y;
 }

 LcdComando4(LCD_DDRAM|posicion);
}

uint8_t letra;

void LcdPrintData(prog_char Mensaje[])
{
 
 uint8_t i=0;

 if(Mensaje==0)
    return;
 
 do{

    letra = pgm_read_byte_near(Mensaje+i);
    
	if(letra!=0)
	 {
	  LcdDatos4(letra);
	 }

	 i++;

   }while(letra!=0);

}

void LcdShowChar(uint8_t caracter)
{
 LcdDatos4(caracter); // ejemplo: LcdShowChar('R');
}

void LcdShowNum(uint8_t numero)
{
 LcdDatos4(numero + 48); //ejemplo: LcdShowNum(5);
}

void clc()
{
 cbi(LCD_PORT,RS);
 _delay_ms(1);
 LcdComando4(0x01); 
 _delay_ms(1);
}

void LcdMostrarNum8bits(uint8_t num8)
{
 uint8_t arr[3];

 arr[0] = num8/100;
 arr[1] = (num8%100)/10;
 arr[2] = (num8%100)%10;

 if(arr[0] == 0)
  {
   if(arr[1] == 0)
    {
	 LcdDatos4(arr[2]+48);
	 _delay_ms(1);
     LcdDatos4(0x0D);
	}
   else
    {
	 LcdDatos4(arr[1]+48);
	 LcdDatos4(arr[2]+48);
    }
  }
 else
  {
    LcdDatos4(arr[0]+48);
	LcdDatos4(arr[1]+48);
	LcdDatos4(arr[2]+48);
  }
}

void LcdMostrarNum16bits(uint16_t num16)
{
 uint16_t arr[5];

 arr[0] = num16/10000;
 arr[1] = (num16%10000)/1000;
 arr[2] = ((num16%10000)%1000)/100;
 arr[3] = (((num16%10000)%1000)%100)/10;
 arr[4] = (((num16%10000)%1000)%100)%10;

 if(arr[0] == 0)
  {
   if(arr[1] == 0)
    {
	 if(arr[2] == 0)
	  {
	   if(arr[3] == 0)
	    {
		 LcdDatos4(arr[4]+48);
		 _delay_ms(1);
         LcdDatos4(0x0D);
		}
       else
	    {
		 LcdDatos4(arr[3]+48);
		 LcdDatos4(arr[4]+48);
		}
	  }
	 else
	  {
	   LcdDatos4(arr[2]+48);
	   LcdDatos4(arr[3]+48);
	   LcdDatos4(arr[4]+48);
	  }
	}
   else
    {
	 LcdDatos4(arr[1]+48);
	 LcdDatos4(arr[2]+48);
	 LcdDatos4(arr[3]+48);
	 LcdDatos4(arr[4]+48);
	}
  }
 else
  {
   LcdDatos4(arr[0]+48);
   LcdDatos4(arr[1]+48);
   LcdDatos4(arr[2]+48);
   LcdDatos4(arr[3]+48);
   LcdDatos4(arr[4]+48);
  }  
}

