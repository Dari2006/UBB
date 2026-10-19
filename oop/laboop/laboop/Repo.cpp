#include "Repo.h"
#include <algorithm>

void Repo::adauga(const Activitate& a) {
	auto p = std::find(activitati.begin(), activitati.end(), a);
	if (p != activitati.end()) { throw RepoException("Descrierea exista deja"); }
	else {
		activitati.push_back(a);
	}
}

void Repo::sterge(const Activitate& a) {
	auto p = std::find(activitati.begin(), activitati.end(), a);
	if (p == activitati.end()) {
		throw RepoException("Actibitatea nu exirtsa");}
	else {
		activitati.erase(p);
	}
}

void Repo::actualizeaza(const Activitate& v, const Activitate& n) {
	auto p = std::find(activitati.begin(), activitati.end(), v);
	if (p != activitati.end()) {
		auto index = std::distance(activitati.begin(), p);
		activitati[index] = n;
	}
	else {
		throw RepoException("Activitatea nu exista!");
	}
}

