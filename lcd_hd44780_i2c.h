
#ifndef LCD_1602_I2C_H
#define LCD_1602_I2C_H 120

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

//#include "stm32f3xx_hal.h"
#include "stm32f4xx_hal.h"



#define PIN_RS    (1 << 0)
#define PIN_EN    (1 << 2)
#define BACKLIGHT (1 << 3)

#define LCD_DELAY_MS 5

#define LCD_BIT_RS                 ((uint8_t)0x01U)
#define LCD_BIT_RW                 ((uint8_t)0x02U)
#define LCD_BIT_E                  ((uint8_t)0x04U)
#define LCD_BIT_BACKIGHT_ON        ((uint8_t)0x01U)
#define LCD_BIT_BACKIGHT_OFF       ((uint8_t)0x00U)

#define LCD_FUNC_SET               ((uint8_t)0x20U)
#define LCD_MODE_4BITS             ((uint8_t)0x02U)
#define LCD_MODE_8BITS             ((uint8_t)0x10U)
#define LCD_BIT_1LINE              ((uint8_t)0x00U)
#define LCD_BIT_2LINE              ((uint8_t)0x08U)
#define LCD_BIT_4LINE              LCD_BIT_2LINE
#define LCD_BIT_5x8DOTS            ((uint8_t)0x00U)
#define LCD_BIT_5x10DOTS           ((uint8_t)0x04U)
#define LCD_BIT_SETCGRAMADDR       ((uint8_t)0x40U)
#define LCD_BIT_SETDDRAMADDR       ((uint8_t)0x80U)

#define LCD_BIT_DISPLAY_CONTROL    ((uint8_t)0x08U)
#define LCD_BIT_DISPLAY_ON         ((uint8_t)0x04U)
#define LCD_BIT_CURSOR_ON          ((uint8_t)0x02U)
#define LCD_BIT_CURSOR_OFF         ((uint8_t)0x00U)
#define LCD_BIT_BLINK_ON           ((uint8_t)0x01U)
#define LCD_BIT_BLINK_OFF          ((uint8_t)0x00U)

#define LCD_BIT_DISP_CLEAR         ((uint8_t)0x01U)
#define LCD_BIT_CURSOR_HOME        ((uint8_t)0x02U)

#define LCD_BIT_ENTRY_MODE         ((uint8_t)0x04U)
#define LCD_BIT_CURSOR_DIR_RIGHT   ((uint8_t)0x02U)
#define LCD_BIT_CURSOR_DIR_LEFT    ((uint8_t)0x00U)
#define LCD_BIT_DISPLAY_SHIFT      ((uint8_t)0x01U)

// TODO: Update commands with this defines
#define LCD_BIT_CURSOR_SHIFT_MODE  ((uint8_t)0x10U)
#define LCD_BIT_CURSOR_DISP_SHIFT  ((uint8_t)0x08U)
#define LCD_BIT_CURSOR_MOVE        ((uint8_t)0x00U)
#define LCD_BIT_CURSOR_SHIFT_DIR_R ((uint8_t)0x40U)
#define LCD_BIT_CURSOR_SHIFT_DIR_L ((uint8_t)0x00U)


/* Function defines */
#define lcdBacklightOn()           lcdBacklight(LCD_BIT_BACKIGHT_ON)
#define lcdBacklightOff()          lcdBacklight(LCD_BIT_BACKIGHT_OFF)
//#define lcdAutoscrollOn()          lcdCommand(LCD_DISPLAY_SHIFT, LCD_PARAM_SET)
//#define lcdAutoscrollOff()         lcdCommand(LCD_DISPLAY_SHIFT, LCD_PARAM_UNSET)
#define lcdDisplayClear()          LCD_SendCommand(LCD_BIT_DISP_CLEAR)
//#define lcdDisplayOn()             lcdCommand(LCD_DISPLAY, LCD_PARAM_SET)
//#define lcdDisplayOff()            lcdCommand(LCD_DISPLAY, LCD_PARAM_UNSET)
//#define lcdCursorOn()              lcdCommand(LCD_CURSOR, LCD_PARAM_SET)
//#define lcdCursorOff()             lcdCommand(LCD_CURSOR, LCD_PARAM_UNSET)
//#define lcdBlinkOn()               lcdCommand(LCD_CURSOR_BLINK, LCD_PARAM_SET)
//#define lcdBlinkOff()              lcdCommand(LCD_CURSOR_BLINK, LCD_PARAM_UNSET)
//#define lcdCursorDirToRight()      lcdCommand(LCD_CURSOR_DIR_RIGHT, LCD_PARAM_SET)
//#define lcdCursorDirToLeft()       lcdCommand(LCD_CURSOR_DIR_LEFT, LCD_PARAM_SET)
#define lcdCursorHome()            LCD_SendCommand(LCD_BIT_CURSOR_HOME)




typedef enum {
    LCD_BACKLIGHT = 0,
    LCD_DISPLAY,
    LCD_CLEAR,
    LCD_CURSOR,
    LCD_CURSOR_BLINK,
    LCD_CURSOR_HOME,
    LCD_CURSOR_DIR_LEFT,
    LCD_CURSOR_DIR_RIGHT,
    LCD_DISPLAY_SHIFT
} LCDCommands;


void LCD_Init(I2C_HandleTypeDef hndi2c, UART_HandleTypeDef hnduart, uint8_t lcd_addr);
HAL_StatusTypeDef LCD_SendInternal(uint8_t data, uint8_t flags);
void LCD_SendCommand(uint8_t cmd);
void LCD_SetCursor(uint8_t row, uint8_t col);
void LCD_SendData(uint8_t data);
void LCD_SendString(char *str) ;

uint8_t I2C_Scan(I2C_HandleTypeDef hndi2c, UART_HandleTypeDef hnduart);
void lcdBacklight(uint8_t data);

/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif
