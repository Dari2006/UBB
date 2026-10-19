#ifndef VECTOR_H
#define VECTOR_H

#include "cheltuiala.h"
typedef void* ElemType;
typedef void (*DestroyFunction)(ElemType);
typedef void* (*CopyFunction)(void*);
      // ^              ^       ^-----------ce parametru primeste functia
      // |      pointer catre o functie
    //ce returneaza

typedef struct {
    ElemType* data;     //Expense** data
    int size;
    int capacity;
} Vector;

Vector* createVector(int capacity);
void destroyVector(Vector* v, DestroyFunction destrF);
void addToVector(Vector* v, ElemType e);
void removeFromVector(Vector* v, int index);
void setVectorElement(Vector* v, int index, ElemType e);
ElemType getVectorElement(const Vector* v, int index);
int getVectorSize(const Vector* v);
void resizeVector(Vector* v, int newCapacity);
void destroyVectorOnly(Vector* v);
void destroyListaExpense(Vector* v);
Vector* copyVector(Vector* v, CopyFunction copyF);
ElemType popFromVector(Vector* v);

#endif
