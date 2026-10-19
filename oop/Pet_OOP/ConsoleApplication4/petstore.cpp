// ConsoleApplication4.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


#include "pet.h"
#include "vectordinamic.h"
#include "petcontroller.h"
#include "storeui.h"

void addSamplePets(PetController& ctr) {
	ctr.add( "Pasare", "Papagal", 20);
	ctr.add( "Pasare", "Randunica", 2);
	ctr.add( "Peste", "Pastrav", 90);
	ctr.add( "Peste", "Rechin", 100);
	ctr.add( "Pasare", "Soim", 200);
}

int main()
{
	testPet();
	testVector();
	testCtr();
	{
	PetRepo rep;
	PetController ctr{ rep };
	addSamplePets(ctr);
	PetUI ui{ ctr };
	ui.startUI();
	}
	_CrtDumpMemoryLeaks();
    return 0;
}

