#ifndef COLORGRADIENTWIDGET_H
#define COLORGRADIENTWIDGET_H

#include <QMouseEvent>
#include <QObject>
#include <QPainter>
#include <QWidget>

class ColorGradientWidget : public QWidget
{
    Q_OBJECT
  public:
    ColorGradientWidget(QWidget *parent = nullptr);
    QSize sizeHint() const override;
  signals:
    void colorSelected(const QColor &);

  protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;

  private:
    QColor getColorAtPos(const QPoint &);
    QVector<QColor> m_colors;
    int m_rows{12};
    int m_cols{12};
    int m_cellSize{20};
};

#endif // COLORGRADIENTWIDGET_H
