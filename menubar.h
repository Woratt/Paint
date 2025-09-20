#ifndef MENUBAR_H
#define MENUBAR_H

#include <QMenuBar>
#include <QObject>
#include <QWidget>

#include "createFileWindow.h"
#include "filesystem.h"

class PaintWindow;
class FileSystem;

class MenuBar : public QMenuBar
{
    Q_OBJECT
  public:
    // MenuBar(QWidget* parent = nullptr);
    MenuBar(const QString &, PaintWindow *, QWidget *parent = nullptr);

  private:
    QAction *saveAct;
    QAction *newAct;
    QAction *openAct;
    QAction *closeAct;
    QAction *undoAct;
    QAction *redoAct;
    QMenu *fileMenu;
    QMenu *editMenu;
    PaintWindow *paintWindow;
    const QString &nameImage = nullptr;
    FileSystem *fileSystem;
  public slots:
    void save();
    void close();
    void newFile();
    void open();
};

#endif // MENUBAR_H
