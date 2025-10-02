#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QApplication>
#include <QDir>
#include <QFile>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QToolBar>
#include <QWidgetAction>

class PaintWindow;
class FileSystem;
class Canvas;
class MenuPalette;

enum class Tool
{
    Brush,
    Rectangle,
    Circle,
    Eraser,
    Bucket,
    Line,
    BrokenLine,
};

class ToolBar : public QToolBar
{
    Q_OBJECT
  public:
    ToolBar(PaintWindow *, QWidget *parent = nullptr);

  private:
    static QPushButton *createButton(const QString &);
    static QPushButton *createFlippedButton(const QString &);
    static QWidget *createSpacer(int);
    static QWidget *createExpandingSpacer();
  signals:
    void toolSelected(Tool tool);
    void changedWidth(int Width);
};

#endif // TOOLBAR_H
