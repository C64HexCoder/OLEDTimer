/*
 * ADC.c
 *
 * Created: 14/03/2024 22:31:48
 *  Author: yossi
 */ 

#include <avr/interrupt.h>
#include "SSD1306.h"
//#include "SevenSeg19H.h"

ADC_init()
{
	ADMUX |= (1<<REFS0) | (1<<REFS1); // Internal 2.56v refrence
	ADCSRA |= (1<<ADEN) | (1<<ADPS2) | (1 << ADPS1) | (1<<ADIE);// 64
	//sei();
}

ADC_StartConversion()
{
	ADCSRA |= (1<<ADSC);
}

