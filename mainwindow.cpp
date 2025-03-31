//to do: make the windows responsive
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamewindow.h"
#include <QPixmap>
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
//#include <QStatusBar>

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

    ui->pushButton_start->setStyleSheet("QPushButton{background-color: rgb(23, 255, 23);"
                                        "border: solid;"
                                        "border-color: rgb(255, 255, 255);"
                                        "border-width: 4px;"
                                        "border-radius: 30px;"
                                        "font: 700 italic 28pt;"
                                        "position:relative;\ntext-align: center;"
                                        "qproperty-iconAlignment: AlignCenter;"
                                        "text-align: center;}"
                                        "QPushButton:hover { background-color: #45a049; }");

    QMessageBox welcome;
    welcome.setText("welcome to tactcal monsters\n"
                    "made by yours truly");
    welcome.setWindowTitle("welcome!");

    welcome.setStyleSheet(
        "QMessageBox {"
        "    background-color: black;"
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
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_start_clicked()
{
    /*gameWindow Game=new gameWindow(this);
    Game.show();
    hide();*/

}

