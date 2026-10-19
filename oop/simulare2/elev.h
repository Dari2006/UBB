#include <string>
#include <vector>
using std::vector;
using std::string;


class Elev {
private:
	string nume;
	string scoala;
	int nrMatricol;  //unic
	vector<string> activ;
public:
	Elev() {
	}
	Elev(const string& n, const string& scl, const int& nr, const vector<string>& act) : nume{ n }, scoala{ scl }, nrMatricol{ nr }, activ{ act } {

	}
	const string &getNume() const{
		return nume;
	}
	const string& getScoala() const{
		return scoala;
	}
	const int& getNrMatricol() const{
		return nrMatricol;
	}
	const vector<string>& getActiv() const{
		return activ;
	}
};