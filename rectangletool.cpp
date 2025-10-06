#include "rectangletool.h"
#include <QPainter>

void RectangleTool::onMousePress(const QPoint &point)
{
    m_startPoint = point;
    m_endPoint = point;
    m_isDrawing = true;
}

void RectangleTool::onMouseMove(QPainter &painter, const QPoint &point)
{
    if (m_isDrawing)
    {
        m_endPoint = point;

        QPen pen(ToolSettings::getColor(), ToolSettings::getWidth(), ToolSettings::getPenStyle());
        painter.setPen(pen);
        painter.setBrush(Qt::NoBrush);

        QRect rect(m_startPoint, m_endPoint);
        painter.drawRect(rect.normalized());
    }
}

void RectangleTool::onMouseRelease(QPainter &painter, const QPoint &point)
{
    if (m_isDrawing)
    {
        m_endPoint = point;
        m_isDrawing = false;

        QPen pen(ToolSettings::getColor(), ToolSettings::getWidth(), ToolSettings::getPenStyle());
        painter.setPen(pen);
        painter.setBrush(Qt::NoBrush);

        QRect finalRect(m_startPoint, m_endPoint);
        painter.drawRect(finalRect.normalized());
    }
}

bool RectangleTool::needsPreview() const { return true; }

QString RectangleTool::getName() const { return "Rectangle"; }
