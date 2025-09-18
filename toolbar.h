#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QToolBar>
#include <QLabel>
#include <QFile>
#include <QDir>
#include <QApplication>
#include <QPushButton>
#include <QSpinBox>

#include "filesystem.h"
#include "paintwindow.h"

class PaintWindow;

enum class Tool{
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
    ToolBar(PaintWindow*, QWidget* parent = nullptr);
private:
signals:
    void toolSelected(Tool tool);
    void changedWidth(int Width);
};

#endif // TOOLBAR_H
