#ifndef STARRATEDISHWINDOW_H
#define STARRATEDISHWINDOW_H

#include <QDialog>
#include <QtWidgets>
#include <QtSql>

namespace Ui {
class starrateDishWindow;
}

class starrateDishWindow : public QDialog
{
    Q_OBJECT

public:
    explicit starrateDishWindow(QWidget *parent = 0);
    ~starrateDishWindow();

private slots:
    void on_submitBtn_clicked();

private:
    Ui::starrateDishWindow *ui;
    QSqlRelationalTableModel *model;
    bool othersIsModified();
};

#endif // STARRATEDISHWINDOW_H
