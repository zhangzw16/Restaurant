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
    ~menuwindow();

private:
    Ui::menuwindow *ui;
    QSqlRelationalTableModel *model;
};

#endif // MENUWINDOW_H
