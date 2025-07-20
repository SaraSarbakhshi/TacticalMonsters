#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "mapwindow.h"

#include <QPixmap>
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QIcon>
#include <QStatusBar>
#include <QFont>
#include <QFontDatabase>
#include <QLabel>


gameWindow::gameWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::gameWindow)
{
    ui->setupUi(this);
    ui->label_scroll->hide();
    ui->pushButton_X->hide();
    this->setWindowTitle("tactical monsters_main window");
    QPixmap splashBG(":/images/splashBG.jpg");
    int w=splashBG.width();int h=splashBG.height();
    ui->label->setScaledContents(true);
    ui->label->setGeometry(0,0,w,h);
    this->setMaximumSize(1000,750);
    this->setMinimumSize(1000,750);
    ui->scrollArea_2->hide();

    ui->label_info->setText("attention! this text is the exact copy from the game itself so it is not completely acurate\n"
                            "it's here merely cuz i wanted to\n"
                            "Game rule description \nSync PVP battle \n "
                            "1. Before the real-time battle begins, decide which side is the first player by flipping a coin."
                            "\n 2.In the formation phase, the first player first deploys ONE monster to battle ground."
                            " Then the second player deploys TWO monsters in a row. Then the first player deploys TWO monsters."
                            " Alternate in turn, until both sides have selected all the monsters and enter the battle phase."
                            "\n 3.After the battle begins, the first player gets ONE move to act first."
                            " Then TWO moves from the second player. "
                            "Then the first player will act TWO moves in a row. Alternately, "
                            "when one party has no monsters to act, the other party can continue to act until all the monsters have acted, "
                            "and the round ends."
                            "\n 4.At the end of each round, the two parties exchange their hands and repeat the alternate sequence of actions "
                            "in the first round until one party is defeated or the number of rounds is exhausted."
                            "The difference between Async PVP and Sync PVP battles"
                            "\n 1.The player is always first."
                            "\n 2.In the formation phase, you can see the opponent’s lineup, and you need to complete the formation of all monsters in a row.");
    ui->label_info->setWordWrap(true);
    ui->label_info->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    ui->pushButton_PVP->setStyleSheet(
        "QPushButton {"
        "background-image: url(:/images/pvpBT.PNG);"
        "background-color: rgba(0, 0, 0, 0);"
        "border: none;"
        "background-repeat: no-repeat;"
        "background-size: contain;"
        "}"
        "QPushButton:hover { "
        "background-image: url(:/images/pvpBT_hover.PNG);"
        "background-color: rgba(0, 0, 0, 0);"
        "border: none;"
        "background-repeat: no-repeat;"
        "background-size: contain;"
        " }"
        "QPushButton:pressed{"
        "background-image: url(:/images/pvpBT_active.PNG);"
        "background-color: rgba(0, 0, 0, 0);"
        "border: none;"
        "background-repeat: no-repeat;"
        "background-size: contain;"
        " }"
        );

    ui->pushButton_HTP->setStyleSheet(
        "QPushButton {"
        "background-image: url(:/images/howtoBT.png);"
        "background-color: rgba(0, 0, 0, 0);"
        "border: none;"
        "background-repeat: no-repeat;"
        "background-size: contain;"
        "}"
        "QPushButton:hover { "
        "background-image: url(:/images/howtoBT_hover.PNG);"
        "background-color: rgba(0, 0, 0, 0);"
        "border: none;"
        "background-repeat: no-repeat;"
        "background-size: contain;"
        " }"
        "QPushButton:pressed{"
        "background-image: url(:/images/howtoBT_active.PNG);"
        "background-color: rgba(0, 0, 0, 0);"
        "border: none;"
        "background-repeat: no-repeat;"
        "background-size: contain;"
        " }"
        );

    ui->pushButton_agents->setStyleSheet(
        "QPushButton {"
        "background-image: url(:/images/agentsBT.png);"
        "background-color: rgba(0, 0, 0, 0);"
        "border: none;"
        "background-repeat: no-repeat;"
        //"background-size: contain;"
        "}"
        "QPushButton:hover { "
        "background-image: url(:/images/agentsBT_hover.PNG);"
        "background-color: rgba(0, 0, 0, 0);"
        "border: none;"
        "background-repeat: no-repeat;"
        //"background-size: contain;"
        " }"
        "QPushButton:pressed{"
        "background-image: url(:/images/agentsBT_active.PNG);"
        "background-color: rgba(0, 0, 0, 0);"
        "border: none;"
        "background-repeat: no-repeat;"
        "background-size: contain;"
        " }"
        );
    ui->pushButton_X->setStyleSheet(
        "QPushButton {"
        "    image: url(:/images/x.png);"
        "    background: transparent;"
        "}"
        "QPushButton:hover {"
        "    image: url(:/images/x_hover.PNG);"
        "}"
        "QPushButton:pressed {"
        "    image: url(:/images/x_active.PNG);"
        "}"
        );

    loadCustomFont();
}

gameWindow::~gameWindow()
{
    delete ui;
}

void gameWindow::on_pushButton_HTP_clicked()
{
    ui->label_scroll->show();
    ui->pushButton_X->show();
    ui->scrollArea_2->show();
    QPixmap scroll(":/images/scroll.png");

    int fontId = QFontDatabase::addApplicationFont(":/font/pixelFont.ttf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont customFont(fontFamily, 10);
    QMessageBox justSoUKnow;
    justSoUKnow.setText("attention! this text is the exact copy from the game itself so it is not completely acurate\n"
                        "it's here merely cuz i wanted to\n");
    justSoUKnow.setWindowTitle("attention!");

    justSoUKnow.setFont(customFont);

    justSoUKnow.setStyleSheet(
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
    /*::warning(this, "attention!","this text is the exact copy from the game itself so it is not completely acurate\n"
                               "it's here merely cuz i wanted to\n");*/

    justSoUKnow.exec();
}

void gameWindow::on_pushButton_agents_clicked()
{
    agentsWindow=new agents(this);
    agentsWindow->show();
}


/*void gameWindow::on_pushButton_PVP_clicked()
{
    hide();
    naghshe=new mapWindow(this);
    naghshe->show();

}*/

void gameWindow::loadCustomFont() {
    int fontId = QFontDatabase::addApplicationFont(":/font/pixelFont.ttf");

    if (fontId == -1) {
        qWarning() << "Failed to load font!";
        return;
    }

    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont txtFont(fontFamily, 20);

    ui->label_info->setFont(txtFont);

}


void gameWindow::on_pushButton_PVP_clicked()
{
    mapWindow map;
    map.setModal(true);
    map.exec();
}


void gameWindow::on_pushButton_X_clicked()
{
    ui->label_scroll->hide();
    ui->pushButton_X->hide();
    ui->scrollArea_2->hide();
}

