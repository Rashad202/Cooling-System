/*
 *<<<<<<<<<<<     DIO_Interface.h   >>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Rashad
 *  Layer  : MCAL
 *  SWC    : DIO/GPIO
 *
 */ 
#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H

/** Macros as Direction options */
#define DIO_INPUT               0
#define DIO_OUTPUT              1

/**** Macros as Value options ***/
#define DIO_LOW                 0
#define DIO_HIGH                1

/*** Macros as Status options ***/
#define DIO_OFF                 0
#define DIO_ON                  1

#define DIO_PORT_OUTPUT		    0xFF
#define DIO_PORT_INPUT			0

/* Macros as PortNumber options */
#define DIO_PORTA 				0
#define DIO_PORTB 	 			1
#define DIO_PORTC  				2
#define DIO_PORTD  				3

/** Macros as PinNumber options */
#define DIO_PIN0   				0
#define DIO_PIN1   				1
#define DIO_PIN2   				2
#define DIO_PIN3   				3
#define DIO_PIN4   				4
#define DIO_PIN5   				5
#define DIO_PIN6   				6
#define DIO_PIN7   				7


void DIO_voidSetPinDirection (u8 Copy_u8PortNumber, u8 Copy_u8PinNumber, u8 Copy_u8Direction );

void DIO_voidSetPortDirection (u8 Copy_u8PortNumber, u8 Copy_u8Direction );                 

void DIO_voidSetPinValue (u8 Copy_u8PortNumber, u8 Copy_u8PinNumber, u8 Copy_u8Value );

void DIO_voidSetPortValue (u8 Copy_u8PortNumber, u8 Copy_u8Value );

u8 DIO_u8GetPinValue (u8 Copy_u8PortNumber, u8 Copy_u8PinNumber );

u8 DIO_u8GetPortValue (u8 Copy_u8PortNumber );

void DIO_voidTogglePinValue (u8 Copy_u8PortNumber, u8 Copy_u8PinNumber );

void DIO_voidTogglePortValue (u8 Copy_u8PortNumber );

void DIO_voidConfig_Pull_Up_Port (u8 Copy_u8PortNumber, u8 Copy_u8PullUpStatus );

void DIO_voidConfig_Pull_Up_Pin (u8 Copy_u8PortNumber,u8 Copy_u8PinNumber,u8 Copy_u8PullUpStatus);


#endif
