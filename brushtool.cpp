#include "brushtool.h"

void BrushTool::onMousePress(const QPoint& point){
    m_lastPoint = point;
    m_isDrawing = true;

}

void BrushTool::onMouseMove(QPainter& painter, const QPoint& point){
    if(m_isDrawing){

        QPen pen(ToolSettings::getColor(), ToolSettings::getWidth(), ToolSettings::getPenStyle());
        painter.setPen(pen);
        painter.setBrush(Qt::NoBrush);

        painter.drawLine(m_lastPoint, point);
        m_lastPoint = point;
    }
}

void BrushTool::onMouseRelease(QPainter& painter, const QPoint& point){
    if(m_isDrawing){

        m_isDrawing = false;
        QPen pen(ToolSettings::getColor(), ToolSettings::getWidth(), ToolSettings::getPenStyle());
        painter.setPen(pen);
        painter.setBrush(Qt::NoBrush);

        painter.drawLine(m_lastPoint, point);
        m_lastPoint = point;
    }
}

bool BrushTool::needsPreview() const{
    return false;
}

QString BrushTool::getName() const{
    return "Brush";
}
