#ifndef EXPENSE_H
#define EXPENSE_H

typedef struct {
    int apartment;
    float sum;
    char* type;
} Expense;

Expense* createExpense(int apartment, float sum, const char* type);
void copyExpense(Expense* dest, const Expense* src);
int compareExpenses(const Expense* a, const Expense* b);
void printExpense(const Expense* e);
Expense* deepCopyExpense(Expense* e);
void destroyExpense(Expense* e);

#endif
