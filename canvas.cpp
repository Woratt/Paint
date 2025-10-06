#include "canvas.h"
#include "infobar.h"
#include "menupalette.h"
#include "toolbar.h"
#include "infobar.h"

Canvas::Canvas(QWidget *parent) : QWidget(parent) {}

Canvas::Canvas(const QImage &image, QWidget *parent) : QWidget(parent)
{
    history.push_back(image);
    m_pixMap = QPixmap::fromImage(image);
    QSize const imageSize = image.size();

    QSize const targetSize_(1280, 720);

    QSize const scaledSize_ = imageSize.scaled(targetSize_, Qt::KeepAspectRatio);

    setFixedSize(scaledSize_);

    QSize const scaledSize = m_pixMap.size() * m_zoom;

    m_offset = QPointF((width() - scaledSize.width()) / 2, (height() - scaledSize.height()) / 2);

    QRect const target(m_offset.x(), m_offset.y(), scaledSize.width(), scaledSize.height());

    setAttribute(Qt::WA_AcceptTouchEvents);

    QPainter painter(&m_pixMap);

    painter.drawPixmap(target, m_pixMap);

    pen.setColor(Qt::black);
    pen.setWidth(3);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);

    grabGesture(Qt::PinchGesture);

    setMouseTracking(true);
}

Canvas &Canvas::operator=(const Canvas &canvas)
{
    if (this == &canvas)
    {
        return *this;
    }

    m_pixMap = canvas.m_pixMap;
    numClik = canvas.numClik;
    m_zoom = canvas.m_zoom;
    m_offset = canvas.m_offset;
    // widthLine = canvas.widthLine;
    numOfHistory = canvas.numOfHistory;
    return *this;
}

void Canvas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QSize scaledSize = m_pixMap.size() * m_zoom;
    QRect targetRect(m_offset.x(), m_offset.y(), scaledSize.width(), scaledSize.height());
    painter.drawPixmap(targetRect, m_pixMap);

    if(!m_previewPixmap.isNull()) {
        painter.drawPixmap(targetRect, m_previewPixmap);
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    emit updateCursor(eventPosToImagePoint(event->pos()));

    if(m_currentTool && (event->buttons() & Qt::LeftButton)) {
        QPoint point = eventPosToImagePoint(event->pos());
        if(m_currentTool->needsPreview()){
            m_previewPixmap.fill(Qt::transparent);
            QPainter painter(&m_previewPixmap);
            m_currentTool->onMouseMove(painter, point);
        }else{
            QPainter painter(&m_pixMap);
            m_currentTool->onMouseMove(painter, point);
        }

        update();
    }
}


