#include "service.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*
 * createService
 * Parametri:
 *   - Repo* r: pointer la repository-ul de cheltuieli
 * Ce face:
 *   - aloca si initializeaza o structura Service care retine pointerul la repo
 * Return:
 *   - Service*: pointer la Service-ul creat (trebuie eliberat cu destroyService)
 */
Service* createService(Repo* r) {
    Service* s = malloc(sizeof(Service));
    s->repo = r;
    Vector* undoL = createVector(r->expenses->capacity);
    s->undoL = undoL;
    return s;
}

/*
 * destroyService
 * Parametri:
 *   - Service* s: pointer la Service creat
 * Ce face:
 *   - elibereaza memoria ocupata de structura Service
 * Observatii:
 *   - nu elibereaza Repo-ul din interiorul Service
 * Return:
 *   - void
 */
void destroyService(Service* s) {
    if(s == NULL) return;
    destroyVector(s->undoL, (DestroyFunction)destroyListaExpense);
    free(s);
}

/*
 * validateExpense
 * Parametri:
 *   - int apartment: numarul apartamentului (trebuie > 0)
 *   - float sum: suma cheltuielii (trebuie > 0)
 *   - const char* type: tipul cheltuielii ("apa", "canal", "incalzire", "gaz")
 * Ce face:
 *   - verifica validitatea campurilor unei cheltuieli conform regulilor simple
 * Return:
 *   - int: 1 daca datele sunt valide, 0 altfel
 */
int validateExpense(int apartment, float sum, const char* type) {
    if (apartment <= 0) return 0;
    if (sum <= 0) return 0;
    if (strcmp(type, "apa") != 0 && strcmp(type, "canal") != 0 && strcmp(type, "incalzire") != 0 && strcmp(type, "gaz") != 0) return 0;
    return 1;
}

/*
 * addExpenseService
 * Parametri:
 *   - Service* s: pointer la Service
 *   - int apartment, float sum, const char* type: campurile cheltuielii de adaugat
 * Ce face:
 *   - valideaza campurile si, daca sunt valide, creeaza un Expense si il adauga in repo
 * Return:
 *   - int: 1 la succes, 0 daca datele sunt invalide
 */
int addExpenseService(Service* s, int apartment, float sum, const char* type) {
    if (!validateExpense(apartment, sum, type)) return 0;
    Vector* copie = copyVector(s->repo->expenses, (CopyFunction)deepCopyExpense);
    addToVector(s->undoL, copie);
    Expense* e = createExpense(apartment, sum, type);
    addExpenseRepo(s->repo, e);
    return 1;
}

/*
 * updateExpenseService
 * Parametri:
 *   - Service* s: pointer la Service
 *   - int oldApartment, float oldSum, const char* oldType: identificatori pentru cheltuiala existenta
 *   - int newApartment, float newSum, const char* newType: noile valori pentru cheltuiala
 * Ce face:
 *   - valideaza noile valori, gaseste indexul cheltuielii existente si o inlocuieste cu noile date
 * Return:
 *   - int: 1 la succes, 0 daca datele sunt invalide sau cheltuiala nu exista
 */
int updateExpenseService(Service* s, int oldApartment, float oldSum, const char* oldType, int newApartment, float newSum, const char* newType) {
    if (!validateExpense(newApartment, newSum, newType)) return 0;
    int index = findExpenseByIndex(s->repo, oldApartment, oldSum, oldType);
    if (index == -1) return 0;
    Vector* copie = copyVector(s->repo->expenses, (CopyFunction)deepCopyExpense);
    addToVector(s->undoL, copie);
    Expense* e = createExpense(newApartment, newSum, newType);
    updateExpenseRepo(s->repo, index, e);
    return 1;
}

/*
 * deleteExpenseService
 * Parametri:
 *   - Service* s: pointer la Service
 *   - int apartment, float sum, const char* type: identificatorii cheltuielii de sters
 * Ce face:
 *   - cauta cheltuiala in repo si o sterge daca exista
 * Return:
 *   - int: 1 la succes, 0 daca cheltuiala nu a fost gasita
 */
