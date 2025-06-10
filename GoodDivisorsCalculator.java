import java.util.Scanner;

public class GoodDivisorsCalculator{
    // Константа для модуля (10^9 + 7)
    private static final long MOD = 1000000007;

    // Возведение в степень по модулю
    private static long powMod(long base, long exp, long mod) {
        long result = 1;  // Инициализация результата
        base %= mod;      // Защита от переполнения
        
        // Алгоритм быстрого возведения в степень
        while (exp > 0) {
            if ((exp & 1) == 1) {
                result = (result * base) % mod;
            }
            base = (base * base) % mod;
            exp >>= 1;
        }
        return result;
    }

    // Рекурсивная функция
    private static long maxGoodDivisorsRecursive(int primeFactors) {
        // Базовые случаи
        if (primeFactors <= 0) return 0;
        if (primeFactors == 1) return 1;
        if (primeFactors == 2) return 2;
        if (primeFactors == 3) return 3;
        if (primeFactors == 4) return 4;

        long ans = 0;
        // Пробуем разбить на группу из 2 множителей
        if (primeFactors >= 2) {
            long current = (2L * maxGoodDivisorsRecursive(primeFactors - 2)) % MOD;
            ans = Math.max(ans, current);
        }
        // Пробуем разбить на группу из 3 множителей
        if (primeFactors >= 3) {
            long current = (3L * maxGoodDivisorsRecursive(primeFactors - 3)) % MOD;
            ans = Math.max(ans, current);
        }
        // Пробуем разбить на группу из 4 множителей
        if (primeFactors >= 4) {
            long current = (4L * maxGoodDivisorsRecursive(primeFactors - 4)) % MOD;
            ans = Math.max(ans, current);
        }
        return ans;
    }

    // Обёртка для приведения типа
    private static int maxGoodDivisors(int primeFactors) {
        return (int) maxGoodDivisorsRecursive(primeFactors);
    }

    public static void main(String[] args) {
        // Тестовые случаи
        System.out.println("Input: 5\tOutput: " + maxGoodDivisors(5));
        System.out.println("Input: 8\tOutput: " + maxGoodDivisors(8));
        System.out.println("Input: 1\tOutput: " + maxGoodDivisors(1));
        System.out.println("Input: 2\tOutput: " + maxGoodDivisors(2));
        System.out.println("Input: 3\tOutput: " + maxGoodDivisors(3));
        System.out.println("Input: 4\tOutput: " + maxGoodDivisors(4));
        System.out.println("Input: 6\tOutput: " + maxGoodDivisors(6));
        System.out.println("Input: 10\tOutput: " + maxGoodDivisors(10));

        // Ввод с клавиатуры
        Scanner scanner = new Scanner(System.in);
        while (scanner.hasNextInt()) {
            int a = scanner.nextInt();
            System.out.println("Input: " + a + "\tOutput: " + maxGoodDivisors(a));
        }
        scanner.close();
    }
}
