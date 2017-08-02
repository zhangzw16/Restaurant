#include "signupwindow.h"
#include "ui_signupwindow.h"
#include <QMessageBox>
#include "account.h"
#include "loginwindow.h"

signUpWindow::signUpWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::signUpWindow)
{
    ui->setupUi(this);
}

signUpWindow::~signUpWindow()
{
    delete ui;
}

bool signUpWindow::signupCustomer()
{
    QString tel = ui->telLineEdit->text();
    QString pwd = ui->pwdLineEdit->text();

    QSqlDatabase dbAccount;
    dbAccount = QSqlDatabase::database("connection1");
    QSqlQuery query(dbAccount);
    if (tel.length() != 11) {
        QMessageBox::warning(this, "Invalid",
                             "Please enter a valid phone number");
        return false;
    }
    query.exec(QString("insert into account values(%1, %2, 1)").arg(tel).arg(pwd));
    return true;
}

void signUpWindow::on_okBtn_clicked()
{
    if (signupCustomer()) {
        this->hide();
        LoginWindow lw;
        lw.show();
        lw.exec();
    }

}

void signUpWindow::on_backToLoginBtn_clicked()
{
    this->hide();
    LoginWindow lw;
    lw.show();
    lw.exec();
}
