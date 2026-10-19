#include "teste.h"

void testTask() {
	vector<string> p{"Andrei", "Mircea"};
	Task t{1, "site", p, "open"};
	assert(t.getId() == 1);
	assert(t.getDescriere() == "site");
	const auto& pro = t.getProgramatori();
	assert(pro.size() == 2);
	assert(pro[0] == "Andrei");
	assert(pro[1] == "Mircea");
	assert(t.getStare() == "open");
}

void testRepo() {
	Repo r{"tasks.txt"};
	const auto& toate = r.getAll();
	assert(r.getAll().size() == 3);
	const auto& t = toate[2];
	assert(t.getStare() == "closed");
	assert(t.getId() == 3);
	assert(t.getDescriere() == "idk");
	assert(t.getProgramatori().size() == 3);
	assert(t.getProgramatori()[0] == "Alex");
	const auto& t2 = toate[1];
	assert(t2.getStare() == "inprogress");
	assert(t2.getProgramatori().size() == 1);

	const auto& t3 = toate[0];
	assert(t3.getStare() == "open");

	

}


void testService()
{
	Repo r{"tasks.txt"};
	Service s{r};
	const auto& toate = s.getAll();
	assert(toate.size() == 3);
	const auto& t = toate[2];
	assert(t.getStare() == "closed");
	assert(t.getId() == 3);
	assert(t.getDescriere() == "idk");
	assert(t.getProgramatori().size() == 3);
	assert(t.getProgramatori()[0] == "Alex");
	const auto& t2 = toate[1];
	assert(t2.getStare() == "inprogress");
	assert(t2.getProgramatori().size() == 1);

	const auto& t3 = toate[0];
	assert(t3.getStare() == "open");

	int id= 5;
	string descr = "nuj";
	vector<string> p{"1", "2"};
	string stare = "open";
	s.add(id, descr, p, stare);
	assert(s.getAll().size() == 4);
}

void testAll() {
	testTask();
	testRepo();
	testService();
}