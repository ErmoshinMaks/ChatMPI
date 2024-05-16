#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H
#include <QDebug>
#include <QSqlTableModel>
#include "database.h"




class DatabaseController:public QObject
{
    Q_OBJECT
public:
    DatabaseController();
    DatabaseController& operator=(DatabaseController&& other);
    QSqlDatabase returnDb();
    int connection();
    int closing();
    Client selectByFIO(QString FIO);
    void insert(QString FIO,QString ip);
    QVector<Client> selectAll();

private:
    QSqlDatabase db;
    ClientTable clientTable;

};


#endif // DATABASECONTROLLER_H
