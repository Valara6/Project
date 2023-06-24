#include "Funcs_for_server.h"
#include "database.h"
#include <QDebug>
#include <QCoreApplication>
#include <QSqlDatabase>
#include "mytcpserver.h"
void settask(const QString& name,const QString& nameex,const QString& des, const QString& ans)
{
    QString query="select `add_tasks` ('"+name+"','"+nameex+"','"+des+"','"+ans+"') as login ;";
    QString boolmember = DatabaseConnection::getInstance()->executeQuery(query);
    if (boolmember == "1") {  // Если найдено больше нуля записей с заданным именем пользователя,
        QString a="settask$task inserted successfully.";
        qDebug() << a;
        MyTcpServer::getInstance()->sendToClientSlot(a);
            }
    else {  // Иначе пользователь с заданным именем не найден в базе данных.
        QString a="settask$task not inserted successfully. ";
        qDebug() << a;
        MyTcpServer::getInstance()->sendToClientSlot(a);
            }
}



void updatedes(const QString& name,const QString& nameex,const QString& des)
{
    QString query="select `update-des` ('"+name+"','"+nameex+"','"+des+"') as login ;";
    QString boolmember = DatabaseConnection::getInstance()->executeQuery(query);
    if (boolmember == "1") {  // Если найдено больше нуля записей с заданным именем пользователя,
        QString a="uptdes$Updated successfully.";
        qDebug() << a;
        MyTcpServer::getInstance()->sendToClientSlot(a);
            }
    else {  // Иначе пользователь с заданным именем не найден в базе данных.
        QString a="uptdes$Not updated successfully. ";
        qDebug() << a;
        MyTcpServer::getInstance()->sendToClientSlot(a);
            }
}



void updateans(const QString& name,const QString& nameex,const QString& ans)
{
    QString query="select `updateans` ('"+name+"','"+nameex+"','"+ans+"') as login ;";
    QString boolmember = DatabaseConnection::getInstance()->executeQuery(query);
    if (boolmember == "1") {  // Если найдено больше нуля записей с заданным именем пользователя,
        QString a="uptans$Updated successfully.";
        qDebug() << a;
        MyTcpServer::getInstance()->sendToClientSlot(a);
            }
    else {  // Иначе пользователь с заданным именем не найден в базе данных.
        QString a="uptans$Not updated successfully. ";
        qDebug() << a;
        MyTcpServer::getInstance()->sendToClientSlot(a);
            }
}


void deletetask(const QString& nameex)
{
    QString query="select `deltask` ('"+nameex+"') as login ;";
    QString boolmember = DatabaseConnection::getInstance()->executeQuery(query);
    if (boolmember == "1") {  // Если найдено больше нуля записей с заданным именем пользователя,
        QString a="deltask$deleted successfully.";
        qDebug() << a;
        MyTcpServer::getInstance()->sendToClientSlot(a);
            }
    else {  // Иначе пользователь с заданным именем не найден в базе данных.
        QString a="deltask$Not deleted successfully.";
        qDebug() << a;
        MyTcpServer::getInstance()->sendToClientSlot(a);
            }
}




