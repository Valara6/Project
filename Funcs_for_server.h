#ifndef FUNCS_FOR_SERVER_H
#define FUNCS_FOR_SERVER_H
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include <QtNetwork>
#include <QByteArray>
#include <QDebug>

#include <QVector>

void Parsing(QByteArray message);
void Login(QString username, QString password);
void Registration(QString email,QString username, QString password);

#endif // FUNCS_FOR_SERVER_H
