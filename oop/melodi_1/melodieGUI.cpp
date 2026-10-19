#include "melodieGUI.h"

void melodieGUI::initGUI() {
	QHBoxLayout* lyMain = new QHBoxLayout{this};
	lyMain->addWidget(tblv);

	tblv->setModel(model);
	auto lyRight = new QVBoxLayout{this};
	lyRight->addWidget(line);
	lyMain->addWidget(sld);
	sld->setTickInterval(1);
	sld->setMinimum(0);
	sld->setMaximum(10);
	lyMain->addLayout(lyRight);
	lyRight->addWidget(btn);
	lyRight->addWidget(btnDel);


	lyRight->addWidget(d);
	

	//lyMain->addWidget(tblv);
	//lyMain->addWidget(tbl);
} 


void melodieGUI::loadData() {
	const auto& toate = s.getAll();
	tbl->setColumnCount(4);
	tbl->setRowCount(toate.size() + 1);
	tbl->setItem(0, 0, new QTableWidgetItem(QString::fromStdString("id")));
	tbl->setItem(0, 1, new QTableWidgetItem(QString::fromStdString("titlu")));
	tbl->setItem(0, 2, new QTableWidgetItem(QString::fromStdString("artist")));
	tbl->setItem(0, 3, new QTableWidgetItem(QString::fromStdString("rank")));
	int i{1};
	for (const auto& m : toate) {
		tbl->setItem(i, 0, new QTableWidgetItem(QString::number(m.getId())));
		tbl->setItem(i, 3, new QTableWidgetItem(QString::number(m.getRank())));
		tbl->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(m.getTitlu())));
		tbl->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(m.getArtist())));

		++i;
	}
}

void melodieGUI::initconnect() {
	QObject::connect(tblv, &QTableView::clicked, this, [&]{
	
	const auto& toate = s.getAll();
	const auto& mel = toate[tblv->currentIndex().row()];
	line->setText(QString::fromStdString(mel.getTitlu()));
	});

	QObject::connect(sld, &QSlider::valueChanged, this, [&] {
		//auto i = sld->value();
		//auto& toate = s.getall();
		//auto& mel = toate[tblv->currentIndex().row()];
		//mel.setRank(i);
		

	});

	QObject::connect(btn, &QPushButton::clicked, this, [&]{
		int i = sld->value();
		const auto& text = line->text();
		const auto& t = text.toStdString();
		auto& toate = s.getall();
		auto it = std::find_if(toate.begin(), toate.end(), [&text](const Melodie& a){return a.getTitlu() == text;});
		auto& mel = toate[tblv->currentIndex().row()];
		if (it == toate.end()) {	
				mel.setTitlu(t);
		}
		mel.setRank(i);
		s.save();
		d->update();
	});

	QObject::connect(btnDel, &QPushButton::clicked, [&](){
		const auto& text = line->text();
		const auto& titlu = text.toStdString();
		try {
			s.sterge(titlu);
			s.save();
			d->update();
		}
		catch (std::runtime_error& e) {
			QMessageBox::warning(this, "eroare", QString::fromStdString("eroare"));
		}

		
	});
}