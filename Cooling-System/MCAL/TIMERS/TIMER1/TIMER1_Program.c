/*
 *<<<<<<<<<<<    TIMER_Program.c   >>>>>>>>>>>>
 *
 *  Author : Rashad
 *  Layer  : MCAL
 *  SWC    : Timer
 *
 */
#include "../../../LIB/STD_TYPES.h"
#include "../../../LIB/BIT_MATH.h"

/* Include My own Header Files*/
#include "TIMER1_Interface.h"
#include "TIMER1_Private.h"
#include "TIMER1_Config.h"

void (*Global_PointerToFunction_OVF_T1) (void) = NULL ; 
void (*Global_PointerToFunction_CTC_TA) (void) = NULL ; 
void (*Global_PointerToFunction_CTC_TB) (void) = NULL ;
u16 Global_u16PreloadValue = 0 ;
u16 Global_u16CompareMatchValue_1A = 0 ;
u16 Global_u16CompareMatchValue_1B = 0 ;



void TIMER1_voidInit (void)
{

/*         TIMER1 Mode Selection        */
    #if (MODE == NORMAL_OVF)                             
        CLR_BIT(TCCR1A_REG,TCCR1A_WGM10);
        CLR_BIT(TCCR1A_REG,TCCR1A_WGM11);
		CLR_BIT(TCCR1B_REG,TCCR1B_WGM12);
        CLR_BIT(TCCR1B_REG,TCCR1B_WGM13);
        SET_BIT(TIMSK_REG,TIMER_TIMSK_TOIE1);         // Enable T1 OVF Interrupt [PIE]. 
    #elif (MODE == PWM_PHASECORRECT_8_BIT)                     
          SET_BIT(TCCR1A_REG,TCCR1A_WGM10);
        CLR_BIT(TCCR1A_REG,TCCR1A_WGM11);
		CLR_BIT(TCCR1B_REG,TCCR1B_WGM12);
        CLR_BIT(TCCR1B_REG,TCCR1B_WGM13);
    #elif (MODE == PWM_PHASECORRECT_9_BIT)                                 
        CLR_BIT(TCCR1A_REG,TCCR1A_WGM10);
          SET_BIT(TCCR1A_REG,TCCR1A_WGM11);
		CLR_BIT(TCCR1B_REG,TCCR1B_WGM12);
        CLR_BIT(TCCR1B_REG,TCCR1B_WGM13);
    #elif (MODE == PWM_PHASECORRECT_10_BIT)                             
          SET_BIT(TCCR1A_REG,TCCR1A_WGM10);
          SET_BIT(TCCR1A_REG,TCCR1A_WGM11);
		CLR_BIT(TCCR1B_REG,TCCR1B_WGM12);
        CLR_BIT(TCCR1B_REG,TCCR1B_WGM13);
    #elif (MODE == CTC)
        CLR_BIT(TCCR1A_REG,TCCR1A_WGM10);
        CLR_BIT(TCCR1A_REG,TCCR1A_WGM11);
		  SET_BIT(TCCR1B_REG,TCCR1B_WGM12);                 
        CLR_BIT(TCCR1B_REG,TCCR1B_WGM13);
        SET_BIT(TIMSK_REG,TIMER_TIMSK_OCIE1A);         // Enable T1 A CTC Interrupt [PIE].
        SET_BIT(TIMSK_REG,TIMER_TIMSK_OCIE1B);         // Enable T1 B CTC Interrupt [PIE].
    #elif (MODE == FAST_PWM_8_BIT)
          SET_BIT(TCCR1A_REG,TCCR1A_WGM10);
        CLR_BIT(TCCR1A_REG,TCCR1A_WGM11);
		  SET_BIT(TCCR1B_REG,TCCR1B_WGM12);                 
        CLR_BIT(TCCR1B_REG,TCCR1B_WGM13);
    #elif (MODE == FAST_PWM_9_BIT)
        CLR_BIT(TCCR1A_REG,TCCR1A_WGM10);
          SET_BIT(TCCR1A_REG,TCCR1A_WGM11);
		  SET_BIT(TCCR1B_REG,TCCR1B_WGM12);                 
        CLR_BIT(TCCR1B_REG,TCCR1B_WGM13);
    #elif (MODE == FAST_PWM_10_BIT)
          SET_BIT(TCCR1A_REG,TCCR1A_WGM10);
          SET_BIT(TCCR1A_REG,TCCR1A_WGM11);
		  SET_BIT(TCCR1B_REG,TCCR1B_WGM12);                 
        CLR_BIT(TCCR1B_REG,TCCR1B_WGM13);
    #elif (MODE == PWM_Phase_FrequencyCorrect_ICR1)
        CLR_BIT(TCCR1A_REG,TCCR1A_WGM10);
        CLR_BIT(TCCR1A_REG,TCCR1A_WGM11);
		CLR_BIT(TCCR1B_REG,TCCR1B_WGM12);
          SET_BIT(TCCR1B_REG,TCCR1B_WGM13);
    #elif (MODE == PWM_Phase_FrequencyCorrect)
          SET_BIT(TCCR1A_REG,TCCR1A_WGM10);
        CLR_BIT(TCCR1A_REG,TCCR1A_WGM11);
		CLR_BIT(TCCR1B_REG,TCCR1B_WGM12);
          SET_BIT(TCCR1B_REG,TCCR1B_WGM13);
    #elif (MODE == PWM_PhaseCorrect_ICR1)
        CLR_BIT(TCCR1A_REG,TCCR1A_WGM10);
          SET_BIT(TCCR1A_REG,TCCR1A_WGM11);
		CLR_BIT(TCCR1B_REG,TCCR1B_WGM12);
          SET_BIT(TCCR1B_REG,TCCR1B_WGM13);
    #elif (MODE == PWM_PhaseCorrect)
          SET_BIT(TCCR1A_REG,TCCR1A_WGM10);
          SET_BIT(TCCR1A_REG,TCCR1A_WGM11);
		CLR_BIT(TCCR1B_REG,TCCR1B_WGM12);
          SET_BIT(TCCR1B_REG,TCCR1B_WGM13);
    #elif (MODE == CTC_ICR1)
        CLR_BIT(TCCR1A_REG,TCCR1A_WGM10);
        CLR_BIT(TCCR1A_REG,TCCR1A_WGM11);
		  SET_BIT(TCCR1B_REG,TCCR1B_WGM12);                 
          SET_BIT(TCCR1B_REG,TCCR1B_WGM13);
          SET_BIT(TIMSK_REG,TIMER_TIMSK_TICIE);         // Enable T1 CTC ICR1 Interrupt [PIE].
    #elif (MODE == Reversed)
          SET_BIT(TCCR1A_REG,TCCR1A_WGM10);
        CLR_BIT(TCCR1A_REG,TCCR1A_WGM11);
		  SET_BIT(TCCR1B_REG,TCCR1B_WGM12);                 
          SET_BIT(TCCR1B_REG,TCCR1B_WGM13);
    #elif (MODE == FAST_PWM_ICR1)
        CLR_BIT(TCCR1A_REG,TCCR1A_WGM10);
          SET_BIT(TCCR1A_REG,TCCR1A_WGM11);
		  SET_BIT(TCCR1B_REG,TCCR1B_WGM12);                 
          SET_BIT(TCCR1B_REG,TCCR1B_WGM13);
    #elif (MODE == FAST_PWM)
          SET_BIT(TCCR1A_REG,TCCR1A_WGM10);
          SET_BIT(TCCR1A_REG,TCCR1A_WGM11);
		  SET_BIT(TCCR1B_REG,TCCR1B_WGM12);                 
          SET_BIT(TCCR1B_REG,TCCR1B_WGM13);
    #else 
        #error  Wrong selection of operation mode
    #endif 

/*          OC1A Mode Selection                 */
    #if (OC1A_MODE == DISCONNECTED)
        CLR_BIT(TCCR1A_REG,TCCR1A_COM1A0);
        CLR_BIT(TCCR1A_REG,TCCR1A_COM1A1);
    #elif ((OC1A_MODE == SETonTOP_CLEARonCOMPARE) || (OC1A_MODE == SETonCOMPdownCounting_CLEARonCOMPupCounting))
        CLR_BIT(TCCR1A_REG,TCCR1A_COM1A0);
          SET_BIT(TCCR1A_REG,TCCR1A_COM1A1);
    #elif ((OC1A_MODE == SETonCOMPARE_CLEARonTOP) || (OC1A_MODE == SETonCOMPupCounting_CLEARonCOMPdownCounting))
        SET_BIT(TCCR1A_REG,TCCR1A_COM1A0);
        SET_BIT(TCCR1A_REG,TCCR1A_COM1A1);
    #else 
        #error  Wrong selection of OC1A mode
    #endif
    #if ( MODE == NORMAL_OVF || MODE == CTC || MODE == CTC_ICR1 )       // Compare Output Mode, non-PWM
        CLR_BIT(TCCR1A_REG,TCCR1A_COM1A0);                            // Disable OC1A
        CLR_BIT(TCCR1A_REG,TCCR1A_COM1A1);                            // Disable OC1A

    #endif

/*          OC1B Mode Selection                 */

    #if (OC1B_MODE == DISCONNECTED)
        CLR_BIT(TCCR1A_REG,TCCR1A_COM1B0);
        CLR_BIT(TCCR1A_REG,TCCR1A_COM1B1);
    #elif ((OC1B_MODE == SETonTOP_CLEARonCOMPARE) || (OC1B_MODE == SETonCOMPdownCounting_CLEARonCOMPupCounting))
        CLR_BIT(TCCR1A_REG,TCCR1A_COM1B0);
          SET_BIT(TCCR1A_REG,TCCR1A_COM1B1);
    #elif ((OC1B_MODE == SETonCOMPARE_CLEARonTOP) || (OC1B_MODE == SETonCOMPupCounting_CLEARonCOMPdownCounting))
        SET_BIT(TCCR1A_REG,TCCR1A_COM1B0);
        SET_BIT(TCCR1A_REG,TCCR1A_COM1B1);
    #else 
        #error  Wrong selection of OC1B mode
    #endif
    #if ( MODE == NORMAL_OVF || MODE == CTC || MODE == CTC_ICR1 )       // Compare Output Mode, non-PWM
        CLR_BIT(TCCR1A_REG,TCCR1A_COM1B0);                            // Disable OC1B
        CLR_BIT(TCCR1A_REG,TCCR1A_COM1B1);                            // Disable OC1B

    #endif


/*     TIMER1 Prescaller Selection      */
    TCCR1B_REG = ( TCCR1B_REG & 0b11111000 );              // Clear Prescaller 

    #if( PRESCALER == NO_CLK_SOURCE_TIMER_STOPED )          
        CLR_BIT(TCCR1B_REG,TCCR1B_CS10);
        CLR_BIT(TCCR1B_REG,TCCR1B_CS11);
        CLR_BIT(TCCR1B_REG,TCCR1B_CS12);
    #elif ( PRESCALER == NOT_USE_PRESCALER )
          SET_BIT(TCCR1B_REG,TCCR1B_CS10);
        CLR_BIT(TCCR1B_REG,TCCR1B_CS11);
        CLR_BIT(TCCR1B_REG,TCCR1B_CS12);
    #elif ( PRESCALER == PRESCALER_DIVISION_BY_8 )
        CLR_BIT(TCCR1B_REG,TCCR1B_CS10);
          SET_BIT(TCCR1B_REG,TCCR1B_CS11);
        CLR_BIT(TCCR1B_REG,TCCR1B_CS12);
    #elif ( PRESCALER == PRESCALER_DIVISION_BY_64 )
          SET_BIT(TCCR1B_REG,TCCR1B_CS10);
          SET_BIT(TCCR1B_REG,TCCR1B_CS11);
        CLR_BIT(TCCR1B_REG,TCCR1B_CS12);
    #elif ( PRESCALER == PRESCALER_DIVISION_BY_256 )
        CLR_BIT(TCCR1B_REG,TCCR1B_CS10);
        CLR_BIT(TCCR1B_REG,TCCR1B_CS11);
          SET_BIT(TCCR1B_REG,TCCR1B_CS12);
    #elif ( PRESCALER == PRESCALER_DIVISION_BY_1024 )
          SET_BIT(TCCR1B_REG,TCCR1B_CS10);
        CLR_BIT(TCCR1B_REG,TCCR1B_CS11);
          SET_BIT(TCCR1B_REG,TCCR1B_CS12);
    #elif ( PRESCALER == EXTERNAL_CLK_SOURCE_FALLING_EDGE )
        CLR_BIT(TCCR1B_REG,TCCR1B_CS10);
          SET_BIT(TCCR1B_REG,TCCR1B_CS11);
          SET_BIT(TCCR1B_REG,TCCR1B_CS12);
    #elif ( PRESCALER == EXTERNAL_CLK_SOURCE_RAISING_EDGE )
        SET_BIT(TCCR1B_REG,TCCR1B_CS10);
        SET_BIT(TCCR1B_REG,TCCR1B_CS11);
        SET_BIT(TCCR1B_REG,TCCR1B_CS12);
    #else
        #error  Wrong selection of Prescaller mode
    #endif

}

