#pragma once
#include <string>
#include "Repo.h"
#include "Activitate.h"
#include "planificare.h"
#include <map>	
#include <vector>
#include <memory>
using std::string;
using std::vector;
typedef bool (*ConditieFiltrare)(const Activitate&, const string&);
class ActiuneUndo;

class ValidatorException {
private:
	vector<string> erori;
public:
	ValidatorException(const vector<string>& er) : erori{ er } {

	}
	const vector<string>& getErori() const noexcept {
		return erori;
	}
};

/*clasa pentru validare activitati*/
class Validator {
public:
	/*metoda valideaza, returneaza 1 daca parametrii sunt valizi, 0 altfel*/
	void valideaza(const string& titlu, const string& descr, const string& tip, double durata) const;
};

class ServiceException {
private:
	string msg;
public:
	ServiceException(string m) : msg{ m } {
	}string getMessage() const { return msg; }
};


class Service {
private:
	Repo& rep; //service primeste un repository ca parametru
	Validator val; //service primeste un validator ca parametru
	Planificare planCurent;
	vector<std::unique_ptr<ActiuneUndo>> undoActions;
public:
	Service(Repo& rep, Validator& val) : rep {rep}, val {val} {

	}
	~Service();
	/*adauga o activitate noua*/
	void adauga(const string& titlu, const string& descr, const string& tip, double durata);

	/*returneaza lista cu toate instantele*/
	const vector<Activitate>& getAll() const noexcept{
		return rep.getAll();
	}
	/*sterge o activitate*/
	void sterge(const string& titlu, const string& descr, const string& tip, double durata);
	/*actualizeaza o activitate*/
	void actualizeaza(const string& titluv, const string& descrv, const string& tipv, double duratav,
					  const string& titlun, const string& descrn, const string& tipn, double duratan);
	/*cauta o activitate dupa titlu
	- returneaza activitatile gasite*/
	vector<Activitate> cauta(const string& titlu) const;
	const Activitate& cautaDupaAtribute(const string& titlu, const string& descriere, const string& tip, double durata);
	/*filtrarea dupa tip sau descriere*/
	vector<Activitate> filtrareGenerica(const string& param, ConditieFiltrare cond);
	/*sorteaza dupa titlu crescator*/
	vector<Activitate> sortTitluCresc() const;
	/*sorteaza dupa titlu descrescator*/
	vector<Activitate> sortTitluDescr() const;
	/*sorteaza crescator dupa tip + durata*/
	vector<Activitate> sortTipDurata() const;
	/*sorteaza dupa descriere crescator*/
	vector<Activitate> sortDescriereCresc() const;
	/*sorteaza dupa descriere descrescator*/
	vector<Activitate> sortDescriereDescr() const;
	void adauga_planificare(const string &titlu);
	void genereazaPlanRandom(size_t nr);
	// non-const overload so callers can modify/subscribe to the plan
	Planificare& getPlan() noexcept { return planCurent; }
	// const overload for read-only access
	const Planificare& getPlan() const noexcept { return planCurent; }
	void golestePlan() noexcept { 
		planCurent.goleste(); 
	}size_t dimPLan() const noexcept {return planCurent.dim();}
	void exportaPlanificareaCSV(const string& numeFisier) const;
	void exportaPlanificareaHTML(const string& numeFisier) const;
	const vector<Activitate>& getToateDinPlan() const {
		return planCurent.getToate();
	}
	std::map<string, int> raportPeTipuri() const;
	void undo();
};

inline bool filtreazaDupaTip(const Activitate& a, const string& tip) noexcept{
	return a.getTip() == tip;
}
inline bool filtreazaDupaDescriere(const Activitate& a, const string& desc) noexcept{
	/**/
	return a.getDescriere() == desc;
}

class ActiuneUndo {
public:
	virtual void doUndo() = 0; 
	virtual ~ActiuneUndo() = default; 
};

class UndoAdauga : public ActiuneUndo {
	Activitate adaugat;
	Repo& repo;
public:
	UndoAdauga(Repo& r, const Activitate& e) : repo{ r }, adaugat{ e } {}
	void doUndo() override {
		repo.sterge(adaugat); 
	}
};

class UndoSterge : public ActiuneUndo {
	Activitate sters;
	Repo& repo;
public:
	UndoSterge(Repo& r, const Activitate& e) : repo{ r }, sters{ e } {}
	void doUndo() override {
		repo.adauga(sters); 
	}
};

class UndoActualizeaza : public ActiuneUndo {
	Activitate activitateVeche;
	Activitate activitateNoua; 
	Repo& rep;
public:
	UndoActualizeaza(Repo& r, const Activitate& v, const Activitate& n)
		: rep{ r }, activitateVeche{ v }, activitateNoua{ n } {
	}

	void doUndo() override {
		rep.actualizeaza(activitateNoua, activitateVeche);
	}
};