#ifndef TABLES_H
#define TABLES_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QDebug>
#include <QSqlError>

//static void addTable(QSqlQuery &q, int &id, QString &waiter,
//              QString &user, int &dish1, int &dish2,
//              int &dish3, int &dish4, int &dish5,
//              int &dish6, int &dish7, int &dish8,
//              int &dish9, int &dish10, int &dish11,
//                     int &dish12, int &dish13) {
//    q.exec(QString("insert into diningTables values(%1, '%2', '%3', %4, %5, %6 ,%7, %8, %9, %10, %11, %12, %13, %14, %15, %16").arg(id).arg(waiter).arg(user).arg(dish1).arg(dish2).arg(dish3).arg(dish4).arg(dish5).arg(dish6).arg(dish7).arg(dish8).arg(dish9).arg(dish10).arg(dish11).arg(dish12).arg(dish13));
//    qDebug() << q.lastError() << QString("addTable");
//}

static void addDish(QSqlQuery &q, const int &id, const int &quantity, const QString &dish) {
    qDebug() << QString("update diningTables set %1 = %2 where id = %3").arg(dish).arg(quantity).arg(id);
    q.exec(QString("update diningTables set %1 = %2 where id = %3").arg(dish).arg(quantity).arg(id));
}

static bool createConnection_forTables() {

    QSqlDatabase db3 = QSqlDatabase::addDatabase("QSQLITE", "connection3");
    QSqlQuery query(db3);

    db3.setDatabaseName("diningTables.db");
    if(!db3.open()) {
        QMessageBox::critical(0,
                              QString("Cannot open database: diningTables"),
                              QString("Unable to establish a database connection."),
                              QMessageBox::Cancel);
        return false;
    }

    query.exec("create table diningTables ("
               "id int primary key,"
               "waiter varchar(20),"
               "user varchar(20),"
               "dish1 int,"
               "dish2 int,"
               "dish3 int,"
               "dish4 int,"
               "dish5 int,"
               "dish6 int,"
               "dish7 int,"
               "dish8 int,"
               "dish9 int,"
               "dish10 int,"
               "dish11 int,"
               "dish12 int,"
               "dish13 int)");

    qDebug() << query.lastError();

//    addTable(query, 2, QString('0'), QString('0'), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
//    addTable(query, 2, QString('0'), QString('0'), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);



    query.exec("insert into diningTables values(0, '0', '0', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)");
    query.exec("insert into diningTables values(1, '0', '0', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)");
    query.exec("insert into diningTables values(2, '1', '0', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)");
    query.exec("insert into diningTables values(3, '0', '0', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)");
    query.exec("insert into diningTables values(4, '0', '0', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)");
    query.exec("insert into diningTables values(5, '0', '0', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)");
    query.exec("insert into diningTables values(6, '0', '0', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)");
    query.exec("insert into diningTables values(7, '0', '0', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)");
    query.exec("insert into diningTables values(8, '0', '0', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)");
    query.exec("insert into diningTables values(9, '0', '0', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)");
    query.exec("insert into diningTables values(10, '0', '0', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)");

//    addDish(query, 0, 13, QString("dish1"));
//    query.exec("update diningTables set dish1 = 12 where id = 0");
//    qDebug() << query.lastError();
    query.exec("select * from diningTables");
    while(query.next()) {
        int id = query.value(0).toInt();
        QString waiter = query.value(1).toString();
        QString usrname = query.value(2).toString();
        int d1 = query.value(3).toInt();
        int d2 = query.value(4).toInt();
        int d3 = query.value(5).toInt();
        int d4 = query.value(6).toInt();
        int d5 = query.value(7).toInt();
        int d6 = query.value(8).toInt();
        int d7 = query.value(9).toInt();
        int d8 = query.value(10).toInt();
        int d9 = query.value(11).toInt();
        int d10 = query.value(12).toInt();
        int d11 = query.value(13).toInt();
        int d12 = query.value(14).toInt();
        int d13 = query.value(15).toInt();
        qDebug() << id << waiter << usrname << d1 << d2 << d3 << d4
                 << d5 << d6 << d7 << d8 << d9 << d10 << d11 << d12 << d13;

    }
    return true;
}

static void deleteTable(QSqlQuery &q, const int &id) {
    q.exec(QString("delete from diningTables where id = '%1").arg(id));
}

static QList<int> getQuantityList(QSqlQuery &q, const int &id) {
    QList<int> quantityList;
    for (int i=1; i<=13; i++) {
        q.exec(QString("select dish%1 from diningTables where id = %2").arg(i).arg(id));
        q.next();
        quantityList.append(q.value(0).toInt());
    }
    return quantityList;
}

#endif // TABLES_H
