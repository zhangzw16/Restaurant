#include "editaccountwindow.h"
#include "ui_editaccountwindow.h"
#include "account.h"
#include "signupwindow.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>

editAccountWindow::editAccountWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editAccountWindow)
{
    ui->setupUi(this);

    QSqlDatabase dbAccount = QSqlDatabase::database("connection1");
    QSqlQuery query(dbAccount);
    qDebug() << query.lastError();

    model = new QSqlRelationalTableModel(this, dbAccount);
    model->setTable("account");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    if (!model->select()) {
        qDebug() << model->lastError();
    }

    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked |
                                   QAbstractItemView::SelectedClicked);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

}

editAccountWindow::~editAccountWindow()
{
    delete ui;
}


void editAccountWindow::on_submitBtn_clicked()
{
    model->submitAll();
    this->close();
}

void editAccountWindow::on_deleteAccountBtn_clicked()
{
    QItemSelectionModel *accountModel = ui->tableView->selectionModel();
    QModelIndex accountIndex = accountModel->selectedRows()[0];
    qDebug() << model->data(accountIndex);

    QSqlDatabase dbAccount = QSqlDatabase::database("connection1");
    QSqlQuery queryA(dbAccount);
    deleteAccount(queryA, QString("%1").arg(model->data(accountIndex).toString()));
}

void editAccountWindow::on_addAccountBtn_clicked()
{
    signUpWindow suw(this, 4);
    suw.show();
    suw.exec();
}

void editAccountWindow::on_comboBox_activated(const QString &arg1)
{
    QSqlDatabase dbAccount = QSqlDatabase::database("connection1");
    QSqlQuery query(dbAccount);
    query.exec("select * from account");
    int accountSum = 0;
    while(query.next()) {
        accountSum++;
    }
    if (arg1 == "ALL") {
        for (int i=0; i<accountSum; i++) {
            ui->tableView->setRowHidden(i, false);
        }

    } else if (arg1 == "USER") {
        for (int i=0; i<accountSum; i++) {
            ui->tableView->setRowHidden(i, false);
        }
        int i = 0;
        query.exec("select * from account");
        while( query.next()) {
            if (query.value(2).toInt() != 0) {
                ui->tableView->setRowHidden(i, true);
            }
            i++;
        }
    } else if (arg1 == "WAITER") {
        for (int i=0; i<accountSum; i++) {
            ui->tableView->setRowHidden(i, false);
        }
        int i = 0;
        query.exec("select * from account");
        while( query.next()) {
            if (query.value(2).toInt() != 1) {
                ui->tableView->setRowHidden(i, true);
            }
            i++;
        }
    } else if (arg1 == "COOK") {
        for (int i=0; i<accountSum; i++) {
            ui->tableView->setRowHidden(i, false);
        }
        int i = 0;
        query.exec("select * from account");
        while( query.next()) {
            if (query.value(2).toInt() != 2) {
                ui->tableView->setRowHidden(i, true);
            }
            i++;
        }
    } else if (arg1 == "ADMIN") {
        for (int i=0; i<accountSum; i++) {
            ui->tableView->setRowHidden(i, false);
        }
        int i = 0;
        query.exec("select * from account");
        while( query.next()) {
            if (query.value(2).toInt() != 3) {
                ui->tableView->setRowHidden(i, true);
            }
            i++;
        }
    }
}
