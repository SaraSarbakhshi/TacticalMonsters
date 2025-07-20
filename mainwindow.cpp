 //to do: make the windows responsive
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QIcon>
#include <QFont>
#include <QFontDatabase>
#include <QApplication>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //loadCustomFont();

    this->setWindowTitle("tactical monsters");
    QPixmap splashBG(":/images/splashBG.jpg");
    int w=splashBG.width();int h=splashBG.height();
    ui->label->setScaledContents(true);
    ui->label->setGeometry(0,0,w,h);
    this->setMaximumSize(1000,750);
    this->setMinimumSize(1000,750);



    int fontId = QFontDatabase::addApplicationFont(":/font/pixelFont.ttf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont customFont(fontFamily, 10);
    QMessageBox welcome;
    welcome.setText("welcome to tactcal monsters\n"
                    "made by yours truly\n"
                    "P.S.: it's a knock off :(");
    welcome.setWindowTitle("welcome!");

    welcome.setFont(customFont);

    welcome.setStyleSheet(
        "QMessageBox {"
        "    background-color: #222222;"
        "    color: white;"
        "}"
        "QPushButton {"
        "    background-color: black;"
        "    color: white;"
        "    border-radius: 5px;"
        "    padding: 5px 10px;"
        "}"
        "QPushButton:hover {"
        "    background-color: green;"
        "}"
        );

    welcome.exec();

    ui->statusbar->setStyleSheet("color:white;"
                                 "background-color:black;");
    ui->statusbar->showMessage("Sara Sarbakhshi");


    ui->pushButton_start->setStyleSheet(
        "QPushButton {"
        "background-image: url(:/images/startBT.png);"
        "background-color: rgba(0, 0, 0, 0);"
        "border: none;"
        "background-repeat: no-repeat;"
        "background-position:center"
        "}"
        "QPushButton:hover { "
        "background-image: url(:/images/startBT_hover.PNG);"
        "background-color: rgba(0, 0, 0, 0);"
        "border: none;"
        "background-repeat: no-repeat;"
        "background-position:center"
        " }"
        "QPushButton:pressed{"
        "background-image: url(:/images/startBT_active.PNG);"
        "background-color: rgba(0, 0, 0, 0);"
        "border: none;"
        "background-repeat: no-repeat;"
        "background-position:center"
        " }"
        );
}

//load custom font
/*void mainWindow::loadCustomFont() {
    int fontId = QFontDatabase::addApplicationFont(":/font/pixelFont.ttf");

    if (fontId == -1) {
        qWarning() << "Failed to load font!";
        return;
    }

    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont buttonFont(fontFamily, 10);
    QFont groupBoxFont(fontFamily, 10);

    welcome->setFont(buttomFont);

}*/


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_start_clicked()
{
    hide();
    game=new gameWindow(this);
    game->show();
}

