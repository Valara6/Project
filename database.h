#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <QtSql>
#include <QSqlDatabase>

class SingletonDestroyer
{
private:
    QSqlDatabase* p_database;
public:
    ~SingletonDestroyer();
    void initialize(QSqlDatabase* p);
};

class DatabaseConnection
{
private:
    static DatabaseConnection* p_instance;
    static SingletonDestroyer destroyer;
    QSqlDatabase database;

protected:
    DatabaseConnection();
    DatabaseConnection(const DatabaseConnection&) = delete;
    DatabaseConnection& operator=(const DatabaseConnection&) = delete;
    ~DatabaseConnection();

    friend class SingletonDestroyer;

public:
    static DatabaseConnection* getInstance();
    QSqlDatabase& getDatabase();
    QSqlQuery executeQuery(const QString& query);
};

#endif // DATABASECONNECTION_H
