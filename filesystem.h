#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <QColor>
#include <QDebug>
#include <QDir>
#include <QImage>
#include <QObject>
#include <QStandardPaths>
#include <QWidget>

class Canvas;

class FileSystem : QWidget
{
    Q_OBJECT
  public:
    explicit FileSystem(QWidget *parent = nullptr);

  
    static void create(const QString&, int, int);
    static void clearDirectory();
    static void saveImage(QPixmap *, const QString &);
    static void undo(Canvas *);
    static void redo(Canvas *);
};

#endif // FILESYSTEM_H
