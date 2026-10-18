#include <iostream>
using namespace std;

// Рекурсивный алгоритм Евклида
int gcd(int a, int b) {
    if(b == 0)
        return a;
    return gcd(b, a % b);
}

// Вычисление НОК через НОД
long long lcm(int a, int b) {
    if (a == 0 || b == 0) return 0;          // gcd(0, 0) = 0 -> было деление на ноль
    return (long long)(a / gcd(a, b)) * b;   // long long: НОК легко выходит за пределы int
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
    long long resultLCM = lcm(num1, num2);
    
    cout << "GCD: " << resultGCD << endl;
    cout << "LCM: " << resultLCM << endl;
    
    return 0;
}