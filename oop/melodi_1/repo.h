#pragma once
#include "Melodie.h"
#include <vector>
using std::vector;
#include <fstream>
#include <sstream>
#include <algorithm>
class Repo {
private:
	vector<Melodie> melodii;
	string filename;

	void sortMelodii() {
		sort(melodii.begin(), melodii.end(), [](const Melodie& a, const Melodie& b) {return a.getRank() < b.getRank();});
	}
public:
	Repo(const string& f) : filename{ f } {
		loadFromFile();
	}
	void loadFromFile();
	const vector<Melodie>& getAll() const {
		return melodii;
	}
	vector<Melodie>& getall() {
		return melodii;
	}
	
	void saveToFile();

	void sterge(int index) {
		melodii.erase(melodii.begin() + index);
	}
};