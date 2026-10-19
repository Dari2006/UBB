#ifndef domain_h
#define domain_h


/*
* Modulul gestioneaza tipul de data Produs
* Fiecare produs are: id, tip, producator, model, pret, cantitate
*/

typedef struct {
	int id, pret, cantitate;
	char *tip, *producator, *model;
}Produs;

//creeaza un nou produs
Produs* creeaza_produs(int id, char* tip, char* producator, char* model, int pret, int cantitate);

//distruge un produs, eliberand memoria din heap
void distruge_produs(Produs* p);


//returneaza 1 daca produsul e valid, 0 altfel
int valideaza_produs(Produs* p);

//getteri
int get_id(Produs* p);
int get_pret(Produs* p);
int get_cantitate(Produs* p);
char* get_tip(Produs* p);
char* get_producator(Produs* p);
char* get_model(Produs* p);


//setteri
void set_pret(Produs* p, int pret_nou);
void set_cantitate(Produs* p, int cantitate_noua);

#endif
