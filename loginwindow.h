#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    static int getTableNum();
    ~LoginWindow();

private slots:

    void on_signUpBtn_clicked();

    void on_signInBtn_customer_clicked();

    void on_signInBtn_admin_clicked();

private:
    Ui::LoginWindow *ui;
    bool verify_customer();
    bool verify_admin();
};

#endif // LOGINWINDOW_H
