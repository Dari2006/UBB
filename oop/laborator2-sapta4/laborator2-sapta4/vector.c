#include "vector.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
 * createVector
 * Parametri:
 *   - int capacity: capacitatea initiala a vectorului
 * Ce face:
 *   - aloca si initializeaza un Vector ce poate stoca Expense-uri
 * Return:
 *   - Vector*: pointer la vectorul creat (trebuie eliberat cu destroyVector)
 */
Vector* createVector(int capacity) {
    Vector* v = malloc(sizeof(Vector));
    if(v == NULL) return NULL;
    if(capacity <= 0)  capacity = 1;
    v->data = malloc(capacity * sizeof(ElemType));
    v->size = 0;
    v->capacity = capacity;
    for(int i = 0; i < v->capacity; i++)
        v->data[i] = NULL;
    return v;
}

/*
 * destroyVector
 * Parametri:
 *   - Vector* v: pointer la vector creat
 * Ce face:
 *   - elibereaza memoria alocata pentru date si pentru structura Vector
 * Return:
 *   - void
 */
void destroyVector(Vector* v, DestroyFunction destrF) {
    if(v == NULL) return;
       
    for (int i = 0; i < v->size; i++)
    {
        if (v->data[i] != NULL)
        {
            ElemType e = v->data[i];
            if(destrF != NULL)
                destrF(e);
        }
    }
    if(v->data != NULL)
        free(v->data);
    free(v);
}

void destroyVectorOnly(Vector* v)
{
    if(v == NULL) return;
       
    if(v->data != NULL)
        free(v->data);
    free(v);
}

void destroyListaExpense(Vector* v) {
    destroyVector(v, destroyExpense);
}

/*
 * addToVector
 * Parametri:
 *   - Vector* v: pointer la vector
 *   - Expense e: elementul de adaugat
 * Ce face:
 *   - redimensioneaza vectorul daca e nevoie si adauga elementul la sfarsit
 * Return:
 *   - void
 */
void addToVector(Vector* v, ElemType e) {
    if (v->size == v->capacity) {
        resizeVector(v, v->capacity * 2);
    }
    v->data[v->size++] = e;
}

/*
 * removeFromVector
 * Parametri:
 *   - Vector* v: pointer la vector
 *   - int index: pozitia elementului de sters
 * Ce face:
 *   - daca index este valid, muta elementele si scade dimensiunea
 * Return:
 *   - void
 */
void removeFromVector(Vector* v, int index) {
    if (index < 0 || index >= v->size) return;
    destroyExpense(v->data[index]);
    for (int i = index; i < v->size - 1; i++) {
        v->data[i] = v->data[i + 1];
    }
    v->data[v->size - 1] = NULL;
    v->size--;
}

ElemType popFromVector(Vector* v)
{
    if (v == NULL || v->size == 0) return NULL;
	ElemType e = v->data[v->size - 1];
	v->data[v->size - 1] = NULL;
    v->size--;
    return e;
}

/*
 * setVectorElement
 * Parametri:
 *   - Vector* v: pointer la vector
 *   - int index: pozitia elementului de modificat
 *   - Expense e: noua valoare
 * Ce face:
 *   - seteaza elementul de la pozitia index la valoarea e daca index este valid
 * Return:
 *   - void
 */
void setVectorElement(Vector* v, int index, ElemType e) {
    if (index >= 0 && index < v->size) {
        destroyExpense(v->data[index]);
        v->data[index] = e;
    }
}

/*
 * getVectorElement
 * Parametri:
 *   - const Vector* v: pointer la vector
 *   - int index: pozitia elementului de returnat
 * Ce face:
 *   - returneaza o copie a elementului de la pozitia index (fara validare)
 * Return:
 *   - Expense: valoarea elementului
 */
ElemType getVectorElement(const Vector* v, int index) {
    return v->data[index];
}

/*
 * getVectorSize
 * Parametri:
 *   - const Vector* v: pointer la vector
 * Ce face:
 *   - intoarce numarul de elemente stocate in vector
 * Return:
 *   - int: dimensiunea vectorului
 */
int getVectorSize(const Vector* v) {
    return v->size;
}

/*
 * resizeVector
 * Parametri:
 *   - Vector* v: pointer la vector
 *   - int newCapacity: noua capacitate dorita
 * Ce face:
 *   - realoca buffer-ul intern la noua capacitate
 * Return:
 *   - void
 */
void resizeVector(Vector* v, int newCapacity) {
    ElemType* newData = malloc(newCapacity * sizeof(ElemType));
    for(int i = 0; i < v->size; i++)
        newData[i] = v->data[i];
    for(int i = v->size; i < newCapacity; i++)
        newData[i] = NULL;
    free(v->data);
    v->data = newData;
    v->capacity = newCapacity;
}

Vector* copyVector(Vector* v, CopyFunction copyF)
{
    Vector* nou = createVector(v->capacity);
    for (int i = 0; i < v->size; i++)
    {
        void* e = copyF(v->data[i]);   //aici apelam functia cu deepCopyExpense(parametrul copyF e o fct generica de copiere)
        addToVector(nou, e);
    }
    return nou;
}
