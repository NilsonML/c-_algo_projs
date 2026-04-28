#include <iostream>
#include <cmath>
using namespace std;

// Оптимизированная проверка на простоту
bool isPrime(int n) {
    if(n <= 1) return false;
    if(n <= 3) return true;
    if(n % 2 == 0 || n % 3 == 0) return false;
    
    for(int i = 5; i * i <= n; i += 6) {
        if(n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

// Решето Эратосфена для нахождения всех простых чисел до n
void sieveOfEratosthenes(int n) {
    bool prime[n + 1];
    for(int i = 0; i <= n; i++)
        prime[i] = true;
    
    prime[0] = prime[1] = false;
    
    for(int p = 2; p * p <= n; p++) {
        if(prime[p] == true) {
            for(int i = p * p; i <= n; i += p)
                prime[i] = false;
        }
    }
    
    cout << "Prime numbers up to " << n << ": ";
    for(int p = 2; p <= n; p++) {
        if(prime[p])
            cout << p << " ";
    }
    cout << endl;
}

int main() {
    // INSTRUCTION: Enter a number to check primality and get all primes up to that number
    cout << "Enter a number: ";
    int num;
    cin >> num;
    
    // Проверка одного числа
    if(isPrime(num))
        cout << num << " is prime" << endl;
    else
        cout << num << " is not prime" << endl;
    
    // Вывод всех простых чисел до num
    if(num >= 2)
        sieveOfEratosthenes(num);
    
    return 0;
}