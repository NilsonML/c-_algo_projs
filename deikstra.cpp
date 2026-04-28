#include <iostream>
#include <vector>
#include <limits>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max();

int main() {
    // =================================================================
    // ЧАСТЬ 1: ВВОД ВЕРШИН
    // =================================================================
    cout << "Введите номера вершин (через пробел):" << endl;
    cin.ignore(); // Очищаем буфер ввода
    string line;
    getline(cin, line);          // Читаем всю строку
    stringstream ss(line);       // Превращаем строку в поток для удобного чтения
    
    vector<int> vertices;        // Список всех вершин графа
    int vertex;
    while (ss >> vertex) {       // Пока в потоке есть числа
        vertices.push_back(vertex);
    }
    
    // Находим максимальный номер вершины (нужно для размещения матрицы)
    int maxVertex = 0;
    for (int v : vertices) {
        if (v > maxVertex) maxVertex = v;
    }
    
    // СОЗДАЁМ МАТРИЦУ СТОИМОСТЕЙ
    // c[u][v] - стоимость ребра из u в v
    // Размер: (maxVertex+1) x (maxVertex+1)
    // Инициализируем всё бесконечностью (INF)
    vector<vector<int>> c(maxVertex + 1, vector<int>(maxVertex + 1, INF));
    
    // Расстояние от вершины до самой себя равно 0
    for (int v : vertices) {
        c[v][v] = 0;
    }
    
    // =================================================================
    // ЧАСТЬ 2: ВВОД РЁБЕР
    // =================================================================
    cout << "\nВведите рёбра (from to weight). 0 0 0 - конец ввода:" << endl;
    
    int from, to, weight;
    while (true) {
        cin >> from >> to >> weight;
        if (from == 0 && to == 0 && weight == 0) break;
        
        // Если встретилась новая вершина с номером больше maxVertex
        // расширяем матрицу
        int newMax = max(max(from, to), maxVertex);
        if (newMax > maxVertex) {
            c.resize(newMax + 1);
            for (int i = 0; i <= newMax; i++) {
                c[i].resize(newMax + 1, INF);
                if (i <= maxVertex) c[i][i] = 0;
            }
            maxVertex = newMax;
        }
        
        // Добавляем новые вершины в список, если их там нет
        if (find(vertices.begin(), vertices.end(), from) == vertices.end()) {
            vertices.push_back(from);
            c[from][from] = 0;
        }
        if (find(vertices.begin(), vertices.end(), to) == vertices.end()) {
            vertices.push_back(to);
            c[to][to] = 0;
        }
        
        // Запоминаем стоимость ребра
        c[from][to] = weight;
    }
    
    // =================================================================
    // ЧАСТЬ 3: ВВОД ИСТОЧНИКА
    // =================================================================
    cout << "\nВведите номер вершины-источника: ";
    int v0;
    cin >> v0;
    
    // =================================================================
    // ЧАСТЬ 4: АЛГОРИТМ ДЕЙКСТРЫ
    // =================================================================
    /*
    КЛЮЧЕВАЯ ИДЕЯ АЛГОРИТМА:
    - S - множество вершин, для которых мы УЖЕ ЗНАЕМ кратчайшее расстояние
    - D[v] - ТЕКУЩАЯ ОЦЕНКА расстояния до вершины v (может улучшаться)
    
    НА КАЖДОМ ШАГЕ:
    1. Выбираем вершину w НЕ из S с МИНИМАЛЬНЫМ D[w]
       (это вершина, до которой мы точно знаем кратчайший путь,
        потому что любой другой путь был бы длиннее)
    2. Добавляем w в S
    3. Пытаемся УЛУЧШИТЬ расстояния до всех соседей v:
       Если D[w] + вес(w→v) < D[v], то обновляем D[v]
    */
    
    vector<bool> S(maxVertex + 1, false);   // S[v] = true если вершина обработана
    vector<int> D(maxVertex + 1, INF);      // D[v] - текущее кратчайшее расстояние
    
    // ИНИЦИАЛИЗАЦИЯ (как в презентации)
    S[v0] = true;                           // Источник в S
    D[v0] = 0;                              // Расстояние до источника = 0
    
    // Для всех остальных вершин D[v] = c(v0, v) (или INF если ребра нет)
    for (int v : vertices) {
        if (v != v0) {
            D[v] = c[v0][v];
        }
    }
    
    // Список ещё не обработанных вершин
    vector<int> unvisited;
    for (int v : vertices) {
        if (v != v0) {
            unvisited.push_back(v);
        }
    }
    
    // ОСНОВНОЙ ЦИКЛ: пока есть необработанные вершины
    while (!unvisited.empty()) {
        
        // ШАГ 1: найти w с минимальным D[w] среди непосещённых
        int w = -1;
        int minD = INF;
        for (int v : unvisited) {
            if (D[v] < minD) {
                minD = D[v];
                w = v;
            }
        }
        
        // Если minD всё ещё бесконечность → остальные вершины недостижимы
        if (w == -1 || minD == INF) break;
        
        // ШАГ 2: удаляем w из списка непосещённых (добавляем в S)
        unvisited.erase(remove(unvisited.begin(), unvisited.end(), w), unvisited.end());
        
        // ШАГ 3: релаксация (ослабление) рёбер из w
        // Для каждой непосещённой вершины v пытаемся улучшить D[v]
        for (int v : unvisited) {
            // Если есть ребро w→v и D[w] не бесконечность
            if (c[w][v] != INF && D[w] != INF) {
                int newDist = D[w] + c[w][v];
                if (newDist < D[v]) {
                    D[v] = newDist;   // Нашли более короткий путь
                }
            }
        }
    }
    
    // =================================================================
    // ЧАСТЬ 5: ВЫВОД РЕЗУЛЬТАТОВ
    // =================================================================
    cout << "\nКратчайшие расстояния от вершины " << v0 << ":\n";
    for (int v : vertices) {
        if (v == v0) {
            cout << v0 << " -> " << v0 << " = 0\n";
        } else if (D[v] == INF) {
            cout << v0 << " -> " << v << " = INF\n";
        } else {
            cout << v0 << " -> " << v << " = " << D[v] << "\n";
        }
    }
    
    return 0;
}