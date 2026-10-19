#include "melodii_1.h"
#include <QtWidgets/QApplication>
#include "teste.h"
#include "melodieGUI.h"
int main(int argc, char *argv[])
{
    runTests();
    
    QApplication app(argc, argv);
    Repo r{"melodii.txt"};
    Service s{r};
    melodieGUI gui{s};
    gui.show();
    return app.exec();
}
