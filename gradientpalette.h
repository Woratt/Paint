#ifndef GRADIENTPALETTE_H
#define GRADIENTPALETTE_H

#include <QColor>
#include <QMouseEvent>
#include <QObject>
#include <QPaintEvent>
#include <QPainter>
#include <QWidget>

class GradientPalette : public QWidget
{
    Q_OBJECT
  public:
    explicit GradientPalette(QWidget *parent = nullptr);
    QSize sizeHint() const override { return QSize(256, 256); }
  signals:
    void colorSelected(const QColor &);

  protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;

  private:
    QColor getColorAtPoint(const QPoint &);
};

#endif // GRADIENTPALETTE_H
