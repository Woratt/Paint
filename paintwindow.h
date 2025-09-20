#ifndef PAINTWINDOW_H
#define PAINTWINDOW_H

#include <QAction>
#include <QMainWindow>
#include <QMenuBar>
#include <QMouseEvent>
#include <QPainter>
#include <QScrollArea>
#include <QToolBar>

#include "canvas.h"
#include "menubar.h"
#include "toolbar.h"

class Canvas;
class ToolBar;
class MenuBar;

class PaintWindow : public QMainWindow
{
    Q_OBJECT

  public:
    PaintWindow(QImage, const QString &, QWidget *parent = nullptr);
    Canvas *takeCanvas();
    ~PaintWindow();

  protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;

  private:
    QPoint lastPoint;
    bool drawing = false;
    MenuBar *menu;
    Canvas *canvas;
    ToolBar *toolBar;
};
#endif // PAINTWINDOW_H
