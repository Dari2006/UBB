#include "repo.h"
#include <string.h>
#include <stdlib.h>

/*
 * createRepo
 * Parametri:
 *   - none
 * Ce face:
 *   - aloca si initializeaza un Repo cu un Vector intern pentru cheltuieli
 * Return:
 *   - Repo*: pointer la repository-ul creat (trebuie eliberat cu destroyRepo)
 */
Repo* createRepo() {
    Repo* r = malloc(sizeof(Repo));
    if(r!=NULL)
    {
        r->expenses = createVector(10);}
    return r;
}

/*
 * destroyRepo
 * Parametri:
 *   - Repo* r: pointer la repository creat
 * Ce face:
 *   - elibereaza vectorul intern de cheltuieli si memoria repository-ului
 * Return:
 *   - void
 */
void destroyRepo(Repo* r) {
    if(r == NULL) return;
       
    if(r->expenses != NULL)
        destroyVector(r->expenses, destroyExpense);
    free(r);
}

/*
 * addExpenseRepo
 * Parametri:
 *   - Repo* r: pointer la repository
 *   - Expense e: cheltuiala de adaugat
 * Ce face:
 *   - adauga cheltuiala in vectorul intern
 * Return:
 *   - void
 */
void addExpenseRepo(Repo* r, ElemType e) {
    addToVector(r->expenses, e);
}

/*
 * updateExpenseRepo
 * Parametri:
 *   - Repo* r: pointer la repository
 *   - int index: pozitia elementului de modificat
 *   - Expense e: noile date ale cheltuielii
 * Ce face:
 *   - inlocuieste elementul de la index cu noua cheltuiala
 * Return:
 *   - void
 */
void updateExpenseRepo(Repo* r, int index, ElemType e) {
    setVectorElement(r->expenses, index, e);
}

/*
 * deleteExpenseRepo
 * Parametri:
 *   - Repo* r: pointer la repository
 *   - int index: pozitia elementului de sters
 * Ce face:
 *   - sterge elementul de la pozitia index din vectorul intern
 * Return:
 *   - void
 */
void deleteExpenseRepo(Repo* r, int index) {
    removeFromVector(r->expenses, index);
}

/*
 * getAllExpensesRepo
 * Parametri:
 *   - Repo* r: pointer la repository
 * Ce face:
 *   - returneaza pointerul la vectorul intern ce contine toate cheltuielile
 * Return:
 *   - Vector*: pointer la vectorul intern (nu elibereaza memoria)
 */
Vector* getAllExpensesRepo(Repo* r) {
    return r->expenses;
}

/*
 * findExpenseByIndex
 * Parametri:
 *   - Repo* r: pointer la repository
 *   - int apartment, float sum, const char* type: campurile dupa care se cauta
 * Ce face:
 *   - cauta prima aparitie a unei cheltuieli care are campurile identice cu cele date
 * Return:
 *   - int: indexul gasit sau -1 daca nu exista
 */
int findExpenseByIndex(Repo* r, int apartment, float sum, const char* type) {
    for (int i = 0; i < getVectorSize(r->expenses); i++) {
        Expense* e = getVectorElement(r->expenses, i);
        if (e->apartment == apartment && e->sum == sum && strcmp(e->type, type) == 0) {
            return i;}}

    return -1;
}
