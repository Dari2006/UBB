#include "repo.h"


class Service {
private:
	Repo& r;

public:
	Service(Repo& rep): r{ rep } {

	}
	const vector<Melodie> getAll() {
		return r.getAll();
	}
};