#include <QtCore>
#include <QGuiApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QtQml>

#include <stdio.h>

#include "sqlconversationmodel.h"
#include "sqlcontactmodel.h"
#include "logmodel.h"

static void connect_to_server()
{

}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<LogModel>("chatlib", 1, 0, "LogModel");
    qmlRegisterType<SqlContactModel>("chatlib", 1, 0, "SqlContactModel");
    qmlRegisterType<SqlConversationModel>("chatlib", 1, 0, "SqlConversationModel");

    connect_to_server();
    
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}