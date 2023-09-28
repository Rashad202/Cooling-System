/*
 *<<<<<<<<<<    EXTI_Program.c    >>>>>>>>>>>
 *
 *  Author : Rashad
 *  Layer  : MCAL
 *  SWC    : EXTI
 *
 */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

/* Include My own Header Files*/
#include "EXTI_Interface.h"
#include "EXTI_Private.h"
#include "EXTI_Config.h"

/* Global PoEXTI_INTer to Function */
void (*Global_PF_Vector_1)(void) = NULL ;
void (*Global_PF_Vector_2)(void) = NULL ;
void (*Global_PF_Vector_3)(void) = NULL ;



void EXTI_voidEnable ( u8 Copy_u8EXTI_INTnumber , u8 Copy_u8SenseControl )
{
    switch ( Copy_u8EXTI_INTnumber )
    {
        case EXTI_INT0 :     // Set 1 On PIN6 At GTCR_REG to [Enable] (PIE) Peripheral EXTI_INTerrupt Enable to EXTI_INT0 .
                         SET_BIT(GICR_REG,PIN6);            
                        switch ( Copy_u8SenseControl )
                        {															 // BIT1  -  BIT0  on MCUCR_REG
                            case FALLING_EDGE :										 //    1   -   0   Falling Edge
                            	SET_BIT(MCUCR_REG,PIN1);
                            	CLR_BIT(MCUCR_REG,PIN0);
                            	break;
                            case RAISING_EDGE :     								 //   1   -   1   Raising Edge
                            	SET_BIT(MCUCR_REG,PIN1);
                            	SET_BIT(MCUCR_REG,PIN0);
                            	break;
                            case LOW_LEVEL    :     								 //   0   -   0   Low Level
                            	CLR_BIT(MCUCR_REG,PIN1);
                            	CLR_BIT(MCUCR_REG,PIN0);
                            	break;
                            case ON_CHANGE    :										//   0   -   1   On Change
                            	CLR_BIT(MCUCR_REG,PIN1);
                            	SET_BIT(MCUCR_REG,PIN0);
                            	break;
                            default           :
                            	break;
                        }
                        break;

        case EXTI_INT1 :     // Set 1 On PIN7 At GTCR_REG to [Enable] (PIE) Peripheral EXTI_INTerrupt Enable to EXTI_INT1 .
                        SET_BIT(GICR_REG,PIN7);             
                        switch ( Copy_u8SenseControl )
                        {                                                           // BIT3  -  BIT2  on MCUCR_REG
                            case FALLING_EDGE :										//   1   -   0   Falling Edge
                            	SET_BIT(MCUCR_REG,PIN3);
                            	CLR_BIT(MCUCR_REG,PIN2);
                            	break;
                            case RAISING_EDGE :     								//   1   -   1   Raising Edge
                            	SET_BIT(MCUCR_REG,PIN3);
                            	SET_BIT(MCUCR_REG,PIN2);
                            	break;
                            case LOW_LEVEL    :										//   0   -   0   Low Level
                            	CLR_BIT(MCUCR_REG,PIN3);
                            	CLR_BIT(MCUCR_REG,PIN2);
                            	break;
                            case ON_CHANGE    :										//   0   -   1   On Change
                            	CLR_BIT(MCUCR_REG,PIN3);
                            	SET_BIT(MCUCR_REG,PIN2);
                            	break;
                            default           :                                                                   break;  
                        }
                        break;
        case EXTI_INT2 :      // Set 1 On PIN5 At GTCR_REG to [Enable] (PIE) Peripheral EXTI_INTerrupt Enable to EXTI_INT2 .
                        SET_BIT(GICR_REG,PIN5);            
                        switch ( Copy_u8SenseControl )
                        {                                                                      //  BIT6  on  MCUCSR_REG
                            case FALLING_EDGE :
                            	CLR_BIT(MCUCSR_REG,PIN6);      								   //   0    Falling Edge
                            	break;
                            case RAISING_EDGE :     										   //   1    Raising Edge
                            	SET_BIT(MCUCSR_REG,PIN6);
                            	break;
                            default           :
                            	break;
                        } 
                        break;
        default   :
        	break;
    }
}


void EXTI_voidDisable ( u8 Copy_u8EXTI_INTnumber )
{
    switch ( Copy_u8EXTI_INTnumber )
    {
        case EXTI_INT0 :         // Set 0 On PIN6 At GTCR_REG to [Disable] (PIE) Peripheral EXTI_INTerrupt Enable to EXTI_INT0 .
        	CLR_BIT(GICR_REG,PIN6);
        	break;
        case EXTI_INT1 :         // Set 0 On PIN7 At GTCR_REG to [Disable] (PIE) Peripheral EXTI_INTerrupt Enable to EXTI_INT1 .
        	CLR_BIT(GICR_REG,PIN7);
        	break;
        case EXTI_INT2 :         // Set 0 On PIN5 At GTCR_REG to [Disable] (PIE) Peripheral EXTI_INTerrupt Enable to EXTI_INT2 .
        	CLR_BIT(GICR_REG,PIN5);
        	break;
        default   :
        	break;
    }
}

void EXTI_voidSetCallBack ( u8 Copy_u8EXTI_INTnumber , void (*Local_PoEXTI_INTerToFunction) (void) )
{
    switch( Copy_u8EXTI_INTnumber )
    {
        case EXTI_INT0 :
        	Global_PF_Vector_1 = Local_PoEXTI_INTerToFunction ;
        	break;
        case EXTI_INT1 :
        	Global_PF_Vector_2 = Local_PoEXTI_INTerToFunction ;
        	break;
        case EXTI_INT2 :
        	Global_PF_Vector_3 = Local_PoEXTI_INTerToFunction ;
        	break;
        default   :
        	break;
    } 
}

void EXTI_voidClearFlag ( u8 Copy_u8Line ){

    SET_BIT( GIFR_REG , Copy_u8Line );

}

void __vector_1 (void)   __attribute__((signal));
void __vector_1 (void)
{
    if ( Global_PF_Vector_1 != NULL )
    {
        Global_PF_Vector_1 ();  // calling Global poEXTI_INTer to function that contain address of Application Function with EXTI_INT0.
        EXTI_voidClearFlag( EXTI_INT0 );
    }

}

void __vector_2 (void)   __attribute__((signal));
void __vector_2 (void) 
{
    if ( Global_PF_Vector_2 != NULL )
    {
        Global_PF_Vector_2 ();  // calling Global poEXTI_INTer to function that contain address of Application Function with EXTI_INT1.
        EXTI_voidClearFlag( EXTI_INT1 );
    }
    
}

void __vector_3 (void)   __attribute__((signal));
void __vector_3 (void) 
{
    if ( Global_PF_Vector_3 != NULL )
    {
        Global_PF_Vector_3 ();  // calling Global poEXTI_INTer to function that contain address of Application Function with EXTI_INT2.
        EXTI_voidClearFlag( EXTI_INT2 );
    }
}
