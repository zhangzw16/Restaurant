#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQueryModel>
#include <QTableView>
#include <QSqlQuery>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QSqlDatabase dbMenu;
    dbMenu = QSqlDatabase::database("connection2");
    QSqlQuery query(dbMenu);
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery("select * from menu", dbMenu);

    query.exec("select * from menu");
    while(query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        int price = query.value(2).toInt();
        qDebug() << id << name << price << endl;
    }

    model->setHeaderData(0, Qt::Horizontal, "id");
    model->setHeaderData(1, Qt::Horizontal, "name");
    model->setHeaderData(2, Qt::Horizontal, "price");
    QTableView *view = new QTableView;
    view->setModel(model);
    view->show();
}
