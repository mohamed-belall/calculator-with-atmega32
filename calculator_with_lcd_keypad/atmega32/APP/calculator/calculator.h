/*
 * calculator.h
 *
 * Created: 8/28/2023 4:36:45 PM
 * Author : Mohamed Belal
 */ 

#ifndef CALCULATOR_H_
#define CALCULATOR_H_




#include "./../../MCAL/Timer/Timer.h"
#include "./../../MCAL/ADC/ADC.h"
#include "./../../HAL/lcd_driver.h"
#include "./../../HAL/keypad/keypad.h"
#include "./../../MCAL/DIO.h"

#define MAX_SIZE 100

// Stack structure
typedef struct
{
	int top;
	int array[MAX_SIZE];
} Stack;

// Function prototypes
void calculatorApp(void);
// stack functions
void initialize(Stack *stack);
void push(Stack *stack, int value);
int pop(Stack *stack);
int isEmpty(Stack *stack);
int peek(Stack *stack);
// other function
int isOperator(char ch);
int getPrecedence(char op);
int doMath(int operand1, int operand2, char operator);

int evaluateInfix(char expression[]);



#endif /* CALCULATOR_H_ */