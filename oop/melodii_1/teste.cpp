#include "service.h"
#include <assert.h>

void testRepo() {
	Repo r{"melodii.txt"};
	assert(r.getAll().size() == 2);
	auto toate = r.getAll();
	assert(toate[0].getRank() == 7);
}

void runTests() {
	testRepo();
}