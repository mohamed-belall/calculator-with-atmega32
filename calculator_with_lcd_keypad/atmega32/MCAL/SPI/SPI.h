/*
 * SPI.h
 *
 * Created: 12/26/2023 10:56:46 AM
 *  Author: Mohamed Belal
 */ 


#ifndef SPI_H_
#define SPI_H_


/* ========================================================================================= */
/* ======================================= Includes ======================================== */
/* ========================================================================================= */
#include "./../../utils/Atmeg32_Config.h"
#include "./../../MCAL/DIO.h"



/*******************************************************************************
                             Generic Macros                                   
 *******************************************************************************/
#define MCU_Act_As_MASTER
//#define MCU_Act_As_SLAVE




/* ========================================================================================= */
/* =========================== User Type Definition (Structures) =========================== */
/* ========================================================================================= */
typedef struct 
{
	/* ==== SPI_MODE ====
	 * specifies the SPI mode (MASTER mode | SLAVE Mode)
	 * this parameter must be set base on @ref SPI_MODE_Define
	 * Bit 4 – MSTR: Master/Slave Select => SPCR
	 * */
	uint8_t SPI_MODE;
	
	
	/* ==== SPI_prescaler ====
	 * specifies the SPI prescaler => Relationship Between SCK and the Oscillator Frequency
	 * this parameter must be set base on @ref SPI_prescaler_Define
	 * Bits 1, 0 – SPR1, SPR0: SPI Clock Rate Select 1 and 0 => SPCR
	 * */
	uint8_t SPI_prescaler;
	
	
	
	/* ==== SPI_Double_Speed ====
	 * specifies the SPI double speed. This means that the minimum SCK period 
	 * this parameter must be set base on @ref SPI_Double_Speed_Define
	 * Bit 0 – SPI2X: Double SPI Speed Bit => SPSR
	 * */
	uint8_t SPI_Double_Speed;
	
	
	
	
	/* ==== SPI_Data_Order ====
	 * specifies the SPI Data Order  written to one,  the LSB of the data word is transmitted first
	 *								 written to zero, the MSB of the data word is transmitted first
	 * this parameter must be set base on @ref SPI_Data_Order_Define
	 * Bit 5 – DORD: Data Order => SPCR
	 * */
	uint8_t SPI_Data_Order;
	
	
	
	/* ==== SPI_CLK_Polarity ====
	 * specifies the SPI Clock Polarity			written to one,  SCK is high when idle
	 *											written to zero, SCK is low  when idle
	 * this parameter must be set base on @ref SPI_CLK_Polarity_Define
	 * Bit 3 – CPOL: Clock Polarity => SPCR
	 * */
	uint8_t SPI_CLK_Polarity;
	
	
	
	
	/* ==== SPI_CLK_Phase ====
	 * specifies the SPI Clock Phase  =>  The settings of the Clock Phase bit (CPHA) determine 
	 *									  if data is sampled on the leading (first) or trailing (last) edge of SCK
	 *											
	 * this parameter must be set base on @ref SPI_CLK_Phase_Define
	 * Bit 2 – CPHA: Clock Phase => SPCR
	 * */
	uint8_t SPI_CLK_Phase;
	
	
	
	
	
		/* ==== SPI_IRQ ====
	 * specifies the SPI Interrupt Enable   =>  @note: global interrupt enable bit in SREG is set.
	 * this parameter must be set base on @ref SPI_IRQ_Define
	 * Bit 7 – SPIE: SPI Interrupt Enable => SPCR
	 * */
	uint8_t SPI_IRQ;
	 

	//set the C Function which will be called once IRQ Happens
	void (* P_IRQ_CallBack)(void);

	
}SPI_Config_t;



/* ========================================================================================= */
/* ============================= Macros Configuration References =========================== */
/* ========================================================================================= */



//-------------------------------------
//		@ref SPI_MODE_Define
//-------------------------------------
#define SPI_MODE_Master					(1<<MSTR)		
#define SPI_MODE_Slave					(0)	



//-------------------------------------
//		@ref SPI_prescaler_Define
//-------------------------------------

#define  SPI_prescaler_4				(0b00<<SPR0)
#define  SPI_prescaler_16				(0b01<<SPR0)
#define  SPI_prescaler_64				(0b10<<SPR0)
#define  SPI_prescaler_128				(0b11<<SPR0)

/* SPSR.Bit 0 – SPI2X: Double SPI Speed Bit */
#define  SPI_prescaler_DOUBLE_SPEED_2			(0b00<<SPR0)
#define  SPI_prescaler_DOUBLE_SPEED_8			(0b01<<SPR0)
#define  SPI_prescaler_DOUBLE_SPEED_32			(0b10<<SPR0)
#define  SPI_prescaler_DOUBLE_SPEED_64			(0b11<<SPR0)



//-------------------------------------
//		@ref SPI_Double_Speed_Define
//-------------------------------------
#define  SPI_Double_Speed_Enable		(1<<SPI2X)
#define  SPI_Double_Speed_Disable		(0)


//-------------------------------------
//		@ref SPI_IRQ_Define
//-------------------------------------
#define  SPI_IRQ_Enable					(1<<SPIE)
#define  SPI_IRQ_Disable				(0)




//-------------------------------------
//		 @ref SPI_Data_Order_Define
//-------------------------------------
#define  SPI_Data_Order_LSB				(1<<DORD)
#define  SPI_Data_Order_MSB 			(0)



//-------------------------------------
//		@ref SPI_CLK_Polarity_Define
//-------------------------------------
#define  SPI_CLK_Polarity_idle_high		(1<<CPOL)	/* FALLING RISING */
#define  SPI_CLK_Polarity_idle_low 		(0)			/* RISING FALLING */


//-------------------------------------
//		@ref SPI_CLK_Phase_Define
//-------------------------------------
#define  SPI_CLK_Phase_Trailing			(1<<CPHA)   /* SETUP SAMPLE */
#define  SPI_CLK_Phase_Leading 			(0)			/* SAMPLE SETUP */





//-------------------------------------
//				channel enum
//-------------------------------------
	
	



/* ========================================================================================= */
/* ========================= APIs Supported by "MCAL Timer0 DRIVER" ======================== */
/* ========================================================================================= */
MCAL_SPI_Init         (SPI_Config_t* spi_CFG);
MCAL_SPI_DEInit       (void);

MCAL_SPI_Send_Data    (uint8_t* p_TxBuffer  );
MCAL_SPI_Receive_Data (uint8_t* p_RxBuffer  );
MCAL_SPI_send_receive (uint8_t* p_RxBuffer  );


#endif /* SPI_H_ */