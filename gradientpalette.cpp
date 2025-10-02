#include "gradientpalette.h"

GradientPalette::GradientPalette(QWidget* parent) : QWidget(parent) {
    setFixedSize(256, 256);
    setMouseTracking(true);
}

void GradientPalette::paintEvent(QPaintEvent* event){
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    for(int x = 0; x < width(); ++x){
        for(int y = 0; y < height(); ++y){
            QColor color;
            int hue = x * 360 / width();
            int saturation = 255;
            int value = 255 - (y * 255 / height());
            color.setHsv(hue, saturation, value);
            painter.setPen(color);
            painter.drawPoint(QPoint(x, y));
        }
    }

    painter.setPen(Qt::black);
    painter.drawRect(0, 0, width()-1, height()-1);
}

void GradientPalette::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        QColor color = getColorAtPoint(event->pos());
        emit colorSelected(color);
    }
}

void GradientPalette::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons() & Qt::LeftButton){
        QColor color = getColorAtPoint(event->pos());
        emit colorSelected(color);
    }
}

QColor GradientPalette::getColorAtPoint(const QPoint& point){
    int x = qBound(0, point.x(), width() -1);
    int y = qBound(0, point.y(), height() - 1);

    QColor color;
    int hue = x * 360 / width();
    int saturation = 255;
    int value = 255 - (y * 255) / height();
    color.setHsv(hue, saturation, value);

    return color;
}
