#include "edittableswindow.h"
#include "ui_edittableswindow.h"
#include "tables.h"

editTablesWindow::editTablesWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editTablesWindow)
{
    ui->setupUi(this);

    QSqlDatabase dbTables = QSqlDatabase::database("connection3");
    QSqlQuery queryTemp(dbTables);
    query = queryTemp;

    model = new QSqlRelationalTableModel(this, dbTables);
    model->setTable("diningTables");
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

editTablesWindow::~editTablesWindow()
{
    delete ui;
}

void editTablesWindow::on_deleteTableBtn_clicked()
{
    QItemSelectionModel *tableModel = ui->tableView->selectionModel();
    QModelIndex tableIndex = tableModel->selectedRows()[0]; //返回选中的第一行（因为设置了只能选中一行）
    qDebug() << model->data(tableIndex).toInt();
    deleteTable(query, model->data(tableIndex).toInt());
//    query.exec("delete from diningTables where id = 12");
}

void editTablesWindow::on_addTableBtn_clicked()
{
    addTable(query);
}

void editTablesWindow::on_submitBtn_clicked()
{
    model->submitAll();
    this->close();
}
