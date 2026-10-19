#pragma once
#include "Activitate.h"
#include "Lista.h"
#include <vector>
#include <string>
#include <map>
#include <random>
using std::string;
using std::vector;

class RepoException {
private:
	/*mesajul de eroare afisat*/
	string msg;
public:
	RepoException(string m): msg {m} {
	}
	/*metoda care returneaza mesajul de eroare*/
	const string& getMesaj() const noexcept{
		return msg;
	}
};


class Repo{
private:
	vector<Activitate> activitati;
public:
	Repo() = default;
	void adauga(const Activitate& a);
	void sterge(const Activitate& a);
	void actualizeaza(const Activitate& v, const Activitate& n);
	const vector<Activitate>& getAll() { return activitati; }
};
