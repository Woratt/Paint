#include "toolbar.h"

ToolBar::ToolBar(PaintWindow* paintWindow, QWidget* parent) : QToolBar(parent) {

    FileSystem* fileSystem = new FileSystem();

    setToolButtonStyle(Qt::ToolButtonIconOnly);

    setMovable(false);

    QLabel* label = new QLabel("Paint");

    QFont font = this->font();
    font.setPointSize(24);

    label->setFont(font);

    QWidget* spacer_left_margin = new QWidget();
    spacer_left_margin->setFixedWidth(20);

    QWidget* spacer_right_margin = new QWidget();
    spacer_right_margin->setFixedWidth(20);

    QWidget* spacerLeft = new QWidget();
    spacerLeft->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    QWidget* spacerRight = new QWidget();
    spacerRight->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    addWidget(spacer_left_margin);

    addWidget(label);

    addWidget(spacerLeft);

    setMinimumHeight(50);

    QString basePath = QFileInfo(QString(__FILE__)).absolutePath();
    basePath += "/../../../icons/";

    qDebug() << basePath << "\n";

    QPushButton* paintBt = new QPushButton();
    QPushButton* rectangleBt = new QPushButton();
    QPushButton* circleBt = new QPushButton();
    QPushButton* eraserBt = new QPushButton();
    QPushButton* paletteBt = new QPushButton();
    QPushButton* bucketBt = new QPushButton();
    QPushButton* lineBt = new QPushButton();
    QPushButton* brokenLine = new QPushButton();

    QLabel* widthLabel = new QLabel("Width:");

    QSpinBox* spin = new QSpinBox();
    spin->setMinimum(1);
    spin->setMaximum(100);
    spin->setSingleStep(1);
    spin->setValue(3);


    paletteBt->setIcon(QIcon(basePath + "palette.png"));
    bucketBt->setIcon(QIcon(basePath + "bucket.png"));
    paintBt->setIcon(QIcon(basePath + "paint.png"));
    lineBt->setIcon(QIcon(basePath + "line.png"));
    brokenLine->setIcon(QIcon(basePath + "brokenLine.png"));
    rectangleBt->setIcon(QIcon(basePath + "rectangle.png"));
    circleBt->setIcon(QIcon(basePath + "circle.png"));
    eraserBt->setIcon(QIcon(basePath + "eraser.png"));


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

    addWidget(spacerRight);

    QPushButton* returntBt = new QPushButton();
    QPushButton* nextBt = new QPushButton();
    QPushButton* increaseZoomBt = new QPushButton();
    QPushButton* reduceZoomBt = new QPushButton();

    QPixmap pix(basePath + "arrow.png");

    nextBt->setIcon(pix);

    pix = pix.transformed(QTransform().scale(-1, 1));

    returntBt->setIcon((QIcon(pix)));

    increaseZoomBt->setIcon(QIcon(basePath + "increaseZoom.png"));
    reduceZoomBt->setIcon(QIcon(basePath + "reduceZoom.png"));

    addWidget(increaseZoomBt);
    addWidget(reduceZoomBt);
    addSeparator();
    addWidget(returntBt);
    addWidget(nextBt);

    addWidget(spacer_right_margin);

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
}
