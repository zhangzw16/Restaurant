#ifndef EDITTABLESWINDOW_H
#define EDITTABLESWINDOW_H

#include <QDialog>
#include <QSqlRelationalTableModel>
#include <QSqlQuery>

namespace Ui {
class editTablesWindow;
}

class editTablesWindow : public QDialog
{
    Q_OBJECT

public:
    explicit editTablesWindow(QWidget *parent = 0);
    ~editTablesWindow();

private slots:
    void on_deleteTableBtn_clicked();

    void on_addTableBtn_clicked();

    void on_submitBtn_clicked();

private:
    Ui::editTablesWindow *ui;
    QSqlRelationalTableModel *model;
    QSqlQuery query;
};

#endif // EDITTABLESWINDOW_H
