#include "linkList.h"
#include <stdlib.h>

term* CreateTerm(const double coe, const double x_exp, const double y_exp)
{
	term* p = (term*)malloc(sizeof(term));
	if (p == NULL)
		return NULL;
	p->coe = coe;
	p->x_exp = x_exp;
	p->y_exp = y_exp;
	p->next = NULL;
	return p;
}

term* InsertTerm(term* t, term* head)
{
	if (t == NULL && head == NULL)
		return NULL;
	if (t == NULL || t->coe == 0)
		return head;
	if (head == NULL)
		return t;

	int cmp = CompareTermExponential(t, head);
	if (cmp == 1)
	{
		t->next = head;
		return t;
	}
	else if (cmp == 0)
	{
		head->coe += t->coe;
		return head;
	}

	term* p = head;
	while (p->next != NULL)
	{
		cmp = CompareTermExponential(t, p->next);
		if (cmp == 1)
		{
			t->next = p->next;
			p->next = t;
			return head;			
		}
		if (cmp == 0)
		{
			p->next->coe += t->coe;
			if (p->next->coe == 0)
			{
				term* temp = p->next->next;
				free(p->next);
				p->next = temp;
			}
			return head;
		}
		p = p->next;
	}
	p->next = t;
	return head;
}

void DeleteAllTerm(term** head)
{
	term* p = *head;
	while (p != NULL)
	{
		term* temp = p->next;
		free(p);
		p = temp;		
	}
	*head = NULL;
}

double GetTermExponential(const term* t)
{
	if (t == NULL)
		return 0;
	return t->x_exp + t->y_exp;
}

int CompareTermExponential(const term* t1, const term* t2)
{
	if (t1 == NULL && t2 == NULL)
		return 0;
	if (t1 == NULL)
		return -1;
	if (t2 == NULL)
		return 1;
	double t1_exp = GetTermExponential(t1);
	double t2_exp = GetTermExponential(t2);
	if (t1_exp > t2_exp)
		return 1;
	else if (t1_exp < t2_exp)
		return -1;
	else
	{
		if (t1->x_exp > t2->x_exp)
			return 1;
		else if (t1->x_exp < t2->x_exp)
			return -1;
		else
			return 0;
	}
}

term* Plus(term* expr1Head, term* expr2Head)
{
	term *p = NULL, *resHead = NULL;	
	p = expr1Head;
	while (p != NULL)
	{
		resHead = InsertTerm(CreateTerm(p->coe, p->x_exp, p->y_exp), resHead);
		p = p->next;
	}
	p = expr2Head;
	while (p != NULL)
	{
		resHead = InsertTerm(CreateTerm(p->coe, p->x_exp, p->y_exp), resHead);
		p = p->next;
	}
	return resHead;
}

term* Minus(term* expr1Head, term* expr2Head)
{
	term *p = NULL, *resHead = NULL;	
	p = expr1Head;
	while (p != NULL)
	{
		resHead = InsertTerm(CreateTerm(p->coe, p->x_exp, p->y_exp), resHead);
		p = p->next;
	}
	p = expr2Head;
	while (p != NULL)
	{
		resHead = InsertTerm(CreateTerm(-(p->coe), p->x_exp, p->y_exp), resHead);
		p = p->next;
	}
	return resHead;
}

term* Multiply(term* expr1Head, term* expr2Head)
{
	term *p1 = expr1Head, *p2 = expr2Head;
	term *resHead = NULL;
	while (p1 != NULL)
	{
		while (p2 != NULL)
		{
			resHead = InsertTerm(CreateTerm((p1->coe)*(p2->coe), 
				(p1->x_exp)+(p2->x_exp), (p1->y_exp)+(p2->y_exp)), resHead);
			p2 = p2->next;
		}
		p2 = expr2Head;
		p1 = p1->next;
	}
	return resHead;
}
