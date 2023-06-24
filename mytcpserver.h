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
    static MyTcpServer* getInstance();
    ~MyTcpServer();
    QTcpSocket *socket;
signals:
    void sendToClientSignal(QString message);
public slots:
    void slotReadyRead();
    void incomingConnection(qintptr socketDescriptor);
    void sendToClientSlot(QString message);
private:
    QVector<QTcpSocket*> sockets;//Массив сокетов
    QByteArray data;
    void SendToClient(QString message);
    MyTcpServer();
    static MyTcpServer* m_instance;
};

#endif // MYTCPSERVER_H
