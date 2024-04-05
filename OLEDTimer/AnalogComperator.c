/*
 * AnalogComperator.c
 *
 * Created: 18/03/2024 14:37:24
 *  Author: yossi
 */ 

#include "AnalogComperator.h"

void TurnOnAnalogComparator()
{
	ACSR = (1<<ACBG) | (1<<ACIE) | (1<<ACIS0) | (1<<ACIS1);
}