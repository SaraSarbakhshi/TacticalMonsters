#include "mapwindow.h"
#include "Characters.h"
#include "ui_mapwindow.h"
#include "tiles.h"
#include "player.h"
#include <Qfont>
#include <QFontDatabase>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QRandomGenerator>
#include <QMessageBox>
#include <QPixmap>
#include <QVector>
#include <QLabel>
#include <QIcon>
#include <QIntValidator>
#include <QLineEdit>
#include <QFont>
#include <QGroupBox>
#include <QtMath>
#include <QPoint>
#include <QQueue>
#include <QSet>
#include <QPair>
#include <QMovie>


player player1,player2,*currentPlayer;
struct hex
{
    int index;
    int column;
    int row;
    bool crossable;
    bool visited = false;
    int distance = 100;

    hex(int r=0,int c=0) : row(r),column(c),visited(false),distance(100),crossable(true){}
};

mapWindow::mapWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::mapWindow)
{
    ui->setupUi(this);
    ui->pushButton_allChosen->hide();
    ui->groupBox_setting->hide();
    ui->groupBox_gameOver->hide();
    //ui->groupBox_GO->hide();



    ui->pushButton_setting->setStyleSheet(
        "QPushButton {"
        "background-image: url(:/images/settingBTN.png);"
        "background-color:transparent;"
        "border: transparent;"
        "}"
        "QPushButton:hover { "
        "background-image: url(:/images/settingBTN_hover.PNG);"
        "background-color:transparent;"
        "border: transparent;"
        " }"
        "QPushButton:pressed{"
        "background-image: url(:/images/settingBTN_active.PNG);"
        "background-color:transparent;"
        "border: transparent;"
        " }"
        );

    ui->pushButton_musique->setStyleSheet(
        "QPushButton {"
        "background-image: url(:/images/musicBTN_on.png);"
        "background-color:transparent;"
        "border: transparent;"
        "}"
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


    agentsPics={
        ui->pushButton_p101,ui->pushButton_p102,ui->pushButton_p103,ui->pushButton_p104,
        ui->pushButton_p105,ui->pushButton_p106,ui->pushButton_p107,ui->pushButton_p108,
        ui->pushButton_p109,ui->pushButton_p110,ui->pushButton_p111,ui->pushButton_p112,
        ui->pushButton_p113,ui->pushButton_p114,ui->pushButton_p115,ui->pushButton_p116,
        ui->pushButton_p117,ui->pushButton_p118,ui->pushButton_p119,ui->pushButton_p120,
        ui->pushButton_p121,ui->pushButton_p122,ui->pushButton_p123,ui->pushButton_p124,
        ui->pushButton_p201,ui->pushButton_p202,ui->pushButton_p203,ui->pushButton_p204,
        ui->pushButton_p205,ui->pushButton_p206,ui->pushButton_p207,ui->pushButton_p208,
        ui->pushButton_p209,ui->pushButton_p210,ui->pushButton_p211,ui->pushButton_p212,
        ui->pushButton_p213,ui->pushButton_p214,ui->pushButton_p215,ui->pushButton_p216,
        ui->pushButton_p217,ui->pushButton_p218,ui->pushButton_p219,ui->pushButton_p220,
        ui->pushButton_p221,ui->pushButton_p222,ui->pushButton_p223,ui->pushButton_p224,
    };

    //name,pic,hp,dp,mobility,range
   /*QVector<Characters*>*/    characterList = {
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



        new Grounded("Ghost Face", QPixmap(":/images/charachters/ghostface.PNG"), 320, 110, 3, 1),//1--
        new Grounded("Frank", QPixmap(":/images/charachters/frank.PNG"), 400, 120, 2, 1),//2--
        new Grounded("John Kramer", QPixmap(":/images/charachters/JohnKramer.PNG"), 320, 130, 2, 1),//3--
        new Grounded("Slender Man", QPixmap(":/images/charachters/slenderMan.png"), 400, 80, 2, 1),//4
        new Grounded("Pyramid Head", QPixmap(":/images/charachters/pyramidHead.png"), 320, 90, 3, 1),//5
        new Grounded("Sam", QPixmap(":/images/charachters/sam.png"), 400, 100, 2, 1),//6
        new Grounded("Leather Face", QPixmap(":/images/charachters/leatherFace.png"), 240, 100, 2, 3),//7
        new Grounded("Micheal Myers", QPixmap(":/images/charachters/michealMyers.png"), 160, 100, 2, 2),//8
        new Grounded("Death", QPixmap(":/images/charachters/death.png"), 320, 140, 2, 2),//9
        new Grounded("Hanibal Lector", QPixmap(":/images/charachters/hanibalLector.png"), 280, 80, 2, 2),//10
        new Grounded("Pin Head", QPixmap(":/images/charachters/pinHead.png"), 400, 100, 2, 1),//11
        new Grounded("Art The Clown", QPixmap(":/images/charachters/artTheClown.png"), 260, 80, 2, 2),//12
        new Grounded("esther", QPixmap(":/images/charachters/esther.png"), 400, 100, 2, 1),//13


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

    for(int i=0;i<48;i++){
        agentsPics[i]->setStyleSheet("border: 1px solid white;background-color:white;");
        agentsPics[i]->setFixedSize(60, 60);
        agentsPics[i]->move(20,20);
        agentsPics[i]->setText("");
        agentsPics[i]->setToolTip(characterList[i]->name);
    }



    for(int i = 0 ; i < 24; i++){
        agentsPics[i]->setIcon(characterList[i]->picture);
        agentsPics[i]->setIconSize(agentsPics[i]->size());
    }
    for(int i = 24 ; i < 48; i++){
        agentsPics[i]->setIcon(characterList[i]->picture);
        agentsPics[i]->setIconSize(agentsPics[i]->size());
    }





    //preys
    /*Characters indianaJones("indianaJones",QPixmap(":/images/charachters/IndianaJones.PNG"),100,40,3,1,false,true);
    ui->pushButton_p21->setIcon(QIcon(indianaJones.getPic()));
    ui->pushButton_p21->setIconSize(ui->pushButton_p21->size());
    Characters martyMcFly("martyMcFly",QPixmap(":/images/charachters/MartyMcFly.PNG"),100,40,2,1,false,true);
    ui->pushButton_p22->setIcon(QIcon(martyMcFly.getPic()));
    ui->pushButton_p22->setIconSize(ui->pushButton_p22->size());
    Characters johnMc1clane("chucky",QPixmap(":/images/charachters/JohnMcClane.PNG"),100,40,2,1,false,true);
    ui->pushButton_p23->setIcon(QIcon(johnMc1clane.getPic()));
    ui->pushButton_p23->setIconSize(ui->pushButton_p23->size());
    Characters rambo("rambo",QPixmap(":/images/charachters/rambo.PNG"),100,40,2,1,false,true);
    ui->pushButton_p24->setIcon(QIcon(rambo.getPic()));
    ui->pushButton_p24->setIconSize(ui->pushButton_p24->size());
    Characters rocky("rocky",QPixmap(":/images/charachters/RockyBalboa.PNG"),100,40,2,1,false,true);
    ui->pushButton_p25->setIcon(QIcon(rocky.getPic()));
    ui->pushButton_p25->setIconSize(ui->pushButton_p25->size());
    Characters johnKramer("frank",QPixmap(":/images/charachters/JohnKramer.PNG"),100,40,2,1,false,true);
    ui->pushButton_p26->setIcon(QIcon(johnKramer.getPic()));
    ui->pushButton_p26->setIconSize(ui->pushButton_p26->size());*/



    m_tilesB = {// for 2nd map
        ui->pushButton_B00, ui->pushButton_B20, ui->pushButton_B40, ui->pushButton_B60, ui->pushButton_B80,
        ui->pushButton_B10, ui->pushButton_B30, ui->pushButton_B50, ui->pushButton_B70,
        ui->pushButton_B01, ui->pushButton_B21, ui->pushButton_B41, ui->pushButton_B61, ui->pushButton_B81,
        ui->pushButton_B11, ui->pushButton_B31, ui->pushButton_B51, ui->pushButton_B71,
        ui->pushButton_B02, ui->pushButton_B22, ui->pushButton_B42, ui->pushButton_B62, ui->pushButton_B82,
        ui->pushButton_B12, ui->pushButton_B32, ui->pushButton_B52, ui->pushButton_B72,
        ui->pushButton_B03, ui->pushButton_B23, ui->pushButton_B43, ui->pushButton_B63, ui->pushButton_B83,
        ui->pushButton_B13, ui->pushButton_B33, ui->pushButton_B53, ui->pushButton_B73,
        ui->pushButton_B04, ui->pushButton_B24, ui->pushButton_B44, ui->pushButton_B64, ui->pushButton_B84
    };

    m_tilesB_2 = {// for 1st map
        ui->pushButton_B00_2, ui->pushButton_B20_2, ui->pushButton_B40_2, ui->pushButton_B60_2, ui->pushButton_B80_2,
        ui->pushButton_B10_2, ui->pushButton_B30_2, ui->pushButton_B50_2, ui->pushButton_B70_2,
        ui->pushButton_B01_2, ui->pushButton_B21_2, ui->pushButton_B41_2, ui->pushButton_B61_2, ui->pushButton_B81_2,
        ui->pushButton_B11_2, ui->pushButton_B31_2, ui->pushButton_B51_2, ui->pushButton_B71_2,
        ui->pushButton_B02_2, ui->pushButton_B22_2, ui->pushButton_B42_2, ui->pushButton_B62_2, ui->pushButton_B82_2,
        ui->pushButton_B12_2, ui->pushButton_B32_2, ui->pushButton_B52_2, ui->pushButton_B72_2,
        ui->pushButton_B03_2, ui->pushButton_B23_2, ui->pushButton_B43_2, ui->pushButton_B63_2, ui->pushButton_B83_2,
        ui->pushButton_B13_2, ui->pushButton_B33_2, ui->pushButton_B53_2, ui->pushButton_B73_2,
        ui->pushButton_B04_2, ui->pushButton_B24_2, ui->pushButton_B44_2, ui->pushButton_B64_2, ui->pushButton_B84_2
    };

    //funcs to work the game
    beautify();
    setCharacters();
    loadAndProcessMap();
    loadCustomFont();
    chooseType();
}


mapWindow::~mapWindow()
{
    delete ui;
    /*for (Characters* character : characterList) {
        delete character;
    }*/
    qDeleteAll(characterList);

}

//beautify
void mapWindow::beautify(){

    QPixmap all(":/images/icons/all.png");
    QPixmap grounded(":/images/icons/grounded.png");
    QPixmap waterWalking(":/images/icons/waterWalking.png");
    QPixmap floating(":/images/icons/floating.png");
    QPixmap flying(":/images/icons/flying.png");

    QPixmap health(":/images/icons/health.png");
    QPixmap attack(":/images/icons/attack.png");
    QPixmap mobility(":/images/icons/mobility.png");
    QPixmap range(":/images/icons/range.png");




    QVector<QGroupBox *> infoList = {
        ui->groupBox_p101info, ui->groupBox_p102info, ui->groupBox_p103info, ui->groupBox_p104info,//1
        ui->groupBox_p105info, ui->groupBox_p106info, ui->groupBox_p107info, ui->groupBox_p108info,
        ui->groupBox_p109info, ui->groupBox_p110info, ui->groupBox_p111info, ui->groupBox_p112info,
        ui->groupBox_p113info, ui->groupBox_p114info, ui->groupBox_p115info, ui->groupBox_p116info,//4
        ui->groupBox_p117info, ui->groupBox_p118info, ui->groupBox_p119info, ui->groupBox_p120info,
        ui->groupBox_p121info, ui->groupBox_p122info, ui->groupBox_p123info, ui->groupBox_p124info,

        ui->groupBox_p201info, ui->groupBox_p202info, ui->groupBox_p203info, ui->groupBox_p204info,//7
        ui->groupBox_p205info, ui->groupBox_p206info, ui->groupBox_p207info, ui->groupBox_p208info,
        ui->groupBox_p209info, ui->groupBox_p210info, ui->groupBox_p211info, ui->groupBox_p212info,
        ui->groupBox_p213info, ui->groupBox_p214info, ui->groupBox_p215info, ui->groupBox_p216info,//10
        ui->groupBox_p217info, ui->groupBox_p218info, ui->groupBox_p219info, ui->groupBox_p220info,
        ui->groupBox_p221info, ui->groupBox_p222info, ui->groupBox_p223info, ui->groupBox_p224info
    };


    QVector<QLabel*> typeList = {
        ui->label_p101type, ui->label_p102type, ui->label_p103type, ui->label_p104type,//1
        ui->label_p105type, ui->label_p106type, ui->label_p107type, ui->label_p108type,
        ui->label_p109type, ui->label_p110type, ui->label_p111type, ui->label_p112type,
        ui->label_p113type, ui->label_p114type, ui->label_p115type, ui->label_p116type,//4
        ui->label_p117type, ui->label_p118type, ui->label_p119type, ui->label_p120type,
        ui->label_p121type, ui->label_p122type, ui->label_p123type, ui->label_p124type,

        ui->label_p201type, ui->label_p202type, ui->label_p203type, ui->label_p204type,//7
        ui->label_p205type, ui->label_p206type, ui->label_p207type, ui->label_p208type,
        ui->label_p209type, ui->label_p210type, ui->label_p211type, ui->label_p212type,
        ui->label_p213type, ui->label_p214type, ui->label_p215type, ui->label_p216type,//10
        ui->label_p217type, ui->label_p218type, ui->label_p219type, ui->label_p220type,
        ui->label_p221type, ui->label_p222type, ui->label_p223type, ui->label_p224type
    };


    QVector<QLabel*> attackList = {
        ui->label_p101attack, ui->label_p102attack, ui->label_p103attack, ui->label_p104attack,//1
        ui->label_p105attack, ui->label_p106attack, ui->label_p107attack, ui->label_p108attack,
        ui->label_p109attack, ui->label_p110attack, ui->label_p111attack, ui->label_p112attack,
        ui->label_p113attack, ui->label_p114attack, ui->label_p115attack, ui->label_p116attack,//4
        ui->label_p117attack, ui->label_p118attack, ui->label_p119attack, ui->label_p120attack,
        ui->label_p121attack, ui->label_p122attack, ui->label_p123attack, ui->label_p124attack,

        ui->label_p201attack, ui->label_p202attack, ui->label_p203attack, ui->label_p204attack,//7
        ui->label_p205attack, ui->label_p206attack, ui->label_p207attack, ui->label_p208attack,
        ui->label_p209attack, ui->label_p210attack, ui->label_p211attack, ui->label_p212attack,
        ui->label_p213attack, ui->label_p214attack, ui->label_p215attack, ui->label_p216attack,//10
        ui->label_p217attack, ui->label_p218attack, ui->label_p219attack, ui->label_p220attack,
        ui->label_p221attack, ui->label_p222attack, ui->label_p223attack, ui->label_p224attack
    };

    QVector<QLabel*> hpList = {
        ui->label_p101hp, ui->label_p102hp, ui->label_p103hp, ui->label_p104hp,//1
        ui->label_p105hp, ui->label_p106hp, ui->label_p107hp, ui->label_p108hp,
        ui->label_p109hp, ui->label_p110hp, ui->label_p111hp, ui->label_p112hp,
        ui->label_p113hp, ui->label_p114hp, ui->label_p115hp, ui->label_p116hp,//4
        ui->label_p117hp, ui->label_p118hp, ui->label_p119hp, ui->label_p120hp,
        ui->label_p121hp, ui->label_p122hp, ui->label_p123hp, ui->label_p124hp,

        ui->label_p201hp, ui->label_p202hp, ui->label_p203hp, ui->label_p204hp,//7
        ui->label_p205hp, ui->label_p206hp, ui->label_p207hp, ui->label_p208hp,
        ui->label_p209hp, ui->label_p210hp, ui->label_p211hp, ui->label_p212hp,
        ui->label_p213hp, ui->label_p214hp, ui->label_p215hp, ui->label_p216hp,//10
        ui->label_p217hp, ui->label_p218hp, ui->label_p219hp, ui->label_p220hp,
        ui->label_p221hp, ui->label_p222hp, ui->label_p223hp, ui->label_p224hp
    };

    QVector<QLabel*> mobilityList = {
        ui->label_p101mobility, ui->label_p102mobility, ui->label_p103mobility, ui->label_p104mobility,//1
        ui->label_p105mobility, ui->label_p106mobility, ui->label_p107mobility, ui->label_p108mobility,
        ui->label_p109mobility, ui->label_p110mobility, ui->label_p111mobility, ui->label_p112mobility,
        ui->label_p113mobility, ui->label_p114mobility, ui->label_p115mobility, ui->label_p116mobility,//4
        ui->label_p117mobility, ui->label_p118mobility, ui->label_p119mobility, ui->label_p120mobility,
        ui->label_p121mobility, ui->label_p122mobility, ui->label_p123mobility, ui->label_p124mobility,

        ui->label_p201mobility, ui->label_p202mobility, ui->label_p203mobility, ui->label_p204mobility,//7
        ui->label_p205mobility, ui->label_p206mobility, ui->label_p207mobility, ui->label_p208mobility,
        ui->label_p209mobility, ui->label_p210mobility, ui->label_p211mobility, ui->label_p212mobility,
        ui->label_p213mobility, ui->label_p214mobility, ui->label_p215mobility, ui->label_p216mobility,//10
        ui->label_p217mobility, ui->label_p218mobility, ui->label_p219mobility, ui->label_p220mobility,
        ui->label_p221mobility, ui->label_p222mobility, ui->label_p223mobility, ui->label_p224mobility
    };

    QVector<QLabel*> rangeList = {
        ui->label_p101range, ui->label_p102range, ui->label_p103range, ui->label_p104range,//1
        ui->label_p105range, ui->label_p106range, ui->label_p107range, ui->label_p108range,
        ui->label_p109range, ui->label_p110range, ui->label_p111range, ui->label_p112range,
        ui->label_p113range, ui->label_p114range, ui->label_p115range, ui->label_p116range,//4
        ui->label_p117range, ui->label_p118range, ui->label_p119range, ui->label_p120range,
        ui->label_p121range, ui->label_p122range, ui->label_p123range, ui->label_p124range,

        ui->label_p201range, ui->label_p202range, ui->label_p203range, ui->label_p204range,//7
        ui->label_p205range, ui->label_p206range, ui->label_p207range, ui->label_p208range,
        ui->label_p209range, ui->label_p210range, ui->label_p211range, ui->label_p212range,
        ui->label_p213range, ui->label_p214range, ui->label_p215range, ui->label_p216range,//10
        ui->label_p217range, ui->label_p218range, ui->label_p219range, ui->label_p220range,
        ui->label_p221range, ui->label_p222range, ui->label_p223range, ui->label_p224range
    };



    for(int i=0;i<characterList.size();i++){
        infoList[i]->setStyleSheet("border:transparentt;");
        infoList[i]->move(90,20);

        typeList[i]->setStyleSheet("border:transparent;"
                                   "background:transparent;"
                                   "background-image:transparent;");
        typeList[i]->move(10,10);
        typeList[i]->setScaledContents(true);
        typeList[i]->setMaximumSize(20,20);

        attackList[i]->setPixmap(attack);
        attackList[i]->setScaledContents(true);
        attackList[i]->setToolTip(QString::number(characterList[i]->damage));

        hpList[i]->setPixmap(health);
        hpList[i]->setScaledContents(true);
        hpList[i]->setToolTip(QString::number(characterList[i]->health));

        mobilityList[i]->setPixmap(mobility);
        mobilityList[i]->setScaledContents(true);
        mobilityList[i]->setToolTip(QString::number(characterList[i]->mobility));

        rangeList[i]->setPixmap(range);
        rangeList[i]->setScaledContents(true);
        rangeList[i]->setToolTip(QString::number(characterList[i]->range));


        int type = characterList[i]->type;
        switch (type) {
        case 1://grounded
            typeList[i]->setPixmap(grounded);
            break;
        case 2://water walking
            typeList[i]->setPixmap(waterWalking);
            break;
        case 3://floating
            typeList[i]->setPixmap(floating);
            break;
        case 4://flying
            typeList[i]->setPixmap(flying);
            break;
        }
    }

}

//taking players names
void mapWindow::on_pushButton_confirmNames_clicked()
{
    player1.name=ui->textEdit_p1->toPlainText();
    player2.name=ui->textEdit_p2->toPlainText();
    ui->groupBox_names->hide();
    ui->groupBox_p1agents->setTitle(player1.name+"'s agents");
    ui->groupBox_p2agents->setTitle(player2.name+"'s agents");


}

//opening actual game map
void mapWindow::on_pushButton_allChosen_clicked()
{
    ui->groupBox_map->hide();
    ui->groupBox_p1agents->hide();
    ui->groupBox_p2agents->hide();
    ui->groupBox_bigMap->show();
}

//reading a map
QString mapWindow::loadRandomMap() {
    const QStringList availableMaps = {
        ":/map/maps/grid1.txt",
        ":/map/maps/grid2.txt",
        ":/map/maps/grid3.txt",
        ":/map/maps/grid4.txt",
        ":/map/maps/grid5.txt",
        ":/map/maps/grid6.txt",
        ":/map/maps/grid7.txt",
        ":/map/maps/grid8.txt"
    };

    int randomIndex = QRandomGenerator::global()->bounded(availableMaps.size());
    QString selectedPath = availableMaps.at(randomIndex);

    // Show the selected index and file path
    /*QMessageBox::information(this, "Random Map Selected",
                             QString("Index: %1\nPath: %2").arg(randomIndex).arg(selectedPath));*/

    // Load the file
    QFile file(selectedPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open map file:" << selectedPath;
        return QString();
    }

    return QTextStream(&file).readAll();
}

//custom font
void mapWindow::loadCustomFont() {
    int fontId = QFontDatabase::addApplicationFont(":/font/pixelFont.ttf");

    if (fontId == -1) {
        qWarning() << "Failed to load font!";
        return;
    }

    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont buttonFont(fontFamily, 12);
    QFont groupBoxFont(fontFamily, 10);

    ui->pushButton_allChosen->setFont(buttonFont);
    ui->groupBox_names->setFont(groupBoxFont);
    ui->label->setFont(groupBoxFont);
    ui->label_2->setFont(groupBoxFont);
    ui->label_3->setFont(groupBoxFont);
    ui->pushButton_confirmNames->setFont(groupBoxFont);
    ui->textEdit_p1->setFont(groupBoxFont);
    ui->textEdit_p2->setFont(groupBoxFont);
    ui->label_setting->setFont(groupBoxFont);
    ui->groupBox_p1agents->setFont(groupBoxFont);
    ui->groupBox_p2agents->setFont(groupBoxFont);
    ui->pushButton_p1all->setFont(groupBoxFont);
    ui->pushButton_p2all->setFont(groupBoxFont);

}

//process map
void mapWindow::loadAndProcessMap() {
    QString mapContent = loadRandomMap();
    QString processedMap;
    processedMap.reserve(41);
    if(!mapContent.isEmpty()){
        int size=mapContent.size()-28;
        for(int i=0;i<size;i++){
            if(mapContent[i]=='/' && i+1 < size){
                QChar next=mapContent[i+1];
                switch (next.toLatin1()){
                    case '1':
                        processedMap.append('1');
                        break;
                    case '2':
                        processedMap.append('2');
                        break;
                    case ' ':
                       processedMap.append('3');//for land
                        break;
                    case '~':
                        processedMap.append('4');//for water
                        break;
                    case '#':
                        processedMap.append('5');//for mountain
                        break;
                }
                i++;
            }
        }
    }

    int count=0;
    //int i = 0,j = 0;
    const int verticalHex[][2]={{-4,0},{-2,-1},{0,-2},{2,-3},{4,-4},
                                {-3,0},{-1,-1},{1,-2},{3,-3},
                                {-4,1},{-2,0},{0,-1},{2,-2},{4,-3},
                                {-3,1},{-1,0},{1,-1},{3,-2},
                                {-4,2},{-2,1},{0,0},{2,-1},{4,-2},
                                {-3,2},{-1,1},{1,0},{3,-1},
                                {-4,3},{-2,2},{0,1},{2,0},{4,-1},
                                {-3,3},{-2,2},{1,1},{3,0},
                                {-4,4},{-2,3},{0,2},{2,1},{4,0}};

    while (count < 41){
        tilesList[count].column = verticalHex[count][0];
        tilesList[count].row = verticalHex[count][1];
        tilesList[count].landscape = processedMap[count].digitValue();
        count++;
    }

    /*while (count < 41) {
        if (i % 2 == 0) { // even column
            for (j = 0; j < 5; j++) {
                tilesList[count].row = i;
                tilesList[count].column = j;
                tilesList[count].landscape = processedMap[count].digitValue();
                count++;
            }
        } else { // odd column
            for (j = 0; j < 4; j++) {
                tilesList[count].row = i;
                tilesList[count].column = j;
                tilesList[count].landscape = processedMap[count].digitValue();
                count++;
            }
        }
        i++;
    }*/
    /*while(count<41){
        i=0;
        while(i%2==0 && i<9 && j<5){
            tilesList[count].row=i;
            tilesList[count].column=j;
            tilesList[count].landscape = processedMap[count].digitValue();
            i+=2;
            count++;
        }
        i=1;
        while(i%2==1 && i<9 && j<4){
            tilesList[count].row=i;
            tilesList[count].column=j;
            tilesList[count].landscape = processedMap[count].digitValue();
            i+=2;
            count++;
        }
        j++;
    }*/

    QVector<QLabel*> labels = {//for 1st map
            ui->label_00, ui->label_20, ui->label_40,ui->label_60,ui->label_80,
            ui->label_10, ui->label_30, ui->label_50,ui->label_70,
            ui->label_01, ui->label_21, ui->label_41,ui->label_61,ui->label_81,
            ui->label_11, ui->label_31, ui->label_51,ui->label_71,
            ui->label_02, ui->label_22, ui->label_42,ui->label_62,ui->label_82,
            ui->label_12, ui->label_32, ui->label_52,ui->label_72,
            ui->label_03, ui->label_23, ui->label_43,ui->label_63,ui->label_83,
            ui->label_13, ui->label_33, ui->label_53,ui->label_73,
            ui->label_04, ui->label_24, ui->label_44,ui->label_64,ui->label_84,
            };

    for(int i=0;i<41;i++){
        labels[i]->hide();
        if(tilesList[i].landscape==1){//p1 land red
            labels[i]->setStyleSheet("background-image: url(:/images/land-p1.png);"
                                     "border: 0.5px solid black;");
            m_tilesB[i]->setStyleSheet("background-image: url(:/images/land.png);"
                                      "border: 1.5px solid black;");
            m_tilesB_2[i]->setStyleSheet("background-image: url(:/images/land-p1.png);"
                                     "border: 0.5px solid black;");

        }
        else if(tilesList[i].landscape==2){//p2 land blue
            labels[i]->setStyleSheet("background-image: url(:/images/land-p2.png);"
                                     "border: 0.5px solid black;");
            m_tilesB[i]->setStyleSheet("background-image: url(:/images/land.png);"
                                      "border: 1.5px solid black;");
            m_tilesB_2[i]->setStyleSheet("background-image: url(:/images/land-p2.png);"
                                     "border: 0.5px solid black;");
        }
        else if(tilesList[i].landscape==3){//normal land
            labels[i]->setStyleSheet("background-image: url(:/images/land.png);"
                                     "border: 0.5px solid black;");
            m_tilesB[i]->setStyleSheet("background-image: url(:/images/land.png);"
                                      "border: 1.5px solid black;");
            m_tilesB_2[i]->setStyleSheet("background-image: url(:/images/land.png);"
                                     "border: 0.5px solid black;");
        }
        else if(tilesList[i].landscape==4){//water
            labels[i]->setStyleSheet("background-image: url(:/images/water.png);"
                                     "border: 0.5px solid black;");
            m_tilesB[i]->setStyleSheet("background-image: url(:/images/water.png);"
                                      "border: 1.5px solid black;");
            m_tilesB_2[i]->setStyleSheet("background-image: url(:/images/water.png);"
                                      "border: 0.5px solid black;");
        }
        else if(tilesList[i].landscape==5){//mountain
            labels[i]->setStyleSheet("background-image: url(:/images/mountain.png);"
                                     "border: 0.5px solid black;");
            m_tilesB[i]->setStyleSheet("background-image: url(:/images/mountain.png);"
                                      "border: 1.5px solid black;");
            m_tilesB_2[i]->setStyleSheet("background-image: url(:/images/mountain.png);"
                                     "border: 0.5px solid black;");
        }
    }
}





//set characters
void mapWindow::setCharacters() {

    size = agentsPics.size();
    halfSize = size/2;

    for (int i = 0; i < size ; i++) {
        connect(agentsPics[i], &QPushButton::clicked, this, [this, i]() {
            m_selectedIcon = agentsPics[i]->icon();
            m_selectedPlayerButtonIndex = i;
            qDebug() << "Player button clicked:" << i;

            bool isPlayer1 = (i < halfSize);
            int requiredLandscape = isPlayer1 ? 1 : 2;

            for (int k = 0; k < 41; k++) {
                bool isAvailable = (tilesList[k].landscape == requiredLandscape) && tilesList[k].isEmpty;
                m_tilesB_2[k]->setEnabled(isAvailable);

            }
        });
    }

    if (m_tilesB.size() == m_tilesB_2.size()) {
        for (int i = 0; i < 41; ++i) {
            connect(m_tilesB_2[i], &QPushButton::clicked, this, [this, i]() {

                //these are important
                //put row and column of the chosen tile in the row and column of the character
                characterList[m_selectedPlayerButtonIndex]->row = tilesList[i].row;
                characterList[m_selectedPlayerButtonIndex]->column = tilesList [i].column;
                //put the type of the chosen character in the type of the chosen tile
                tilesList[i].type = characterList[m_selectedPlayerButtonIndex]->type;
                //put the index of the chosen character in the occupiedByIndex of the tile
                tilesList[i].occupiedByIndex = m_selectedPlayerButtonIndex;

                bool isPlayer1 = (m_selectedPlayerButtonIndex < 24);
                if(isPlayer1) {
                    p1Count++;
                    player1.playerCharacters.push_back(characterList[m_selectedPlayerButtonIndex]);
                    player1.playerTiles.push_back(i);
                }
                if(!isPlayer1) {
                    p2Count++;
                    player2.playerCharacters.push_back(characterList[m_selectedPlayerButtonIndex]);
                    player2.playerTiles.push_back(i);
                }

                if (!m_selectedIcon.isNull()) {
                    m_tilesB_2[i]->setIcon(m_selectedIcon);
                    m_tilesB[i]->setIcon(m_selectedIcon);
                    m_tilesB_2[i]->setIconSize(m_tilesB_2[i]->size());
                    m_tilesB[i]->setIconSize(m_tilesB[i]->size());
                    agentsPics[m_selectedPlayerButtonIndex]->setEnabled(false);

                    qDebug() << "Tile updated at index:" << i;
                } else {
                    qWarning() << "No icon selected! Click a player button first.";
                }

                if (m_selectedPlayerButtonIndex != -1) {
                    agentsPics[m_selectedPlayerButtonIndex]->setEnabled(false);
                    m_selectedPlayerButtonIndex = -1;  // Reset selection
                }

                if(p1Count==5){
                    for(int i=0;i<halfSize;i++){
                        agentsPics[i]->setEnabled(false);

                    }
                }
                if(p2Count==5){
                    for(int i=halfSize;i<size;i++){
                        agentsPics[i]->setEnabled(false);
                    }
                }
                if(p2Count==5 && p1Count==5){
                    ui->pushButton_allChosen->show();
                }

                m_tilesB_2 [i]->setEnabled(false);
                tilesList[i].isEmpty = false;
            });
        }
    } else {
        qCritical() << "Tile button vectors are different sizes!";
    }




}

//types
void mapWindow::chooseType(){
    typeButtons = { ui->pushButton_p1all,ui->pushButton_p1type1,ui->pushButton_p1type2,ui->pushButton_p1type3,ui->pushButton_p1type4,
                    ui->pushButton_p2all,ui->pushButton_p2type1,ui->pushButton_p2type2,ui->pushButton_p2type3,ui->pushButton_p2type4};

    agentsGRPBX = {
        ui->groupBox_p101, ui->groupBox_p102, ui->groupBox_p103, ui->groupBox_p104,//1
        ui->groupBox_p105, ui->groupBox_p106, ui->groupBox_p107, ui->groupBox_p108,
        ui->groupBox_p109, ui->groupBox_p110, ui->groupBox_p111, ui->groupBox_p112,
        ui->groupBox_p113, ui->groupBox_p114, ui->groupBox_p115, ui->groupBox_p116,//4
        ui->groupBox_p117, ui->groupBox_p118, ui->groupBox_p119, ui->groupBox_p120,
        ui->groupBox_p121, ui->groupBox_p122, ui->groupBox_p123, ui->groupBox_p124,

        ui->groupBox_p201, ui->groupBox_p202, ui->groupBox_p203, ui->groupBox_p204,//7
        ui->groupBox_p205, ui->groupBox_p206, ui->groupBox_p207, ui->groupBox_p208,
        ui->groupBox_p209, ui->groupBox_p210, ui->groupBox_p211, ui->groupBox_p212,
        ui->groupBox_p213, ui->groupBox_p214, ui->groupBox_p215, ui->groupBox_p216,//10
        ui->groupBox_p217, ui->groupBox_p218, ui->groupBox_p219, ui->groupBox_p220,
        ui->groupBox_p221, ui->groupBox_p222, ui->groupBox_p223, ui->groupBox_p224
    };


    for (int btn = 0; btn < typeButtons.size(); ++btn) {
        connect(typeButtons[btn], &QPushButton::clicked, this, [this, btn]() {
            bool isPlayer1 = btn < 5;
            int startIndex = isPlayer1 ? 0 : 24;
            int endIndex   = isPlayer1 ? 24 : 48;
            int yPos       = 40;
            int typeBTN    = btn % 5;

            if (characterList.size() < 48) {
                qWarning() << "characterList too small!";
                return;
            }

            // Loop only through the relevant 24 group boxes
            for (int j = startIndex; j < endIndex; ++j) {
                bool matches = (typeBTN == 0 || typeBTN == characterList[j]->type);
                if (matches) {
                    agentsGRPBX[j]->show();
                    agentsGRPBX[j]->move(0, yPos);
                    yPos += 107;
                } else {
                    agentsGRPBX[j]->hide();
                }
            }

            qDebug() << "Button" << btn
                     << "(" << (isPlayer1 ? "P1" : "P2") << " type" << typeBTN << ") clicked.";
        });
    }



    /*for(int i=0;i<10;i++){
        connect(typeButtons[i], &QPushButton::clicked, this, [this, i]() {
            bool isPlayer1 = i<5;

            if(isPlayer1){
                agentsGRPBX[i]->show();
                x1=40;
                typeBTN = i%5;
                for(x2=0;x2<24;x2++){
                    if(!typeBTN){
                        agentsGRPBX[x2]->move(0,x1);
                        x1+=107;
                    }
                    else if(typeBTN == characterList[x2]->type){
                        agentsGRPBX[x2]->move(0,x1);
                        x1+=107;
                    }
                    else{
                        agentsGRPBX[x2]->hide();
                    }
                }
            }
            else{
                agentsGRPBX[i]->show();
                x2=40;
                typeBTN = i%5;
                for(x1=24;x1<48;x1++){
                    if(!typeBTN){
                        agentsGRPBX[x1]->move(0,x2);
                        x2+=107;
                    }
                    else if(typeBTN == characterList[x1]->type){
                        agentsGRPBX[x1]->move(0,x2);
                        x2+=107;
                    }
                    else{
                        agentsGRPBX[x1]->hide();
                    }
                }
            }
            qDebug()<<i<<"*";
        });

    }*/
}

//setting
void mapWindow::on_pushButton_setting_clicked()
{
    ui->groupBox_setting->show();

}

//undo
void mapWindow::on_pushButton_undo_clicked()
{
    for(int i = 0 ; i < size ; i++){
        agentsPics[i] -> setEnabled(true);
    }

    for(int i = 0 ; i < 41 ; i++){
        m_tilesB_2[i] -> setEnabled(true);
        m_tilesB_2[i] -> setIcon(QIcon());
        m_tilesB[i] -> setEnabled(true);
        m_tilesB[i] -> setIcon(QIcon());
        tilesList[i].isEmpty = true;
    }

    ui->pushButton_allChosen->hide();
    p1Count = 0;
    p2Count = 0;
}

//check if every cell has been visited
/*bool allVisited(hexGrid visitedList[]){
    for(int i=0;i<41;i++){
        if(!visitedList[i].visited){
            return false;
        }
    }
    return true;
}*/


//check if they can go there
void mapWindow::can(int fromIndex,int type,bool isPlayer1Turn){

    for(int i=0;i<41;i++){
        if(tilesList[i].landscape == 1 || tilesList[i].landscape == 2){//this is just cuz i dont neeed them to b different no more
            tilesList[i].landscape = 3;
        }
    }

    for(int i=0;i<41;i++){
        m_tilesB[i]->setEnabled(true);
        QString currentStyle = m_tilesB[i]->styleSheet();
        m_tilesB[i]->setStyleSheet(currentStyle + "border: 1.5px solid black;");
        m_tilesB[i]->setEnabled(true);
        //m_tilesB[i]->setStyleSheet("border:1.5px solid black;");
    }




    // Initialize board
    QVector<QVector<hex>> board(9);
    for (int i = 0; i < 9; i++) {
        int cols = (i % 2 == 0) ? 5 : 4;
        board[i].resize(cols);
        for (int j = 0; j < cols; j++) {
            board[i][j] = hex(i, j);
        }
    }

    /*QVector<QVector<hex>> board(9);
    for(int i=0; i<9; i++) {
        board[i].resize((i%2 == 0) ? 5 : 4);  // 5 for even rows, 4 for odd rows
    }*/

    //qDebug()<<"board made";


    /*QVector<QVector<hex>> board(9);

    for(int i=0;i<9;i++){
        if(i%2 == 0){
            for(int j=0;j<5;j++){
                board[i][j] = hex(i,j);
            }
        }
        else{
            for(int j=0;j<4;j++){
                board[i][j] = hex(i,j);
            }
        }
    }*/

    hex start;
    int index=0;
    for(int i=0;i<9;i++){
        for(int j=0;j<board[i].size();j++){
            board[i][j].index = index;
            board[i][j].row = i;
            board[i][j] .column = j;
            switch(type){
                case 1://grounded
                    if(tilesList[index].landscape != 3){//if it was not normal land
                        board[i][j].crossable = false;
                    }
                    break;
                case 2://water walking
                    if(tilesList[index].landscape == 5){//if it was mountain
                        board[i][j].crossable = false;
                    }
                    break;
                case 3://floating
                case 4://flying
                    board[i][j].crossable = true;//can cross everyhthing
                    break;
            }
            if(index == fromIndex){
                start = board[i][j];
                board[i][j].distance = 0;
            }
            index++;
        }
    }

    /*for(int i=0;i<9;i++){
        for(int j=0;j<board[i].size();j++){
            qDebug()<<board[i][j].crossable;
        }
    }*/

    start.distance = 0;

    auto inBounds = [&](int i, int j) {
        return i >= 0 && i < board.size() && j >= 0 && j < board[i].size();
    };

    bool changed = true;
    while (changed) {
        changed = false;

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < board[i].size(); j++) {
                if (!board[i][j].crossable) continue;

                int minVal = board[i][j].distance;

                // Pointy-topped neighbors differ by row parity
                QVector<QPair<int, int>> neighbors;
                if (i % 2 == 0) {
                    neighbors = {
                        {i - 2, j},     // up
                        {i - 1, j},     // up-right
                        {i - 1, j - 1}, // up-left
                        {i + 1, j},     // down-right
                        {i + 1, j - 1}, // down-left
                        {i + 2, j}      // down
                    };
                } else {
                    neighbors = {
                        {i - 2, j},     // up
                        {i - 1, j + 1}, // up-right
                        {i - 1, j},     // up-left
                        {i + 1, j + 1}, // down-right
                        {i + 1, j},     // down-left
                        {i + 2, j}      // down
                    };
                }

                for (const auto& [ni, nj] : neighbors) {
                    if (inBounds(ni, nj) && board[ni][nj].crossable) {
                        if (board[ni][nj].distance + 1 < minVal) {
                            minVal = board[ni][nj].distance + 1;
                        }
                    }
                }

                if (minVal < board[i][j].distance) {
                    board[i][j].distance = minVal;
                    changed = true;
                }
            }
        }
    }

    /*for (int i = 0; i < 9; i++) {
        for (int j = 0; j < board[i].size(); j++) {
            qDebug()<<i<<"*"<<j<<board[i][j].distance;
        }
    }*/

    index=0;
    int mobility = characterList[tilesList[fromIndex].occupiedByIndex]->mobility;
    //qDebug()<<"mobility"<<mobility;
    while(index<41){
        for(int i=0;i<9;i++){
            for(int j=0;j<board[i].size();j++){
                if(board[i][j].distance <= mobility){
                    QString currentStyle = m_tilesB[index]->styleSheet();
                    m_tilesB[index]->setStyleSheet(currentStyle + "border: 3px solid white;");
                }

                else{
                    m_tilesB[index]->setEnabled(false);
                }
                if(isPlayer1Turn && tilesList[index].occupiedByIndex < 24){
                    m_tilesB[index]->setEnabled(true);
                }
                else if(!isPlayer1Turn && tilesList[index].occupiedByIndex >= 24){
                    m_tilesB[index]->setEnabled(true);
                }
                index++;
            }
        }
    }


    int range =  (characterList[tilesList[fromIndex].occupiedByIndex]->range) * 90 * 1.5;
    qDebug()<<"ragne  = "<<range;
    for(int i=0;i<9;i++){
        for(int j=0;j<board[i].size();j++){
            if(board[i][j].distance == mobility) {
                int centerX = m_tilesB[board[i][j].index]->geometry().center().x();
                int centerY = m_tilesB[board[i][j].index]->geometry().center().y();
                //qDebug()<<i<<" * "<<j;

                //qDebug()<<"cnenter"<<centerX<<" - "<<centerY;
                index = 0;
                for(int k=0;k<9;k++){
                    for(int l=0;l<board[k].size();l++){
                        int targetX = m_tilesB[board[k][l].index]->geometry().center().x();
                        int targetY = m_tilesB[board[k][l].index]->geometry().center().y();


                        //qDebug()<<k<<" ! "<<l;

                        //qDebug()<<"target"<<targetX<<" / "<<targetY;

                        int dx = targetX - centerX;
                        int dy = targetY - centerY;

                        int distanceSquared = dx * dx + dy * dy;
                        //qDebug()<<"ds"<<k<<"/"<<l<<"   "<<distanceSquared;
                        //qDebug()<<"index"<<index;

                        if (distanceSquared <= range * range && board[k][l].distance > mobility){
                            qDebug()<<"done!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1";
                            QString currentStyle = m_tilesB[index]->styleSheet();
                            m_tilesB[index]->setStyleSheet(currentStyle + "border: 3px solid red;");
                            m_tilesB[index]->setEnabled(true);
                        }
                        index++;
                    }
                }
            }
        }
    }
}


    /*index = 0;
    int index2;
    while(index < 41){
        index2 = 0;
        while(index2 < 41){
            for(int i=0;i<9;i++){
                for(int j=0;j<board[i].size();j++){
                    if(board[i][j].distance == mobility){
                        int centerX = m_tilesB[index]->geometry().center().x();
                        int centerY = m_tilesB[index]->geometry().center().y();

                        int targetX = m_tilesB[index2]->geometry().center().x();
                        int targetY = m_tilesB[index2]->geometry().center().y();

                        int dx = targetX - centerX;
                        int dy = targetY - centerY;

                        int distanceSquared = dx * dx + dy * dy;

                        if (distanceSquared <= range * range && board[i][j].distance > mobility){
                            QString currentStyle = m_tilesB[index2]->styleSheet();
                            m_tilesB[index2]->setStyleSheet(currentStyle + "border: 3px solid pink;");
                            //m_tilesB[j]->setStyleSheet("border:1.5px solid red;");
                            m_tilesB[index2]->setEnabled(true);
                        }
                    }
                }
            }
            index2++;
        }
        index++;
    }*/
        /*if(board[i].distance == mobility){
            int centerX = m_tilesB[i]->geometry().center().x();
            int centerY = m_tilesB[i]->geometry().center().y();
            for(int j=0;j<41;j++){
                int targetX = m_tilesB[j]->geometry().center().x();
                int targetY = m_tilesB[j]->geometry().center().y();
                int dx = targetX - centerX;
                int dy = targetY - centerY;
                int distanceSquared = dx * dx + dy * dy;
                if (distanceSquared <= range * range && board[j].distance > mobility){
                    QString currentStyle = m_tilesB[i]->styleSheet();
                    m_tilesB[i]->setStyleSheet(currentStyle + "border: 3px solid pink;");
                    //m_tilesB[j]->setStyleSheet("border:1.5px solid red;");
                    m_tilesB[j]->setEnabled(true);
                }
            }*/



    /*index = 0;
    while(index<41){
        for(int i=0;i<9;i++){
            for(int j=0;j<board[i].size();i+j++){

            }
        }
    }*/

    /*index = 0;
    while(index<41){
        for(int i=0;i<9;i++){
            for(int j=0;j<board[i].size();j++){
                if(board[i][j].distance > mobility && board[i][j].distance < mobility + range){
                    m_tilesB[index]->setEnabled(true);
                    QString currentStyle = m_tilesB[index]->styleSheet();
                    m_tilesB[index]->setStyleSheet(currentStyle + "border: 3px solid red;");
                    //m_tilesB[i]->setStyleSheet("border:1.5px solid green;");
                }
                index++;
            }
        }
    }*/




    /*const int hexDirectionIndex[6] = {-5, -9, -4, 5, 9, 4};//up left - up - up right - down right - down - down left


    hexGrid board[41];
    for(int i=0;i<41;i++){
        board[i].column = tilesList[i].column;
        board[i].visited = false;
        board[i].distance = 100;
        board[i].index = i;
        //board[i].crossable = true;
        switch (type) {
        case 1://grounded
            if(tilesList[i].landscape != 3){//if it was not normal land
                board[i].crossable = false;
            }
            break;
        case 2://water walking
            if(tilesList[i].landscape == 5){//if it was mountain
                board[i].crossable = false;
            }
            break;
        case 3://floating
                board[i].crossable = true;//can cross everyhthing
            break;
        case 4://flying
                board[i].crossable = true;//can cross everyhthing
            break;
            }
    }
        board[fromIndex].visited = true;
        board[fromIndex].distance = 0;
        hexGrid current = board[fromIndex];
        hexGrid neighbor;


        for(int j=0;j<6;j++){
            for(int i=0;i<6;i++){
                if(current.index + hexDirectionIndex[i] < 41 && current.index + hexDirectionIndex[i] > -1){
                    neighbor = board[current.index + hexDirectionIndex[i]];
                    if(board[neighbor.index].crossable == false){
                        board[neighbor.index].visited = true;
                    }
                    else if(current.index == 18){
                        int minVal = std::min({board[9].distance,
                                               board[14].distance,
                                               board[23].distance,
                                               board[27].distance});
                    }
                    else{
                        neighbor.visited = true;
                        int minVal = std::min( {board[neighbor.index + hexDirectionIndex[0]].distance,
                                               board[neighbor.index + hexDirectionIndex[1]].distance,
                                               board[neighbor.index + hexDirectionIndex[2]].distance,
                                               board[neighbor.index + hexDirectionIndex[3]].distance,
                                               board[neighbor.index + hexDirectionIndex[4]].distance,
                                               board[neighbor.index + hexDirectionIndex[5]].distance});
                        if(board[neighbor.index].distance > minVal + 1){
                            board[neighbor.index].distance = minVal + 1;
                        }
                    }
                }
            }
            if(current.index + hexDirectionIndex[j] < 41 && current.index + hexDirectionIndex[j] > -1){
                current = board[current.index + hexDirectionIndex[j]];
            }
        }


    int mobility = characterList[tilesList[fromIndex].occupiedByIndex]->mobility;
    for(int i=0;i<41;i++){
        if(board[i].distance < mobility){
            m_tilesB[i]->setEnabled(true);
            QString currentStyle = m_tilesB[i]->styleSheet();
            m_tilesB[i]->setStyleSheet(currentStyle + "border: 3px solid white;");
            //m_tilesB[i]->setStyleSheet("border:1.5px solid green;");
        }
    }

    int range = characterList[tilesList[fromIndex].occupiedByIndex]->range;
    for(int i=0;i<41;i++){
        if(board[i].distance > mobility && board[i].distance < mobility + range){
            m_tilesB[i]->setEnabled(true);
            QString currentStyle = m_tilesB[i]->styleSheet();
            m_tilesB[i]->setStyleSheet(currentStyle + "border: 3px solid cyan;");
            //m_tilesB[i]->setStyleSheet("border:1.5px solid green;");
        }
    }

    for(int i=0;i<41;i++){
        if(board[i].distance == mobility){
            int centerX = m_tilesB[i]->geometry().center().x();
            int centerY = m_tilesB[i]->geometry().center().y();
            for(int j=0;j<41;j++){
                int targetX = m_tilesB[j]->geometry().center().x();
                int targetY = m_tilesB[j]->geometry().center().y();
                int dx = targetX - centerX;
                int dy = targetY - centerY;
                int distanceSquared = dx * dx + dy * dy;
                if (distanceSquared <= range * range && board[j].distance > mobility){
                    QString currentStyle = m_tilesB[i]->styleSheet();
                    m_tilesB[i]->setStyleSheet(currentStyle + "border: 3px solid pink;");
                    //m_tilesB[j]->setStyleSheet("border:1.5px solid red;");
                    m_tilesB[j]->setEnabled(true);
                }
            }
        }
    }*/
