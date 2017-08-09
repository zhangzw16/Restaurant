#include "choosetablewindow.h"
#include "ui_choosetablewindow.h"
#include "tables.h"
#include "account.h"
#include "mainwindow.h"
#include <QtWidgets>
#include <QMessageBox>

QList<int> tableList;

chooseTableWindow::chooseTableWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chooseTableWindow),
    tables(0)
{
    ui->setupUi(this);
    getAvaliableTableNum();
    ui->lineEdit->setText(QString("%1").arg(tables));
}

int chooseTableWindow::getAvaliableTableNum()
{
    QSqlDatabase dbTables = QSqlDatabase::database("connection3");
    QSqlQuery query(dbTables);
    query.exec("select * from diningTables");
//    qDebug() << query.lastError();
    while(query.next()) {
        qDebug() << query.value(3).toString();
        if (query.value(3).toString() == '0') {
            tables++;
            qDebug() << query.value(0).toInt();
            tableList.append(query.value(0).toInt());
            qDebug() << tableList;
        }
    }
    qDebug() << tables;
    return tables;
}

chooseTableWindow::~chooseTableWindow()
{
    delete ui;
}

void chooseTableWindow::on_pushButton_clicked()
{
    QSqlDatabase dbTables = QSqlDatabase::database("connection3");
    QSqlQuery query(dbTables);
    if (!tables > 0) {
        QMessageBox::warning(this, "No table available!",
                             "There is no table left. Please wait for some time");
    } else {
        query.exec(QString("update tables set usrname = %1 where id = %2").arg(usrnameA).arg(tableList[0]));
        this->hide();
        MainWindow mw;
        mw.show();
    }

}
