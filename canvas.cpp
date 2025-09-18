#include "canvas.h"

QVector<QImage> history;

Canvas::Canvas(const QImage& image, QWidget* parent) : QWidget(parent) {
    history.push_back(image);
    pixMap = QPixmap::fromImage(image);
    QSize imageSize = image.size();

    QSize targetSize_(1280, 720);

    QSize scaledSize_ = imageSize.scaled(targetSize_, Qt::KeepAspectRatio);

    setFixedSize(scaledSize_);

    QSize scaledSize = pixMap.size() * zoom;

    offset = QPointF((width() - scaledSize.width()) / 2, (height() - scaledSize.height()) / 2);

    QRect target(offset.x(), offset.y(), scaledSize.width(), scaledSize.height());

    setAttribute(Qt::WA_AcceptTouchEvents);

    QPainter painter(&pixMap);

    painter.drawPixmap(target, pixMap);


    grabGesture(Qt::PinchGesture);
}

void Canvas::paintEvent(QPaintEvent* event){
    QPainter painter(this);
    QSize scaledSize = pixMap.size() * zoom;

    QRect target(offset.x(), offset.y(), scaledSize.width(), scaledSize.height());

    painter.drawPixmap(target, pixMap);

    if(draw && (tool == Tool::Rectangle || tool == Tool::Circle || tool == Tool::Line)){
        painter.setPen(QPen(Qt::black, widthLine));
        QPoint p1(qRound(lastPoint.x() * zoom) + offset.x(), qRound(lastPoint.y() * zoom) + offset.y());
        QPoint p2(qRound(secondPoint.x() * zoom) + offset.x(), qRound(secondPoint.y() * zoom) + offset.y());
        QRect rect(p1, p2);
        rect = rect.normalized();

        if(tool == Tool::Rectangle){
            painter.drawRect(rect);
        }else if(tool == Tool::Circle){
            painter.drawEllipse(rect);
        }else if(tool == Tool::Line){
            painter.drawLine(p1, p2);
        }else if(tool == Tool::BrokenLine){
            painter.drawLine(p1, p2);
            lastPoint = secondPoint;
        }
    }
    qDebug() << history.size() << "\n";
}

void Canvas::mouseMoveEvent(QMouseEvent* event){
    if(!draw) return;
    QPainter painter(&pixMap);

    QPoint imgPoint = eventPosToImagePoint(event->pos());

    if(tool == Tool::Brush){
        painter.setPen(QPen(Qt::black, widthLine));
        painter.drawLine(lastPoint, imgPoint);
        lastPoint = imgPoint;
    }else if(tool == Tool::Eraser){
        painter.setPen(QPen(Qt::white, widthLine));
        painter.drawLine(lastPoint, imgPoint);
        lastPoint = imgPoint;
    }else{
        secondPoint = imgPoint;
    }

    update();
}

void Canvas::mousePressEvent(QMouseEvent* event){
    if(event->button() == Qt::LeftButton){
        draw = true;
        lastPoint = eventPosToImagePoint(event->pos());
        secondPoint = lastPoint;

        if(tool == Tool::Brush){
            QPainter painter(&pixMap);
            painter.setPen(QPen(Qt::black, widthLine));

            painter.drawPoint(lastPoint);
            update();
        }else if(tool == Tool::Eraser){
            QPainter painter(&pixMap);
            painter.setPen(QPen(Qt::white, widthLine));

            painter.drawPoint(lastPoint);
            update();
        }
    }

}

void Canvas::mouseReleaseEvent(QMouseEvent* event){

    if (!draw || event->button() != Qt::LeftButton) return;

    draw = false;

    QPainter painter(&pixMap);
    painter.setPen(QPen(Qt::black, widthLine));

    QRect rect(lastPoint, secondPoint);
    rect = rect.normalized();

    if(tool == Tool::Circle){
        painter.drawEllipse(rect);
    }else if(tool == Tool::Rectangle){
        painter.drawRect(rect);
    }else if(tool == Tool::Line){
        painter.drawLine(lastPoint, secondPoint);
    }else if(tool == Tool::BrokenLine){
        painter.drawLine(lastPoint, secondPoint);
        lastPoint = secondPoint;
    }
    addImageInHistory(pixMap.toImage());
    update();
}

