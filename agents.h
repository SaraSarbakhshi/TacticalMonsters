#ifndef AGENTS_H
#define AGENTS_H

#include <QDialog>

namespace Ui {
class agents;
}

class agents : public QDialog
{
    Q_OBJECT

public:
    explicit agents(QWidget *parent = nullptr);
    ~agents();

private:
    Ui::agents *ui;
};

#endif // AGENTS_H
