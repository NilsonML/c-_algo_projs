#include <iostream>
#include <vector>

// Функция шейкерной сортировки (сортировка перемешиванием)
void shakerSort(std::vector<int>& arr) {
    int n = arr.size();
    bool swapped = true;
    int start = 0;
    int end = n - 1;
    
    while (swapped) {
        // Сбрасываем флаг обмена
        swapped = false;
        
        // Проход слева направо (как пузырьковая сортировка)
        for (int i = start; i < end; i++) {
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        
        // Если не было обменов, массив отсортирован
        if (!swapped) {
            break;
        }
        
        // Уменьшаем правую границу, так как последний элемент уже на месте
        end--;
        
        // Сбрасываем флаг для обратного прохода
        swapped = false;
        
        // Проход справа налево
        for (int i = end - 1; i >= start; i--) {
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        
        // Увеличиваем левую границу, так как первый элемент уже на месте
        start++;
    }
}

// Функция для вывода массива
void printArray(const std::vector<int>& arr) {
    for (size_t i = 0; i < arr.size(); i++) {
        std::cout << arr[i];
        if (i < arr.size() - 1) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
}

// Функция для демонстрации процесса сортировки с выводом каждого шага
void shakerSortWithSteps(std::vector<int>& arr) {
    int n = arr.size();
    bool swapped = true;
    int start = 0;
    int end = n - 1;
    int pass = 1;
    
    std::cout << "Начальный массив: ";
    printArray(arr);
    std::cout << std::endl;
    
    while (swapped) {
        swapped = false;
        
        std::cout << "Проход " << pass << " слева направо: ";
        
        // Проход слева направо
        for (int i = start; i < end; i++) {
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                swapped = true;
                std::cout << "(" << arr[i] << "↔" << arr[i + 1] << ") ";
            }
        }
        
        printArray(arr);
        
        if (!swapped) {
            break;
        }
        
        end--;
        swapped = false;
        
        std::cout << "Проход " << pass << " справа налево: ";
        
        // Проход справа налево
        for (int i = end - 1; i >= start; i--) {
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                swapped = true;
                std::cout << "(" << arr[i] << "↔" << arr[i + 1] << ") ";
            }
        }
        
        printArray(arr);
        std::cout << "Границы: start=" << start << ", end=" << end << std::endl;
        std::cout << std::endl;
        
        start++;
        pass++;
    }
    
    std::cout << "Сортировка завершена!" << std::endl;
}

int main() {
    // Пример 1: Основная демонстрация
    std::vector<int> arr1 = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    
    std::cout << "=== Шейкерная сортировка ===" << std::endl;
    std::cout << "Исходный массив: ";
    printArray(arr1);
    
    shakerSort(arr1);
    
    std::cout << "Отсортированный массив: ";
    printArray(arr1);
    
    std::cout << std::endl;
    
    // Пример 2: Демонстрация с пошаговым выводом
    std::vector<int> arr2 = {64, 34, 25, 12, 22, 11, 90};
    
    std::cout << "=== Пошаговая демонстрация ===" << std::endl;
    shakerSortWithSteps(arr2);
    
    std::cout << std::endl;
    
    // Пример 3: Уже отсортированный массив
    std::vector<int> arr3 = {1, 2, 3, 4, 5};
    
    std::cout << "=== Уже отсортированный массив ===" << std::endl;
    std::cout << "Исходный массив: ";
    printArray(arr3);
    
    shakerSort(arr3);
    
    std::cout << "Отсортированный массив: ";
    printArray(arr3);
    
    return 0;
}