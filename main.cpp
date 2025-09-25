#include "homepage.h"
#include "paintwindow.h"

#include <QApplication>

#include "resourcepath.h"

auto main(int argc, char *argv[]) -> int
{
    QString resourcePath = resourcepath::getResourcePath();
    QApplication const app(argc, argv);
#ifdef Q_OS_MAC
    QApplication::setWindowIcon(QIcon(resourcePath + "icons/icon.icns"));
#endif
    HomePage homePage;

    homePage.show();

    return QApplication::exec();
}
