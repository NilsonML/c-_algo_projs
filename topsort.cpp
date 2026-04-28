#include <iostream>
#include <list>
#include <queue>
#include <vector>
#include <sstream>

using namespace std;

// Структура вершины с иерархическим списком потомков
struct Node {
    int key;                    // Номер вершины
    int counter;                // Количество входящих рёбер
    list<Node*> children;       // Иерархический список потомков
    
    Node(int k) : key(k), counter(0) {}
};

class Graph {
private:
    list<Node*> vertices;       // Иерархический список всех вершин
    
    Node* findVertex(int key) {
        for (Node* v : vertices) {
            if (v->key == key) return v;
        }
        return nullptr;
    }
    
public:
    void addVertex(int key) {
        if (!findVertex(key)) {
            vertices.push_back(new Node(key));
        }
    }
    
    void addEdge(int from, int to) {
        Node* fromNode = findVertex(from);
        Node* toNode = findVertex(to);
        if (fromNode && toNode) {
            fromNode->children.push_back(toNode);
            toNode->counter++;
        }
    }
    
    void updateCounters() {
        for (Node* v : vertices) v->counter = 0;
        for (Node* u : vertices) {
            for (Node* v : u->children) {
                v->counter++;
            }
        }
    }
    
    // ТОПОЛОГИЧЕСКАЯ СОРТИРОВКА (только алгоритм Кана)
    bool topologicalSort(vector<int>& result) {
        result.clear();
        updateCounters();
        
        queue<Node*> q;
        for (Node* v : vertices) {
            if (v->counter == 0) q.push(v);
        }
        
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            result.push_back(current->key);
            
            for (Node* child : current->children) {
                child->counter--;
                if (child->counter == 0) {
                    q.push(child);
                }
            }
        }
        
        return result.size() == vertices.size();
    }
    
    void print() {
        for (Node* v : vertices) {
            cout << v->key << " (вх=" << v->counter << ") -> { ";
            for (Node* child : v->children) cout << child->key << " ";
            cout << "}\n";
        }
    }
    
    size_t getVertexCount() { return vertices.size(); }
    
    ~Graph() {
        for (Node* v : vertices) delete v;
    }
};

void clearInput() {
    cin.clear();
    cin.ignore(10000, '\n');
}

void inputVertices(Graph& g) {
    string input;
    cout << "Введите вершины через пробел: ";
    getline(cin, input);
    stringstream ss(input);
    int v;
    while (ss >> v) g.addVertex(v);
}

void inputEdges(Graph& g) {
    string input;
    int from, to;
    cout << "Введите рёбра (from to), пустая строка для конца:\n";
    while (true) {
        cout << "Ребро: ";
        getline(cin, input);
        if (input.empty()) break;
        stringstream ss(input);
        ss >> from >> to;
        if (from == 0 && to == 0) break;
        g.addEdge(from, to);
    }
}

int main() {
    Graph g;
    bool running = true;
    
    while (running) {
        cout << "\n1.Ввести граф 2.Сортировка 3.Вывести 0.Выход\nВыбор: ";
        
        int choice;
        cin >> choice;
        clearInput();
        
        switch (choice) {
            case 1: {
                g = Graph();  // Создаём новый граф (старый удалится автоматически)
                inputVertices(g);
                if (g.getVertexCount() > 0) {
                    inputEdges(g);
                    g.updateCounters();
                }
                break;
            }
            case 2: {
                if (g.getVertexCount() == 0) {
                    cout << "Граф пуст!\n";
                    break;
                }
                vector<int> result;
                if (g.topologicalSort(result)) {
                    cout << "Порядок: ";
                    for (int x : result) cout << x << " ";
                    cout << endl;
                } else {
                    cout << "Граф содержит цикл!\n";
                }
                break;
            }
            case 3: {
                if (g.getVertexCount() == 0) {
                    cout << "Граф пуст!\n";
                } else {
                    g.print();
                }
                break;
            }
            case 0: {
                running = false;
                break;
            }
        }
    }
    return 0;
}