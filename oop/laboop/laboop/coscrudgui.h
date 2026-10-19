#pragma once
#include <QWidget>
//#include "observer.h"
#include "planificare.h"
#include <QPushButton>
#include "Service.h"
#include <qlineedit.h>
#include <qtablewidget.h>
#include <qmessagebox.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <qlabel.h>


#include <QAbstractTableModel>


class MyTableModel : public QAbstractTableModel {
private:
    Planificare& plan;
public:
    MyTableModel(Planificare& p) : plan{ p } {}

    int rowCount(const QModelIndex& = QModelIndex()) const override {
        return static_cast<int>(plan.dim());
    }

    int columnCount(const QModelIndex& = QModelIndex()) const override {
        return 4; // Titlu, Descriere, Tip, Durata
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (!index.isValid() || index.row() >= static_cast<int>(plan.dim())) {
            return QVariant();
        }

        if (role == Qt::DisplayRole) {
            const auto& activitate = plan.getToate()[index.row()];
            if (index.column() == 0) return QString::fromStdString(activitate.getTitlu());
            if (index.column() == 1) return QString::fromStdString(activitate.getDescriere());
            if (index.column() == 2) return QString::fromStdString(activitate.getTip());
            if (index.column() == 3) return QVariant(activitate.getDurata());
        }
        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
            if (section == 0) return "Titlu";
            if (section == 1) return "Descriere";
            if (section == 2) return "Tip";
            if (section == 3) return "Durata";
        }
        return QVariant();
    }

    void refresh() {
        emit layoutAboutToBeChanged();
        emit layoutChanged();
    }
};





class cosCrudGui : public QWidget, public Observer {
	Q_OBJECT
private:
	Planificare& plan;
	
	QPushButton* btnGenereazaPlan = new QPushButton{ "&Genereaza plan" };
	QPushButton* btnGolestePlan = new QPushButton{ "&Goleste plan" };
    QTableView* table = new QTableView;
    MyTableModel* model;
	
	void initGUI();
	void connectbtns();

	void loadData();
public:
	QLineEdit* lineTitluPlan = new QLineEdit;
	cosCrudGui(Planificare& p) : plan{ p } {
		initGUI();
		connectbtns();
		plan.addObserver(this);
	}

	void update() override {
		loadData();
	}

	~cosCrudGui() {
		plan.removeObserver(this); 
	}
signals:
	void cerePlanRandom();
};