void TIMER1_voidSetCallBack_OVF (void (*Local_PointerToFunction_OVF) (void))
{
    Global_PointerToFunction_OVF_T1 = Local_PointerToFunction_OVF ;
}


void TIMER1_voidSetCallBack_CTC_A (void (*Local_PointerToFunction_CTC) (void))
{
    Global_PointerToFunction_CTC_TA = Local_PointerToFunction_CTC ;
}


void TIMER1_voidSetCallBack_CTC_B (void (*Local_PointerToFunction_CTC) (void))
{
    Global_PointerToFunction_CTC_TB = Local_PointerToFunction_CTC ;
}



void TIMER1_voidSetPreloadValue ( u16 Local_u16PreloadValue )
{
    #if (MODE == NORMAL_OVF)
        TCNT1_REG = Local_u16PreloadValue ;
        Global_u16PreloadValue = Local_u16PreloadValue ;
    #else
        // No Action
    #endif
}


void TIMER1_voidSetCompareMatchValue_T1A ( u16 Local_u16CompareMatchValue )
{
    #if (MODE != NORMAL_OVF)
        OCR1A_REG = Local_u16CompareMatchValue ;
        Global_u16CompareMatchValue_1A = Local_u16CompareMatchValue ;
    #endif
}

void TIMER1_voidSetCompareMatchValue_T1B ( u16 Local_u16CompareMatchValue )
{
    #if (MODE != NORMAL_OVF)
        OCR1B_REG = Local_u16CompareMatchValue ;
        Global_u16CompareMatchValue_1B = Local_u16CompareMatchValue ;
    #endif
}


