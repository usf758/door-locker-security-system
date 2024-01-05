/*
 * Lcd_driver.c
 *
 *  Created on: Sep 30, 2023
 *      Author: youss
 */

#include"Lcd_driver.h"
#include"common_macros.h"
#include"gpio.h"
#include <util/delay.h>

void lcd_sendCommand(uint8 command){
	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);
	_delay_ms(1);
#if(lcdbits == 4)

	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(command,4));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(command,5));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(command,6));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(command,7));

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(command,0));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(command,1));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(command,2));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(command,3));

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */

#elif(lcdbits == 8)
	GPIO_writePort(LCD_DATA_PORT_ID,command);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	_delay_ms(1);

#endif
}

void lcd_displayCharacter(uint8 data){
	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_HIGH);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);
	_delay_ms(1);

#if(lcdbits == 4)
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(data,4));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(data,5));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(data,6));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(data,7));

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(data,0));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(data,1));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(data,2));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(data,3));

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */

#elif(lcdbits == 8)
	GPIO_writePort(LCD_DATA_PORT_ID,data);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	_delay_ms(1);

#endif
}


void lcd_init(void){
	GPIO_setupPinDirection(LCD_RS_PORT_ID,LCD_RS_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_E_PORT_ID,LCD_E_PIN_ID,PIN_OUTPUT);
	_delay_ms(20);

#if(lcdbits == 4)
	/* Configure 4 pins in the data port as output pins */
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,PIN_OUTPUT);

	/* Send for 4 bit initialization of LCD  */
	lcd_sendCommand(0X33);
	lcd_sendCommand(0X32);

	/* use 2-lines LCD + 4-bits Data Mode + 5*7 dot display Mode */
	lcd_sendCommand(0X28);

#elif(lcdbits == 8)

	GPIO_setupPortDirection(LCD_DATA_PORT_ID,PORT_OUTPUT);
	lcd_sendCommand(0X38);

#endif
	lcd_sendCommand(0X0C);
	lcd_sendCommand(0X01);
}
void lcd_displaystring(uint8 *str)
{
	for(int i=0;str[i]!='\0';i++)
	{
		lcd_displayCharacter(str[i]);
	}
}

void LCD_movecursor(uint8 row,uint8 col)
{
	uint8 lcd_memoryaddress;
	switch(row)
	{
	case 0:
		lcd_memoryaddress=col;
		break;
	case 1:
		lcd_memoryaddress=col+0x40;
		break;
	case 2:
		lcd_memoryaddress=col+0x10;
		break;
	case 3:
		lcd_memoryaddress=col+0x50;
		break;
	}
	lcd_sendCommand(lcd_memoryaddress | 0X80);

}
void lcd_displayrowcolumn(uint8 *str,uint8 row,uint8 col)
{
	LCD_movecursor(row,col);
	lcd_displaystring(str);
}
void lcd_clearscreen()
{
	lcd_sendCommand(0X01);
}

void lcd_intgertostring(int data)
{
	char buffer[16];
	itoa(data,buffer,10);
	lcd_displaystring(buffer);
}
void LCD_clearScreen(void)
{
	lcd_sendCommand(0x01);
}
