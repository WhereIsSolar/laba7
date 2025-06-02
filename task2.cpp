#include <iostream>
#include <cmath>
using namespace std;

// Константа для модуля (10^9 + 7)
const long long MOD = 1000000007;

// БЛОК 1: Функция быстрого возведения в степень
long long powMod(long long base, long long exp, long long mod) {
    long long result = 1;  // Инициализация результата
    base %= mod;           // Защита от переполнения
    
    // Алгоритм быстрого возведения в степень
    while (exp > 0) {
        // Если степень нечетная
        if (exp & 1) {
            result = (result * base) % mod;
        }
        // Возводим base в квадрат
        base = (base * base) % mod;
        // Делим степень пополам
        exp >>= 1;
    }
    return result;
}

// БЛОК 2: Основная логика вычислений
int maxGoodDivisors(int primeFactors) {
    // Базовые случаи для малых значений
    if (primeFactors <= 4) {
        return primeFactors;
    }
    
    // Определяем остаток от деления на 3
    int r = primeFactors % 3;
    long long ans = 0;
    long long k = 0;
    
    // Оптимальное разбиение в зависимости от остатка
    if (r == 0) {
        // Случай: делится на 3 (3^k)
        k = primeFactors / 3;
        ans = powMod(3, k, MOD);
    } else if (r == 1) {
        // Случай: остаток 1 (4*3^(k-1))
        k = (primeFactors - 4) / 3;
        ans = (4LL * powMod(3, k, MOD)) % MOD;
    } else {
        // Случай: остаток 2 (2*3^k)
        k = (primeFactors - 2) / 3;
        ans = (2LL * powMod(3, k, MOD)) % MOD;
    }
    
    return static_cast<int>(ans);
}

// БЛОК 3: Тестирование и вывод результатов
int main() {
    // Тестовые случаи из условия задачи
    cout << "Input: 5\tOutput: " << maxGoodDivisors(5) << endl;
    cout << "Input: 8\tOutput: " << maxGoodDivisors(8) << endl;
    
    // Дополнительные тестовые случаи
    cout << "Input: 1\tOutput: " << maxGoodDivisors(1) << endl;
    cout << "Input: 2\tOutput: " << maxGoodDivisors(2) << endl;
    cout << "Input: 3\tOutput: " << maxGoodDivisors(3) << endl;
    cout << "Input: 4\tOutput: " << maxGoodDivisors(4) << endl;
    cout << "Input: 6\tOutput: " << maxGoodDivisors(6) << endl;
    cout << "Input: 10\tOutput: " << maxGoodDivisors(10) << endl;

    int a;
    while (true){
        cin >> a;
        cout << "Input: " << a << "\tOutput: " << maxGoodDivisors(a) << endl;}
    
    return 0;
}
