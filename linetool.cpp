#include "linetool.h"

void LineTool::onMousePress(const QPoint &point)
{
    m_startPoint = point;
    m_endPoint = point;
    m_isDrawing = true;
}

void LineTool::onMouseMove(QPainter &painter, const QPoint &point)
{
    if (m_isDrawing)
    {
        m_endPoint = point;

        QPen pen(ToolSettings::getColor(), ToolSettings::getWidth(), ToolSettings::getPenStyle());
        painter.setPen(pen);
        painter.setBrush(Qt::NoBrush);

        painter.drawLine(m_startPoint, m_endPoint);
    }
}

void LineTool::onMouseRelease(QPainter &painter, const QPoint &point)
{
    if (m_isDrawing)
    {
        m_endPoint = point;
        m_isDrawing = false;

        QPen pen(ToolSettings::getColor(), ToolSettings::getWidth(), ToolSettings::getPenStyle());
        painter.setPen(pen);
        painter.setBrush(Qt::NoBrush);

        painter.drawLine(m_startPoint, m_endPoint);
    }
}

QString LineTool::getName() const { return "Line"; }

bool LineTool::needsPreview() const { return true; }
