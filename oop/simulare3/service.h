#include "repo.h"

class Service {
private:
	Repo& r;
public:
	Service(Repo& rep) : r{ rep } {

	}
	const vector<Rochie>& getAll() {
		return r.getAll();
	}
};