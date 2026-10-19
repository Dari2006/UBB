#include "service.h"

const vector<Telefon>& Service::filtrare(const string& cat) {
	const auto& toate = getAll();
	vector<Telefon> filtr;
	for (auto tel : toate) {
		if (tel.getCategorie() == cat) {
			filtr.push_back(tel);
		}
	}
	return filtr;
}