/*
 * calculator.c
 *
 * Created: 2/24/2024 4:07:43 PM
 *  Author: mohamed belal
 */ 
#include "calculator.h"

void calculatorApp(void)
{
	char keyPressed;
	int i=0;

	char flag =0 ;
	char expression[MAX_SIZE];
		
	LCD_Init();
	keypad_Init();
	
 	LCD_Send_String("welcome to Bello calculator");
 	_delay_ms(500);
	LCD_Clear_Screen();

	
	while (1)
	{
		keyPressed = keypad_GetKey();
		switch(keyPressed)
		{
			case('A'):
				break; //do nothing if no key pressed
			case('?'):
					LCD_Clear_Screen();
				break; //do nothing if no key pressed
			default:
					LCD_Send_Character(keyPressed); // send the key to LCD
					if (keyPressed == '=')
					{
						expression[i] = '\0';
						LCD_Display_Number(evaluateInfix(expression));
						i=0;
						
					}else
					{
						expression[i] = keyPressed;
						i++;
					}
				break;
		}
	
		
	}

}

	void initialize(Stack *stack)
	{
		stack->top = -1;
	}

	void push(Stack *stack, int value)
	{
		if (stack->top != MAX_SIZE - 1)
		{
			++stack->top;
			stack->array[stack->top] = value;
		}
	}

	int pop(Stack *stack)
	{
		if (!isEmpty(stack))
		{
			return stack->array[stack->top--];
		}
		return -1;
	}

	int isEmpty(Stack *stack)
	{
		if (stack->top == -1)
		return 1;
		else
		return 0;
	}

	int peek(Stack *stack)
	{
		if (!isEmpty(stack))
		{
			return stack->array[stack->top];
		}
		return -1;
	}

	int isOperator(char ch)
	{
		if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
		return 1;
		else
		return 0;
	}
	int getPrecedence(char op)
	{
		int x;
		switch (op)
		{
			case '+':
			case '-':
			x = 1;
			break;

			case '*':
			case '/':
			x = 2;
			break;

			default:
			x = 0;
			break;
		}
		return x;
	}
	int doMath(int operand1, int operand2, char operator)
	{
		int result;
		switch (operator)
		{
			case '+':
			result = operand1 + operand2;
			break;
			case '-':
			result = operand1 - operand2;
			break;
			case '*':
			result = operand1 * operand2;
			break;
			case '/':
			if (operand2 != 0)
			result = operand1 / operand2;
			else
			result = -1;
			break;
			default:
			result = -1;
			break;
		}
		return result;
	}
	int evaluateInfix(char expression[])
	{
		Stack operandStack, operatorStack;
		int i = 0;
		initialize(&operandStack);
		initialize(&operatorStack);
		for (i = 0; expression[i] != '\0'; i++)
		{
			// If the character is a digit, convert it to an integer and push onto the operand stack
			if (isdigit(expression[i]))
			{
				// to transfer from char int int value
				int operand = expression[i] - '0';
				while (isdigit(expression[i + 1]))
				{
					operand = operand * 10 + (expression[i + 1] - '0');
					i++;
				}
				push(&operandStack, operand);
			}
			// If the character is an operator, pop operators from the operator stack
			// and apply them to the operands from the operand stack until the conditions are met
			else if (isOperator(expression[i]))
			{
				while (!isEmpty(&operatorStack) &&
				getPrecedence(peek(&operatorStack)) >= getPrecedence(expression[i]))
				{
					int operand2 = pop(&operandStack);
					int operand1 = pop(&operandStack);
					char operator= pop(&operatorStack);
					push(&operandStack, doMath(operand1, operand2, operator));
				}
				// Push the current operator onto the operator stack
				push(&operatorStack, expression[i]);
			}
		}

		while (!isEmpty(&operatorStack))
		{
			int operand2 = pop(&operandStack);
			int operand1 = pop(&operandStack);
			char operator= pop(&operatorStack);
			push(&operandStack, doMath(operand1, operand2, operator));
		}

		// The final result is on the top of the operand stack
		return pop(&operandStack);
	}


