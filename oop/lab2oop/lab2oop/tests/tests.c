#include "tests.h"
#include "../domain/domain.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../infrastructura/repo.h"
#include "../business/service.h"

void test_creeaza_produs()
{
	//date de test
	int id = 1;
	char* tip = "laptop";
	char* producator = "asus";
	char* model = "TUF";
	int pret = 7000;
	int cantitate = 100;
	Produs* p = creeaza_produs(id, tip, producator, model, pret, cantitate);

	assert(get_id(p) == 1);
	assert(strcmp(get_tip(p), "laptop") == 0);
	assert(strcmp(get_producator(p), "asus") == 0);
	assert(strcmp(get_model(p), "TUF") == 0);
	assert(get_pret(p) == 7000);
	assert(get_cantitate(p) == 100);

	assert(valideaza_produs(p) == 1);
	set_pret(p, 20);
	assert(get_pret(p) == 20);
	set_cantitate(p, 20);
	assert(get_cantitate(p) == 20);

	distruge_produs(p);

	Produs* t = creeaza_produs(id, tip, producator, model, -2, cantitate);

	assert(valideaza_produs(t) == 0);
	distruge_produs(t);

	Produs* u = creeaza_produs(id, tip, "", model, pret, cantitate);

	assert(valideaza_produs(u) == 0);
	distruge_produs(u);

	printf_s("test domain ok\n");
}

void test_repo()
{
	RepoProduse* repo = creeaza_repo();
	Produs* p1 = creeaza_produs(1, "laptop", "ASUS", "TUF", 3000, 5);
	//test adaugare
	adauga_produs(repo, p1);
	assert(repo->lungime == 1);
	assert(cauta_produs(repo, 1) == 0); // Trebuie să fie la indexul 0
	

	//teste cautare
	assert(cauta_produs(repo, 99) == -1);
	assert(cauta_produs(repo, 1) == 0);

	// test actualizare
	Produs* p1_nou = creeaza_produs(1, "laptop", "ASUS", "TUF", 5000, 2);
	assert(actualizeaza_produs(repo, p1_nou) == 1);
	assert(strcmp(get_model(p1_nou), "TUF") == 0);
	assert(get_pret(p1_nou) == 5000);
	Produs* p3_nou = creeaza_produs(999, "laptop", "lenovo", "idk", 300, 42);
	assert(actualizeaza_produs(repo, p3_nou) == -1);
	
	Produs* p2_nou  = creeaza_produs(1, "laptop", "caca", "TUF", 500, 2);
	assert(actualizeaza_produs(repo, p2_nou) == -1);

	RepoProduse* repo2 = NULL;
	assert(actualizeaza_produs(NULL, p2_nou) == -1);

	//test stergere
	Produs* p4 = creeaza_produs(3, "laptop", "ASUS", "TUF", 5000, 2);
	adauga_produs(repo, p4);
	sterge_produs(repo, 1);
	assert(sterge_produs(repo, 1) == -1);
	sterge_produs(repo, 3);
	assert(repo->lungime == 0);
	distruge_repo(repo);

	RepoProduse* repo1 = creeaza_repo();
	Produs* p2 = creeaza_produs(1, "laptop", "ASUS", "TUF", 3000, 5);
	adauga_produs(repo1, p2);
	distruge_repo(repo1);

	RepoProduse* r3 = NULL;
	Produs* p5 = creeaza_produs(1, "laptop", "ASUS", "TUF", 3000, 5);
	assert(cauta_produs(r3, 1) == -2);
	assert(actualizeaza_produs(r3, p5) == -1);
	distruge_produs(p5);
	//distruge_repo(r3);
	

	//test get_all
	RepoProduse* repo5 = creeaza_repo();
	Produs* p7 = creeaza_produs(1, "laptop", "asus", "tuf", 100, 10);
	Produs* p6 = creeaza_produs(2, "telefon", "apple", "iphone", 500, 5);

	adauga_produs(repo5, p7);
	adauga_produs(repo5, p6);

	Produs** lista = get_all(repo5);
	int lungime = get_lungime(repo5);

	assert(lungime == 2);

	assert(get_id(lista[0]) == 1);
	assert(get_id(lista[1]) == 2);
	assert(lista[0] == p7);
	assert(lista[1] == p6);


	free(lista);

	distruge_repo(repo5);


	printf_s("test repo ok\n");
}

