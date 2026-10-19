#include "podcastGUI.h"
#include <exception>

void podcastGUI::initGUI() {
lastClicked = "default";
	QHBoxLayout* lyMain = new QHBoxLayout{this};

	lyMain->addWidget(lst);

	QVBoxLayout* lyRight = new QVBoxLayout{this};



	lyRight->addWidget(lineCod);
	lyRight->addWidget(lineCateg);

	lyMain->addLayout(lyRight);

	QVBoxLayout* lySort = new QVBoxLayout{this};
	lySort->addWidget(btnSortTitlu);
	lySort->addWidget(btnSortCreator);
	lySort->addWidget(btnSortDefault);
	lySort->addWidget(btnDescr);

	lyMain->addLayout(lySort);


}


void podcastGUI::loadData() {
	auto toate = s.getAll();
	for (auto& p : toate) {
		string text = p.getTitlu() + " - " + p.getCreator();
		lst->addItem(QString::fromStdString(text));
	}
}


void podcastGUI::reloadData(const vector<Podcast>& v) {
	lst->clear();

	for (auto p : v) {
		string text = p.getTitlu() + " - " + p.getCreator();
		lst->addItem(QString::fromStdString(text));
	}
}


void podcastGUI::initConnect() {
	QObject::connect(lst, &QListWidget::itemSelectionChanged, [&](){
		auto index = lst->currentRow();
		auto& toate = s.getAll();
		auto pod = toate[index];

		lineCod->setText(QString::fromStdString(pod.getCod()));
		lineCateg->setText(QString::fromStdString(pod.getCategorie()));
	});

	QObject::connect(btnSortDefault, &QPushButton::clicked, [&](){
		lst->clear();

		loadData();
		lastClicked = "default";
	});

	QObject::connect(btnSortTitlu, &QPushButton::clicked, [&](){
		//const auto& v = s.sortTitlu();
		//reloadData(toate);

		lst->clear();
		auto toate = s.getAllCopy();
		std::sort(toate.begin(), toate.end(), [](Podcast a, Podcast& b) {return a.getTitlu() < b.getTitlu();});
		for (auto p : toate) {
			string text = p.getTitlu() + " - " + p.getCreator();
			lst->addItem(QString::fromStdString(text));
		}
		lastClicked = "titlu";
	});

	QObject::connect(btnSortCreator, &QPushButton::clicked, [&](){
		lst->clear();
		auto toate = s.getAllCopy();
		std::sort(toate.begin(), toate.end(), [](Podcast a, Podcast& b) {return a.getCreator() < b.getCreator();});
		for (auto p : toate) {
			string text = p.getTitlu() + " - " + p.getCreator();
			lst->addItem(QString::fromStdString(text));
		}
		lastClicked = "creat";
	});

	QObject::connect(btnDescr, &QPushButton::clicked, [&](){
		try{
		auto index = lst->currentRow();

		if (lastClicked == "default") {
			auto toate = s.getAll();
			auto p = toate[index];
			string descr = p.getDescriere();
			QMessageBox::information(this, "Descriere", QString::fromStdString(descr));
		}
		else if (lastClicked == "titlu") {
			auto toate = s.getAllCopy();
			std::sort(toate.begin(), toate.end(), [](Podcast a, Podcast& b) {return a.getTitlu() < b.getTitlu();});
			auto p = toate[index];
			string descr = p.getDescriere();
			QMessageBox::information(this, "Descriere", QString::fromStdString(descr));
		}
		else if (lastClicked == "creat") {
			auto toate = s.getAllCopy();
			std::sort(toate.begin(), toate.end(), [](Podcast a, Podcast& b) {return a.getCreator() < b.getCreator();});
			auto p = toate[index];
			string descr = p.getDescriere();
			QMessageBox::information(this, "Descriere", QString::fromStdString(descr));
		}
		}
		catch (std::exception& e) {
			QMessageBox::warning(this, "Eroare", "Nu a-ti selectat un podcast");
		}
	
	});
}