#include "mapwindow.h"
#include "Characters.h"
#include "ui_mapwindow.h"
#include "tiles.h"
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



mapWindow::mapWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::mapWindow)
{
    ui->setupUi(this);
    int size;
    ui->groupBox_location->hide();
    loadAndProcessMap();
    setCharacters();

    ui->pushButton_locationInfo->setStyleSheet(
        "QPushButton {"
        "background-image: url(:/pics/howtoBT.png);"
        "background-color:transparent;"
        "border: transparent;"
        "}"
        "QPushButton:hover { "
        "background-image: url(:/pics/howtoBT_hover.PNG);"
        "background-color:transparent;"
        "border: transparent;"
        " }"
        "QPushButton:pressed{"
        "background-image: url(:/pics/howtoBT_active.PNG);"
        "background-color:transparent;"
        "border: transparent;"
        " }"
        );
    //QVector<Characters> hunters;
    //QVector<Characters> preys;
    //QVector<QPixmap*> huntersPic=;
    //QVevtor<QPixmap*> preysPic;

    QVector<QPushButton*> agentsPics={
        ui->pushButton_p11,ui->pushButton_p12,ui->pushButton_p13,ui->pushButton_p14,
        ui->pushButton_p15,ui->pushButton_p16,ui->pushButton_p17,ui->pushButton_p18,
        ui->pushButton_p19,ui->pushButton_p110,
        ui->pushButton_p21,ui->pushButton_p22,ui->pushButton_p23,ui->pushButton_p24,
        ui->pushButton_p25,ui->pushButton_p26,ui->pushButton_p27,ui->pushButton_p28,
        ui->pushButton_p29,ui->pushButton_p210,
    };
    size=agentsPics.size();
    for(int i=0;i<size;i++){
        agentsPics[i]->setStyleSheet("border: 1px solid white;background-color:white;");
        agentsPics[i]->setFixedSize(60, 60);
        agentsPics[i]->move(20,20);
        agentsPics[i]->setText("");
    }

    //characters
    Characters drakula("drakula",QPixmap(":/pics/charachters/drakula.PNG"),100,40,3,1,false,true);
    ui->pushButton_p11->setIcon(QIcon(drakula.getPic()));
    ui->pushButton_p11->setIconSize(ui->pushButton_p11->size());
    Characters pennyWise("pennyWise",QPixmap(":/pics/charachters/pennyWise.PNG"),100,40,2,1,false,true);
    ui->pushButton_p12->setIcon(QIcon(pennyWise.getPic()));
    ui->pushButton_p12->setIconSize(ui->pushButton_p12->size());




    /*QVector<QGroupBox*> agentBox={
        ui->groupBox_p11,ui->groupBox_p12,ui->groupBox_p13,ui->groupBox_p14,
        ui->groupBox_p15,ui->groupBox_p16,ui->groupBox_p17,ui->groupBox_p18,
        ui->groupBox_p19,ui->groupBox_p110,
        ui->groupBox_p21,ui->groupBox_p22,ui->groupBox_p23,ui->groupBox_p24,
        ui->groupBox_p25,ui->groupBox_p26,ui->groupBox_p27,ui->groupBox_p28,
        ui->groupBox_p29,ui->groupBox_p210,
    };*/


}


mapWindow::~mapWindow()
{
    delete ui;
}

//taking players names
void mapWindow::on_pushButton_clicked()
{
    QString p1name=ui->textEdit_p1->toPlainText();
    QString p2name=ui->textEdit_p2->toPlainText();
    ui->groupBox_names->hide();
    ui->groupBox_p1agents->setTitle(p1name+"'s agents");
    ui->groupBox_p2agents->setTitle(p2name+"'s agents");
}

