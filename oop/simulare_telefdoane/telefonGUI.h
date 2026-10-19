#include <qwidget.h>
#include "service.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <qcombobox.h>
#include <qlineedit.h>
class telefonGUI : public QWidget {
private:
	Service& s;
	//pt cerinta 1
	QListWidget* lst = new QListWidget{this};
	//pt cerinta 2
	QComboBox* box = new QComboBox{ this };
	std::set<string> categorii;

	//pt cerinta 3
	QLineEdit* linie = new QLineEdit;


	void initGUI();
	void loadData();
	void connect();
	void reloadData(const vector<Telefon>& v);
public:
	telefonGUI(Service& serv) : s{ serv } {
		
		loadData();initGUI();
		connect();
	}
};