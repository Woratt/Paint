#ifndef FILESMODEL_H
#define FILESMODEL_H

#include <QFileSystemModel>
#include <QListView>
#include <QObject>
#include <QStandardPaths>
#include <QWidget>

class filesModel : public QWidget
{
    Q_OBJECT
  public:
    filesModel(QWidget *parent = nullptr);
    QListView *takeView();
    QFileSystemModel *takeModel();

  private:
    QFileSystemModel *model;
    QListView *view;
};

#endif // FILESMODEL_H
