/************************************************************************
 * Module: dc_motor Driver
 *
 * File Name: dc_motor.h
 *
 * Description: Header File For dc_motor Driver
 *
 * Author:	Youssef Amr
 *
 * Date: 03/11/2023
 *
 *************************************************************************/
#include "dc_motor.h"
#include "gpio.h"
#include <avr/io.h>

void PWM_Timer0_Init(unsigned char set_duty_cycle)
{

	TCNT0 = 0; //Set Timer Initial value

	OCR0  = set_duty_cycle; // Set Compare Value

	DDRB  = DDRB | (1<<PB3); //set PB3/OC0 as output pin --> pin where the PWM signal is generated from MC.

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);
}
/*
 * Function Name: DcMotor_init
 * Description:
 * 	The Function responsible for setup the direction for the two
 *	motor pins through the GPIO driver.
 *	Stop at the DC-Motor at the beginning through the GPIO driver.
 */
void DcMotor_init(void)
{
	/* Make Motor which connected to motor O/P pins*/
	GPIO_setupPinDirection(DC_MOTORT_PORT_ID,DC_MOTOR_INPUT_FIRST_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTORT_PORT_ID,DC_MOTOR_INPUT_SECOND_PIN_ID,PIN_OUTPUT);
	/*	Write LOW to make motor in Stop mode*/
	GPIO_writePin(DC_MOTORT_PORT_ID,DC_MOTOR_INPUT_FIRST_PIN_ID,LOGIC_LOW);
	GPIO_writePin(DC_MOTORT_PORT_ID,DC_MOTOR_INPUT_SECOND_PIN_ID,LOGIC_LOW);
}
/*
 * Function Name: DcMotor_Rotate()
 * Description:
 * 	The function responsible for rotate the DC Motor CW/ or A-CW or
 *	stop the motor based on the state input state value.
 *	Send the required duty cycle to the PWM driver based on the
 *  required speed value.
 */
void DcMotor_Rotate(DcMotor_State  state ,uint8 speed)
{
	/****Choose Configuration of Timer0 in DcMotor ,Beacuse in Main i'm Just deal with HAL*****/
	/*
	 * 1.Fast PWM MODE
	 * 2.Non Inverting
	 * 3.Prescaler 8
	 */
	PWM_Timer0_Init(speed);
	/*Choose How DC_Motor Rotate CCW , CW ,Stop*/
	if(state==Stop)
	{
		/*Stop A=0  , B=0*/
		GPIO_writePin(DC_MOTORT_PORT_ID,DC_MOTOR_INPUT_FIRST_PIN_ID,LOGIC_LOW);
		GPIO_writePin(DC_MOTORT_PORT_ID,DC_MOTOR_INPUT_SECOND_PIN_ID,LOGIC_LOW);
	}
	else if(state==Clock_Wise)
	{
		/* CW A=1 ,B=0*/
		GPIO_writePin(DC_MOTORT_PORT_ID,DC_MOTOR_INPUT_FIRST_PIN_ID,LOGIC_HIGH);
		GPIO_writePin(DC_MOTORT_PORT_ID,DC_MOTOR_INPUT_SECOND_PIN_ID,LOGIC_LOW);
	}
	else if(state==Anti_Clock_Wise)
	{
		/*Anti CCW A=0 ,B=1 */
		GPIO_writePin(DC_MOTORT_PORT_ID,DC_MOTOR_INPUT_FIRST_PIN_ID,LOGIC_LOW);
		GPIO_writePin(DC_MOTORT_PORT_ID,DC_MOTOR_INPUT_SECOND_PIN_ID,LOGIC_HIGH);
	}
}

