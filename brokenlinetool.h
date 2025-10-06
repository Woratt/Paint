#ifndef BROKENLINETOOL_H
#define BROKENLINETOOL_H

#include <QObject>
#include <QWidget>

#include "idrawingtool.h"
#include "toolsettings.h"

class BrokenLineTool : public IDrawingTool
{
    Q_OBJECT
  public:
    BrokenLineTool() = default;
    void onMousePress(const QPoint&) override;
    void onMouseMove(QPainter&, const QPoint&) override;
    void onMouseRelease(QPainter&, const QPoint&) override;
    QString getName() const override;
    bool needsPreview() const override;
  private:
    QPoint m_lastPoint;
    bool m_isDrawing{false};
    bool m_isFirstClick{true};
};

#endif // BROKENLINETOOL_H
