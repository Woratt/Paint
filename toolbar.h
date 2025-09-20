#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QApplication>
#include <QDir>
#include <QFile>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QToolBar>

#include "filesystem.h"
#include "paintwindow.h"

class PaintWindow;

enum class Tool
{
    Brush,
    Rectangle,
    Circle,
    Eraser,
    Bucket,
    Line,
    BrokenLine,
};

class ToolBar : public QToolBar
{
    Q_OBJECT
  public:
    ToolBar(PaintWindow *, QWidget *parent = nullptr);

  private:
    QPushButton *createButton(const QString &);
    QPushButton *createFlippedButton(const QString &);
    QWidget *createSpacer(int);
    QWidget *createExpandingSpacer();
  signals:
    void toolSelected(Tool tool);
    void changedWidth(int Width);
};

#endif // TOOLBAR_H