void test_service()
{
	RepoProduse* repo = creeaza_repo();
	//Produs* p = creeaza_produs(1, "laptop", "ASUS", "TUF", 3000, 5);

	//test adaugare
	adauga_produs_service(repo, 1, "laptop", "ASUS", "TUF", 3000, 5);
	assert(repo->lungime == 1);
	assert(get_id(repo->elemente[0]) == 1);
	adauga_produs_service(repo, 1, "laptop", "ASUS", "TUF", 3000, 5);
	assert(get_cantitate(repo->elemente[0]) == 10);
	assert(adauga_produs_service(repo, 1, "laptop", "ASUS", "TUF", -5, -20) == -1);
	//test sterge
	sterge_produs_service(repo, 1);
	assert(repo->lungime == 0);
	assert(sterge_produs_service(repo, 99) == 0);

	//test actualizeaza
	adauga_produs_service(repo, 1, "laptop", "ASUS", "TUF", 3000, 5);
	assert(actualizeaza_produs_service(repo, 999, "laptop", "ASUS", "TUF", 3000, 5) == -1);
	assert(actualizeaza_produs_service(repo, 1, "laptop", "ASUS", "TUF", 3000, 10) == 1);

	distruge_repo(repo);
	


	//test get_all
	RepoProduse* repo2 = creeaza_repo();
	adauga_produs_service(repo2, 10, "tableta", "samsung", "tab", 300, 2);
	Produs** lista = get_all_service(repo2);
	int lungime = get_lungime(repo2);
	assert(lungime == 1);
	assert(get_id(lista[0]) == 10);
	assert(strcmp(get_tip(lista[0]), "tableta") == 0);

	free(lista);


	printf_s("test service ok\n");

}


void test_sortare_service() {
	
	RepoProduse* repo = creeaza_repo();

	adauga_produs_service(repo, 1, "laptop", "asus", "tuf", 100, 10);
	adauga_produs_service(repo, 2, "mouse", "logi", "mx", 100, 5);
	adauga_produs_service(repo, 3, "monitor", "dell", "u24", 50, 1);

	//int lungime_rezultat = 0;


	Produs** lista = ordoneaza_produse_service(repo, 1, 1, 2, 1);

	//assert(lungime_rezultat == 3);
	assert(get_id(lista[0]) == 3); 
	assert(get_id(lista[1]) == 2); 
	assert(get_id(lista[2]) == 1); 

	
	free(lista);

	// 3. Testam: Pret Descrescator (param2=2), Cantitate Descrescatoare (param4=2)
	// Ordinea asteptata: Laptop (100, 10) -> Mouse (100, 5) -> Monitor (50, 1)

	lista = ordoneaza_produse_service(repo, 1, 2, 2, 2);

	assert(get_id(lista[0]) == 1); 
	assert(get_id(lista[1]) == 2);
	assert(get_id(lista[2]) == 3);

	free(lista);
	distruge_repo(repo);

	printf("Test sortare ierarhica: lejer\n");
}




void test_filtrare_service() {
	RepoProduse* repo = creeaza_repo();

	adauga_produs_service(repo, 1, "laptop", "Asus", "TUF", 100, 10);
	adauga_produs_service(repo, 2, "mouse", "Logitech", "G502", 50, 5);
	adauga_produs_service(repo, 3, "tastatura", "Asus", "ROG", 150, 2);

	int lg = 0;
	Produs** filtrate = NULL;

	
	filtrate = filtreaza_service(repo, 1, 0, "Asus", &lg);
	assert(lg == 2);
	assert(get_id(filtrate[0]) == 1);
	assert(get_id(filtrate[1]) == 3);
	free(filtrate);

	
	filtrate = filtreaza_service(repo, 1, 0, "Samsung", &lg);
	assert(lg == 0);
	free(filtrate);

	
	filtrate = filtreaza_service(repo, 2, 100, "", &lg);
	assert(lg == 2);
	assert(get_id(filtrate[0]) == 1);
	assert(get_id(filtrate[1]) == 2);
	free(filtrate);

	filtrate = filtreaza_service(repo, 3, 5, "", &lg);
	assert(lg == 2);
	assert(get_id(filtrate[0]) == 2);
	assert(get_id(filtrate[1]) == 3);
	free(filtrate);

	filtrate = filtreaza_service(repo, 4, 0, "", &lg);
	assert(lg == 0);
	free(filtrate);

	distruge_repo(repo);
	printf("Test filtrare service:ok\n");
}



void test_compara() {
	
	Produs* p1 = creeaza_produs(1, "tip", "prod", "mod", 100, 10);
	Produs* p2 = creeaza_produs(2, "tip", "prod", "mod", 200, 5);
	Produs* p_egal = creeaza_produs(3, "tip", "prod", "mod", 100, 10);

	
	assert(compara(p1, p2, 1, 1, 0, 1) == 0);
	
	assert(compara(p2, p1, 1, 1, 0, 1) == 1);


	assert(compara(p1, p2, 1, 2, 0, 1) == 1);
	
	assert(compara(p2, p1, 1, 2, 0, 1) == 0);

	
	assert(compara(p1, p_egal, 1, 1, 0, 1) == 0);
	
	assert(compara(p1, p_egal, 1, 1, 0, 2) == 0);

	

	
	assert(compara(p1, p2, 2, 1, 0, 1) == 1);
	
	assert(compara(p2, p1, 2, 1, 0, 1) == 0);

	
	assert(compara(p1, p2, 2, 2, 0, 1) == 0);
	
	assert(compara(p2, p1, 2, 2, 0, 1) == 1);

	
	assert(compara(p1, p_egal, 2, 1, 0, 1) == 0);

	assert(compara(p1, p_egal, 2, 1, 0, 2) == 0);




	printf("test compara ok\n");
}




void ruleaza_toate_testele()
{
	test_creeaza_produs();
	test_repo();
	test_service();
	test_sortare_service();
	test_filtrare_service();
	test_compara();
	printf("Testele e trecutele boss");
}
