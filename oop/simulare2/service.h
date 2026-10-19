#include "repo.h"

class Service {
private:
	Repo r;
	string filename;
public:
	Service(const Repo& rep, const string& fn) : r{ rep }, filename {fn} {

	}
	void loadFromFile();

	const vector<Elev> getAll() {
		return r.getAll();
	}

	const vector<Elev> sortNume();
};