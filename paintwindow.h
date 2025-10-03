#ifndef USERS_ADMIN_DOWNLOADS_EDUCATION_PAINT_PAINTWINDOW_H
#define USERS_ADMIN_DOWNLOADS_EDUCATION_PAINT_PAINTWINDOW_H

#include <QAction>
#include <QMainWindow>
#include <QMenuBar>
#include <QMouseEvent>
#include <QPainter>
#include <QScrollArea>
#include <QToolBar>

class MenuBar;
class ToolBar;
class Canvas;
class createFileWindow;
class InfoBar;

class PaintWindow : public QMainWindow
{
    Q_OBJECT

  public:
    PaintWindow(const QImage &, const QString &, QWidget *parent = nullptr);
    auto takeCanvas() -> Canvas *;

    PaintWindow(const PaintWindow &) = delete;
    auto operator=(const PaintWindow &) -> PaintWindow & = delete;
    PaintWindow(PaintWindow &&) = delete;
    auto operator=(PaintWindow &&) -> PaintWindow & = delete;

    ~PaintWindow() override;

  protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

  private:
    QPoint lastPoint;
    bool drawing = false;
    MenuBar *menu;
    Canvas *canvas;
    ToolBar *toolBar;
};
#endif // USERS_ADMIN_DOWNLOADS_EDUCATION_PAINT_PAINTWINDOW_H
