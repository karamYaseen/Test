#include "STD_TYPES.h"
#include "DIO_Confiq.h"
#include "DIO_Private.h"
#include "LCD_Private.h"
#include "LCD_Confiq.h"
int main(void){



	DIO_enu_Init();
	LCD_enu_Init();
	LCD_enu_GoToXY(0, 0);
	LCD_enu_WriteNumber(2023);
	LCD_enu_WriteString("IEEE-ZSB-RAS ");
	LCD_enu_GoToXY(1, 2);
	LCD_enu_WriteString("Karam Yaseen");


	while(1){
	};



	return 0;
}
