#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include <QtNetwork>
#include <QByteArray>
#include <QDebug>

#include <QVector>
class MyTcpServer : public QTcpServer
{
    Q_OBJECT

public:
    //explicit MyTcpServer(QObject *parent = nullptr);
    MyTcpServer();
    ~MyTcpServer();
    QTcpSocket *socket;
public slots:
    void slotReadyRead();
    void incomingConnection(qintptr socketDescriptor);
private:
    QVector<QTcpSocket*> sockets;//Массив сокетов
    QByteArray data;
    void SendToClient(QString message);
    void Login(QString email,QString passwrd);
    void Registration(QString email,QString passwrd);
    void SendAnswer(QString ans,int tasknum);
};

#endif // MYTCPSERVER_H

