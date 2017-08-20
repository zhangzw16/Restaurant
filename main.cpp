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
int tablesNum = -1; //在tables.h中累加，因为有第零桌所以从-1开始加
int tableId = 0;
int availableTableNum = 0;
QList<int> tableList;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile f(":qdarkstyle/style.qss");
    if (!f.exists())
    {
        printf("Unable to set stylesheet, file not found\n");
    }
    else
    {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        qApp->setStyleSheet(ts.readAll());
    }

    if(!createConnection_forMenu()) return 1;
    if(!createConnection_forAccount()) return 1;
    if(!createConnection_forTables()) return 1;

    LoginWindow lw;
    lw.show();
//    MainWindow w;
    //w.show();

    if (lw.exec() == QDialog::Accepted) {
        MainWindow w;
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
