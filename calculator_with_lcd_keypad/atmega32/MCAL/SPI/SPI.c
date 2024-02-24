/*
 * SPI.c
 *
 * Created: 12/26/2023 10:56:36 AM
 *  Author: Mohamed Belal
 */ 

/* ============================================================================ */
/* ================================= Includes ================================= */
/* ============================================================================ */
#include "SPI.h"


/* ============================================================================ */
/* ===========================  Global Variables ============================== */
/* ============================================================================ */
SPI_Config_t *G_SPI_Config = 0;


/* ============================================================================ */
/* ==================== APIs Supported by "MCAL ADC DRIVER" =================== */
/* ============================================================================ */
MCAL_SPI_Init         (SPI_Config_t* spi_CFG)
{
	SPCR = 0X00;
	SPSR = 0X00;
	
	// 1. set SPI mode
	SPCR |= spi_CFG->SPI_MODE;
	
	
	if (spi_CFG->SPI_MODE == SPI_MODE_Master)
	{
		// 2. set GPIO PIN
		// Set MOSI, SCK, SS as an output pins
		// Set MISO pin as an input pin
		// SS => PB4   |    MOSI => PB5   |    MISO => PB6   |    SCK => PB7
		SETBIT(DDRB , 4);
		SETBIT(DDRB , 5);
		SETBIT(DDRB , 7);
		CLEARBIT(DDRB , 6);
		
		// 3. set SS pin to high
		SETBIT(PORTB , 4);
		
	}else if (spi_CFG->SPI_MODE == SPI_MODE_Slave)
	{
		// 2. set GPIO PIN
		// Set MOSI, SCK, SS as an input pins
		// Set MISO pin as an output pin
		// SS => PB4   |    MOSI => PB5   |    MISO => PB6   |    SCK => PB7
		CLEARBIT(DDRB , 4);
		CLEARBIT(DDRB , 5);
		CLEARBIT(DDRB , 7);
		SETBIT(DDRB , 6);
	}
	
	// 4. SELECT SPI_prescaler
	SPCR |= spi_CFG->SPI_prescaler;
	
	// 5. SPI_Double_Speed
	SPSR |= spi_CFG->SPI_Double_Speed;
	
	// 6. SPI_Data_Order
	SPCR |= spi_CFG->SPI_Data_Order;
	
	// 7. SPI_CLK_Polarity
	SPCR |= spi_CFG->SPI_CLK_Polarity;
	
	// 8. SPI_CLK_Phase
	SPCR |= spi_CFG->SPI_CLK_Phase;
	
	// 9. SPI IRQ
	SPCR |= spi_CFG->SPI_IRQ;
	if (spi_CFG->SPI_IRQ == SPI_IRQ_Enable)
	{
		sei();
	}
	
	// 10. enable SPI  => Bit 6 – SPE: SPI Enable
	SETBIT(SPCR , SPE);
	
}




MCAL_SPI_DEInit       (void)
{
	SPCR = 0X00;
	SPSR = 0X00;
}

MCAL_SPI_Send_Data    (uint8_t* p_TxBuffer  )
{
	
	// 1. pull ss pin to low 
	CLEARBIT(PORTB , 4);
	
	// 2. write data to SPI data register
	SPDR  = *p_TxBuffer;
	
	// 3. wait until transmission complete
	while(!READBIT(SPSR , SPIF));
	
	// 4. pull ss pin to high
	SETBIT(PORTB , 4);
	

}
MCAL_SPI_Receive_Data (uint8_t* p_RxBuffer  )
{
	// 1. pull ss pin to low
	CLEARBIT(PORTB , 4);
	
	// 2. write data to SPI data register
	 *p_RxBuffer = SPDR  ;
	
	// 3. wait until transmission complete
	while(!READBIT(SPSR , SPIF));
	
	// 4. pull ss pin to high
	SETBIT(PORTB , 4);
}
MCAL_SPI_send_receive (uint8_t* p_RxBuffer  );







/*******************************************************************************
                                  IRQ Handlers
*******************************************************************************/
ISR(SPI_STC_vect)
{
	G_SPI_Config->P_IRQ_CallBack();
}