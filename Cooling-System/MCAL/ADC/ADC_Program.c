/*
 *<<<<<<<<<<<<    ADC_Program.h   >>>>>>>>>>>>>>
 *
 *  Author : Rashad
 *  Layer  : MCAL
 *  SWC    : ADC
 *
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

/* Include Header Files From MCAL */
#include "../DIO/DIO_Interface.h"

/* Include My own Header Files*/
#include "ADC_Interface.h"
#include "ADC_Private.h"
#include "ADC_Config.h"

/* Global Pointer to Function */
void (*Global_PF_Vector_16)(void) = NULL ;

u16 ADC_u16Result = 0 ;
u8 ADC_u18BusyFlag = 0 ;

void ADC_voidInit (void)
{

/*       Select Reference Voltage       */ 

    #if ( REFERENCE_VOLTAGE == AREF )
        CLR_BIT(ADMUX_REG,ADMUX_REFS0);
        CLR_BIT(ADMUX_REG,ADMUX_REFS1);
    #elif ( REFERENCE_VOLTAGE == AVCC )
      SET_BIT(ADMUX_REG,ADMUX_REFS0);
        CLR_BIT(ADMUX_REG,ADMUX_REFS1);
    #elif ( REFERENCE_VOLTAGE == INTERNAL )
      SET_BIT(ADMUX_REG,ADMUX_REFS0);
      SET_BIT(ADMUX_REG,ADMUX_REFS1);
    #else
        CLR_BIT(ADMUX_REG,ADMUX_REFS0);
      SET_BIT(ADMUX_REG,ADMUX_REFS1);
    #endif

/*     Select RIGHT or LEFT Adjust      */

    #if ( ADJUST == RIGHT )
        CLR_BIT(ADMUX_REG,ADMUX_ADLAR);
    #elif ( ADJUST == LEFT )
      SET_BIT(ADMUX_REG,ADMUX_ADLAR);
    #endif

/*        ADC Enable or Disable         */

    #if ( ADEN == ENABLE )
      SET_BIT(ADCSRA_REG,ADCSRA_ADEN);
    #elif ( ADEN == DISABLE )
        CLR_BIT(ADCSRA_REG,ADCSRA_ADEN);
    #endif

/*    AUTO Trigger Enable or Disable    */

    #if ( ADATE == ENABLE )
      SET_BIT(ADCSRA_REG,ADCSRA_ADATE);
           
            /*       ADC Auto Trigger Source        */
            
        #if( AUTO_TRIGGER_SOURCE == Free_Running_Mode )
            CLR_BIT(SFIOR_REG,SFIOR_ADTS0);
            CLR_BIT(SFIOR_REG,SFIOR_ADTS1);
            CLR_BIT(SFIOR_REG,SFIOR_ADTS2);
        #elif ( AUTO_TRIGGER_SOURCE == Analog_Comparator )
            SET_BIT(SFIOR_REG,SFIOR_ADTS0);
            CLR_BIT(SFIOR_REG,SFIOR_ADTS1);
            CLR_BIT(SFIOR_REG,SFIOR_ADTS2);
        #elif ( AUTO_TRIGGER_SOURCE == External_Interrupt_Request_0 )
            CLR_BIT(SFIOR_REG,SFIOR_ADTS0);
            SET_BIT(SFIOR_REG,SFIOR_ADTS1);
            CLR_BIT(SFIOR_REG,SFIOR_ADTS2);
        #elif ( AUTO_TRIGGER_SOURCE == Timer_Counter0_Compare_Match )
            SET_BIT(SFIOR_REG,SFIOR_ADTS0);
            SET_BIT(SFIOR_REG,SFIOR_ADTS1);
            CLR_BIT(SFIOR_REG,SFIOR_ADTS2);
        #elif ( AUTO_TRIGGER_SOURCE == Timer_Counter0_Overflow )
            CLR_BIT(SFIOR_REG,SFIOR_ADTS0);
            CLR_BIT(SFIOR_REG,SFIOR_ADTS1);
            SET_BIT(SFIOR_REG,SFIOR_ADTS2);
        #elif ( AUTO_TRIGGER_SOURCE == Timer_Counter1_Compare_MatchB )
            SET_BIT(SFIOR_REG,SFIOR_ADTS0);
            CLR_BIT(SFIOR_REG,SFIOR_ADTS1);
            SET_BIT(SFIOR_REG,SFIOR_ADTS2);
        #elif ( AUTO_TRIGGER_SOURCE == Timer_Counter1_Overflow )
            CLR_BIT(SFIOR_REG,SFIOR_ADTS0);
            SET_BIT(SFIOR_REG,SFIOR_ADTS1);
            SET_BIT(SFIOR_REG,SFIOR_ADTS2);
        #elif ( AUTO_TRIGGER_SOURCE == Timer_Counter1_Capture_Event )
            SET_BIT(SFIOR_REG,SFIOR_ADTS0);
            SET_BIT(SFIOR_REG,SFIOR_ADTS1);
            SET_BIT(SFIOR_REG,SFIOR_ADTS2);
        #endif

    #elif ( ADATE == DISABLE )
        CLR_BIT(ADCSRA_REG,ADCSRA_ADATE);
    #endif

/*    ADC Interrupt Enable or Disable   */

    #if ( ADIE == ENABLE )          // work with Interrupt
        SET_BIT(ADCSRA_REG,ADCSRA_ADIE);
    #elif ( ADIE == DISABLE )       // work with Polling
        CLR_BIT(ADCSRA_REG,ADCSRA_ADIE);
    #endif

/*       ADC Prescaler Selection        */

    /*     Clear Prescaler      */ 
    ADCSRA_REG = ( ADCSRA_REG & 0b11111000 );

    #if( PRESCALER == NOT_USE_PRESCALER )
        // NOTHING
    #elif ( PRESCALER == PRESCALER_DIVISION_BY_2 )
        SET_BIT(ADCSRA_REG,ADCSRA_ADPS0);
        CLR_BIT(ADCSRA_REG,ADCSRA_ADPS1);
        CLR_BIT(ADCSRA_REG,ADCSRA_ADPS2);
    #elif ( PRESCALER == PRESCALER_DIVISION_BY_4 )
        CLR_BIT(ADCSRA_REG,ADCSRA_ADPS0);
        SET_BIT(ADCSRA_REG,ADCSRA_ADPS1);
        CLR_BIT(ADCSRA_REG,ADCSRA_ADPS2);
    #elif ( PRESCALER == PRESCALER_DIVISION_BY_8 )
        SET_BIT(ADCSRA_REG,ADCSRA_ADPS0);
        SET_BIT(ADCSRA_REG,ADCSRA_ADPS1);
        CLR_BIT(ADCSRA_REG,ADCSRA_ADPS2);
    #elif ( PRESCALER == PRESCALER_DIVISION_BY_16 )
        CLR_BIT(ADCSRA_REG,ADCSRA_ADPS0);
        CLR_BIT(ADCSRA_REG,ADCSRA_ADPS1);
        SET_BIT(ADCSRA_REG,ADCSRA_ADPS2);
    #elif ( PRESCALER == PRESCALER_DIVISION_BY_32 )
        SET_BIT(ADCSRA_REG,ADCSRA_ADPS0);
        CLR_BIT(ADCSRA_REG,ADCSRA_ADPS1);
        SET_BIT(ADCSRA_REG,ADCSRA_ADPS2);
    #elif ( PRESCALER == PRESCALER_DIVISION_BY_64 )
        CLR_BIT(ADCSRA_REG,ADCSRA_ADPS0);
        SET_BIT(ADCSRA_REG,ADCSRA_ADPS1);
        SET_BIT(ADCSRA_REG,ADCSRA_ADPS2);
    #elif ( PRESCALER == PRESCALER_DIVISION_BY_128 )
        SET_BIT(ADCSRA_REG,ADCSRA_ADPS0);
        SET_BIT(ADCSRA_REG,ADCSRA_ADPS1);
        SET_BIT(ADCSRA_REG,ADCSRA_ADPS2);
    #endif

}

