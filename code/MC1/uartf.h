/******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver. I modified the one in the course
 *
 * Author: Youssef Amr
 *
 *******************************************************************************/

#ifndef UARTF_H_
#define UARTF_H_

#include "std_types.h"

typedef enum
{
	Disabled,Reserved,Even_parity,Odd_parity
}UART_Parity;

typedef enum
{
fivebit,sixbit,sevenbit,eightbit,reserved,reserved1,reserved2,ninebit
}UART_BitData;

typedef enum
{
	one_bit,two_bits
}UART_StopBit;

typedef enum
{
	bd9600, bd19200, bd38400, bd115200
}UART_BaudRate;

typedef struct{
	UART_BitData bit_data;
	UART_Parity parity;
	UART_StopBit stop_bit;
	UART_BaudRate baud_rate;
}UART_ConfigType;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType * Config_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UARTF_H_ */
