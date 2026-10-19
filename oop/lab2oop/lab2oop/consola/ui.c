#include "ui.h"
#include <stdlib.h>
#include <string.h>
#include "../business/service.h"
#include <stdio.h>

void ui_run(RepoProduse* r)
{
	int comanda = -1;
	while (1)
	{
		//printf("Introduceti comanda: ");
		printf("comenzi:\n1 - adauga produs\n2 - actualizeaza produs\n3 - sterge produs\n4 - afiseaza tot\n5 - sorteaza\n6 - filtrare\n0 - exit\n");
		comanda = citeste_int("Introduceti comanda: ");
		if (comanda == 0)
		{
			printf("\nciau");
			break;
		}
		else if (comanda == 1)
		{
			adauga_produs_ui(r);
		}
		else if (comanda == 2)
		{
			actualizeaza_produs_ui(r);
		}
		else if (comanda == 3)
		{
			sterge_produs_ui(r);
		}
		else if (comanda == 4)
		{
			print_all_ui(r);
		}
		else if (comanda == 5)
		{
			sortare_ui(r);
		}
		else if (comanda == 6)
		{
			filtrare_ui(r);
		}
		else
			printf("Comanda invalida\n");
	}
}



int citeste_int(char* mesaj)
{
	int nr=-1;
	printf_s("%s", mesaj);
	while (scanf_s("%d", &nr) != 1)
	{
		printf_s("Invalid, introduceti un numar intreg: ");
		while(getchar()!='\n');
	}
	while (getchar() != '\n');
	return nr;
}

void citeste_text(char* mesaj, char* buffer, int marime)
{
	printf_s("%s", mesaj);
	if (fgets(buffer, marime, stdin) != NULL)
	{
		if(strlen(buffer) > 0 && buffer[strlen(buffer)-1] == '\n')
			buffer[strlen(buffer)-1] = '\0';
	}
	else
		while(getchar() != '\n');
}

void adauga_produs_ui(RepoProduse* r)
{
	int id = citeste_int("Introduceti id: ");
	char tip[50];
	citeste_text("Introduceti tip: ", tip, 50);
	char producator[50];
	citeste_text("Introduceti producator: ", producator, 50);
	char model[50];
	citeste_text("Introduceti model: ", model, 50);
	int pret = citeste_int("Introduceti pret: ");
	int cantitate = citeste_int("Introduceti cantitate: ");
	if(adauga_produs_service(r, id, tip, producator, model, pret, cantitate) == 1)
		printf("Produs adaugat cu succes\n");
	else
		printf("Produsul nu a putut fi adaugat\n");
}

void actualizeaza_produs_ui(RepoProduse* r)
{
	int id = citeste_int("Introduceti id: ");
	char tip[50];
	citeste_text("Introduceti tip: ", tip, 50);
	char producator[50];
	citeste_text("Introduceti producator: ", producator, 50);
	char model[50];
	citeste_text("Introduceti model: ", model, 50);
	int pret = citeste_int("Introduceti pret: ");
	int cantitate = citeste_int("Introduceti cantitate: ");
	if(actualizeaza_produs_service(r, id, tip, producator, model, pret, cantitate) == 1)
		printf_s("Produs actualizat cu succes\n");
	else
		printf_s("Produsul nu fost modificat\n");
}

void sterge_produs_ui(RepoProduse* r)
{
	int id = citeste_int("Introduceti id: ");
	if(sterge_produs_service(r, id) == 1)
		printf_s("Produsul a fost sters\n");
	else
		printf_s("Produsul nu a fost sters\n");
}


void print_all_ui(RepoProduse* r)
{
	int lungime = get_lungime_service(r);
	Produs** copie = get_all_service(r);
	for (int i = 0; i < lungime; i++)
	{
		printf("%d.", i+1);
		printf("ID: %d ", get_id(copie[i]));
		printf("TIP: %s ", get_tip(copie[i]));
		printf("PRODUCATOR: %s ", get_producator(copie[i]));
		printf("MODEL: %s ", get_model(copie[i]));
		printf("PRET: %d ", get_pret(copie[i]));
		printf("CANTITATE: %d ", get_cantitate(copie[i]));
		printf("\n");
	}
	free(copie);
}

