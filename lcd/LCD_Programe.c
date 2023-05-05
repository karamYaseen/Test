/*********************************************************************************************/
/*************************** Name     :  Karam Yaseen   **************************************/
/*************************** Data     :  4/5/2023       **************************************/
/*************************** SWC      :  LCD            **************************************/
/*************************** E_Mail   :  karamyaseen725@gmail.com    *************************/
/*************************** version  :  1.0            **************************************/
/*********************************************************************************************/

/*
 * RS: Register Select, Data/Instruction select, driven
       high for data, and low for instruction.
*/

#include "BIT_MATH.h"
#include "Error_State.h"
#include "DIO_Confiq.h"
#include "DIO_Private.h"
#include "DIO_Interface.h"
#include "LCD_Confiq.h"
#include "LCD_Private.h"

#include <util/delay.h>

#define F_CPU 1000000UL


ES_t LCD_enu_SendCommand  (u8 Copy_u8_command)
 {

	/*RS=0*/
	DIO_enu_SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_RS_PIN,DIO_u8_LOW);
	/*RW=0*/
	DIO_enu_SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_RW_PIN,DIO_u8_LOW);

	DIO_enu_SetPortValue(LCD_u8_DATA_PORT,Copy_u8_command);
	/*Sending enable signal*/
	DIO_enu_SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_E_PIN,DIO_u8_HIGH);
	_delay_us(1);
	DIO_enu_SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_E_PIN,DIO_u8_LOW);
	//_delay_us(200);

	return STD_TYPES_OK;
}


ES_t LCD_enu_Init(void)
 {

/*Directions of Rs-Rw-E*/
	DIO_enu_SetPinDirection(LCD_u8_CONTROL_PORT,LCD_u8_RS_PIN,DIO_u8_INITIAL_OUTPUT);
	DIO_enu_SetPinDirection(LCD_u8_CONTROL_PORT,LCD_u8_RW_PIN,DIO_u8_INITIAL_OUTPUT);
	DIO_enu_SetPinDirection(LCD_u8_CONTROL_PORT,LCD_u8_E_PIN,DIO_u8_INITIAL_OUTPUT);
	DIO_enu_SetPortDirection(LCD_u8_DATA_PORT,DIO_u8_INITIAL_OUTPUT);

	DIO_enu_SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_RS_PIN,DIO_u8_OUTPUT_LOW);
	DIO_enu_SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_RW_PIN,DIO_u8_OUTPUT_LOW);
	DIO_enu_SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_E_PIN,DIO_u8_OUTPUT_LOW);
	DIO_enu_SetPortValue(LCD_u8_DATA_PORT,DIO_u8_OUTPUT_LOW);

	_delay_ms(35);

	LCD_enu_SendCommand(LCD_FUNCTION_SET); /*Function Set*/
	_delay_us(40);

	LCD_enu_SendCommand(LCD_DISPLAY_CONTROL);
	_delay_us(40);

	LCD_enu_SendCommand(LCD_CLEAR_SCREEN); /*Clear screen*/
	_delay_ms(2);

	LCD_enu_SendCommand(LCD_ENTRY_MODE);

	return STD_TYPES_OK;
}

ES_t LCD_enu_WriteCharacter(u8 Copy_u8_char)
{
	DIO_enu_SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_RS_PIN,DIO_u8_HIGH);
	DIO_enu_SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_RW_PIN,DIO_u8_LOW);

	DIO_enu_SetPortValue(LCD_u8_DATA_PORT,Copy_u8_char);

	DIO_enu_SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_E_PIN,DIO_u8_HIGH);
	_delay_ms(2);
	DIO_enu_SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_E_PIN,DIO_u8_LOW);
	_delay_ms(2);
	DIO_enu_SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_E_PIN,DIO_u8_HIGH);

	return STD_TYPES_OK;

}

ES_t LCD_enu_WriteString(s8 * Copy_ps8_String)
 {	
	do {
		LCD_enu_WriteCharacter(*Copy_ps8_String);
		(Copy_ps8_String++);
	}while(*Copy_ps8_String != '\0');

	return STD_TYPES_OK;
 }

ES_t LCD_enu_WriteSizedString(s8 * Copy_ps8_String,u8 Copy_u8_size)
{	
	u8 Copy_u8_iterator = 0;
	do {
		LCD_enu_WriteCharacter(*Copy_ps8_String);
		(Copy_ps8_String++);
		Copy_u8_iterator++;
	}while(Copy_u8_size > Copy_u8_iterator);

	return STD_TYPES_OK;
}

