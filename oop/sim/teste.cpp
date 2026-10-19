#include "teste.h"
#include <assert.h>
//#include "podcast.h"
//#include "repo.h"
#include <qmessagebox.h>
#include "service.h"


void testPodcast() {
	Podcast pod{"P01", "Mindset de luni", "dezvoltare personala", "Urban Talks", "Discutii despe productivitate"};
	assert(pod.getCod() == "P01");
	assert(pod.getTitlu() == "Mindset de luni");
	assert(pod.getCategorie() == "dezvoltare personala");
	assert(pod.getCreator() == "Urban Talks");
	assert(pod.getDescriere() == "Discutii despe productivitate");
}


void testRepo() {
	Repo r{"testePod.txt"};
	auto toate = r.getAll();
	assert(toate.size() == 3);
	assert(toate[0].getCod() == "P01");
}


void testService() {
	Repo r{ "testePod.txt" };
	Service s{r};

	auto toate = s.getAll();

	assert(toate.size() == 3);

	auto sortTitlu = s.sortTitlu();
	assert(sortTitlu.size() == 3);
	assert(sortTitlu[0].getTitlu() == "Crime Stories");
	assert(sortTitlu[1].getTitlu() == "Mindset de luni");
	assert(sortTitlu[2].getTitlu() == "Tech pe scurt");
}

void runTests() {
	testPodcast();
	testRepo();
	testService();
}