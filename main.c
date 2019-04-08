#include "linkList.h"
#include <stdio.h>

void PrintResult(term* exprHead);
term* ReadInExpr();
void PrintTitleWords();
void PrintTitleWords();
void ClearScreen();
void ClearStdin();

void PrintResult(term* exprHead)
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
		if (ch == 'c' || ch == 'C')
		{
			DeleteAllTerm(&exprHead);
			ClearScreen();
			break;
		}
		else if (ch == '+')
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
	printf("----Polynomial Calculator----\n\n");
	printf("Valid Input Examples\n");
	printf("x+y\txy\t1X2y2+0Y\t1.1xy+x2.1 ...\n");
	printf("Invalid Input Examples\n");
	printf("x + y\tyx\ta+b\t1/3x\t+/- ...\n");
	printf("Tip: Enter C To Clear Screen\n\n");
}

void ClearScreen()
{
	system("cls");
	PrintTitleWords();
}

void ClearStdin()
{
	char ch;
	while ((ch = getc(stdin)) != '\n')
		continue;
}

int main(int argc, char* argv[])
{
	term *expr1Head = NULL, *expr2Head = NULL;
	char inputChar = 0; // To judge is there any more questions to solve

	ClearScreen();	
	do
	{
		// Input expression 1
		do
		{
			printf("Please Enter Expression 1> ");
			expr1Head = ReadInExpr();
			ClearStdin();
		} while (expr1Head == NULL);
		// Input expression 2
		do
		{
			printf("Please Enter Expression 2> ");
			expr2Head = ReadInExpr();
			ClearStdin();
		} while (expr2Head == NULL);
		// Calculate result
		term *plusHead = Plus(expr1Head, expr2Head);
		term *minusHead = Minus(expr1Head, expr2Head);
		term *multiplyHead = Multiply(expr1Head, expr2Head);
		// Display result
		printf("Plus Result: ");
		PrintResult(plusHead);
		printf("Minus Result: ");
		PrintResult(minusHead);
		printf("Multiply Result: ");
		PrintResult(multiplyHead);
		// Delete all temp expressions
		DeleteAllTerm(&expr1Head);
		DeleteAllTerm(&expr2Head);
		DeleteAllTerm(&plusHead);
		DeleteAllTerm(&minusHead);
		DeleteAllTerm(&multiplyHead);
		// Ask is any more questions to solve
		printf("Next Problem?(Y/N)>");
		inputChar = getchar();
		if (inputChar == 'c' || inputChar == 'C')
			ClearScreen();
		ClearStdin();
	} while (inputChar != 'n' && inputChar != 'N');
	return 0;
}