int deleteExpenseService(Service* s, int apartment, float sum, const char* type) {
    int index = findExpenseByIndex(s->repo, apartment, sum, type);
    if (index == -1) return 0;
    Vector* copie = copyVector(s->repo->expenses, (CopyFunction)deepCopyExpense);
    addToVector(s->undoL, copie);
    deleteExpenseRepo(s->repo, index);
    return 1;
}

void undo(Service* s)
{
    if (s == NULL || s->undoL == NULL) return;
    if (s->undoL->size == 0) return;

    Vector* nou = (Vector*)popFromVector(s->undoL);
    if (nou == NULL) return;

    destroyVector(s->repo->expenses, destroyExpense);
    s->repo->expenses = nou;
}

/*
 * filterByApartmentService
 * Parametri:
 *   - Service* s: pointer la Service
 *   - int apartment: numarul apartamentului pentru filtrare
 * Ce face:
 *   - construieste si returneaza un Vector nou cu cheltuielile care au campul apartment egal cu valoarea data
 * Return:
 *   - Vector*: pointer la vectorul rezultat; apelantul trebuie sa elibereze cu destroyVector
 */
Vector* filterByApartmentService(Service* s, int apartment) {
    Vector* all = getAllExpensesRepo(s->repo);
    Vector* filtered = createVector(10);
    for (int i = 0; i < getVectorSize(all); i++) {
        Expense* e = getVectorElement(all, i);
        if (e->apartment == apartment) {
            addToVector(filtered, e);
        }
    }
    return filtered;
}

/*
 * filterByTypeService
4 * Parametri:
 *   - Service* s: pointer la Service
 *   - const char* type: tipul pentru filtrare
 * Ce face:
 *   - construieste si returneaza un Vector nou cu cheltuielile care au campul type egal cu valoarea data
 * Return:
 *   - Vector*: pointer la vectorul rezultat; apelantul trebuie sa elibereze cu destroyVector
 */
Vector* filterByTypeService(Service* s, const char* type) {
    Vector* all = getAllExpensesRepo(s->repo);
    Vector* filtered = createVector(10);
    for (int i = 0; i < getVectorSize(all); i++) {
        Expense* e = getVectorElement(all, i);
        if (strcmp(e->type, type) == 0) {
            addToVector(filtered, e);
        }
    }
    return filtered;
}

/*
 * filterBySumGreaterService
 * Parametri:
 *   - Service* s: pointer la Service
 *   - float sum: pragul minim pentru suma
 * Ce face:
 *   - construieste si returneaza un Vector nou cu cheltuielile care au suma >= sum
 * Return:
 *   - Vector*: pointer la vectorul rezultat; apelantul trebuie sa elibereze cu destroyVector
 */
Vector* filterBySumGreaterService(Service* s, float sum) {
    Vector* all = getAllExpensesRepo(s->repo);
    Vector* filtered = createVector(10);
    for (int i = 0; i < getVectorSize(all); i++) {
        Expense* e = getVectorElement(all, i);
        if (e->sum >= sum) {
            addToVector(filtered, e);
        }
    }
    return filtered;
}

// functiile cu comparatori
/*
 * defaultCompare (static)
 * Parametri:
 *   - const Expense* a, const Expense* b: elementele de comparat
 *   - void* p: parametru auxiliar (ignorata)
 * Ce face:
 *   - wrapper care apeleaza compareExpenses pentru comparare completa (apartment, sum, type)
 * Return:
 *   - int: <0 daca a < b, 0 daca egal, >0 daca a > b
 */
static int defaultCompare(const ElemType a, const ElemType b, void* p) {
    (void)p;
    return compareExpenses(a, b);
}

