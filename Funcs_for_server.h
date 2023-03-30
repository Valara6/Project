#ifndef FUNCS_FOR_SERVER_H
#define FUNCS_FOR_SERVER_H
#include <QObject>



void Parsing(QByteArray message);
void Login(const QString& username,const QString& password);//log + pass
void Registration(const QString& email,const QString& username,const QString& role, const QString& password,const QString& verifypass);
void CheckResult(); //task + input+ + answer
void Statistic_stud();
void Statistic_teach();
void ConnectDatabase();
#endif // FUNCS_FOR_SERVER_H
