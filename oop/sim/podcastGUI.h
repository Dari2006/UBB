#include <qwidget.h>
#include "service.h"
#include <qlistwidget.h>
#include <QHBoxLayout>
#include <qlineedit.h>
#include <QVBoxLayout>
#include <qpushbutton.h>
#include <qmessagebox.h>
class podcastGUI : public QWidget {
private:
	Service& s;

	//pt cerinta 1
	QListWidget* lst = new QListWidget{this};

	//pt cerinta 2
	QLineEdit* lineCod = new QLineEdit{this};
	QLineEdit* lineCateg = new QLineEdit{ this };

	//pt cerinta 3
	QPushButton* btnSortTitlu = new QPushButton{"&Sortare dupa titlu"};
	QPushButton* btnSortCreator = new QPushButton{"&Sortare dupa creator"};
	QPushButton* btnSortDefault = new QPushButton{"&Nesortat"};

	//pt cerinta 4
	QPushButton* btnDescr = new QPushButton{"&Afiseaza descriere"};
	string lastClicked;

	void initGUI();
	void loadData();
	void initConnect();

public:
	podcastGUI(Service& serv) : s{ serv } {
		initGUI();
		loadData();
		initConnect();
	}
	//metoda care reincarca datele din lista
	void reloadData(const vector<Podcast>& v);
};