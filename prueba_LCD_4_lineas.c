/*
 * prueba_LCD_4_lineas.c
 *
 * Main para majar una linea lcd de 4 lineas.
 * En este código se muestra las funciones típicas sobre cómo controlar un a LCD mediante 4 líneas. 
 * También se muestra como dar formato a números usando la simple función sprintf de la librería studio.h. 
 * En comentarios también se encuentra la manera de usar printf mediante el re direccionamiento de los 
 * punteros de salida.
 * Esta librería trae además una nueva función llamada scrolling_text que nos permite poner un 
 * texto en movimiento en cualquiera de las dos líneas de la LCD. 
 * Se adjunta una simulación en proteus para un microcontrolador ATmega16.
 *  Author: JoamManuel
 */ 

#include "lcd_7_lines.h"

int main(void)
{
	char buff[16];
	//FILE mystream = FDEV_SETUP_STREAM(escribir, NULL,_FDEV_SETUP_WRITE);
	init_lcd_7();
	//stdout = &mystream;
	//printf("JOAM ^ %d\nManuel",2);
	//send_dir_lcd_7(2,0);
	//printf("Rincon %d",9);
	sprintf(buff, "%3d:%03d:%03d", 12, 0, 0);
	send_string_lcd_7(buff);
	scrolling_text(2);
	/*send_command_lcd_7(LCD_CLEAR,1);
	send_string_lcd_7("JOAM");
	send_dir_lcd_7(2,2);
	send_string_lcd_7("Manuel");*/
    while(1)
    {
        //TODO:: Please write your application code 
    }
}
