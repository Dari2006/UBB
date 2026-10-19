#include "repo.h"
#include <fstream>
#include <sstream>
void Repo::loadFomFile() {
	std::ifstream f(filename);
	string linie;
	while (getline(f, linie)) {
		std::stringstream ss(linie);
		string nr;
		ss >> nr;     //sau getline(ss, nr);
		int id = stoi(nr);

		string titlu;
		ss >> titlu;

		string artist;
		ss >> artist;

		nr.clear();
		ss >> nr;
		int rank = stoi(nr);

		Melodie mel{id, titlu, artist, rank};
		melodii.push_back(mel);
	}
}