#ifndef UI_H
#define UI_H

#include "service.h"

void runUI(Service* s);
void printMenu();
void addExpenseUI(Service* s);
void updateExpenseUI(Service* s);
void deleteExpenseUI(Service* s);
void filterUI(Service* s);
void sortUI(Service* s);
void printExpenses(Vector* v);


#endif