u16 ADC_u16ReadSynchronus ( u8 Copy_u8ChannelNumber ) 
{

    /*     Clear MUX      */ 
    ADMUX_REG = ( ADMUX_REG & 0b11100000 );        

    /*   Select channel   */ 
    switch ( Copy_u8ChannelNumber )
    {
        case ADC0 :     ADMUX_REG = (( ADMUX_REG & 0b11100000 ) | 0b00000000 );     break;
        case ADC1 :     ADMUX_REG = (( ADMUX_REG & 0b11100000 ) | 0b00000001 );     break;
        case ADC2 :     ADMUX_REG = (( ADMUX_REG & 0b11100000 ) | 0b00000010 );     break;        
        case ADC3 :     ADMUX_REG = (( ADMUX_REG & 0b11100000 ) | 0b00000011 );     break;
        case ADC4 :     ADMUX_REG = (( ADMUX_REG & 0b11100000 ) | 0b00000100 );     break;
        case ADC5 :     ADMUX_REG = (( ADMUX_REG & 0b11100000 ) | 0b00000101 );     break;
        case ADC6 :     ADMUX_REG = (( ADMUX_REG & 0b11100000 ) | 0b00000110 );     break;
        case ADC7 :     ADMUX_REG = (( ADMUX_REG & 0b11100000 ) | 0b00000111 );     break;
        default   :                                                                 break;
    }
 
    /*    Start Conversion    */ 
    #if ( ADATE == ENABLE )
        // Start Conversion When Triggering Occures.
    #elif ( ADATE == DISABLE )
      SET_BIT(ADCSRA_REG,ADCSRA_ADSC);
    #endif
    
    // work with Interrupt
    #if ( ADIE == ENABLE )                        
    // When ADC Finish conversion will Raising Interrupt Flag and Jump to ADC_ISR Function.    
    #elif ( ADIE == DISABLE )                     // work with Polling
        /* GET FLAG and Polling the Flag */
        u8 ADIF=0 ;
        while( ADIF == 0 )
        {
            ADIF = GET_BIT(ADCSRA_REG,ADCSRA_ADIF);    // Stuck on while untill Flag Raising 1 .
        }
    #endif


    #if ( ADIE == ENABLE )          // work with Interrupt
        // Interrupt Flag Will Cleared Automaticlly.    
    #elif ( ADIE == DISABLE )       // work with Polling
        /* Clear Flag */
      SET_BIT(ADCSRA_REG,ADCSRA_ADIF);
    #endif 

    #if ( ADJUST == RIGHT )
        return ADC_REG ;      
    #elif ( ADJUST == LEFT )
        return ADCH_REG ;
    #endif

}

