#include "colorgradientwidget.h"

ColorGradientWidget::ColorGradientWidget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(m_cols * m_cellSize, m_rows * m_cellSize);
    setMouseTracking(true);

    for (int row = 0; row < m_rows; ++row)
    {
        for (int col = 0; col < m_cols; ++col)
        {
            QColor color;
            if (row < 8)
            {
                int hue = (col * 30) % 360;
                int saturation = 255 - (row * 30);
                int value = 220;
                color.setHsv(hue, saturation, value);
            }
            else
            {
                int grayValue = 255 - (col * 20 + row * 2);
                color.setRgb(grayValue, grayValue, grayValue);
            }
            m_colors.append(color);
        }
    }
}

QSize ColorGradientWidget::sizeHint() const { return QSize(m_cols * m_cellSize, m_rows * m_cellSize); }

void ColorGradientWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    for (int i = 0; i < m_colors.size(); ++i)
    {
        int row = i / m_cols;
        int col = i % m_cols;

        QRect rect(col * m_cellSize, row * m_cellSize, m_cellSize, m_cellSize);
        painter.fillRect(rect, m_colors[i]);
        painter.setPen(Qt::gray);
        painter.drawRect(rect);
    }
}

void ColorGradientWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QColor color = getColorAtPos(event->pos());
        if (color.isValid())
        {
            emit colorSelected(color);
        }
    }
}

void ColorGradientWidget::mouseMoveEvent(QMouseEvent *event) { update(); }

QColor ColorGradientWidget::getColorAtPos(const QPoint &point)
{
    int col = point.x() / m_cellSize;
    int row = point.y() / m_cellSize;

    if (row >= 0 && row < m_rows && col >= 0 && col < m_cols)
    {
        int index = row * m_cols + col;
        if (index < m_colors.size())
        {
            return m_colors[index];
        }
    }
    return QColor();
}
