#include "filesystem.h"
#include "canvas.h"

FileSystem::FileSystem(QWidget *parent) : QWidget(parent) {}

void FileSystem::create(const QString &name, int width, int height)
{
    QString const folderPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/MyPaintFiles";

    QImage image(width, height, QImage::Format_RGB32);
    image.fill(Qt::white);
    image.save(folderPath + "/" + name + ".png", "PNG");
}

void FileSystem::clearDirectory()
{
    QString const folderPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/MyPaintFiles";
    QDir dir(folderPath);

    if (!dir.exists())
    {
        qDebug() << "Директорії не існує:" << folderPath;
        return;
    }

    QStringList const files = dir.entryList(QDir::Files);

    for (const QString &file : files)
    {
        if (!dir.remove(file))
        {
            qDebug() << "Не вдалося видалити файл";
        }
    }
}

void FileSystem::saveImage(QPixmap *canvas, const QString &nameImage) { canvas->toImage().save(nameImage, "PNG"); }

void FileSystem::undo(Canvas *canvas) { canvas->takeImageWithHistory(false); }

void FileSystem::redo(Canvas *canvas) { canvas->takeImageWithHistory(true); }