//}



void mapWindow::startTurn(bool whoseTurn) {

    for (int i = 0; i < 41; ++i) {
        m_tilesB[i]->setEnabled(false); // disable all first
    }
    if(whoseTurn){
        currentPlayer = &player1;
    }
    else{
        currentPlayer = &player2;
    }

    for(int i=0;i<currentPlayer->playerCharacters.size();i++){
        m_tilesB[currentPlayer->playerTiles[i]]->setEnabled(true);
    }

    /*if(whoseTurn){
        for(int i=0;i<player1.playerCharacters.size();i++){
            m_tilesB[player1.playerTiles[i]]->setEnabled(true);
        }
        currentPlayer = &player1;

    }
    else{
        for(int i=0;i<player2.playerCharacters.size();i++){
            m_tilesB[player2.playerTiles[i]]->setEnabled(true);
        }
        currentPlayer = &player2;
    }*/
    /*for (int i = 0; i < 41; ++i) {
        m_tilesB[i]->setEnabled(false); // disable all first
    }

    for (int i = 0; i < currentPlayer.playerTiles.size(); ++i) {
        int tileIndex = currentPlayer.playerTiles[i];
        m_tilesB[tileIndex]->setEnabled(true);
    }

    //currentTurnPlayer = &currentPlayer;*/
}