/*
 * compareBySum (static)
 * Parametri:
 *   - const Expense* a, const Expense* b: elementele de comparat
 *   - void* p: parametru auxiliar (ignorata)
 * Ce face:
 *   - compara doar campul sum al celor doua cheltuieli
 * Return:
 *   - int: -1 daca a->sum < b->sum, 1 daca a->sum > b->sum, 0 daca egale
 */
static int compareBySum(const Expense* a, const Expense* b, void* p) {
    (void)p;
    if (a->sum < b->sum) return -1;
    if (a->sum > b->sum) return 1;return 0;
    
}

/*
 * compareByType (static)
 * Parametri:
 *   - const Expense* a, const Expense* b: elementele de comparat
 *   - void* p: parametru auxiliar (ignorata)
 * Ce face:
 *   - compara lexicografic campul type folosind strcmp
 * Return:
 *   - int: rezultat strcmp (<0, 0, >0)
 */
static int compareByType(const Expense* a, const Expense* b, void* p) {
    (void)p;
    return strcmp(a->type, b->type);
}

// bubble sort cu comparator
/*
 * sortWithComparator (static)
 * Parametri:
 *   - Service* s: service care furnizeaza repo-ul
 *   - int ascending: 1 pentru ordonare crescatoare, 0 pentru descrescatoare
 *   - int (*cmp)(const Expense*, const Expense*, void*): functie de comparare; daca NULL se foloseste defaultCompare
 *   - void* param: parametru auxiliar transmis functiei de comparare (poate fi NULL)
 * Ce face:
 *   - construieste o copie a elementelor din repo intr-un Vector nou si aplica bubble-sort folosind comparatorul
 * Return:
 *   - Vector*: pointer la vectorul sortat (apelantul trebuie sa elibereze)
 */
static Vector* sortWithComparator(Service* s, int ascending, int (*cmp)(const ElemType, const ElemType, void*), void* param) {
    Vector* all = getAllExpensesRepo(s->repo);
    Vector* sorted = createVector(getVectorSize(all));

    for (int i = 0; i < getVectorSize(all); i++) {
        addToVector(sorted, getVectorElement(all, i));
    }
    if (cmp == NULL) cmp = defaultCompare;

    int n = getVectorSize(sorted);
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            ElemType a = getVectorElement(sorted, j);
            ElemType b = getVectorElement(sorted, j + 1);
            int res = cmp(a, b, param);
            if ((ascending && res > 0) || (!ascending && res < 0)) {
               // setVectorElement(sorted, j, b);
                //setVectorElement(sorted, j + 1, a);
                ElemType aux = a;
                sorted->data[j] = b;
                sorted->data[j+1] = aux;
            }
        }
    }
    return sorted;
}
// Comparator-enabled APIs (Cmp suffix)
Vector* sortBySumAscServiceCmp(Service* s, int (*cmp)(const ElemType, const ElemType, void*), void* param) {
    /*
     * sortBySumAscServiceCmp
     * Parametri:
     *   - Service* s: pointer la Service
     *   - int (*cmp)(const Expense*, const Expense*, void*): functie de comparare personalizata (poate fi NULL)
     *   - void* param: parametru auxiliar pentru comparator
     * Ce face:
     *   - sorteaza crescator folosind comparatorul furnizat sau comparatorul implicit dupa suma
     * Return:
     *   - Vector*: pointer la vectorul sortat (apelantul trebuie sa elibereze)
     */
    if (cmp == NULL) cmp = compareBySum;
    return sortWithComparator(s, 1, cmp, param);
}

Vector* sortBySumDescServiceCmp(Service* s, int (*cmp)(const ElemType, const ElemType, void*), void* param) {
    /*
     * sortBySumDescServiceCmp
     * Parametri:
     *   - Service* s: pointer la Service
     *   - int (*cmp)(const Expense*, const Expense*, void*): functie de comparare personalizata (poate fi NULL)
     *   - void* param: parametru auxiliar pentru comparator
     * Ce face:
     *   - sorteaza descrescator folosind comparatorul furnizat sau comparatorul implicit dupa suma
     * Return:
     *   - Vector*: pointer la vectorul sortat (apelantul trebuie sa elibereze)
     */
    if (cmp == NULL) cmp = compareBySum;
    return sortWithComparator(s, 0, cmp, param);
}

