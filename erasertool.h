#ifndef ERASERTOOL_H
#define ERASERTOOL_H

#include <QObject>
#include <QWidget>

#include "idrawingtool.h"
#include "toolsettings.h"

class EraserTool : public IDrawingTool
{
    Q_OBJECT
  public:
    void onMousePress(const QPoint&) override;
    void onMouseMove(QPainter&, const QPoint&) override;
    void onMouseRelease(QPainter&, const QPoint&) override;
    QString getName() const override;
    bool needsPreview() const override;
  private:
    QPoint m_lastPoint;
    bool m_isDrawing{false};
};

#endif // ERASERTOOL_H
