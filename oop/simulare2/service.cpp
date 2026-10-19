#include "service.h"
#include <algorithm>
#include <fstream>
#include <sstream>

void Service::loadFromFile() {
	std::ifstream f(filename);
	string nume;
	string scoala;
	int nrMatricol;
	string activitate;
	vector<string> activitati;
	string linie;
	while (std::getline(f, linie)) {
		activitati.clear();
		std::stringstream ss{linie};
		ss >> nume;
		ss >> scoala;
		ss >> nrMatricol;
		while (ss >> activitate) {
			activitati.push_back(activitate);
		}
		Elev e{nume, scoala, nrMatricol, activitati};
		r.adaugaElev(e);
	}
}

const vector<Elev> Service::sortNume() {
	 auto toate = getAll();
	//vector<Elev> sortat;
	sort(toate.begin(), toate.end(), []( Elev a, Elev b){return a.getNume() < b.getNume();});
	return toate;
}