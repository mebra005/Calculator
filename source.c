#define _CRT_SECURE_NO_WARNINGS
#include "stack.h"
#include <string.h>
#include <math.h>
#define MAX_SIZE 255
#define NUM_OPERATORS 5
#define L 1
#define R 2

struct Priority
{
	int add;
	int subtract;
	int multiply;
	int divide;
	int exp;
};

struct Association
{
	int add;
	int subtract;
	int multiply;
	int divide;
	int exp;
};
// global variables to store association and priorities
struct Association asc;
struct Priority prio;

void initialize()
{
	prio.add = 1;
	prio.subtract = 1;
	prio.multiply = 2;
	prio.divide = 2;
	prio.exp = 3;

	asc.add = L;
	asc.subtract = L;
	asc.multiply = L;
	asc.divide = L;
	asc.exp = R;
}

// function prints error and exists
void error()
{
	printf("Error\n");

}

// function to check if input is an operand
int isOperand(char c)
{
	if (c >= '0' && c <= '9')
		return TRUE;
	else
		return FALSE;
}

// function to check if input is an operator
int isOperator(char c)
{
	if (c == '+' || c == '-' || c == '/' || c == '*' || c == '^' || c == 'X' || c =='x' || c ==')' || c == '(')
		return TRUE;
	else
		return FALSE;
}

// function returns priority for operator
int priority(char c)
{
	int p = 0;
	switch (c)
	{
	case '+':
		p = prio.add;
		break;
	case '-':
		p = prio.subtract;
		break;
	case '/':
		p = prio.divide;
		break;
	case '*':
		p = prio.multiply;
		break;
	case 'X':
		p = prio.multiply;
		break;
	case 'x':
		p = prio.multiply;
		break;
	case '^':
		p = prio.exp;
		break;
	}
	return p;
}

// function returns associativity for operator
int associativity(char c)
{
	int p = L;
	switch (c)
	{
	case '+':
		p = asc.add;
		break;
	case '-':
		p = asc.subtract;
		break;
	case '/':
		p = asc.divide;
		break;
	case '*':
		p = asc.multiply;
		break;
	case 'x':
		p = asc.multiply;
		break;
	case 'X':
		p = asc.multiply;
		break;
	case '^':
		p = asc.exp;
		break;
	}
	return p;
}

// function evaluates the answer and pushes to opnd stack
void evaluate(struct node **opnd, struct node **oprtr)
{
	int num1;
	int num2;
	char operator;
	int answer = 0;

	// get num 1
	if (isEmpty(*opnd) == FALSE)
	{
		num1 = top(*opnd);
		pop(opnd);
	}
	else
	{
		error();
		return;
	}
	
	// get num 2
	if (isEmpty(*opnd) == FALSE)
	{
		num2 = top(*opnd);
		pop(opnd);
	}
	else
	{
		error();
		return;
	}
	// get operator
	if (isEmpty(*oprtr) == FALSE)
	{
		operator = top(*oprtr);
		pop(oprtr);
	}
	else
	{
		error();
		return;
	}

	// evaluate value
	switch (operator)
	{
	case '+':
		answer = num2 + num1;
		break;
	case '-':
		answer = num2 - num1;
		break;
	case '/':
		answer = num2 / num1;
		break;
	case '*':
		answer = num2 * num1;
		break;
	case 'x':
		answer = num2 * num1;
		break;
	case 'X':
		answer = num2 * num1;
		break;
	case '^':
		answer = pow(num2 , num1);
		break;
	}
	// push answer to opnd stack
	push(opnd,answer);
}

void solveExpression(char * line)
{
	struct node *opnd = NULL;
	struct node *oprtr = NULL;

	char tk = '\0';
	char string[MAX_SIZE];
	memset(string, 0, MAX_SIZE);
	int i = 0;
	int result = 0;
	int k = 0;

	while ((tk = line[k]) != '\n')
	{
		// if is operand
		if (isOperand(tk))
		{
			string[i] = tk;
			i++;
		}
		// if is operator
		else if (isOperator(tk))
		{
			// push previous operand to top of opnd stack
			if (i > 0)
			{
				push(&opnd, atoi(string));
				// reset string for next operand
				memset(string, 0, MAX_SIZE);
				i = 0;
			}
			// if oprtr stack is empty push to top
			if (isEmpty(oprtr))
			{
				push(&oprtr, tk);
			}
			else if (tk == '(')
			{
				push(&oprtr, tk);
			}
			// if ')' is encountered evaluate answer and push to stack till ')'
			else if (tk == ')')
			{
				while (isEmpty(oprtr) == FALSE && top(oprtr) != '(')
					evaluate(&opnd, &oprtr);
				if (top(oprtr) == '(')
					pop(&oprtr);
				else
				{
					error();
					return;
				}
			}
			// evaluate or push based on priority of top of operator stack
			else if (priority(tk) > priority(top(oprtr)))
				push(&oprtr, tk);
			else if (priority(tk) < priority(top(oprtr)))
			{
				evaluate(&opnd, &oprtr);
				push(&oprtr, tk);
			}
			// if priority is equal evaluate based on associativity
			else if (associativity(tk) == L)
			{
				evaluate(&opnd, &oprtr);
				push(&oprtr, tk);
			}
			else
			{
				push(&oprtr, tk);
			}
		}
		// if space is encountered
		else if (tk == ' ')
		{
			if (i > 0)
			{
				push(&opnd, atoi(string));
				// reset string for next operand
				memset(string, 0, MAX_SIZE);
				i = 0;
			}
		}
		else{
			error();
			return;
		}
		k++;
	}

	// add any left operand to top of stack
	if (i > 0)
	{
		push(&opnd, atoi(string));
		// reset string for next operand
		memset(string, 0, MAX_SIZE);
		i = 0;
	}

	// evaluate when done reading expression
	while (isEmpty(oprtr) == FALSE)
		evaluate(&opnd, &oprtr);

	// store result 
	result = top(opnd);
	pop(&opnd);

	// check if no more oprnd left
	if (isEmpty(opnd) == TRUE)
		printf("result: %d\n", result);
	else
	{
		error();
		return;
	}
}

void setSettings()
{
	char line[MAX_SIZE];
	int i = 0;

	char oprtr;
	int priority = 0;
	char asco;
	int asc_int = L;
	for (i = 0; i < NUM_OPERATORS; i++)
	{
		scanf("%c %d %c", &oprtr, &priority, &asco);
		// ingnore end of line
		getchar();
		if (asco == 'R')
			asc_int = R;
		else
			asc_int = L;

		switch (oprtr)
		{
		case '+':
			prio.add = priority;
			asc.add = asc_int;
			break;
		case '-':
			prio.subtract = priority;
			asc.subtract = asc_int;
			break;
		case '/':
			prio.divide = priority;
			asc.divide = asc_int;
			break;
		case '*':
			prio.multiply = priority;
			asc.multiply = asc_int;
			break;
		case 'x':
			prio.multiply = priority;
			asc.multiply = asc_int;
			break;
		case 'X':
			prio.multiply = priority;
			asc.multiply = asc_int;
			break;
		case '^':
			prio.exp = priority;
			asc.exp = asc_int;
			break;
		}
	}
}

int main()
{
	
	char line[MAX_SIZE];
	memset(line, 0, MAX_SIZE);

	printf("Enter priorities and association:\n");
	// set user settings for priority and associations
	setSettings();
	// while end of line is encountered
	printf("Enter expression:\n");
	while (fgets(line, MAX_SIZE, stdin) != NULL)
	{
		solveExpression(line);
		// reset line buffer
		memset(line, 0, MAX_SIZE);
	}
	return 0;
}
