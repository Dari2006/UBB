#ifndef ui_h
#define ui_h
#include "../infrastructura/repo_dinamic.h"

void ui_run(RepoProduse* r);

int citeste_int(char* mesaj);
void citeste_text(char* mesaj, char* buffer, int marime);
void adauga_produs_ui(RepoProduse* r);
void actualizeaza_produs_ui(RepoProduse* r);
void print_all_ui(RepoProduse* r);
void sorteaza_implicit_ui(RepoProduse* r);

//sterge produs
void sterge_produs_ui(RepoProduse* r);

void sortare_ui(RepoProduse* r);

void filtrare_ui(RepoProduse* r);

#endif