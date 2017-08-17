#ifndef CHECKBILLWINDOW_H
#define CHECKBILLWINDOW_H

#include <QDialog>
#include <QtWidgets>
#include <QtSql>

namespace Ui {
class CheckBillWindow;
}

class CheckBillWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CheckBillWindow(QWidget *parent = 0);
    ~CheckBillWindow();
    static int getTotalPrice(const int &id);

private slots:
    void on_returnBtn_clicked();

    void on_payBillBtn_clicked();

private:
    Ui::CheckBillWindow *ui;
    QSqlRelationalTableModel *modelTables;
    QStandardItemModel *stdModel;
};

#endif // CHECKBILLWINDOW_H
