#ifndef BRUSHTOOL_H
#define BRUSHTOOL_H

#include "idrawingtool.h"
#include "toolsettings.h"
#include <QObject>
#include <QWidget>

class BrushTool : public IDrawingTool
{
    Q_OBJECT
  public:
    BrushTool() = default;
    void onMousePress(const QPoint &) override;
    void onMouseMove(QPainter &, const QPoint &) override;
    void onMouseRelease(QPainter &, const QPoint &) override;
    QString getName() const override;
    bool needsPreview() const override;

  private:
    QPoint m_lastPoint;
    bool m_isDrawing{false};
};

#endif // BRUSHTOOL_H
