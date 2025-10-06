#ifndef BUCKETTOOL_H
#define BUCKETTOOL_H

#include <QObject>
#include <QStack>
#include <QWidget>

#include "idrawingtool.h"
#include "toolsettings.h"

class BucketTool : public IDrawingTool
{
    Q_OBJECT
  public:
    BucketTool() = default;
    void onMousePress(const QPoint &point) override;
    void onMouseMove(QPainter &, const QPoint &) override;
    void onMouseRelease(QPainter &, const QPoint &) override;
    QString getName() const override;
    bool needsPreview() const override;

  private:
    void floodFill(QImage &image, const QPoint &startPoint, QRgb targetColor, QRgb replacementColor);
    QColor m_fillColor{Qt::black};
};

#endif // BUCKETTOOL_H
