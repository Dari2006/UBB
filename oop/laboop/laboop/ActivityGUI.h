#pragma once
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qtablewidget.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qlabel.h>
#include "Service.h" 
#include "coscrudgui.h"
#include "cosreadonlygui.h"
class ActivityGUI : public QWidget {
private:
    Service& serv; // Referinta la Service

    // Componente pentru afisare
    QListWidget* lst = new QListWidget; 
    QListWidget* lstPlan = new QListWidget;

    // Componente pentru input (le punem aici ca sa le accesam in functii)
    QLineEdit* txtTitlu = new QLineEdit;
    QLineEdit* txtDescriere = new QLineEdit;
    QLineEdit* txtTip = new QLineEdit;
    QLineEdit* txtDurata = new QLineEdit;
    QLineEdit* lineExport = new QLineEdit;

    // Butoane
    QPushButton* btnAdd = new QPushButton{ "&Adauga" };
    QPushButton* btnDelete = new QPushButton{ "&Sterge" };
    QPushButton* btnUndo = new QPushButton{ "&Undo" };
    QPushButton* btnExit = new QPushButton{ "&Exit" };
    QPushButton* btnUpdate = new QPushButton{"&Modifica"};

    QPushButton* btnExportHTML = new QPushButton{ "&Export HTML"};
    QPushButton* btnExportCSV = new QPushButton{ "&Export CSV" };

    QPushButton* btnAdaugaPlan = new QPushButton{ "&Adauga activitate in plan"};
    QLineEdit* lineTitluPlan = new QLineEdit;
    QPushButton* btnGenereazaPlan = new QPushButton{ "&Genereaza plan" };
    QPushButton* btnGolestePlan = new QPushButton{"&Goleste plan"};

    QVBoxLayout* lyTipuri = new QVBoxLayout; // Layout pentru butoanele de tipuri
    QWidget* containerTipuri = new QWidget;

    QLineEdit* txtFilter = new QLineEdit;
    QPushButton* btnFilterDescriere = new QPushButton{ "&Descriere filtrare" };
    QPushButton* btnFilter = new QPushButton{ "&Filtrare" };

    QPushButton* btnSort = new QPushButton{ "&Sortare" };
    QPushButton* btnSortCresc = new QPushButton{ "&Crescator" };
    QPushButton* btnSortDescr = new QPushButton{ "&Descrescator" };

    QPushButton* btnDeschideCRUD = new QPushButton{ "Deschide Cos CRUD" };
    QPushButton* btnDeschideReadOnly = new QPushButton{ "Deschide Cos ReadOnly" };

    void guiAdaugaButoaneTipuri();

    void initGUI();
    void loadData();
    void initConnect();
    void loadDataPlan();

public:
    ActivityGUI(Service& s) : serv{ s } {
        initGUI();
        loadData();
        initConnect();
        loadDataPlan();
        void guiAdaugaButoaneTipuri();
    }
};

class PlanGUI : public QWidget {
private:
    Service& serv;
    QTableWidget* table = new QTableWidget;

    QLineEdit* lineExport = new QLineEdit;
    QPushButton* btnExportHTML = new QPushButton{ "&Export HTML" };
    QPushButton* btnExportCSV = new QPushButton{ "&Export CSV" };
    QPushButton* btnAdaugaPlan = new QPushButton{ "&Adauga activitate in plan" };
    QLineEdit* lineTitluPlan = new QLineEdit;
    QPushButton* btnGenereazaPlan = new QPushButton{ "&Genereaza plan" };
    QPushButton* btnGolestePlan = new QPushButton{ "&Goleste plan" };


    void initGUI();
    void loadData();
    void connect();

public:
    PlanGUI(Service& s) : serv{ s } {
        initGUI();
        loadData();
        connect();
    }
};