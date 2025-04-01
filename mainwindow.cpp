//to do: make the windows responsive
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QIcon>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("tactical monsters");
    QPixmap splashBG(":/pics/splashBG.jpg");
    int w=splashBG.width();int h=splashBG.height();
    ui->label->setScaledContents(true);
    ui->label->setGeometry(0,0,w,h);
    this->setMaximumSize(w,h);
    this->setMinimumSize(w,h);

    QMessageBox welcome;
    welcome.setText("welcome to tactcal monsters\n"
                    "made by yours truly");
    welcome.setWindowTitle("welcome!");

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


    ui->pushButton_play->setStyleSheet(
        "QPushButton {"
        "background-image: url(:/pics/playBT.png);"
        "background-color: rgba(0, 0, 0, 0);"
        "border: none;"
        "background-repeat: no-repeat;"
        "}"
        "QPushButton:hover { "
        "background-image: url(:/pics/playBT_hover.PNG);"
        "background-color: rgba(0, 0, 0, 0);"
        "border: none;"
        "background-repeat: no-repeat;"
        " }"
        "QPushButton:pressed{"
        "background-image: url(:/pics/playBT_active.PNG);"
        "background-color: rgba(0, 0, 0, 0);"
        "border: none;"
        "background-repeat: no-repeat;"
        " }"
        );

    ui->pushButton_play->setStyleSheet(
        "QPushButton {"
        "background-image: url(:/pics/playBT.png);"
        "background-color: rgba(0, 0, 0, 0);"
        "border: none;"
        "background-repeat: no-repeat;"
        "}"
        "QPushButton:hover { "
        "background-image: url(:/pics/playBT_hover.PNG);"
        "background-color: rgba(0, 0, 0, 0);"
        "border: none;"
        "background-repeat: no-repeat;"
        " }"
        "QPushButton:pressed{"
        "background-image: url(:/pics/playBT_active.PNG);"
        "background-color: rgba(0, 0, 0, 0);"
        "border: none;"
        "background-repeat: no-repeat;"
        " }"
        );

}


MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pushButton_play_clicked()
{
    hide();
    game=new gameWindow(this);
    game->show();
}

