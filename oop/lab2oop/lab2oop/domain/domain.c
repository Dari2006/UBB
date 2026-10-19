#include "domain.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
Modulul reprezinta implementarea Produs
*/

//Constructor; aloca memorie pentru un produs nou
Produs* creeaza_produs(int id, char* tip, char* producator, char* model, int pret, int cantitate)
{
	Produs* p = (Produs*)malloc(sizeof(Produs));
	//if(p == NULL)
		//return NULL;  //verificam daca s-a alocat spatiu pentru produs

	p->id = id;
	p->tip = (char*)malloc((strlen(tip)+1) * sizeof(char));
	if(p->tip != NULL)
		strcpy_s(p->tip, strlen(tip)+1, tip);
	p->producator = (char*)malloc((strlen(producator)+1) * sizeof(char));
	if(p->producator != NULL)
		strcpy_s(p->producator, strlen(producator)+1, producator);
	p->model = (char*)malloc((strlen(model)+1) * sizeof(char));
	if(p->model != NULL)
		strcpy_s(p->model, strlen(model)+1, model);
	p->pret = pret;
	p->cantitate = cantitate;
	return p;
}

//Destructor; elibereaza memoria ocupata de un produs
void distruge_produs(Produs* p)
{
	//if(p == NULL)
		//return  //produsul nu exista
	
	free(p->tip);
	free(p->producator);
	free(p->model);

	free(p);
}

//implementare getteri
int get_id(Produs* p)
{
	//if(p == NULL)
		//return -1; //produsul nu exista
	return p->id;
}
char* get_tip(Produs* p)
{
	//if (p == NULL)
		//return NULL; //produsul nu exista
	return p->tip;
}
char* get_producator(Produs* p)
{
	//if (p == NULL)
		//return NULL; //produsul nu exista
	return p->producator;
}
char* get_model(Produs* p)
{
	//if (p == NULL)
		//return NULL; //produsul nu exista
	return p->model;
}
int get_pret(Produs* p)
{
	//if (p == NULL)
		//return -1; //produsul nu exista
	return p->pret;
}
int get_cantitate(Produs* p)
{
	//if (p == NULL)
		//return -1; //produsul nu exista
	return p->cantitate;
}


//implementare validator
int valideaza_produs(Produs* p)
{
	//if(p == NULL)
		//return 0;
	if(get_pret(p) < 0 || get_cantitate(p)<0)
		return 0;

	if(strlen(get_tip(p)) == 0 || strlen(get_model(p)) == 0 || strlen(get_producator(p)) == 0)
		return 0;

	return 1;
}

//seteri
void set_pret(Produs* p, int pret_nou)
{
	//if(p == NULL)
		//return;
	if(p != NULL && pret_nou > 0)
		p->pret = pret_nou;
}

void set_cantitate(Produs* p, int cantitate_noua)
{
	//if(p == NULL)
		//return;
	if(p != NULL && cantitate_noua > 0)
		p->cantitate = cantitate_noua;
}