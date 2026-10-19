#include <assert.h>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <iterator>
#include "Activitate.h"
#include "teste.h"
#include "Repo.h"
#include "Service.h"
using std::cout;
using std::vector;

void testActivitate() {
	/*testam constructor activitate*/
	Activitate a{"a", "b", "c", 2.5};

	assert(a.getTitlu() == "a");
	assert(a.getDescriere() == "b");
	assert(a.getTip() == "c");
	assert(a.getDurata() == 2.5);

	cout<<("test activitate da\n");
}


void testRepo() {
	Repo r;
	Activitate a{"a", "b", "c", 2.5};
	r.adauga(a);  //ar trebui sa mearga

	try {
		r.adauga(a);assert(false);  //daca reuseste nu e bine pentru ca "a" exista deja 
	}
	catch (RepoException) {
		assert(true);  //daca arunca exceptie e bine
	}

	const vector<Activitate> ac = r.getAll();
	assert(ac.size() == 1);    //ar trebui sa avem o singura instanta

	/*urmeaza sa testam stergerea*/
	//avem o singura activitate, mai adaugam doua
	Activitate b{ "b", "c", "d", 2.5 };
	r.adauga(b);
	Activitate c{ "c", "d", "e", 2.5 };
	r.adauga(c);
	//stergem a doua activitate
	try {
		r.sterge(b);assert(true); } catch (RepoException e) {  /*teoretic nu ajungem aici*/ assert(false);}
	const vector<Activitate> rez = r.getAll();
	assert(rez.size() == 2); //am sters o activitate din 3

	//incercam sa stergem o activitate care nu exista
	Activitate d{ "f", "g", "h", 2.5 };
	try {
		r.sterge(d);assert(false);
	}
	catch (RepoException e) {
		assert(true);
	}
	/*testam actualizarea*/
	Activitate e{"d", "d", "d", 67};
	try {
		r.actualizeaza(e, a);   //prima data testam cazul in care act veche nu exista
		assert(false);    //d inca nu e in vector, deci nu ar trebui sa reuseasca
	}
	catch (RepoException er) {
		assert(true); 
	}
	try {r.actualizeaza(a, e);assert(true);}catch (RepoException er) {assert(false);}

	cout << ("test repo ok\n");
}

void testValidator() {
	Validator val;

	/*definim parametri valizi si invalizi*/
	string titlu1 = "";
	string descriere1 = "";
	string tip1 = "";
	constexpr double durata1 = 0;

	string titlu2 = "a";
	string descriere2 = "a";
	string tip2 = "a";
	constexpr double durata2= 2.5;

	/*titlu invalid*/
	try {
		val.valideaza(titlu1, descriere2, tip2, durata2);	assert(false);
	}
	catch (ValidatorException) {
		assert(true);
	}
	/*descriere invalida*/
	try {
		val.valideaza(titlu2, descriere1, tip2, durata2);assert(false);
	}
	catch (ValidatorException) {
		assert(true);
	}
	/*tip invalid*/
	try {
		val.valideaza(titlu2, descriere2, tip1, durata2);assert(false);
	}
	catch (ValidatorException) {
		assert(true);
	}
	/*durata invalida*/
	try {
		val.valideaza(titlu2, descriere2, tip2, durata1);assert(false);
	}
	catch (ValidatorException) {
		assert(true);
	}
	/*activitate valida*/
	try {
		val.valideaza(titlu2, descriere2, tip2, durata2);assert(true);}catch (ValidatorException) {assert(false);}

	cout << ("validatorul valideaza\n");
}

void testValidatorException() {
	/*creeam 2 mesaje de eroare*/
	vector<string> erori = { "eroare1", "eroare2" };
	ValidatorException e(erori);
	const vector<string>& er = e.getErori();
	assert(er.size() == 2);
	assert(er[0] == "eroare1");
	assert(er[1] == "eroare2");

	cout << "test ValidatorException ok\n";
}

void testRepoException() {
	/*creeam un mesaj de eroare*/
	string er = "Eroare:(";
	RepoException r(er);
	assert(r.getMesaj() == "Eroare:(");

	cout<< "test RepoException ok\n";
}

