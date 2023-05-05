/*********************************************************************************************/
/*************************** Name     :  Karam Yaseen   **************************************/
/*************************** Data     :  4/5/2023       **************************************/
/*************************** SWC      :  LCD            **************************************/
/*************************** E_Mail   :  karamyaseen725@gmail.com    *************************/
/*************************** version  :  1.0            **************************************/
/*********************************************************************************************/

#ifndef LCD_Private_H
#define LCD_Private_H

/*Deprecated definitions*/

#define LCD_ENTRY_MODE      0b00000110
#define LCD_DISPLAY_CONTROL 0b00001100
#define LCD_FUNCTION_SET    0b00111000
#define LCD_CLEAR_SCREEN    0b00000001

#define LCD_u8_LINE0                   0
#define LCD_u8_LINE1                   1
#define ADDRESS_OF_LINE0               0xc0
#define ADDRESS_OF_LINE1               0x80

#define MAX_LOCATION 39
#define COLS_NUMBER  8
#define ROWS_NUMBER  2



#endif
