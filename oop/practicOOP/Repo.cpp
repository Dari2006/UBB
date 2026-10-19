#include "Repo.h"

void Repo::loadFromFile(const string& file) {
	std::ifstream f(file);
	if(!f.is_open())
		return;
	string linie;
	int id{};
	string text;
	string descr;
	vector<string> pro;
	string stare;
	while (getline(f, linie)) {
		if (linie.empty()) {
			continue;
		}
		std::stringstream ss(linie);
		ss >> id;
		ss >> descr;

		pro.clear();
		pro.resize(0);
		ss >> text;
		while (text != "open" && text != "inprogress" && text != "closed") {
			//ss >> text;
			if(text != "open" && text != "inprogress" && text != "closed")
				pro.push_back(text);
			ss >> text;

		}
		if (text == "open" || text == "inprogress" || text == "closed"){
			Task t{ id, descr, pro, text};
			tasks.push_back(t);

			continue;
		}
		else {
			ss >> stare;
			
		}
		Task t{id, descr, pro, stare};
		tasks.push_back(t);

	}
	sortTasks();
	f.close();
}


void Repo::saveToFile(const string& file) const{
	std::ofstream f(file);
	if (!f.is_open()) {
		return;
	}
	const auto& toate = getAll();
	for (const auto& t : toate) {
		f << t.getId() << " " << t.getDescriere() << " ";

		const auto& pro = t.getProgramatori();
		for(const auto& p : pro)
			f << p << " ";
		
		f << t.getStare() << std::endl;

	}


	f.close();
}
