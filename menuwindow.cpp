#include "menuwindow.h"
#include "ui_menuwindow.h"
#include "menu.h"

menuwindow::menuwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::menuwindow)
{
    ui->setupUi(this);

    QSqlDatabase dbMenu = QSqlDatabase::database("connection2");
//    QSqlQuery query(dbMenu);

    model = new QSqlTableModel(this, dbMenu);
    model->setTable("menu");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

//    dishesIdx = model->fieldIndex("name");
//    model->setHeaderData(model->fieldIndex("name"), Qt::Horizontal, "name");
//    model->setHeaderData(model->fieldIndex("price"), Qt::Horizontal, "price");
//    model->setHeaderData(model->fieldIndex("rate"), Qt::Horizontal, "rate");

    if (!model->select()) {
        qDebug() << model->lastError();
    }

    ui->menuTable->setModel(model);
//    ui->menuTable->setItemDelegate();
    ui->menuTable->setColumnHidden(model->fieldIndex("id"), true);
    ui->menuTable->setColumnHidden(model->fieldIndex("remains"), true);
    ui->menuTable->setSelectionMode(QAbstractItemView::SingleSelection);
}

menuwindow::~menuwindow()
{
    delete ui;
}
