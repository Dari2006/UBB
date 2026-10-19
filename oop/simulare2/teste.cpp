#include "teste.h"
//#include "repo.h"
#include <assert.h>
#include <iostream>
#include "service.h"

using std::cout;

void testElev() {
	Elev el{"eu", "lazar", 108, {"jurnalism"}};
	assert(el.getNume() == "eu");
	assert(el.getNrMatricol() == 108);
	assert(el.getScoala() == "lazar");
	assert(el.getActiv()[0] == "jurnalism");
	assert(el.getActiv().size() == 1);
	cout<<"test eelv ok\n";
}

void testRepo(){
	Repo r{};
	Elev e{"Darian", "Lazar", 108, {"caca", "pisu"}};
	r.adaugaElev(e);
	vector<Elev> toate = r.getAll();
	assert(toate.size() == 1);
	assert(toate[0].getNume() == "Darian");
	cout<<"test repo ok\n";
}

void testService() {
	Repo r{};
	Service s{r, "test.txt"};
	s.loadFromFile();
	vector<Elev> toate = s.getAll();
	assert(toate.size() == 2);
}

void testAll() {
	testElev();
	testRepo();
	testService();
}