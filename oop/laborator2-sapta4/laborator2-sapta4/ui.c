#include "ui.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * printMenu
 * Parametri:
 *   - none
 * Ce face:
 *   - afiseaza meniul principal in consola
 * Return:
 *   - void
 */
void printMenu() {
    printf("\n--- Administrator Imobil ---\n");
    printf("1. Adauga cheltuiala\n");
    printf("2. Modifica cheltuiala\n");
    printf("3. Sterge cheltuiala\n");
    printf("4. Vizualizare filtrata\n");
    printf("5. Vizualizare ordonata\n");
    printf("6. Undo\n");
    printf("0. Iesire\n");
    printf("Alegeti optiunea: ");
}

/*
 * printExpenses
 * Parametri:
 *   - Vector* v: pointer la vectorul de afisat
 * Ce face:
 *   - afiseaza toate cheltuielile din vector (apel metoda printExpense pentru fiecare element)
 * Return:
 *   - void
 */
void printExpenses(Vector* v) {
    if (getVectorSize(v) == 0) {
        printf("Nu exista cheltuieli.\n");
        return;
    }
    for (int i = 0; i < getVectorSize(v); i++) {
        Expense* e = getVectorElement(v, i);
        printExpense(e);
    }
}

/*
 * addExpenseUI
 * Parametri:
 *   - Service* s: pointer la Service
 * Ce face:
 *   - citeste de la utilizator campurile unei cheltuieli si apeleaza addExpenseService
 * Return:
 *   - void
 */
void addExpenseUI(Service* s) {
    int apartment;
    float sum;
    char type[20];
    printf("Apartament: ");
    scanf_s("%d", &apartment);
    printf("Suma: ");
    scanf_s("%f", &sum);
    printf("Tip (apa/canal/incalzire/gaz): ");
    scanf_s("%19s", type, (unsigned)sizeof(type));
    if (addExpenseService(s, apartment, sum, type)) {
        printf("Cheltuiala adaugata cu succes.\n");
    }
    else {
        printf("Date invalide.\n");
    }
}

/*
 * updateExpenseUI
 * Parametri:
 *   - Service* s: pointer la Service
 * Ce face:
 *   - citeste datele vechi si noile date ale unei cheltuieli si apeleaza updateExpenseService
 * Return:
 *   - void
 */
void updateExpenseUI(Service* s) {
    int oldApartment, newApartment;
    float oldSum, newSum;
    char oldType[20], newType[20];
    printf("Apartament vechi: ");
    scanf_s("%d", &oldApartment);
    printf("Suma veche: ");
    scanf_s("%f", &oldSum);
    printf("Tip vechi: ");
    scanf_s("%19s", oldType, (unsigned)sizeof(oldType));
    printf("Apartament nou: ");
    scanf_s("%d", &newApartment);
    printf("Suma noua: ");
    scanf_s("%f", &newSum);
    printf("Tip nou: ");
    scanf_s("%19s", newType, (unsigned)sizeof(newType));
    if (updateExpenseService(s, oldApartment, oldSum, oldType, newApartment, newSum, newType)) {
        printf("Cheltuiala modificata cu succes.\n");
    }
    else {
        printf("Cheltuiala nu exista sau date invalide.\n");
    }
}

/*
 * deleteExpenseUI
 * Parametri:
 *   - Service* s: pointer la Service
 * Ce face:
 *   - citeste identificatorii unei cheltuieli si apeleaza deleteExpenseService
 * Return:
 *   - void
 */
void deleteExpenseUI(Service* s) {
    int apartment;
    float sum;
    char type[20];
    printf("Apartament: ");
    scanf_s("%d", &apartment);
    printf("Suma: ");
    scanf_s("%f", &sum);
    printf("Tip: ");
    scanf_s("%19s", type, (unsigned)sizeof(type));
    if (deleteExpenseService(s, apartment, sum, type)) {
        printf("Cheltuiala stearsa cu succes.\n");
    }
    else {
        printf("Cheltuiala nu exista.\n");
    }
}

/*
 * filterUI
 * Parametri:
 *   - Service* s: pointer la Service
 * Ce face:
 *   - afiseaza optiunile de filtrare, citeste optiunea si parametrii corespunzatori, apeleaza functia de filtrare
 * Return:
 *   - void
 */
void filterUI(Service* s) {
    int option;
    printf("Filtrare dupa:\n");
    printf("1. Apartament\n");
    printf("2. Tip\n");
    printf("3. Suma >=\n");
    scanf_s("%d", &option);
    Vector* filtered = NULL;
    if (option == 1) {
        int apartment;
        printf("Apartament: ");
        scanf_s("%d", &apartment);
        filtered = filterByApartmentService(s, apartment);
    }
    else if (option == 2) {
        char type[20];
        printf("Tip: ");
        scanf_s("%19s", type, (unsigned)sizeof(type));
        filtered = filterByTypeService(s, type);
    }
    else if (option == 3) {
        float sum;
        printf("Suma minima: ");
        scanf_s("%f", &sum);
        filtered = filterBySumGreaterService(s, sum);
    }
    if (filtered) {
        printExpenses(filtered);
        destroyVector(filtered, destroyExpense);
    }
    else {
        printf("Optiune invalida.\n");
    }
}

/*
 * sortUI
 * Parametri:
 *   - Service* s: pointer la Service
 * Ce face:
 *   - afiseaza optiunile de sortare, citeste optiunea si ordinea si afiseaza lista sortata
 * Return:
 *   - void
 */
void sortUI(Service* s) {
    int option, order;
    printf("Ordonare dupa:\n");
    printf("1. Suma\n");
    printf("2. Tip\n");
    scanf_s("%d", &option);
    printf("Ordine: 1. Crescator 2. Descrescator\n");
    scanf_s("%d", &order);
    Vector* sorted = NULL;
    if (option == 1) {
        if (order == 1) sorted = sortBySumAscService(s);
        else sorted = sortBySumDescService(s);
    }
    else if (option == 2) {
        if (order == 1) sorted = sortByTypeAscService(s);
        else sorted = sortByTypeDescService(s);
    }
    if (sorted) {
        printExpenses(sorted);
        destroyVector(sorted, destroyExpense);
    }
    else {
        printf("Optiune invalida.\n");
    }
}




void runUI(Service* s) {
    int option = -1;
    while (option != 0) {
        printMenu();
        scanf_s("%d", &option);
        if (option == 1) addExpenseUI(s);
        else if (option == 2) updateExpenseUI(s);
        else if (option == 3) deleteExpenseUI(s);
        else if (option == 4) filterUI(s);
        else if (option == 5) sortUI(s);
        else if(option == 6) undo(s);
        else if (option != 0) printf("Optiune invalida.\n");
    }
}