void TIMER1_void_u16PWM_T1A ( u16 Copy_u16CompareMatchValue , u16 Copy_u16TopValue )
{
    TIMER1_voidSetCompareMatchValue_T1A ( Copy_u16CompareMatchValue );
    ICR1_REG = Copy_u16TopValue ;
}


void TIMER1_void_u16PWM_T1B ( u16 Copy_u16CompareMatchValue , u16 Copy_u16TopValue )
{
    TIMER1_voidSetCompareMatchValue_T1B ( Copy_u16CompareMatchValue );
    ICR1_REG = Copy_u16TopValue ;
}






/*TIMER1 Normal Mode ISR*/
void __vector_9 (void)      __attribute__((signal)) ;
void __vector_9 (void)
{
    if (Global_PointerToFunction_OVF_T1 != NULL)
    {
    	Global_PointerToFunction_OVF_T1() ;
    }
}

/*TIMER1 CTCB Mode ISR*/
void __vector_8 (void)      __attribute__((signal)) ;
void __vector_8 (void)
{
    if (Global_PointerToFunction_CTC_TB != NULL)
    {
    	Global_PointerToFunction_CTC_TB() ;
    }
}

/*TIMER1 CTCA Mode ISR*/
void __vector_7 (void)      __attribute__((signal)) ;
void __vector_7 (void)
{
    if (Global_PointerToFunction_CTC_TA != NULL)
    {
    	Global_PointerToFunction_CTC_TA() ;
    }
}
