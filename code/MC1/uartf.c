/******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.c
 *
 * Description: Source file for the UART AVR driver. I modified the one in the course
 *
 * Author: Youssef Amr
 *
 *******************************************************************************/

#include "uartf.h"

#include "avr/io.h" /* To use the UART Registers */
#include "common_macros.h" /* To use the macros like SET_BIT */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType * Config_Ptr)
{
	uint16 ubrr_value = 0;

	/* U2X = 1 for double transmission speed */
	UCSRA = (1<<U2X);

	/************************** UCSRB Description **************************
	 * RXCIE = 0 Disable USART RX Complete Interrupt Enable
	 * TXCIE = 0 Disable USART Tx Complete Interrupt Enable
	 * UDRIE = 0 Disable USART Data Register Empty Interrupt Enable
	 * RXEN  = 1 Receiver Enable
	 * RXEN  = 1 Transmitter Enable
	 * UCSZ2 = 0 For 8-bit data mode
	 * RXB8 & TXB8 not used for 8-bit data mode
	 ***********************************************************************/ 
	UCSRB = (1<<RXEN) | (1<<TXEN);

	/************************** UCSRC Description **************************
	 * URSEL   = 1 The URSEL must be one when writing the UCSRC
	 * parity bit,bit_data,stop_bit,baud_rate is selected
	 ***********************************************************************/ 	
	UCSRC = (1<<URSEL);
	switch(Config_Ptr->parity)
	{
	case 0:

		break;
	case 1:
		UCSRC |= (1<<UPM0);
		break;
	case 2:
		UCSRC |= (1<<UPM1);
		break;
	case 3:
		UCSRC |= (1<<UPM1) | (1<<UPM0);
		break;
	}

	switch(Config_Ptr->stop_bit)
	{
	case 0:
		break;
	case 1:
		UCSRC |= (1<<USBS);
		break;
	}


	switch(Config_Ptr->bit_data)
	{
	case 0:
		break;
	case 1:
		UCSRC |= (1<<UCSZ0);
		break;
	case 2:
		UCSRC |= (1<<UCSZ1);
		break;
	case 3:
		UCSRC |= (1<<UCSZ0) | (1<<UCSZ1);
		break;
	case 4:
		UCSRC |= (1<<UCSZ2);
		break;
	case 5:
		UCSRC |= (1<<UCSZ0) | (1<<UCSZ2);
		break;
	case 6:
		UCSRC |= (1<<UCSZ1) | (1<<UCSZ2);
		break;
	case 7:
		UCSRC |= (1<<UCSZ1) | (1<<UCSZ2);
		break;
	}

	switch(Config_Ptr->baud_rate)
	{
	case 0:
		ubrr_value = (uint16)(((F_CPU / (9600 * 8UL))) - 1);
		break;
	case 1:
		ubrr_value = (uint32)(((F_CPU / (19200 * 8UL))) - 1);
		break;
	case 2:
		ubrr_value = (uint32)(((F_CPU / (38400 * 8UL))) - 1);
		break;
	case 3:
		ubrr_value = (uint32)(((F_CPU / (115200 * 8UL))) - 1);
		break;
	}


	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	UBRRH = ubrr_value>>8;
	UBRRL = ubrr_value;
}

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data)
{
	/*
	 * UDRE flag is set when the Tx buffer (UDR) is empty and ready for
	 * transmitting a new byte so wait until this flag is set to one
	 */
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}

	/*
	 * Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now
	 */
	UDR = data;

	/************************* Another Method *************************
	UDR = data;
	while(BIT_IS_CLEAR(UCSRA,TXC)){} // Wait until the transmission is complete TXC = 1
	SET_BIT(UCSRA,TXC); // Clear the TXC flag
	 *******************************************************************/
}

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void)
{
	/* RXC flag is set when the UART receive data so wait until this flag is set to one */
	while(BIT_IS_CLEAR(UCSRA,RXC)){}

	/*
	 * Read the received data from the Rx buffer (UDR)
	 * The RXC flag will be cleared after read the data
	 */
	return UDR;
}

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str)
{
	uint8 i = 0;

	/* Send the whole string */
	while(Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}
	/************************* Another Method *************************
	while(*Str != '\0')
	{
		UART_sendByte(*Str);
		Str++;
	}		
	 *******************************************************************/
}

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str)
{
	uint8 i = 0;

	/* Receive the first byte */
	Str[i] = UART_recieveByte();

	/* Receive the whole string until the '#' */
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_recieveByte();
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	Str[i] = '\0';
}
