#include <QApplication>
#include "mytcpserver.h"
#include "database.h"
#include "mainwindow.h"
#include "second.h"
#include "QStyleFactory"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MyTcpServer server;
    MainWindow* window = MainWindow::instance();
    window->show();

    return a.exec();
}
