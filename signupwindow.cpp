#include "signupwindow.h"
#include "ui_signupwindow.h"
#include <QMessageBox>
#include "account.h"
#include "loginwindow.h"
#include <QDebug>
#include <QSqlError>

signUpWindow::signUpWindow(QWidget *parent, int statusSum) :
    QDialog(parent),
    ui(new Ui::signUpWindow),
    statusSum(statusSum)
{
    ui->setupUi(this);
    QStringList comboBoxList;
    for (int i=0; i<statusSum; i++) {
        comboBoxList.append(QString("%1").arg(i));
    }
    ui->statusComboBox->insertItems(0, comboBoxList);
}

signUpWindow::~signUpWindow()
{
    delete ui;
}

bool signUpWindow::signupCustomer()
{
    QString tel = ui->telLineEdit->text();
    QString pwd = ui->pwdLineEdit->text();
    int status = ui->statusComboBox->currentData().toInt();
//    ui->statusComboBox->setCursor();

    QSqlDatabase dbAccount;
    dbAccount = QSqlDatabase::database("connection1");
    QSqlQuery query(dbAccount);
    if (tel.length() != 11) {
        QMessageBox::warning(this, "Invalid",
                             "Please enter a valid phone number");
        return false;
    }
    query.exec(QString("insert into account values('%1', '%2', %3)").arg(tel).arg(pwd).arg(status));
    qDebug() << "sign up" << query.lastError();
    return true;
}

void signUpWindow::on_okBtn_clicked()
{
    if (statusSum == 1) {
        if (signupCustomer()) {
            this->close();
            LoginWindow lw;
            lw.show();
            lw.exec();
        }
    } else {
        if (signupCustomer())
            this->close();
    }


}

void signUpWindow::on_backToLoginBtn_clicked()
{
    this->close();
    LoginWindow lw;
    lw.show();
    lw.exec();
}
