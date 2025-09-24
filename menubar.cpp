#include "menubar.h"
#include "canvas.h"
#include "createfilewindow.h"
#include "filesystem.h"
#include "paintwindow.h"
#include "toolbar.h"

MenuBar::MenuBar(const QString &nameImage, PaintWindow *paintWindow, QWidget *parent)
    : QMenuBar(parent), nameImage(nameImage), fileSystem(new FileSystem()), paintWindow(paintWindow)
{
    saveAct = new QAction(tr("&Save"), this);
    newAct = new QAction(tr("&New file"), this);
    openAct = new QAction(tr("&Open file"), this);
    closeAct = new QAction(tr("&Close file"), this);

    undoAct = new QAction(tr("&Undo"), this);
    redoAct = new QAction(tr("&Redo"), this);

    fileMenu = addMenu(tr("&File"));
    fileMenu->addAction(saveAct);
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(closeAct);

    editMenu = addMenu(tr("&Edit"));
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);

    saveAct->setShortcut(QKeySequence::Save);
    newAct->setShortcut(QKeySequence::New);
    openAct->setShortcut(QKeySequence::Open);
    closeAct->setShortcut(QKeySequence::Close);

    undoAct->setShortcut(QKeySequence::Undo);
    redoAct->setShortcut(QKeySequence::Redo);

    connect(saveAct, &QAction::triggered, this, [this, paintWindow, nameImage]() -> void
            { FileSystem::saveImage(&(paintWindow->takeCanvas()->takePixmap()), nameImage); });
    connect(newAct, &QAction::triggered, this,
            [this]() -> void
            {
                auto *window = new createFileWindow(this);
                window->exec();
            });
    connect(openAct, &QAction::triggered, this, &MenuBar::open);
    connect(closeAct, &QAction::triggered, this, &MenuBar::close);

    connect(undoAct, &QAction::triggered, this,
            [this, paintWindow]() -> void { FileSystem::undo(paintWindow->takeCanvas()); });

    connect(redoAct, &QAction::triggered, this,
            [this, paintWindow]() -> void { FileSystem::redo(paintWindow->takeCanvas()); });
}

void MenuBar::close() {}

void MenuBar::newFile() {}

void MenuBar::open() {}

void MenuBar::save() {}
