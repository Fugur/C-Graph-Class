#include <iostream>
#include <vector>
#include <cassert>
#include "Graph.h"  // Предполагаем, что твой класс в Graph.h

using namespace std;

Graph<vector<int>> basicTests() {
    Graph<vector<int>> vectors_g;

    vector<vector<int>> elem;
    for (int i = 1; i <= 10; i++) {
        vector<int> new_vert;
        for (int j = 0; j <= i; j++) {
            new_vert.emplace_back(j);
        }
        elem.emplace_back(new_vert);
    }
    vectors_g.addVertex(elem);
    return vectors_g;
}

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "Запуск тестов для класса Graph\n" << endl;
    
    cout << basicTests().getVertexCount();

}