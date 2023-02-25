/*
 * main.c
 *
 *  Created on: Dec 4, 2022
 *      Author: Lenovo
 */


#define F_CPU 8000000UL
#include  <avr/delay.h>

/*LIB*/
#include "types.h"
#include "BIT_MATH.h"

#include <stdlib.h>


/*DIO*/
#include "DIO_interface.h"

/*LCD*/
#include "LCD_interface.h"

/*KPD*/
#include "KPD_interface.h"


int main ()
{

	// initialozation zone
	DIO_vidSetPortDir(DIO_PORTB,0x0F);
	DIO_vidSetPortDir(DIO_PORTD,PORT_OUTPUT);



	DIO_vidSetPinDir (DIO_PORTC, DIO_PIN0, DIO_OUTPUT);
	DIO_vidSetPinDir (DIO_PORTC, DIO_PIN1, DIO_OUTPUT);
	DIO_vidSetPinDir (DIO_PORTC, DIO_PIN2, DIO_OUTPUT);
	u8 key;                                             // act as temp variable because key won't save the variable to store the data to be monitored on the screen.
	u8 NUM1[5];
	u8 NUM2[5];
	u8 count;
	u8 flag = 0;
	u8 operation;
	u16 res;
	u16 rr [5];

	//set input pins pullup
	DIO_vidSetPortVal (DIO_PORTB,0xF0 );

	/* Init LCD */
	HLCD_vidInit();



	// supper loop zone

	while (1)
	{
		key = KPD_u8GetPressedKey ();
		//HLCD_vidsendChar(key);                     // this action will result in infinity loop of printing
		if(key != NOT_PRESSED)
		{
			HLCD_vidsendChar(key);
			if((key == '+') || (key == '-') || (key == '/') || (key == '*'))
			{
				operation = key;
				count =0;
				flag = 1;

			}



			else if(key == '=')
			{
				flag = 0;

				switch (operation)
					{
						case '+':
							res = atoi (NUM1) + atoi(NUM2);
							itoa (res, rr, 10);
							HLCD_vidGoToXY(2 , 1);
							HLCD_vidWriteStr (rr);

							for (u8 i=0; i <5; i++)
							{
								NUM1[i]=0;


							}

							for (u8 i=0; i <5; i++)
							{

								NUM2 [i] =0;
							}





							break;

						case '-' :
							res = atoi (NUM1) - atoi(NUM2);
							itoa (res, rr, 10);
							HLCD_vidGoToXY(2 , 1);
							//if (atoi(NUM2)>atoi (NUM1))
							//{
								//HLCD_vidsendChar ('-');
								//HLCD_vidWriteStr (rr);
							//}                            // i think this is not true, i think i should think from the point of negative numbers that had been explained by saif
							//else
							//{
								HLCD_vidWriteStr (rr);
							//}



							for (u8 i=0; i <5; i++)
							{
								NUM1[i]=0;

							}

							for (u8 i=0; i <5; i++)
							{

								NUM2 [i] =0;
							}





							break;

						case '/' :
							res = atoi (NUM1) / atoi(NUM2);

							if (atoi(NUM2) == 0)
							{
								HLCD_vidGoToXY(2 , 1);
								HLCD_vidWriteStr ("Error!");
							}
							else
							{
								itoa (res, rr, 10);
								HLCD_vidGoToXY(2 , 1);
								HLCD_vidWriteStr (rr);
							}



							for (u8 i=0; i <5; i++)
							{
								NUM1[i]=0;

							}

							for (u8 i=0; i <5; i++)
							{

								NUM2 [i] =0;
							}





							break;

						case '*' :
							res = atoi (NUM1) * atoi(NUM2);
							itoa (res, rr, 10);
							HLCD_vidGoToXY(2 , 1);
							HLCD_vidWriteStr (rr);

							for (u8 i=0; i <5; i++)
							{
								NUM1[i]=0;

							}

							for (u8 i=0; i <5; i++)
							{

								NUM2 [i] =0;
							}




							break;

						default :
							// do nothing;
							break;

					}






			}
			else if (key == 'c')
			{
				 HLCD_vidsendCMD(LCD_CLR);

					for (u8 i=0; i <5; i++)
					{
						NUM1[i]=0;

					}

					for (u8 i=0; i <5; i++)
					{

						NUM2 [i] =0;
					}

					flag = 0;
					count =0;




			}
			else
			{
				if(flag == 0)
				{
					NUM1[count] = key;
					count++;

				}
				else
				{
					NUM2[count] = key;
					count++;
				}




			}




		}


	}




}



/*
#define _OPEN_SYS_ITOA_EXT
#include <stdio.h>
#include <stdlib.h>

int main ()
{
   int i;
   char buffer [sizeof(int)*8+1];
   printf ("Enter a number: ");
   if (scanf ("%d",&i) == 1) {
      itoa (i,buffer,DECIMAL);
      printf ("decimal: %s\n",buffer);

*/








//NUM1 = KPD_u8GetPressedKey ();
//NUM2 = KPD_u8GetPressedKey ();
//u8 arr[2]= {NUM1, NUM2} ;
//u16 r;
//u8 *data = arr ;
//NUM1 =NUM1- '0' ;
//NUM2 = NUM2 -'0';
//result  = (NUM1 *10) + NUM2;
//result = result + '0';
//NUM1 = KPD_u8GetPressedKey ();
//NUM1 =NUM1- '0' ;
//HLCD_vidWriteStr (arr);
//vid_Result();

/*
 *

if(NUM1 != NOT_PRESSED)
{
	HLCD_vidGoToXY(1,0);
	//HLCD_vidWriteStr (arr);
	while (*result =! '\0')
	{
	HLCD_vidWriteStr (*result++);
	}
}*/

/*
u16 u16_calculate (u16 x, char operator, u16 y)
{
	switch (operator)
	{
	case '+':
		r = x+y;
		return r;

	case '-':
		r= x-y;
		return r;

	case '*':
		r = x*y;
		return r;

	case '/':
		r = x/y;
		return r;

	default:
		//do nothing;
		break;
	}
}*/



	/*
	void vid_Result()
	{
		u8 KeyPressed =  KPD_u8GetPressedKey ();
		if(KeyPressed != NOT_PRESSED)
			{
				HLCD_vidGoToXY(1,0);
				HLCD_vidWriteStr (arr);
			}



	}

*/





/*

void vidPrintString (u8 *u8_conToInt)
	{

	}
*/






/*
			f64 a, b;
			f64 sum1 =0;
			f64 sum2 =0;
			for (u8 i =0 ; i <5; i++)
			{
				f64 product =1;
				u8 exp = 4-i;
				u8 base =10;
				while (exp != 0)
				{
					product *= base;
					--exp;
				}
				NUM1[i] = NUM1 [i] - '0';
				a = NUM1 [i] * product;
				sum1 = sum1 +a;

				NUM2[i] = NUM2[i] -'0';
				b = NUM1 [i] * product;
				sum2 = sum2 +b;
			}
			*/



/*NUM1[0] = 0;
NUM1[1] = 0;
NUM1[2] = 0;
NUM1[3] = 0;
NUM1[4] = 0;

NUM2[0] = 0;
NUM2[1] = 0;
NUM2[2] = 0;
NUM2[3] = 0;
NUM2[4] = 0;*/
