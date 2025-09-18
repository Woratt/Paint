#include "paintwindow.h"

PaintWindow::PaintWindow(QImage image, const QString& name, QWidget *parent)
    : QMainWindow(parent)
{
    QWidget* central = new QWidget(this);

    setCentralWidget(central);

    setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);

    showFullScreen();

    QVBoxLayout* VCentralLayout = new QVBoxLayout(central);

    VCentralLayout->setContentsMargins(0,0,0,0);

    toolBar = new ToolBar(this);
    addToolBar(toolBar);

    menu = new MenuBar(name, this);

    canvas = new Canvas(image);
    QScrollArea* scrollArea = new QScrollArea;
    scrollArea->setWidget(canvas);
    scrollArea->setAlignment(Qt::AlignCenter);

    VCentralLayout->addWidget(scrollArea);

    connect(toolBar, &ToolBar::toolSelected, this, [=](Tool tool){
        canvas->setTool(tool);
    });

    connect(toolBar, &ToolBar::changedWidth, canvas, &Canvas::changedWidth);
}


void PaintWindow::paintEvent(QPaintEvent *event){

}

void PaintWindow::mousePressEvent(QMouseEvent* event){
    if(event->button() == Qt::LeftButton){
        qDebug() << "Left Button pressed";
        drawing = true;
        lastPoint = event->pos();

    }else if(event->button() == Qt::RightButton){
        qDebug() << "Right Button preseed";
    }
}

void PaintWindow::mouseMoveEvent(QMouseEvent* event){
}

void PaintWindow::mouseReleaseEvent(QMouseEvent* event){

}

Canvas* PaintWindow::takeCanvas(){
    return canvas;
};


PaintWindow::~PaintWindow() {
    delete menu;
}
