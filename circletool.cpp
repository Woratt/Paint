#include "circletool.h"

void CircleTool::onMousePress(const QPoint &point)
{
    m_startPoint = point;
    m_endPoint = point;
    m_isDrawing = true;
}

void CircleTool::onMouseMove(QPainter &painter, const QPoint &point)
{
    if (m_isDrawing)
    {
        m_endPoint = point;

        QPen pen(ToolSettings::getColor(), ToolSettings::getWidth(), ToolSettings::getPenStyle());
        painter.setPen(pen);
        painter.setBrush(Qt::NoBrush);

        QRect rect(m_startPoint, m_endPoint);
        painter.drawEllipse(rect.normalized());
    }
}

void CircleTool::onMouseRelease(QPainter &painter, const QPoint &point)
{
    if (m_isDrawing)
    {
        m_endPoint = point;
        m_isDrawing = false;

        QPen pen(ToolSettings::getColor(), ToolSettings::getWidth(), ToolSettings::getPenStyle());
        painter.setPen(pen);
        painter.setBrush(Qt::NoBrush);

        QRect rect(m_startPoint, m_endPoint);
        painter.drawEllipse(rect.normalized());
    }
}

bool CircleTool::needsPreview() const { return true; }

QString CircleTool::getName() const { return "Circle"; }
