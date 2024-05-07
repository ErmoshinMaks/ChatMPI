#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QtSql>
#include <QVector>


class Client
{
public:
    int id;
    QString FIO;
    QString ip;
};

class ClientTable
{
public:
    Client selectById(int id);
    Client selectByFIO(QString FIO);
    void insert(QString FIO,QString ip);
    QVector<Client> selectAll();
};

#endif // DATABASE_H
