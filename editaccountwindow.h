#ifndef EDITACCOUNTWINDOW_H
#define EDITACCOUNTWINDOW_H

#include <QDialog>
#include <QSqlRelationalTableModel>

namespace Ui {
class editAccountWindow;
}

class editAccountWindow : public QDialog
{
    Q_OBJECT

public:
    explicit editAccountWindow(QWidget *parent = 0);
    ~editAccountWindow();

private slots:
    void on_submitBtn_clicked();

    void on_deleteAccountBtn_clicked();

private:
    Ui::editAccountWindow *ui;
    QSqlRelationalTableModel *model;
};

#endif // EDITACCOUNTWINDOW_H
