/* ==================================================================
 * Module: Buzzer Driver
 *
 * File Name: buzzer.c
 *
 * Description: Source File for Buzzer driver.
 *
 * Author: Yousef Amr
 *
 * Date: 03/11/2023
 * ====================================================================*/

#include "buzzer.h"
#include "gpio.h"

/*
 * Function Name: BUZZER_init
 * Description: Setup Buzzer_pin as output pin  and turn off the buzzer
 */
void BUZZER_init(void)
{
	/* Make BuzzerPin as output pin*/
	GPIO_setupPinDirection(BUZZER_PORT , BUZZER_PIN , PIN_OUTPUT);
	/* Buzzer of at first*/
	GPIO_writePin(BUZZER_PORT , BUZZER_PIN , LOGIC_LOW);
}

/*
 * Function Name: BUZZER_On()
 * Description :  enable the Buzzer through the GPIO
 */
void BUZZER_On(void)
{
	GPIO_writePin(BUZZER_PORT , BUZZER_PIN , LOGIC_HIGH);
}
/*
 * Function Name: BUZZER_Off()
 * Description:  disable the Buzzer through the GPIO.
 */
void BUZZER_Off(void)
{
	GPIO_writePin(BUZZER_PORT , BUZZER_PIN , LOGIC_LOW);
}
