#include <string>
using std::string;

class Podcast {
private:
	string cod;
	string titlu;
	string categorie;
	string creator;
	string descriere;
public:
	//constructor cu parametri
	Podcast(const string& c, const string& t, const string& cat, const string& creat, const string& descr) :
		cod{ c }, titlu{ t }, categorie{ cat }, creator{ creat }, descriere{ descr } {

	}

	//getteri
	const string& getCod() {
		return cod;
	}
	const string& getTitlu() {
		return titlu;
	}
	const string& getCategorie() {
		return categorie;
	}
	const string& getCreator() {
		return creator;
	}
	const string& getDescriere() {
		return descriere;
	}
};