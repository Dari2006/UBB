#include "repo.h"
#include <stdlib.h>

RepoProduse* creeaza_repo()
{
	RepoProduse* r = (RepoProduse*)malloc(sizeof(RepoProduse));
	if (r != NULL)
	{
		r->lungime = 0;
		for(int i = 0; i< max_produse; i++)
			r->elemente[i] = NULL;
	}
	return r;
}

int adauga_produs(RepoProduse* r, Produs* p)
{
	if (r->lungime <= max_produse)
	{
		r->elemente[r->lungime] = p;
		r->lungime++;
		return 1;
	}
		
}

void distruge_repo(RepoProduse* r)
{
	if(r->lungime < 1)
		return;
	for(int i=0; i<r->lungime; i++)
		if(r->elemente[i] != NULL)
			distruge_produs(r->elemente[i]);

	free(r);
}

int cauta_produs(RepoProduse* r, int id)
{
	if(r == NULL)
		return -2;  //nu exista elemente
	for (int i = 0; i < r->lungime; i++)
	{
		if(get_id(r->elemente[i]) == id)
			return i;
	}
	return -1;
}

int sterge_produs(RepoProduse* r, int id)
{
	
	int index = cauta_produs(r, id);
	//if(index == -1)
		//return -1;  //nu exista produsul

	//index = cauta_produs(r, id);	
	if(index < 0 || index > r->lungime)
		return -1;
	distruge_produs(r->elemente[index]);

	int lim = r->lungime-1;

	for (int i = index; i < lim; i++)
		r->elemente[i] = r->elemente[i+1];

	r->lungime--;
	return 1; //succes
}

int actualizeaza_produs(RepoProduse* r, Produs* p_nou)
{
	if (r == NULL || r->elemente == NULL) {
			//printf_s("EROARE FATALA: Repo sau vectorul este NULL!\n");
			return -1;
		}

	int index = cauta_produs(r, get_id(p_nou));
	if (index < 0 || get_id(p_nou) != get_id(r->elemente[index]))
		return -1;

	if(strcmp(get_model(p_nou), get_model(r->elemente[index])) != 0 || strcmp(get_producator(p_nou), get_producator(r->elemente[index])) != 0 || strcmp(get_tip(p_nou), get_tip(r->elemente[index])) != 0)
		return -1;
	
	if(r->elemente[index] != NULL)
		distruge_produs(r->elemente[index]);

	
	r->elemente[index] = p_nou;
	//printf_s("Scriere reusita!\n");


	return 1; //succes

}

Produs** get_all(RepoProduse* r)
{
	Produs** copie = (Produs**)malloc(sizeof(Produs*)*r->lungime);
	if(copie != NULL)
		for (int i = 0; i < r->lungime; i++)
		{
			copie[i] = r->elemente[i];
		}
	return copie;
}
//trebuie eliberata memoria in ui

int get_lungime(RepoProduse* r)
{
	//int lungime = r->lungime;
	return r->lungime;
}