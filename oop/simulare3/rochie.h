#include <string>
using std::string;

class Rochie {
private:
	int cod; //unic
	string	denumire;
	string marime;
	int pret;
	bool disponibilitate;
public:
	Rochie(int d, string den, string mar, int pr, bool disp) : cod{ d }, denumire{ den }, marime{ mar }, pret{ pr }, disponibilitate{ disp } {

	}
	const int& getCod() {
		return cod;
	}
	const string& getDenumire() {
		return denumire;
	}
	const string& getMarime() {
		return marime;
	}
	const int& getPret() {
		return pret;
	}
	const bool getDisponibilitate() {
		return disponibilitate;
	}
	void setDisponibilitate(bool disp) {
		disponibilitate = disp;
	}
};