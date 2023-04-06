#ifndef SINGLETON_H
#define SINGLETON_H
#include <QSqlDatabase>
class Singleton;

class SingletonDestroyer
{
    private:
        Singleton * p_instance;
    public:
        ~SingletonDestroyer() { delete p_instance;}
        void initialize(Singleton * p){p_instance = p;}
};


class Singleton
{
    private:
        static Singleton * p_instance;
        static SingletonDestroyer destroyer;
        static QSqlDatabase db;
    protected:
        Singleton(){
            db = QSqlDatabase::addDatabase("QMYSQL");
            db.setHostName("localhost");
            db.setPort(3306);
            db.setDatabaseName("project#1");
                            db.setUserName("root");
                            db.setPassword("qosimjon123");}
        Singleton(const Singleton& );
        Singleton& operator = (Singleton &);
        ~Singleton() {db.close();}
        friend class SingletonDestroyer;
    public:


        static Singleton* getInstance(){
            if (!p_instance)
            {
                p_instance = new Singleton();
                destroyer.initialize(p_instance);
            }
            return p_instance;
        }
        QByteArray sendQuery(QString b)
        {

        }
        QByteArray sendQuery(QString b,int b)
        {
            QSqlQuery query;
                // Подготавливаем запрос для поиска пользователя с заданным именем в таблице 'users'
                query.prepare("select login (:email,:password) as login ;");

                query.exec();  // Выполняем запрос
                query.next();  // Переходим к первой записи в результате запроса
                int boolmember = query.value(0).toInt();  // Получаем значение первого столбца первой записи
                if (boolmember == 1) {  // Если найдено больше нуля записей с заданным именем пользователя,
                    qDebug() << "User called " << email << "exists in database.";

                }
                else {  // Иначе пользователь с заданным именем не найден в базе данных.
                    qDebug() << "Incorrect password or email ";

                }
        }
};

Singleton * Singleton::p_instance;
SingletonDestroyer Singleton::destroyer;
Singleton * SingletonDestroyer::p_instance;
#endif // SINGLETON_H
