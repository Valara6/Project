#ifndef SINGLTONCLIENT_H
#define SINGLTONCLIENT_H
#include "qobject.h"
class SingletonDestroyer
{
public:
    ~SingletonDestroyer();
};
class SingletonClient: public QObject
{
    static SingletonClient* p_instance;
    static SingletonDestroyer destroyer;
protected:
    SingletonClient();
    SingletonClient(const SingletonClient&) = delete;
    SingletonClient& operator=(const SingletonClient&) = delete;
    ~SingletonClient();
public:
    static SingletonClient* getInstance();
    void SendtoServer(QString);


};

#endif // SINGLTONCLIENT_H