ES_t LCD_enu_WriteNumber(u16 Copy_u16_Number)
{
	
	if(Copy_u16_Number < 10) {
		LCD_enu_WriteCharacter('0');
		LCD_enu_WriteCharacter(Copy_u16_Number+'0');
	}
	else {
		if (Copy_u16_Number < 100) {
			LCD_enu_WriteCharacter(Copy_u16_Number/10+'0');
			LCD_enu_WriteCharacter(Copy_u16_Number%10+'0');
		}
		else if (Copy_u16_Number < 1000) {
			LCD_enu_WriteCharacter((Copy_u16_Number/100)+'0');
			LCD_enu_WriteCharacter((Copy_u16_Number%100)/10+'0');
			LCD_enu_WriteCharacter((Copy_u16_Number%100)%10+'0');
		}
		else if (Copy_u16_Number < 10000)
		{
			LCD_enu_WriteCharacter((Copy_u16_Number/1000)+'0');
			LCD_enu_WriteCharacter((Copy_u16_Number%1000)/100+'0');
			LCD_enu_WriteCharacter((Copy_u16_Number%100)/10+'0');
			LCD_enu_WriteCharacter((Copy_u16_Number%100)%10+'0');
		}
	}

	return STD_TYPES_OK;
}

ES_t LCD_enu_WriteSizedNumber(u16 Copy_u16_Number, u8 Copy_u8_size)
{
	u8 Copy_u8_iterator;
	if(Copy_u16_Number < 10) {
		for (Copy_u8_iterator = 0; Copy_u8_iterator < Copy_u8_size-1; Copy_u8_iterator++)
		{		
			LCD_enu_WriteCharacter('0');
		}
		LCD_enu_WriteCharacter(Copy_u16_Number+'0');
	}
	else {
		if (Copy_u16_Number < 100) {
			for (Copy_u8_iterator = 0; Copy_u8_iterator < Copy_u8_size-2; Copy_u8_iterator++)
			{		
				LCD_enu_WriteCharacter('0');
			}

			LCD_enu_WriteCharacter(Copy_u16_Number/10+'0');
			LCD_enu_WriteCharacter(Copy_u16_Number%10+'0');
		}
		else if (Copy_u16_Number < 1000) {
			for (Copy_u8_iterator = 0; Copy_u8_iterator < Copy_u8_size-3; Copy_u8_iterator++)
			{		
				LCD_enu_WriteCharacter('0');
			}
			LCD_enu_WriteCharacter((Copy_u16_Number/100)+'0');
			LCD_enu_WriteCharacter((Copy_u16_Number%100)/10+'0');
			LCD_enu_WriteCharacter((Copy_u16_Number%100)%10+'0');
		}
		else if (Copy_u16_Number < 10000)
		{
			for (Copy_u8_iterator = 0; Copy_u8_iterator < Copy_u8_size-4; Copy_u8_iterator++)
			{		
				LCD_enu_WriteCharacter('0');
			}
			LCD_enu_WriteCharacter((Copy_u16_Number/1000)+'0');
			LCD_enu_WriteCharacter((Copy_u16_Number%1000)/100+'0');
			LCD_enu_WriteCharacter((Copy_u16_Number%100)/10+'0');
			LCD_enu_WriteCharacter((Copy_u16_Number%100)%10+'0');
		}
	}

	return STD_TYPES_OK;
}

ES_t LCD_enu_GoToXY(u8 Copy_u8_LineNumber, u8 Copy_u8_Location) {
	if(Copy_u8_Location<=MAX_LOCATION)
	{
		switch(Copy_u8_LineNumber) {
			case LCD_u8_LINE0:LCD_enu_SendCommand(ADDRESS_OF_LINE1+Copy_u8_Location);break;
			case LCD_u8_LINE1:LCD_enu_SendCommand(ADDRESS_OF_LINE0+Copy_u8_Location);break;
			default: return STD_TYPES_NOK;
		}
	}else{
		return STD_TYPES_NOK;
	}
	return STD_TYPES_OK;
}

ES_t LCD_enu_CreateCustomChar(u8 * Copy_pu8_Char, u8 Copy_u8_Location) {
	u8 Copy_u8_iterator = INITIAL_VALUE;
	LCD_enu_SendCommand(0x40+(Copy_u8_Location*COLS_NUMBER)); /*Command 0x40 and onwards forces to point CGRAM address*/
	while (Copy_u8_iterator != COLS_NUMBER) {
		LCD_enu_WriteCharacter(*Copy_pu8_Char++);
		Copy_u8_iterator++;
	}
	LCD_enu_WriteCharacter(0x00+Copy_u8_Location);
	return STD_TYPES_OK;
}

ES_t LCD_vidClearSpace(u8 Copy_u8_xPosStart, u8 Copy_u8_xPosEnd ,u8 Copy_u8_yPos)
{
	u8 Copy_u8_iterator = INITIAL_VALUE;
	LCD_enu_GoToXY(Copy_u8_xPosStart,Copy_u8_yPos);
	for (Copy_u8_iterator = 0; Copy_u8_iterator < Copy_u8_xPosEnd; Copy_u8_iterator++)
	{
		LCD_enu_WriteCharacter(' ');
	}
	LCD_enu_GoToXY(Copy_u8_xPosStart,Copy_u8_yPos);
	return STD_TYPES_OK;
}

ES_t LCD_enu_Clear(void){
	LCD_enu_SendCommand(LCD_CLEAR_SCREEN);
	return STD_TYPES_OK;
}
