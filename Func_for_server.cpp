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
//data format: funk_name$dat1$dat2$...
    QList<QByteArray> parts = message.split('$');
    //for(const QByteArray& part : parts){
        //QList<QByteArray> pair = part.split('=');
        qDebug()<<parts[0];
        if(parts[0]=="login"){
            if (parts.count()!=3){
                qDebug()<<"Unvalid data for "<<parts[0];
            }
            else{
            //Разделить имя и пароль
            QString name = parts[1];
            QString pass= parts[2];
            //Убрать \r\n у pass
            Login(name,pass);
            }
        }
        else if (parts[0]=="registration"){
            //Разделить почту, имя, пароль
            if (parts.count()!=4){
                qDebug()<<"Unvalid data for "<<parts[0];
            }
            else
            {
            QString mail=parts[1];
            QString name = parts[2];
            QString pass= parts[3];
            //Убрать \r\n у pass
            Registration(mail,name,pass);
            }
        }
        else{
            qDebug()<< "Invalid func name";
        }
    }



