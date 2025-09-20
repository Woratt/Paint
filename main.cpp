#include "homepage.h"
#include "paintwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    HomePage homePage;

    homePage.show();

    return a.exec();
}
