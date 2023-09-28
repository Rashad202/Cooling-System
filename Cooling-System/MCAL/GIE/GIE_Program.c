/*
 *<<<<<<<<<<    GIE_Program.c   >>>>>>>>>>>
 *
 *  Author : Rashad
 *  Layer  : MCAL
 *  SWC    : GIE
 *
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

/* Include My own Header Files*/
#include "GIE_Interface.h"
#include "GIE_Private.h"
#include "GIE_Config.h"


void GIE_void_Enable ( void)
{
         SET_BIT(SREG_REG,SREG_I);
}
void GIE_void_Disable ( void)
{
         CLR_BIT(SREG_REG,SREG_I);
}
