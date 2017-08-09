#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QDialog>
#include <QtWidgets>
#include <QtSql>

namespace Ui {
class menuwindow;
}

class menuwindow : public QDialog
{
    Q_OBJECT

public:
    explicit menuwindow(QWidget *parent = 0);
    int getTableId();
    int getDishId();
    ~menuwindow();

private slots:
    void on_commitBtn_clicked();

    void on_toTheCartBtn_clicked();

private:
    Ui::menuwindow *ui;
    QSqlRelationalTableModel *model;
    QSqlRelationalTableModel *modelTables;
};

#endif // MENUWINDOW_H
