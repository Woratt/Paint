#include "canvas.h"
#include "toolbar.h"

QVector<QImage> Canvas::history;

Canvas::Canvas(QWidget *parent) : QWidget(parent) {}

Canvas::Canvas(const QImage &image, QWidget *parent) : QWidget(parent)
{
    history.push_back(image);
    pixMap = QPixmap::fromImage(image);
    QSize const imageSize = image.size();

    QSize const targetSize_(1280, 720);

    QSize const scaledSize_ = imageSize.scaled(targetSize_, Qt::KeepAspectRatio);

    setFixedSize(scaledSize_);

    QSize const scaledSize = pixMap.size() * zoom;

    offset = QPointF((width() - scaledSize.width()) / 2, (height() - scaledSize.height()) / 2);

    QRect const target(offset.x(), offset.y(), scaledSize.width(), scaledSize.height());

    setAttribute(Qt::WA_AcceptTouchEvents);

    QPainter painter(&pixMap);

    painter.drawPixmap(target, pixMap);

    pen.setColor(Qt::black);
    pen.setWidth(3);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);

    grabGesture(Qt::PinchGesture);
}

Canvas &Canvas::operator=(const Canvas &canvas)
{
    if (this == &canvas)
    {
        return *this;
    }

    lastPoint = canvas.lastPoint;
    secondPoint = canvas.secondPoint;
    pixMap = canvas.pixMap;
    tool = canvas.tool;
    numClik = canvas.numClik;
    zoom = canvas.zoom;
    offset = canvas.offset;
    // widthLine = canvas.widthLine;
    numOfHistory = canvas.numOfHistory;
    return *this;
}

void Canvas::paintEvent(QPaintEvent * /*event*/)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);

    QSize const scaledSize = pixMap.size() * zoom;

    QRect const target(offset.x(), offset.y(), scaledSize.width(), scaledSize.height());

    painter.drawPixmap(target, pixMap);

    if (draw && (tool == Tool::Rectangle || tool == Tool::Circle || tool == Tool::Line))
    {
        painter.setPen(pen);
        QPoint const p1(qRound(lastPoint.x() * zoom) + offset.x(), qRound(lastPoint.y() * zoom) + offset.y());
        QPoint const p2(qRound(secondPoint.x() * zoom) + offset.x(), qRound(secondPoint.y() * zoom) + offset.y());
        QRect rect(p1, p2);
        rect = rect.normalized();

        if (tool == Tool::Rectangle)
        {
            painter.drawRect(rect);
        }
        else if (tool == Tool::Circle)
        {
            painter.drawEllipse(rect);
        }
        else if (tool == Tool::Line)
        {
            painter.drawLine(p1, p2);
        }
        else if (tool == Tool::BrokenLine)
        {
            painter.drawLine(p1, p2);
            lastPoint = secondPoint;
        }
    }
    qDebug() << history.size() << "\n";
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if (!draw)
    {
        return;
    }
    QPainter painter(&pixMap);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QPoint const imgPoint = eventPosToImagePoint(event->pos());

    if (tool == Tool::Brush)
    {
        painter.setPen(pen);
        painter.drawLine(lastPoint, imgPoint);
        lastPoint = imgPoint;
    }
    else if (tool == Tool::Eraser)
    {
        painter.setPen(pen);
        painter.drawLine(lastPoint, imgPoint);
        lastPoint = imgPoint;
    }
    else
    {
        secondPoint = imgPoint;
    }

    update();
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        draw = true;
        lastPoint = eventPosToImagePoint(event->pos());
        secondPoint = lastPoint;

        if (tool == Tool::Brush)
        {
            QPainter painter(&pixMap);
            painter.setPen(pen);
            painter.setRenderHint(QPainter::Antialiasing, true);

            painter.drawPoint(lastPoint);
            update();
        }
        else if (tool == Tool::Eraser)
        {
            QPainter painter(&pixMap);
            painter.setPen(pen);
            painter.setRenderHint(QPainter::Antialiasing, true);

            painter.drawPoint(lastPoint);
            update();
        }
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (!draw || event->button() != Qt::LeftButton)
    {
        return;
    }

    draw = false;

    QPainter painter(&pixMap);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QRect rect(lastPoint, secondPoint);
    rect = rect.normalized();

    if (tool == Tool::Circle)
    {
        painter.drawEllipse(rect);
    }
    else if (tool == Tool::Rectangle)
    {
        painter.drawRect(rect);
    }
    else if (tool == Tool::Line)
    {
        painter.drawLine(lastPoint, secondPoint);
    }
    else if (tool == Tool::BrokenLine)
    {
        painter.drawLine(lastPoint, secondPoint);
        lastPoint = secondPoint;
    }
    addImageInHistory(pixMap.toImage());
    update();
}

