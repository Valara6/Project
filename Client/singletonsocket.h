#ifndef SINGLETONSOCKET_H
#define SINGLETONSOCKET_H

#include <QObject>
#include <QTcpSocket>

class SingletonSocket : public QObject
{
Q_OBJECT
public:
static SingletonSocket* instance();
void write(const QByteArray& data);
QTcpSocket* getSocket();
signals:
    void messageReceived(const QString& message,const QString& windowName);
private slots:
void on_connected();
void on_disconnected();
void on_readyRead();

private:
explicit SingletonSocket(QObject* parent = nullptr);
~SingletonSocket();
static SingletonSocket* m_instance;
QTcpSocket* m_socket;
};

#endif // SINGLETONSOCKET_H
