#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QtGlobal>
#include <QGestureEvent>
#include <QPinchGesture>

#include "toolbar.h"

class ToolBar;
enum class Tool;

class Canvas : public QWidget
{
public:
    Canvas(const QImage&, QWidget* parent = nullptr);
    QPixmap& takePixmap();
private:
    QPixmap pixMap;
    bool draw = false;
    QPoint lastPoint, secondPoint;
    Tool tool;
    int numClik = 0;
    double zoom = 1.0;
    QPointF offset;
    QPoint eventPosToImagePoint(const QPoint&) const;
    bool gestureEvent(QGestureEvent*);
    void pinchTriggered(QPinchGesture*);
    void clampOffset();
    int widthLine = 3;
    void addImageInHistory(const QImage&);
    int numOfHistory = 0;
protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;
    void wheelEvent(QWheelEvent*) override;
    bool event(QEvent*) override;
public slots:
    void setTool(Tool);
    void changedWidth(int);
    void takeImageWithHistory(bool);
};

#endif
