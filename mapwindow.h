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
    void startTurn();
    void gameOver();
    void toMove();
    int afterAttackMovement(int,int);
    //void endTurn();
    //void handleMapClick(int);

    void on_pushButton_X_clicked();

private:
    Ui::mapWindow *ui;
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
    bool isPlayer1Turn = false;
    int selectedFrom = -1;
    bool waitingForFrom = true;
    int selectedTo = -1;
    bool awaitingSelection = true;
    player player1;
    player player2;
    player *currentPlayer;
    player *otherPlayer;

    QVector <QGroupBox*> agentsGRPBX;
    QVector<QPushButton*> typeButtons;
    QVector<QPushButton*> agentsPics;
    QVector<Characters*> characterList;

};

#endif // MAPWINDOW_H
