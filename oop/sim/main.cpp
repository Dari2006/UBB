#include "sim.h"
#include <QtWidgets/QApplication>
#include "teste.h"
#include "podcastGUI.h"
int main(int argc, char *argv[])
{
    runTests();

    QApplication app(argc, argv);
    Repo r{"podcast.txt"};
    Service s{r};
    podcastGUI gui{s};
    gui.show();
    return app.exec();
}
