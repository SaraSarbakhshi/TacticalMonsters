#ifndef MAPWINDOW_H
#define MAPWINDOW_H

#include <QDialog>
#include <QString>
#include <QVector>
#include <QImage>
#include <QPushButton>
#include <QIcon>
#include <QGroupBox>
#include "tiles.h"
#include "characters.h"
#include "player.h"

namespace Ui {
class mapWindow;
}

class mapWindow : public QDialog
{
    Q_OBJECT

public:
    explicit mapWindow(QWidget *parent = nullptr);
    ~mapWindow();
    tiles tilesList[41];
    friend class Characters;

private slots:
    void on_pushButton_confirmNames_clicked();
    void on_pushButton_allChosen_clicked();
    void loadAndProcessMap();
    void beautify();
    QString loadRandomMap();
    void setCharacters();
    void chooseType();
    void loadCustomFont();
    //void disablePlayerButtons();
    void actualGame();
    void can(int,int,bool);

    void on_pushButton_setting_clicked();

    void on_pushButton_undo_clicked();
    void startTurn(bool);
    void gameOver(bool);
    int afterAttackMovement(int,int);
    //void endTurn();


    //void on_pushButton_B02_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    //void on_pushButton_B11_clicked();

private:
    Ui::mapWindow *ui;
    /*QString p1name;
    QString p2name;*/
    //QVector<QPushButton*> m_playerButtons;
    QVector<QPushButton*> m_tilesB;//2nd/actual map
    QVector<QPushButton*> m_tilesB_2;//1st map
    QIcon m_selectedIcon;
    int m_selectedPlayerButtonIndex = -1;
    QPushButton* m_clickedButton = nullptr;
    int p1Count = 0;
    int p2Count = 0;
    int listOfPushButtonsSize = 0;
    int size;
    int halfSize;
    int x1;
    int x2;
    int typeBTN;
    bool isPlayer1Turn;
    int selectedFrom = -1;
    int selectedTo = -1;
    bool awaitingSelection = true;
    QVector <QGroupBox*> agentsGRPBX;
    QVector<QPushButton*> typeButtons;
    QVector<QPushButton*> agentsPics;
    QVector<Characters*> characterList;


};

#endif // MAPWINDOW_H
