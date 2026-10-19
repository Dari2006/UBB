#include "service.h"
#include <qwidget.h>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>

class melodieGUI : public QWidget {
private:
	Service& s;
	//pt cerinta 1
	QTableWidget* tbl = new QTableWidget{this};

	void initGUI();
	void loadData();
	void connect();
public:
	melodieGUI(Service& serv) : s{ serv } {
		initGUI();
		loadData();
		connect();
	}
};