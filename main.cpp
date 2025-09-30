#include <iostream>
#include <vector>
#include <cassert>
#include "Graph.h"  // Предполагаем, что твой класс в Graph.h

using namespace std;

void testBasicOperations() {
    cout << "=== Тест базовых операций ===" << endl;
    Graph g;

    // Добавление вершин
    g.addVertex(10);
    g.addVertex(20);
    g.addVertex(30);
    g.addVertex(40);
    g.addVertex(50);

    assert(g.getVertexCount() == 5);
    cout << "✓ Добавление вершин работает" << endl;

    // Проверка получения вершин
    Vertex v = g.getVertexById(2);
    assert(v.getValue() == 30);
    assert(v.getId() == 2);
    cout << "✓ Получение вершины по ID работает" << endl;

    // Добавление рёбер
    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);

    assert(g.getEdgeCount() == 4);
    cout << "✓ Добавление рёбер работает" << endl;
}

void testBFS() {
    cout << "\n=== Тест BFS ===" << endl;
    Graph g;

    // Строим граф: 0-1-2
    //             |   |
    //             4   3
    g.addVertex(10); // 0
    g.addVertex(20); // 1
    g.addVertex(30); // 2
    g.addVertex(40); // 3
    g.addVertex(50); // 4

    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);

    // BFS из вершины 2
    vector<int> bfs = g.BFS(2);

    // Проверяем порядок обхода
    assert(bfs.size() == 5);
    assert(bfs[0] == 30); // 2
    assert(bfs[1] == 20); // 1
    assert(bfs[2] == 10); // 0
    assert(bfs[3] == 40); // 3
    assert(bfs[4] == 50); // 4

    cout << "✓ BFS обход в правильном порядке: ";
    for (int val : bfs) cout << val << " ";
    cout << endl;
}

void testShortestPath() {
    cout << "\n=== Тест кратчайшего пути ===" << endl;
    Graph g;

    // Строим граф: 0-1-2
    //             |   |
    //             4   3
    g.addVertex(10); // 0
    g.addVertex(20); // 1
    g.addVertex(30); // 2
    g.addVertex(40); // 3
    g.addVertex(50); // 4

    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);

    // Путь из 2 в 4
    vector<int> path = g.shortestPath(2, 4);

    assert(path.size() == 4);
    assert(path[0] == 30); // 2
    assert(path[1] == 20); // 1  
    assert(path[2] == 10); // 0
    assert(path[3] == 50); // 4

    cout << "✓ Кратчайший путь найден: ";
    for (int val : path) cout << val << " ";
    cout << endl;

    // Тест когда путь не существует
    Graph disconnected;
    disconnected.addVertex(10);
    disconnected.addVertex(20);
    // Нет рёбер - граф несвязный

    vector<int> noPath = disconnected.shortestPath(0, 1);
    assert(noPath.empty());
    cout << "✓ Обработка отсутствия пути работает" << endl;
}

void testSearchByValue() {
    cout << "\n=== Тест поиска по значению ===" << endl;
    Graph g;

    g.addVertex(10);
    g.addVertex(20);
    g.addVertex(10); // Дубликат значения
    g.addVertex(30);
    g.addVertex(10); // Ещё один дубликат

    vector<Vertex> found = g.getVertexByValue(10);
    assert(found.size() == 3);

    cout << "✓ Найдено вершин со значением 10: " << found.size() << endl;
    cout << "  Их ID: ";
    for (const auto& v : found) {
        cout << v.getId() << " ";
    }
    cout << endl;
}

void testErrorHandling() {
    cout << "\n=== Тест обработки ошибок ===" << endl;
    Graph g;
    g.addVertex(10);
    g.addVertex(20);

    try {
        g.addEdge(0, 5); // Несуществующая вершина
        assert(false); // Не должны сюда попасть
    }
    catch (const out_of_range& e) {
        cout << "✓ Правильно обработана ошибка добавления ребра: " << e.what() << endl;
    }

    try {
        g.getVertexById(10); // Несуществующий ID
        assert(false);
    }
    catch (const out_of_range& e) {
        cout << "✓ Правильно обработана ошибка получения вершины: " << e.what() << endl;
    }

    try {
        g.BFS(10); // Несуществующий старт
        assert(false);
    }
    catch (const out_of_range& e) {
        cout << "✓ Правильно обработана ошибка BFS: " << e.what() << endl;
    }
}

void testMatrixAndEdgeCount() {
    cout << "\n=== Тест матрицы и подсчёта рёбер ===" << endl;
    Graph g;

    g.addVertex(10);
    g.addVertex(20);
    g.addVertex(30);

    g.addEdge(0, 1);
    g.addEdge(1, 2);

    assert(g.getEdgeCount() == 2);
    cout << "✓ Количество рёбер: " << g.getEdgeCount() << endl;

    auto matrix = g.getMatrix();
    assert(matrix.size() == 3);
    assert(matrix[0][1] == 1 && matrix[1][0] == 1); // Ребро 0-1
    assert(matrix[1][2] == 1 && matrix[2][1] == 1); // Ребро 1-2
    assert(matrix[0][2] == 0 && matrix[2][0] == 0); // Нет ребра 0-2

    cout << "✓ Матрица смежности корректна" << endl;
}

void testSameStartTarget() {
    cout << "\n=== Тест одинаковых start/target ===" << endl;
    Graph g;
    g.addVertex(10);
    g.addVertex(20);
    g.addEdge(0, 1);

    vector<int> path = g.shortestPath(0, 0);
    assert(path.size() == 1);
    assert(path[0] == 10);
    cout << "✓ Путь из вершины в саму себя работает" << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "Запуск тестов для класса Graph\n" << endl;

    try {
        testBasicOperations();
        testBFS();
        testShortestPath();
        testSearchByValue();
        testErrorHandling();
        testMatrixAndEdgeCount();
        testSameStartTarget();

        cout << "\nВсе тесты пройдены успешно!" << endl;
        cout << "Твой Graph класс готов к использованию!" << endl;

    }
    catch (const exception& e) {
        cout << "\nТест упал с ошибкой: " << e.what() << endl;
        return 1;
    }

    return 0;

    return 0;
}