#include "homepage.h"
#include "paintwindow.h"

#include <QApplication>

auto main(int argc, char *argv[]) -> int
{
    QApplication const app(argc, argv);

    HomePage homePage;

    homePage.show();

    return QApplication::exec();
}
