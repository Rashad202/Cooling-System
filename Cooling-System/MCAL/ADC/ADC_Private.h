/*
 *<<<<<<<<<<<<    ADC_Program.h   >>>>>>>>>>>>>>
 *
 *  Author : Rashad
 *  Layer  : MCAL
 *  SWC    : ADC
 *
 */

#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H

/* Private Macros */
#define      ADMUX_REG             *((volatile u8*)0x27)
/* ADMUX Bits   */
#define ADMUX_REFS1         7							//Reference selection bit1
#define ADMUX_REFS0         6							//Reference selection bit0
#define ADMUX_ADLAR         5							//ADC left adjust result

#define     ADCSRA_REG             *((volatile u8*)0x26)
/* ADCSRA Bits   */
#define ADCSRA_ADEN			7							//ADC enable
#define ADCSRA_ADSC			6                           //Start conversion
#define ADCSRA_ADATE		5                           //Auto trigger enable
#define ADCSRA_ADIF			4                           //Interrupt flag
#define ADCSRA_ADIE			3                           //Interrupt enable
#define ADCSRA_ADPS2		2                           //Prescaler bit2
#define ADCSRA_ADPS1  	    1                           //Prescaler bit1
#define ADCSRA_ADPS0	    0                           //Prescaler bit0



#define       ADCH_REG             *((volatile u8*)0x25)   // Pointer to 8 bit ADCH to read Data From 8 BIT of ADC Data by Right Adjust.
#define       ADCL_REG             *((volatile u8*)0x24)
#define        ADC_REG             *((volatile u16*)0x24)  // Pointer to 16 bit ADCH and ADCL to read Data From 10 BIT of ADC Data. 


#define      SFIOR_REG             *((volatile u8*)0x50)
/* SFIOR Bits   */
#define SFIOR_ADTS2			7                          //Trigger Source bit2
#define SFIOR_ADTS1	     	6                          //Trigger Source bit1
#define SFIOR_ADTS0		    5                          //Trigger Source bit0


#define     BUSY                    0
#define     NOT_BUSY                1

#define     NULL                (void*)(0)

#endif
