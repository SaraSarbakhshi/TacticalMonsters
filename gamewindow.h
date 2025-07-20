#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QDialog>
#include "agents.h"

namespace Ui {
class gameWindow;
}

class gameWindow : public QDialog
{
    Q_OBJECT

public:
    explicit gameWindow(QWidget *parent = nullptr);
    ~gameWindow();

private slots:
    void on_pushButton_HTP_clicked();

    void on_pushButton_agents_clicked();

    //void on_pushButton_PVP_clicked();

    void on_pushButton_PVP_clicked();

    void on_pushButton_X_clicked();
    void loadCustomFont();


private:
    Ui::gameWindow *ui;
    //mapWindow *naghshe;
    agents *agentsWindow;



};

#endif // GAMEWINDOW_H
