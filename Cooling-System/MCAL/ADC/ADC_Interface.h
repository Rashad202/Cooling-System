/*
 *<<<<<<<<<<<<    ADC_Program.h   >>>>>>>>>>>>>>
 *
 *  Author : Rashad
 *  Layer  : MCAL
 *  SWC    : ADC
 *
 */
#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

/*       Select Reference Voltage       */

#define     AREF                         0
#define     AVCC                         1
#define     RESERVED                     2
#define     INTERNAL                     3


/*     Select RIGHT or LEFT Adjust      */
#define     RIGHT                        0
#define     LEFT                         1

/*        ADC ENABLE or DISABLE         */
#define     DISABLE                      0
#define     ENABLE                       1

/*       ADC Auto Trigger Source        */
#define  Free_Running_Mode               0
#define  Analog_Comparator               1
#define  External_Interrupt_Request_0    2
#define  Timer_Counter0_Compare_Match    3
#define  Timer_Counter0_Overflow         4
#define  Timer_Counter1_Compare_MatchB   5
#define  Timer_Counter1_Overflow         6
#define  Timer_Counter1_Capture_Event    7



/*        ADC Prescaler Selection        */

#define     NOT_USE_PRESCALER             0
#define     PRESCALER_DIVISION_BY_2       2
#define     PRESCALER_DIVISION_BY_4       4
#define     PRESCALER_DIVISION_BY_8       8
#define     PRESCALER_DIVISION_BY_16      16
#define     PRESCALER_DIVISION_BY_32      32
#define     PRESCALER_DIVISION_BY_64      64
#define     PRESCALER_DIVISION_BY_128     128

/*    ADC Interrupt Enable or Disable   */
#define     DISABLE                      0
#define     ENABLE                       1

/*     Macros of Channel Number    */
#define     ADC0                    0
#define     ADC1                    1
#define     ADC2                    2
#define     ADC3                    3
#define     ADC4                    4
#define     ADC5                    5
#define     ADC6                    6
#define     ADC7                    7




void ADC_voidInit (void);

u16 ADC_u16ReadSynchronus ( u8 Copy_u8ChannelNumber ) ;

u16 ADC_u16ReadASynchronus ( u8 Copy_u8ChannelNumber ,  void (*Local_PointerToFunction) (void) ) ;

#endif
