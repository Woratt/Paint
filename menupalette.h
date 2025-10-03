#ifndef MENUPALETTE_H
#define MENUPALETTE_H

#include <QBoxLayout>
#include <QButtonGroup>
#include <QMenu>
#include <QObject>
#include <QPushButton>
#include <QWidget>
#include <QWidgetAction>

class GradientPalette;
class ColorGradientWidget;

class MenuPalette : public QMenu
{
    Q_OBJECT
  public:
    MenuPalette(QWidget *parent = nullptr);

  public slots:
    void onColorSelected(const QColor &);
    void showGrid();
    void showGradient();

  private:
    QWidget *createButtons();
    GradientPalette *m_gradientPalette;
    ColorGradientWidget *m_gradientColor;
    QWidgetAction *toggleAction;
    QWidgetAction *gradientAction;
    QWidgetAction *gridAction;
    QWidget *buttonWidget;
  signals:
    void colorPicked(QColor);
};

#endif // MENUPALETTE_H
