#include "repo.h"

class Service {
private:
	Repo& r;
public:
	Service(Repo& rep) : r{ rep } {

	}
	const vector<Telefon>& getAll() {
		return r.getAll();
	}
	const vector<Telefon>& filtrare(const string& cat);
};