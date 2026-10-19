#include "laboop.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <vector>
#include <string>
#include "ActivityGUI.h"
#include "teste.h"

using std::vector;
using std::string;
int main(int argc, char *argv[])
{
    ruleazaTeste();
    QApplication app(argc, argv);

    Repo r;
    Validator v;
    Service s{r, v};

    ActivityGUI gui{s};
    gui.show();
    PlanGUI guiPlan{s};
    guiPlan.show();
    

    


    return app.exec();
}
