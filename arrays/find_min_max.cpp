#include <iostream>
#include <vector>
using namespace std;

int main() {
    // INSTRUCTION: Enter array size, then elements to find max and min
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
    
    // Поиск максимума и минимума
    int maxVal = arr[0], minVal = arr[0];
    for(int i = 1; i < n; i++) {
        if(arr[i] > maxVal)
            maxVal = arr[i];
        if(arr[i] < minVal)
            minVal = arr[i];
    }
    
    cout << "Maximum: " << maxVal << endl;
    cout << "Minimum: " << minVal << endl;
    
    return 0;
}