/*
 * I2C.h
 *
 * Created: 12/27/2023 3:18:57 PM
 *  Author: Mohamed Belal
 */ 


#ifndef I2C_H_
#define I2C_H_




/* ========================================================================================= */
/* ======================================= Includes ======================================== */
/* ========================================================================================= */
#include "./../../utils/Atmeg32_Config.h"
#include "./../../MCAL/DIO.h"



/*******************************************************************************
                             Generic Macros                                   
 *******************************************************************************/
#define GET_I2C_Frequency(SCL_FREQ , prescaler)		( ( (F_CPU/SCL_FREQ) -16) / (2*prescaler) )		
#define SCL	PC0
#define SDA PC1


/* ========================================================================================= */
/* =========================== User Type Definition (Structures) =========================== */
/* ========================================================================================= */
typedef struct
{
	/* ==== I2C_SCL_Clock ====
	 * specifies the i2c scl clock
	 * this parameter must be set by user
	 * */
	uint8_t I2C_SCL_Clock;
	

	/* ==== I2C_MODE ====
	 * specifies the i2c mode (MASTER mode | SLAVE Mode)
	 * this parameter must be set base on @ref I2C_MODE_Define
	 * */
	uint8_t I2C_MODE;
	
	
	/* ==== I2C_Prescaler ====
	 * specifies the i2c prescaler (MASTER mode | SLAVE Mode)
	 * this parameter must be set base on @ref I2C_Prescaler_Define
	 * Bits 1..0 – TWPS: TWI Prescaler Bits => TWSR
	 * */
	uint8_t I2C_Prescaler;
	
	/* ==== I2C_Prescaler ====
	 * specifies the i2c ACK enable by hardware or disable it
	 * this parameter must be set base on @ref I2C_ACK_Control_Define
	 * Bit 6 – TWEA: TWI Enable Acknowledge Bit => TWCR
	 * */
	uint8_t I2C_ACK_Control;
	
	
	/* ==== I2C_general_call ====
	 * specifies the i2c general call
	 * this parameter must be set base on @ref I2C_general_call_Define
	 * Bit 0 – TWGCE: TWI General Call Recognition Enable Bit => TWAR
	 * */
	uint8_t I2C_general_call;
	
	/* ==== I2C_Slave_Address ====
	 * specifies the i2c slave address
	 * this parameter must be set base by user
	 * */
	uint8_t I2C_Slave_Address;
	
	
	
	/* ==== I2C_IRQ ====
	 * specifies the i2c interupt 
	 * this parameter must be set base on @ref I2C_IRQ_Define
	 * Bit 0 – TWIE: TWI Interrupt Enable => TWCR
	 * */
	uint8_t I2C_IRQ;
	
	
	/* Set the C Function which will be called once IRQ Happens */
	void (*P_Slave_CallBack)(void); 

}I2C_config_t;


/* ========================================================================================= */
/* ============================= Macros Configuration References =========================== */
/* ========================================================================================= */



//-------------------------------------
//		@ref I2C_MODE_Define
//-------------------------------------
#define I2C_MODE_master					0	
#define I2C_MODE_slave					1	


//-------------------------------------
//		@ref I2C_Prescaler_Define
//-------------------------------------
#define I2C_Prescaler_1					(0b00<<TWPS0)
#define I2C_Prescaler_4					(0b01<<TWPS0)
#define I2C_Prescaler_16				(0b10<<TWPS0)
#define I2C_Prescaler_64				(0b11<<TWPS0)

//-------------------------------------
//		@ref I2C_ACK_Control_Define
//-------------------------------------
#define I2C_ACK_Control_disable			(0)
#define I2C_ACK_Control_enable			(1<<TWEA)

//-------------------------------------
//		@ref I2C_general_call_Define
//-------------------------------------
#define I2C_general_call_disable		(0)
#define I2C_general_call_enable			(1<<TWGCE)




//-------------------------------------
//		@ref @ref I2C_IRQ_Define
//-------------------------------------
#define I2C_IRQ_disable					(0)
#define I2C_IRQ_enable					(1<<TWIE)




//-------------------------------------
//				channel enum
//-------------------------------------
typedef enum{
		Start_Disable,
		Start_Enable,
		Repeated_Start,
}Start_Condition_t;


typedef enum{
	Stop_Disable,
	Stop_Enable,
}Stop_Condition_t;


typedef enum{
	ACK,
	NACK,
}Acknowledge_t;


typedef enum{
	WRITE,
	READ,
}I2C_Direction_t;


/* ========================================================================================= */
/* ========================= APIs Supported by "MCAL Timer0 DRIVER" ======================== */
/* ========================================================================================= */
void MCAL_I2C_Init(I2C_config_t* I2C_CFG);

void MCAL_I2C_Start_Condition(void);
void MCAL_I2C_Stop_Condition(void);

void MCAL_I2C_TX(uint8_t* TX_buffer);
void MCAL_I2C_RX(uint8_t* RX_buffer);





#endif /* I2C_H_ */