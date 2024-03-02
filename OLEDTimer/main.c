/*
 * main.c
 *
 * Created: 2/20/2024 9:25:58 PM
 *  Author: יוסי שלי
 */ 

#define F_CPU 8000000L
#include <util/delay.h>
#include "i2c.h"
#include "ssd1306.h"
#include "CathClockMainScreenRLE.h"
#include "SevenSeg19H.h"
#include "Big_Tooth.h"
//#include "OLED.h"

unsigned char Minuts,Seconds;
unsigned char Buffer[55][3];


int main(void)
{
	DDRD = 0x01;
	//OLED oled;
	Minuts = 2;
	Seconds = 0;
	char finished = false;
	
	OLED_Init();  //initialize the OLED
	OLED_Clear(); //clear the display (for good measure)
		
			OLED_SetCursor(0, 0);        //set the cursor position to (0, 0)
			OLED_DrawBitmapRLE (0,0,CathClockMainScreenRLE,566); //Print out some text
			OLED_WriteTwoDigitNumber(SevenSegments_struc,37,4,02,false,false,false,false,false);
			OLED_WriteChar(SevenSegments_struc,59,4,':',false,false,false);
			OLED_WriteTwoDigitNumber(SevenSegments_struc,70,4,0,false,false,false,false,false);
	
	
	while (!finished)
	{
		PORTD ^= 0x01;
		_delay_ms (100);
			
		if (--Seconds == 255)
		{
			if (--Minuts == 255)
			{
				TimerFinished();
				finished = true;;
			}
			else
				Seconds = 59;
		}
	
	
		
		if (!finished) 
		{	
			//OLED_SetCursor(0, 0);        //set the cursor position to (0, 0)
			//OLED_DrawBitmapRLE (0,0,CathClockMainScreenRLE,566); //Print out some text
			OLED_WriteTwoDigitNumber(SevenSegments_struc,37,4,Minuts,false,false,false,false,false);
			OLED_WriteChar(SevenSegments_struc,59,4,':',false,false,false);
			OLED_WriteTwoDigitNumber(SevenSegments_struc,70,4,Seconds,false,false,false,false,false);
		}
	}
    //TODO:: Please write your application code 

}

void TimerFinished ()
{
	OLED_SetCursor(0,0);
	OLED_DrawBitmapRLE(0,0,Big_Tooth,194);
	Minuts = 2;
	Seconds = 0;		
}