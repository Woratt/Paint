#ifndef CIRCLETOOL_H
#define CIRCLETOOL_H

#include <QObject>
#include <QWidget>

#include "idrawingtool.h"
#include "toolsettings.h"

class CircleTool : public IDrawingTool
{
    Q_OBJECT
  public:
    CircleTool() = default;
    void onMousePress(const QPoint&) override;
    void onMouseMove(QPainter&, const QPoint&) override;
    void onMouseRelease(QPainter&, const QPoint&) override;
    QString getName() const override;
    bool needsPreview() const override;
  private:
    QPoint m_startPoint;
    QPoint m_endPoint;
    bool m_isDrawing{false};
};

#endif // CIRCLETOOL_H
