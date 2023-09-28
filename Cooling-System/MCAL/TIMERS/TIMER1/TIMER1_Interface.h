/*
 *<<<<<<<<<<<    TIMER_Interface.h   >>>>>>>>>>>>
 *
 *  Author : Rashad
 *  Layer  : MCAL
 *  SWC    : Timer
 *
 */
#ifndef TIMER1_INTERFACE_H
#define TIMER1_INTERFACE_H


void TIMER1_voidInit (void);


void TIMER1_voidSetCallBack_OVF (void (*Local_PointerToFunction_OVF) (void));


void TIMER1_voidSetCallBack_CTC_A (void (*Local_PointerToFunction_CTC) (void));


void TIMER1_voidSetCallBack_CTC_B (void (*Local_PointerToFunction_CTC) (void));


void TIMER1_voidSetPreloadValue ( u16 Copy_u16PreloadValue );


void TIMER1_voidSetCompareMatchValue_T1A ( u16 Local_u16CompareMatchValue );


void TIMER1_voidSetCompareMatchValue_T1B ( u16 Local_u16CompareMatchValue );


void TIMER1_void_u16PWM_T1A ( u16 Copy_u16CompareMatchValue , u16 Copy_u16TopValue );


void TIMER1_void_u16PWM_T1B ( u16 Copy_u16CompareMatchValue , u16 Copy_u16TopValue );


#endif
