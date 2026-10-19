#include "ActivityGUI.h"
#include "Activitate.h"
#include <string>

void ActivityGUI::initGUI() {
    QHBoxLayout* lyMain = new QHBoxLayout{ this };

    // Partea stanga: Lista
    lyMain->addWidget(lst);

    // Partea dreapta: Formular si Butoane
    auto lyRight = new QVBoxLayout;
    auto formLy = new QFormLayout;
    formLy->addRow("Titlu:", txtTitlu);
    formLy->addRow("Descriere:", txtDescriere);
    formLy->addRow("Tip:", txtTip);
    formLy->addRow("Durata:", txtDurata);
    lyRight->addLayout(formLy);

    auto lyBtns = new QHBoxLayout;
    lyBtns->addWidget(btnAdd);
    lyBtns->addWidget(btnDelete);
    lyBtns->addWidget(btnUndo);
    lyBtns->addWidget(btnUpdate);
    lyBtns->addWidget(btnDeschideCRUD);
    lyBtns->addWidget(btnDeschideReadOnly);
    lyRight->addLayout(lyBtns);

    auto lyFilter = new QVBoxLayout{};
    auto lblFiltrare = new QLabel{ "Filtru/Criteriu sortare:" };
    
    lyFilter->addWidget(lblFiltrare);
    lyFilter->addWidget(txtFilter);
    lyFilter->addWidget(btnFilter);

    QVBoxLayout* lySortare = new QVBoxLayout{};
    lySortare->addWidget(btnSort);
    lySortare->addWidget(btnSortCresc);
    lySortare->addWidget(btnSortDescr);
    btnSortCresc->hide();
    btnSortDescr->hide();


    lyRight->addLayout(lyFilter);
    lyRight->addLayout(lySortare);
    lyRight->addStretch(); 
    lyRight->addWidget(btnExit);

    containerTipuri->setLayout(lyTipuri);
    lyMain->addWidget(containerTipuri);

    

    
    
    lyMain->addLayout(lyRight);

    //adaugam in dreapta lista pentru planificare
    
}

void ActivityGUI::loadData() {
    lst->clear();
    try {
        const auto& all = serv.getAll();
        for (const auto& a : all) {
            lst->addItem(QString::fromStdString(a.getTitlu()));
        }
    }
    catch (const RepoException& ex) {
        QMessageBox::critical(this, "Error", QString::fromStdString(ex.getMesaj()));
    }
    guiAdaugaButoaneTipuri();
}

void ActivityGUI::loadDataPlan() {
    lstPlan->clear();
    const auto &toate = serv.getToateDinPlan();
    for (const auto& p : toate) {
        lstPlan->addItem(QString::fromStdString(p.getTitlu()));
    }
}

