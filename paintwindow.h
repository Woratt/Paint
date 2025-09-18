#ifndef PAINTWINDOW_H
#define PAINTWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QPainter>
#include <QMouseEvent>
#include <QScrollArea>

#include "menubar.h"
#include "toolbar.h"
#include "canvas.h"

class Canvas;
class ToolBar;
class MenuBar;

class PaintWindow : public QMainWindow
{
    Q_OBJECT

public:
    PaintWindow(QImage,const QString&, QWidget *parent = nullptr);
    Canvas* takeCanvas();
    ~PaintWindow();
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;
private:
    QPoint lastPoint;
    bool drawing = false;
    MenuBar* menu;
    Canvas* canvas;
    ToolBar* toolBar;
};
#endif // PAINTWINDOW_H
