#include "rochie.h"
#include <vector>
using std::vector;
class Repo {
private:
	string filename;
	vector<Rochie> rochii;
	void loadFromFile();
public:
	Repo(string name) : filename{ name } {
		loadFromFile();
	}
	const vector<Rochie>& getAll() {
		return rochii;
	}
};