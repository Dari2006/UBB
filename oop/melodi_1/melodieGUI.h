#pragma once
#include "service.h"
#include <qwidget.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <qtablewidget.h>
#include "tablemodel.h"
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qslider.h>
#include <qmessagebox.h>
#include "desen.h"
class melodieGUI : public QWidget {
private:
	Service& s;

	QTableWidget* tbl = new QTableWidget{this};
	QTableView* tblv = new QTableView{this};
	TableModel* model;

	//pt cerinta a treia
	QLineEdit* line = new QLineEdit;
	QSlider* sld = new QSlider{};
	QPushButton* btn = new QPushButton{"update"};
	//pt cerinta 4
	QPushButton* btnDel = new QPushButton{"delete"};

	//cerinta 5
	Desen* d = new Desen{s};
	void initGUI();
	void loadData();
	void initconnect();
public:
	melodieGUI(Service& serv) : s{ serv } {
		model = new TableModel{s};
		initGUI();
		loadData();
		initconnect();
	}
};