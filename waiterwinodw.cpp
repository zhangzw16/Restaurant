#include "waiterwinodw.h"
#include "ui_waiterwinodw.h"
#include <QString>
#include "values.h"
#include "menuwindow.h"
#include "editaccountwindow.h"

WaiterWinodw::WaiterWinodw(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WaiterWinodw)
{
    ui->setupUi(this);
    ui->showTableId->setText(QString("%1").arg(tableId));
}

WaiterWinodw::~WaiterWinodw()
{
    delete ui;
}

void WaiterWinodw::on_editMenuBtn_clicked()
{
    menuwindow mw;
    mw.show();
    mw.exec();
}

void WaiterWinodw::on_editAccountBtn_clicked()
{
    editAccountWindow eaw;
    eaw.show();
    eaw.exec();
}