void ActivityGUI::initConnect() {
    // Exit
    QObject::connect(btnExit, &QPushButton::clicked, [&]() {
        exit(0);
        });

    // Adaugare
    QObject::connect(btnAdd, &QPushButton::clicked, [&]() {
        auto t = txtTitlu->text().toStdString();
        auto d = txtDescriere->text().toStdString();
        auto ty = txtTip->text().toStdString();
        auto dur = txtDurata->text().toDouble();

        try {
            serv.adauga(t, d, ty, dur);
            loadData(); // Reincarcam lista
        }
        catch (const RepoException& ex) {
            QMessageBox::warning(this, "Error", QString::fromStdString(ex.getMesaj()));
        }
        catch (const ValidatorException& e) {
            for (auto const& msg : e.getErori()) {
                QMessageBox::warning(this, "Error", QString::fromStdString(msg));
            }
        }
        });

    QObject::connect(lst, &QListWidget::itemSelectionChanged, [&]() {
        auto sel = lst->selectedItems();
        if (sel.isEmpty()) {
            // Resetam campurile daca nu e nimic selectat
            txtTitlu->clear();
            txtDescriere->clear();
            txtTip->clear();
            txtDurata->clear();
        }
        else {
            auto item = sel.at(0);
            string titluSelectat = item->text().toStdString();

            try {
                const auto& toate = serv.getAll();
                auto it = std::find_if(toate.begin(), toate.end(), [&](const Activitate& a) {
                    return a.getTitlu() == titluSelectat;
                    });

                if (it != toate.end()) {
                    const auto& a = *it;
                    txtTitlu->setText(QString::fromStdString(a.getTitlu()));
                    txtDescriere->setText(QString::fromStdString(a.getDescriere()));
                    txtTip->setText(QString::fromStdString(a.getTip()));
                    txtDurata->setText(QString::number(a.getDurata()));
                }
            }
            catch (const RepoException& ex) {
                QMessageBox::critical(this, "Eroare", QString::fromStdString(ex.getMesaj()));
            }
        }
        });

    QObject::connect(btnDelete, &QPushButton::clicked, [&]() {
        auto titlu = txtTitlu->text().toStdString();

        if (titlu.empty()) {
            QMessageBox::information(this, "Atenție", "Titlu invalid");
            return;
        }

        try {
            const auto& toate = serv.getAll();
            auto it = std::find_if(toate.begin(), toate.end(), [&](const Activitate& a) {
                return a.getTitlu() == titlu;
                });
            if (it != toate.end()) {
                const auto&a = *it;
                try {
                    serv.sterge(a.getTitlu(), a.getDescriere(), a.getTip(), a.getDurata());
                }
                catch (RepoException& e) {
                    QMessageBox::critical(this, "Eroare", QString::fromStdString(e.getMesaj()));
                }
                 loadData();
                 txtTitlu->clear();
                 txtDescriere->clear();
                 txtTip->clear();
                 txtDurata->clear();

                 QMessageBox::information(this, "Succes", "Activitatea a fost stearsa!");
            }
            else {
                if (it == toate.end()) {
                    QMessageBox::information(this, "Eroare", "Activitatea nu exista");
                }
            }
        }
        catch (const RepoException& ex) {
            QMessageBox::critical(this, "Eroare", QString::fromStdString(ex.getMesaj()));
        }
        });

    // Conectare pentru butonul de Undo
    QObject::connect(btnUndo, &QPushButton::clicked, [&]() {
        try {
            serv.undo();

            loadData();

            txtTitlu->clear();
            txtDescriere->clear();
            txtTip->clear();
            txtDurata->clear();

            QMessageBox::information(this, "Undo", "Undo succes");
        }
        catch (const RepoException& ex) {
            QMessageBox::warning(this, "Atenție", QString::fromStdString(ex.getMesaj()));
        }
        catch (ServiceException& e) {
            QMessageBox::warning(this, "Eroare", QString::fromStdString(e.getMessage()));
        }
        });

    QObject::connect(btnUpdate, &QPushButton::clicked, [&]() {
        try {
            auto sel = lst->selectedItems();
            if (sel.isEmpty()) {
                QMessageBox::warning(this, "Atenție", "Selectati o activitate din lista");
                return;
            }

            string titluVechi = sel.at(0)->text().toStdString();

            string titluNou = txtTitlu->text().toStdString();
            string descNoua = txtDescriere->text().toStdString();
            string tipNou = txtTip->text().toStdString();
            double durataNoua = txtDurata->text().toDouble();

            const auto& toate = serv.getAll();
            auto it = std::find_if(toate.begin(), toate.end(), [&](const Activitate& a) {
                return a.getTitlu() == titluVechi;
                });
            if (it != toate.end()) {
                Activitate a = *it;
                serv.actualizeaza(a.getTitlu(), a.getDescriere(), a.getTip(), a.getDurata(), titluNou, descNoua, tipNou, durataNoua);
            }
            
            loadData();
            QMessageBox::information(this, "Succes", "Activitate actualizata cu succes!");
        }
        catch (const RepoException& ex) {
            QMessageBox::critical(this, "Eroare Repo", QString::fromStdString(ex.getMesaj()));
        }
        catch (const ValidatorException& ex) {
              for(const auto& msg : ex.getErori())
                    QMessageBox::warning(this, "Eroare Validare", QString::fromStdString(msg));
        }
        });

        //filtrare
    QObject::connect(btnFilter, &QPushButton::clicked, [&]() {
        string criteriu = txtFilter->text().toStdString();
        lst->clear();
        auto toate = serv.getAll();
        vector<Activitate> gasite;
        copy_if(toate.begin(), toate.end(), back_inserter(gasite), [&criteriu](const Activitate &p){return p.getDescriere() == criteriu || p.getTip() == criteriu;});

        for (const auto& p : gasite) {
            lst->addItem(QString::fromStdString(p.getTitlu()));
        }
        if (criteriu.length() == 0) {
            lst->clear();
            loadData();
        }
        
    });

    QObject::connect(btnSort, &QPushButton::clicked, [&]() {
        string criteriu = txtFilter->text().toStdString();
        if (criteriu != "1" && criteriu != "2" && criteriu != "3") {
            QMessageBox::warning(this, "Eroare", QString::fromStdString("1 - titlu\n2 - descriere\n3 - tip + durata"));
        }
        if (criteriu == "1" || criteriu == "2" || criteriu == "3") {
            btnSortCresc->show();
            btnSortDescr->show();
        }
        
    });

    QObject::connect(btnSortCresc, &QPushButton::clicked, [&]() {
        if (txtFilter->text().toStdString() == "1") {
            lst->clear();
            auto toate = serv.sortTitluCresc();
            for (const auto& p : toate) {
                lst->addItem(QString::fromStdString(p.getTitlu()));
            }
        }
        if (txtFilter->text().toStdString() == "2") {
            lst->clear();
            auto toate = serv.sortDescriereCresc();
            for (const auto& p : toate) {
                lst->addItem(QString::fromStdString(p.getTitlu()));
            }
        }
        txtFilter->clear();
        btnSortCresc->hide();
        btnSortDescr->hide();
    });

    QObject::connect(btnSortDescr, &QPushButton::clicked, [&]() {
        if (txtFilter->text().toStdString() == "1") {
            lst->clear();
            auto toate = serv.sortTitluDescr();
            for (const auto& p : toate) {
                lst->addItem(QString::fromStdString(p.getTitlu()));
            }
        }
        if (txtFilter->text().toStdString() == "2") {
            lst->clear();
            auto toate = serv.sortDescriereDescr();
            for (const auto& p : toate) {
                lst->addItem(QString::fromStdString(p.getTitlu()));
            }
        }
        txtFilter->clear();
        btnSortCresc->hide();
        btnSortDescr->hide();
        });


    QObject::connect(btnDeschideCRUD, &QPushButton::clicked, [&]() {
        auto& planCurent = serv.getPlan();

        auto* ferCRUD = new cosCrudGui(planCurent);

        QObject::connect(ferCRUD, &cosCrudGui::cerePlanRandom, [&, ferCRUD]() {
            try {
                   int nr = stoi(ferCRUD->lineTitluPlan->text().toStdString());
                   if (nr < 1) {
                       QMessageBox::warning(this, "Eroare", "Numar invalid");
                   }
                   serv.genereazaPlanRandom(nr);
            }
            catch (const std::exception&) {
                QMessageBox::warning(this, "Eroare", "Numar invalid");
            }
            
            });

        ferCRUD->setAttribute(Qt::WA_DeleteOnClose);
        ferCRUD->show();
        });


    QObject::connect(btnDeschideReadOnly, &QPushButton::clicked, [this]() {
        auto& planCurent = serv.getPlan();
        auto* ferReadOnly = new CosReadOnlyGUI(planCurent);
        ferReadOnly->setAttribute(Qt::WA_DeleteOnClose);
        ferReadOnly->show();
        });

}

