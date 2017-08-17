#ifndef WAITERWINODW_H
#define WAITERWINODW_H

#include <QDialog>

namespace Ui {
class WaiterWinodw;
}

class WaiterWinodw : public QDialog
{
    Q_OBJECT

public:
    explicit WaiterWinodw(QWidget *parent = 0);
    ~WaiterWinodw();

private slots:
    void on_editMenuBtn_clicked();

private:
    Ui::WaiterWinodw *ui;
};

#endif // WAITERWINODW_H