void testLista() {
	// default construction
	Lista<int> l;
	assert(l.size() == 0);
	assert(l.empty());

	// add elements
	l.add(1);
	l.add(2);
	l.add(3);
	assert(l.size() == 3);
	assert(!l.empty());

	// non-const operator[] and modification
	l[0] = 10;
	assert(l[0] == 10);

	// const operator[]
	const Lista<int>& cl = l;
	assert(cl[1] == 2);
	assert(cl[2] == 3);

	// iteration using begin/end and summation
	int sum = 0;
	for (auto it = l.begin(); it != l.end(); ++it) {
		sum += *it;
	}
	assert(sum == (10 + 2 + 3));

	// copy constructor
	Lista<int> copy = l;
	assert(copy.size() == l.size());
	for (int i = 0; i < l.size(); ++i) {
		assert(copy[i] == l[i]);
	}

	// assignment operator
	Lista<int> assign;
	assign = l;
	assert(assign.size() == l.size());
	for (int i = 0; i < l.size(); ++i) {
		assert(assign[i] == l[i]);
	}

	// remove middle element (value 2)
	l.remove(2);
	assert(l.size() == 2);
	// remaining values should be 10 and 3 in that order
	assert(l[0] == 10);
	assert(l[1] == 3);

	// remove head (value 10)
	l.remove(10);
	assert(l.size() == 1);
	assert(l[0] == 3);

	// remove tail (value 3)
	l.remove(3);
	assert(l.size() == 0);
	assert(l.empty());

	// remove non-existing value -> no-op, size stays 0
	l.remove(42);
	assert(l.size() == 0);

	// verify const-empty overload on const reference
	const Lista<int>& clref = l;
	assert(clref.empty());

	cout << "test Lista ok\n";
}

