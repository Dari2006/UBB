#pragma once

#include <string>
using std::string;

class Melodie	{
private:
	int id;  //unic
	string titlu;
	string artist;
	int rank;   //int >=0 && <=10
public:
	Melodie(const int  i, const string& t, const string& a, const int r) : id{ i }, titlu{ t }, artist{ a }, rank{ r } {

	}
	int getId () const{
		return id;
	}

	const string& getTitlu() const {
		return titlu;
	}

	const string& getArtist() const {
		return artist;
	}

	int getRank() const {
		return rank;
	}

	void setRank(const int r) {
		rank = r;
	}
	void setTitlu(const string& t) {
		titlu = t;
	}
};

