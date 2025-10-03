#include "menupalette.h"
#include "gradientpalette.h"
#include "colorgradientwidget.h"

MenuPalette::MenuPalette(QWidget *parent) : QMenu(parent)
{
    m_gradientPalette = new GradientPalette(this);
    setStyleSheet("QMenu {"
                  "   background-color: rgba(255, 255, 255, 200);"
                  "   border: 1px solid gray;"
                  "   padding: 10px 5px 8px 5px;"
                  "   border-radius: 8px;"
                  "}");

    gridAction = new QWidgetAction(this);
    m_gradientColor = new ColorGradientWidget(this);
    gridAction->setDefaultWidget(m_gradientColor);

    gradientAction = new QWidgetAction(this);
    gradientAction->setDefaultWidget(m_gradientPalette);

    buttonWidget = createButtons();

    toggleAction = new QWidgetAction(this);
    toggleAction->setDefaultWidget(buttonWidget);

    addAction(toggleAction);
    addAction(gridAction);

    connect(m_gradientColor, &ColorGradientWidget::colorSelected, this, &MenuPalette::onColorSelected);
    connect(m_gradientPalette, &GradientPalette::colorSelected, this, &MenuPalette::onColorSelected);
}

QWidget *MenuPalette::createButtons()
{
    QWidget *buttonWidget = new QWidget(this);
    QHBoxLayout *buttonLayout = new QHBoxLayout(buttonWidget);

    QPushButton *commonButton = new QPushButton("Common");
    QPushButton *allButton = new QPushButton("All");

    commonButton->setCheckable(true);
    allButton->setCheckable(true);

    commonButton->setChecked(true);

    QButtonGroup *buttonGroup = new QButtonGroup(this);

    buttonGroup->addButton(commonButton);
    buttonGroup->addButton(allButton);

    buttonGroup->setExclusive(true);

    buttonLayout->addWidget(commonButton);
    buttonLayout->addWidget(allButton);

    QString buttonStyle = "QPushButton {"
                          "   background-color: white;"
                          "   border: none;"
                          "   padding: 4px 8px;"
                          "   border-radius: 8px;"
                          "}"
                          "QPushButton:checked {"
                          "   background-color: #E0E0E0;"
                          "   font-weight: bold;"
                          "}"
                          "QPushButton:hover {"
                          "   background-color: #F0F0F0;"
                          "}";

    commonButton->setStyleSheet(buttonStyle);
    allButton->setStyleSheet(buttonStyle);

    connect(commonButton, &QPushButton::toggled, this, &MenuPalette::showGrid);

    connect(allButton, &QPushButton::toggled, this, &MenuPalette::showGradient);

    return buttonWidget;
}

void MenuPalette::onColorSelected(const QColor &color)
{
    emit colorPicked(color);
}

void MenuPalette::showGrid()
{
    removeAction(gradientAction);
    addAction(gridAction);
    adjustSize();
}

void MenuPalette::showGradient()
{
    removeAction(gridAction);
    addAction(gradientAction);
    adjustSize();
}