void testService() {
	Repo r;
	Validator v;
	Service s(r, v);
	
	/*definim parametri valizi si invalizi*/
	string titlu1 = "";
	string descriere1 = "";
	string tip1 = "";
	constexpr double durata1 = 0;

	string titlu2 = "a";
	string descriere2 = "a";
	string tip2 = "a";
	constexpr double durata2 = 2.5;

	/*titlu invalid*/
	try {
		s.adauga(titlu1, descriere2, tip2, durata2);assert(false);
	}
	catch (ValidatorException) {assert(true);
	}
	/*descriere invalida*/
	try {
		s.adauga(titlu2, descriere1, tip2, durata2);assert(false);
	}
	catch (ValidatorException) {assert(true);
	}
	/*tip invalid*/
	try {
		s.adauga(titlu2, descriere2, tip1, durata2);assert(false);
	}
	catch (ValidatorException) {assert(true);
	}
	/*durata invalida*/
	try {
		s.adauga(titlu2, descriere2, tip2, durata1);assert(false);
	}
	catch (ValidatorException) {assert(true);
	}
	/*activitate valida*/
	try {
		s.adauga(titlu2, descriere2, tip2, durata2);assert(true);}catch (ValidatorException) {assert(false);}

	/*urmeaza sa testam stergerea*/
	string titlu3 = "b";
	string descriere3 = "b";
	string tip3 = "b";
	constexpr double durata3 = 2.5;
	string titlu4 = "c";
	string descriere4 = "c";
	string tip4 = "c";
	constexpr double durata4 = 2.5;
	s.adauga(titlu3, descriere3, tip3, durata3);
	s.adauga(titlu4, descriere4, tip4, durata4);
	//stergem activitatea "3"
	try {
		s.sterge(titlu3, descriere3, tip3, durata3);assert(true);}catch (ValidatorException v) {assert(false);}catch (RepoException r) {assert(false);}
	/*stergem o activitate care nu exista*/
	string titlu5 = "d";
	string descriere5 = "d";
	string tip5 = "d";
	constexpr double durata5 = 2.5;
	try {
		s.sterge(titlu5, descriere5, tip5, durata5); assert(false); }catch (ValidatorException v) { assert(false); }
	catch (RepoException r) {
		assert(true);
	}

	/*testam actualizarea*/
	try {
		s.actualizeaza(titlu5, descriere5, tip5, durata5, titlu4, descriere4, tip4, durata4); assert(false);}catch (RepoException) {assert(true);  /*repo ar trebui sa arunce exceptie pentru ca nu gaseste act 5*/ } catch (ValidatorException) { assert(false);  }
	try {
		s.actualizeaza(titlu4, descriere4, tip4, durata4, titlu5, descriere5, tip5, durata5);	assert(true);  /*act 4 exista */ } catch (RepoException) { assert(false); } catch (ValidatorException) { assert(false); }
	/*testam cautarea*/
	const string titlu{ "g" };
	
	string titlu6 = "g";
	string descriere6 = "d";
	string tip6 = "d";
	constexpr double durata6 = 2.5;
	string titlu7 = "g";
	string descriere7 = "b";
	string tip7 = "h";
	constexpr double durata7 = 12;

	s.adauga(titlu6, descriere6, tip6, durata6);
	s.adauga(titlu7, descriere7, tip7, durata7);

	const auto rezc = s.cauta(titlu);
	assert(rezc[0].getTitlu() == "g");

	/*testam filtrarea*/
	// Filtrare dupa tip:
	auto rezultate = s.filtrareGenerica("a", filtreazaDupaTip);
	assert(rezultate[0].getTip() == "a");

	// Filtrare dupa descriere:
	auto rezultate2 = s.filtrareGenerica("b", filtreazaDupaDescriere);
	assert(rezultate2[0].getDescriere() == "b");


	//dupa ceva ce nu avem
	auto rezultate3 = s.filtrareGenerica("sdfsdfsdf", filtreazaDupaDescriere);
	assert(rezultate3.empty());

	/*testam sortarea, facem service total nou*/
	{
		Repo rsort;
		Validator vsort;
		Service ssort(rsort, vsort);

		
		ssort.adauga("b", "b", "x", 2.0);
		ssort.adauga("a", "c", "y", 3.0);
		ssort.adauga("c", "a", "x", 1.0);
		ssort.adauga("d", "d", "z", 4.0);

		// titlu cresc
		auto st = ssort.sortTitluCresc();
		assert(st.size() == 4);
		assert(st[0].getTitlu() == "a");
		assert(st[1].getTitlu() == "b");
		assert(st[2].getTitlu() == "c");
		assert(st[3].getTitlu() == "d");

		// titlu descr
		auto st2 = ssort.sortTitluDescr();
		assert(st2.size() == 4);
		assert(st2[0].getTitlu() == "d");
		assert(st2[1].getTitlu() == "c");
		assert(st2[2].getTitlu() == "b");
		assert(st2[3].getTitlu() == "a");

		//descriere cresc
		auto sd = ssort.sortDescriereCresc();
		assert(sd.size() == 4);
		assert(sd[0].getDescriere() == "a");
		assert(sd[0].getTitlu() == "c");
		assert(sd[1].getDescriere() == "b");
		assert(sd[1].getTitlu() == "b");
		assert(sd[2].getDescriere() == "c");
		assert(sd[2].getTitlu() == "a");
		assert(sd[3].getDescriere() == "d");
		assert(sd[3].getTitlu() == "d");

		// descriere descr
		auto sd2 = ssort.sortDescriereDescr();
		assert(sd2.size() == 4);
		assert(sd2[0].getDescriere() == "d");
		assert(sd2[0].getTitlu() == "d");
		assert(sd2[1].getDescriere() == "c");
		assert(sd2[1].getTitlu() == "a");
		assert(sd2[2].getDescriere() == "b");
		assert(sd2[2].getTitlu() == "b");
		assert(sd2[3].getDescriere() == "a");
		assert(sd2[3].getTitlu() == "c");

		// tip+durata
		auto sttd = ssort.sortTipDurata();
		assert(sttd.size() == 4);
		assert(sttd[0].getTitlu() == "c");
		assert(sttd[1].getTitlu() == "b");
		assert(sttd[2].getTitlu() == "a");
		assert(sttd[3].getTitlu() == "d");
	}

	cout << "service ul face business\n";
}


