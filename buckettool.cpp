#include "buckettool.h"

void BucketTool::onMousePress(const QPoint &) {}

void BucketTool::onMouseMove(QPainter &, const QPoint &) {}

QString BucketTool::getName() const { return "Bucket"; }

bool BucketTool::needsPreview() const { return false; }

void BucketTool::onMouseRelease(QPainter &painter, const QPoint &point)
{
    QPaintDevice *device = painter.device();

    if (!device)
        return;

    QPixmap *pixmap = dynamic_cast<QPixmap *>(device);

    // QImage* image = dynamic_cast<QImage*>(device);

    // if(image->isNull()) return;
    if (pixmap)
    {
        QImage image = pixmap->toImage();
        if (image.isNull())
            return;

        m_fillColor = ToolSettings::getColor();

        QRgb targetPixel = image.pixel(point);
        QColor color = QColor::fromRgb(targetPixel);

        if (qAlpha(targetPixel) == qAlpha(m_fillColor.rgba()) && qRed(targetPixel) == m_fillColor.red() &&
            qGreen(targetPixel) == m_fillColor.green() && qBlue(targetPixel) == m_fillColor.blue())
        {
            return; // Такий самий колір
        }

        floodFill(image, point, targetPixel, m_fillColor.rgba());

        painter.drawImage(0, 0, image);
    }
}

void BucketTool::floodFill(QImage &image, const QPoint &startPoint, QRgb targetColor, QRgb replacementColor)
{
    int width = image.width();
    int height = image.height();

    if (startPoint.x() < 0 || startPoint.x() >= width || startPoint.y() < 0 || startPoint.y() >= height)
    {
        return;
    }

    // Перевіряємо за значенням RGB (без альфа-каналу для порівняння)
    QRgb startPixel = image.pixel(startPoint);
    if ((startPixel & 0x00FFFFFF) != (targetColor & 0x00FFFFFF))
    {
        return;
    }

    QStack<QPoint> stack;
    stack.push(startPoint);
    QSet<QPoint> visited;

    while (!stack.isEmpty())
    {
        QPoint p = stack.pop();

        if (p.x() < 0 || p.x() >= width || p.y() < 0 || p.y() >= height)
            continue;
        if (visited.contains(p))
            continue;

        QRgb currentPixel = image.pixel(p);

        // Порівнюємо тільки RGB (без альфа-каналу)
        if ((currentPixel & 0x00FFFFFF) != (targetColor & 0x00FFFFFF))
            continue;

        image.setPixel(p, replacementColor);
        visited.insert(p);

        stack.push(QPoint(p.x() + 1, p.y()));
        stack.push(QPoint(p.x() - 1, p.y()));
        stack.push(QPoint(p.x(), p.y() + 1));
        stack.push(QPoint(p.x(), p.y() - 1));
    }
};
