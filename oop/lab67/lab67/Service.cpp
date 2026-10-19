#include "Service.h"
#include <algorithm>
#include <random>
#include <exception>
#include <memory>
using std::vector;
using std::string;
Service::~Service() = default;
/*verificam daca parametii introdusi de utilizator sunt valizi*/
void Validator::valideaza(const string& titlu, const string& descr, const string& tip, double durata) const{
	vector<string> erori;
	if(titlu.empty())
		erori.push_back("Titlu invalid");
	if(descr.empty())
		erori.push_back("Descriere invalida");
	if(tip.empty())
		erori.push_back("Tip invalid");
	if(durata <= 0.5)
		erori.push_back("Durata invalida");
	if(erori.size() > 0)
		throw ValidatorException(erori);
}

void Service::adauga(const string& titlu, const string& descr, const string& tip, double durata) {
	val.valideaza(titlu, descr, tip, durata); //exceptia trebuie prinsa de ui
	Activitate a{titlu, descr, tip, durata};
	rep.adauga(a);
	undoActions.push_back(std::make_unique<UndoAdauga>(rep, a));
}

void Service::sterge(const string& titlu, const string& descr, const string& tip, double durata) {
	Validator e;  //exceptia trebuie prinsa de ui
	e.valideaza(titlu, descr, tip, durata);
	Activitate a{titlu, descr, tip, durata};
	rep.sterge(a);
	undoActions.push_back(std::make_unique<UndoSterge>(rep, a));
}

void Service::actualizeaza(const string& titluv, const string& descrv, const string& tipv, double duratav,
	const string& titlun, const string& descrn, const string& tipn, double duratan) {

	Validator e; //exceptiile trebuie prinse de ui
	e.valideaza(titluv, descrv, tipv, duratav);
	e.valideaza(titlun, descrn, tipn, duratan);

	Activitate v{ titluv, descrv, tipv, duratav};
	Activitate n{titlun, descrn, tipn, duratan};

	rep.actualizeaza(v, n);
	undoActions.push_back(std::make_unique<UndoActualizeaza>(rep, v, n));
}

vector<Activitate> Service::cauta(const string& titlu) const {
	vector<Activitate> rez{ };
	const vector<Activitate>&list = getAll();

	copy_if(list.begin(), list.end(), std::back_inserter(rez), [&titlu](const Activitate &p) {return titlu == p.getTitlu();});

	return rez;
}



vector<Activitate> Service::filtrareGenerica(const string& param, ConditieFiltrare cond) {
	vector<Activitate> rez;
	
	vector<Activitate> toate = getAll();
	copy_if(toate.begin(), toate.end(), std::back_inserter(rez), [&param, cond](Activitate &p){return cond(p, param);});

	return rez;
}



vector<Activitate> Service::sortDescriereCresc() const {
	auto lista = getAll();
	
	sort(lista.begin(), lista.end(), [](Activitate &a, Activitate &b){return a.getDescriere() < b.getDescriere();});

	return lista;
}

vector<Activitate> Service::sortDescriereDescr() const {
	auto lista = getAll();
	
	sort(lista.begin(), lista.end(), [](Activitate &a, Activitate &b){return a.getDescriere() > b.getDescriere();});

	return lista;
}

vector<Activitate> Service::sortTipDurata() const {
	auto lista = getAll();
	
	sort(lista.begin(), lista.end(), [](const Activitate& a, const Activitate& b){
		if (a.getTip() != b.getTip()) {
			return a.getTip() < b.getTip();}
		else {
			return a.getDurata() < b.getDurata();
		}
			});

	return lista;
}

vector<Activitate> Service::sortTitluCresc() const {
	auto lista = getAll();
	
	sort(lista.begin(), lista.end(), [](const Activitate &a, const Activitate &b){return a.getTitlu() < b.getTitlu();});

	return lista;
}


vector<Activitate> Service::sortTitluDescr() const {
	auto lista = getAll();
	
	sort(lista.begin(), lista.end(), [](const Activitate &a, const Activitate &b){return a.getTitlu() > b.getTitlu();});

	return lista;
}

void Service::adauga_planificare(const string& titlu) {
	const auto &toate = getAll();
	auto it = std::find_if(toate.begin(), toate.end(), [&titlu](const Activitate &p){return p.getTitlu() == titlu;});
	if (it != toate.end()) {
		planCurent.adauga(*it);
	}
	else {
		throw ServiceException{"Nu exista activitati cu acest titlu"};
	}
}

void Service::genereazaPlanRandom(size_t nr) {
	auto toate = rep.getAll();

	if (nr > toate.size()) {
		nr = toate.size();
	}

	planCurent.goleste();

	std::shuffle(toate.begin(), toate.end(), std::default_random_engine(std::random_device{}()));

	for (size_t i{ 0 }; i < nr; i++) {
		planCurent.adauga(toate[i]);
	}
}

void Service::exportaPlanificareaCSV(const string& numeFisier) const {
	
	planCurent.exportaCSV(numeFisier);
}

void Service::exportaPlanificareaHTML(const string& numeFisier) const {
	planCurent.exportaHTML(numeFisier);
}

std::map<string, int> Service::raportPeTipuri() const {
	std::map<string, int> rez;
	for (const auto& a : rep.getAll()) {
		rez[a.getTip()]++; 
	}
	return rez;
}

void Service::undo() {
	if (undoActions.empty()) {
		throw ServiceException("Nu se mai poate face undo!");
	}

	undoActions.back()->doUndo();
	undoActions.pop_back();
}