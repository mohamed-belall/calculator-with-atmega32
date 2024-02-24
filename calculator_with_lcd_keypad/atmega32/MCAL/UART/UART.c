/*
 * UART.c
 *
 * Created: 12/25/2023 8:11:07 PM
 *  Author: Mohamed Belal
 */ 

/* ============================================================================ */
/* ================================= Includes ================================= */
/* ============================================================================ */
#include "UART.h"


/* ============================================================================ */
/* ===========================  Global Variables ============================== */
/* ============================================================================ */



/* ============================================================================ */
/* ==================== APIs Supported by "MCAL ADC DRIVER" =================== */
/* ============================================================================ */
void MCAL_UART_Init(UART_Config_t* UARTCFG)
{
	// 1. set baud rate
	 UBRRL = UARTCFG->UART_BaudRate;
	 
	// 2. disable double speed
	CLEARBIT(UCSRA ,U2X );
	
	// 3. set bit size
	UCSRC |= UARTCFG->UART_DATA_SIZE;
	CLEARBIT(UCSRB , UCSZ2);
	if (UARTCFG->UART_DATA_SIZE == UART_DATA_SIZE_9bit)
	{
		SETBIT(UCSRB , UCSZ2);
	}
	
	// 4. parity mode
	UCSRC |= UARTCFG->UART_Parity_Mode;
	
	// 5. stop bit
	UCSRC |= UARTCFG->UART_STOP_Bit;
	
	// 6. ENABLE/DISABLE INTERRUPT
	UCSRB |= UARTCFG->UART_IRQ;
	if (UARTCFG->UART_IRQ != UART_IRQ_disable)
	{
		sei();
	}
	
	// 7. Enable Sending Receiving 
	SETBIT(UCSRB, RXEN);
	SETBIT(UCSRB, TXEN);
	
}
void MCAL_UART_DEInit(void);

void MCAL_UART_send_data(uint8_t* TxBuffer, Polling_t polling)
{
	if(polling == PollingENABLE)
		while(!READBIT(UCSRA , UDRE));
	
	if (READBIT(UCSRB, UCSZ2))  // 9bit mode
	{
		/*	If 9-bit characters are used (UCSZ = 7),				*/
		/*	the ninth bit must be written to the TXB8 bit in UCSRB	*/
		/*	before the low byte of the character is written to UDR.	*/
		UCSRB &= ~(1<<TXB8); 
		if((*TxBuffer & (1<<8)))
			UCSRB |= (1<<TXB8); 
			
		UDR = ((uint8_t)(*TxBuffer));	
	}else
	{
		UDR = ((uint8_t)(*TxBuffer));		
	}
}
uint16_t MCAL_UART_Receive_data( Polling_t polling)
{
	uint16_t rxBuffer;
	if(polling == PollingENABLE)
		while(!READBIT(UCSRA , RXC));
	
	if (READBIT(UCSRB, UCSZ2))  // 9bit mode
	{
		/* If 9 bit characters are used (UCSZ=7)				 */		/* the ninth bit must be read from the RXB8 bit in UCSRB */		/* before reading the low bits from the UDR.			 */
		rxBuffer = READBIT(UCSRB , RXB8);
		rxBuffer = UDR ;
	}else
	{
		rxBuffer = UDR ;
	}
	
	return rxBuffer;
}

void MCAL_USART_SendString(uint8_t *pTxBuffer)
{
	while(*pTxBuffer !='\0')
	{
		while(!READBIT(UCSRA, UDRE));
		
		if(READBIT(UCSRB, UCSZ2))
		{
			CLEARBIT(UCSRB, TXB8);
			UDR = (uint8_t)(*pTxBuffer);
		}
		else
		{
			UDR = (*pTxBuffer);
			pTxBuffer++;
		}
	}
	
	while(!READBIT(UCSRA, UDRE));
	
	UDR = '\0';
}