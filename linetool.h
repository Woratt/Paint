#ifndef LINETOOL_H
#define LINETOOL_H

#include <QObject>
#include <QWidget>

#include "idrawingtool.h"
#include "toolsettings.h"

class LineTool : public IDrawingTool
{
    Q_OBJECT
  public:
    LineTool() = default;
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

#endif // LINETOOL_H
