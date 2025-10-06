#ifndef _H
#define _H

#include <QObject>
#include <QPainter>

class IDrawingTool : public QObject
{
    Q_OBJECT
  public:
    virtual ~IDrawingTool() = default;

    virtual void onMousePress(QPainter &, const QPoint &) = 0;
    virtual void onMouseMove(QPainter &, const QPoint &) = 0;
    virtual void onMouseRelease(QPainter &, const QPoint &) = 0;

    virtual QString getName() const = 0;
};

#endif // _H
