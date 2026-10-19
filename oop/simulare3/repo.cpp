#include "repo.h"
#include <fstream>
#include <sstream>
void Repo::loadFromFile() {
	std::ifstream f(filename);
	string linie;
	while (getline(f, linie)) {
		std::stringstream ss(linie);
		string nr;
		getline(ss, nr, ',');
		int cod = stoi(nr);
		string den;
		getline(ss, den, ',');
		string mar;
		getline(ss, mar, ',');
		nr.clear();
		getline(ss, nr, ',');
		int pr = stoi(nr);
		string disp;
		getline(ss, disp, ',');
		bool d = false;
		if (disp == "True") {
			 d = true;
		}
		Rochie a{cod, den, mar, pr, d};
		rochii.push_back(a);
	}
}