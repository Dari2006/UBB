#include "ui.h"
#include <iostream>
#include <limits>
using std::endl;
using std::cin;
using std::cout;
using std::string;
using std::ws;

void UI::adaugaUI() {
	cout << "Introduceti titlul: ";
	string titlu;
	getline(cin >> ws, titlu);  //ws = whitespace, adica scapam de TAB-uri si SPACE-uri
	
	cout << "Introduceti descrierea: ";
	string descriere;
	getline(cin >> ws, descriere);

	cout << "Introduceti tipul: ";
	string tip;
	getline(cin >> ws, tip);

	cout << "Introduceti durata: ";
	double durata;
	cin >> durata;
	while (1) {
		if (cin.fail()) {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Durata trebuie sa fie un numar\nIntroduceti durata: ";
			cin >> durata;
		}
		else {
			break;
		}
	}
	cin.ignore(10000, '\n');

	try {
		s.adauga(titlu, descriere, tip, durata);
		cout << "Activitate adaugata cu succes\n\n";
	}
	catch (const ValidatorException& e) {
		const vector<string> erori = e.getErori();
		for(auto msg : erori)
			cout << msg;
	}
	catch (const RepoException& e) {
		const string m = e.getMesaj();
		cout << m << "\n";
	}

}

void UI::stergeUI() {
	string descriere;
	cout << "Introduceti descrierea: ";
	getline(cin >> ws, descriere);

	string titlu;
	cout << "Introduceti titlul: ";
	getline(cin >> ws, titlu);

	string tip;
	cout << "Introduceti tipul: ";
	getline(cin >> ws, tip);

	double durata;
	cout << "Introduceti durata: ";
	while (1) {
		if (!(cin >> durata)) {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Durata trebuie sa fie un numar\n";
		}
		else {
			break;
		}
	}
	try {
		s.sterge(descriere, titlu, tip, durata);
		cout << "Activitatea a fost stearsa cu succes!\n";
	}
	catch (const ValidatorException& v) {
		vector<string> erori = v.getErori();
		for (auto& e : erori) {
			cout << e << "\n";
		}
	}
	catch (const RepoException& e) {
		string er = e.getMesaj();
		cout << er << '/n';
	}
	
}

void UI::actualizeazaUI() {
	//prima data citim parametrii activitatii pe care vrem sa o inlocuim
	string descrierev;
	cout << "Introduceti descrierea: ";
	getline(cin >> ws, descrierev);

	string titluv;
	cout << "Introduceti titlul: ";
	getline(cin >> ws, titluv);

	string tipv;
	cout << "Introduceti tipul: ";
	getline(cin >> ws, tipv);

	double duratav;
	cout << "Introduceti durata: ";
	while (1) {
		if (!(cin >> duratav)) {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Durata trebuie sa fie un numar\n";
		}
		else {
			break;
		}
	}
	//citim parametrii activitaii noi
	string descrieren;
	cout << "Introduceti descrierea: ";
	getline(cin >> ws, descrieren);

	string titlun;
	cout << "Introduceti titlul: ";
	getline(cin >> ws, titlun);

	string tipn;
	cout << "Introduceti tipul: ";
	getline(cin >> ws, tipn);

	double duratan;
	cout << "Introduceti durata: ";
	while (1) {
		if (!(cin >> duratan)) {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Durata trebuie sa fie un numar\n";
		}
		else {
			break;
		}
	}
	try {
		s.actualizeaza(titluv, descrierev, tipv, duratav, titlun, descrieren, tipn, duratan);
	}
	catch (ValidatorException v) {
		vector<string> erori = v.getErori();
		for (auto er : erori) {
			cout<< er << "\n";
		}
	}
	catch (RepoException r) {
		cout << r.getMesaj() << "\n";
	}
	
}

void UI::printAll() {
	const vector<Activitate> &list{s.getAll()};
	int i{1};
	try{
	for (const auto &p : list) {
		cout<< i++ << "." << p.getTitlu() << " " << p.getDescriere() << " " << p.getTip() << " " <<
			p.getDurata() << "\n";
	}
	}
	catch (const RepoException& e) {
		const string m = e.getMesaj();
		cout << m << "\n";
	}
}