void testPlanificare() {
	// Test Planificare directly
	Planificare p;
	assert(p.dim() == 0);

	Activitate a{ "t1", "d1", "x", 1.0 };
	Activitate b{ "t2", "d2", "y", 2.0 };
	p.adauga(a);
	p.adauga(b);
	assert(p.dim() == 2);

	const auto& toate = p.getToate();
	assert(toate.size() == 2);
	assert(toate[0].getTitlu() == "t1");
	assert(toate[1].getTitlu() == "t2");

	p.goleste();
	assert(p.dim() == 0);

	// Test Service-level plan operations
	Repo r;
	Validator v;
	Service s(r, v);

	// populate repo
	s.adauga("t1", "d1", "x", 1.0);
	s.adauga("t2", "d2", "y", 2.0);
	s.adauga("t3", "d3", "z", 3.0);
	s.adauga("t4", "d4", "w", 4.0);

	// plan initially empty
	assert(s.getPlan().dim() == 0);

	// add by title (existing)
	s.adauga_planificare("t2");
	assert(s.getPlan().dim() == 1);
	assert(s.getPlan().getToate()[0].getTitlu() == "t2");

	// add by title (non-existing) -> should not change plan
	try {
		s.adauga_planificare("noSuch");assert(false);
	}
	catch (ServiceException) {
		assert(true);
	}

	

	// generate random plan of size 2
	s.genereazaPlanRandom(2);
	size_t dim2 = s.getPlan().dim();
	assert(dim2 == 2);

	

	// request more than available -> plan size becomes repo.size()
	s.genereazaPlanRandom(100);
	assert(s.getPlan().dim() == (int)s.getAll().size());

	// clear plan via service helper
	s.golestePlan();
	assert(s.getPlan().dim() == 0);

	cout << "Ba Foca, am un plan: DELTAPLAAAAAN!!!\n";
}


void testPlanificareExports() {
	Repo r;
	Validator v;
	Service s(r, v);
	
	// populate repo and plan
	s.adauga("pt1", "pd1", "ptip1", 1.25);
	s.adauga("pt2", "pd2", "ptip2", 2.5);
	s.adauga_planificare("pt1");
	s.adauga_planificare("pt2");

	// test getToateDinPlan
	const auto& planVec = s.getToateDinPlan();
	assert(planVec.size() == 2);
	assert(planVec[0].getTitlu() == "pt1");
	assert(planVec[1].getTitlu() == "pt2");

	// test export CSV via service
	const std::string csvFile = "test_plan.csv";
	s.exportaPlanificareaCSV(csvFile);
	std::ifstream in(csvFile);
	assert(in.is_open());
	std::string line;
	std::getline(in, line);
	assert(line.find("pt1") != std::string::npos);
	assert(line.find("pd1") != std::string::npos);
	assert(line.find("ptip1") != std::string::npos);
	std::getline(in, line);
	assert(line.find("pt2") != std::string::npos);
	in.close();
	std::remove(csvFile.c_str());

	// test export HTML via service
	const std::string htmlFile = "test_plan.html";
	s.exportaPlanificareaHTML(htmlFile);
	std::ifstream inHtml(htmlFile);
	assert(inHtml.is_open());
	std::string htmlContent((std::istreambuf_iterator<char>(inHtml)), std::istreambuf_iterator<char>());
	assert(htmlContent.find("<html") != std::string::npos);
	assert(htmlContent.find("pt1") != std::string::npos);
	assert(htmlContent.find("pt2") != std::string::npos);
	inHtml.close();
	std::remove(htmlFile.c_str());

	// test Planificare export throws when target is a directory (existing x64 folder)
	try {
		s.getPlan().exportaCSV("x64");assert(false);
	} catch (const std::runtime_error&) {
		assert(true);
	}
	try {
		s.getPlan().exportaHTML("x64");assert(false);
	} catch (const std::runtime_error&) {
		assert(true);
	}
}

