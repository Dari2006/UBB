#pragma once
#include "pet.h"
#include "vectordinamic.h"
class PetRepo {
private:
	VectorDinamic all;
public:
	PetRepo() {}

	PetRepo(const PetRepo& ot) = delete;//nu vreau sa se copieze repo
	/*
	Salveaza pet
	*/
	void store(const Pet& p) {
		all.add(p);
	}

	VectorDinamic getAll() const{
		return all;
	}
};