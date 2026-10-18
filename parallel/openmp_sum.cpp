#include <iostream>
#include <vector>
#include <omp.h>  // Библиотека OpenMP для параллельных вычислений
using namespace std;

int main() {
    // INSTRUCTION: Enter array size, then elements. Program will sum them using multiple CPU cores
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
    
    int sum = 0;
    
    // Параллельное выполнение цикла с распределением итераций между потоками
    // reduction - безопасное суммирование результатов из разных потоков
    #pragma omp parallel for reduction(+:sum)
    for(int i = 0; i < n; i++) {
        sum += arr[i];
    }
    
    // Получение количества используемых потоков (только в параллельной области)
    int threads_used = 0;
    #pragma omp parallel
    {
        #pragma omp single
        threads_used = omp_get_num_threads();
    }
    
    cout << "Sum: " << sum << endl;
    cout << "Threads used: " << threads_used << endl;
    
    return 0;
}