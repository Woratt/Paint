#include "homepage.h"

HomePage::HomePage(QWidget *parent) : QMainWindow(parent)
{
    setMinimumSize(600, 400);

    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);

    // MenuBar* menuBar = new MenuBar("", nullptr);

    QWidget *central = new QWidget(this);

    fileSystem = new FileSystem(this);

    setCentralWidget(central);

    QVBoxLayout *VLayout = new QVBoxLayout(central);
    QHBoxLayout *HLayot = new QHBoxLayout();

    clearBt = new QPushButton("...");
    createBt = new QPushButton("Create New");
    openBt = new QPushButton("Open");
    openOtherBt = new QPushButton("Open Other ...");

    QMenu *clearMenu = new QMenu();

    clearMenu->addAction("Clear Recent Documents");

    clearBt->setMenu(clearMenu);
    clearBt->setMaximumWidth(45);

    createBt->setMaximumSize(100, 40);
    openBt->setMaximumSize(100, 40);
    openOtherBt->setMaximumSize(100, 40);

    openBt->setEnabled(false);

    filesModel *fileModel = new filesModel();

    label = new QLabel("Recent Documents:");

    VLayout->addWidget(label);
    VLayout->addWidget(fileModel->takeView());
    VLayout->addLayout(HLayot);

    HLayot->addWidget(clearBt);
    HLayot->addWidget(createBt);
    HLayot->addSpacing(250);
    HLayot->addWidget(openBt);
    HLayot->addWidget(openOtherBt);

    connect(createBt, &QPushButton::clicked,
            [=]()
            {
                createFileWindow *window = new createFileWindow(this);
                window->exec();
            });

    connect(clearMenu, &QMenu::triggered, this,
            [=](QAction *action)
            {
                if (action->text() == "Clear Recent Documents")
                    ;
                fileSystem->clearDirectory();
            });

    QItemSelectionModel *selectionModel = fileModel->takeView()->selectionModel();

    connect(selectionModel, &QItemSelectionModel::selectionChanged, this,
            [=](const QItemSelection &selected, const QItemSelection &deselected)
            {
                if (!selected.indexes().isEmpty())
                {
                    file = fileModel->takeModel()->filePath(selected.indexes().first());
                    qDebug() << "Файл вибрано";
                    openBt->setEnabled(true);
                }
            });

    connect(openBt, &QPushButton::clicked, this,
            [&]()
            {
                this->hide();
                QImageReader info(file);
                QImage image = info.read();
                qDebug() << info.fileName() << "\n";
                PaintWindow *w = new PaintWindow(image, info.fileName());
                w->setAttribute(Qt::WA_DeleteOnClose);
                w->show();
                connect(w, &QWidget::destroyed, this, [=]() { this->show(); });
            });

    connect(openOtherBt, &QPushButton::clicked, this,
            [=]()
            {
                file = QFileDialog::getOpenFileName(this, tr("Open file"), QDir::homePath(), tr("Image (*.png *.jpg)"));
                if (file.isEmpty())
                    return;

                QImageReader info(file);
                QImage image = info.read();

                if (image.isNull())
                {
                    QMessageBox::warning(this, "Error", "Failed to load image!");
                    return;
                }

                QFileInfo fileInfo(file);
                QString imageName = fileInfo.fileName();

                PaintWindow *w = new PaintWindow(image, info.fileName());

                w->setAttribute(Qt::WA_DeleteOnClose);
                w->show();

                connect(w, &QWidget::destroyed, this, [=]() { this->show(); });

                this->hide();
            });
}

bool HomePage::takeIsOpen() { return open; }
