#include "practicOOP.h"
#include <QtWidgets/QApplication>
#include "teste.h"
#include "Repo.h"
#include "gui.h"
int main(int argc, char *argv[])
{
    //testAll();
    QApplication app(argc, argv);
    Repo r{"task.txt"};
    Service s{r};
    gui f{s};
    f.show();
    return app.exec();
}
