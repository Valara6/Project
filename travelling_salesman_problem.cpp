//#include <QString>
//#include <QVector>

//typedef QVector<int> row_t;
//typedef QVector<row_t> matrix_t;

//// Поиск эйлерова цикла
//void DFS(matrix_t& graph, int edges, int start, row_t& solution)
//{
//    // Выход если рёбер не осталось
//    if (solution.size() > edges)
//        return;

//    // Добавить текущую вершину в путь
//    solution.push_back(start);

//    // Поиск непройденных рёбер
//    for (int i = 0; i < graph.size(); i++)
//    {
//        if (graph[start][i] > 0)
//        {
//            // Уменьшить количество рёбер
//            graph[start][i]--;
//            graph[i][start]--;

//            // Поиск пути
//            DFS(graph, edges, i, solution);

//            // Восстановить количество рёбер
//            graph[start][i]++;
//            graph[i][start]++;
//        }
//    }

//    // Если эйлеров цикл не найден - убрать текущую вершину из пути
//    if (solution.size() <= edges || solution.back() != solution.front())
//        solution.pop_back();
//}

//QString maint(QString& vertices, int& lines, QString& str)
//{
//    int edges = 0, start = 0;
//     QList<QString> parts = message.split(' ');
//    // Матрица смежности, хранит количество рёбер между вершинами
//    matrix_t matrix(vertices.size(), row_t(vertices.size(), 0));
//    while (lines > 0)
//    {
//        // Проверка на длину строки
//        if (str.size() < 2)
//            continue;

//        // Поиск вершин
//        int x, y;
//        x = vertices.indexOf(parts[0]);
//        y = vertices.indexOf(parts[1]);

//        // Добавление ребра если обе вершины найдены
//        if (x != -1 && y != -1)
//        {
//            matrix[x][y]++;
//            matrix[y][x]++;
//            edges++;
//            start = y;
//        }
//        lines -= 1;
//    }

//    // Проверка на наличие рёбер
//    if (edges == 0)
//    {
//        return "The graph doesn't contain any edges!";
//    }

//    // Поиск пути
//    row_t result;
//    DFS(matrix, edges, start, result);
//    QString res = "";
//    // Вывод результата
//    // ответ для теста 8162783543648
//    for (int i = 0; i < result.size(); i++)
//    {
//        res += vertices[result[i]];
//        res += " ";
//    }

//    if (result.empty())
//        return "The graph doesn't contain an Eulerian cycle.";

//    return res;
//}
