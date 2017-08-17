#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QDebug>

//static QString usrnameA;

//void addAccount(QSqlQuery &q, const QString &username,
//                const QString &password, const int &status) {
//    q.addBindValue(username);
//    q.addBindValue(password);
//    q.addBindValue(status);
//}

static void deleteAccount(QSqlQuery &q, const QString &username) {
    q.exec(QString("delete from account where username = '%1'").arg(username));
}

static bool createConnection_forAccount() { 
    QSqlDatabase db1 = QSqlDatabase::addDatabase("QSQLITE", "connection1");
    QSqlQuery query1(db1);

//    if (QSqlDatabase::contains("GBond"))
//        db = QSqlDatabase::database("GBond");
//    else
//        db = QSqlDatabase::addDatabase("QSQLITE","GBond");

    db1.setDatabaseName("account.db"); //set name
    if(!db1.open()) { //if database failed to open
        QMessageBox::critical(0,
                              QString("Cannot open database: account"),
                              QString("Unable to establish a database connection."),
                              QMessageBox::Cancel);
        return false;
    }

    query1.exec("create table account ("
               "username varchar(20) PRIMARY KEY,"
               "password varchar(20),"
               "status int)");
//    status '0 for admin', '1 for customer'
//    query.exec("delete from account where username = 'admin'");
//    query.exec("select * from account where username = 'admin'");
//    qDebug() << query.next();
//    if (!query.next()) {
//        query.exec("insert into account values('admin', 'Zz123456', 0)");
//    }


    query1.exec("select * from account");
    while(query1.next()) {
        QString tel = query1.value(0).toString();
        QString pwd = query1.value(1).toString();
        int status = query1.value(2).toInt();
        qDebug() << tel << pwd << status << endl;
    }

//    query.exec("select password from account where username = 'admin'");
//    query.next();
//    qDebug() << query.value(0).toString();

    return true;   
}

#endif // ACCOUNT_H
