/*********************************************************************************************/
/*************************** Name     :  Karam Yaseen   **************************************/
/*************************** Data     :  4/5/2023       **************************************/
/*************************** SWC      :  LCD            **************************************/
/*************************** E_Mail   :  karamyaseen725@gmail.com    *************************/
/*************************** version  :  1.0            **************************************/
/*********************************************************************************************/

#ifndef LCD_Interface_H
#define LCD_Interface_H

#define LCD_SET_CURSOR_LOCATION    0x80


/*Deprecated definitions*/

#define LCD_ENTRY_MODE      0b00000110
#define LCD_DISPLAY_CONTROL 0b00001100
#define LCD_FUNCTION_SET    0b00111000
#define LCD_CLEAR_SCREEN    0b00000001


/*Display on/off control */
#define LCD_DISPLAY_ON  0x0C
#define LCD_DISPLAY_OFF 0x08

#define LCD_CURSOR_ON  0x0A
#define LCD_CURSOR_OFF 0x08

#define LCD_CURSOR_BLINK_ON  0x09
#define LCD_CURSOR_BLINK_OFF 0x08


/*Function definitions*/
ES_t LCD_enu_Init           	(void);

ES_t LCD_enu_SendCommand    	(u8 Copy_u8_command);

ES_t LCD_enu_WriteCharacter 	(u8 Copy_u8_char);

ES_t LCD_enu_WriteString    	(s8 * Copy_ps8_String);

ES_t LCD_enu_WriteSizedString   (s8 * Copy_ps8_String,u8 Copy_u8_size);

ES_t LCD_enu_WriteNumber        (u16 Copy_u16_Number);

ES_t LCD_enu_WriteSizedNumber   (u16 Copy_u16_Number, u8 Copy_u8_size);

ES_t LCD_enu_SetCursor(u8 Copy_u8_LineNum,u8 Copy_u8_Location);

ES_t LCD_enu_Clear(void);

#endif
