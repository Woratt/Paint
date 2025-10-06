#include "brokenlinetool.h"

void BrokenLineTool::onMousePress(const QPoint &point)
{
    m_isDrawing = true;
    if (m_isFirstClick)
    {
        m_lastPoint = point;
        m_isFirstClick = false;
    }
}

void BrokenLineTool::onMouseMove(QPainter &painter, const QPoint &point)
{
    if (m_isDrawing)
    {

        QPen pen(ToolSettings::getColor(), ToolSettings::getWidth(), ToolSettings::getPenStyle());
        painter.setPen(pen);
        painter.setBrush(Qt::NoBrush);

        painter.drawLine(m_lastPoint, point);

        // m_lastPoint = point;
    }
}

void BrokenLineTool::onMouseRelease(QPainter &painter, const QPoint &point)
{
    if (m_isDrawing)
    {
        m_isDrawing = false;

        QPen pen(ToolSettings::getColor(), ToolSettings::getWidth(), ToolSettings::getPenStyle());
        painter.setPen(pen);
        painter.setBrush(Qt::NoBrush);

        painter.drawLine(m_lastPoint, point);

        m_lastPoint = point;
    }
}

QString BrokenLineTool::getName() const { return "BrokenLine"; }

bool BrokenLineTool::needsPreview() const { return true; }
