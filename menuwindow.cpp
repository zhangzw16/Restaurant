#include "menuwindow.h"
#include "ui_menuwindow.h"
#include "menu.h"
#include "tables.h"
#include "menudelegate.h"
#include <QItemSelectionModel>
#include "values.h"


menuwindow::menuwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::menuwindow)
{
    ui->setupUi(this);
    QSqlDatabase dbMenu = QSqlDatabase::database("connection2");

    //创建一个model,并设置他的 headername
    model = new QSqlRelationalTableModel(this, dbMenu);
    model->setTable("menu");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setHeaderData(model->fieldIndex("name"), Qt::Horizontal, "DISHES");
    model->setHeaderData(model->fieldIndex("price"), Qt::Horizontal, "PRICE");
    model->setHeaderData(model->fieldIndex("rate"), Qt::Horizontal, "RATE");

    if (!model->select()) {
        qDebug() << model->lastError();
    }

    //将menuTable和model绑定在一起，并将部分列设置为不可见
    ui->menuTable->setModel(model);
    ui->menuTable->setItemDelegate(new MenuDelegate(this));
    ui->menuTable->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    ui->menuTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->menuTable->setColumnHidden(model->fieldIndex("id"), true);
    ui->menuTable->setColumnHidden(model->fieldIndex("remains"), true);
//    ui->menuTable->setColumnHidden(model->fieldIndex("rate"), true);
    ui->menuTable->setSelectionMode(QAbstractItemView::SingleSelection);

    //设置一个mapper将数据在中间的控件里显示出来
    QDataWidgetMapper *mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->setItemDelegate(new MenuDelegate(this));
    mapper->addMapping(ui->NameLineEdit, model->fieldIndex("name"));
    mapper->addMapping(ui->priceSpinBox, model->fieldIndex("price"));
    mapper->addMapping(ui->ratingSpinBox, model->fieldIndex("rate"));
    connect(ui->menuTable->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            mapper, SLOT(setCurrentModelIndex(QModelIndex)));
    ui->menuTable->setCurrentIndex(model->index(0,0)); //设置当前的mapper显示目标

    //设置另一个model--modelTables
    QSqlDatabase dbTables = QSqlDatabase::database("connection3");
    modelTables = new QSqlRelationalTableModel(this, dbTables);
    modelTables->setTable("diningTables");
    modelTables->setEditStrategy(QSqlTableModel::OnManualSubmit);

    for (int i=0; i<menuList.length(); i++) {
        modelTables->setHeaderData(modelTables->fieldIndex(QString("dish%1").arg(i+1)),
                                   Qt::Horizontal, menuList[i]);
    }
    if (!modelTables->select()) {
        qDebug() << modelTables->lastError();
    }
    ui->tablesTable->setModel(modelTables);
    ui->tablesTable->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    ui->tablesTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tablesTable->setColumnHidden(modelTables->fieldIndex("waiter"), true);
    ui->tablesTable->setColumnHidden(modelTables->fieldIndex("user"), true);
    ui->tablesTable->setSelectionMode(QAbstractItemView::SingleSelection);
    for (int i=0; i<=tablesNum; i++) {
        if (i != getTableId()) {
            ui->tablesTable->setRowHidden(i, true);
        }
    }
}

int menuwindow::getTableId()
{
    return tableId;
}

int menuwindow::getDishId()
{
    QItemSelectionModel *sModel = ui->menuTable->selectionModel();
    QModelIndex sIndex = sModel->currentIndex();
//    qDebug() << sIndex.row();
//    QSqlDatabase dbTables = QSqlDatabase::database("connection3");
    int dishId = sIndex.row() + 1;
    return dishId;
}

menuwindow::~menuwindow()
{
    delete ui;
}

void menuwindow::on_commitBtn_clicked()
{
    modelTables->submitAll();
    this->close();
}

void menuwindow::on_toTheCartBtn_clicked()
{
    int dishId = getDishId();
    QString dishIdString = QString("dish%1").arg(dishId);
    int dishQuantity = ui->dishQuantitySpinBox->value();
    int tableId = 0; //default
    qDebug() << dishIdString << dishQuantity;
    QSqlDatabase dbTables = QSqlDatabase::database("connection3");
    QSqlQuery q(dbTables);
    addDish(q, tableId, dishQuantity, dishIdString);
}
