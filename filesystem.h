#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <QColor>
#include <QDebug>
#include <QDir>
#include <QImage>
#include <QObject>
#include <QStandardPaths>
#include <QWidget>

#include "canvas.h"
class Canvas;

class FileSystem : QWidget
{
    Q_OBJECT
  public:
    explicit FileSystem(QWidget *parent = nullptr);

  public slots:
    void create(QString, int, int);
    void clearDirectory();
    void saveImage(QPixmap *, const QString &);
    void undo(Canvas *);
    void redo(Canvas *);
};

#endif // FILESYSTEM_H
