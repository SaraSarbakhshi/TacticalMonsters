#include "agents.h"
#include "ui_agents.h"
#include "characters.h"
#include <QPixmap>
#include <QFontDatabase>
#include <QDebug>
#include <QPushButton>
#include <QVector>
#include <QIcon>
#include <QGroupBox>
#include <QSize>

agents::agents(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::agents)
{
    ui->setupUi(this);
    this->setWindowTitle("tactical monsters_agents");
    QPixmap agentsBG(":/images/splashBG.jpg");
    ui->BG->setPixmap(agentsBG);
    ui->BG->setScaledContents(true);
    ui->BG->setGeometry(0, 0, agentsBG.width(), agentsBG.height());
    ui->BG->lower();
    this->setFixedSize(1000, 750);
    ui->groupBox_moreInfo->hide();



    ui->pushButton_back->setStyleSheet(
        "QPushButton {"
        "background-image: url(:/images/backBT.PNG);"
        "background-color: rgba(0, 0, 0, 0);"
        "border: none;"
        "background-repeat: no-repeat;"
        "background-size: contain;"
        "}"
        "QPushButton:hover { "
        "background-image: url(:/images/backBT_hover.PNG);"
        "background-color: rgba(0, 0, 0, 0);"
        "border: none;"
        "background-repeat: no-repeat;"
        "background-size: contain;"
        " }"
        "QPushButton:pressed{"
        "background-image: url(:/images/backBT_active.PNG);"
        "background-color: rgba(0, 0, 0, 0);"
        "border: none;"
        "background-repeat: no-repeat;"
        "background-size: contain;"
        " }"
        );



    characterPushButtons = {
        // Hunters
        ui->pushButton_h01, ui->pushButton_h02, ui->pushButton_h03,
        ui->pushButton_h04, ui->pushButton_h05, ui->pushButton_h06,
        ui->pushButton_h07, ui->pushButton_h08, ui->pushButton_h09,
        ui->pushButton_h10, ui->pushButton_h11, ui->pushButton_h12,
        ui->pushButton_h13, ui->pushButton_h14, ui->pushButton_h15,
        ui->pushButton_h16, ui->pushButton_h17, ui->pushButton_h18,
        ui->pushButton_h19, ui->pushButton_h20, ui->pushButton_h21,
        ui->pushButton_h22, ui->pushButton_h23, ui->pushButton_h24,

        // Preys
        ui->pushButton_p01, ui->pushButton_p02, ui->pushButton_p03,
        ui->pushButton_p04, ui->pushButton_p05, ui->pushButton_p06,
        ui->pushButton_p07, ui->pushButton_p08, ui->pushButton_p09,
        ui->pushButton_p10, ui->pushButton_p11, ui->pushButton_p12,
        ui->pushButton_p13, ui->pushButton_p14, ui->pushButton_p15,
        ui->pushButton_p16, ui->pushButton_p17, ui->pushButton_p18,
        ui->pushButton_p19, ui->pushButton_p20, ui->pushButton_p21,
        ui->pushButton_p22, ui->pushButton_p23, ui->pushButton_p24
    };




    characterList = {
        new Flying("Drakula", QPixmap(":/images/charachters/drakula.PNG"), 320, 120, 3, 1),//1--

        new Floating("PennyWise", QPixmap(":/images/charachters/pennyWise.PNG"), 320, 100, 3, 1),//1--
        new Floating("Valak", QPixmap(":/images/charachters/valek.PNG"), 240, 120, 3, 2),//2--


        new WaterWalking("Freddy Krueger", QPixmap(":/images/charachters/FreddyKrueger.PNG"), 320, 90, 3, 1),//1--
        new WaterWalking("Chucky", QPixmap(":/images/charachters/chucky.PNG"), 320, 80, 2, 2),//2--
        new WaterWalking("Alien", QPixmap(":/images/charachters/alien.PNG"), 400, 100, 2, 1),//3-
        new WaterWalking("Jason Voorhees", QPixmap(":/images/charachters/jasonVoorhees.png"), 320, 100, 2, 2),//4-
        new WaterWalking("Samara Morgan", QPixmap(":/images/charachters/samaraMorgen.png"), 400, 100, 2, 1),//5-
        new WaterWalking("Jack Torrance", QPixmap(":/images/charachters/jackTorrance.png"), 320, 90, 2, 2),//6-
        new WaterWalking("Annabelle", QPixmap(":/images/charachters/anabelle.PNG"), 320, 100, 3, 1),//7--
        new WaterWalking("Brahms", QPixmap(":/images/charachters/brahms.png"), 320, 100, 3, 1),//8-



        new Grounded("Ghost Face", QPixmap(":/images/charachters/ghostface.PNG"), 100, 40, 2, 1),//1--
        new Grounded("Frank", QPixmap(":/images/charachters/frank.PNG"), 100, 40, 2, 1),//2--
        new Grounded("John Kramer", QPixmap(":/images/charachters/JohnKramer.PNG"), 100, 40, 2, 1),//3--
        new Grounded("Slender Man", QPixmap(":/images/charachters/slenderMan.png"), 100, 40, 2, 1),//4
        new Grounded("Pyramid Head", QPixmap(":/images/charachters/pyramidHead.png"), 100, 40, 3, 1),//5
        new Grounded("Sam", QPixmap(":/images/charachters/sam.png"), 100, 40, 2, 1),//6
        new Grounded("Leather Face", QPixmap(":/images/charachters/leatherFace.png"), 100, 40, 2, 1),//7
        new Grounded("Micheal Myers", QPixmap(":/images/charachters/michealMyers.png"), 100, 40, 2, 1),//8
        new Grounded("Death", QPixmap(":/images/charachters/death.png"), 100, 40, 2, 1),//9
        new Grounded("Hanibal Lector", QPixmap(":/images/charachters/hanibalLector.png"), 100, 40, 2, 1),//10
        new Grounded("Pin Head", QPixmap(":/images/charachters/pinHead.png"), 100, 40, 3, 1),//11
        new Grounded("Art The Clown", QPixmap(":/images/charachters/artTheClown.png"), 100, 40, 2, 1),//12
        new Grounded("esther", QPixmap(":/images/charachters/esther.png"), 100, 40, 2, 1),//13


        new Flying("Mikeyangelo", QPixmap(":/images/charachters/mikeyangelo.png"), 320, 120, 3, 1),//1--

        new Floating("Alice Abernathy", QPixmap(":/images/charachters/aliceAbernathy.png"), 320, 100, 3, 1),//1--
        new Floating("Inspector Gadget", QPixmap(":/images/charachters/inspectorGadget.png"), 240, 120, 3, 2),//2--


        new WaterWalking("Indiana Jones", QPixmap(":/images/charachters/IndianaJones.PNG"), 320, 90, 3, 1),//1--
        new WaterWalking("Lara Croft", QPixmap(":/images/charachters/laraCroft.png"), 320, 80, 2, 2),//2--
        new WaterWalking("Jesus", QPixmap(":/images/charachters/jesus.png"), 400, 100, 2, 1),//3-
        new WaterWalking("Garalt", QPixmap(":/images/charachters/garalt.png"), 320, 100, 2, 2),//4-
        new WaterWalking("Constantine", QPixmap(":/images/charachters/constantine.png"), 400, 100, 2, 1),//5-
        new WaterWalking("Luke Skywalker", QPixmap(":/images/charachters/luke.png"), 320, 90, 2, 2),//6-
        new WaterWalking("Sarah Conner", QPixmap(":/images/charachters/sarahConner.png"), 320, 100, 3, 1),//7--
        new WaterWalking("Ellen Ripley.", QPixmap(":/images/charachters/ellenRipley.png"), 320, 100, 3, 1),//8-



        new Grounded("April O'Neil", QPixmap(":/images/charachters/aprilONeil.png"), 320, 110, 3, 1),//1--
        new Grounded("Hellboy", QPixmap(":/images/charachters/hellboy.png"), 400, 120, 2, 1),//2--
        new Grounded("John Mc Clane", QPixmap(":/images/charachters/JohnMcClane.PNG"), 320, 130, 2, 1),//3--
        new Grounded("Lankester Merrin", QPixmap(":/images/charachters/lankesterMerrin.png"), 400, 80, 2, 1),//4
        new Grounded("Marty Mc Fly", QPixmap(":/images/charachters/MartyMcFly.PNG"), 320, 90, 2, 1),//5
        new Grounded("Rambo", QPixmap(":/images/charachters/rambo.PNG"), 400, 100, 2, 1),//6
        new Grounded("Alex James Murphy", QPixmap(":/images/charachters/alexJamesMurphy.png"), 240, 100, 2, 3),//7
        new Grounded("Van Helsing", QPixmap(":/images/charachters/vanHsesing.png"), 160, 100, 2, 2),//8
        new Grounded("T-800", QPixmap(":/images/charachters/T800.png"), 320, 140, 2, 2),//9
        new Grounded("Casey Jones", QPixmap(":/images/charachters/caseyJones.png"), 280, 80, 2, 2),//10
        new Grounded("Rockey Bolboa", QPixmap(":/images/charachters/RockyBalboa.PNG"), 400, 100, 2, 1),//11
        new Grounded("Peter Venkman", QPixmap(":/images/charachters/peterVenkman.png"), 260, 80, 2, 2),//12
        new Grounded("Tree Gelbman", QPixmap(":/images/charachters/treeGelbman.png"), 400, 100, 2, 1),//13

    };

    //characters pushbuttons stylesheet
    for(int i = 0; i < 48; i++){
        characterPushButtons[i]->setStyleSheet("background:transparent;");

        characterPushButtons[i]->setIcon(characterList[i]->getPic());
        characterPushButtons[i]->setIconSize(QSize(150, 150));


        characterPushButtons[i]->setToolTip("name: " + characterList[i]->name +
                                          "\nattack power: " + QString::number(characterList[i]->damage) +
                                          "\nhealth: " + QString::number(characterList[i]->health) +
                                          "\nmobility: " + QString::number(characterList[i]->mobility) +
                                          "\nattack range: " + QString::number(characterList[i]->range));
    }
    ui->groupBox_h->setStyleSheet("background:transparent;");
    ui->groupBox_p->setStyleSheet("background:transparent;");

    moreInfo();
    loadCustomFont();
}

