#ifndef FUNCS_FOR_SERVER_H
#define FUNCS_FOR_SERVER_H
#include <QObject>
#include "mytcpserver.h"
void Parsing(QByteArray message);
void Login(const QString& username,const QString& password);//log + pass
void Registration(const QString& email,const QString& username,const QString& role, const QString& password,const QString& verifypass);
void CheckResult(const QString& taskname, const QString& answer, const QString &username); //task + input+ + answer
void Statistic_stud(QString& name);
void Statistic_teach();
void gettask(const QString& name);
void settask(const QString& name,const QString& nameex,const QString& des, const QString& ans);
void updatedes(const QString& name,const QString& nameex,const QString& des);
void updateans(const QString& name,const QString& nameex,const QString& ans);
void deletetask(const QString& nameex);
void getoverstat();
#endif // FUNCS_FOR_SERVER_H
