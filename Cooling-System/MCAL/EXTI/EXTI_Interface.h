/*
 *<<<<<<<<<<    EXTI_Interface.h    >>>>>>>>>>>
 *
 *  Author : Rashad
 *  Layer  : MCAL
 *  SWC    : EXTI
 *
 */
#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H

/* Macros as INT options */
#define  EXTI_INT0              0
#define  EXTI_INT1             1
#define  EXTI_INT2             2

/* Macros as Sense Control options */
#define  FALLING_EDGE                 0
#define  RAISING_EDGE                 1
#define  LOW_LEVEL                    2
#define  ON_CHANGE                    3

/* Private Macros to BIT Numbers */
#define  PIN0                    0
#define  PIN1                    1
#define  PIN2                    2
#define  PIN3                    3
#define  PIN4                    4
#define  PIN5                    5
#define  PIN6                    6
#define  PIN7                    7

void EXTI_voidEnable ( u8 Copy_u8INTnumber , u8 Copy_u8SenseControl );

void EXTI_voidDisable ( u8 Copy_u8INTnumber );

void EXTI_voidSetCallBack ( u8 Copy_u8INTnumber , void (*Local_PointerToFunction) (void) );

void EXTI_voidClearFlag ( u8 Copy_u8Line );




#endif
