#pragma once
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlayout.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qlineedit.h>
#include <QTableWidget>


#include "service.h"


class elevGUI : public QWidget {
private:
	Service& serv;

	//QHBoxLayout* lyMain = new QHBoxLayout{this};

	QListWidget* lista = new QListWidget{this};
	QPushButton* btnSort = new QPushButton{"&Sortare Nume"};
	QLineEdit* act = new QLineEdit{this};
	//QVBoxLayout* lyRight = new QVBoxLayout;

	//pt cerinta 4
	QTableWidget* tabel = new QTableWidget{this};
	QPushButton* btn1 = new QPushButton{"&desen+pictura"};
	QPushButton* btn2 = new QPushButton{ "&informatica" };
	QPushButton* btn3 = new QPushButton{ "&muzica" };
	QPushButton* btn4 = new QPushButton{ "&forografie" };
	QPushButton* btn5 = new QPushButton{ "&jurnalism" };




	void initGUI();
	void initConnect();
	void loadData();
	void populeazaTabela(string atelier);
public:
	elevGUI(Service& s) : serv{ s } {
		initGUI();
		loadData();
		initConnect();
	}
	
};