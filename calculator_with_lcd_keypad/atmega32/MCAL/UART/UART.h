/*
 * UART.h
 *
 * Created: 12/25/2023 8:11:17 PM
 *  Author: Mohamed Belal
 */ 


#ifndef UART_H_
#define UART_H_


/* ========================================================================================= */
/* ======================================= Includes ======================================== */
/* ========================================================================================= */
#include "./../../utils/Atmeg32_Config.h"
#include "./../../MCAL/DIO.h"


/* ========================================================================================= */
/* =========================== User Type Definition (Structures) =========================== */
/* ========================================================================================= */
typedef struct 
{
	/* ==== UART_MODE ====
	 * specifies the UART mode (Transmitter mode | Receiver Mode)
	 * this parameter must be set base on @ref UART_MODE_Define
	 * bit Bit 4 – RXEN & Bit 3 – TXEN => UCSRB
	 * */
	uint8_t UART_MODE;
	
	/* ==== UART_BaudRate ====
	 * specifies the UART baud rate  assume => Fosc:8MHZ ,  U2X = 0   disable double speed
	 * this parameter must be set base on @ref UART_BaudRate_Define
	 * Bit 11:0 – UBRR11:0: USART Baud Rate Register => UBRRL and UBRRH
	 * */
	uint8_t UART_BaudRate;
	
	/* ==== UART_DATA_SIZE ====
	 * specifies the UART data size 5bit , 6bit , 7bit , 8bit , 9bit 
	 * this parameter must be set base on @ref UART_DATA_SIZE_Define
	 * Bit 2:1 – UCSZ1:0: Character Size => UCSRC
	 * */
	uint8_t UART_DATA_SIZE;
	
	
	/* ==== UART_Parity_Mode ====
	 * specifies the UART parity bit
	 * this parameter must be set base on @ref UART_Parity_Mode_Define
	 * Bit 5:4 – UPM1:0: Parity Mode => UCSRC
	 * */
	uint8_t UART_Parity_Mode;
	
	
	/* ==== UART_STOP_Bit ====
	 * specifies the UART stop bit  1bit | 2bit
	 * this parameter must be set base on @ref UART_STOP_Bit_Define
	 * Bit 3 – USBS: Stop Bit Select => UCSRC
	 * */
	uint8_t UART_STOP_Bit;
	
	
	/* ==== UART_IRQ ====
	 * enable UART interrupt
	 * this parameter must be set base on @ref UART_IRQ_Define
	 * Bit 7 – RXCIE: RX Complete Interrupt Enable  :  Bit 6 – TXCIE:  => UCSRB
	 * */
	uint8_t UART_IRQ;
	
	void(*P_IRQ_CallBack)(void);
	
	
}UART_Config_t;
	 



/* ========================================================================================= */
/* ============================= Macros Configuration References =========================== */
/* ========================================================================================= */



//-------------------------------------
//		@ref UART_MODE_Define
//-------------------------------------
#define UART_MODE_Transmitter	(1<<TXEN)
#define UART_MODE_Receiver		(1<<RXEN)


//-------------------------------------
//		@ref @ref UART_BaudRate_Define
//-------------------------------------
#define UART_BaudRate_2400			(207)
#define UART_BaudRate_4800			(103)
#define UART_BaudRate_9600			(51)
#define UART_BaudRate_14400			(34)
#define UART_BaudRate_19200			(25)
#define UART_BaudRate_28800			(16)
#define UART_BaudRate_38400			(12)
#define UART_BaudRate_57600			(8)
#define UART_BaudRate_76800			(6)
#define UART_BaudRate_115200		(3)
#define UART_BaudRate_230400		(1)
#define UART_BaudRate_250000		(1)

//-------------------------------------
//		@ref UART_DATA_SIZE_Define
//-------------------------------------
#define UART_DATA_SIZE_5bit			(0b00<<UCSZ0)
#define UART_DATA_SIZE_6bit			(0b01<<UCSZ0)
#define UART_DATA_SIZE_7bit			(0b10<<UCSZ0)
#define UART_DATA_SIZE_8bit			(0b11<<UCSZ0)
#define UART_DATA_SIZE_9bit			(0b11<<UCSZ0)



//-------------------------------------
//		@ref UART_Parity_Mode_Define
//-------------------------------------
#define UART_Parity_Mode_disable		(0b00<<UPM0)
#define UART_Parity_Mode_even			(0b10<<UPM0)
#define UART_Parity_Mode_odd			(0b11<<UPM0)


//-------------------------------------
//		@ref UART_STOP_Bit_Define
//-------------------------------------
#define UART_STOP_Bit_1BIT				(0)
#define UART_STOP_Bit_2BIT				(1<<USBS)

//-------------------------------------
//		@ref UART_IRQ_Define
//-------------------------------------
#define UART_IRQ_disable					(0)
#define UART_IRQ_RXCIE					(1<<RXCIE)
#define UART_IRQ_TXCIE					(1<<TXCIE)
#define UART_IRQ_TXCIE_RXCIE			( (1<<RXCIE) | (1<<TXCIE) )



//-------------------------------------
//				channel enum
//-------------------------------------
	
	typedef enum
	{
		PollingENABLE,
		PollingDISABLE
	}Polling_t;



/* ========================================================================================= */
/* ========================= APIs Supported by "MCAL Timer0 DRIVER" ======================== */
/* ========================================================================================= */
void MCAL_UART_Init(UART_Config_t* UARTCFG);
void MCAL_UART_DEInit(void);

void MCAL_UART_send_data(uint8_t* TxBuffer, Polling_t polling);
uint16_t MCAL_UART_Receive_data( Polling_t polling);

void MCAL_USART_SendString(uint8_t *pTxBuffer);



#endif /* UART_H_ */