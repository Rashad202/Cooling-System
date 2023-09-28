/*
 *   			--- LM35_Program.c----
 *
 *  Author : Rashad
 *  Layer  : HAL
 *  SWC    : LM35
 *
 */
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/ADC/ADC_Interface.h"


#include "LM35_Interface.h"


u16 Temp_u8GetReading(u8 Copy_u8Channel)
{
	u16 Digital_Signal_Temp,Analog_Signal_Temp,Temp_Value;

	Digital_Signal_Temp =  ADC_u16ReadSynchronus ( Copy_u8Channel ) ;
	Analog_Signal_Temp = ((u32)Digital_Signal_Temp * VREF_VOLTAGE_MV ) /ADC_RESOLUTION ;   // 5000 mv   to read Analog_Signal by mv.
	Temp_Value = Analog_Signal_Temp / 10 ;

	return Temp_Value;

}

