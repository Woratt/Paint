#include "homepage.h"
#include "paintwindow.h"

#include <QApplication>

#include "resourcepath.h"

resourcePath = resourcepath::getResourcePath();
auto main(int argc, char *argv[]) -> int
{
    QApplication const app(argc, argv);
#ifdef Q_OS_MAC
    QApplication::setWindowIcon(QIcon(resourcePath + "icons/icon.icns"));
#endif
    HomePage homePage;

    homePage.show();

    return QApplication::exec();
}
