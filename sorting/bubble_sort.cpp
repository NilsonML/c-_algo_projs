#include <iostream>
#include <vector>
using namespace std;

int main() {
    // INSTRUCTION: Enter array size, then elements to sort in ascending order
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
    
    // Пузырьковая сортировка
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(arr[j] > arr[j+1]) {
                // Обмен значений
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    
    cout << "Sorted array: ";
    for(int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    return 0;
}   