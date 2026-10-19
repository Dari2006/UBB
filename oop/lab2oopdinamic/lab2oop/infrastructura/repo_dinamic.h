#ifndef repo_dinamic_h
#define repo_dinamic_h
#include "../domain/domain.h"


typedef struct {
	Produs** elemente; 
	int lungime;
	int capacitate;
}RepoProduse;

RepoProduse* creeaza_repo_dinamic();  //initializam repo

void distruge_repo(RepoProduse* r); //eliberam memoria

//adauga produs, return 1 daca a resusir, 0 altfel
int adauga_produs(RepoProduse* r, Produs* p);

//cauta produs dupa id, return index daca gasit, -1 sau -2 altfel
int cauta_produs(RepoProduse* r, int id);

//sterge produs dupa id, return 1 daca a fost seters, -1 altfel
int sterge_produs(RepoProduse* r, int id);

//actualizeaza produs, return 1 daca succes, 0 altfel
int actualizeaza_produs(RepoProduse* r, Produs* p_nou);

//returneaza o lista copie a lui r->elemente
Produs** get_all(RepoProduse* r);

int get_lungime(RepoProduse* r);

void redimensionare(RepoProduse* r);

#endif