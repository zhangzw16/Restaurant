#include "waiterwinodw.h"
#include "ui_waiterwinodw.h"
#include <QString>
#include "values.h"
#include "menuwindow.h"

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
