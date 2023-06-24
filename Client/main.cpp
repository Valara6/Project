#include <QApplication>
#include "mainwindow.h"
#include "second.h"
#include "teachermod.h"
#include "QStyleFactory"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //https://github.com/TheAlgorithms/C-Plus-Plus/blob/master/graph/travelling_salesman_problem.cpp
    MainWindow* window = MainWindow::instance();
    window->show();

    return a.exec();
}
