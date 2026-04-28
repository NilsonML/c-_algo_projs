#include <iostream>
using namespace std;

int main() {
    // INSTRUCTION: Enter array size, then elements, then number to search
    cout << "Enter size of array: ";
    int n;
    cin >> n;
    
    int arr[n];
    cout << "Enter " << n << " elements: ";
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    cout << "Enter element to search: ";
    int key;
    cin >> key;
    
    // Линейный поиск
    int pos = -1;
    for(int i = 0; i < n; i++) {
        if(arr[i] == key) {
            pos = i;
            break;
        }
    }
    
    if(pos != -1)
        cout << "Found at index " << pos << endl;
    else
        cout << "Not found" << endl;
    
    return 0;
}