agents::~agents()
{
    delete ui;
}

void agents::on_pushButton_back_clicked()
{
    this->close();
}


void agents::loadCustomFont() {
    int fontId = QFontDatabase::addApplicationFont(":/font/pixelFont.ttf");

    if (fontId == -1) {
        qWarning() << "Failed to load font!";
        return;
    }

    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont nameFont(fontFamily, 35);
    QFont infoFont(fontFamily, 30);

    ui->label_name->setFont(nameFont);
    ui->label_HP->setFont(infoFont);
    ui->label_Attack->setFont(infoFont);
    ui->label_Mobility->setFont(infoFont);
    ui->label_Range->setFont(infoFont);
}

void agents::showCharacterInfo(int index) {
    if (index < 0 || index >= characterList.size()) return;

    Characters* character = characterList[index];

    QPixmap grounded(":/images/icons/grounded.png");
    QPixmap waterWalking(":/images/icons/waterWalking.png");
    QPixmap floating(":/images/icons/floating.png");
    QPixmap flying(":/images/icons/flying.png");

    ui->groupBox_moreInfo->show();
    ui->label_picture->setPixmap(character->picture);
    ui->label_picture->setScaledContents(true);

    ui->label_name->setText(character->name);
    ui->label_name->setAlignment(Qt::AlignCenter);
    ui->label_HP->setText(QString::number(character->health));
    ui->label_Attack->setText(QString::number(character->damage));
    ui->label_Mobility->setText(QString::number(character->mobility));
    ui->label_Range->setText(QString::number(character->range));

    switch (character->type) {
    case 1: ui->label_type->setPixmap(grounded); break;
    case 2: ui->label_type->setPixmap(waterWalking); break;
    case 3: ui->label_type->setPixmap(floating); break;
    case 4: ui->label_type->setPixmap(flying); break;
    }

    ui->label_type->setScaledContents(true);
}

void agents::moreInfo() {
    for (int i = 0; i < 48; i++) {
        connect(characterPushButtons[i], &QPushButton::clicked, this, [this, i]() {
            bool isHunter = i < 24;
            currentStartIndex = isHunter ? 0 : 24;
            currentEndIndex = isHunter ? 23 : 47;

            currentMoreInfoIndex = i;
            showCharacterInfo(currentMoreInfoIndex);
        });
    }

    connect(ui->pushButton_previous, &QPushButton::clicked, this, [this]() {


        if (currentMoreInfoIndex > currentStartIndex) {
            currentMoreInfoIndex--;
        } else {
            currentMoreInfoIndex = currentStartIndex + 23;
        }

        showCharacterInfo(currentMoreInfoIndex);
    });

    connect(ui->pushButton_next, &QPushButton::clicked, this, [this]() {
        if (currentMoreInfoIndex < currentEndIndex ) {
            currentMoreInfoIndex++;
        } else {
            currentMoreInfoIndex = currentStartIndex;
        }

        showCharacterInfo(currentMoreInfoIndex);
    });
}


void agents::on_pushButton_clicked()
{
    ui->groupBox_moreInfo->hide();
}

