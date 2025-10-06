#include "erasertool.h"

void EraserTool::onMousePress(const QPoint& point){
    m_lastPoint = point;
    m_isDrawing = true;
}

void EraserTool::onMouseMove(QPainter& painter, const QPoint& point){
    if(m_isDrawing){

        QPen pen(Qt::white, ToolSettings::getWidth());
        painter.setPen(pen);
        painter.setBrush(Qt::NoBrush);

        painter.drawLine(m_lastPoint, point);
        m_lastPoint = point;
    }
}

void EraserTool::onMouseRelease(QPainter& painter, const QPoint& point){
    if(m_isDrawing){
        m_isDrawing = false;

        QPen pen(Qt::white, ToolSettings::getWidth());
        painter.setPen(pen);
        painter.setBrush(Qt::NoBrush);

        painter.drawLine(m_lastPoint, point);
        m_lastPoint = point;
    }
}

QString EraserTool::getName() const{
    return "Eraser";
}

bool EraserTool::needsPreview() const{
    return false;
}