u16 ADC_u16ReadASynchronus ( u8 Copy_u8ChannelNumber ,  void (*Local_PvoidCallBackFunctionPtr) (void) ) 
{
    if ( (ADC_u18BusyFlag == BUSY) ||  (Local_PvoidCallBackFunctionPtr == NULL) )
    {
        return 0;
    }
    else
    {
        /*   Make the ADC State is Busy   */
            ADC_u18BusyFlag = BUSY ;
        
            /*     Clear MUX      */ 
            ADMUX_REG = ( ADMUX_REG & 0b11100000 );        
        
            /*   Select channel   */ 
            switch ( Copy_u8ChannelNumber )
            {
                case ADC0 :     ADMUX_REG = (( ADMUX_REG & 0b11100000 ) | 0b00000000 );     break;
                case ADC1 :     ADMUX_REG = (( ADMUX_REG & 0b11100000 ) | 0b00000001 );     break;
                case ADC2 :     ADMUX_REG = (( ADMUX_REG & 0b11100000 ) | 0b00000010 );     break;        
                case ADC3 :     ADMUX_REG = (( ADMUX_REG & 0b11100000 ) | 0b00000011 );     break;
                case ADC4 :     ADMUX_REG = (( ADMUX_REG & 0b11100000 ) | 0b00000100 );     break;
                case ADC5 :     ADMUX_REG = (( ADMUX_REG & 0b11100000 ) | 0b00000101 );     break;
                case ADC6 :     ADMUX_REG = (( ADMUX_REG & 0b11100000 ) | 0b00000110 );     break;
                case ADC7 :     ADMUX_REG = (( ADMUX_REG & 0b11100000 ) | 0b00000111 );     break;
                default   :                                                                 break;
            }
        
            /*    Set The Call Back Function    */ 
            Global_PF_Vector_16 = Local_PvoidCallBackFunctionPtr ;
          
            /*    Start Conversion    */ 
            #if ( ADATE == ENABLE )
                // Start Conversion When Triggering Occures.
            #elif ( ADATE == DISABLE )
              SET_BIT(ADCSRA_REG,ADCSRA_ADSC);
            #endif
          
            /*     Enable ADIE  AD Interrupt Enable  and Interrupt Flag Will Cleared Automaticlly.       */   
          SET_BIT(ADCSRA_REG,ADCSRA_ADIE);
     
           return ADC_u16Result ; 
        
    }
}

void __vector_16 (void)   __attribute__((signal));
void __vector_16 (void)
{


    #if ( ADJUST == RIGHT )
    ADC_u16Result = ADC_REG ;      
    #elif ( ADJUST == LEFT )
    ADC_u16Result = ADCH_REG ;
    #endif

/*   Make the ADC State is NOT Busy because it's Completed   */
    ADC_u18BusyFlag = NOT_BUSY ;

/*   Call Call Back Function br Global PTR   */
    Global_PF_Vector_16 ();

/*     Disable ADIE  AD Interrupt Enable     */   
    CLR_BIT(ADCSRA_REG,ADCSRA_ADIE);
    
}
