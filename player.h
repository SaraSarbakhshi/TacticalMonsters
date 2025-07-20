#ifndef PLAYER_H
#define PLAYER_H

#include <QDialog>
#include "Characters.h"
#include "tiles.h"


class player{
public:
    QString name;
    QVector<Characters*> playerCharacters;
    QVector<int> playerTiles;
    int score;
    bool turn;

};

#endif // PLAYER_H
