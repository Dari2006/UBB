#include "tests.h"
#include "cheltuiala.h"
#include "vector.h"
#include "repo.h"
#include "service.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

void testCreateExpense() {
    Expense* e = createExpense(1, 100.0, "apa");
    assert(e->apartment == 1);
    assert(e->sum == 100.0);
    assert(strcmp(e->type, "apa") == 0);
    destroyExpense(e);
    printf("testCreateExpense passed\n");

}

void testDefaultCompare() {
	Repo* r = createRepo();
	Service* s = createService(r);

	addExpenseService(s, 2, 150, "canal");
	addExpenseService(s, 1, 100, "apa");
	addExpenseService(s, 1, 200, "gaz");
	// defaultCompare delegates to compareExpenses: apartment, sum, type
	Vector* sorted = sortDefaultService(s);
	// expected order: apartment 1 (sum 100, type apa), apartment 1 (sum 200, type gaz), apartment 2 (sum 150, type canal)
	assert(((Expense*)getVectorElement(sorted, 0))->apartment == 1);
	assert(((Expense*)getVectorElement(sorted, 0))->sum == 100);
	assert(((Expense*)getVectorElement(sorted, 1))->apartment == 1);
	assert(((Expense*)getVectorElement(sorted, 1))->sum == 200);
	assert(((Expense*)getVectorElement(sorted, 2))->apartment == 2);

	destroyVectorOnly(sorted);

	destroyService(s);
	destroyRepo(r);
	printf("testDefaultCompare passed\n");
}

void testVector() {
    Vector* v = createVector(2);
    ElemType e1 = createExpense(1, 100, "apa");
    ElemType e2 = createExpense(2, 200, "gaz");
    addToVector(v, e1);
    addToVector(v, e2);
    assert(getVectorSize(v) == 2);
    Expense* e = getVectorElement(v, 0);  //acum e si e1 pointeaza catre aceeasi locatie
    assert(e->apartment == 1);
    removeFromVector(v, 0);   
    assert(getVectorSize(v) == 1);
    e = getVectorElement(v, 0);   //acum e pointeaza spre aceeasi locatie ca e2
    assert(e->apartment == 2);
    destroyVector(v, destroyExpense);
    printf("testVector passed\n");
}


void testVectorExtra() {
    Vector* v = createVector(1);
    ElemType e1 = createExpense(1, 10, "apa");
    ElemType e2 = createExpense(2, 20, "gaz");
    ElemType e3 = createExpense(3, 30, "curent");
    addToVector(v, e1); 
    addToVector(v, e2); 
    assert(getVectorSize(v) == 2);

    
    resizeVector(v, 10);
    assert(v->capacity == 10);
    //resizeVector(v, 1);
    
    setVectorElement(v, 0, e3);
    assert(((Expense*)getVectorElement(v, 0))->apartment == 3);
    setVectorElement(v, 10, e1); //asta teoretic nu face nimic

    
    removeFromVector(v, -1);  //nu face nmc
    assert(getVectorSize(v) == 2);
    removeFromVector(v, 0);
    assert(getVectorSize(v) == 1);
    printf("Acum stergem in testVectorExtra\n");
    destroyVector(v, destroyExpense);
    printf("testVectorExtra passed\n");
}

void testRepo() {
    Repo* r = createRepo();
    Expense* e = createExpense(1, 100, "apa");
    addExpenseRepo(r, e);
    Vector* all = getAllExpensesRepo(r);
    assert(getVectorSize(all) == 1);
    int index = findExpenseByIndex(r, 1, 100, "apa");
    assert(index == 0);
    updateExpenseRepo(r, 0, createExpense(1, 150, "apa"));
    e = getVectorElement(all, 0);
    assert(e->sum == 150);
    deleteExpenseRepo(r, 0);
    assert(getVectorSize(all) == 0);
    destroyRepo(r);
    printf("testRepo passed\n");
}


void testRepoExtra() {
    Repo* r = createRepo();
    
    int idx = findExpenseByIndex(r, 99, 1.0, "apa");
    assert(idx == -1);

    
    deleteExpenseRepo(r, 5);
    Vector* all = getAllExpensesRepo(r);
    assert(getVectorSize(all) == 0);


    Expense* e = createExpense(1, 100, "apa");
    addExpenseRepo(r, e);
    Expense* e2 = createExpense(2, 200, "gaz");
    updateExpenseRepo(r, 5, e2); 
    destroyExpense(e2);
   
    assert(((Expense*)getVectorElement(all, 0))->sum == 100);
    destroyRepo(r);
    printf("testRepoExtra passed\n");
}

