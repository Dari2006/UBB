#include "EelevGUI.h"

void elevGUI::initGUI() {

QHBoxLayout* lyMain = new QHBoxLayout{ this };
QVBoxLayout* lyRight = new QVBoxLayout{this};
QVBoxLayout* lyAteliere = new QVBoxLayout{this};


	lyMain->addWidget(lista);
	lyRight->addWidget(act);
	lyRight->addWidget(btnSort);
	lyMain->addLayout(lyRight);

	lyAteliere->addWidget(btn1);
	lyAteliere->addWidget(btn2);
	lyAteliere->addWidget(btn3);
	lyAteliere->addWidget(btn4);
	lyAteliere->addWidget(btn5);

	lyMain->addLayout(lyAteliere);



	lyMain->addWidget(tabel);
}

void elevGUI::loadData() {
	serv.loadFromFile();
	lista->clear();
	auto toate = serv.getAll();
	for (const auto& el : toate) {
		string linie = el.getNume() + " - " + el.getScoala();
		lista->addItem(QString::fromStdString(linie));
	}
}

void elevGUI::initConnect() {
	QObject::connect(lista, &QListWidget::itemSelectionChanged, [&](){
		auto index = lista->currentRow();
		const auto& toate = serv.getAll();
		const auto& elev = toate[index];
		const auto& activitati = elev.getActiv();
		string text = "";
		for(const auto& a : activitati) {
			text += a;
			text += " ";
		}

		act->setText(QString::fromStdString(text));
	});

	QObject::connect(btnSort, &QPushButton::clicked, [&](){
		lista->clear();
		const auto& toate = serv.sortNume();
		for (const auto& e : toate) {
			string text = "";
			text = e.getNume() + " - " + e.getScoala();
			lista->addItem(QString::fromStdString(text));
		}
	});

	QObject::connect(btn1, &QPushButton::clicked, [&](){
		populeazaTabela("desen+pictura");
	});

}

void elevGUI::populeazaTabela(string atelier) {
tabel->clear();
	const auto& toate = serv.getAll();
	vector<Elev> filtrat;
	for (const auto& e : toate) {
		for (const auto& a : e.getActiv())
		{
			if(atelier == a)
				filtrat.push_back(e);
				break;
		}
	}
	int nr = filtrat.size()+1;
	tabel->setRowCount(nr);
	tabel->setColumnCount(3);
	int row = 0;
	tabel->setItem(row, 0, new QTableWidgetItem(QString::fromStdString("nume")));
	tabel->setItem(row, 1, new QTableWidgetItem(QString::fromStdString("scoala")));
	tabel->setItem(row, 2, new QTableWidgetItem(QString::fromStdString("nr Matricol")));

	for (const auto& e : filtrat) {
		row++;
		tabel->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(e.getNume())));
		tabel->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(e.getScoala())));
		tabel->setItem(row, 2, new QTableWidgetItem(QString::number(e.getNrMatricol())));

	}
}

