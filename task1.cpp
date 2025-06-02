import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the number of levels: ");
        int levels = scanner.nextInt();
        System.out.println("Cantor set construction for " + levels + " levels:");
        cantorSet(levels, levels);
        System.out.println("Construction completed.");
    }

    public static void cantorSet(int level, int maxLevels) {
        if (level == 0) return;
        
        int segmentLength = (int) Math.pow(3, level - 1);
        int numSegments = 1 << (maxLevels - level);  // Эквивалент 2^(maxLevels-level)
        
        // Добавление отступов для визуализации
        for (int i = 0; i < maxLevels - level; i++) {
            System.out.print("  ");
        }
        
        // Рисование сегментов Кантора
        for (int s = 0; s < numSegments; s++) {
            for (int i = 0; i < segmentLength; i++) {
                System.out.print("-");
            }
            if (s < numSegments - 1) {
                for (int i = 0; i < segmentLength; i++) {
                    System.out.print(" ");
                }
            }
        }
        System.out.println();
        
        // Рекурсивный вызов для следующего уровня
        cantorSet(level - 1, maxLevels);
    }
}


