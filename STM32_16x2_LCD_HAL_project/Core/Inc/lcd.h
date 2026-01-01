#ifndef LCD_H
#define LCD_H

#include "stm32f4xx_hal.h"

void LCD_Init(void);
void LCD_Send_Command(uint8_t cmd);
void LCD_Send_Data(uint8_t data);
void LCD_Send_String(char *str);
void LCD_Set_Cursor(uint8_t row, uint8_t col);

#endif
