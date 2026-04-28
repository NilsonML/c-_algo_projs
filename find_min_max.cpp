#include <iostream>
using namespace std;

int main() {
    // INSTRUCTION: Enter array size, then elements to find max and min
    cout << "Enter size of array: ";
    int n;
    cin >> n;
    
    int arr[n];
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