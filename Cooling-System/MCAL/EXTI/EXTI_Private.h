/*
 *<<<<<<<<<<    EXTI_Private.h    >>>>>>>>>>>
 *
 *  Author : Rashad
 *  Layer  : MCAL
 *  SWC    : EXTI
 *
 */
#ifndef EXTI_PRIVATE_H
#define EXTI_PRIVATE_H

/* Private Macros */
#define  GIFR_REG 		     *((volatile u8*)0x5A)
#define  GICR_REG            *((volatile u8*)0x5B)
#define  MCUCR_REG           *((volatile u8*)0x55)
#define  MCUCSR_REG          *((volatile u8*)0x54)


#define  NULL                     (void*)(0)

#endif
