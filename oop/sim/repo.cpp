#include "repo.h"
#include <fstream>
#include <sstream>
void Repo::loadFromFile() {
	std::ifstream f(filename);

	string linie;
	while (getline(f, linie)) {
		std::stringstream ss(linie);  //folosim un stream nou
		string c;
		getline(ss, c, ';');

		string t;
		getline(ss, t, ';');

		string categ;
		getline(ss, categ, ';');

		string creat;
		getline(ss, creat, ';');

		string descr;
		getline(ss, descr, ';');

		Podcast pod{c, t, categ, creat, descr};
		podcasts.push_back(pod);
	}
}