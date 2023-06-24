#include <QtSql>
#include "database.h"
#include <QSqlDatabase>
DatabaseConnection* DatabaseConnection::p_instance = nullptr;
SingletonDestroyer DatabaseConnection::destroyer;

SingletonDestroyer::~SingletonDestroyer()
{
    delete p_database;
}

void SingletonDestroyer::initialize(QSqlDatabase* p)
{
    p_database = p;
}

DatabaseConnection::DatabaseConnection()
{
    database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("localhost"); // set your MySQL host name
    database.setDatabaseName("project#1"); // set your MySQL database name
    database.setUserName("root"); // set your MySQL user name
    database.setPassword("qosimjon123"); // set your MySQL password

    if (!database.open()) {
        qDebug() << "Failed to open database connection.";
    }
}

DatabaseConnection::~DatabaseConnection()
{
    database.close();
}

DatabaseConnection* DatabaseConnection::getInstance()
{
    if (!p_instance) {
        p_instance = new DatabaseConnection();
        destroyer.initialize(&p_instance->database);
    }
    return p_instance;
}

QSqlDatabase& DatabaseConnection::getDatabase()
{
    return database;
}
QString DatabaseConnection::executeQuery(const QString &query)
{
    QSqlQuery s;

    // Подготавливаем запрос
    if (!s.prepare(query)) {
        qDebug() << "Failed to prepare query:" << s.lastError().text();
        return "-1";
    }

    // Выполняем запрос
    if (!s.exec()) {
        qDebug() << "Failed to execute query:" << s.lastError().text();
        return "-1";
    }

    // Переходим к первой записи в результате запроса
    if (!s.next()) {
        qDebug() << "No records returned by query:" << s.lastError().text();
        return "-1";
    }

    // Извлекаем значение первого поля из текущей записи
    QString a = s.value(0).toString();
    return a;
}

