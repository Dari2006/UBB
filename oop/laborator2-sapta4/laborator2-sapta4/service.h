#ifndef SERVICE_H
#define SERVICE_H

#include "repo.h"

typedef struct {
    Repo* repo;
    Vector* undoL;
} Service;

Service* createService(Repo* r);
void destroyService(Service* s);
int addExpenseService(Service* s, int apartment, float sum, const char* type);
int updateExpenseService(Service* s, int oldApartment, float oldSum, const char* oldType, int newApartment, float newSum, const char* newType);
int deleteExpenseService(Service* s, int apartment, float sum, const char* type);
Vector* filterByApartmentService(Service* s, int apartment);
Vector* filterByTypeService(Service* s, const char* type);
Vector* filterBySumGreaterService(Service* s, float sum);

// Sortare simpla, fara comparator
Vector* sortBySumAscService(Service* s);
Vector* sortBySumDescService(Service* s);
Vector* sortByTypeAscService(Service* s);
Vector* sortByTypeDescService(Service* s);
// Sorteaza folosind comparatorul implicit (defaultCompare) din service.c
Vector* sortDefaultService(Service* s);

// Sortare cu comparator
Vector* sortBySumAscServiceCmp(Service* s, int (*cmp)(const ElemType, const ElemType, void*), void* param);
Vector* sortBySumDescServiceCmp(Service* s, int (*cmp)(const ElemType, const ElemType, void*), void* param);
Vector* sortByTypeAscServiceCmp(Service* s, int (*cmp)(const ElemType, const ElemType, void*), void* param);
Vector* sortByTypeDescServiceCmp(Service* s, int (*cmp)(const ElemType, const ElemType, void*), void* param);
int validateExpense(int apartment, float sum, const char* type);
void undo(Service* s);

#endif
