#include "Activitate.h"

bool Activitate::operator==(const Activitate& ot) const{
	return descriere == ot.descriere && titlu == ot.titlu && tip == ot.tip && durata == ot.durata;
}