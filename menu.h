#ifndef MENU_H
#define MENU_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QDebug>
#include <QSqlError>

//void addDish(QSqlQuery &q, const int &id, const QString &name,
//             const int &price, const int remains, const int rate) {
//    q.addBindValue(id);
//    q.addBindValue(name);
//    q.addBindValue(price);
//    q.addBindValue(remains);
//    q.addBindValue(rate);
//}

//void deleteDish(QSqlQuery &q, const int &id) {
//    q.exec(QString("delete from menu where id = '%1").arg(id));
//}

static QStringList menuList;
static int menuNum = 0;

static bool createConnection_forMenu() {

    QSqlDatabase db2 = QSqlDatabase::addDatabase("QSQLITE", "connection2");
    QSqlQuery query2(db2);

    db2.setDatabaseName("menu.db"); //set name
    if(!db2.open()) { //if database failed to open
        QMessageBox::critical(0,
                              QString("Cannot open database: account"),
                              QString("Unable to establish a database connection."),
                              QMessageBox::Cancel);
        return false;
    }

    query2.exec("create table menu ("
               "id int primary key,"
               "name varchar(20),"
               "price int,"
               "remains int,"
               "rate int)");

    qDebug() << query2.lastError();
//    rate for 评价；remains for 剩余的数量；

    query2.exec("insert into menu values(1, 'Spring Rolls', 5, 100, 5)");
    query2.exec("insert into menu values(2, 'Lobster Slices', 3, 100, 5)");
    query2.exec("insert into menu values(3, 'Fried Wonton', 20, 100, 5)");
    query2.exec("insert into menu values(4, 'Fried Seaweed', 8, 100, 5)");
    query2.exec("insert into menu values(5, 'Shrimps Toast', 10, 100, 5)");
    query2.exec("insert into menu values(6, 'Mais Soup', 6, 100, 5)");
    query2.exec("insert into menu values(7, 'Wonton Soup', 15, 100, 5)");
    query2.exec("insert into menu values(8, 'Hot and Sour Soup', 12, 100, 5)");
    query2.exec("insert into menu values(9, 'Shark Fin Soup', 100, 100, 5)");

    query2.exec("select * from menu");
    while(query2.next()) {
        int id = query2.value(0).toInt();
        QString name = query2.value(1).toString();
        int price = query2.value(2).toInt();
        menuNum++;
        qDebug() << id << name << price << endl;
//        qDebug() << menuNum;
    }

    for (int i=1; i<=menuNum; i++) {
        query2.exec(QString("select name from menu where id = %1").arg(i));
        query2.next();
        QString menuThis = query2.value(0).toString();
        menuList.append(menuThis);
    }
    qDebug() << menuList;

    return true;
}

#endif // MENU_H