//opening actual game map
void mapWindow::on_pushButton_2_clicked()
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

    tiles tilesList[41];
    int count=0;
    int i,j=0;
    while(count<41){
        i=0;
        while(i%2==0 && i<9 && j<5){
            tilesList[count].row=i;
            tilesList[count].column=j;
            tilesList[count].pic = processedMap[count].digitValue();
            i+=2;
            count++;
        }
        i=1;
        while(i%2==1 && i<9 && j<4){
            tilesList[count].row=i;
            tilesList[count].column=j;
            tilesList[count].pic = processedMap[count].digitValue();
            i+=2;
            count++;
        }
        j++;
    }

    QVector<QLabel*> labels = {//for 1st map
            ui->label_00, ui->label_09, ui->label_18,ui->label_27,ui->label_36,
            ui->label_05, ui->label_14, ui->label_23,ui->label_32,
            ui->label_01, ui->label_10, ui->label_19,ui->label_28,ui->label_37,
            ui->label_06, ui->label_15, ui->label_24,ui->label_33,
            ui->label_02, ui->label_11, ui->label_20,ui->label_29,ui->label_38,
            ui->label_07, ui->label_16, ui->label_25,ui->label_34,
            ui->label_03, ui->label_12, ui->label_21,ui->label_30,ui->label_39,
            ui->label_08, ui->label_17, ui->label_26,ui->label_35,
            ui->label_04, ui->label_13, ui->label_22,ui->label_31,ui->label_40,
            };
    QVector<QLabel*> labelsB = {//for 2nd map
        ui->label_00B, ui->label_20B, ui->label_40B,ui->label_60B,ui->label_80B,
        ui->label_10B, ui->label_30B, ui->label_50B,ui->label_70B,
        ui->label_01B, ui->label_21B, ui->label_41B,ui->label_61B,ui->label_81B,
        ui->label_11B, ui->label_31B, ui->label_51B,ui->label_71B,
        ui->label_02B, ui->label_22B, ui->label_42B,ui->label_62B,ui->label_82B,
        ui->label_12B, ui->label_32B, ui->label_52B,ui->label_72B,
        ui->label_03B, ui->label_23B, ui->label_43B,ui->label_63B,ui->label_83B,
        ui->label_13B, ui->label_33B, ui->label_53B,ui->label_73B,
        ui->label_04B, ui->label_24B, ui->label_44B,ui->label_64B,ui->label_84B,
    };

    for(i=0;i<41;i++){
        if(tilesList[i].pic==1){//p1 land red
            labels[i]->setStyleSheet("background-image: url(:/pics/land-p1.png);"
                                     "border: 0.5px solid black;");
            labelsB[i]->setStyleSheet("background-image: url(:/pics/land.png);"
                                      "border: 1.5px solid black;");

        }
        else if(tilesList[i].pic==2){//p2 land blue
            labels[i]->setStyleSheet("background-image: url(:/pics/land-p2.png);"
                                     "border: 0.5px solid black;");
            labelsB[i]->setStyleSheet("background-image: url(:/pics/land.png);"
                                      "border: 1.5px solid black;");
        }
        else if(tilesList[i].pic==3){//normal land
            labels[i]->setStyleSheet("background-image: url(:/pics/land.png);"
                                     "border: 0.5px solid black;");
            labelsB[i]->setStyleSheet("background-image: url(:/pics/land.png);"
                                      "border: 1.5px solid black;");
        }
        else if(tilesList[i].pic==4){//water
            labels[i]->setStyleSheet("background-image: url(:/pics/water.png);"
                                     "border: 0.5px solid black;");
            labelsB[i]->setStyleSheet("background-image: url(:/pics/water.png);"
                                      "border: 1.5px solid black;");
        }
        else if(tilesList[i].pic==5){//mountain
            labels[i]->setStyleSheet("background-image: url(:/pics/mountain.png);"
                                     "border: 0.5px solid black;");
            labelsB[i]->setStyleSheet("background-image: url(:/pics/mountain.png);"
                                      "border: 1.5px solid black;");
        }
    }




    /*if (!processedMap.isEmpty()) {
        QStringList lines = processedMap.split('\n');

        // Example: Display in a QPlainTextEdit (if you have one)
        if (ui->plainTextEdit) {
            ui->plainTextEdit->setPlainText(processedMap);
            for (const QString& line : lines) {
                if (!line.trimmed().isEmpty()) {
                    qDebug() << "Line:" << line;
                }
            }
        }
    }*/



}

