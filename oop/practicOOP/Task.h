#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;
class Task
{
private:
	int id; //unic
	string descriere;
	vector<string> programatori; //persoanele care lucreaza la task
	string stare; //poate fi: open/inprogress/closed
public:
	Task(int id, const string& descr, const vector<string>& pro, const string& st) : id{ id }, descriere{ descr }, programatori{ pro },
	stare{ st } {

	}
	//getteri
	int getId() const{
		return id;
	}
	const string& getDescriere() const{
		return descriere;
	}
	const vector<string>& getProgramatori() const{
		return programatori;
	}
	const string& getStare() const{
		return stare;
	}
};