void Canvas::mousePressEvent(QMouseEvent *event)
{
    if(m_currentTool && (event->button() == Qt::LeftButton)){
        QPoint point = eventPosToImagePoint(event->pos());

        m_previewPixmap = QPixmap(m_pixMap.size());
        m_previewPixmap.fill(Qt::transparent);

        m_currentTool->onMousePress(point);
        update();
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    if(m_currentTool && event->button() == Qt::LeftButton){
        QPoint point = eventPosToImagePoint(event->pos());

        QPainter painter(&m_pixMap);
        m_currentTool->onMouseRelease(painter, point);

        m_previewPixmap = QPixmap();

        addImageInHistory(m_pixMap.toImage());
        update();
    }
}

//void Canvas::setTool(Tool tool) { this->tool = tool; }

void Canvas::wheelEvent(QWheelEvent *event)
{
    int const numDegreesY = event->angleDelta().y() / 8;
    int const numStepsY = numDegreesY / 15;

    int const numDegreesX = event->angleDelta().x() / 8;
    int const numStepsX = numDegreesX / 15;

    if (m_zoom > 1)
    {
        if (numStepsX < 0)
        {
            m_offset = QPoint(m_offset.x() - 20, m_offset.y());
        }
        else if (numStepsX > 0)
        {
            m_offset = QPoint(m_offset.x() + 20, m_offset.y());
        }

        if (numStepsY < 0)
        {
            m_offset = QPoint(m_offset.x(), m_offset.y() - 20);
        }
        else if (numStepsY > 0)
        {
            m_offset = QPoint(m_offset.x(), m_offset.y() + 20);
        }

        clampOffset();
    }

    update();
}

auto Canvas::eventPosToImagePoint(const QPoint &point) const -> QPoint
{

    QPoint const rel = point - QPoint(m_offset.x(), m_offset.y());

    double const imgX = static_cast<double>(rel.x()) / m_zoom;
    double const imgY = static_cast<double>(rel.y()) / m_zoom;

    int const ix = qBound(0, qRound(imgX), m_pixMap.width() - 1);
    int const iy = qBound(0, qRound(imgY), m_pixMap.height() - 1);

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
    qreal factor = pinch->scaleFactor();

    QSize scaledSize = m_pixMap.size() * m_zoom;
    QPointF cursorPos = pinch->centerPoint();
    QPointF imgCoordBefore = (cursorPos - m_offset) / m_zoom;

    if (factor > 1)
    {
        m_zoom *= 1.1;
    }
    else if (factor < 1)
    {

        m_zoom *= 0.9;
    }
    m_zoom = qBound(0.1, m_zoom, 10.0);

    if (m_zoom > 1)
    {

        m_offset = cursorPos - imgCoordBefore * m_zoom;
    }
    else
    {
        m_offset = QPointF((width() - scaledSize.width()) / 2, (height() - scaledSize.height()) / 2);
    }

    emit updateZoom(m_zoom);

    clampOffset();

    updateGeometry();
    update();
}

void Canvas::clampOffset()
{
    QSize const scaledSize = m_pixMap.size() * m_zoom;

    if (scaledSize.width() <= width())
    {
        m_offset.setX((width() - scaledSize.width()) / 2);
    }
    else
    {
        int const minX = width() - scaledSize.width();
        int const maxX = 0;
        m_offset.setX(qBound(minX, static_cast<int>(m_offset.x()), maxX));
    }

    if (scaledSize.height() <= height())
    {
        m_offset.setY((height() - scaledSize.height()) / 2);
    }
    else
    {
        int const minY = height() - scaledSize.height();
        int const maxY = 0;
        m_offset.setY(qBound(minY, static_cast<int>(m_offset.y()), maxY));
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
            m_pixMap = QPixmap::fromImage(history[numOfHistory]);
        }
    }
    else
    {
        if (numOfHistory > 0)
        {
            --numOfHistory;
            m_pixMap = QPixmap::fromImage(history[numOfHistory]);
        }
    }

    update();
}

void Canvas::increaseZoom()
{
    m_zoom *= 1.1;
    m_zoom = qBound(0.1, m_zoom, 10.0);

    emit updateZoom(m_zoom);
}

void Canvas::reduceZoom()
{
    m_zoom *= 0.9;
    m_zoom = qBound(0.1, m_zoom, 10.0);

    emit updateZoom(m_zoom);
}

void Canvas::changeOffset(bool isFromButton, const QPointF &point)
{
    if (isFromButton && m_zoom > 1) {
        QPointF imgCoordBefore = (point - m_offset) / m_zoom;
        QSize scaledSize = m_pixMap.size() * m_zoom;
        m_offset = point - imgCoordBefore * m_zoom;
    } else {
        QSize scaledSize = m_pixMap.size() * m_zoom;
        m_offset = QPointF((width() - scaledSize.width()) / 2, (height() - scaledSize.height()) / 2);
    }

    clampOffset();
    update();
}

void Canvas::changedWidth(int width) { pen.setWidth(width); }

void Canvas::setColorPen(QColor color){
    pen.setColor(color);

    emit updateColor(color);
}

void Canvas::setTool(ToolType type){
    m_currentToolType = type;
    m_currentTool = ToolFactory::createTool(type);
}

ToolType Canvas::getToolType(){
    return m_currentToolType;
}

auto Canvas::takePixmap() -> QPixmap & { return m_pixMap; }
