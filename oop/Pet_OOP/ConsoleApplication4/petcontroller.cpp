#include "stdafx.h"

#include "petcontroller.h"
#include <assert.h>
/*
Adauga pet
*/
void PetController::add(const char* type, const char* species, int price) {
	//Pet p{ type,species,price };
	repo.store(Pet{ type,species,price });
}
/*
Toate
*/
VectorDinamic PetController::getAllPets() {
	return repo.getAll();	
}

/*
sortare dupa un criteriu dat (o functie)
*/
void sort(VectorDinamic& v, int(*CmpFct)(const Pet& p1, const Pet& p2)) {
	for (int i = 0; i < v.size(); i++) {
		for (int j = i + 1; j < v.size(); j++) {
			if (CmpFct(v.get(i), v.get(j)) > 0) {
				//interschimbam
				Pet aux = v.get(i);
				v.set(i, v.get(j));
				v.set(j, aux);
			}
		}
	}
}
/*
Sortat dupa pret
*/
VectorDinamic PetController::getSortByPrice() {
	auto v = repo.getAll();
	sort(v, cmpByPrice);
	return v;
}
/*
Sortat dupa tip
*/
VectorDinamic PetController::getSortByType() {
	auto v = repo.getAll();
	//sort(v, cmpByType);
	sort(v, [](const Pet& p1, const Pet& p2) {return strcmp(p1.getType(),p2.getType()); });
	return v;
}
/*
Filtrare dupa pret
*/
VectorDinamic PetController::getFilterByPrice(int price) {
	VectorDinamic rez;
	VectorDinamic all = repo.getAll();
	for (int i = 0; i < all.size(); i++) {
		if (all.get(i).getPrice()>price) {
			rez.add(all.get(i));
		}
	}
	return rez;
}


void testCtr() {
	PetRepo rep;
	PetController ctr{ rep };
	ctr.add("aaa", "bbb", 3);
	ctr.add("ccc", "bbb", 2);
	ctr.add("bbb", "bbb", 1);

	VectorDinamic v = ctr.getSortByPrice();
	assert(v.get(0).getPrice() == 1);
	assert(v.get(1).getPrice() == 2);
	assert(v.get(2).getPrice() == 3);

	VectorDinamic v2 = ctr.getSortByType();
	assert(strcmp(v2.get(0).getType(),"aaa")==0);
	assert(strcmp(v2.get(1).getType(), "bbb") == 0);
	assert(strcmp(v2.get(2).getType(), "ccc") == 0);

	/*v = ctr.getSortByType();
	assert(strcmp(v.get(0).getType(), "aaa") == 0);
	assert(strcmp(v.get(1).getType(), "bbb") == 0);
	assert(strcmp(v.get(2).getType(), "ccc") == 0);
	*/

	VectorDinamic filtrat = ctr.getFilterByPrice(2);
	assert(filtrat.size() == 1);
	assert(filtrat.get(0).getPrice() == 3);
}