#include "simulare3.h"
#include <QtWidgets/QApplication>
#include "rochieGUI.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Repo r{"rochie.txt"};
    Service s{r};
    rochieGUI GUI{s};
    GUI.show();
    return app.exec();
}
