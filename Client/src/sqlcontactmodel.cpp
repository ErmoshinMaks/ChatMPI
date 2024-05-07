#include "sqlcontactmodel.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

SqlContactModel::SqlContactModel(QObject *parent) :
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