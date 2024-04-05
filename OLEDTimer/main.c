/*
 * main.c
 *
 * Created: 2/20/2024 9:25:58 PM
 *  Author: יוסי שלי
 */ 

#define F_CPU 8000000L
#include <util/delay.h>
#include <stdlib.h>
#include "i2c.h"
#include "ssd1306.h"
//#include "CathClockMainScreenRLE.h"
#include "RazTimer.h"
#include "SevenSeg19H.h"
#include "Big_Tooth.h"
#include "main.h"
#include "ADC.h"

#define FINISH_BUZ_TIME 200
#define START 0
#define FINISHED 1


unsigned char Minuts,Seconds;


int main(void)
{
	int temp;
	DDRD = 0x03;
	DDRC = 0x00;
	
	PORTC = 0x00;
	//OLED oled;
	Minuts = 2;
	Seconds = 0;
	char finished = false;
	_delay_ms(60);
	OLED_Init();  //initialize the OLED
	OLED_Clear(); //clear the display (for good measure)
	//sei();
	//ADC_init();
	//ADC_StartConversion();
	
	//_delay_ms(5000);

		//stay: goto stay;
		while (1) {
			OLED_SetCursor(0, 0);        //set the cursor position to (0, 0)
			OLED_DrawBitmapRLE (0,0,RazTimer,474); //Print out some text
			OLED_WriteTwoDigitNumber(SevenSegments_struc,37,4,02,false,false,false,false,false);
			OLED_WriteChar(SevenSegments_struc,59,4,':',false,false,false);
			OLED_WriteTwoDigitNumber(SevenSegments_struc,70,4,0,false,false,false,false,false);
	
		WaitForStartButton();
		PlayBuzzer(START);
	
		while (!finished)
		{
			PORTD ^= 0x01;
			_delay_ms (10);
			
			if (--Seconds == 255)
			{
				if (--Minuts == 255)
				{
					TimerFinished();
					PlayBuzzer(FINISHED);
					finished = true;
					break;
				}
				else
					Seconds = 59;
			}
	
	
		
			//if (!finished) 
			//{	
				//OLED_SetCursor(0, 0);        //set the cursor position to (0, 0)
				//OLED_DrawBitmapRLE (0,0,CathClockMainScreenRLE,566); //Print out some text
				OLED_WriteTwoDigitNumber(SevenSegments_struc,37,4,Minuts,false,false,false,false,false);
				OLED_WriteChar(SevenSegments_struc,59,4,':',false,false,false);
				OLED_WriteTwoDigitNumber(SevenSegments_struc,70,4,Seconds,false,false,false,false,false);
			//}
		}
	
		WaitForStartButton();
		finished = false;
	
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


void PlayBuzzer (char event)
{
	switch (event)
	{
		case 0:
			PORTD |= 0x02;
			_delay_ms(100);
			PORTD &= ~0x02;
		break;
		case 1:
			for (int i=0; i < 5; i++)
			{
				PORTD |= 0x02;
				_delay_ms(FINISH_BUZ_TIME);
				PORTD &= ~0x02;
				_delay_ms(FINISH_BUZ_TIME);
			}		
		break;
	}

}

void WaitForStartButton ()
{
	do {
	while (PIND & (1 << PIND4));
	_delay_ms(50);
	} while (PIND & (1 << PIND4));
}

ISR (ADC_vect)
{
	cli();
	//PlayBuzzer(START);
	//sei();
	//unsigned char tempSREG = SREG;
	//OLED_SetCursor(0,0);

	OLED_WriteNumber(SevenSegments_struc,0,2,ADC);	//OLED_WriteTwoDigitNumber(ADCL);
	//SREG = tempSREG;
	//ADCSRA |= (1<<ADIF);
	sei();
}