void testService() {
    Repo* r = createRepo();
    Service* s = createService(r);
    assert(addExpenseService(s, 1, 100, "apa") == 1);
    assert(addExpenseService(s, 1, -10, "apa") == 0); 
    assert(addExpenseService(s, 1, 100, "invalid") == 0);
    Vector* all = getAllExpensesRepo(r);
    assert(getVectorSize(all) == 1);
    assert(updateExpenseService(s, 1, 100, "apa", 1, 200, "gaz") == 1);
    Expense* e = getVectorElement(all, 0);
    assert(e->sum == 200 && strcmp(e->type, "gaz") == 0);
    assert(deleteExpenseService(s, 1, 200, "gaz") == 1);
    assert(getVectorSize(all) == 0);
    destroyService(s);
    destroyRepo(r);
    printf("testService passed\n");
}


static int reverseSumCmp(const Expense* a, const Expense* b, void* p) {
    (void)p;
    if (a->sum < b->sum) return 1;
    if (a->sum > b->sum) return -1;return 0;
    
}

void testServiceExtra() {
    Repo* r = createRepo();
    Service* s = createService(r);

    
    assert(addExpenseService(s, 0, 10, "apa") == 0);
    assert(addExpenseService(s, 1, -5, "apa") == 0);
    assert(addExpenseService(s, 1, 10, "invalid") == 0);

    
    assert(updateExpenseService(s, 9, 9, "apa", 1, 20, "gaz") == 0);

    assert(deleteExpenseService(s, 9, 9, "apa") == 0);

   
    addExpenseService(s, 1, 100, "apa");
    addExpenseService(s, 2, 200, "gaz");
    addExpenseService(s, 3, 150, "canal");

    Vector* desc = sortBySumDescServiceCmp(s, NULL, NULL);
    assert(((Expense*)getVectorElement(desc, 0))->sum == 200);
    destroyVectorOnly(desc);

    Vector* rev = sortBySumAscServiceCmp(s, reverseSumCmp, NULL);
  
    assert(((Expense*)getVectorElement(rev, 0))->sum == 200);
    destroyVectorOnly(rev);

    Vector* typeDesc = sortByTypeDescServiceCmp(s, NULL, NULL);
   
    assert(strcmp(((Expense*)getVectorElement(typeDesc, 0))->type, "gaz") == 0);
    destroyVectorOnly(typeDesc);

 
   Vector* filtered = filterByApartmentService(s, 999);
   assert(getVectorSize(filtered) == 0);
   destroyVectorOnly(filtered);

    destroyService(s);
    destroyRepo(r);
    printf("testServiceExtra passed\n");
}

void testFilter() {
    Repo* r = createRepo();
    Service* s = createService(r);

    addExpenseService(s, 1, 100, "apa");
    addExpenseService(s, 1, 200, "gaz");
    addExpenseService(s, 2, 150, "apa");

    Vector* filtered = filterByApartmentService(s, 1);
    assert(getVectorSize(filtered) == 2);
    destroyVectorOnly(filtered);

    filtered = filterByTypeService(s, "apa");
    assert(getVectorSize(filtered) == 2);
    destroyVectorOnly(filtered);

    filtered = filterBySumGreaterService(s, 150);
    assert(getVectorSize(filtered) == 2);
    destroyVectorOnly(filtered);

    destroyService(s);
    destroyRepo(r);
    printf("testFilter passed\n");
}

void testSort() {
    Repo* r = createRepo();
    Service* s = createService(r);

    addExpenseService(s, 1, 200, "gaz");
    addExpenseService(s, 1, 100, "apa");
    addExpenseService(s, 2, 150, "canal");

    Vector* sorted = sortBySumAscService(s);
    assert(((Expense*)getVectorElement(sorted, 0))->sum == 100);
    assert(((Expense*)getVectorElement(sorted, 1))->sum == 150);
    assert(((Expense*)getVectorElement(sorted, 2))->sum == 200);
    destroyVectorOnly(sorted);

    sorted = sortByTypeAscService(s);
    Vector* sorted1 = sortBySumDescService(s);
    assert(((Expense*)getVectorElement(sorted1, 2))->sum == 100);
    assert(((Expense*)getVectorElement(sorted1, 1))->sum == 150);
    assert(((Expense*)getVectorElement(sorted1, 0))->sum == 200);

    // apa, canal, gaz
    assert(strcmp(((Expense*)getVectorElement(sorted, 0))->type, "apa") == 0);
    assert(strcmp(((Expense*)getVectorElement(sorted, 1))->type, "canal") == 0);
    assert(strcmp(((Expense*)getVectorElement(sorted, 2))->type, "gaz") == 0);
    Vector* sorted2 = sortByTypeDescService(s);
    assert(strcmp(((Expense*)getVectorElement(sorted2, 2))->type, "apa") == 0);
    assert(strcmp(((Expense*)getVectorElement(sorted2, 1))->type, "canal") == 0);
    assert(strcmp(((Expense*)getVectorElement(sorted2, 0))->type, "gaz") == 0);

    /* free all returned vectors to avoid memory leaks */
    destroyVectorOnly(sorted1);
    destroyVectorOnly(sorted2);
    destroyVectorOnly(sorted);

    destroyService(s);
    destroyRepo(r);
    printf("testSort passed\n");
}

