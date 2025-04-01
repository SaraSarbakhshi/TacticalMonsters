#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "agents.h"

#include <QPixmap>
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QIcon>
#include <QStatusBar>

gameWindow::gameWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::gameWindow)
{
    ui->setupUi(this);
    ui->scrollArea->hide();


    this->setWindowTitle("tactical monsters_main window");
    QPixmap splashBG(":/pics/splashBG.jpg");
    int w=splashBG.width();int h=splashBG.height();
    ui->label->setScaledContents(true);
    ui->label->setGeometry(0,0,w,h);
    this->setMaximumSize(w,h);
    this->setMinimumSize(w,h);

    ui->pushButton_PVP->setStyleSheet(
        "QPushButton {"
        "background-image: url(:/pics/pvpBT.png);"
        "background-color: rgba(0, 0, 0, 0);"
        "border: none;"
        "background-repeat: no-repeat;"
        "background-size: contain;"
        "}"
        "QPushButton:hover { "
        "background-image: url(:/pics/pvpBT_hover.PNG);"
        "background-color: rgba(0, 0, 0, 0);"
        "border: none;"
        "background-repeat: no-repeat;"
        "background-size: contain;"
        " }"
        "QPushButton:pressed{"
        "background-image: url(:/pics/pvpBT_active.PNG);"
        "background-color: rgba(0, 0, 0, 0);"
        "border: none;"
        "background-repeat: no-repeat;"
        "background-size: contain;"
        " }"
        );

    ui->pushButton_HTP->setStyleSheet(
        "QPushButton {"
        "background-image: url(:/pics/howtoBT.png);"
        "background-color: rgba(0, 0, 0, 0);"
        "border: none;"
        "background-repeat: no-repeat;"
        "background-size: contain;"
        "}"
        "QPushButton:hover { "
        "background-image: url(:/pics/howtoBT_hover.PNG);"
        "background-color: rgba(0, 0, 0, 0);"
        "border: none;"
        "background-repeat: no-repeat;"
        "background-size: contain;"
        " }"
        "QPushButton:pressed{"
        "background-image: url(:/pics/howtoBT_active.PNG);"
        "background-color: rgba(0, 0, 0, 0);"
        "border: none;"
        "background-repeat: no-repeat;"
        "background-size: contain;"
        " }"
        );

    ui->pushButton_agents->setStyleSheet(
        "QPushButton {"
        "background-image: url(:/pics/agentsBT.png);"
        "background-color: rgba(0, 0, 0, 0);"
        "border: none;"
        "background-repeat: no-repeat;"
        //"background-size: contain;"
        "}"
        "QPushButton:hover { "
        "background-image: url(:/pics/agentsBT_hover.PNG);"
        "background-color: rgba(0, 0, 0, 0);"
        "border: none;"
        "background-repeat: no-repeat;"
        //"background-size: contain;"
        " }"
        "QPushButton:pressed{"
        "background-image: url(:/pics/agentsBT_active.PNG);"
        "background-color: rgba(0, 0, 0, 0);"
        "border: none;"
        "background-repeat: no-repeat;"
        "background-size: contain;"
        " }"
        );

}

gameWindow::~gameWindow()
{
    delete ui;
}

/*void gameWindow::on_pushButton_HTP_clicked()
{
    this->setEnabled(false);
    ui->scrollArea->show();

}
*/




void gameWindow::on_pushButton_agents_clicked()
{
    agents Agents;
    Agents.setModal(true);
    Agents.exec();
}

