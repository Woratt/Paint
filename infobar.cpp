#include "infobar.h"

InfoBar::InfoBar(QWidget *parent) : QStatusBar(parent)
{

    QFont font = this->font();
    font.setPointSize(16);

    zoomLabel = new QLabel("Zoom: 100%");
    cursorLabel = new QLabel();
    sizeLabel = new QLabel;
    colorLabel = new QLabel();
    textColorLabel = new QLabel("Color: ");
    QPixmap pixMap(25, 25);
    pixMap.fill(Qt::black);
    colorLabel->setPixmap(pixMap);

    addWidget(createSpacer(20));
    addWidget(sizeLabel);
    addWidget(createSpacer(40));
    addWidget(zoomLabel);
    addWidget(createSpacer(40));
    addWidget(textColorLabel);
    addWidget(colorLabel);
    addWidget(createExpandingSpacer());
    addWidget(cursorLabel);
    addWidget(createSpacer(20));

    zoomLabel->setFont(font);
    cursorLabel->setFont(font);
    sizeLabel->setFont(font);
    colorLabel->setFont(font);
    textColorLabel->setFont(font);
}

void InfoBar::updateCursor(const QPoint &point)
{
    if (point.x() < 1 || point.y() < 1 || point.x() > imgSize.width() - 2 || point.y() > imgSize.height() - 2)
    {
        cursorLabel->setText(" ");
    }
    else
    {
        cursorLabel->setText("X: " + QString::number(point.x()) + " Y: " + QString::number(point.y()));
    }
}

void InfoBar::updateColor(const QColor &color)
{
    QPixmap pixmap(30, 30);
    pixmap.fill(Qt::transparent); // Прозорий фон

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setBrush(color);
    painter.setPen(QPen(Qt::gray, 1));
    painter.drawRoundedRect(1, 1, 28, 28, 6, 6);
    colorLabel->setPixmap(pixmap);
    colorLabel->setStyleSheet("background: transparent;");
}

void InfoBar::setImageSize(const QSize &size)
{
    imgSize = size;
    sizeLabel->setText("Image size: " + QString::number(size.width()) + "X" + QString::number(size.height()));
}

void InfoBar::updateZoom(double zoom)
{
    zoomLabel->setText("Zoom: " + QString::number(static_cast<int>(zoom * 100)) + "%");
}

auto InfoBar::createSpacer(int width) -> QWidget *
{
    auto *spacer = new QWidget();
    spacer->setFixedWidth(width);
    return spacer;
}

auto InfoBar::createExpandingSpacer() -> QWidget *
{
    auto *spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    return spacer;
}
