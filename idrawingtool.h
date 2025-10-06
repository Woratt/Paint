#ifndef IDRAWINGTOOL_H
#define IDRAWINGTOOL_H

#include <QWidget>
#include <QPainter>
#include <QPen>

class IDrawingTool : public QWidget{
  public:
    virtual ~IDrawingTool() = default;

    virtual void onMousePress(const QPoint&) = 0;
    virtual void onMouseMove(QPainter&, const QPoint&) = 0;
    virtual void onMouseRelease(QPainter&, const QPoint&) = 0;
    virtual QString getName() const = 0;
    virtual bool needsPreview() const = 0;
};

#endif // IDRAWINGTOOL_H
