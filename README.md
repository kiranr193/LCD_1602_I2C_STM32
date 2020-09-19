# LCD_1602_I2C_STM32
LCD Driver for 1602 charecter display using I2C plugin with STM32407 

Working revision tested with STM32F407VET6 configured to use I2C1 for communication and UART2 for debug. The I2C chip connected is PCF8574T with address 0x27. 
By changing the header file for micro-controller can be used with Blue Pill board too.

#define LCD_ADDR (0x27 << 1)

void init() 
{
    LCD_Init(hi2c1, huart2, LCD_ADDR);
    lcdBacklightOff();
    //I2C_Scan();
    // set address to 0x00
    LCD_SetCursor(0, 0);
    LCD_SendString("HELLO EVERYONE");
    // set address to 0x40
    LCD_SetCursor(1, 0);
    LCD_SendString("TESTING PROGRAM...");
}