void ActivityGUI::guiAdaugaButoaneTipuri() {
    
    QLayoutItem* item;
    while ((item = lyTipuri->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    std::map<string, int> statistici;
    const auto& toate = serv.getAll();
    for (const auto& a : toate) {
        statistici[a.getTip()]++;
    }

    for (auto const& [tip, numar] : statistici) {
        auto btn = new QPushButton{ QString::fromStdString(tip) };
        lyTipuri->addWidget(btn);

 
        QObject::connect(btn, &QPushButton::clicked, [this, tip, numar]() {
            QMessageBox::information(this, "Statistici",
                QString("Exista %1 activitati de tipul %2").arg(numar).arg(QString::fromStdString(tip)));
            });
    }
}


//PENTRU PLAN

void PlanGUI::initGUI() {
    auto ly = new QHBoxLayout{this};
    ly->addWidget(table);

    auto lyRight = new QVBoxLayout{this};
    lyRight->addWidget(new QLabel("Titlu activitate/Numar activitati dorite:"));
    lyRight->addWidget(lineTitluPlan);
    lyRight->addWidget(btnAdaugaPlan);
    lyRight->addWidget(btnGenereazaPlan);
    lyRight->addWidget(btnGolestePlan);
    lyRight->addWidget(new QLabel("Nume fisier:"));
    lyRight->addWidget(lineExport);
    lyRight->addWidget(btnExportHTML);
    lyRight->addWidget(btnExportCSV);

    ly->addLayout(lyRight);

    this->resize(1000, 400);
}

void PlanGUI::loadData() {
    table->clear();
    auto toate = serv.getToateDinPlan();
    int nrRows = static_cast<int>(toate.size()+1);
    table->setRowCount(nrRows);
    table->setColumnCount(4);
    table->setItem(0, 0, new QTableWidgetItem(QString::fromStdString("titlu")));
    table->setItem(0, 1, new QTableWidgetItem(QString::fromStdString("descriere")));
    table->setItem(0, 2, new QTableWidgetItem(QString::fromStdString("tip")));
    table->setItem(0, 3, new QTableWidgetItem(QString::fromStdString("durata")));

    int row = 1;

    for (const auto& a : toate) {
        table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(a.getTitlu())));
        table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(a.getDescriere())));
        table->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(a.getTip())));
        table->setItem(row, 3, new QTableWidgetItem(QString::number(a.getDurata())));

        row++;
    }
    
}