void mapWindow::gameOver(bool whoseTurn){

    QLabel *gifLabel = new QLabel(this); // Or use an existing QLabel from the UI
    QMovie *movie = new QMovie(":/images/victoryDance.gif"); // or "loading.gif" if not using resources

    gifLabel->setMovie(movie);
    movie->start();

    if(whoseTurn){
        ui->groupBox_gameOver->show();
        ui->label_gameover->setText("GAME OVER!\n"
                                    +player1.name+"won");
    }
    else{
        ui->groupBox_gameOver->show();
        ui->label_gameover->setText("GAME OVER!\n"
                                    +player2.name+"won");
    }
}

int mapWindow::afterAttackMovement(int defenderIndex,int attackerType){
    QQueue<int> neighbors;
    int centerX = m_tilesB[defenderIndex]->geometry().center().x();
    int centerY = m_tilesB[defenderIndex]->geometry().center().y();
    int targetX,targetY;
    int qSize;




    for(int i=0 ; i<41;i++){
        targetX = m_tilesB[i]->geometry().center().x();
        targetY = m_tilesB[i]->geometry().center().y();

        int dx = targetX - centerX;
        int dy = targetY - centerY;

        int distanceSquared = dx * dx + dy * dy;



        if(distanceSquared <= 135){
            if(attackerType == 1 || attackerType == 4){//grounded or flying
                if(tilesList[i].landscape == 3){//is land
                    neighbors.append(i);
                }
            }
            else if(attackerType == 2){//water walking
                if(tilesList[i].landscape != 5){//is not mountain
                    neighbors.append(i);
                }
            }
            else{
                neighbors.append(i);
            }
        }
    }

    qSize = neighbors.size();
    int randomValue = QRandomGenerator::global()->bounded(qSize);

    return neighbors[randomValue];
}


