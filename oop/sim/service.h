#include "repo.h"

class Service {
private:
	Repo& r;  //service primeste referinta catre repo

public:
	//constructor cu parametrii
	Service(Repo& rep) : r{ rep } {

	}
	//returneaza insatele adaugate
	const vector<Podcast>& getAll() {
		return r.getAll();
	}

	//returneaza copie a instantelor adaugate
	 vector<Podcast> getAllCopy() {
		return r.getAllCopy();
	}
	//sortari
	vector<Podcast> sortTitlu();
	vector<Podcast> sortCreator();

};