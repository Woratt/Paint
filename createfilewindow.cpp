#include "createfilewindow.h"
#include "filesystem.h"
#include "numberline.h"

createFileWindow::createFileWindow(QWidget *parent) : QDialog(parent)
{

    setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint);

    createsAllComponents();
    initializeLayouts();
    initializeFields();
    initializeButtons();
    initializeButtonMenu();
    initializeConnections();
}

void createFileWindow::createsAllComponents(){
    mainLayout = new QVBoxLayout(this);

    nameLayout = new QHBoxLayout();
    presentLayout = new QHBoxLayout();
    widthLayout = new QHBoxLayout();
    heightLayout = new QHBoxLayout();
    buttonLayout = new QHBoxLayout();

    nameLabel = new QLabel();
    presentLabel = new QLabel();
    widthLabel = new QLabel();
    heightLabel = new QLabel();

    nameLine = new QLineEdit();
    widthLine = new numberLine();
    heightLine = new numberLine();

    okButton = new QPushButton("OK");
    cancelButton = new QPushButton("Cancel");
    presentButton = new QPushButton("Custom");
}

void createFileWindow::initializeButtonMenu(){
    QMap<QString, QSize> presetSizes = {
        {"640 X 480", QSize(640, 480)},
        {"800 X 600", QSize(800, 600)},
        {"1024 X 768", QSize(1024, 768)},
        {"1280 X 1024", QSize(1280, 1024)},
        {"1440 X 900", QSize(1440, 900)},
        {"1280 X 720 (720P HD)", QSize(1280, 720)},
        {"1920 X 1080 (1080P HD)", QSize(1920, 1080)},
        {"2560 X 1440 (1440P HD)", QSize(2560, 1440)},
        {"3840 X 2160 (HD 4K)", QSize(3840, 2160)},
        {"5120 X 2280 (5K)", QSize(5120, 2280)},
        {"A0", QSize(841, 1189)},
        {"A1", QSize(594, 841)},
        {"A2", QSize(420, 594)},
        {"A3", QSize(297, 420)},
        {"A4", QSize(210, 297)},
        {"A5", QSize(148, 210)},
        {"A6", QSize(105, 148)}
    };

    presentButton->setMinimumWidth(200);

    auto *presentMenu = new QMenu();

    for (const auto &str : presetSizes.keys()) {
        presentMenu->addAction(str);
    }

    presentButton->setMenu(presentMenu);

    connect(presentMenu, &QMenu::triggered, this,
            [=](QAction *action) -> void
            {
                presentButton->setText(action->text());
                if(presetSizes.contains(action->text())){
                    QSize sz = presetSizes[action->text()];
                    widthLine->setText(QString::number(sz.width()));
                    heightLine->setText(QString::number(sz.height()));
                }
            });
}

void createFileWindow::initializeLayouts(){

    nameLayout->addStretch();
    nameLayout->addWidget(nameLabel);
    nameLayout->addWidget(nameLine);

    presentLayout->addWidget(presentLabel);
    presentLayout->addWidget(presentButton);

    widthLayout->addStretch();
    widthLayout->addWidget(widthLabel);
    widthLayout->addWidget(widthLine);

    heightLayout->addStretch();
    heightLayout->addWidget(heightLabel);
    heightLayout->addWidget(heightLine);

    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(okButton);

    mainLayout->addLayout(nameLayout);
    mainLayout->addLayout(presentLayout);
    mainLayout->addLayout(widthLayout);
    mainLayout->addLayout(heightLayout);
    mainLayout->addLayout(buttonLayout);
}

void createFileWindow::initializeFields(){

    nameLabel->setText("Name File:");
    presentLabel->setText("Present:");
    widthLabel->setText("Width:");
    heightLabel->setText("Height:");

    nameLine->setFixedWidth(200);
    widthLine->setFixedWidth(200);
    heightLine->setFixedWidth(200);

    nameLine->setPlaceholderText("Name File");
    widthLine->setPlaceholderText("Width");
    heightLine->setPlaceholderText("Height");
}

void createFileWindow::initializeButtons(){

    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(okButton);
}

void createFileWindow::initializeConnections(){
    connect(widthLine, &QLineEdit::textEdited, this, [=]() -> void { presentButton->setText("Custom"); });

    connect(heightLine, &QLineEdit::textEdited, this, [=]() -> void { presentButton->setText("Custom"); });

    connect(cancelButton, &QPushButton::clicked, this, &QDialog::close);

    connect(okButton, &QPushButton::clicked, this,
            [=]() -> void
            {
                QString const folderPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) +
                                           "/MyPaintFiles/" + nameLine->text() + ".png";
                if(widthLine->text() == "0" || heightLine->text() == "0" || nameLine->text().isEmpty()){
                    auto *msgBox = new QMessageBox();
                    msgBox->setText("incomplete information ");
                    msgBox->exec();
                }else{
                    if (QFile::exists(folderPath))
                    {
                        auto *msgBox = new QMessageBox();
                        msgBox->setText("This file already exists\n\nReplace it");
                        msgBox->setIcon(QMessageBox::Critical);

                        msgBox->setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);

                        int const ret = msgBox->exec();

                        if (ret == QMessageBox::Ok)
                        {
                            FileSystem().create(nameLine->text(), widthLine->text().toInt(), heightLine->text().toInt());
                            this->close();
                        }
                        else
                        {
                            this->close();
                        }
                    }
                    else
                    {
                        FileSystem().create(nameLine->text(), widthLine->text().toInt(), heightLine->text().toInt());
                        this->close();
                    }
                }
            });
}
