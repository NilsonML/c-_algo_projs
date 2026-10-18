#include <iostream>
#include <vector>
using namespace std;

int main() {
    // INSTRUCTION: Enter array size, then elements to reverse
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
    
    // Реверс массива
    for(int i = 0; i < n / 2; i++) {
        int temp = arr[i];
        arr[i] = arr[n - 1 - i];
        arr[n - 1 - i] = temp;
    }
    
    cout << "Reversed array: ";
    for(int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    return 0;
}