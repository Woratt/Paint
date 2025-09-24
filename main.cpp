#include "homepage.h"
#include "paintwindow.h"

#include <QApplication>

#include "resourcepath.h"

extern QString resourcePath = resourcepath::getResourcePath();
auto main(int argc, char *argv[]) -> int
{
    QApplication const app(argc, argv);

    QApplication::setWindowIcon(QIcon(resourcePath + "icons/icon.icns"));
    HomePage homePage;

    homePage.show();

    return QApplication::exec();
}