void sortare_ui(RepoProduse* r)
{
	int param1 = 0, param2 = 0, param3 = 0, param4 = 0;

	printf("Alegeti criteriul principal: (1 - pret; 2 - cantitate): ");
	while (param1 != 1 && param1 != 2)
	{
		
		if (scanf_s("%d", &param1) != 1)
		{
			printf("Numar invalid\n");
			while(getchar() != '\n');
		}
		
		else if(param1!=1 && param1!=2)
			printf("\nParametru invalid\n");
	}
	while(getchar() != '\n');

	printf("Alegeti ordinea criteriului principal(1 - crescator; 2 - descrescator): ");
	while (param2 != 1 && param2 != 2)
	{
		
		if (scanf_s("%d", &param2) != 1)
		{
			printf("Numar invalid\n");
			while(getchar() != '\n');
		}
		else if(param2 != 1 && param2 != 2)
			printf("\nParametru invalid\n");
	}
	while (getchar() != '\n');

	if (param1 == 1)
	{
		printf("Al doilea criteriu este cantitate\n");
		param3 = 2;
	}
	if (param1 == 2)
	{
	    param3 = 1;
		printf("Al doilea criteriu este pret\n");
	}

	printf("Alegeti ordinea criteriului secundar(1 - crescator; 2 - descrescator): ");
	while (param4 != 1 && param4 != 2)
	{
		if (scanf_s("%d", &param4) != 1)
		{
			printf("Numar invalid\n");
			while(getchar() != '\n');
		}
		else if (param4 != 1 && param4 != 2)
		{
			printf("parametru invalid");
		}
	}
	while (getchar() != '\n');

	Produs** lista = ordoneaza_produse_service(r, param1, param2, param3, param4);

	int lungime = get_lungime_service(r);
	for (int i = 0; i < lungime; i++)
	{
		printf("%d.", i + 1);
		printf("ID: %d ", get_id(lista[i]));
		printf("TIP: %s ", get_tip(lista[i]));
		printf("PRODUCATOR: %s ", get_producator(lista[i]));
		printf("MODEL: %s ", get_model(lista[i]));
		printf("PRET: %d ", get_pret(lista[i]));
		printf("CANTITATE: %d ", get_cantitate(lista[i]));
		printf("\n");
	}
	free(lista);
}



void filtrare_ui(RepoProduse* r)
{
	int criteriu = 0;
	char producator[50] = "";
	int val_max = -1;
	printf("Introduceti criteriul filtrarii(1 - producator; 2 - pret; 3 - cantitate): ");
	while(scanf_s("%d", &criteriu) != 1 || (criteriu!=1 && criteriu!=2 && criteriu!=3))
	{
		printf("\nCriteriu invalid\n");
		while(getchar() != '\n');
	}
	while(getchar() != '\n');

	if (criteriu == 1)//producator
	{
		printf("Introduceti producatorul: ");
		gets_s(producator, 49);
		//while(getchar() != '\n');
	}
	if (criteriu == 2) //pret
	{
		printf("Introduceti pretul: ");
		while (scanf_s("%d", &val_max) != 1 || val_max < 1)
		{
			printf("Pret invalid");
			while(getchar() != '\n');
		}
		while(getchar() != '\n');
	}
	if (criteriu == 3)  //cantitate
	{
		printf("Introduceti cantitatea: ");
		while (scanf_s("%d", &val_max) != 1 || val_max < 1)
		{
			printf("Cantitate invalida\n");
			while(getchar() != '\n');
		}
		while(getchar() != '\n');
	}
	int l = 0;
	Produs** lista = filtreaza_service(r, criteriu, val_max, producator, &l);

	if(l == 0)
		printf("Nu s-au gasit rezultate");
	else
	{
		for (int i = 0; i < l; i++)
			{
				printf("%d.", i + 1);
				printf("ID: %d ", get_id(lista[i]));
				printf("TIP: %s ", get_tip(lista[i]));
				printf("PRODUCATOR: %s ", get_producator(lista[i]));
				printf("MODEL: %s ", get_model(lista[i]));
				printf("PRET: %d ", get_pret(lista[i]));
				printf("CANTITATE: %d ", get_cantitate(lista[i]));
				printf("\n");
			}
	}
	if(lista)
	free(lista);

}