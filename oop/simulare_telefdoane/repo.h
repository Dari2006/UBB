#include "teelfon.h"
#include <vector>
using std::vector;

class Repo {
private:
	vector<Telefon> telefoane;
	string filename;
	void loadFromFile();
public:
	Repo(string nume) : filename{ nume } {
		loadFromFile();
	}
	const vector<Telefon>& getAll() {
		return telefoane;
	}
};