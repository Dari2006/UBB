#include <string>
using std::string;


class Telefon {
private:
	int codProdus;
	string denumire;
	string categorie;
	int anFabricatie;
	int pret;
public:
	Telefon(int cod, string den, string cat, int an, int bani) : codProdus{ cod }, denumire{ den }, categorie{ cat }, anFabricatie{ an }, pret{ bani } {

	}
	const int& getCod() {
		return codProdus;
	}
	const string& getDenumire() {
		return denumire;
	}
	const string& getCategorie() {
		return categorie;
	}
	const int& getAn() {
		return anFabricatie;
	}
	const int& getPret() {
		return pret;
	}
};