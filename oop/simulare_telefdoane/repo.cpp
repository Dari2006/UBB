#include "repo.h"
#include <fstream>
#include <sstream>

void Repo::loadFromFile() {
	std::ifstream f(filename);
	string linie;
	while (getline(f, linie)) {
		std::stringstream ss(linie);
		string nr;
		//getline(ss, nr);
		ss >> nr;
		int cod = stoi(nr);

		string den;
		//getline(ss, den);
		ss >> den;
		string categ;
		//getline(ss, categ);
		ss>>categ;
		nr.clear();
		string a;
		//getline(ss, a);
		ss >> a;
		int an = stoi(a);

		nr.clear();
		string b;
		//getline(ss, b);
		ss >> b;
		int bani = stoi(b);

		Telefon tel{cod, den, categ, an, bani};
		telefoane.push_back(tel);
	}

}