#include "stdafx.h"
#include "storeui.h"
#include <iostream>
#include "pet.h"
#include "vectordinamic.h"
/*
tipareste meniu si citeste comanda
*/
int PetUI::readCommand() {
	std::cout << " 1 adauga \n 2 Toate\n 3 Filtreaza pret\n 4 Sortat dupa tip\n 5 Sortat dupa pret\n";
	std::cout << " 0 Iesire\n Dati comanda:";
	int cmd;
	std::cin >> cmd;
	return cmd;
}
/*
Tipareste lista de pet
*/
void PetUI::printPets(const VectorDinamic& v) {
	std::cout << "\n Pets("<<v.size()<<"):\n";
	for (int i = 0; i < v.size(); i++) {
		Pet p = v.get(i);
		std::cout << "Type:" << p.getType() << " Species:" << p.getSpecies();
		std::cout << "Price:" << p.getPrice() << std::endl;
	}
	std::cout << std::endl;
}
/*
citest de la tastatura si adauga pet
*/
void PetUI::addPet() {
	char type[20];
	char species[20];
	int price;
	std::cout << "\nType:";
	std::cin >> type;
	std::cout << "\nSpecies:";
	std::cin >> species;
	std::cout << "\nPrice:";	
	std::cin >> price;
	ctr.add(type, species, price);
}

void PetUI::startUI()
{
	while (true) {
		int cmd = readCommand();
		if (cmd == 0) {
			break;
		}
		if (cmd == 1) {
			addPet();
		}
		if (cmd == 2) {
			VectorDinamic v = ctr.getAllPets();
			printPets(v);
		}
		if (cmd == 3) {
			std::cout << "Pret:";
			int price;
			std::cin >> price;
			printPets(ctr.getFilterByPrice(price));
		}
		if (cmd == 4) {
			printPets(ctr.getSortByType());
		}
		if (cmd == 5) {
			printPets(ctr.getSortByPrice());
		}

	}
}
