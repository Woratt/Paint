#ifndef TOOLSETTINGS_H
#define TOOLSETTINGS_H

#include <QObject>
#include <QWidget>

class ToolSettings : public QWidget
{
    Q_OBJECT
  public:
    static QColor getColor() { return s_color; };
    static int getWidth() { return s_width; };
    static Qt::PenStyle getPenStyle() { return s_penStyle; };

public slots:
    static void setColor(const QColor& color) {s_color = color; };
    static void setWidth(int width) { s_width = width; };
    static void setPenQStyle(Qt::PenStyle penStyle) { s_penStyle = penStyle; };

  private:
    static QColor s_color;
    static int s_width;
    static Qt::PenStyle s_penStyle;
};

#endif // TOOLSETTINGS_H
