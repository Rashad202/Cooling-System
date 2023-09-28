/*
 *   			--- LM35_Interface.h----
 *
 *  Author : Rashad
 *  Layer  : HAL
 *  SWC    : LM35
 *
 */

#ifndef _LM35_INTERFACE_H_
#define _LM35_INTERFACE_H_


#define VREF_VOLTAGE_MV		5000UL
#define ADC_RESOLUTION		1024UL




u16 Temp_u8GetReading(u8 Copy_u8Channel);

#endif /* _LM35_INTERFACE_H_ */
