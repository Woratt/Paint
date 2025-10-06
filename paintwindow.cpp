#include "paintwindow.h"
#include "canvas.h"
#include "createfilewindow.h"
#include "infobar.h"
#include "menubar.h"
#include "toolbar.h"

PaintWindow::PaintWindow(const QImage &image, const QString &name, QWidget *parent)
    : QMainWindow(parent), toolBar(new ToolBar(this)), menu(new MenuBar(name, this)), canvas(new Canvas(image))
{
    auto *central = new QWidget(this);

    setCentralWidget(central);

    setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);

    showFullScreen();

    auto *VCentralLayout = new QVBoxLayout(central);

    VCentralLayout->setContentsMargins(0, 0, 0, 0);

    addToolBar(toolBar);

    auto *scrollArea = new QScrollArea;
    scrollArea->setWidget(canvas);
    scrollArea->setAlignment(Qt::AlignCenter);

    InfoBar *bar = new InfoBar();
    bar->setImageSize(image.size());
    QWidget *widgetBar = new QWidget(this);

    VCentralLayout->addWidget(scrollArea, 10);
    VCentralLayout->addWidget(bar, 1);


    //connect(toolBar, &ToolBar::changedWidth, canvas, &Canvas::changedWidth);

    connect(canvas, &Canvas::updateZoom, bar, &InfoBar::updateZoom);
    //connect(canvas, &Canvas::updateColor, bar, &InfoBar::updateColor);
    connect(canvas, &Canvas::updateCursor, bar, &InfoBar::updateCursor);
    connect(toolBar, &ToolBar::changeColor, this, &ToolSettings::setColor);
    connect(toolBar, &ToolBar::changedWidth, this, &ToolSettings::setWidth);

    connect(toolBar, &ToolBar::changeColor, bar, &InfoBar::updateColor);

    //connect(toolBar, &ToolBar::changedWidth)
}

void PaintWindow::paintEvent(QPaintEvent *event) {}

void PaintWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        qDebug() << "Left Button pressed";
        drawing = true;
        lastPoint = event->pos();
    }
    else if (event->button() == Qt::RightButton)
    {
        qDebug() << "Right Button preseed";
    }
}

void PaintWindow::mouseMoveEvent(QMouseEvent *event) {}

void PaintWindow::mouseReleaseEvent(QMouseEvent *event) {}

auto PaintWindow::takeCanvas() -> Canvas * { return canvas; };

PaintWindow::~PaintWindow() { delete menu; }
