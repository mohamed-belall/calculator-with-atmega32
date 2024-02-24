/*
 * I2C.c
 *
 * Created: 12/27/2023 3:18:48 PM
 *  Author: Mohamed Belal
 */ 

/* ============================================================================ */
/* ================================= Includes ================================= */
/* ============================================================================ */
#include "I2C.h"


/* ============================================================================ */
/* ===========================  Global Variables ============================== */
/* ============================================================================ */



/* ============================================================================ */
/* ==================== APIs Supported by "MCAL ADC DRIVER" =================== */
/* ============================================================================ */

void MCAL_I2C_Init(I2C_config_t* I2C_CFG)
{
	/*	========  1. set bit rate  ========	*/	
	TWBR = 0x00;
	TWSR |= I2C_CFG->I2C_Prescaler;
	switch (I2C_CFG->I2C_Prescaler)
	{
		case I2C_Prescaler_1:
			TWBR = GET_I2C_Frequency(I2C_CFG->I2C_SCL_Clock , 1);
			break;
		case I2C_Prescaler_4:
			TWBR = GET_I2C_Frequency(I2C_CFG->I2C_SCL_Clock , 4);
			break;
		case I2C_Prescaler_16:
			TWBR = GET_I2C_Frequency(I2C_CFG->I2C_SCL_Clock , 16);
			break;
		case I2C_Prescaler_64:
			TWBR = GET_I2C_Frequency(I2C_CFG->I2C_SCL_Clock , 64);
			break;
	}
	
	/*	========  2. enable TWI Interrupt  ========	*/	
	SETBIT(TWCR , TWINT);
	
	/*	========  3. disable general call  ========	*/	
	CLEARBIT(TWAR , TWGCE);
	
	/*	========  4. enable global interrupt  ========	*/	
	SETBIT(TWCR , TWIE);
	
	/*	========  5. enable I2C  ========	*/	
	SETBIT(TWCR , TWEN);
	
	/*	========  6. set ACK  ========	*/
	if(I2C_CFG->I2C_ACK_Control = I2C_ACK_Control_enable )
		SETBIT(TWCR , TWEA);
	else if(I2C_CFG->I2C_ACK_Control = I2C_ACK_Control_disable )
		CLEARBIT(TWCR , TWEA);
		
	/*	========  6. set slave address  ========	*/
	TWAR = I2C_CFG->I2C_Slave_Address;
	
	while(!(READBIT(TWCR , TWINT)));

}





void MCAL_I2C_Start_Condition(void)
{
	SETBIT(TWCR , TWINT);
	SETBIT(TWCR , TWSTA);
	while((READBIT(TWCR , TWINT)));
}

void MCAL_I2C_Stop_Condition(void)
{
	SETBIT(TWCR , TWINT);
	SETBIT(TWCR , TWSTO);
	while((READBIT(TWCR , TWINT)));
}

void MCAL_I2C_TX(uint8_t* TX_buffer)
{
	SETBIT(TWCR , TWINT);
	TWDR = *TX_buffer;
	while(!(READBIT(TWCR , TWINT)));
}
void MCAL_I2C_RX(uint8_t* RX_buffer)
{
	SETBIT(TWCR , TWINT);
	*RX_buffer = TWDR;
	while((READBIT(TWCR , TWINT)));
}



/*******************************************************************************
                                  IRQ Handlers
*******************************************************************************/
