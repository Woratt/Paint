#ifndef FILESMODEL_H
#define FILESMODEL_H

#include <QObject>
#include <QWidget>
#include <QFileSystemModel>
#include <QListView>
#include <QStandardPaths>

class filesModel : public QWidget
{
    Q_OBJECT
public:
    filesModel(QWidget* parent = nullptr);
    QListView* takeView();
    QFileSystemModel* takeModel();
private:
    QFileSystemModel* model;
    QListView* view;
};

#endif // FILESMODEL_H
