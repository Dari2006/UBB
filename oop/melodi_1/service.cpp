#include "service.h"
#include <exception>
void Service::sterge(const string& titlu) {
	int k{0};
	int index{-1};
	int i{0};
	const auto& toate = getAll();

	auto it = std::find_if(toate.begin(), toate.end(), [&titlu](const Melodie& m){return m.getTitlu() == titlu;});
	if (it == toate.end()) {
		throw std::runtime_error("nu am gasit");
	}
	const auto& mel = *it;
	for (const auto& m : toate) {
		if (m.getArtist() == mel.getArtist()) {
			k++;
		}
		if (m.getTitlu() == mel.getTitlu()) {
			index = i;
		}
		++i;
	}
	if (k == 1) {
		throw std::runtime_error("ultima");
	}
	r.sterge(index);
}