#include "linkList.h"
#include <stdio.h>

void PrintExpression(term* exprHead);
term* ReadInExpr();
void PrintTitleWords();
void InputExpression();
void PrintInputExample();
void PrintCurrentExpression();
void ClearScreen();
void ClearStdin();

term *expr1Head = NULL, *expr2Head = NULL;
term *plusHead = NULL;
term *minusHead = NULL;
term *multiplyHead = NULL;

void PrintExpression(term* exprHead)
{
	if (exprHead == NULL)
	{
		printf("0\n");
		return;
	}
	term* temp = exprHead;
	int isPrint = 0;
	while (temp != NULL)
	{
		if (temp->coe == 0)
		{
			temp = temp->next;
			continue;
		}
		else if (temp->coe == 1)
		{
			if (isPrint)
				printf("+");
			else
				;
			if (temp->x_exp == 0 && temp->y_exp == 0)
				printf("1");
		}
		else if (temp->coe == -1)
		{
			printf("-");
			if (temp->x_exp == 0 && temp->y_exp == 0)
				printf("1");
		}
		else
		{
			if (isPrint || temp->coe < 0)
				printf("%+g", temp->coe);
			else
				printf("%g", temp->coe);
		}

		if (temp->x_exp == 0)
			;
		else if (temp->x_exp == 1)
			printf("x");
		else
			printf("x%g", temp->x_exp);

		if (temp->y_exp == 0)
			;
		else if (temp->y_exp == 1)
			printf("y");
		else
			printf("y%g", temp->y_exp);

		isPrint = 1;
		temp = temp->next;
	}
	if (!isPrint)
		printf("0");
	printf("\n");
}

term* ReadInExpr()
{
	term *exprHead = NULL, *t = NULL;
	double coe = 0, x_exp = 0, y_exp = 0;
	int pn_flag = 1;
	int isFirstTerm = 1;
	char ch;
	while (1)
	{
		pn_flag = 1;
		ch = getchar();

		if (ch == '+')
			pn_flag = 1;
		else if (ch == '-')
			pn_flag = -1;
		else
			ungetc(ch, stdin);

		if (1 != scanf("%lf", &coe))
			coe = 1;
		coe *= pn_flag;

		ch = getc(stdin);
		if (ch != 'x' && ch != 'X')
		{
			x_exp = 0;
			ungetc(ch, stdin);
		}
		else
		{
			ch = getc(stdin);
			if (ch == '+' || ch == '-' || ch == '\n')
			{
				ungetc(ch, stdin);
				x_exp = 1;
			}
			else
			{
				ungetc(ch, stdin);
				if (1 != scanf("%lf", &x_exp))
					x_exp = 1;
			}
		}
		ch = getc(stdin);
		if (ch != 'y' && ch != 'Y')
		{
			y_exp = 0;
			ungetc(ch, stdin);
		}
		else
		{
			ch = getc(stdin);
			if (ch == '+' || ch == '-' || ch == '\n')
			{
				ungetc(ch, stdin);
				y_exp = 1;
			}
			else
			{
				ungetc(ch, stdin);
				if (1 != scanf("%lf", &y_exp))
					y_exp = 1;
			}
		}
		ch = getc(stdin);
		if (ch != '+' && ch != '-' && ch != '\n')
		{
			DeleteAllTerm(&exprHead);
			return NULL;
		}
		else
		{
			if (exprHead == NULL)
			{
				exprHead = CreateTerm(coe, x_exp, y_exp);
				t = exprHead;
			}
			else
			{
				t->next = CreateTerm(coe, x_exp, y_exp);
				t = t->next;
			}
		}
		if (ch != '\n')
			ungetc(ch, stdin);
		else
		{
			ungetc(ch, stdin);
			break;
		}
	}
	return exprHead;
}

void PrintTitleWords()
{
	printf("--------------Polynomial Calculator--------------\n");
	printf("Input(A)  ");
	printf("Plus(B)  ");
	printf("Minus(C)  ");
	printf("Multiply(D)  ");
	printf("Quit(E)\n\n");
}

void InputExpression()
{
	PrintInputExample();
	// Delete all temp expressions
	DeleteAllTerm(&expr1Head);
	DeleteAllTerm(&expr2Head);
	DeleteAllTerm(&plusHead);
	DeleteAllTerm(&minusHead);
	DeleteAllTerm(&multiplyHead);
	int isInputValid = 1;
	// Input expression 1
	do
	{
		ClearStdin();
		if (isInputValid)
			printf("Please Enter Expression 1>");
		else
			printf("Invalid Input! Please Enter Expression 1 Again>");
		expr1Head = ReadInExpr();
		isInputValid = 0;
	} while (expr1Head == NULL);
	// Input expression 2
	isInputValid = 1;
	do
	{
		ClearStdin();
		if (isInputValid)
			printf("Please Enter Expression 2>");
		else
			printf("Invalid Input! Please Enter Expression 2 Again>");
		expr2Head = ReadInExpr();
		isInputValid = 0;
	} while (expr2Head == NULL);
}

void PrintInputExample()
{
	printf("Valid Input Examples\n");
	printf("x+y\txy\tx+x\t0X0y1-1Y\t1.1xy+x2.1 ...\n");
	printf("Invalid Input Examples\n");
	printf("x + y\tyx\txx\ta+b\t1/3x ...\n\n");
}

void PrintCurrentExpression()
{
	printf("Expression 1: ");
	PrintExpression(expr1Head);
	printf("Expression 2: ");
	PrintExpression(expr2Head);
	printf("\n");
}

void ClearScreen()
{
	system("cls");
}

void ClearStdin()
{
	char ch;
	while ((ch = getchar()) != '\n' && ch != EOF)
		continue;
}

int main(int argc, char* argv[])
{
	char inputChar = 0;
	int isInputValid = 0;
	expr1Head = NULL; 
	expr2Head = NULL;
	ClearScreen();
	PrintTitleWords();
	PrintCurrentExpression();
	while(1)
	{
		if (isInputValid)
			printf("Please Enter a Vaild Character");
		printf(">");
		inputChar = getc(stdin);
		ClearScreen();
		PrintTitleWords();
		PrintCurrentExpression();
		if (inputChar == 'A' || inputChar == 'a')
		{
			InputExpression();
			// Calculate result
			plusHead = Plus(expr1Head, expr2Head);
			minusHead = Minus(expr1Head, expr2Head);
			multiplyHead = Multiply(expr1Head, expr2Head);
			ClearScreen();
			PrintTitleWords();
			PrintCurrentExpression();
		}
		else if (inputChar == 'B' || inputChar == 'b')
		{
			printf("Plus Result: ");
			PrintExpression(plusHead);
		}
		else if (inputChar == 'C' || inputChar == 'c')
		{
			printf("Minus Result: ");
			PrintExpression(minusHead);
		}
		else if (inputChar == 'D' || inputChar == 'd')
		{
			printf("Multiply Result: ");
			PrintExpression(multiplyHead);
		}
		else if (inputChar == 'E' || inputChar == 'e')
			break;
		else
		{
			isInputValid = 1;
			ClearStdin();
			continue;
		}
		ClearStdin();
		isInputValid = 0;
	}
	return 0;
}
