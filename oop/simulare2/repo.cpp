#include "repo.h"
#include <vector>
#include <string>
#include <exception>
using std::vector;
using std::string;

void Repo::adaugaElev(const Elev& e) {
	for (const auto& el : elevi) {
		if (el.getNrMatricol() == e.getNrMatricol()) {
			throw (std::exception{});
		}
	}
	elevi.push_back(e);
}
