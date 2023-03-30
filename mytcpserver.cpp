#include "mytcpserver.h"
#include "Funcs_for_server.h"
#include <QDebug>
#include <QCoreApplication>
#include <QDataStream>

MyTcpServer::~MyTcpServer()
{

}
MyTcpServer::MyTcpServer(){
    if(this->listen(QHostAddress::Any,33333))//Задаём адреса и порт подключения к серверу
    {
        qDebug() << "start";
    }
    else    {
        qDebug() << "error";
    }
}

void MyTcpServer::incomingConnection(qintptr socketDescriptor){
    socket=new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, &QTcpSocket::readyRead,this, &MyTcpServer::slotReadyRead);
    connect(socket,&QTcpSocket::disconnected,socket,&QTcpSocket::deleteLater);

    sockets.push_back(socket);//Добавляем сокет в массив
    qDebug()<<"Client connected" <<socketDescriptor;
}

void MyTcpServer::slotReadyRead(){
    socket=(QTcpSocket*)sender();
    QDataStream in(socket);

    if(in.status()==QDataStream::Ok){
        qDebug() <<"Ready to read.";
        QByteArray requestData="";
        QString request = "";
        while(socket->bytesAvailable()>0){
            // Read data from the client
            requestData = socket->readAll();
            request += QString::fromUtf8(requestData);
            request.chop(2);
            qDebug() <<"client said "<<request;
        }

        if (!request.isEmpty()) {
            requestData.chop(2);
            Parsing(requestData);
        }
    }
    else{
        qDebug() << "DataStream error";
    }
}




void MyTcpServer::SendToClient(QString request){
    qDebug() <<"Sending... "<<request;
    data.clear();
    //QByteArray responseData;
    //QString response=" ";
    if (request=="who\r\n"){
        socket->write("cares\n");
    }
    else{
    QByteArray responseData= request.toUtf8();
    socket->write("You said: " +responseData);}
    socket->flush();
}



