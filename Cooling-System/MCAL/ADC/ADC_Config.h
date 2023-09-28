/*
 *<<<<<<<<<<<<    ADC_Program.h   >>>>>>>>>>>>>>
 *
 *  Author : Rashad
 *  Layer  : MCAL
 *  SWC    : ADC
 *
 */
#ifndef ADC_CONFIG_H
#define ADC_CONFIG_H

/*
 *        Select Reference Voltage

#define     AREF                         0
#define     AVCC                         1
#define     RESERVED                     2
#define     INTERNAL                     3
 */

#define     REFERENCE_VOLTAGE             AVCC


/*
	Select RIGHT or LEFT Adjust
	RIGHT
	LEFT
 */

#define     ADJUST                        RIGHT

/*
	ADC ENABLE or DISABLE
	DISABLE
	ENABLE
 */

#define     ADEN                         ENABLE

/*
	AUTO Trigger Enable or Disable
	DISABLE
	ENABLE
 */

#define     ADATE                        DISABLE

/*
	-->> ADC Auto Trigger Source

	Free_Running_Mode
	Analog_Comparator
	External_Interrupt_Request_0
	Timer_Counter0_Compare_Match
	Timer_Counter0_Overflow
	Timer_Counter1_Compare_MatchB
	Timer_Counter1_Overflow
	Timer_Counter1_Capture_Event
 */

#define  AUTO_TRIGGER_SOURCE     Free_Running_Mode

/*
    ADC Interrupt Enable or Disable
    DISABLE
    ENABLE
 */

#define     ADIE                         DISABLE

/*
   ADC Prescaler Selection

     NOT_USE_PRESCALER
     PRESCALER_DIVISION_BY_2
     PRESCALER_DIVISION_BY_4
     PRESCALER_DIVISION_BY_8
     PRESCALER_DIVISION_BY_16
     PRESCALER_DIVISION_BY_32
     PRESCALER_DIVISION_BY_64
     PRESCALER_DIVISION_BY_128
 */

#define     PRESCALER           PRESCALER_DIVISION_BY_128

#endif
