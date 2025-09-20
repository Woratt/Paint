#include "toolbar.h"

ToolBar::ToolBar(PaintWindow* paintWindow, QWidget* parent) : QToolBar(parent) {

    FileSystem* fileSystem = new FileSystem();

    setToolButtonStyle(Qt::ToolButtonIconOnly);

    setMovable(false);

    QLabel* label = new QLabel("Paint");

    QFont font = this->font();
    font.setPointSize(24);

    label->setFont(font);

    addWidget(createSpacer(20));

    addWidget(label);

    addWidget(createExpandingSpacer());

    setMinimumHeight(50);

    QString basePath = QFileInfo(QString(__FILE__)).absolutePath();
    basePath += "/../../../icons/";

    qDebug() << basePath << "\n";

    QLabel* widthLabel = new QLabel("Width:");

    QSpinBox* spin = new QSpinBox();
    spin->setMinimum(1);
    spin->setMaximum(100);
    spin->setSingleStep(1);
    spin->setValue(3);

    qDebug() << basePath << "\n";

    QPushButton* paletteBt = createButton(basePath + "palette.png");
    QPushButton* bucketBt = createButton(basePath + "bucket.png");
    QPushButton* paintBt = createButton(basePath + "paint.png");
    QPushButton* lineBt = createButton(basePath + "line.png");
    QPushButton* brokenLine = createButton(basePath + "brokenLine.png");
    QPushButton* rectangleBt = createButton(basePath + "rectangle.png");
    QPushButton* circleBt = createButton(basePath + "circle.png");
    QPushButton* eraserBt = createButton(basePath + "eraser.png");

    addWidget(paletteBt);
    addWidget(bucketBt);
    addWidget(paintBt);
    addWidget(lineBt);
    addWidget(brokenLine);
    addWidget(rectangleBt);
    addWidget(circleBt);
    addWidget(eraserBt);
    addWidget(widthLabel);
    addWidget(spin);

    addWidget(createExpandingSpacer());

    QPushButton* returntBt = createFlippedButton(basePath + "arrow.png");
    QPushButton* nextBt = createButton(basePath + "arrow.png");
    QPushButton* increaseZoomBt = createButton(basePath + "increaseZoom.png");
    QPushButton* reduceZoomBt = createButton(basePath + "reduceZoom.png");

    addWidget(increaseZoomBt);
    addWidget(reduceZoomBt);
    addSeparator();
    addWidget(returntBt);
    addWidget(nextBt);

    addWidget(createSpacer(20));

    connect(paintBt, &QPushButton::clicked, this, [=](){emit toolSelected(Tool::Brush);});
    connect(rectangleBt, &QPushButton::clicked, this, [=](){emit toolSelected(Tool::Rectangle);});
    connect(circleBt, &QPushButton::clicked, this, [=](){emit toolSelected(Tool::Circle);});
    connect(eraserBt, &QPushButton::clicked, this, [=](){emit toolSelected(Tool::Eraser);});
    connect(lineBt, &QPushButton::clicked, this, [=](){emit toolSelected(Tool::Line);});
    connect(brokenLine, &QPushButton::clicked, this, [=](){emit toolSelected((Tool::BrokenLine));});
    connect(spin, qOverload<int>(&QSpinBox::valueChanged), this, &ToolBar::changedWidth);

    connect(returntBt, &QPushButton::clicked, this, [=](){
        fileSystem->undo(paintWindow->takeCanvas());
    });

    connect(nextBt, &QPushButton::clicked, this, [=](){
        fileSystem->redo(paintWindow->takeCanvas());
    });

    connect(increaseZoomBt, &QPushButton::clicked, this, [=](){
        paintWindow->takeCanvas()->increaseZoom();
        paintWindow->takeCanvas()->changeOffset(false, QPointF(0, 0));
    });
    connect(reduceZoomBt, &QPushButton::clicked, this, [=](){
        paintWindow->takeCanvas()->reduceZoom();
        paintWindow->takeCanvas()->changeOffset(false, QPointF(0, 0));
    });
}

QPushButton* ToolBar::createButton(const QString& path){
    QPushButton* bt = new QPushButton();
    bt->setIcon(QIcon(path));
    return bt;
}

QPushButton* ToolBar::createFlippedButton(const QString& path){
    QPixmap pix(path);
    pix = pix.transformed(QTransform().scale(-1, 1));
    QPushButton* bt = new QPushButton();
    bt->setIcon(QIcon(pix));
    return bt;
}

QWidget* ToolBar::createSpacer(int width){
    QWidget* spacer = new QWidget();
    spacer->setFixedWidth(width);
    return spacer;
}

QWidget* ToolBar::createExpandingSpacer(){
    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    return spacer;
}
