#ifndef CHOOSETABLEWINDOW_H
#define CHOOSETABLEWINDOW_H

#include <QDialog>

namespace Ui {
class chooseTableWindow;
}

class chooseTableWindow : public QDialog
{
    Q_OBJECT

public:
    explicit chooseTableWindow(QWidget *parent = 0);
    int getAvaliableTableNum();
    ~chooseTableWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::chooseTableWindow *ui;
    int tables;
};

#endif // CHOOSETABLEWINDOW_H
