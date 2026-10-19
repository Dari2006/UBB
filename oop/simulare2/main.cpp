#include "simulare2.h"
#include <QtWidgets/QApplication>
#include "teste.h"
#include "EelevGUI.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    testAll();
    Repo r;
    Service s{r, "elevi.txt"};
    elevGUI gui{s};
    gui.show();
    return app.exec();
}
