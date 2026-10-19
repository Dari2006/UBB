#include "stdafx.h"

#include "pet.h"
#include <string.h>
#include <assert.h>

Pet fnct(Pet p) {
	p.setPrice(10);
	return p;
}
void testPet() {
	Pet p{ "abc","dce",8 };
	assert(p.getPrice() == 8);

	assert(strcmp(p.getType(), "abc") == 0);

	Pet p2 = fnct(p);
	//verific daca cele 2 pointeaza la zone de memorie diferite
	//adica s-a facut copiere
	assert(p.getType() != p2.getType());
	//compar efectiv c-stringurile (caracter cu caracter)
	assert(strcmp(p.getType(), p2.getType()) == 0);

	p = p2;

	//verific daca cele 2 pointeaza la zone de memorie diferite
	//adica s-a facut copiere
	assert(p.getType() != p2.getType());
	//compar efectiv c-stringurile (caracter cu caracter)
	assert(strcmp(p.getType(), p2.getType()) == 0);

}


int cmpByPrice(const Pet& p1, const Pet& p2) {
	if (p1.getPrice() == p2.getPrice()) {
		return 0;
	}
	if (p1.getPrice() < p2.getPrice()) {
		return -1;
	}
	return 1;
}

int cmpByType(const Pet& p1, const Pet& p2) {
	return strcmp(p1.getType(), p2.getType());
}