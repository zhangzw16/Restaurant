#ifndef TABLES_H
#define TABLES_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QDebug>

void addTable(QSqlQuery &q, const int &id, const QString &waiter,
              const QString &user, const int dish1, const int dish2,
              const int dish3, const int dish4, const int dish5,
              const int dish6, const int dish7, const int dish8,
              const int dish9, const int dish10, const int dish11) {
    q.addBindValue(id);
    q.addBindValue(waiter);
    q.addBindValue(user);
    q.addBindValue(dish1);
    q.addBindValue(dish2);
    q.addBindValue(dish3);
    q.addBindValue(dish4);
    q.addBindValue(dish5);
    q.addBindValue(dish6);
    q.addBindValue(dish7);
    q.addBindValue(dish8);
    q.addBindValue(dish9);
    q.addBindValue(dish10);
    q.addBindValue(dish11);
}

void deleteTable(QSqlQuery &q, const int &id) {
    q.exec(QString("delete from tables where id = '%1").arg(id));
}


static bool createConnection_froTables() {

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "connection3");
    QSqlQuery query(db);

    db.setDatabaseName("tables.db");
    if(!db.open()) {
        QMessageBox::critical(0,
                              QString("Cannot open database: tables"),
                              QString("Unable to establish a database connection."),
                              QMessageBox::Cancel);
        return false;
    }

    query.exec("create table tables ("
               "id int primary key,"
               "waiter varchar(20),"
               "user varchar(20),"
               "dish1 int,"
               "dish2 int,"
               "dish3 int,"
               "dish4 int,"
               "dish5 int,"
               "dish6 int"
               "dish7 int"
               "dish8 int"
               "dish9 int"
               "dish10 int"
               "dish11 int"
               "dish12 int"
               "dish13 int"
               "waiter varchar(20))")
}

#endif // TABLES_H
