#ifndef CANVAS_H
#define CANVAS_H

#include <QGestureEvent>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QPinchGesture>
#include <QPixmap>
#include <QWheelEvent>
#include <QWidget>
#include <QtGlobal>

class ToolBar;
class InfoBar;
enum class Tool;

class Canvas : public QWidget
{
    Q_OBJECT
  public:
    explicit Canvas(QWidget *parent = nullptr);
    explicit Canvas(const QImage &, QWidget *parent = nullptr);
    auto takePixmap() -> QPixmap &;
    void changeOffset(bool, const QPointF &);
    Canvas &operator=(const Canvas &);

  signals:
    void updateZoom(double zoom);
    void updateCursor(const QPoint &);
    void updateColor(const QColor &);

  private:
    QVector<QImage> history;
    QPixmap pixMap;
    bool draw = false;
    QPoint lastPoint, secondPoint;
    Tool tool;
    int numClik = 0;
    double zoom = 1.0;
    QPointF offset;
    [[nodiscard]] auto eventPosToImagePoint(const QPoint &) const -> QPoint;
    auto gestureEvent(QGestureEvent *) -> bool;
    void pinchTriggered(QPinchGesture *);
    void clampOffset();
    int widthLine = 3;
    void addImageInHistory(const QImage &);
    int numOfHistory = 0;
    QPen pen;

  protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent * /*event*/) override;
    void mousePressEvent(QMouseEvent * /*event*/) override;
    void mouseReleaseEvent(QMouseEvent * /*event*/) override;
    void wheelEvent(QWheelEvent * /*event*/) override;
    auto event(QEvent * /*event*/) -> bool override;
  public slots:
    void increaseZoom();
    void reduceZoom();
    void setTool(Tool);
    void changedWidth(int);
    void takeImageWithHistory(bool);
    void setColorPen(QColor);
};

#endif
