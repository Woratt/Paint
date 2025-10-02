#ifndef MENUPALETTE_H
#define MENUPALETTE_H

#include <QObject>
#include <QWidget>
#include <QMenu>
#include <QBoxLayout>
#include <QWidgetAction>
#include <QPushButton>
#include <QButtonGroup>

class GradientPalette;

class MenuPalette : public QMenu
{
    Q_OBJECT
  public:
    MenuPalette(QWidget* parent = nullptr);

public slots:
    void onColorSelected(const QColor&);
    void showGrid();
    void showGradient();

  private:
    QWidget *createButtons();
    QWidget* createColorGrid();
    GradientPalette* m_gradientPalette;
    QWidgetAction *toggleAction;
    QWidgetAction *gradientAction;
    QWidgetAction* gridAction;
    QWidget* buttonWidget;
  signals:
    void colorPicked(QColor);
};

#endif // MENUPALETTE_H