void testCopyAndPrintExpense() {
    Expense* e1 = createExpense(5, 250.5, "gaz");
    Expense* e2 = malloc(sizeof(Expense));
    e2->type = malloc(sizeof(e1->type)+1);
    copyExpense(e2, e1);
    assert(e2->apartment == 5);
    assert(e2->sum == 250.5f);
    assert(strcmp(e2->type, "gaz") == 0);

    /* exercise printExpense to ensure it doesn't crash; visual output not asserted */
    printExpense(e2);
    destroyExpense(e1);
    destroyExpense(e2);
   // destroyExpense(e2);
    printf("testCopyAndPrintExpense passed\n");
}

void testCompareExpensesByType() {
    /* Test compareExpenses reaching the strcmp(a->type, b->type) branch */
    /* Both expenses have same apartment and sum, differ by type */
    ElemType e1 = createExpense(3, 100.0, "apa");
    ElemType e2 = createExpense(3, 100.0, "gaz");
    ElemType e3 = createExpense(3, 100.0, "canal");

    /* e1 "apa" < e2 "gaz" */
    assert(compareExpenses(e1, e2) < 0);

    /* e2 "gaz" > e1 "apa" */
    assert(compareExpenses(e2, e1) > 0);

    /* e1 "apa" < e3 "canal" */
    assert(compareExpenses(e1, e3) < 0);

    /* same type should return 0 */
    ElemType e4 = createExpense(3, 100.0, "apa");
    assert(compareExpenses(e1, e4) == 0);

    destroyExpense(e1);
    destroyExpense(e2);
    destroyExpense(e3);
    destroyExpense(e4);
    printf("testCompareExpensesByType passed\n");
}

void testListaDeListe()
{
    Vector* expenses = createVector(10);
    addToVector(expenses, createExpense(1, 1, "gaz"));
    addToVector(expenses, createExpense(2, 2, "gaz"));

    Vector* expenses2 = createVector(10);
    addToVector(expenses2, createExpense(1, 1, "gaz"));
    addToVector(expenses2, createExpense(2, 2, "gaz"));

    Vector* undoL = createVector(10);
    addToVector(undoL, expenses);
    assert(undoL->size == 1);
    addToVector(undoL, expenses2);
    assert(undoL->size == 2);

    destroyVector(undoL, destroyListaExpense);

}


void testUndo()
{
    Repo* r = createRepo();
    Service* s = createService(r);

    assert(getVectorSize(getAllExpensesRepo(r)) == 0);

    assert(addExpenseService(s, 1, 100, "apa") == 1);
    assert(getVectorSize(getAllExpensesRepo(r)) == 1);

    assert(addExpenseService(s, 2, 200, "gaz") == 1);
    assert(getVectorSize(getAllExpensesRepo(r)) == 2);

    assert(updateExpenseService(s, 2, 200, "gaz", 2, 300, "gaz") == 1);
    assert(findExpenseByIndex(r, 2, 300, "gaz") != -1);

    assert(deleteExpenseService(s, 1, 100, "apa") == 1);
    assert(findExpenseByIndex(r, 1, 100, "apa") == -1);
 
    undo(s);
    assert(findExpenseByIndex(r, 1, 100, "apa") != -1);
    assert(findExpenseByIndex(r, 2, 300, "gaz") != -1);
    
    undo(s);
    assert(findExpenseByIndex(r, 2, 200, "gaz") != -1);
    assert(findExpenseByIndex(r, 1, 100, "apa") != -1);
   
    undo(s);
    assert(getVectorSize(getAllExpensesRepo(r)) == 1);
    assert(findExpenseByIndex(r, 1, 100, "apa") != -1);
   
    undo(s);
    assert(getVectorSize(getAllExpensesRepo(r)) == 0);

    undo(s);
    assert(getVectorSize(getAllExpensesRepo(r)) == 0);

    destroyService(s);
    destroyRepo(r);
    printf("testUndo passed\n");
}

void runAllTests() {
    testCreateExpense();
    testVector();
    testVectorExtra();
    testRepo();
    testRepoExtra();
    testService();
    testServiceExtra();
    testFilter();
    testSort();
    testDefaultCompare();
    testCopyAndPrintExpense();
    testCompareExpensesByType();
    testListaDeListe();
	testUndo();
    printf("All tests passed!\n");
}