void PlanGUI::connect() {
    QObject::connect(btnAdaugaPlan, &QPushButton::clicked, [&](){
        string titlu = lineTitluPlan->text().toStdString();
        try {
            serv.adauga_planificare(titlu);
            loadData();
            lineTitluPlan->clear();
        }
        catch (ServiceException& e) {
            auto eroare = e.getMessage();
            QMessageBox::warning(this, "Eroare", QString::fromStdString(eroare));
        }
    });

    QObject::connect(btnGenereazaPlan, &QPushButton::clicked, [&]() {
        try {
            table->clear();
            int nr = stoi(lineTitluPlan->text().toStdString());
            if (nr < 1) {
                QMessageBox::warning(this, "Eroare", "Numar invalid");
            }
            serv.genereazaPlanRandom(nr);
            loadData();
            lineTitluPlan->clear();
        }
        catch (const std::exception&) {
            QMessageBox::warning(this, "Eroare", "Numar invalid");
        }
        });

    QObject::connect(btnGolestePlan, &QPushButton::clicked, [&]() {
        serv.golestePlan();
        loadData();
        });

    QObject::connect(btnExportHTML, &QPushButton::clicked, [&]() {
        serv.exportaPlanificareaHTML(lineExport->text().toStdString());
        QMessageBox::information(this, "Succes", QString("Export realizat cu succes"));
        });

    QObject::connect(btnExportCSV, &QPushButton::clicked, [&]() {
        serv.exportaPlanificareaCSV(lineExport->text().toStdString());
        QMessageBox::information(this, "Succes", "Export realizat cu succes");
        });
}