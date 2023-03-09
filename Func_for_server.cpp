#include "Funcs_for_server.h"
#include <QDebug>
#include <QCoreApplication>



void Login(QString username, QString password){
    qDebug()<<"User= "<<username<<" pass="<<password;
}
void Registration(QString email,QString username, QString password){
 qDebug()<<"Mail= "<<email<<" name="<<username<<" pass="<<password;
}
void Parsing(QByteArray message){
    QList<QByteArray> parts = message.split(' ');
    //for(const QByteArray& part : parts){
        //QList<QByteArray> pair = part.split('=');
        if(parts.count()==2){
            //Разделить имя и пароль
            QString name = parts[0];
            QString pass= parts[1];
            //Убрать \r\n у pass
            Login(name,pass);
        }
        else if (parts.count()==3){
            //Разделить почту, имя, пароль
            QString mail=parts[0];
            QString name = parts[1];
            QString pass= parts[2];
            //Убрать \r\n у pass
            Registration(mail,name,pass);
        }
        else{
            qDebug()<< "Invalid Data";
        }
    }



