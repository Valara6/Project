#include "singletonsocket.h"

#include <QTcpSocket>

SingletonSocket* SingletonSocket::m_instance = nullptr;

SingletonSocket::SingletonSocket(QObject* parent) : QObject(parent)
{
    m_socket = new QTcpSocket(this);
    connect(m_socket, &QTcpSocket::connected, this, &SingletonSocket::on_connected);
    connect(m_socket, &QTcpSocket::disconnected, this, &SingletonSocket::on_disconnected);
    connect(m_socket, &QTcpSocket::readyRead, this, &SingletonSocket::on_readyRead);

    m_socket->connectToHost("127.0.0.1", 33333);
}
QTcpSocket* SingletonSocket::getSocket() { return m_socket; }
SingletonSocket::~SingletonSocket()
{
    delete m_socket;
}

SingletonSocket* SingletonSocket::instance()
{
    if (m_instance == nullptr) {
        m_instance = new SingletonSocket();
    }
    return m_instance;
}

void SingletonSocket::write(const QByteArray& data)
{
    if (m_socket->state() == QAbstractSocket::ConnectedState) {
        m_socket->write(data);
    }
}

void SingletonSocket::on_connected()
{
    qDebug() << "Connected to server";
}

void SingletonSocket::on_disconnected()
{
    qDebug() << "Disconnected from server";
}

void SingletonSocket::on_readyRead()
{
    QTcpSocket* socket = getSocket();
    QByteArray response = socket->readAll();
    QList<QByteArray> parts = response.split('$');
    if(parts.count()==4)
    {
        parts[1]+="$"+parts[2]+"$"+parts[3];
    }
    if(parts.count()==3)
    {
        parts[1]+="$"+parts[2];
    }
    qDebug() << "Received data from server:" << parts[1];
    emit messageReceived(parts[1],parts[0]);

}
