#include "rochieGUI.h"
#include <qmessagebox.h>

void rochieGUI::initGUI() {
	QHBoxLayout* lyMain = new QHBoxLayout{this};

	QVBoxLayout* lyRight = new QVBoxLayout{this};
	//lyMain->addSpacing(2000);
	lst->resize(200, 400);
	lyMain->addWidget(lst);
	//lyMain->addWidget(btnInchiriere);
	lyRight->addWidget(btnInchiriere);
	lyMain->addLayout(lyRight);

}

void rochieGUI::loadData() {
	const auto& toate = s.getAll();
	string linie;
	for (auto p : toate) {
		linie.clear();
		linie+= p.getDenumire();
		linie+= "|";
		linie+= p.getMarime();
		linie += "|";
		linie+= std::to_string(p.getPret());
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(linie));
		if (p.getDisponibilitate() == true) {
			item->setBackground(QColor(Qt::green));
		}
		else {
			item->setBackground(QColor(Qt::red));
		}
		lst->addItem(item);
	}
}

void rochieGUI::connect() {
	

	QObject::connect(btnInchiriere, &QPushButton::clicked, [&](){
		auto p = lst->currentRow();
		const auto toate = s.getAll();
		auto rochie = toate[p];
		if (rochie.getDisponibilitate() == false) {
			QMessageBox::warning(this, "Eroare", "Rochia nu e valabila");
		}
		else {
			QListWidgetItem* item = lst->currentItem();
			item->setBackground(QColor(Qt::red));
			rochie.setDisponibilitate(false);
		}
	});
}