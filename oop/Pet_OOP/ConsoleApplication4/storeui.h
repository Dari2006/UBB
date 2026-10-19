#pragma once

#include "petcontroller.h"
class PetUI {
private:
	PetController& ctr;
	/*
	tipareste meniu si citeste comanda
	*/
	int readCommand();
	/*
	Tipareste lista de pet
	*/
	void printPets(const VectorDinamic& v);
	/*
	citest de la tastatura si adauga pet
	*/
	void addPet();
public:
	PetUI(PetController& ctr) :ctr{ ctr } {}
	void startUI();
};