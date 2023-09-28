/*
 * main.c
 *
 *  Created on: 28 Sep 2023
 *      Author: Rashad
 */


/* LIB */
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"


/*  MCAL Layer */
#include "../MCAL/DIO/DIO_Interface.h"
#include "../MCAL/ADC/ADC_Interface.h"
#include"../MCAL/GIE/GIE_Interface.h"
#include"../MCAL/TIMERS/TIMER1/TIMER1_Interface.h"
/*  HAL Layer */
#include "../HAL/LCD/LCD_Interface.h"
#include "../HAL/LM35/LM35_Interface.h"
#include "../HAL/SERVO_MOTOR/SERVO_Interface.h"

#include "avr/delay.h"



u16 Temp_Value;
void main()
{

	ADC_voidInit();
	LCD_voidInit();
	TIMER1_voidInit();
	DIO_voidSetPortDirection(DIO_PORTB,DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTA,DIO_PIN1,DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTA,DIO_PIN2,DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTA,DIO_PIN3,DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTA,DIO_PIN4,DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTB,DIO_PIN6,DIO_OUTPUT);

	while(1)
	{

		LCD_voidGoTo_XY(0,0);
		LCD_voidWriteString("Temperature:");
		Temp_Value = Temp_u8GetReading(ADC0) ;


		if(Temp_Value>=20 &&Temp_Value<26)
		{
			LCD_voidGoTo_XY(0,13);
			DIO_voidSetPortValue(DIO_PORTB,0X00);
			LCD_voidWrite_u32Number(Temp_Value);
			LCD_voidGoTo_XY(1,5);
			LCD_voidWriteString("Nice ");
			DIO_voidSetPinValue(DIO_PORTA,DIO_PIN2,DIO_HIGH);
			DIO_voidSetPinValue(DIO_PORTA,DIO_PIN4,DIO_HIGH);
			DIO_voidSetPinValue(DIO_PORTA,DIO_PIN1,DIO_LOW);
			DIO_voidSetPinValue(DIO_PORTA,DIO_PIN3,DIO_LOW);
			DIO_voidSetPinValue(DIO_PORTB,DIO_PIN6,DIO_LOW);
			SERVO_voidRotateSpecificAngle_OC1A(0);

		}
		else if(Temp_Value<20)
		{

			LCD_voidGoTo_XY(0,13);
			DIO_voidSetPortValue(DIO_PORTB,0X00);
			LCD_voidWrite_u32Number(Temp_Value);
			LCD_voidGoTo_XY(1,5);
			LCD_voidWriteString("Cold ");
			DIO_voidSetPinValue(DIO_PORTA,DIO_PIN1,DIO_HIGH);
			DIO_voidSetPinValue(DIO_PORTA,DIO_PIN2,DIO_LOW);
			DIO_voidSetPinValue(DIO_PORTA,DIO_PIN3,DIO_LOW);
			DIO_voidSetPinValue(DIO_PORTA,DIO_PIN4,DIO_LOW);
			DIO_voidSetPinValue(DIO_PORTB,DIO_PIN6,DIO_HIGH);
			SERVO_voidRotateSpecificAngle_OC1A(90);
		}
		else if(Temp_Value>=26)
		{
			LCD_voidGoTo_XY(0,13);
			LCD_voidWrite_u32Number(Temp_Value);
			DIO_voidSetPortValue(DIO_PORTB,0X3F);
			LCD_voidGoTo_XY(1,5);
			LCD_voidWriteString("HOT  ");
			DIO_voidSetPinValue(DIO_PORTA,DIO_PIN3,DIO_HIGH);
			DIO_voidSetPinValue(DIO_PORTA,DIO_PIN2,DIO_LOW);
			DIO_voidSetPinValue(DIO_PORTA,DIO_PIN1,DIO_LOW);
			DIO_voidSetPinValue(DIO_PORTB,DIO_PIN6,DIO_LOW);
			DIO_voidSetPinValue(DIO_PORTA,DIO_PIN4,DIO_LOW);
			SERVO_voidRotateSpecificAngle_OC1A(90);

		}
	}
}
