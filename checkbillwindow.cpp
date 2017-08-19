#include "checkbillwindow.h"
#include "ui_checkbillwindow.h"
#include <QSqlDatabase>
#include <QSqlRelationalTableModel>
#include "tables.h"
#include <QItemSelectionModel>
#include "values.h"
#include "menu.h"
#include <QMessageBox>

CheckBillWindow::CheckBillWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CheckBillWindow)
{
    ui->setupUi(this);

    QSqlDatabase dbTables = QSqlDatabase::database("connection3");
    QSqlQuery queryT(dbTables);
    QSqlDatabase dbMenu = QSqlDatabase::database("connection2");
    QSqlQuery queryM(dbMenu);

    stdModel = new QStandardItemModel(this);
    stdModel->setHorizontalHeaderItem(0, new QStandardItem("Dish"));
    stdModel->setHorizontalHeaderItem(1, new QStandardItem("Price for Each"));
    stdModel->setHorizontalHeaderItem(2, new QStandardItem("Quantity"));
    stdModel->setHorizontalHeaderItem(3, new QStandardItem("Price for All"));

    QList<int> quantityList = getQuantityList(queryT, tableId);
    QList<int> priceList = getPriceList(queryM);
//    qDebug() << quantityList;

    for (int i=0; i<menuList.length(); i++) {
        QString dishName = menuList[i];
//        queryM.exec(QString("select price from menu where id = %1").arg(i+1));
//        queryM.next();
        int Price = priceList[i];
        int Quantity = quantityList[i];
        int Cost = Price * Quantity;
        stdModel->setItem(i, 0, new QStandardItem(dishName));
        stdModel->setItem(i, 1, new QStandardItem(QString("%1").arg(Price)));
        stdModel->setItem(i, 2, new QStandardItem(QString("%1").arg(Quantity)));
        stdModel->setItem(i, 3, new QStandardItem(QString("%1").arg(Cost)));
    }

    ui->billTable->setModel(stdModel);
    ui->billTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->billTable->setSelectionBehavior(QAbstractItemView::SelectRows);
}

CheckBillWindow::~CheckBillWindow()
{
    delete ui;
}

int CheckBillWindow::getTotalPrice(const int &id)
{
    QSqlDatabase dbTables = QSqlDatabase::database("connection3");
    QSqlQuery queryT(dbTables);
    QSqlDatabase dbMenu = QSqlDatabase::database("connection2");
    QSqlQuery queryM(dbMenu);
    int totalPrice = 0;

    QList<int> priceList = getPriceList(queryM);
    QList<int> quantityList = getQuantityList(queryT, tableId);
    for (int i=0; i<priceList.length(); i++) {
        totalPrice += priceList[i] * quantityList[i];
    }
    return totalPrice;
}

void CheckBillWindow::on_returnBtn_clicked()
{
    this->close();
}

void CheckBillWindow::on_payBillBtn_clicked()
{
    QMessageBox::information(this,
                             "Pay Winodw",
                             QString("The total price of this bill is %1").arg(getTotalPrice(tableId)),
                             QMessageBox::Ok);
    this->close();
}
