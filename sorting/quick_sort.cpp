#include <iostream>
#include <vector>
using namespace std;

// Функция разделения массива (схема Ломуто)
int partition(vector<int>& arr, int low, int high) {
    // Опорный — средний элемент (переставляем его в конец). С последним
    // элементом в роли опорного уже отсортированный массив даёт O(n^2)
    // и рекурсию глубины n — на больших входах это переполнение стека.
    int mid = low + (high - low) / 2;
    swap(arr[mid], arr[high]);
    int pivot = arr[high];
    int i = low - 1;
    
    for(int j = low; j < high; j++) {
        if(arr[j] <= pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    
    return i + 1;
}

// Рекурсивная быстрая сортировка
void quickSort(vector<int>& arr, int low, int high) {
    if(low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    // INSTRUCTION: Enter array size, then elements to sort using Quick Sort
    cout << "Enter size of array: ";
    int n;
    cin >> n;
    if (!cin || n <= 0) {
        cerr << "Size must be a positive integer" << endl;
        return 1;
    }
    
    // std::vector вместо int arr[n]: массивы переменной длины (VLA) — расширение
    // GCC, их нет в стандарте C++ и MSVC (cl.exe) их не компилирует
    vector<int> arr(n);
    cout << "Enter " << n << " elements: ";
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    quickSort(arr, 0, n - 1);
    
    cout << "Sorted array: ";
    for(int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    return 0;
}