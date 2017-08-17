#include "editaccountwindow.h"
#include "ui_editaccountwindow.h"
#include "account.h"
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
