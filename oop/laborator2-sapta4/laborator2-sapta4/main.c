#include "ui.h"
#include "service.h"
#include "repo.h"
#include "tests.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main() {
    runAllTests();
    Repo* r = createRepo();
    Service* s = createService(r);
    runUI(s);
    destroyService(s);
    destroyRepo(r);
    _CrtDumpMemoryLeaks();
    return 0;
}