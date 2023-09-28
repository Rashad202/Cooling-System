#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

/* Include Header Files From MCAL Layer */
#include "../../MCAL/DIO/DIO_Interface.h"
// #include"../../MCAL/TIMERS/TIMER0/TIMER0_Interface.h"
#include <util/delay.h>

/* Include My own Header Files*/
#include "LCD_Interface.h"
#include "LCD_Private.h"
#include "LCD_Config.h"

void LCD_voidInit (void)
{
    /* Control Pins Directions */
    DIO_voidSetPortDirection(LCD_DATA_PORT , DIO_OUTPUT);
    DIO_voidSetPinDirection(LCD_CONTROL_PORT,RS_PIN,DIO_OUTPUT);
    DIO_voidSetPinDirection(LCD_CONTROL_PORT,RW_PIN,DIO_OUTPUT);
    DIO_voidSetPinDirection(LCD_CONTROL_PORT,E_PIN,DIO_OUTPUT);

    _delay_ms(35);    //TIMER0_voidSetBusyWait_ms(35);

    /* Send Command Function Set */
    LCD_voidWriteCommand ( FS_8BIT_2LINES_5x7 );
    _delay_ms(1);     // TIMER0_voidSetBusyWait_ms(1);

    /* Send Command Display ON-OFF Control */
    LCD_voidWriteCommand ( DIS_ON_NO_CURSER );
    _delay_ms(1);     //TIMER0_voidSetBusyWait_ms(1);

    /* Send Command Display Clear */
    LCD_voidWriteCommand ( DIS_CLEAR );
    _delay_ms(2);     //TIMER0_voidSetBusyWait_ms(2);

    /* Send Command Entry Mode */
    LCD_voidWriteCommand ( ENTRY_MODE_INCREASE_NO_SHIFT );
    _delay_ms(1);     //TIMER0_voidSetBusyWait_ms(1);


}


void LCD_voidWriteCommand ( u8 Copy_u8Command )
{
    /* RS=0 because we send a Command not Data */
    DIO_voidSetPinValue (LCD_CONTROL_PORT,RS_PIN,DIO_LOW);

    /* RW=0 because we Write a Command not Read */
    DIO_voidSetPinValue (LCD_CONTROL_PORT,RW_PIN,DIO_LOW);

    /* Send Data bits from MC PINS to LCD Data PINS */
    DIO_voidSetPortValue(LCD_DATA_PORT,Copy_u8Command);

    /* Falling Edge on E PIN to make LCD Read This Command */
    DIO_voidSetPinValue (LCD_CONTROL_PORT,E_PIN,DIO_HIGH);
    _delay_ms(2);
    DIO_voidSetPinValue (LCD_CONTROL_PORT,E_PIN,DIO_LOW);
}


void LCD_voidWriteChar ( u8 Copy_u8Char )
{
    /* RS=1 because we send a Data not Command */
    DIO_voidSetPinValue (LCD_CONTROL_PORT,RS_PIN,DIO_HIGH);

    /* RW=0 because we Write a Data not Read */
    DIO_voidSetPinValue (LCD_CONTROL_PORT,RW_PIN,DIO_LOW);

    /* Send Data bits from MC PINS to LCD Data PINS */
    DIO_voidSetPortValue(LCD_DATA_PORT,Copy_u8Char);

    /* Falling Edge on E PIN to make LCD Read This Command */
    DIO_voidSetPinValue (LCD_CONTROL_PORT,E_PIN,DIO_HIGH);
    _delay_ms(1);
    DIO_voidSetPinValue (LCD_CONTROL_PORT,E_PIN,DIO_LOW);
}



void LCD_voidWriteString (u8 *Copy_u8Arr )
{
    u8 i = 0 ;
    while (Copy_u8Arr[i] != '\0' )
    {
        LCD_voidWriteChar ( Copy_u8Arr[i] );
        i++;
        if(i==16)
        {
        	LCD_voidGoTo_XY(1,0);
        }
        else if(i==32)
        {
        	LCD_voidGoTo_XY(0,0);
        }
    }
}


void LCD_voidWrite_u32Number ( u32 Copy_u32Number)
{
    u8 Arr[40] ;
    u8 i=0 ;
    while ( Copy_u32Number > 0 )
    {
        Arr[i] = Copy_u32Number % 10 ;
        Copy_u32Number /= 10 ;
        i++;
    }
    i--;
    for( s16 j=i ; j>=0 ; j--)
    {
        LCD_voidWriteChar ( Arr[j] + '0' );
    }
}


void LCD_voidGoTo_XY ( u8 Copy_u8Line , u8 Copy_u8Position )
{
    /* i/p validation */
    if ( Copy_u8Line > LINE_2 || Copy_u8Position > 15 )
    {
        // Do Nothing
    }
    else
    {
        switch(Copy_u8Line)
        {
            case LINE_1 :    LCD_voidWriteCommand ( 0x80 + Copy_u8Position );      break;  //First position at Line_1 is 0x80 Address at DDRAM
            case LINE_2 :    LCD_voidWriteCommand ( 0xC0 + Copy_u8Position );      break;  //First position at Line_2 is 0xC0 Address at DDRAM
            default     :                                                          break;
        }        
    }
}



void LCD_voidDrawPattern ( u8 Copy_u8Pattern_Number , u8 *Copy_u8Arr_Pattern )
{
    LCD_voidWriteCommand ( Copy_u8Pattern_Number );

    for ( u8 i=0 ; i < 8 ; i++ )
    {
        LCD_voidWriteChar ( Copy_u8Arr_Pattern[i] );
    }
}




void LCD_voidWritePattern ( u8 Copy_u8Pattern , u8 Copy_u8Line , u8 Copy_u8Position )
{
    LCD_voidGoTo_XY ( Copy_u8Line , Copy_u8Position );
    LCD_voidWriteChar ( Copy_u8Pattern );
}





void LCD_voidClearDisplay (void)
{
    LCD_voidWriteCommand ( DIS_CLEAR );
    LCD_voidGoTo_XY(0,0);
}





void LCD_voidShiftLeft (void)
{
    LCD_voidWriteCommand ( ENTRY_MODE_INCREASE_LEFT_SHIFT );
}




void LCD_voidShiftRight (void)
{
    LCD_voidWriteCommand ( ENTRY_MODE_DECREASE_RIGHT_SHIFT );
}



