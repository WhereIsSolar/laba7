import java.util.Scanner;

public class GoodDivisorsCalculator {
    // Константа для модуля (10^9 + 7)
    private static final long MOD = 1000000007L;

    // БЛОК 1: Функция быстрого возведения в степень
    private static long powMod(long base, long exp, long mod) {
        long result = 1;  // Инициализация результата
        base %= mod;      // Защита от переполнения
        
        // Алгоритм быстрого возведения в степень
        while (exp > 0) {
            // Если степень нечетная
            if ((exp & 1) == 1) {
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
    private static int maxGoodDivisors(int primeFactors) {
        // Базовые случаи для малых значений
        if (primeFactors <= 4) {
            return primeFactors;
        }
        
        // Определяем остаток от деления на 3
        int r = primeFactors % 3;
        long ans;
        long k;
        
        // Оптимальное разбиение в зависимости от остатка
        if (r == 0) {
            // Случай: делится на 3 (3^k)
            k = primeFactors / 3;
            ans = powMod(3, k, MOD);
        } else if (r == 1) {
            // Случай: остаток 1 (4*3^(k-1))
            k = (primeFactors - 4) / 3;
            ans = (4 * powMod(3, k, MOD)) % MOD;
        } else {
            // Случай: остаток 2 (2*3^k)
            k = (primeFactors - 2) / 3;
            ans = (2 * powMod(3, k, MOD)) % MOD;
        }
        
        return (int) ans;
    }

    // БЛОК 3: Тестирование и вывод результатов
    public static void main(String[] args) {
        // Тестовые случаи из условия задачи
        System.out.println("Input: 5\tOutput: " + maxGoodDivisors(5));
        System.out.println("Input: 8\tOutput: " + maxGoodDivisors(8));
        
        // Дополнительные тестовые случаи
        System.out.println("Input: 1\tOutput: " + maxGoodDivisors(1));
        System.out.println("Input: 2\tOutput: " + maxGoodDivisors(2));
        System.out.println("Input: 3\tOutput: " + maxGoodDivisors(3));
        System.out.println("Input: 4\tOutput: " + maxGoodDivisors(4));
        System.out.println("Input: 6\tOutput: " + maxGoodDivisors(6));
        System.out.println("Input: 10\tOutput: " + maxGoodDivisors(10));

        Scanner scanner = new Scanner(System.in);
        while (true) {
            int a = scanner.nextInt();
            System.out.println("Input: " + a + "\tOutput: " + maxGoodDivisors(a));
        }
    }
}