void UI::filtrareUI() {
	string criteriu{ };
	while (true) {
		cout << "Filtrare dupa (descriere/tip): ";
		getline(cin >> ws, criteriu);
		if (criteriu == "descriere" || criteriu == "tip") break;
		cout << "Optiune invalida!\n";
	}
	cout<<"\n";
	vector<Activitate> rez{ };
	string param{ };
	if (criteriu== "descriere") {
		cout << "Introduceti descrierea: ";
		getline(cin >> ws, param);
		rez = s.filtrareGenerica(param, filtreazaDupaDescriere);
	}
	else {
		cout << "Introduceti tipul: ";
		getline(cin >> ws, param);
		rez = s.filtrareGenerica(param, filtreazaDupaTip);
	}
	if (rez.empty()) {
		cout << "Nu au fost gasite activitati\n";
	}
	else {
		int i{ 1 };
		cout<< "Activitati gasite:\n";
		for (const auto& p : rez) {
			cout << i++ << "." << p.getTitlu() << " " << p.getDescriere() << " " << p.getTip() << " " <<
				p.getDurata() << "\n";
		}
	}
}

void UI::cautaUI() {
	string titlu{ };
	cout << "Introduceti titlul: ";
	getline(cin >> ws, titlu);
	cout << "\n";
	const vector<Activitate> rez = s.cauta(titlu);
	if (rez.empty()) {
		cout << "Nu au fost gasite activitati\n";
	}
	else {
		int i{ 1 };
		cout << "Activitati gasite:\n";
		for (const auto& p : rez) {
			cout << i++ << "." << p.getTitlu() << " " << p.getDescriere() << " " << p.getTip() << " " <<
				p.getDurata() << "\n";	
		}
	}
}

void UI::sortareUI() {
	int criteriu{ };
	cout << "Sortare dupa (1 - titlu/2 - descriere/3 - tip+durata): ";
	while (criteriu != 1 && criteriu != 2 && criteriu != 3) {
		cin >> criteriu;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(10000, '\n');
		}
		if(criteriu != 1 && criteriu != 2 && criteriu != 3)
			cout << "Criteriu invalid\n";
	}
	cout << "\n";
	int a{-1};
	vector<Activitate> rez{ };
	if (criteriu == 1 || criteriu == 2) {
		cout << "Sortare(1 - crescator/2 - descrescator): ";
		while (a != 1 && a != 2) {
			cin >> a;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(10000, '\n');
			}
			if (a != 1 && a != 2)
				cout << "invalid\n";
		}
	}
	if (criteriu == 1) {
		if (a == 1) {
			rez = s.sortTitluCresc();
		}
		else {
			rez = s.sortTitluDescr();
		}
	}
	else if (criteriu == 2) {
		if (a == 1) {
			rez = s.sortDescriereCresc();
		}
		else {
			rez = s.sortDescriereDescr();
		}
	}
	else {
		rez = s.sortTipDurata();
	}
	int i{ 1 };
	cout << "\n";
	for (const auto& p : rez) {
		cout << i++ << "." << p.getTitlu() << " " << p.getDescriere() << " " << p.getTip() << " " <<
			p.getDurata() << "\n";
	}
	
}

void UI::uiAdaugaInPlan() {
	string titlu;
	cout << "Introdu titlul activitatii: ";
	cin >> titlu;
	try {
		s.adauga_planificare(titlu);
		cout << "Activitate adaugata cu succes!" << endl;
	}
	catch (const ServiceException &e) {
		cout << e.getMessage() << endl;
	}
	cout << "In plan sunt acum: " << s.dimPLan() << " activitati." << endl;
}

void UI::uiGenereazaPlan() {
	int nr;
	cout << "Cate activitati vrei in plan? ";
	if (!(cin >> nr)) {
		cout << "Te rog introdu un numar valid!" << endl;
		cin.clear();
		cin.ignore(1000, '\n');
		return;
	}
	try {
		s.genereazaPlanRandom(nr);
		cout << "Plan generat cu succes!" << endl;
	}
	catch (const ServiceException& e) {
		cout << "Eroare: " << e.getMessage() << endl;
	}
	cout << "In plan sunt acum: " << s.dimPLan() << " activitati." << endl;
}

