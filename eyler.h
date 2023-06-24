#ifndef EYLER_H
#define EYLER_H

#include <QVector>
#include <QString>
class Graph {
public:
    Graph(int n);
    void addEdge(int u, int v);
    bool isEulerian();
    void eulerianCycle(int start, QVector<int>& cycle);
private:
    int n;
    QVector<QVector<int>> adj;
    QVector<int> degree;
};
QString realize();
#endif // EYLER_H
