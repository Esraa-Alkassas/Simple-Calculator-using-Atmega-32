/*
 * KPD_prog.c
 *
 *  Created on: Nov 26, 2022
 *      Author: Lenovo
 */

#define F_CPU  8000000UL
#include <avr/delay.h>
/*lib*/
#include "types.h"
#include "BIT_MATH.h"
/*DIO*/
#include "DIO_interface.h"
/*LCD*/
#include "LCD_interface.h"
/*KPD*/
#include "KPD_interface.h"
#include "KPD_priv.h"
#include "KPD_CFG.h"


static const u8 KPD_au8Array[4][4] =                 /*this is a two Darray,,, static to not be able to write extern in other files and use it,,, const because its values are fixedfor my design*/
{
		{'7', '8', '9', '/'},
		{'4', '5', '6', '*'},
		{'1', '2', '3', '-'},
		{'c', '0', '=', '+'}
};


u8 KPD_u8GetPressedKey (void)
{
	u8 u8SwVal = NOT_PRESSED;    /*because if we don't press any key, garbage value doesn't be returned*/
	u8 u8Col;
	u8 u8Row;

	for (u8Col = 0; u8Col<4; u8Col++)
	{
		DIO_vidSetPinVal (KPD_PORT, u8Col, DIO_LOW);
		for (u8Row = 4; u8Row< 8; u8Row++)
		{
			if (DIO_u8GetPinValue(KPD_PORT, u8Row)==DIO_LOW)
			{
				u8SwVal = KPD_au8Array [u8Row-4][u8Col];
				_delay_ms (10);
				while (DIO_u8GetPinValue (KPD_PORT, u8Row) == DIO_LOW);

			}
		}
		DIO_vidSetPinVal (KPD_PORT, u8Col, DIO_HIGH);

	}

	return u8SwVal;
}

