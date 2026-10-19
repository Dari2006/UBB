#include "teste.h"
#include "Service.h"
#include "Repo.h"
#include "Activitate.h"
#include "ui.h"
#define _CRTDBG_MAP_ALLOC
#define _CRT_SECURE_NO_WARNINGS
#include <string>
int main() {
	{
		ruleazaTeste();
		Repo r;
		Validator v;
		Service s(r, v);
		UI u(s);
		u.run();
	}
#ifdef _MSC_VER
	_CrtDumpMemoryLeaks();
#endif
	return 0;
}

/*TO DO:
- adauga in ui metoda care se ocupa cu citirea parametrilor pentru activitati
- formateaza afisarea de activitati
- adauga metoda care se ocupa cu afisarea unei liste de activitati
*/

