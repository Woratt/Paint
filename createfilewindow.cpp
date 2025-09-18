#include "createfilewindow.h"

createFileWindow::createFileWindow(QWidget* parent): QDialog(parent) {

    setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint);
    //setMinimumSize(300, 200);
    //setFixedSize(300, 220);


    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QHBoxLayout* nameLayout = new QHBoxLayout();
    QHBoxLayout* presentLayout = new QHBoxLayout();
    QHBoxLayout* widthLayout = new QHBoxLayout();
    QHBoxLayout* heightLayout = new QHBoxLayout();
    QHBoxLayout* buttonLayout = new QHBoxLayout();

    QLineEdit* nameLine = new QLineEdit();
    numberLine* widthLine = new numberLine();
    numberLine* heightLine = new numberLine();

    QPushButton* presentButton = new QPushButton("Custom");

    presentButton->setMinimumWidth(200);

    QMenu* presentMenu = new QMenu();

    presentMenu->addAction("Custom");
    presentMenu->addAction("640 X 480");
    presentMenu->addAction("800 X 600");
    presentMenu->addAction("1024 X 768");
    presentMenu->addAction("1280 X 1024");
    presentMenu->addAction("1440 X 900");
    presentMenu->addAction("1280 X 720 (720P HD)");
    presentMenu->addAction("1920 X 1080 (1080P HD)");
    presentMenu->addAction("2560 X 1440 (1440P HD)");
    presentMenu->addAction("3840 X 2160 (HD 4K)");
    presentMenu->addAction("5120 X 2280 (5K)");
    presentMenu->addAction("A0");
    presentMenu->addAction("A1");
    presentMenu->addAction("A2");
    presentMenu->addAction("A3");
    presentMenu->addAction("A4");
    presentMenu->addAction("A5");
    presentMenu->addAction("A6");

    presentButton->setMenu(presentMenu);

    nameLine->setFixedWidth(200);
    widthLine->setFixedWidth(200);
    heightLine->setFixedWidth(200);

    nameLine->setPlaceholderText("Name File");
    widthLine->setPlaceholderText("Width");
    heightLine->setPlaceholderText("Height");

    QLabel* nameLabel = new QLabel();
    QLabel* presentLabel = new QLabel();
    QLabel* widthLabel = new QLabel();
    QLabel* heightLabel = new QLabel();

    nameLabel->setText("Name File:");
    presentLabel->setText("Present:");
    widthLabel->setText("Width:");
    heightLabel->setText("Height:");

    QPushButton* okButton = new QPushButton("OK");
    QPushButton* cancelButton = new QPushButton("Cancel");

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


    connect(presentMenu, &QMenu::triggered, this, [=](QAction *action){
        presentButton->setText(action->text());
        QString text = action->text();
        if(text == "640 X 480"){
            widthLine->setText("640");
            heightLine->setText("480");
        }else if(text == "800 X 600"){
            widthLine->setText("800");
            heightLine->setText("600");
        }else if(text == "1024 X 768"){
            widthLine->setText("1024");
            heightLine->setText("768");
        }else if(text == "1280 X 1024"){
            widthLine->setText("1280");
            heightLine->setText("1024");
        }else if(text =="1440 X 900"){
            widthLine->setText("1440");
            heightLine->setText("900");
        }else if(text == "1280 X 720 (720P HD)"){
            widthLine->setText("1280");
            heightLine->setText("720");
        }else if(text == "1920 X 1080 (1080P HD)"){
            widthLine->setText("1920");
            heightLine->setText("1080");
        }else if(text == "2560 X 1440 (1440P HD)"){
            widthLine->setText("2560");
            heightLine->setText("1440");
        }else if(text == "3840 X 2160 (HD 4K)"){
            widthLine->setText("3840");
            heightLine->setText("2160");
        }else if(text == "5120 X 2280 (5K)"){
            widthLine->setText("5120");
            heightLine->setText("2280");
        }else if(text == "A0"){
            widthLine->setText("841");
            heightLine->setText("1189");
        }else if(text == "A1"){
            widthLine->setText("594");
            heightLine->setText("841");
        }else if(text == "A2"){
            widthLine->setText("420");
            heightLine->setText("594");
        }else if(text == "A3"){
            widthLine->setText("297");
            heightLine->setText("420");
        }else if(text == "A4"){
            widthLine->setText("210");
            heightLine->setText("297");
        }else if(text == "A5"){
            widthLine->setText("148");
            heightLine->setText("210");
        }else if(text == "A6"){
            widthLine->setText("105");
            heightLine->setText("148");
        }
    });

    connect(widthLine, &QLineEdit::textEdited , this, [=](){
        presentButton->setText("Custom");
    });

    connect(heightLine, &QLineEdit::textEdited , this, [=](){
        presentButton->setText("Custom");
    });

    connect(cancelButton, &QPushButton::clicked, this, &QDialog::close);

    connect(okButton, &QPushButton::clicked, this, [=](){
        QString folderPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/MyPaintFiles/" +  nameLine->text() + ".png";
        if(QFile::exists(folderPath)){
            QMessageBox* msgBox = new QMessageBox();
            msgBox->setText("This file already exists\n\nReplace it");
            msgBox->setIcon(QMessageBox::Critical);

            msgBox->setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);

            int ret = msgBox->exec();

            if(ret == QMessageBox::Ok){
                FileSystem().create(nameLine->text(), widthLine->text().toInt(), heightLine->text().toInt());
                this->close();
            }else this->close();
        }else{
            FileSystem().create(nameLine->text(), widthLine->text().toInt(), heightLine->text().toInt());
            this->close();
        }
    });

}