//actual game
void mapWindow::actualGame() {
    player1.turn = true; player2.turn = false;
    isPlayer1Turn = false;
    while(!player1.playerCharacters.empty() || !player2.playerCharacters.empty()){
        isPlayer1Turn = !isPlayer1Turn;
        for(int i=0;i<41;i++){
            startTurn(isPlayer1Turn);
            /*if(player1.turn) {
                m_tilesB[player1.playerTiles[i]]->setEnabled(true);
            }
            else if(player2.turn){
                m_tilesB[player2.playerTiles[i]]->setEnabled(true);
            }
            else{
                m_tilesB[i]->setEnabled(false);
            }*/

            connect(m_tilesB[i], &QPushButton::clicked, this, [this, i]() {
                selectedFrom = i;
                m_selectedIcon = m_tilesB[i]->icon();
                can(m_selectedPlayerButtonIndex,tilesList[i].type,isPlayer1Turn);
            });
        }

        for(int i=0;i<41;i++){
            connect(m_tilesB[i], &QPushButton::clicked, this, [this, i]() {
                selectedTo = i;

                if(tilesList[selectedTo].occupiedByIndex == 100){//destination is empty
                    m_tilesB[selectedTo]->setIcon(m_selectedIcon);
                    m_tilesB[selectedFrom]->setIcon(QIcon());

                    tilesList[selectedTo].occupiedByIndex = tilesList[selectedFrom].occupiedByIndex;
                    tilesList[selectedFrom].occupiedByIndex = 100;

                    tilesList[selectedTo].type = tilesList[selectedFrom].type;
                    tilesList[selectedFrom].type = 100;
                }

                int charIndexTo = tilesList[selectedTo].occupiedByIndex;

                /*if((charIndexTo < 24 && isPlayer1Turn) || (charIndexTo >= 24 && !isPlayer1Turn)){//destination has a character from the same player
                    actualGame();
                }*/


                if((charIndexTo < 24 && !isPlayer1Turn) || (charIndexTo >= 24 && isPlayer1Turn)){//destination has a character from the opposing player
                    //attack(characterList[selectedFrom],characterList[selectedTo]);
                    Characters* attacker = characterList[selectedFrom];
                    Characters* defender = characterList[selectedTo];
                    int moveAttackerHere;

                    attacker->attack(*defender);
                    if(defender->health <= 0){//if defender is unalived
                        m_tilesB[selectedTo]->setIcon(QIcon());
                        tilesList[selectedTo].occupiedByIndex = 100;
                    }
                    else if(attacker->health <= 0){//if attacker is unalived
                        m_tilesB[selectedFrom]->setIcon(QIcon());
                        tilesList[selectedFrom].occupiedByIndex = 100;
                    }
                    else{//if neither is unalived
                        moveAttackerHere = afterAttackMovement(selectedTo,tilesList[selectedFrom].type);

                        m_tilesB[selectedFrom]->setIcon(QIcon());
                        m_tilesB[moveAttackerHere]->setIcon(m_selectedIcon);

                        tilesList[moveAttackerHere].type = tilesList[selectedFrom].type ;
                        tilesList[selectedFrom].type = 100;

                        tilesList[moveAttackerHere].occupiedByIndex = tilesList[selectedFrom].occupiedByIndex;
                        tilesList[selectedFrom].occupiedByIndex = 100;
                    }
                }
            });
        }


        gameOver(isPlayer1Turn);

        //for (int i = 0; i < 41; ++i) {}
    }

        /*if(player1.playerCharacters.empty()){
            ui->label_gameover->show();
            ui->label_gameover->setText("GAME OVER!\n"
                                        +player1.name+"won");
        }
        else if(player2.playerCharacters.empty()){
            ui->label_gameover->show();
            ui->label_gameover->setText("GAME OVER!\n"
                                        +player2.name+"won");
        }*/

}


    /*void mapWindow::on_pushButton_B02_clicked()
    {
        can(18,characterList[18]->type,1);
    }*/


    void mapWindow::on_pushButton_clicked()
    {

        m_tilesB[14]->setIcon(QIcon());
        /*for(int i=0;i<41;i++){
            m_tilesB[i]->setEnabled(true);
        }*/
    }


    void mapWindow::on_pushButton_2_clicked()
    {
        for (int i = 0; i < 41; i++) {
            QString currentStyle = m_tilesB[i]->styleSheet();
            m_tilesB[i]->setStyleSheet(currentStyle + "border: 2px solid red;");
        }
    }


    /*void mapWindow::on_pushButton_B11_clicked()
    {
        can(14,characterList[14]->type,1);

    }*/

