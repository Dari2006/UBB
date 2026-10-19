#include "melodieGUI.h"

void melodieGUI::initGUI() {
	QHBoxLayout* lyMain = new QHBoxLayout{this};

	lyMain->addWidget(tbl);
}

void melodieGUI::loadData() {
	tbl->setColumnCount(4);
	const auto toate = s.getAll();
	tbl->setRowCount(toate.size() + 1);
	tbl->setItem(0, 0, new QTableWidgetItem( QString::fromStdString("id")));
	tbl->setItem(0, 1, new QTableWidgetItem(QString::fromStdString("titlu")));
	tbl->setItem(0, 2, new QTableWidgetItem(QString::fromStdString("artist")));
	tbl->setItem(0, 3, new QTableWidgetItem(QString::fromStdString("rank")));
	int i = 1;
	for (auto p : toate) {
		tbl->setItem(i, 0, new QTableWidgetItem(QString::number(p.getId())));
		tbl->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(p.getTitlu())));
		tbl->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(p.getArtist())));
		tbl->setItem(i, 3, new QTableWidgetItem(QString::number(p.getRank())));
		i++;
	}
}

void melodieGUI::connect() {

}