void Canvas::setTool(Tool tool){
    this->tool = tool;
}

void Canvas::wheelEvent(QWheelEvent* event){
    int numDegreesY = event->angleDelta().y() / 8;
    int numStepsY = numDegreesY / 15;

    int numDegreesX = event->angleDelta().x() / 8;
    int numStepsX = numDegreesX / 15;

    if(zoom > 1){
        if(numStepsX < 0){
            offset = QPoint(offset.x() - 20, offset.y());
        }else if(numStepsX > 0){
            offset = QPoint(offset.x() + 20, offset.y());
        }

        if(numStepsY < 0){
            offset = QPoint(offset.x(), offset.y() - 20);
        }else if(numStepsY > 0){
            offset = QPoint(offset.x(), offset.y() + 20);
        }

        clampOffset();
    }

    update();
}

QPoint Canvas::eventPosToImagePoint(const QPoint& point) const{

    QPoint rel = point - QPoint(offset.x(), offset.y());

    double imgX = double(rel.x()) / zoom;
    double imgY = double(rel.y()) / zoom;

    int ix = qBound(0, qRound(imgX), pixMap.width() - 1);
    int iy = qBound(0, qRound(imgY), pixMap.height() - 1);

    return QPoint(ix, iy);
}

bool Canvas::event(QEvent* e){
    if(e->type() == QEvent::Gesture){
        return gestureEvent(static_cast<QGestureEvent*>(e));
    }
    return QWidget::event(e);
}

bool Canvas::gestureEvent(QGestureEvent* event){
    if(QGesture* g = event->gesture(Qt::PinchGesture)){
        QPinchGesture* pinch = static_cast<QPinchGesture*>(g);
        pinchTriggered(pinch);

        event->accept(g);
    }

    return true;
}

void Canvas::pinchTriggered(QPinchGesture* pinch){
    qreal factor = pinch->scaleFactor();

    QSize scaledSize = pixMap.size() * zoom;
    QPointF cursorPos = pinch->centerPoint();
    QPointF imgCoordBefore = (cursorPos - offset) / zoom;

    if(factor > 1){
        zoom *= 1.1;
    }else if(factor < 1){

        zoom *= 0.9;
    }
    zoom = qBound(0.1, zoom, 10.0);

    if(zoom > 1){

        offset = cursorPos - imgCoordBefore * zoom;
    }else{
        offset = QPointF((width() - scaledSize.width()) / 2, (height() - scaledSize.height()) / 2);
    }

    clampOffset();

    updateGeometry();
    update();
}

void Canvas::clampOffset(){
    QSize scaledSize = pixMap.size() * zoom;

    if (scaledSize.width() <= width()) {
        offset.setX((width() - scaledSize.width()) / 2);
    } else {
        int minX = width() - scaledSize.width();
        int maxX = 0;
        offset.setX(qBound(minX, int(offset.x()), maxX));
    }

    if (scaledSize.height() <= height()) {
        offset.setY((height() - scaledSize.height()) / 2);
    } else {
        int minY = height() - scaledSize.height();
        int maxY = 0;
        offset.setY(qBound(minY, int(offset.y()), maxY));
    }
}

void Canvas::addImageInHistory(const QImage& image) {
    // якщо ми зробили undo і почали малювати далі — видаляємо всі "майбутні" стани
    if (numOfHistory + 1 < history.size()) {
        history.resize(numOfHistory + 1);
    }

    history.push_back(image);
    numOfHistory = history.size() - 1; // тепер вказуємо на останній елемент
}

void Canvas::takeImageWithHistory(bool forward) {
    if (forward) { // redo
        if (numOfHistory + 1 < history.size()) {
            ++numOfHistory;
            pixMap = QPixmap::fromImage(history[numOfHistory]);
        }
    } else { // undo
        if (numOfHistory > 0) {
            --numOfHistory;
            pixMap = QPixmap::fromImage(history[numOfHistory]);
        }
    }

    update();
}

void Canvas::changedWidth(int width){
    widthLine = width;
}

QPixmap& Canvas::takePixmap(){
    return pixMap;
}
