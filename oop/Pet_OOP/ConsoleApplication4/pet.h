#pragma once

#include <string.h>
#include <iostream>
class Pet {
private:
	char* type;
	char* species;
	int price;
public:
	/*
	Constructor default
	*/
	Pet() {
		type = nullptr;
		species = nullptr;
		price = -1;
	}
	/*
	  Constructor 3 param
	*/
	Pet(const char* t, const char* s, int p) {
		type = new char[strlen(t) + 1];
		strcpy(type, t);
		species = new char[strlen(s) + 1];
		strcpy(species, s);
		price = p;
	}
	/*
	Constuructor copiere
	Copieaza continutul lui p in obiectul current
	*/
	Pet(const Pet& p) {
		//std::cout << "!!!!! constr copiere pet\n";
		type = new char[strlen(p.type) + 1];
		strcpy(type, p.type);
		species = new char[strlen(p.species) + 1];
		strcpy(species, p.species);
		price = p.price;
	}
	/*
	Destructor: elibereaza memoria alocata in consturctor cu new[]
	*/
	~Pet() {
		delete[] type;
		delete[] species;
	}

	/*
	Operator de assignare
	apelat cand se scrie p1 = p2;
	Continutul lui p2 (ot) copiat in p1
	Obs: p1 are deja ceva inainte de atribuire - trebuie dealocat memoria
	*/
	void operator=(const Pet& ot) {
		delete[] type;
		delete[] species;
		type = new char[strlen(ot.type) + 1];
		strcpy(type, ot.type);
		species = new char[strlen(ot.species) + 1];
		strcpy(species, ot.species);
		price = ot.price;
	}

	int getPrice() const {
		return price;
	}

	void setPrice(int price) {
		this->price = price;
	}

	const char* getType() const {
		return type;
	}
	const char* getSpecies() const {
		return species;
	}
};

int cmpByPrice(const Pet& p1, const Pet& p2);

int cmpByType(const Pet& p1, const Pet& p2);

void testPet();