void Statistic_stud(QString& name)
{
    QString query="select concat(задача№1,'$',задача№2,'$', задача№3) from overstat where username='"+name+"' ;";
    QString task_des = DatabaseConnection::getInstance()->executeQuery(query);
    if (task_des.size() > 1) {  // Если найдено больше нуля записей с заданным именем пользователя,
        QString a="getstat$"+task_des;
        qDebug() << a;
        MyTcpServer::getInstance()->sendToClientSlot(a);
            }
    else {  // Иначе пользователь с заданным именем не найден в базе данных.
        QString a="gettask$not found task";
        qDebug() << a;
        MyTcpServer::getInstance()->sendToClientSlot(a);
            }
}
void gettask(const QString& name)
{
    QString query="select description from tasks where name='"+name+"' ;";
    QString task_des = DatabaseConnection::getInstance()->executeQuery(query);
    if (task_des.size() > 5) {  // Если найдено больше нуля записей с заданным именем пользователя,
        QString a="gettask$"+task_des;
        qDebug() << a;
        MyTcpServer::getInstance()->sendToClientSlot(a);
            }
    else {  // Иначе пользователь с заданным именем не найден в базе данных.
        QString a="gettask$not found task";
        qDebug() << a;
        MyTcpServer::getInstance()->sendToClientSlot(a);
            }
}
void CheckResult(const QString &taskname, const QString &answer,const QString &username)
{
    QString query = "SELECT IF (count(*) > 0, \"correct\", \"incorrect\") FROM tasks WHERE name='" + taskname + "' AND correct_answer='" + answer + "';";
    QString boolmember = DatabaseConnection::getInstance()->executeQuery(query);
    qDebug() << boolmember;
    if (boolmember== "correct") {  // Если найдено больше нуля записей с заданным именем пользователя,
        QString a="chkres$Correct answer.";
        qDebug() << a;

        MyTcpServer::getInstance()->sendToClientSlot(a);
        qDebug()<<taskname;
        qDebug()<<username;
        QString query_str = "UPDATE overstat SET `"+taskname+"` = IF(`"+taskname+"` >= 0, `"+taskname+"` + 1, `"+taskname+"`) WHERE `username` = '"+username+"';";
        DatabaseConnection::getInstance()->executeQuery(query_str);

            }
    else {  // Иначе пользователь с заданным именем не найден в базе данных.
        QString a="chkres$Incorrect answer.";
        qDebug() << a;
        MyTcpServer::getInstance()->sendToClientSlot(a);
        qDebug()<<taskname;
        qDebug()<<username;
        QString query_str ="UPDATE overstat SET `"+taskname+"` = IF(`"+taskname+"` > 0, `"+taskname+"` - 1, `"+taskname+"`) WHERE `username` = '"+username+"';";;
        DatabaseConnection::getInstance()->executeQuery(query_str);

            }
}
void Login(const QString& email,const QString& password){
//    DatabaseConnection* db = DatabaseConnection::getInstance();
    QString query="select `login` ('"+email+"','"+password+"') as login ;";
    QString boolmember = DatabaseConnection::getInstance()->executeQuery(query);
    if (boolmember == "1") {  // Если найдено больше нуля записей с заданным именем пользователя,
        QString query2="select `role` ('"+email+"') as role ;";
        QString boolmember2 = DatabaseConnection::getInstance()->executeQuery(query2);
        QString a="log$User exists in database.$"+boolmember2;
        qDebug() << a;
        MyTcpServer::getInstance()->sendToClientSlot(a);
            }
    else {  // Иначе пользователь с заданным именем не найден в базе данных.
        QString a="log$Incorrect password or email ";
        qDebug() << a;
        MyTcpServer::getInstance()->sendToClientSlot(a);
            }

}
void Registration(const QString& email,const QString& username,const QString& role, const QString& password,const QString& verifypass){
    if(password!=verifypass)
    {
        QString a="reg$passwords are not same";
        qDebug() <<a;
        MyTcpServer::getInstance()->sendToClientSlot(a);
        return;
    }

    QString query="select `registration` ('"+email+"','"+username+"','"+password+"','"+role+"');";

    QString boolmember =DatabaseConnection::getInstance()->executeQuery(query);
    if (boolmember == "1") {
        QString a="reg$User successfully inserted";
        qDebug() << a;
        MyTcpServer::getInstance()->sendToClientSlot(a);
    } else {
        QString a = "reg$User not successfully inserted";
        qDebug() << a;
        MyTcpServer::getInstance()->sendToClientSlot(a);
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
        else if (parts[0]=="getstat"){
            //Разделить почту, имя, пароль
            if (parts.count()!=2){
                qDebug()<<"Unvalid data for "<<parts[0];
            }

            else
            {
                QString name = parts[1];
                //Убрать \r\n у pass
                Statistic_stud(name);
            }
        }
        else if (parts[0]=="gettask"){
            //Разделить почту, имя, пароль
            if (parts.count()!=2){
                qDebug()<<"Unvalid data for "<<parts[0];
            }

            else
            {
                QString name = parts[1];
                //Убрать \r\n у pass
                gettask(name);
            }
        }
        else if (parts[0]=="settask"){
            //Разделить почту, имя, пароль
            if (parts.count()!=5){
                qDebug()<<"Unvalid data for "<<parts[0];
            }

            else
            {
                QString name = parts[1];
                QString nameexer = parts[2];
                QString des = parts[3];
                QString ans = parts[4];
                //Убрать \r\n у pass
                settask(name, nameexer,des,ans);
            }
        }
        else if (parts[0]=="deltask"){
            //Разделить почту, имя, пароль
            if (parts.count()!=2){
                qDebug()<<"Unvalid data for "<<parts[0];
            }

            else
            {
                QString nameexer = parts[1];

                //Убрать \r\n у pass
                deletetask(nameexer);
            }
        }
        else if (parts[0]=="uptdes"){
            //Разделить почту, имя, пароль
            if (parts.count()!=4){
                qDebug()<<"Unvalid data for "<<parts[0];
            }

            else
            {
                QString name = parts[1];
                QString nameexer = parts[2];
                QString des = parts[3];


                //Убрать \r\n у pass
                updatedes(name, nameexer,des);
        }
        }
        else if (parts[0]=="uptans") {
                //Разделить почту, имя, пароль
                if (parts.count()!=4){
                    qDebug()<<"Unvalid data for "<<parts[0];
                }

                else
                {
                    QString name = parts[1];
                    QString nameexer = parts[2];
                    QString ans = parts[3];


                    //Убрать \r\n у pass
                    updateans(name, nameexer,ans);
            }
        }
        else if (parts[0]=="chkres") {
            //Разделить почту, имя, пароль
            if (parts.count()!=4) {
                qDebug()<<"Unvalid data for "<<parts[0];
                }

            else
            {
                QString taskname = parts[1];
                QString answer = parts[2];
                QString username = parts[3];
                //Убрать \r\n у pass
                CheckResult(taskname,answer,username);
            }
        }
        else{
            qDebug()<< "Invalid func name";
        }
    }

