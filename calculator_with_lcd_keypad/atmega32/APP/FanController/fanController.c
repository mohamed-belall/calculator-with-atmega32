/*
 ==================================================================
 Name        : fanController.c
 Author      : Mohamed Belal
 Created on  : 7/2/2024
 Description : fan controller application to controll motor speed acording to temperature value
 ==================================================================
 */

#include "fanController.h"

void fanController_app(void)
{
	/*	=================== INIT DC MOTOR ================ 	*/
	DIO_SetPinDirection(DIO_PORTB, DIO_PIN0, DIO_PIN_OUTPUT);
	DIO_SetPinDirection(DIO_PORTB, DIO_PIN1, DIO_PIN_OUTPUT);
	DIO_SetPinDirection(DIO_PORTB, DIO_PIN3, DIO_PIN_OUTPUT);

	DIO_SetPinValue(DIO_PORTB, DIO_PIN0, DIO_PIN_LOW);
	DIO_SetPinValue(DIO_PORTB, DIO_PIN1, DIO_PIN_HIGH);

	/*	=================== INIT timer =================== 	*/
	TIMER0_Config_t TimerCFG;
	TimerCFG.Timer_Mode = Timer0_Mode_PWM_NONINVERTING;
	TimerCFG.Timer_Clock_Source = Timer_Clock_Source_PRESCALING_8;
	TimerCFG.IRQ_Enable = IRQ_Enable_NON;
	TimerCFG.P_IRQ_CallBack = 0;
	MCAL_Timer0_Init(&TimerCFG);

	/*	=================== INIT ADC =================== 	*/
	ADC_Config_t ADCcfg;
	ADCcfg.ADC_Mode = ADC_Mode_SINGLE_CONVERSION;
	ADCcfg.ADC_Prescaler = ADC_PRESCALER_2;
	ADCcfg.ADC_Result_Presentation = ADC_Result_Presentation_RIGHT;
	ADCcfg.ADC_Voltage_Reference = ADC_Voltage_Reference_AVCC;
	ADCcfg.IRQ_Enable = IRQ_ADIE_Disable;
	ADCcfg.P_IRQ_CallBack = 0;
	MCAL_ADC_Init(&ADCcfg);

	/*	=================== INIT LCD =================== 	*/
	LCD_Init();

	/*	=================== variable section =================== 	*/
	uint8_t temperature = 0;
	uint32_t ADC_Result = 0;
	uint8_t fanSpeed = 10;

	LCD_Send_String("temp: ");
	LCD_gotoXY(2, 0);
	LCD_Send_String("fan speed: ");

	while (1)
	{
		LCD_gotoXY(1, 6);

		/*	=================== get temp from temp sensor =================== 	*/
		MCAL_ADC_GetConversionResult(ADC0, &ADC_Result, Polling_ENABLE);
		temperature = (((ADC_Result * 5000) / 1023) / 10);

		/*	=================== display temp on lcd =================== 	*/
		LCD_Display_Number(temperature);
		LCD_Send_Character('C');

		/*	=================== algorithm to set motor speed according to temp val =================== 	*/
		if (temperature < 15)
			fanSpeed = 0;
		else if (temperature >= 15 && temperature < 25)
			fanSpeed = 10;
		else if (temperature >= 25 && temperature < 35)
			fanSpeed = 20;
		else if (temperature >= 35 && temperature < 45)
			fanSpeed = 30;
		else if (temperature >= 45 && temperature < 55)
			fanSpeed = 40;
		else if (temperature >= 55 && temperature < 65)
			fanSpeed = 50;
		else if (temperature >= 65 && temperature < 75)
			fanSpeed = 60;
		else if (temperature >= 75 && temperature < 85)
			fanSpeed = 70;
		else if (temperature >= 85 && temperature < 95)
			fanSpeed = 80;
		else if (temperature >= 95 && temperature < 100)
			fanSpeed = 90;
		else if (temperature >= 100)
			fanSpeed = 100;

		/*	=================== set motor speed =================== 	*/
		MCAL_Timer0_PWM_DutyCycle(fanSpeed);

		/*	=================== display motor speed on lcd =================== 	*/
		LCD_gotoXY(2, 11);
		LCD_Display_Number(fanSpeed);
	}
}