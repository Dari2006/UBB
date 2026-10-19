#include "service.h"
#include "QListWidget"
#include "QVBoxLayout"
#include <QHBoxLayout>
#include <QPushButton>
class rochieGUI : public QWidget {
private:
	Service& s;
	//pt cerinta 1
	//QHBoxLayout* lyMain = new QHBoxLayout;
	QListWidget* lst = new QListWidget{this};

	//pt cerinta 3
	QPushButton* btnInchiriere = new QPushButton{"&Inchiriere rochie"};

	

	void initGUI();
	void loadData();
	void connect();
public:
	rochieGUI(Service& serv) : s{ serv } {
		initGUI();
		loadData();
		connect();
	}
};