#pragma once
#include "repo.h"

class Service {
private:
	Repo& r;
public:
	Service(Repo& rp): r{rp}{
	}
	const vector<Melodie>& getAll() const {
		return r.getAll();
	}

	vector<Melodie>& getall() {
		return r.getall();
	}
	void save() {
		r.saveToFile();
	}

	void sterge(const string& titlu);
};