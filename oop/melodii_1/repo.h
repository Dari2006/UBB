#include <vector>
using std::vector;
#include "melodie.h"
#include <algorithm>

class Repo {
private:
	vector<Melodie> melodii;
	string filename;
	void loadFomFile();
public:
	Repo(string numeF) : filename{ numeF } {
		loadFomFile();
		sort(melodii.begin(), melodii.end(), [](Melodie a, Melodie b){return a.getRank() < b.getRank();});
	}
	const vector<Melodie>& getAll() {
		return melodii;
	}
};