void testRaport() {
	// 1. Setup: Creăm un Repo și un Service
	Repo rep;
	Validator v;
	Service srv{ rep , v}; // Presupunem că Service primește Repo în constructor

	// 2. Adăugăm câteva activități cu tipuri diferite
	srv.adauga("Fotbal", "Meci", "Sport", 90);
	srv.adauga("Baschet", "Antrenament", "Sport", 60);
	srv.adauga("Analiza", "Curs", "Scoala", 120);

	// 3. Apelăm funcția de raport
	auto raport = srv.raportPeTipuri();

	// 4. Verificări (Assert-uri)

	// Verificăm dacă avem exact 2 tipuri în map (Sport și Scoala)
	assert(raport.size() == 2);

	// Verificăm dacă numărătoarea este corectă
	// În map, accesul se face direct prin cheie
	assert(raport["Sport"] == 2);
	assert(raport["Scoala"] == 1);

	// Verificăm un tip care NU există (ar trebui să returneze 0 sau să nu fie în map)
	assert(raport.find("Gatit") == raport.end());
}


void testServiceException() {
	ServiceException e("Eroare Service Test");
	assert(e.getMessage() == "Eroare Service Test");
	cout << "test ServiceException ok\n";
}

void testUndo() {
	
	Repo repo;
	Validator val;
	Service serv{ repo, val };

	serv.adauga("Titlu1", "Descr1", "Tip1", 10);
	assert(serv.getAll().size() == 1);
	serv.undo();
	assert(serv.getAll().size() == 0);

	serv.adauga("Titlu1", "Descr1", "Tip1", 10);
	serv.sterge("Titlu1", "Descr1", "Tip1", 10);
	assert(serv.getAll().size() == 0);
	serv.undo();
	assert(serv.getAll().size() == 1);
	assert(serv.getAll()[0].getTitlu() == "Titlu1");

	serv.actualizeaza("Titlu1", "Descr1", "Tip1", 10, "Titlu1", "Nou", "Nou", 20);
	assert(serv.getAll()[0].getDescriere() == "Nou");
	serv.undo();
	assert(serv.getAll()[0].getDescriere() == "Descr1");

	serv.undo(); 
}

void testCautaDupaAtribute() {
	// Setup: folosim Repo (pe vector) pentru a evita probabilitatea din RepoLab in teste
	Repo repo;
	Validator val;
	Service serv{ repo, val };

	serv.adauga("Fotbal", "meci in parc", "sport", 1.5);
	serv.adauga("Citit", "biblioteca", "relaxare", 2.0);

	// 1. Test pentru Succes (Match 100%)
	try {
		const auto& a = serv.cautaDupaAtribute("Fotbal", "meci in parc", "sport", 1.5);
		assert(a.getTitlu() == "Fotbal");
		assert(a.getDescriere() == "meci in parc");
		assert(a.getTip() == "sport");
		assert(abs(a.getDurata() - 1.5) < 0.0001);	}catch (...) {assert(false); 	}

	// 2. Test pentru Eșec (Titlu greșit)
	try {
		serv.cautaDupaAtribute("Baschet", "meci in parc", "sport", 1.5);	assert(false); // Nu ar trebui sa ajunga aici
	}
	catch (const RepoException& ex) {
		assert(ex.getMesaj() == "Activitatea nu a fost gasita cu aceste atribute!");
	}

	// 3. Test pentru Eșec (Durata diferită - verifică precizia double)
	try {
		serv.cautaDupaAtribute("Fotbal", "meci in parc", "sport", 1.5002);assert(false);
	}
	catch (const RepoException& ex) {	assert(ex.getMesaj() == "Activitatea nu a fost gasita cu aceste atribute!");
	}

	// 4. Test pentru Eșec (Descriere/Tip greșit)
	try {
		serv.cautaDupaAtribute("Fotbal", "altceva", "sport", 1.5);	assert(false);
	}
	catch (const RepoException& ex) {
		assert(ex.getMesaj() == "Activitatea nu a fost gasita cu aceste atribute!");
	}
}

void ruleazaTeste() {
	testActivitate();
	testRepo();
	testValidator();
	testRepoException();
	testValidatorException();
	testLista();
	testService();
	testPlanificare();
	testPlanificareExports();
	testServiceException();
	testRaport();
	testUndo();
	testCautaDupaAtribute();
}