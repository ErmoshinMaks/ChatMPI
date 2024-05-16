#include "databasecontroller.h"

DatabaseController::DatabaseController()
{
    //this->connection();

}

DatabaseController& DatabaseController::operator=(DatabaseController&& other) {
    if(this != &other) {
        db = std::move(other.db);
    }
    return *this;
}

int DatabaseController::connection()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../CLIENTINFO");

    if (db.open())
    {
        qInfo() << "Database is open!";
        return 0;
    }
    else {
        qInfo() << "Can not open database! "<<db.lastError().databaseText();
        return -1;
    }


}



QSqlDatabase DatabaseController::returnDb()
{
    return db;
}

int DatabaseController::closing()
{
     db.close();
     qInfo() << "Database is closed!";

     return 0;
}

Client DatabaseController::selectByFIO(QString FIO)
{
    return clientTable.selectByFIO(FIO);
}

void DatabaseController::insert(QString FIO,QString ip)
{
    clientTable.insert( FIO, ip);
}



QVector<Client> DatabaseController::selectAll()
{
    return clientTable.selectAll();
}