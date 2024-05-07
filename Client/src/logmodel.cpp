#include "logmodel.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

LogModel::LogModel(QObject *parent) :
    QSqlQueryModel(parent)
{
    // createTable();

    QSqlQuery query;
 
    if (!query.exec("SELECT * FROM Contacts"))
        qFatal("Contacts SELECT query failed: %s", qPrintable(query.lastError().text()));

    setQuery(std::move(query));
    if (lastError().isValid())
        qFatal("Cannot set query on SqlContactModel: %s", qPrintable(lastError().text()));
}

// static void get_contact()
// {
// }
