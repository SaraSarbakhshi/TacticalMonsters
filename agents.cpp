#include "agents.h"
#include "ui_agents.h"

agents::agents(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::agents)
{
    ui->setupUi(this);
    this->setWindowTitle("tactical monsters_agents");
    QPixmap agentsBG(":/pics/agentsBG.jpg");
    int w=agentsBG.width();int h=agentsBG.height();
    ui->label->setScaledContents(true);
    ui->label->setGeometry(0,0,w,h);
    this->setMaximumSize(w,h);
    this->setMinimumSize(w,h);
}

agents::~agents()
{
    delete ui;
}
