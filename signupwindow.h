#ifndef SIGNUPWINDOW_H
#define SIGNUPWINDOW_H

#include <QDialog>

namespace Ui {
class signUpWindow;
}

class signUpWindow : public QDialog
{
    Q_OBJECT

public:
    explicit signUpWindow(QWidget *parent = 0);
    ~signUpWindow();

private slots:

    void on_okBtn_clicked();

    void on_backToLoginBtn_clicked();

private:
    Ui::signUpWindow *ui;
    bool signupCustomer();
};

#endif // SIGNUPWINDOW_H
