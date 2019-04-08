#ifndef __LINKLIST_H__
#define __LINKLIST_H__

#define ERROR_NULL_POINTER 2000

typedef struct term
{
	double coe;				// coefficient
	double x_exp;			// exponential
	double y_exp;
	struct term* next;
} term;

// To craete a term
// Return: the pointer of created term
// Caller should add the pointer to a linklist and delete it after using
term* CreateTerm(const double coe, const double x_exp, const double y_exp);
// To insert a term into a polynomial linklist
// The linklist is arranged in descending order by exponential
term* InsertTerm(term* t, term* head);
// To delete a linklist
void DeleteAllTerm(term** head);
// To calculate the exponential of the term
double GetTermExponential(const term* t);
// To compare exponential of two terms
// returnvalue: 0  t1 = t2
//              1  t1 > t2
//             -1  t1 < t2
// Notice: if one of the parameter equals NULL, it is smaller than the other
int CompareTermExponential(const term* t1, const term* t2);
// To get sum of two expressions
// returnvalue = expr1 + expr2
// The return linklist is arranged in descending order by exponential
term* Plus(term* expr1Head, term* expr2Head);
// To get difference between two expressions
// returnvalue = expr1 - expr2
// The return linklist is arranged in descending order by exponential
term* Minus(term* expr1Head, term* expr2Head);
// To get product of two expressions
// returnvalue = expr1 * expr2
// The return linklist is arranged in descending order by exponential
term* Multiply(term* expr1Head, term* expr2Head);

#endif