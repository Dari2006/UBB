#include "tests/tests.h"
#include "domain/domain.h"
#include <stdio.h>
#include "business/service.h"
#include "consola/ui.h"
#include "infrastructura/repo_dinamic.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
	ruleaza_toate_testele();
	printf("\n");
	//printf("\ngut");
	RepoProduse* repo = creeaza_repo_dinamic();
	ui_run(repo);
	distruge_repo(repo);
	
	_CrtDumpMemoryLeaks();
	
	return 0;
}

