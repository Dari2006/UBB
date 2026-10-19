#ifndef REPO_H
#define REPO_H

#include "vector.h"

typedef struct {
    Vector* expenses;
} Repo;

Repo* createRepo();
void destroyRepo(Repo* r);
void addExpenseRepo(Repo* r, ElemType e);
void updateExpenseRepo(Repo* r, int index, ElemType e);
void deleteExpenseRepo(Repo* r, int index);
Vector* getAllExpensesRepo(Repo* r);
int findExpenseByIndex(Repo* r, int apartment, float sum, const char* type);

#endif
