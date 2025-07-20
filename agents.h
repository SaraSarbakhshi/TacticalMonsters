//this is merely for the page itself
#ifndef AGENTS_H
#define AGENTS_H

#include <QDialog>
#include "characters.h"
#include <QPushButton>

namespace Ui {
class agents;
}

class agents : public QDialog
{
    Q_OBJECT

public:
    explicit agents(QWidget *parent = nullptr);
    ~agents();

private slots:
    void on_pushButton_back_clicked();
    //void moreInfo();
    void loadCustomFont();
    void showCharacterInfo(int);
    void moreInfo();




    void on_pushButton_clicked();

private:
    Ui::agents *ui;
   // QVector<Characters*> huntersList;
    //QVector<Characters*> preysList;
    QVector<Characters*> characterList;
    QVector<QPushButton*> characterPushButtons;
    int currentMoreInfoIndex = -1;
    int currentStartIndex = 0;
    int currentEndIndex = 48;





};

#endif // AGENTS_H
