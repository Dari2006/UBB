#include <string>
using std::string;


class Melodie {
private:
	int id; //unic
	string titlu;
	string artist;
	int rank; //intre 1 si 10
public:
	
	Melodie(int id, string titlu, string artist, int rank) : id{ id }, titlu{ titlu }, artist{ artist }, rank{ rank } {

	}
	const int& getId() {
		return id;
	}
	const string& getTitlu() {
		return titlu;
	}
	const string& getArtist() {
		return artist;
	}
	const int& getRank() {
		return rank;
	}
};