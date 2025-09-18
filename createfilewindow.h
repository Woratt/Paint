#ifndef CREATEFILEWINDOW_H
#define CREATEFILEWINDOW_H

#include <QWidget>
#include <QDialog>
#include <QObject>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileSystemModel>
#include <QListView>
#include <QLabel>
#include <QApplication>
#include <QLineEdit>
#include <QMenuBar>
#include <QMessageBox>

#include "numberLine.h"
#include "filesystem.h"

class createFileWindow : public QDialog
{
    Q_OBJECT
public:
    createFileWindow(QWidget* parent = nullptr);
};

#endif // CREATEFILEWINDOW_H
