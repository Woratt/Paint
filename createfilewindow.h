#ifndef CREATEFILEWINDOW_H
#define CREATEFILEWINDOW_H

#include <QApplication>
#include <QDialog>
#include <QFileSystemModel>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListView>
#include <QMainWindow>
#include <QMenuBar>
#include <QMessageBox>
#include <QObject>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class numberLine;
class FileSystem;

class createFileWindow : public QDialog
{
    Q_OBJECT
  public:
    explicit createFileWindow(QWidget *parent = nullptr);
};

#endif // CREATEFILEWINDOW_H
