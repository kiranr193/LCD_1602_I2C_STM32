#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "lcd_hd44780_i2c.h"

I2C_HandleTypeDef hi2c;
uint8_t  lcdAddr;
UART_HandleTypeDef huart;
uint8_t  lcdBackLight = 1;

void lcdBacklight(uint8_t data)
{
	lcdBackLight = data;
}

uint8_t I2C_Scan(I2C_HandleTypeDef hndi2c, UART_HandleTypeDef hnduart) {
    char info[] = "Scanning I2C bus...\r\n";
    uint8_t retVal = 255;
    HAL_UART_Transmit(&hnduart, (uint8_t*)info, strlen(info), HAL_MAX_DELAY);

    HAL_StatusTypeDef res;
    for(uint16_t i = 0; i < 128; i++) {
        res = HAL_I2C_IsDeviceReady(&hndi2c, i << 1, 1, 10);
        if(res == HAL_OK) {
            char msg[64];
            snprintf(msg, sizeof(msg), "0x%02X", i);
            HAL_UART_Transmit(&hnduart, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
            retVal = i;
        } else {
            HAL_UART_Transmit(&hnduart, (uint8_t*)".", 1, HAL_MAX_DELAY);

        }
    }

    HAL_UART_Transmit(&hnduart, (uint8_t*)"\r\n", 2, HAL_MAX_DELAY);
    return retVal;
}

HAL_StatusTypeDef LCD_SendInternal(uint8_t data, uint8_t flags) {
    HAL_StatusTypeDef res;
    for(;;) {
        res = HAL_I2C_IsDeviceReady(&hi2c, lcdAddr, 1, HAL_MAX_DELAY);
        if(res == HAL_OK)
            break;
    }

    uint8_t up = data & 0xF0;
    uint8_t lo = (data << 4) & 0xF0;

    uint8_t data_arr[4];
    if(lcdBackLight) {
		data_arr[0] = up | flags | BACKLIGHT | PIN_EN;
		data_arr[1] = up | flags | BACKLIGHT;
		data_arr[2] = lo | flags | BACKLIGHT | PIN_EN;
		data_arr[3] = lo | flags | BACKLIGHT;
	} else {
		data_arr[0] = up | flags | PIN_EN;
		data_arr[1] = up | flags;
		data_arr[2] = lo | flags | PIN_EN;
		data_arr[3] = lo | flags;
	}

    res = HAL_I2C_Master_Transmit(&hi2c, lcdAddr, data_arr, sizeof(data_arr), HAL_MAX_DELAY);
    HAL_Delay(LCD_DELAY_MS);
    return res;
}

void LCD_SetCursor(uint8_t row, uint8_t col) {
	uint8_t rowcode[2] = {0x0,0x40};
	uint8_t code = (uint8_t)(col + rowcode[row]);
	LCD_SendCommand(LCD_BIT_SETDDRAMADDR | code);
}
void LCD_SendCommand(uint8_t cmd) {
    LCD_SendInternal(cmd, 0);
}

void LCD_SendData(uint8_t data) {
    LCD_SendInternal(data, PIN_RS);
}

void LCD_Init(I2C_HandleTypeDef hndi2c, UART_HandleTypeDef hnduart, uint8_t lcd_addr) {
	hi2c = hndi2c;
	huart = hnduart;
	lcdAddr = lcd_addr;
    // 4-bit mode, 2 lines, 5x7 format
    LCD_SendCommand(LCD_FUNC_SET|LCD_MODE_8BITS);
    // display & cursor home (keep this!)
    LCD_SendCommand(LCD_BIT_CURSOR_HOME);
    // display on, right shift, underline off, blink off
    LCD_SendCommand(LCD_BIT_DISPLAY_ON | LCD_BIT_CURSOR_DIR_RIGHT | LCD_BIT_BLINK_OFF);
    // clear display (optional here)
    LCD_SendCommand( LCD_BIT_DISP_CLEAR);
}

void LCD_SendString(char *str) {
    while(*str) {
        LCD_SendData((uint8_t)(*str));
        str++;
    }
}
