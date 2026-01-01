#include "lcd.h"

#define RS_PIN GPIO_PIN_0
#define EN_PIN GPIO_PIN_1
#define D4_PIN GPIO_PIN_2
#define D5_PIN GPIO_PIN_3
#define D6_PIN GPIO_PIN_4
#define D7_PIN GPIO_PIN_5
#define LCD_PORT GPIOA

void LCD_Enable(void)
{
    HAL_GPIO_WritePin(LCD_PORT, EN_PIN, GPIO_PIN_SET);
    HAL_Delay(2);
    HAL_GPIO_WritePin(LCD_PORT, EN_PIN, GPIO_PIN_RESET);
    HAL_Delay(2);
}


void LCD_Send_Nibble(uint8_t nibble)
{
    HAL_GPIO_WritePin(LCD_PORT, D4_PIN, (nibble & 0x01));
    HAL_GPIO_WritePin(LCD_PORT, D5_PIN, (nibble & 0x02));
    HAL_GPIO_WritePin(LCD_PORT, D6_PIN, (nibble & 0x04));
    HAL_GPIO_WritePin(LCD_PORT, D7_PIN, (nibble & 0x08));
    LCD_Enable();
}

void LCD_Send_Command(uint8_t cmd)
{
    HAL_GPIO_WritePin(LCD_PORT, RS_PIN, GPIO_PIN_RESET);
    LCD_Send_Nibble(cmd >> 4);
    LCD_Send_Nibble(cmd & 0x0F);
}

void LCD_Send_Data(uint8_t data)
{
    HAL_GPIO_WritePin(LCD_PORT, RS_PIN, GPIO_PIN_SET);
    LCD_Send_Nibble(data >> 4);
    LCD_Send_Nibble(data & 0x0F);
}

void LCD_Init(void)
{
    HAL_Delay(40); // LCD power-up delay

    HAL_GPIO_WritePin(LCD_PORT, RS_PIN, GPIO_PIN_RESET);

    // Force into 4-bit mode
    LCD_Send_Nibble(0x03);
    HAL_Delay(5);

    LCD_Send_Nibble(0x03);
    HAL_Delay(5);

    LCD_Send_Nibble(0x03);
    HAL_Delay(1);

    LCD_Send_Nibble(0x02); // 4-bit mode

    // Function set
    LCD_Send_Command(0x28); // 4-bit, 2 line, 5x8 font
    LCD_Send_Command(0x08); // Display OFF
    LCD_Send_Command(0x01); // Clear display
    HAL_Delay(2);
    LCD_Send_Command(0x06); // Entry mode
    LCD_Send_Command(0x0C); // Display ON, cursor OFF
}

void LCD_Send_String(char *str)
{
    while(*str)
        LCD_Send_Data(*str++);
}

void LCD_Set_Cursor(uint8_t row, uint8_t col)
{
    uint8_t address = (row == 0) ? 0x80 + col : 0xC0 + col;
    LCD_Send_Command(address);
}
