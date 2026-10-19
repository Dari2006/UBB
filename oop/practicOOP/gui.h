#pragma once
#include <QWidget>
#include "Service.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <qtablewidget.h>
#include <qpushbutton.h>
#include <QLineEdit.h>
#include <QMessageBox>	
class gui: public QWidget{
private:
	Service& s;

	//pt cerinta 1
	QTableWidget* tbl = new QTableWidget;

	//pt cerinta 2
	QLineEdit* l1 = new QLineEdit;
	QLineEdit* l2 = new QLineEdit;
	QLineEdit* l3 = new QLineEdit;
	QLineEdit* l4 = new QLineEdit;
	QPushButton* btnAdd = new QPushButton{"Adauga"};

	//pt cerinta 3
	QPushButton* btnFiltr = new QPushButton{"Cauta"};
	QLineEdit* l5 = new QLineEdit;


	void initgui();
	void initconnect();
	void loadData();
public:
	gui(Service& serv) : s{ serv } {
		initgui();
		loadData();
		initconnect();
	}
};