Vector* sortByTypeAscServiceCmp(Service* s, int (*cmp)(const ElemType, const ElemType, void*), void* param) {
    /*
     * sortByTypeAscServiceCmp
     * Parametri:
     *   - Service* s: pointer la Service
     *   - int (*cmp)(const Expense*, const Expense*, void*): functie de comparare personalizata (poate fi NULL)
     *   - void* param: parametru auxiliar pentru comparator
     * Ce face:
     *   - sorteaza crescator dupa tip folosind comparatorul furnizat sau comparatorul implicit dupa type
     * Return:
     *   - Vector*: pointer la vectorul sortat (apelantul trebuie sa elibereze)
     */
    if (cmp == NULL) cmp = compareByType;
    return sortWithComparator(s, 1, cmp, param);
}

Vector* sortByTypeDescServiceCmp(Service* s, int (*cmp)(const ElemType, const ElemType, void*), void* param) {
    /*
     * sortByTypeDescServiceCmp
     * Parametri:
     *   - Service* s: pointer la Service
     *   - int (*cmp)(const Expense*, const Expense*, void*): functie de comparare personalizata (poate fi NULL)
     *   - void* param: parametru auxiliar pentru comparator
     * Ce face:
     *   - sorteaza descrescator dupa tip folosind comparatorul furnizat sau comparatorul implicit dupa type
     * Return:
     *   - Vector*: pointer la vectorul sortat (apelantul trebuie sa elibereze)
     */
    if (cmp == NULL) cmp = compareByType;
    return sortWithComparator(s, 0, cmp, param);
}

/*
 * sortBySumAscService
 * Parametri:
 *   - Service* s: pointer la Service
 * Ce face:
 *   - wrapper backward-compatible care apeleaza varianta cu comparator (implicit: compareBySum) pentru ordonare crescatoare
 * Return:
 *   - Vector*: pointer la vectorul sortat (apelantul trebuie sa elibereze)
 */
Vector* sortBySumAscService(Service* s) { return sortBySumAscServiceCmp(s, NULL, NULL); }

/*
 * sortBySumDescService
 * Parametri:
 *   - Service* s: pointer la Service
 * Ce face:
 *   - wrapper backward-compatible care apeleaza varianta cu comparator (implicit: compareBySum) pentru ordonare descrescatoare
 * Return:
 *   - Vector*: pointer la vectorul sortat (apelantul trebuie sa elibereze)
 */
Vector* sortBySumDescService(Service* s) { return sortBySumDescServiceCmp(s, NULL, NULL); }

/*
 * sortByTypeAscService
 * Parametri:
 *   - Service* s: pointer la Service
 * Ce face:
 *   - wrapper backward-compatible care apeleaza varianta cu comparator (implicit: compareByType) pentru ordonare crescatoare
 * Return:
 *   - Vector*: pointer la vectorul sortat (apelantul trebuie sa elibereze)
 */
Vector* sortByTypeAscService(Service* s) { return sortByTypeAscServiceCmp(s, NULL, NULL); }

/*
 * sortByTypeDescService
 * Parametri:
 *   - Service* s: pointer la Service
 * Ce face:
 *   - wrapper backward-compatible care apeleaza varianta cu comparator (implicit: compareByType) pentru ordonare descrescatoare
 * Return:
 *   - Vector*: pointer la vectorul sortat (apelantul trebuie sa elibereze)
 */
Vector* sortByTypeDescService(Service* s) { return sortByTypeDescServiceCmp(s, NULL, NULL); }

// Expose a wrapper that uses the internal default comparator (defaultCompare)
Vector* sortDefaultService(Service* s) {
    // Passing NULL comparator to sortWithComparator will cause it to use defaultCompare
    return sortWithComparator(s, 1, NULL, NULL);
}
