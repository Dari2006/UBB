#pragma once
#include "pet.h"
#include "petrepo.h"

class PetController {
private:
	PetRepo& repo;	
public:
	PetController(PetRepo& rep) :repo{ rep } {

	}
	PetController(const PetController& ot) = delete;//nu vreau sa se copieze 
	/*
	Adauga pet
	*/
	void add(const char* type, const char* species, int price);
	/*
	  Toate
	*/
	VectorDinamic getAllPets();

	/*
	Sortat dupa pret
	*/
	VectorDinamic getSortByPrice();
	/*
	Sortat dupa tip
	*/
	VectorDinamic getSortByType();

	VectorDinamic getFilterByPrice(int price);
};


void testCtr();