#include "simulare_telefdoane.h"
#include <QtWidgets/QApplication>
#include "telefonGUI.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Repo r{"telefoane.txt"};
    Service s{r};
    telefonGUI gui{s};
    gui.show();
    return app.exec();
}
