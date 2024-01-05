/*
 * timer1.h
 *
 *  Created on: Oct 28, 2023
 *      Author: youss
 */
#include "std_types.h"

#ifndef TIMER1_H_
#define TIMER1_H_
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
typedef enum
{
    no_clock,
    prescalar_1,
    prescalar_8,
    prescalar_64,
    prescalar_256,
    prescalar_1024,
    Ext_on_falling,
    Ext_on_rising
} Timer1_Prescaler;

typedef enum
{
    normal,
    compare
} Timer1_Mode;

typedef struct {
    uint16 initial_value;
    uint16 compare_value;
    Timer1_Prescaler prescaler;
    Timer1_Mode mode;
} Timer1_ConfigType;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * initialize timer1 with configuration
 *
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr);

void Timer1_deInit(void);

void Timer1_setCallBack(void(*a_ptr)(void));

#endif /* TIMER1_H_ */
