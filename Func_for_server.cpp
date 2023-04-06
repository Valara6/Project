#include "Funcs_for_server.h"
#include "database.h"
#include <QDebug>
#include <QCoreApplication>
#include <QSqlDatabase>

void Login(const QString& email,const QString& password){
//    DatabaseConnection* db = DatabaseConnection::getInstance();
    QString query="select `login` ('"+email+"','"+password+"') as login ;";
    int boolmember = DatabaseConnection::getInstance()->executeQuery(query);
    if (boolmember == 1) {  // Если найдено больше нуля записей с заданным именем пользователя,
        qDebug() << "User called " << email << "exists in database.";

            }
    else {  // Иначе пользователь с заданным именем не найден в базе данных.
        qDebug() << "Incorrect password or email ";

            }

}
void Registration(const QString& email,const QString& username,const QString& role, const QString& password,const QString& verifypass){
    if(password!=verifypass)
    {
        qDebug() <<"passwords are not same";
        return;
    }

    QString query="select `registration` ('"+email+"','"+username+"','"+password+"','"+role+"');";

    int boolmember =DatabaseConnection::getInstance()->executeQuery(query);
    if (boolmember == 1) {
        qDebug() << "User successfully inserted";
    } else {
        qDebug() << "User not successfully inserted because user with email: " << email << " already exists";
    }
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
            if (parts.count()!=6){
                qDebug()<<"Unvalid data for "<<parts[0];
            }

            else
            {
            QString mail=parts[1];
            QString name = parts[2];
            QString pass= parts[3];
            QString verpass=parts[4];
            QString role = parts[5];
            //Убрать \r\n у pass
            Registration(mail,name,role,pass,verpass);
            }
        }
        else{
            qDebug()<< "Invalid func name";
        }
    }

