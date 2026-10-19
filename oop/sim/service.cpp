#include "service.h"
#include <algorithm>

//returneaza un vector de podcast-uri sortate crescator dupa titlu
 vector<Podcast> Service::sortTitlu() {
	auto toate = getAllCopy();
	std::sort(toate.begin(), toate.end(), [](Podcast a, Podcast &b){return a.getTitlu() < b.getTitlu();});
	return toate;
}

 //returneaza un vector de podcast-uri sortate crescator dupa creator
vector<Podcast> Service::sortCreator() {
	auto toate = getAllCopy();
	std::sort(toate.begin(), toate.end(), [](Podcast a, Podcast& b) {return a.getCreator() < b.getCreator();});
	return toate;
}
