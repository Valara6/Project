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
QSqlQuery DatabaseConnection::executeQuery(const QString &query)
{
    QSqlQuery s;

    // Подготавливаем запрос для поиска пользователя с заданным именем в таблице 'users'
    s.prepare(query);
    s.exec();  // Выполняем запрос
    s.next();  // Переходим к первой записи в результате запроса
    return s;
}
