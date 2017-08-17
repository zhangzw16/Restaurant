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
    explicit signUpWindow(QWidget *parent = 0, int statusSum = 1);
    ~signUpWindow();
    Ui::signUpWindow *ui;

private slots:

    void on_okBtn_clicked();

    void on_backToLoginBtn_clicked();

private:
    bool signupCustomer();
    int statusSum;
};

#endif // SIGNUPWINDOW_H
