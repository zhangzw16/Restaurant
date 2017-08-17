#include "starratedishwindow.h"
#include "ui_starratedishwindow.h"
#include "menudelegate.h"

starrateDishWindow::starrateDishWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::starrateDishWindow)
{
    ui->setupUi(this);

    QSqlDatabase dbMenu = QSqlDatabase::database("connection2");
    model = new QSqlRelationalTableModel(this, dbMenu);
    model->setTable("menu");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

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
}

starrateDishWindow::~starrateDishWindow()
{
    delete ui;
}

void starrateDishWindow::on_submitBtn_clicked()
{
    if (othersIsModified()) {
        QMessageBox::warning(this,
                             "Warning",
                             "请不要修改星级以外的内容",
                             QMessageBox::Ok);
        this->close();
    } else {
        model->submitAll();
        this->close();
    }
}

bool starrateDishWindow::othersIsModified()
{
    QModelIndex index;
    if (!model->isDirty()) return false;
//    else if (for (int i=0))

    return true;
}
