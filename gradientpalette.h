#ifndef GRADIENTPALETTE_H
#define GRADIENTPALETTE_H

#include <QObject>
#include <QWidget>
#include <QColor>
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>

class GradientPalette : public QWidget
{
    Q_OBJECT
  public:
    explicit GradientPalette(QWidget* parent = nullptr);
    QSize sizeHint() const override {return QSize(256, 256);}
signals:
    void colorSelected(const QColor&);
protected:
    void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;

  private:
    QColor getColorAtPoint(const QPoint&);


};

#endif // GRADIENTPALETTE_H
