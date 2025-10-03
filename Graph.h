#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

// todo
// - tamplate for Vertex value
// - DFS
template<typename T>
class Vertex {
private:
	T value;
	int id;

public:
	Vertex(T _value, int _id) : value(_value), id(_id){	}

	int getId() const { return id; }
	T getValue() const { return value; }
};

template<typename VertexType>
class Graph{
private:

	vector<Vertex<VertexType>> vertexes;
	vector<vector<int>> ad_list;
	vector<vector<int>> ad_matrix;

public:
	Graph() {	}

	// добавление узлов и ребер

	void addVertex(VertexType _value) {
		int new_id = vertexes.size();
		vertexes.push_back(Vertex(_value, new_id));
		
		expandStructures(1);
	}

	void addVertex(const vector<VertexType>& _vertex_values) {
		for (VertexType vertex_value : _vertex_values) {
			int new_id = vertexes.size();
			vertexes.emplace_back(vertex_value, new_id);
		}
		expandStructures(_vertex_values.size());
	}

	void addEdge(int _first_id, int _second_id) {
		if (!validId(_first_id)) throw out_of_range("Первый id вне диапазона");
		if (!validId(_second_id)) throw out_of_range("Второй id вне диапазона");
		if (std::ranges::find(ad_list[_first_id], _second_id) != ad_list[_first_id].end() || std::ranges::find(ad_list[_second_id], _first_id) != ad_list[_second_id].end()) {
			throw invalid_argument("Ребро уже существует");
		}

		ad_list[_first_id].push_back(_second_id);
		ad_list[_second_id].push_back(_first_id);

		ad_matrix[_first_id][_second_id] = 1;
		ad_matrix[_second_id][_first_id] = 1;

		cout << "Добавлено ребро: " << _first_id << " -- " << _second_id << endl;
	}

	// getters
	Vertex<VertexType> getVertexById(int _target_id) const {
		if (validId(_target_id)) {
			return vertexes[_target_id];
		}
		throw out_of_range("Узла с id: " + to_string(_target_id)+" не существует");
	}
	
	vector<Vertex<VertexType>> getVertexByValue(const VertexType& _target_value) const {
		vector<Vertex<VertexType>> found;

		for (int i = 0; i < vertexes.size(); i++) {
			if (vertexes[i].getValue() == _target_value) {
				found.push_back(vertexes[i]);
			}
		}
		return found;
	}

	int getVertexCount() const {
		return vertexes.size();
	}

	int getEdgeCount() const {
		int count = 0;
		for (const auto& row : ad_matrix) {
			for (auto val : row) {
				count += val;
			}
		}
		return count / 2;
	}

	vector<vector<int>> getMatrix() const {
		return ad_matrix;
	}

	// BFS/DFS
	vector<int> BFS(int _start_id) const {
		if (!validId(_start_id)) throw out_of_range("start id is out of range");

		vector<int> traversal_order;
		vector<bool> visited(vertexes.size(), false);
		queue<int> q;

		visited[_start_id] = true;
		q.push(_start_id);

		while (!q.empty()) {
			int current = q.front();
			q.pop();
			traversal_order.push_back(current);

			// add all unvisited neighbors
			for (int neighbor : ad_list[current]) {
				if (!visited[neighbor]) {
					visited[neighbor] = true;
					q.push(neighbor);
				}
			}

		}
		return traversal_order;
	}

	vector<int> shortestPath(int _start_id, int _target_id) const {
		if (!validId(_start_id))throw out_of_range("start id is out of range");
		if (!validId(_target_id)) throw out_of_range("target id is out of range");
		if (_start_id == _target_id) return vector<int>{_start_id};

		vector<int> parent(vertexes.size(), -1);
		vector<bool> visited(vertexes.size(), false);
		queue<int> q;
		bool found = false;

		visited[_start_id] = true;
		q.push(_start_id);

		while (!q.empty() && !found) {
			int current = q.front();
			q.pop();

			for (int neighbor : ad_list[current]) {
				if (!visited[neighbor]) {
					visited[neighbor] = true;
					parent[neighbor] = current;
					q.push(neighbor);

					if (neighbor == _target_id) {
						found = true;
						break;
					}
				}
			}
		}
		if (!found) return vector<int>();

		vector<int> path;
		for (int at = _target_id; at > -1; at = parent[at]) {
			path.push_back(at);
		}
		reverse(path.begin(), path.end());

		return path;
	}
//private methods
private:
	/*void expandMatrix() {
		int new_size = vertexes.size();

		for (auto& row : ad_matrix) {
			row.push_back(0);
		}
		ad_matrix.push_back(vector<int>(new_size, 0));
	}	
	void expandList() {
		ad_list.push_back(vector<int>());
	}*/

	void expandStructures(size_t count) {
		size_t new_size = vertexes.size();
		//расширение матрицы
		for (auto& row : ad_matrix) { // Расширение строк
			row.resize(new_size, 0);
		}

		for (size_t i = 0; i < count; i++) { // Расширение столбцов
			ad_matrix.emplace_back(new_size, 0);
		}
		//расширение листа
		ad_list.resize(new_size);

	};

	bool validId(int _id) const {
		return _id >= 0 && _id < vertexes.size();
	}
};

