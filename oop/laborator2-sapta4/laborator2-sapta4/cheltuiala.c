#include "cheltuiala.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Expense* createExpense(int apartment, float sum, const char* type) {
    Expense* e = malloc(sizeof(Expense));
    e->apartment = apartment;
    e->sum = sum;
    size_t nrC = strlen(type) + 1;
    e->type = malloc(nrC * sizeof(char));
    strcpy_s(e->type, nrC, type);
    return e;
}

void copyExpense(Expense* dest, const Expense* src) {
    dest->apartment = src->apartment;
    dest->sum = src->sum;
    if(dest->type!= NULL)
        free(dest->type);
    dest->type = malloc((strlen(src->type)+1) * sizeof(char));
    strcpy_s(dest->type, strlen(src->type)+1, src->type);
}

Expense* deepCopyExpense(Expense* e)
{
    Expense* nou = createExpense(e->apartment, e->sum, e->type);
    return nou;
}

int compareExpenses(const Expense* a, const Expense* b) {
    if (a->apartment != b->apartment) return a->apartment - b->apartment;
    if (a->sum != b->sum) return (a->sum > b->sum) ? 1 : -1;
    return strcmp(a->type, b->type);
}

void printExpense(const Expense* e) {
if(e != NULL)
    printf("Apartament: %d, Suma: %.2f, Tip: %s\n", e->apartment, e->sum, e->type);
}

void destroyExpense(Expense* e)
{
    if (e == NULL) return;
    if (e->type != NULL) free(e->type);
    free(e);
}