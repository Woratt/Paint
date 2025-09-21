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
    explicit filesModel(QWidget *parent = nullptr);
    auto takeView() -> QListView *;
    auto takeModel() -> QFileSystemModel *;

  private:
    QFileSystemModel *model;
    QListView *view;
};

#endif // FILESMODEL_H
