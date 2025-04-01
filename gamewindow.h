#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QDialog>


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
    //void on_pushButton_HTP_clicked();


    void on_pushButton_agents_clicked();

private:
    Ui::gameWindow *ui;


};

#endif // GAMEWINDOW_H
