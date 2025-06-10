#include <iostream>
using namespace std;

// Константа для модуля (10^9 + 7)
const long long MOD = 1000000007;

// Возведение в степень по модулю
long long powMod(long long base, long long exp, long long mod) {
    long long result = 1;  // Инициализация результата
    base %= mod;           // Защита от переполнения
    
    // Алгоритм быстрого возведения в степень
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

// Рекурсивная функция
long long maxGoodDivisorsRecursive(int primeFactors) {
    // Базовые случаи
    if (primeFactors <= 0) { return 0; }
    if (primeFactors == 1) { return 1; }
    if (primeFactors == 2) { return 2; }
    if (primeFactors == 3) { return 3; }
    if (primeFactors == 4) { return 4; }

    long long ans = 0;
    // Пробуем разбить на группу из 2 множителей (делитель 2)
    if (primeFactors >= 2) {
        long long current = (2LL * maxGoodDivisorsRecursive(primeFactors - 2)) % MOD;
        ans = max(ans, current);
    }
    // Пробуем разбить на группу из 3 множителей (делитель 3)
    if (primeFactors >= 3) {
        long long current = (3LL * maxGoodDivisorsRecursive(primeFactors - 3)) % MOD;
        ans = max(ans, current);
    }
    // Пробуем разбить на группу из 4 множителей (делитель 4)
    if (primeFactors >= 4) {
        long long current = (4LL * maxGoodDivisorsRecursive(primeFactors - 4)) % MOD;
        ans = max(ans, current);
    }

    return ans;
}

// Обёртка
int maxGoodDivisors(int primeFactors) {
    return static_cast<int>(maxGoodDivisorsRecursive(primeFactors));
}


//Лучше вводить английские слова
int main() {
    // Тестовые случаи из условия
    cout << "Input: 5\tOutput: " << maxGoodDivisors(5) << endl;
    cout << "Input: 8\tOutput: " << maxGoodDivisors(8) << endl;
    
    // Дополнительные тестовые случаи
    cout << "Input: 1\tOutput: " << maxGoodDivisors(1) << endl;
    cout << "Input: 2\tOutput: " << maxGoodDivisors(2) << endl;
    cout << "Input: 3\tOutput: " << maxGoodDivisors(3) << endl;
    cout << "Input: 4\tOutput: " << maxGoodDivisors(4) << endl;
    cout << "Input: 6\tOutput: " << maxGoodDivisors(6) << endl;
    cout << "Input: 10\tOutput: " << maxGoodDivisors(10) << endl;

    // Ввод с клавиатуры
    int a;
    while (cin >> a) {
        cout << "Input: " << a << "\tOutput: " << maxGoodDivisors(a) << endl;
    }
    
    return 0;
}
