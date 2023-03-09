#ifndef FUNCS_FOR_SERVER_H
#define FUNCS_FOR_SERVER_H
#include <QObject>


void Parsing(QByteArray message);
void Login(QString username, QString password);//log + pass
void Registration(QString email,QString username, QString password);
void CheckResult(); //task + input+ + answer
void Statistic_stud();
void Statistic_teach();
#endif // FUNCS_FOR_SERVER_H
