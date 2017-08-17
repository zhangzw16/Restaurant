#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQueryModel>
#include <QTableView>
#include <QSqlQuery>
#include <QDebug>
#include <QString>
#include "menuwindow.h"
#include "checkbillwindow.h"
#include "starratedishwindow.h"
#include "values.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->showTableId->setText(QString("%1").arg(tableId));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
//    QSqlDatabase dbMenu;
//    dbMenu = QSqlDatabase::database("connection2");
//    QSqlQuery query(dbMenu);
//    QSqlQueryModel *model = new QSqlQueryModel(this);
//    model->setQuery("select * from menu", dbMenu);

//    model->setHeaderData(0, Qt::Horizontal, "id");
//    model->setHeaderData(1, Qt::Horizontal, "name");
//    model->setHeaderData(2, Qt::Horizontal, "price");
//    QTableView *view = new QTableView;
//    view->setModel(model);
//    view->show();

    menuwindow mw;
    mw.show();
    mw.exec();
}

void MainWindow::on_checkBillBtn_clicked()
{
    CheckBillWindow cbw;
    cbw.show();
    cbw.exec();
}

void MainWindow::on_starrateBtn_clicked()
{
    starrateDishWindow sdw;
    sdw.show();
    sdw.exec();
}
