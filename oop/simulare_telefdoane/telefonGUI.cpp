#include "telefonGUI.h"


void telefonGUI::initGUI() {
	QHBoxLayout* lyMain = new QHBoxLayout{this};

	box->addItem("toate");
	for (const auto& cat : categorii)
	{
		box->addItem(QString::fromStdString(cat));
	}


	lyMain->addWidget(lst);
	lyMain->addWidget(box);
	lyMain->addWidget(linie);

}


void telefonGUI::loadData() {
	auto toate = s.getAll();
	for (auto& tel : toate) {
		categorii.insert(tel.getCategorie());
		QListWidgetItem* item = new QListWidgetItem;
		string den = tel.getDenumire();
		int nr = tel.getAn();
		string an = std::to_string(nr);
		string text = den + "(" + an + ")";
		//QListWidgetItem* item = new QListWidgetItem;
		item->setText(QString::fromStdString(text));
		if (tel.getAn() > 2020) {
			item->setBackground(QColor(Qt::green));
		}
		lst->addItem(item);
	}
}


void telefonGUI::connect() {
	QObject::connect(box, &QComboBox::currentTextChanged, [&](){
		string text = box->currentText().toStdString();
		lst->clear();
		if (text == "toate") {
			loadData();
		}
		else {
			auto it = std::find_if(categorii.begin(), categorii.end(), [text](const auto& cat){return text == cat;});
			if (it != categorii.end()) {
				const auto& toate = s.filtrare(text);
				//reloadData(toate);
				const auto& toat = s.getAll();
				vector<Telefon> filtr;
				for (auto tel : toat) {
					if (tel.getCategorie() == text) {
						filtr.push_back(tel);
						lst->addItem(QString::fromStdString(tel.getDenumire()));
					}
				}
			}
		}
	});


	QObject::connect(linie, &QLineEdit::textChanged, [&](){
		lst->clear();
		string txt = linie->text().toStdString();
		const auto& toate = s.getAll();
		for (auto tel : toate) {
			const auto& nume = tel.getDenumire();
			if (nume.find(txt) != string::npos) {
				lst->addItem(QString::fromStdString(tel.getDenumire()));
			}

		}
	});
}

void telefonGUI::reloadData(const vector<Telefon>& v) {
	//lst->clear();
	lst->addItem(QString::number(v.size()));

	for (auto tel : v) {
		string text = tel.getDenumire() + "(" + std::to_string(tel.getAn()) + ")";
		lst->addItem(QString::fromStdString(text));

	}

}