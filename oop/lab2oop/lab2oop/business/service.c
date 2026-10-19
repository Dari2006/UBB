#include <stdlib.h>
#include "../domain/domain.h"
#include <string.h>
#include "../infrastructura/repo.h"

int adauga_produs_service(RepoProduse* r, int id, char* tip, char* producator, char* model, int pret, int cantitate)
{
	Produs* p = creeaza_produs(id, tip, producator, model, pret, cantitate);
	if (valideaza_produs(p))
	{
		int index = cauta_produs(r, id);
		if (index != -1 && index != -2)
		{
			//Produs* p1 = creeaza_produs(id, tip, producator, model, pret, cantitate);
			set_cantitate(r->elemente[index], r->elemente[index]->cantitate + cantitate);
			return 1;
		}
		adauga_produs(r, p);
	}
	else
	{
		distruge_produs(p);
		return -1;
	}
	return 1;
}

int sterge_produs_service(RepoProduse* r, int id)
{
	int index = cauta_produs(r, id);
	if(index < 0)
		return 0;

	sterge_produs(r, id);
	return 1;
}

int actualizeaza_produs_service(RepoProduse* r, int id, char* tip, char* producator, char* model, int pret_nou, int cantitate_noua)
{
	int index = cauta_produs(r, id);
	if(index == -1 || index == -2)
		return -1; //produs invalid

	struct Produs* p_nou = creeaza_produs(id, tip, producator, model, pret_nou, cantitate_noua);
	return actualizeaza_produs(r, p_nou);
		//return 1;
	//else
		//return 0;
}

Produs** get_all_service(RepoProduse* r)
{
	return get_all(r);
}

int get_lungime_service(RepoProduse* r)
{
	return get_lungime(r);
}

int compara(Produs* p1, Produs* p2, int param1, int param2, int param3, int param4) //returneaza 1 daca trb schimbate, 0 altfel
{                                            //p1 si p2 sunt elemente de pe pozitii consecutive
	int pret_p1 = get_pret(p1);
	int pret_p2 = get_pret(p2);
	int cant_p1 = get_cantitate(p1);
	int cant_p2 = get_cantitate(p2);

	if (param1 == 1)   //comparam pretu;
	{
		if (param2 == 1)   //crescator, p1 pret trb sa fie mai mic decat p2 pret
		{
			if(pret_p1 < pret_p2)
				return 0;   //nu trebuie schimbate
			else if(pret_p1 > pret_p2)
				return 1;   //trb schimbate
		}
		if (param2 == 2)   //descrescator, p1 pret trb sa fie mai mare decat p2 pret
		{
			if (pret_p1 > pret_p2)
				return 0;   //nu trebuie schimbate
			else if (pret_p1 < pret_p2)
				return 1;   //trb schimbate
		}
		//daca ajunem aici, preturile sunt egale, comparam cantitatea
		if (param4 == 1) //crescator, p1 cant trb sa fie mai mic decat p2 cant
		{
			if(cant_p1 <= cant_p2)
				return 0;  //nu trb schimbate
			return 1;
		}
		if (param4 == 2) //descrescator, p1 cant trb sa fie mai mare decat p2 cant
		{
			return cant_p1 < cant_p2;
				//return 0;    //nu trb schimbate
			//return 1;
		}
	}

	if (param1 == 2)   //comparam cantitatea
	{
		if (param2 == 1)    //crescator, deci p1 can trb sa fie mai mic decat p2 cant
		{
			if(cant_p1 < cant_p2)
				return 0; //nu trb schimbate
			if(cant_p1 > cant_p2)
				return 1; //trb schimbate
		}
		if (param2 == 2) //descrescator, deci p1 cant trb sa fie mai mare decat p2 cant
		{
			if(cant_p1 > cant_p2)
				return 0;   //nu trb schimbate
			if(cant_p1 < cant_p2)
				return 1; //trb schimbate
		}
		//daca ajungem aici, cantitatile sunt egale, deci comparam pretul
		if (param4 == 1)//crescator, deci p1 pret trb sa fie mai mic decat p2 pret
		{
			return pret_p1 > pret_p2;
				//return 0; //nu trb schimbate
			
			//return 1;  //trb schimbate
		}
		//if (param4 == 2) //descrescator, deci p1 pret trb sa fie mai mare decat p2 pret
		//{
			//if(pret_p1 >= pret_p2)
			//	return 0;  //nu trb schimbate
			
		//	return 1; //trb schimbate
		//}
	}
	return pret_p1 < pret_p2;
	//return 0; //cumva param1 nu nici 1 nici 2
}


Produs** ordoneaza_produse_service(RepoProduse* r, int param1, int param2, int param3, int param4)
{
	int i = -1, j = -1;
	Produs ** lista = get_all_service(r);
	int lungime = get_lungime_service(r);
	int schimba = 0;
	Produs *aux = NULL;

	for (i = 0; i < lungime-1; i++)
	{
		for (j = i + 1; j < lungime; j++)
		{
			schimba = compara(lista[i], lista[j], param1, param2, param3, param4);
			if (schimba == 1)
			{
				aux = lista[i];
				lista[i] = lista[j];
				lista[j] = aux;
			}
		}
	}
	return lista;
}


Produs** filtreaza_service(RepoProduse* r, int criteriu, int val_max, char* prod, int* lungime_rezultat)
{
	Produs** copie = get_all_service(r);  //lista in care cautam
	int k = 0; //lungimea listei filtrate
	int lungime = get_lungime_service(r);
	Produs** lista = (Produs**)malloc(lungime * sizeof(Produs*)); //lista filtrata
	int i = 0;
	for (i = 0; i < lungime; i++)
	{
		if (criteriu == 1)    //filtram dupa producator
		{
			if (strstr(get_producator(copie[i]), prod))
			{
				lista[k++] = copie[i];
			}
		}
		else if (criteriu == 2)   //filtram dupa pret
		{
			if(get_pret(copie[i]) <= val_max)
			lista[k++] = copie[i];
		}
		else if (criteriu == 3)   //filtram dupa cantitate
		{
			if (get_cantitate(copie[i]) <= val_max)
			{
				lista[k++] = copie[i];
			}
		}
	}
	free(copie);
	*lungime_rezultat = k;

	return lista;
}