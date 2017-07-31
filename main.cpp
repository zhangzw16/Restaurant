#include "mainwindow.h"
#include <QApplication>
#include "account.h"
#include "menu.h"
#include "loginwindow.h"
#include "signupwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(!createConnection_forMenu()) return 2;
    if(!createConnection_forAccount()) return 1;

    QSqlQuery query;
    query.exec(QString("select password from account where username = '18811029016'"));
    query.next();
    QString pwd = query.value(0).toString();
    qDebug() << pwd;

    LoginWindow lw;
    signUpWindow suw;
    lw.show();
    MainWindow w;
    //w.show();

    if (lw.exec() == QDialog::Accepted) {
        w.show();
        return a.exec();
    }

//    MainWindow w;
//    w.show();

//    QSqlQuery query;
//    query.exec("select * from menu");
//    while(query.next()) {
//        int id = query.value(0).toInt();
//        QString name = query.value(1).toString();
//        int price = query.value(2).toInt();
//        qDebug() << id << name << price << endl;
//    }

    return a.exec();
}
