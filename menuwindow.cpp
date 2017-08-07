#include "menuwindow.h"
#include "ui_menuwindow.h"
#include "menu.h"
#include "menudelegate.h"


menuwindow::menuwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::menuwindow)
{
    ui->setupUi(this);

    QSqlDatabase dbMenu = QSqlDatabase::database("connection2");
//    QSqlQuery query(dbMenu);

    model = new QSqlRelationalTableModel(this, dbMenu);
    model->setTable("menu");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

//    dishesIdx = model->fieldIndex("name");
    model->setHeaderData(model->fieldIndex("name"), Qt::Horizontal, "DISHES");
    model->setHeaderData(model->fieldIndex("price"), Qt::Horizontal, "PRICE");
    model->setHeaderData(model->fieldIndex("rate"), Qt::Horizontal, "RATE");

    if (!model->select()) {
        qDebug() << model->lastError();
    }

    ui->menuTable->setModel(model);
    ui->menuTable->setItemDelegate(new MenuDelegate(this));
    ui->menuTable->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    ui->menuTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->menuTable->setColumnHidden(model->fieldIndex("id"), true);
    ui->menuTable->setColumnHidden(model->fieldIndex("remains"), true);
//    ui->menuTable->setColumnHidden(model->fieldIndex("rate"), true);
    ui->menuTable->setSelectionMode(QAbstractItemView::SingleSelection);

    QDataWidgetMapper *mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->setItemDelegate(new MenuDelegate(this));
    mapper->addMapping(ui->NameLineEdit, model->fieldIndex("name"));
    mapper->addMapping(ui->priceSpinBox, model->fieldIndex("price"));
    mapper->addMapping(ui->ratingSpinBox, model->fieldIndex("rate"));

    connect(ui->menuTable->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            mapper, SLOT(setCurrentModelIndex(QModelIndex)));

    ui->menuTable->setCurrentIndex(model->index(0,0));
}

menuwindow::~menuwindow()
{
    delete ui;
}