void Canvas::setTool(Tool tool) { this->tool = tool; }

void Canvas::wheelEvent(QWheelEvent *event)
{
    int const numDegreesY = event->angleDelta().y() / 8;
    int const numStepsY = numDegreesY / 15;

    int const numDegreesX = event->angleDelta().x() / 8;
    int const numStepsX = numDegreesX / 15;

    if (zoom > 1)
    {
        if (numStepsX < 0)
        {
            offset = QPoint(offset.x() - 20, offset.y());
        }
        else if (numStepsX > 0)
        {
            offset = QPoint(offset.x() + 20, offset.y());
        }

        if (numStepsY < 0)
        {
            offset = QPoint(offset.x(), offset.y() - 20);
        }
        else if (numStepsY > 0)
        {
            offset = QPoint(offset.x(), offset.y() + 20);
        }

        clampOffset();
    }

    update();
}

auto Canvas::eventPosToImagePoint(const QPoint &point) const -> QPoint
{

    QPoint const rel = point - QPoint(offset.x(), offset.y());

    double const imgX = static_cast<double>(rel.x()) / zoom;
    double const imgY = static_cast<double>(rel.y()) / zoom;

    int const ix = qBound(0, qRound(imgX), pixMap.width() - 1);
    int const iy = qBound(0, qRound(imgY), pixMap.height() - 1);

    return {ix, iy};
}

auto Canvas::event(QEvent *e) -> bool
{
    if (e->type() == QEvent::Gesture)
    {
        return gestureEvent(dynamic_cast<QGestureEvent *>(e));
    }
    return QWidget::event(e);
}

auto Canvas::gestureEvent(QGestureEvent *event) -> bool
{
    if (QGesture *g = event->gesture(Qt::PinchGesture))
    {
        auto *pinch = dynamic_cast<QPinchGesture *>(g);
        pinchTriggered(pinch);

        event->accept(g);
    }

    return true;
}

void Canvas::pinchTriggered(QPinchGesture *pinch)
{
    qreal const factor = pinch->scaleFactor();

    if (factor > 1)
    {
        increaseZoom();
    }
    else if (factor < 1)
    {
        reduceZoom();
    }
    zoom = qBound(0.1, zoom, 10.0);

    changeOffset(true, pinch->centerPoint());
    clampOffset();

    updateGeometry();
    update();
}

void Canvas::clampOffset()
{
    QSize const scaledSize = pixMap.size() * zoom;

    if (scaledSize.width() <= width())
    {
        offset.setX((width() - scaledSize.width()) / 2);
    }
    else
    {
        int const minX = width() - scaledSize.width();
        int const maxX = 0;
        offset.setX(qBound(minX, static_cast<int>(offset.x()), maxX));
    }

    if (scaledSize.height() <= height())
    {
        offset.setY((height() - scaledSize.height()) / 2);
    }
    else
    {
        int const minY = height() - scaledSize.height();
        int const maxY = 0;
        offset.setY(qBound(minY, static_cast<int>(offset.y()), maxY));
    }
}

void Canvas::addImageInHistory(const QImage &image)
{
    if (numOfHistory + 1 < history.size())
    {
        history.resize(numOfHistory + 1);
    }

    history.push_back(image);
    numOfHistory = history.size() - 1;
}

void Canvas::takeImageWithHistory(bool forward)
{
    if (forward)
    {
        if (numOfHistory + 1 < history.size())
        {
            ++numOfHistory;
            pixMap = QPixmap::fromImage(history[numOfHistory]);
        }
    }
    else
    {
        if (numOfHistory > 0)
        {
            --numOfHistory;
            pixMap = QPixmap::fromImage(history[numOfHistory]);
        }
    }

    update();
}

void Canvas::increaseZoom()
{
    zoom *= 1.1;
    zoom = qBound(0.1, zoom, 10.0);
}

void Canvas::reduceZoom()
{
    zoom *= 0.9;
    zoom = qBound(0.1, zoom, 10.0);
}

void Canvas::changeOffset(bool isFromButton, const QPointF &point)
{
    QPointF const imgCoordBefore = (point - offset) / zoom;
    QSize const scaledSize = pixMap.size() * zoom;

    if (zoom > 1 && isFromButton)
    {

        offset = point - imgCoordBefore * zoom;
    }
    else
    {
        offset = QPointF((width() - scaledSize.width()) / 2, (height() - scaledSize.height()) / 2);
    }
    update();
}

void Canvas::changedWidth(int width) { pen.setWidth(width); }

auto Canvas::takePixmap() -> QPixmap & { return pixMap; }