void UI::uiGolestePlan() {
	s.golestePlan();

	cout << "Lista de activitati a fost golita cu succes!" << endl;
	cout << "In plan sunt acum: " << s.dimPLan() << " activitati." << endl;
}

void UI::uiExport() {
	cout << "Alege formatul exportului:\n";
	cout << "1. CSV\n";
	cout << "2. HTML\n";
	int optiune;
	cin >> optiune;

	string numeFisier;
	cout << "Introdu numele fisierului: ";
	cin >> numeFisier;

	try {
		if (optiune == 1) {
			s.exportaPlanificareaCSV(numeFisier + ".csv");
			cout << "Export CSV realizat cu succes!\n";
		}
		else if (optiune == 2) {
			s.exportaPlanificareaHTML(numeFisier + ".html");
			cout << "Export HTML realizat cu succes!\n";
		}
		else {
			cout << "Optiune invalida!\n";
		}
	}
	catch (const std::runtime_error& e) {
		cout << "Eroare la scrierea fisierului: " << e.what() << endl;
	}

	cout << "In plan sunt acum: " << s.dimPLan() << " activitati.\n";
}

void UI::uiAfiseazaPlan() {
	const auto& listaPlan = s.getToateDinPlan();

	if (listaPlan.empty()) {
		cout << "Planul de activitati este gol!" << endl;
	}
	else {
		for (const auto& a : listaPlan) {
			cout << " " << a.getTitlu() << " " << a.getDescriere()
				<< " " << a.getTip() << " " << a.getDurata() << endl;
		}
	}

	cout << "In plan sunt acum: " << s.dimPLan() << " activitati." << endl;
}

void UI::uiRaport() {
	auto raport = s.raportPeTipuri();

	cout << "--- RAPORT ACTIVITATI ---" << endl;

	for (const auto& x : raport) {
		cout << "Tipul [" << x.first << "] are " << x.second << " activitati." << endl;
	}
}

void UI::uiUndo() {
	try {
		s.undo();
		cout << "Undo realizat cu succes!" << endl;
	}
	catch (const ServiceException& ex) {
		cout << ex.getMessage() << endl;
	}
}

void UI::run() {
	while (true) {
		cout << "--- MENIU ---\n" << "1. adauga activitate\n2. sterge activitate\n3.actualizeaza activitate\n"
		<< "4.afiseaza toate activitatile\n5.filtreaza dupa tip sau descriere\n6.sortare\n0. exit\n";
		cout << "--- PLANIFICARE ---" << endl;
		cout << "7. Goleste planul" << endl;
		cout << "8. Adauga in plan (dupa titlu)" << endl;
		cout << "9. Genereaza plan aleator" << endl;
		cout << "10. Afiseaza planul curent" << endl;
		cout << "11. Exporta planul in format html sau csv" << endl;
		cout << "12. Afiseaza raport dupa tip" << endl;
		cout << "13. Undo" << endl;
		int cmd{ -1 };
		cout << "Introduceti comanda: ";
		cin >> cmd;
		cout<< "\n";
		if (cmd == 0) {
			cout << "zi fain varule";
			break;
		}
		else if (cmd == 1) {
			adaugaUI();
		}
		else if (cmd == 2) {
			stergeUI();
		}
		else if (cmd == 3) {
			actualizeazaUI();
		}
		else if (cmd == 4) {
			printAll();
		}
		else if (cmd == 5) {
			filtrareUI();
		}
		else if (cmd == 6) {
			sortareUI();
		}
		else if (cmd == 7) {
			uiGolestePlan();
		}
		else if (cmd == 8) {
			uiAdaugaInPlan();
		}
		else if (cmd == 9) {
			uiGenereazaPlan();
		}
		else if (cmd == 10) {
			uiAfiseazaPlan();
		}
		else if (cmd == 11) {
			uiExport();
		}
		else if (cmd == 12) {
			uiRaport();
		}
		else if (cmd == 13) {
			uiUndo();
		}
		else {
			cout << "Comanda nu e vaild!\n";
		}
	}
}