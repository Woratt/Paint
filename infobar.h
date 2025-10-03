#ifndef INFOBAR_H
#define INFOBAR_H

#include <QLabel>
#include <QObject>
#include <QPainter>
#include <QStatusBar>
#include <QWidget>

class InfoBar : public QStatusBar
{
    Q_OBJECT
  public:
    InfoBar(QWidget *parent = nullptr);
    void setImageSize(const QSize &);
  public slots:
    void updateZoom(double);
    void updateColor(const QColor &);
    void updateCursor(const QPoint &);

  private:
    QLabel *zoomLabel;
    QLabel *sizeLabel;
    QLabel *colorLabel;
    QLabel *cursorLabel;
    QLabel *textColorLabel;
    QSize imgSize;

    auto createSpacer(int) -> QWidget *;
    auto createExpandingSpacer() -> QWidget *;
};

#endif // INFOBAR_H
