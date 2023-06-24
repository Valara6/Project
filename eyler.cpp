#include "eyler.h"

Graph::Graph(int n) {
    this->n = n;
    adj.resize(n);
    degree.resize(n);
}
void Graph::addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
    degree[u]++;
    degree[v]++;
}
bool Graph::isEulerian() {
    for (int i = 0; i < n; i++) {
        if (degree[i] % 2 != 0) {
            return false;
        }
    }
    QVector<bool> visited(n, false);
    int start = 0;
    for (int i = 0; i < n; i++) {
        if (degree[i] > 0) {
            start = i;
            break;
        }
    }
    QQueue<int> q;
    q.push_back(start);
    while (!q.empty()) {
        int u = q.front();
        q.pop_front();
        visited[u] = true;
        for (int v : adj[u]) {
            if (!visited[v]) {
                q.push_back(v);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (!visited[i] && degree[i] > 0) {
            return false;
        }
    }
    return true;
}
void Graph::eulerianCycle(int start, QVector<int>& cycle) {
    while (!adj[start].empty()) {
        int v = adj[start].back();
        adj[start].pop_back();
        for (int i = 0; i < adj[v].size(); i++) {
            if (adj[v][i] == start) {
                adj[v].erase(adj[v].begin() + i);
                break;
            }
        }
        eulerianCycle(v, cycle);
    }
    cycle.push_back(start);
}
QString Graph(int& vertices,int edges,){}
