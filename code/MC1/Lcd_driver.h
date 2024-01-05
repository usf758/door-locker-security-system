/*
 * Lcd_driver.h
 *
 *  Created on: Sep 30, 2023
 *      Author: youss
 */
#include "std_types.h"

#ifndef LCD_DRIVER_H_
#define LCD_DRIVER_H_

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define lcdbits                        8
#define LCD_RS_PORT_ID                 PORTB_ID
#define LCD_RS_PIN_ID                  PIN0_ID

#define LCD_E_PORT_ID                  PORTB_ID
#define LCD_E_PIN_ID                   PIN1_ID

#define LCD_DATA_PORT_ID               PORTA_ID


#define LCD_DB4_PIN_ID                 PIN3_ID
#define LCD_DB5_PIN_ID                 PIN4_ID
#define LCD_DB6_PIN_ID                 PIN5_ID
#define LCD_DB7_PIN_ID                 PIN6_ID


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

void LCD_sendcommand(uint8 command);
void lcd_init(void);
void lcd_displayCharacter(uint8 data);
void lcd_displaystring(uint8 *str);
void LCD_movecursor(uint8 col,uint8 row);
void lcd_displayrowcolumn(uint8 *str,uint8 row,uint8 col);
void lcd_intgertostring(int data);
void LCD_clearScreen(void);



#endif /* LCD_DRIVER_H_ */
