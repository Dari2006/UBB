#include "gui.h"


void gui::initgui() {
	QHBoxLayout* lyMain = new QHBoxLayout{this};
	lyMain->addWidget(tbl);
	QVBoxLayout* lyRight = new QVBoxLayout{this};
	lyRight->addWidget(l1);
	lyRight->addWidget(l2);
	lyRight->addWidget(l3);
	lyRight->addWidget(l4);
	lyRight->addWidget(btnAdd);
	lyMain->addLayout(lyRight);
	QVBoxLayout* ly3 = new QVBoxLayout{this};

	ly3->addWidget(l5);
	ly3->addWidget(btnFiltr);

	lyMain->addLayout(ly3);
}



void gui::loadData() {
tbl->clear();
	const auto& toate = s.getAll();
	tbl->setColumnCount(4);
	tbl->setRowCount(toate.size() + 1);
	tbl->setItem(0, 0, new QTableWidgetItem(QString::fromStdString("id")));
	tbl->setItem(0, 1, new QTableWidgetItem(QString::fromStdString("descriere")));
	tbl->setItem(0, 2, new QTableWidgetItem(QString::fromStdString("nr. programatori")));
	tbl->setItem(0, 3, new QTableWidgetItem(QString::fromStdString("stare")));
	int i{1};
	for (const auto& t : toate) {
	
		tbl->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(std::to_string(t.getId()))));
		tbl->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(t.getDescriere())));
		tbl->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(std::to_string(t.getProgramatori().size()))));
		tbl->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(t.getStare())));

		++i;
	}
}


void gui::initconnect() {
	QObject::connect(btnAdd, &QPushButton::clicked, [&](){
		string nr = l1->text().toStdString();
		int id = stoi(nr);

		string descr = l2->text().toStdString();

		string linie = l3->text().toStdString();
		std::stringstream ss(linie);

		vector<string> pro;
		string p;
		while (ss >> p) {
			pro.push_back(p);
		}

		string stare = l4->text().toStdString();

		const auto& toate = s.getAll();
		auto it = std::find_if(toate.begin(), toate.end(), [&id](const Task& a){return a.getId() == id;});
		int ok{1};
		if (it != toate.end()) {
			ok = 0;
			QMessageBox::warning(this, "eroare", "id-ul exista deja");
		}

		if (descr.empty()) {
			ok = 0;
			QMessageBox::warning(this, "eroare", "descriere vida");

		}
		if (pro.size() < 1 || pro.size() > 4) {
			ok = 0;
			QMessageBox::warning(this, "eroare", "prea multi/putini programatori");

		}

		if (stare != "open" && stare != "closed" && stare != "inprogress") {
			ok = 0;
			QMessageBox::warning(this, "eroare", "stare invalida");

		}

		if (ok) {

s.add(id, descr, pro, stare);
		loadData();
	

		}
		
	});

	QObject::connect(l5, &QLineEdit::textChanged, [&]{
		string text = l5->text().toStdString();
		if (text.empty()) {
			loadData();
		}
		else {
			vector<Task> gasiti;
			const auto& toate = s.getAll();
			for (const auto& t : toate) {
				const auto& p = t.getProgramatori();
				auto it = std::find_if(p.begin(), p.end(), [&text](const string& a){return a == text;});
				if (it != p.end()) {
					gasiti.push_back(t);
					
				}
			}


			tbl->clear();

			tbl->setColumnCount(4);
			tbl->setRowCount(gasiti.size() + 1);
			tbl->setItem(0, 0, new QTableWidgetItem(QString::fromStdString("id")));
			tbl->setItem(0, 1, new QTableWidgetItem(QString::fromStdString("descriere")));
			tbl->setItem(0, 2, new QTableWidgetItem(QString::fromStdString("nr. programatori")));
			tbl->setItem(0, 3, new QTableWidgetItem(QString::fromStdString("stare")));
			int i{ 1 };
			for (const auto& t : gasiti) {

				tbl->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(std::to_string(t.getId()))));
				tbl->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(t.getDescriere())));
				tbl->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(std::to_string(t.getProgramatori().size()))));
				tbl->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(t.getStare())));

				++i;
			}
		}
	
	});
}