//set chaaractes in map
void mapWindow::setCharacters() {
    //int p1Count=0,p2Count=0;
    //int listOfPushButtonsSize;

    QVector<QPushButton*> listOfPushButtons = {
        ui->pushButton_p11, ui->pushButton_p12, ui->pushButton_p13, ui->pushButton_p14,
        ui->pushButton_p15, ui->pushButton_p16, ui->pushButton_p17, ui->pushButton_p18,
        ui->pushButton_p19, ui->pushButton_p110,
        ui->pushButton_p21, ui->pushButton_p22, ui->pushButton_p23, ui->pushButton_p24,
        ui->pushButton_p25, ui->pushButton_p26, ui->pushButton_p27, ui->pushButton_p28,
        ui->pushButton_p29, ui->pushButton_p210,
    };

    QVector<QLabel*> tilesLabel = {
        ui->label_00, ui->label_01, ui->label_02, ui->label_03, ui->label_04,
        ui->label_05, ui->label_06, ui->label_07, ui->label_08,
        ui->label_09, ui->label_10, ui->label_11, ui->label_12, ui->label_13,
        ui->label_14, ui->label_15, ui->label_16, ui->label_17,
        ui->label_18, ui->label_19, ui->label_20, ui->label_21, ui->label_22,
        ui->label_23, ui->label_24, ui->label_25, ui->label_26,
        ui->label_27, ui->label_28, ui->label_29, ui->label_30, ui->label_31,
        ui->label_32, ui->label_33, ui->label_34, ui->label_35,
        ui->label_36, ui->label_37, ui->label_38, ui->label_39, ui->label_40,
    };

    m_clickedButton = nullptr;
    listOfPushButtonsSize=listOfPushButtons.size();

    for (int i = 0; i < listOfPushButtonsSize; ++i) {
        QPushButton* button = listOfPushButtons[i];
        connect(button, &QPushButton::clicked, this, [this, button]() {
            ui->groupBox_location->show();
            ui->lineEdit->clear();
            ui->lineEdit->setFocus();
            this->m_clickedButton = button;
        });
    }

    QIntValidator *validator = new QIntValidator(0, tilesLabel.size() - 1, this);
    ui->lineEdit->setValidator(validator);

    connect(ui->pushButton_confirm, &QPushButton::clicked, this, [this, tilesLabel,listOfPushButtons]() {
        ui->groupBox_location->hide();

        if (!m_clickedButton) {
            qWarning() << "No button was clicked!";
            return;
        }

        bool ok;
        int location = ui->lineEdit->text().toInt(&ok)-1;

        if (!ok || location < 0 || location >= tilesLabel.size()) {
            qWarning() << "Invalid location!";
            return;
        }

        m_clickedButton->setEnabled(false);
        QIcon icon = m_clickedButton->icon();
        tilesLabel[location]->setPixmap(icon.pixmap(tilesLabel[location]->size()));

        bool isPlayer1=listOfPushButtons.indexOf(m_clickedButton)<(listOfPushButtonsSize/2);
        if(isPlayer1){
            p1Count++;
        }
        else{
            p2Count++;
        }


        const int halfSize=listOfPushButtonsSize/2;
        if(p1Count==5){
            for(int i=0;i<halfSize;i++){
                listOfPushButtons[i]->setEnabled(false);
            }
        }
        if(p2Count==5){
            for(int i=halfSize;i<listOfPushButtonsSize;i++){
                listOfPushButtons[i]->setEnabled(false);
            }
        }

        m_clickedButton = nullptr;
    });


}
