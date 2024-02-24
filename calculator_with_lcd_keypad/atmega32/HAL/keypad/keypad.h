/*
 * keypad.h
 *
 * Created: 2/24/2024 4:11:04 PM
 *  Author: mohamed belal
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_


#include "./../../utils/Atmeg32_Config.h"
#include <string.h>

//keypad Information
#define R0				0
#define R1				1
#define R2				2
#define R3				3
#define C0				4
#define C1				5
#define C2				6
#define C3              7

#define KEYPAD_PORT     PORTD
#define KEYPAD_PIN      PIND
#define KEYPAD_DDR      DDRD

//keypad functions and global ariable

void keypad_Init();
char keypad_GetKey();


#endif /* KEYPAD_H_ */