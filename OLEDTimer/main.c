/*
 * main.c
 *
 * Created: 2/20/2024 9:25:58 PM
 *  Author: יוסי שלי
 */ 

#define F_CPU 8000000
#include <util/delay.h>
#include "i2c.h"
#include "ssd1306.h"
#include "CathClockMainScreenRLE.h"
#include "7segment digits.h"
//#include "OLED.h"

int main(void)
{
	DDRD = 0x01;
	//OLED oled;
		
	OLED_Init();  //initialize the OLED
	OLED_Clear(); //clear the display (for good measure)
		
	OLED_SetCursor(0, 0);        //set the cursor position to (0, 0)
	OLED_DrawBitmapRLE (0,0,CathClockMainScreenRLE,566); //Print out some text
	OLED_WriteTwoDigitNumber(SevenSegments_struc,42,4,02,false,false,false,false,false);
	
	
	while (1)
	{
		PORTD ^= 0x01;
		_delay_ms (100);
			
	}
    //TODO:: Please write your application code 

}