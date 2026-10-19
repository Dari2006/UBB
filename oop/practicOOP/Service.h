#pragma once
#include "Repo.h"
#include <exception>

class Validator{

};

class Service
{
private:
	Repo& r;  //service-ul primeste un repo prin parametru
public:
	//constructor cu parametru
	Service(Repo& rep) : r{ rep } {

	}
	//getter
	const vector<Task>& getAll() const {
		return r.getAll();
	}
	//metoda adauga un task
	//param: id - int, descr - string, pro - vector<int>, stare - string - parametrii noului task
	void add(int id, const string& descr, const vector<string>& pro, const string& stare) {
		Task t{id, descr, pro, stare};
		r.add(t);
	}
};

