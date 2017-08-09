#include "mainwindow.h"
#include <QApplication>
#include "account.h"
#include "menu.h"
#include "loginwindow.h"
#include "signupwindow.h"
#include "menuwindow.h"
#include "tables.h"
#include "menuwindow.h"
#include "values.h"

QStringList menuList;
int menuNum = 0;
int tablesNum = 10;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(!createConnection_forMenu()) return 1;
    if(!createConnection_forAccount()) return 1;
    if(!createConnection_forTables()) return 1;

    QSqlDatabase dbAccount = QSqlDatabase::database("connection1");
    QSqlQuery query(dbAccount);
    query.exec(QString("select password from account where username = '18811029016'"));
    query.next();
    QString pwd = query.value(0).toString();
    qDebug() << pwd;

    LoginWindow lw;
    signUpWindow suw;
    menuwindow mw;
    lw.show();
    MainWindow w;
    //w.show();

    if (lw.exec() == QDialog::Accepted) {
        w.show();
        return a.exec();
    }




//   menuwindow mw;
//   mw.show();

//   return a.exec();




//    MainWindow w;

//    QSqlDatabase dbMenu;
//    dbMenu = QSqlDatabase::database("connection2");
//    QSqlQuery query(dbMenu);
//    query.exec("select * from menu");
//    while(query.next()) {
//        int id = query.value(0).toInt();
//        QString name = query.value(1).toString();
//        int price = query.value(2).toInt();
//        qDebug() << id << name << price << endl;
//    }

//    w.show();
    return a.exec();
}
