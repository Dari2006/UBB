#pragma once
#include "Service.h"

class UI {
private:
	Service& s;
public:
	UI(Service& s) noexcept : s{ s } {

	}
	/*metoda afiseaza un meniu si asteapta o comanda valida de la utilizator*/
	void run();
	/*metoda adauga o noua activitate folosind parametrii introdusi de utilizator*/
	void adaugaUI();
	/*metoda sterge o activitate folosind parametrii introdusi de utilizator*/
	void stergeUI();
	/*metoda actualizeaza o activitata folosind parametrii introdusi de utilizator*/
	void actualizeazaUI();
	/*afiseaza toate activitatile*/
	void printAll();
	/*cauta dupa titlu*/
	void cautaUI();
	/*filtreaza dupa tip sau descriere*/
	void filtrareUI();
	/*sortare*/
	void sortareUI();
	void uiAdaugaInPlan();
	void uiGenereazaPlan();
	void uiGolestePlan();
	void uiExport();
	void uiAfiseazaPlan();
	void uiUndo();
	void uiRaport();
};