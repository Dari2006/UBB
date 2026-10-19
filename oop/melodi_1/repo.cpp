#include "repo.h"

void Repo::loadFromFile() {
	std::ifstream f(filename);
	if(!f.is_open()) return;
	string linie;
	while (getline(f, linie)) {
		std::stringstream ss(linie);
		int id{0};
		ss >> id;
		string titlu;
		ss >> titlu;
		string artist;
		ss >> artist;
		int rank{0};
		ss >> rank;
		melodii.push_back(Melodie{id, titlu, artist, rank});
	}
	f.close();
	
	sortMelodii();
}

void Repo::saveToFile() {
	std::ofstream f(filename);
	if(!f.is_open()) return;
	for (const auto& m : melodii) {
		f << m.getId() << " " << m.getTitlu() << " " << m.getArtist() << " " << m.getRank() << "\n";
	}
	f.close();
	sortMelodii();
}