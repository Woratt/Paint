#include "filesmodel.h"

filesModel::filesModel(QWidget *parent) : QWidget(parent)
{
    QString folderPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/MyPaintFiles";
    QDir dir(folderPath);
    if (!dir.exists())
    {
        if (dir.mkpath("."))
        {
            qDebug() << "Директорію створено:" << folderPath;
        }
        else
        {
            qDebug() << "Не вдалося створити директорію:" << folderPath;
        }
    }
    else
    {
        qDebug() << "Директорія вже існує:" << folderPath;
    }

    model = new QFileSystemModel(this);
    model->setRootPath(folderPath);
    model->setFilter(QDir::Files | QDir::NoDotAndDotDot);

    view = new QListView(this);
    view->setModel(model);
    view->setRootIndex(model->index(folderPath));
}

QListView *filesModel::takeView() { return view; }

QFileSystemModel *filesModel::takeModel() { return model; }
