#include "loginwindow.h"
#include "signupwindow.h"
#include "ui_loginwindow.h"
#include "account.h"
#include "mainwindow.h"
#include "choosetablewindow.h"
#include <QDebug>

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

bool LoginWindow::verify_customer()
{
    QString usr = ui->usrLineEdit->text();
    qDebug() << usr;
    QSqlDatabase dbAccount;
    dbAccount = QSqlDatabase::database("connection1");
    QSqlQuery query(dbAccount);
    query.exec(QString("select password from account where username = '%1'").arg(usr));
    query.next();

    QString pwd = query.value(0).toString();
    qDebug() << pwd;

    query.exec(QString("select status from account where username = '%1'").arg(usr));
    query.next();
    //int status = query.value(0).toInt();
    //if (status != 0) return false;

    if (pwd != ui->pwdLineEdit->text()) {
        QMessageBox::warning(this, QString("Warning!"),
                             "Username or password invalid");
        ui->usrLineEdit->clear();
        ui->pwdLineEdit->clear();
        ui->usrLineEdit->setFocus(); // 把光标固定在usrLineEdit上

        return false;
    }

    return true;
}

bool LoginWindow::verify_admin()
{
    QString usr = ui->usrLineEdit->text();
    qDebug() << usr;

    QSqlDatabase dbAccount;
    dbAccount = QSqlDatabase::database("connection1");
    QSqlQuery query(dbAccount);
    query.exec(QString("select password from account where username = '%1'").arg(usr));
    query.next();

    QString pwd = query.value(0).toString();
    qDebug() << pwd;

    query.exec(QString("select status from account where username = '%1'").arg(usr));
    query.next();
    int status = query.value(0).toInt();

    //如果不是管理人员，返回错误
    if (status != 0) return false;

    if (pwd != ui->pwdLineEdit->text()) {
        QMessageBox::warning(this, QString("Warning!"),
                             "Username or password invalid");
        ui->usrLineEdit->clear();
        ui->pwdLineEdit->clear();
        ui->usrLineEdit->setFocus(); // 把光标固定在usrLineEdit上

        return false;
    }

    return true;
}

void LoginWindow::on_signUpBtn_clicked()
{
    this->hide();
    signUpWindow suw;
    suw.show();
    suw.exec();
    //signUpWindow.exec();
}

void LoginWindow::on_signInBtn_customer_clicked()
{
    if(verify_customer()) {
        usrnameA = ui->usrLineEdit->text();
        this->hide();
        accept();
//        chooseTableWindow ctw;
//        ctw.show();
//        ctw.exec();
    }
}

void LoginWindow::on_signInBtn_admin_clicked()
{
//    if(verify_admin()) {
//        this->hide();
//        accept();
//        //mw.exec();
//    }

    MainWindow mw;
    mw.show();
}
