#include "coscrudgui.h"


void cosCrudGui::initGUI() {
    auto ly = new QHBoxLayout{ this };
    model = new MyTableModel(plan);
    table->setModel(model);
    ly->addWidget(table);

    auto lyRight = new QVBoxLayout{ this };
    lyRight->addWidget(new QLabel("Titlu activitate/Numar activitati dorite:"));
    lyRight->addWidget(lineTitluPlan);
    lyRight->addWidget(btnGenereazaPlan);
    lyRight->addWidget(btnGolestePlan);
   

    ly->addLayout(lyRight);

    this->resize(1000, 400);
}



void cosCrudGui::loadData() {
    model->refresh();
}





void cosCrudGui::connectbtns() {
	QObject::connect(btnGolestePlan, &QPushButton::clicked, [&]{
		plan.goleste();

	});

	QObject::connect(btnGenereazaPlan, &QPushButton::clicked, [&] {
        emit cerePlanRandom();
		});
}