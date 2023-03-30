#include <QCoreApplication>
#include "mytcpserver.h"
#include "database.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyTcpServer server;

    return a.exec();
}
