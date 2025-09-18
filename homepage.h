#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QObject>
#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileSystemModel>
#include <QListView>
#include <QLabel>
#include <QApplication>
#include <QFileDialog>
#include <QImageReader>

#include "filesmodel.h"
#include "menubar.h"
#include "filesystem.h"
#include "createfilewindow.h"
#include "paintwindow.h"

class HomePage : public QMainWindow
{
    Q_OBJECT
public:
    HomePage(QWidget* parent = nullptr);
    bool takeIsOpen();
private:
    QPushButton* createBt;
    QPushButton* openBt;
    QPushButton* openOtherBt;
    QPushButton* clearBt;
    QLabel* label;
    FileSystem* fileSystem;
    QString file;
    bool open = true;
};

#endif // HOMEPAGE_H
