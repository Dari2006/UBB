#ifndef service_h
#define service_h
#include "../infrastructura/repo_dinamic.h"

int adauga_produs_service(RepoProduse* r, int id, char* tip, char* producator, char* model, int pret, int cantitate);

int sterge_produs_service(RepoProduse* r, int id);

int actualizeaza_produs_service(RepoProduse* r, int id, char* tip, char* producator, char* model, int pret, int cantitate);

/*
Vizualizare produse ordonate dupa pret,cantitate(cresc, descr)
parametri va contine pret cresc/descr si cantitate cresc/descr(1 = pret, 2 = cantitate, 3 = cresc, 4 = desccr)
*/
Produs** ordoneaza_produse_service(RepoProduse* r, int param1, int param2, int param3, int param4);

int compara(Produs* p1, Produs* p2,int param1, int param2, int param3, int param4);

int compara_implicit(Produs* p1, Produs* p2);
Produs** sortare_implicita(RepoProduse* r, int (*algortim)(Produs*, Produs*));

Produs** filtreaza_service(RepoProduse* r, int criteriu, int val_max, char* prod, int* lungime_rezultat);

//get all
Produs** get_all_service(RepoProduse* r);

//return lungime
int get_lungime_service(RepoProduse* r);

#endif