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
************************************************************************/


#ifndef dc_motor_H_
#define dc_motor_H_
#include "std_types.h"
/***********************************************************
 * 					Definitions							   *
 **********************************************************/
#define	DC_MOTORT_PORT_ID					PORTB_ID

#define DC_MOTOR_INPUT_FIRST_PIN_ID			PIN1_ID
#define DC_MOTOR_INPUT_SECOND_PIN_ID		PIN2_ID


typedef enum{
	Stop , Anti_Clock_Wise ,Clock_Wise
}DcMotor_State;

/***********************************************************
 * 					Functions Prototypes				   *
 **********************************************************/
void PWM_Timer0_Init(unsigned char set_duty_cycle);
void DcMotor_init(void);
void DcMotor_Rotate(DcMotor_State state ,uint8 speed);
#endif /* DC_MOTOR_H_ */
