#include "melodi_1.h"
#include <QtWidgets/QApplication>
#include "melodieGUI.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Repo r{"melodii.txt"};
    Service s{r};
    melodieGUI gui{s};
    gui.show();
    return app.exec();
}
