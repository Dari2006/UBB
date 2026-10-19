#include "elev.h"
#include <vector>
using std::vector;

class Repo {
private:
	vector<Elev> elevi;
public:
	void adaugaElev(const Elev& e);
	vector<Elev> getAll() {
		return elevi;
	}
};