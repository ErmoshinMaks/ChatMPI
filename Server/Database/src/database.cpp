#include "database.h"

Client ClientTable::selectById(int id)
{
    QSqlQuery my_query;
    my_query.prepare("SELECT * FROM Client WHERE id = (:id)");
    my_query.bindValue(":id", id);
    my_query.exec();

    QSqlRecord rec = my_query.record();
    my_query.first();

    QString FIO = my_query.value(rec.indexOf("FIO")).toString();
    QString ip = my_query.value(rec.indexOf("ip")).toString();


    qInfo() << "Row with id =" <<id<<"FIO = "<< FIO <<"ip ="<< ip;

    Client client = {id, FIO,ip};
    return client;
}

Client ClientTable::selectByFIO(QString FIO)
{
    QSqlQuery my_query;
    my_query.prepare("SELECT * FROM Client WHERE FIO = (:FIO)");
    my_query.bindValue(":FIO", FIO);
    my_query.exec();

    QSqlRecord rec = my_query.record();
    my_query.first();

    int id = my_query.value(rec.indexOf("id")).toInt();
    QString ip = my_query.value(rec.indexOf("ip")).toString();


    qInfo() << "Row with id =" <<id<<"FIO = "<< FIO <<"ip ="<< ip;

    Client client = {id, FIO,ip};
    return client;
}

void ClientTable::insert(QString FIO,QString ip)
{
    if (selectByFIO(FIO).id != 0)
    {
            qInfo() << "You have already registred";
            return;
    }
    QSqlQuery query;
    int id = rand() % (1000000 - 1 + 1) + 0;
    query.prepare("INSERT INTO Client (id, FIO,ip) VALUES (:id, :FIO,:ip)");
    query.bindValue(":id", id);
    query.bindValue(":FIO", FIO);
    query.bindValue(":ip", ip);

    if (!query.exec()) {
        qInfo() << "Cant insert data";
    }
}

QVector<Client> ClientTable::selectAll()
{
    QVector<Client> vec;
    QSqlQuery my_query;
    my_query.prepare("SELECT * FROM Client");
    my_query.exec();

    QSqlRecord rec = my_query.record();
    while(my_query.next())
    {
        int id = my_query.value(rec.indexOf("id")).toInt();
        QString FIO = my_query.value(rec.indexOf("FIO")).toString();
        QString ip = my_query.value(rec.indexOf("ip")).toString();

        Client client = {id,FIO,ip};
        vec.append(client);
    }

    return vec;
}

