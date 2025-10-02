#include "menupalette.h"
#include "gradientpalette.h"

MenuPalette::MenuPalette(QWidget *parent) : QMenu(parent)
{
    m_gradientPalette = new GradientPalette(this);
    QWidget *colorGrid = createColorGrid();
    setStyleSheet("QMenu {"
                  "   background-color: rgba(255, 255, 255, 200);"
                  "   border: 1px solid gray;"
                  "   padding: 10px 5px 8px 5px;"
                  "   border-radius: 8px;"
                  "}");

    gridAction = new QWidgetAction(this);
    gridAction->setDefaultWidget(colorGrid);

    gradientAction = new QWidgetAction(this);
    gradientAction->setDefaultWidget(m_gradientPalette);

    buttonWidget = createButtons();

    toggleAction = new QWidgetAction(this);
    toggleAction->setDefaultWidget(buttonWidget);

    addAction(toggleAction);
    addAction(gridAction);
}

QWidget *MenuPalette::createColorGrid()
{
    QWidget *widget = new QWidget();
    QGridLayout *gridLayout = new QGridLayout(widget);

    gridLayout->setSpacing(1);
    gridLayout->setContentsMargins(2, 2, 2, 2);

    QList<QColor> colors;
    for (int x = 0; x < 12; ++x)
    {
        for (int y = 0; y < 12; ++y)
        {
            QColor color;
            if (x < 8)
            {
                int hue = (y * 30) % 360;
                int saturation = 255 - (x * 30);
                int value = 220;
                color.setHsv(hue, saturation, value);
            }
            else
            {
                // Відтінки сірого
                int grayValue = 255 - (y * 20 + x * 2);
                color.setRgb(grayValue, grayValue, grayValue);
            }
            colors.push_back(color);
        }
    }

    for (int i = 0; i < colors.size(); ++i)
    {
        QPushButton *bt = new QPushButton(this);
        bt->setFixedSize(20, 20);

        QString colorName = colors[i].name();
        bt->setStyleSheet(QString("QPushButton { background-color: %1; border: 1px rgba(255, 255, 255, 200); }"
                                  "QPushButton:hover { border: 2px solid white; }")
                              .arg(colorName));

        bt->setProperty("color", colorName);
        int row = i / 12;
        int col = i % 12;
        gridLayout->addWidget(bt, row, col);

        connect(bt, &QPushButton::clicked, this, &MenuPalette::onColorSelected);
    }

    return widget;
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
    QPushButton *bt = qobject_cast<QPushButton *>(sender());
    if (bt)
    {
        QString colorName = bt->property("color").toString();

        QColor color(colorName);

        emit colorPicked(color);
    }
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
