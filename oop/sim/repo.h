#include "podcast.h"
#include <vector>
using std::vector;

class Repo {
private:
	vector<Podcast> podcasts;  //vector cu instantele stocate
	string filename;  //numele fisierului din care se citeste
	void loadFromFile();  //metoda care citeste din fisier
public:
	Repo(const string& fn) : filename{ fn } {
		loadFromFile();
	}

	//returneaza toate instanele
	const vector<Podcast>& getAll() {
		return podcasts;
	}

	//returneaza copie a instantelor
	 vector<Podcast> getAllCopy() {
		return podcasts;
	}
};