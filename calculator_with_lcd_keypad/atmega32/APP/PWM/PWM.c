/*
 * PWM.c
 *
 * Created: 10/18/2023 7:14:57 AM
 *  Author: moham
 */ 
#include "PWM.h"


void PWM_App(void)
{
		DIO_SetPinDirection(DIO_PORTB , DIO_PIN3,DIO_PIN_OUTPUT);
	
		TIMER0_Config_t timer0CFG;
		timer0CFG.Timer_Mode = Timer0_Mode_PWM_NONINVERTING;
		timer0CFG.Timer_Clock_Source = Timer_Clock_Source_PRESCALING_8;
		timer0CFG.IRQ_Enable = IRQ_Enable_NON;
		timer0CFG.P_IRQ_CallBack = 0;
		
		
		MCAL_Timer0_Init(&timer0CFG);
		
		
		
		volatile uint8_t speed = 0;
		
		DDRC = 0xF0;
		PORTC = 0x0F;
		
		while(1)
		{
			if (READBIT(PINC , 0) == 0)        // reset
			{
				_delay_ms(250);
			speed = 0;
			}
			 if (READBIT(PINC , 1) == 0)  // increment
			{
				_delay_ms(250);
				if(speed<90)   speed += 10;
			}
			 if (READBIT(PINC , 2) == 0)	 // decrement
			{
				_delay_ms(250);
				if(speed>0) speed -= 10;
				
			}
			MCAL_Timer0_PWM_DutyCycle(speed);
		}
}