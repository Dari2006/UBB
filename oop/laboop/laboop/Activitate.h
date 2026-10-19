#pragma once
#include <string>
using std::string;
#include <iostream>

class Activitate{
private:
	string titlu;  
	string descriere;
	string tip;
	double durata;
public:
	Activitate() = default;
	const string& getTitlu() const noexcept{
		return titlu;
	}
	const string& getDescriere() const noexcept{
		return descriere;
	}
	const string& getTip() const noexcept{
		return tip;
	}
	double getDurata() const noexcept{
		return durata;
	}

	/*constructori*/
	Activitate(const string& titlu, const string& descr, const string& tip, double durata): titlu{titlu},descriere{descr},tip{tip}, durata{durata}  {

	}
	Activitate(const Activitate& ot) : titlu{ ot.titlu }, descriere{ ot.descriere }, tip{ ot.tip }, durata{ ot.durata } {
		//std::cout<<"dfdfdfd\n";
	}
	/*override op ==*/
	bool operator==(const Activitate& ot) const;
};