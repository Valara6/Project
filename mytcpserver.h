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
};
#endif // MYTCPSERVER_H







