#include "loginwindow.h"
#include "signupwindow.h"
#include "ui_loginwindow.h"
#include "account.h"
#include "mainwindow.h"
#include "values.h"
#include "waiterwinodw.h"
#include <QDebug>
#include <QSqlError>

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

int LoginWindow::getTableNum()
{
    QSqlDatabase dbTables = QSqlDatabase::database("connection3");
    QSqlQuery query(dbTables);
    query.exec("select * from diningTables");
//    qDebug() << query.lastError();
    while(query.next()) {
        qDebug() << query.value(2).toString();
        if (query.value(2).toString() == '0' & query.value(0).toInt() != 0) {
            // 第0个桌子为测试用，不要分配给用户
            availableTableNum++;
            qDebug() << query.value(0).toInt();
            tableList.append(query.value(0).toInt());
            qDebug() << tableList;
        }
    }
    qDebug() << availableTableNum;
    return availableTableNum;
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

bool LoginWindow::verify_customer()
{
    QString usr = ui->usrLineEdit->text();
    if (usr == NULL) {
        QMessageBox::warning(this, QString("Warning!"),
                             "Username can not be empty");
        ui->usrLineEdit->setFocus();
        return false;
    }

    QSqlDatabase dbAccount;
    dbAccount = QSqlDatabase::database("connection1");
    QSqlQuery query(dbAccount);
    query.exec(QString("select password from account where username = '%1'").arg(usr));
    query.next();
    QString pwd = query.value(0).toString();
    qDebug() << "loginAsCostomer" << pwd;
//    query.exec(QString("select status from account where username = '%1'").arg(usr));
//    query.next();
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
    if (usr == NULL) {
        QMessageBox::warning(this, QString("Warning!"),
                             "Username can not be empty");
        ui->usrLineEdit->setFocus();
        return false;
    }

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


    if (pwd != ui->pwdLineEdit->text()) {
        QMessageBox::warning(this, QString("Warning!"),
                             "Username or password invalid");
        ui->usrLineEdit->clear();
        ui->pwdLineEdit->clear();
        ui->usrLineEdit->setFocus();

        return false;
    }

    //如果不是管理人员，返回错误
    else if (status == 0) {
        QMessageBox::warning(this,QString("Warning!"),
                             "You are not a supervisor");
        return false;
    }

    return true;
}

void LoginWindow::on_signUpBtn_clicked()
{
    this->close();
    signUpWindow suw;
    suw.show();
    suw.exec();
    //signUpWindow.exec();
}

void LoginWindow::on_signInBtn_customer_clicked()
{
//    if(verify_customer()) {
//        QString usrnameA = ui->usrLineEdit->text();
//        this->hide();
//        accept();
//        chooseTableWindow ctw;
//        ctw.show();
//        ctw.exec();
//    }

    if (verify_customer()) {
        QString usrnameA = ui->usrLineEdit->text();
        QMessageBox checkTableMessageBox(this);
        QAbstractButton *confirmButton =
                checkTableMessageBox.addButton("确认", QMessageBox::ActionRole);
        QAbstractButton *cancelButton =
                checkTableMessageBox.addButton("取消", QMessageBox::ActionRole);
        checkTableMessageBox.setText(QString("目前可用餐的餐桌数为: %1").arg(getTableNum()));
        checkTableMessageBox.exec();

        if (checkTableMessageBox.clickedButton() == confirmButton) {
            QSqlDatabase dbTables = QSqlDatabase::database("connection3");
            QSqlQuery query(dbTables);
            if (!availableTableNum > 0) {
                //如果没有桌子显示错误提示
                QMessageBox::warning(this, "No table available!",
                                     "There is no table left. Please wait for some time");
            } else {
                //如果有空桌子，分配排序最前面的桌子，并进入主界面
                query.exec(QString("update diningTables set user = %1 where id = %2").arg(usrnameA).arg(tableList[0]));
                qDebug() << query.lastError();
                tableId = tableList[0];
                qDebug() << tableId;
                this->hide();
                accept();
            }
        }
    }
}

void LoginWindow::on_signInBtn_admin_clicked()
{
    if(verify_admin()) {
        this->close();
        WaiterWinodw ww;
        ww.show();
        ww.exec();
    }
}
