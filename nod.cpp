#include <iostream>
using namespace std;

// Рекурсивный алгоритм Евклида
int gcd(int a, int b) {
    if(b == 0)
        return a;
    return gcd(b, a % b);
}

// Вычисление НОК через НОД
int lcm(int a, int b) {
    return (a / gcd(a, b)) * b;
}

int main() {
    // INSTRUCTION: Enter two positive integers to find GCD and LCM
    cout << "Enter first number: ";
    int num1, num2;
    cin >> num1;
    
    cout << "Enter second number: ";
    cin >> num2;
    
    // Проверка на отрицательные числа
    if(num1 < 0) num1 = -num1;
    if(num2 < 0) num2 = -num2;
    
    int resultGCD = gcd(num1, num2);
    int resultLCM = lcm(num1, num2);
    
    cout << "GCD: " << resultGCD << endl;
    cout << "LCM: " << resultLCM << endl;
    
    return 0;
}