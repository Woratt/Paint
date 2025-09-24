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
  private:
    QHBoxLayout *nameLayout;
    QHBoxLayout *presentLayout;
    QHBoxLayout *widthLayout;
    QHBoxLayout *heightLayout;
    QHBoxLayout *buttonLayout;
    QVBoxLayout *mainLayout;
    QLineEdit *nameLine;
    numberLine *widthLine;
    numberLine *heightLine;
    QPushButton *presentButton;
    QLabel *nameLabel;
    QLabel *presentLabel;
    QLabel *widthLabel;
    QLabel *heightLabel;
    QPushButton *okButton;
    QPushButton *cancelButton;
    void createsAllComponents();
    void initializeButtons();
    void initializeLayouts();
    void initializeFields();
    void initializeButtonMenu();
    void initializeConnections();
};

#endif
