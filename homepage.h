#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QApplication>
#include <QFileDialog>
#include <QFileSystemModel>
#include <QHBoxLayout>
#include <QImageReader>
#include <QLabel>
#include <QListView>
#include <QMainWindow>
#include <QObject>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "createfilewindow.h"
#include "filesmodel.h"
#include "filesystem.h"
#include "menubar.h"
#include "paintwindow.h"

class HomePage : public QMainWindow
{
    Q_OBJECT
  public:
    HomePage(QWidget *parent = nullptr);
    bool takeIsOpen();

  private:
    QPushButton *createBt;
    QPushButton *openBt;
    QPushButton *openOtherBt;
    QPushButton *clearBt;
    QLabel *label;
    FileSystem *fileSystem;
    QString file;
    bool open = true;
};

#endif // HOMEPAGE_H
