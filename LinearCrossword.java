import java.util.*;
import java.util.stream.Collectors;

public class LinearCrossword {

    static class PrefixInfo {
        int total_count;    // Количество слов с этим префиксом
        List<Integer> indices; // Индексы слов с этим префиксом

        PrefixInfo() {
            total_count = 0;
            indices = new ArrayList<>();
        }
    }

    public static List<String> linearCrossword(List<String> words) {
        if (words.isEmpty()) {
            return Collections.emptyList();
        }

        // 1. ИНДЕКСАЦИЯ ПРЕФИКСОВ
        Map<String, PrefixInfo> prefixMap = new HashMap<>();

        for (int idx = 0; idx < words.size(); idx++) {
            String word = words.get(idx);
            int L = word.length();
            if (L < 2) {
                System.out.println("Skipping word '" + word + "' (too short)");
                continue;
            }

            // Генерация всех возможных префиксов
            for (int k = 2; k <= L; k++) {
                String prefix = word.substring(0, k);
                prefixMap.computeIfAbsent(prefix, p -> new PrefixInfo())
                          .indices.add(idx);
                prefixMap.get(prefix).total_count++;
                System.out.println("Added prefix '" + prefix + "' for word '" + word + "' (index " + idx + ")");
            }
        }

        // 2. ПОСТРОЕНИЕ ЦЕПОЧКИ
        List<String> bestChain = new ArrayList<>();

        // Пробуем начать цепочку с каждого слова
        for (int startIdx = 0; startIdx < words.size(); startIdx++) {
            if (words.get(startIdx).length() < 2) continue;

            List<String> currentChain = new ArrayList<>();
            currentChain.add(words.get(startIdx));
            boolean[] used = new boolean[words.size()];
            used[startIdx] = true;

            System.out.println("\nTrying to build chain starting with '" + words.get(startIdx) + "'");

            // Продолжаем строить цепочку
            while (true) {
                String lastWord = currentChain.get(currentChain.size() - 1);
                int L = lastWord.length();
                boolean found = false;

                // Проверяем все возможные суффиксы
                for (int k = 2; k <= L; k++) {
                    String suffix = lastWord.substring(L - k);
                    System.out.println("Checking suffix '" + suffix + "' of word '" + lastWord + "'");

                    PrefixInfo info = prefixMap.get(suffix);
                    if (info != null) {
                        for (int idx : info.indices) {
                            if (!used[idx]) {
                                currentChain.add(words.get(idx));
                                used[idx] = true;
                                found = true;
                                System.out.println("Added word '" + words.get(idx) + "' to chain");
                                break;
                            }
                        }
                        if (found) break;
                    }
                }
                if (!found) {
                    System.out.println("No continuation found for word '" + lastWord + "'");
                    break;
                }
            }

            // Сохраняем самую длинную цепочку
            if (currentChain.size() >= 2 && currentChain.size() > bestChain.size()) {
                bestChain = new ArrayList<>(currentChain);
            }
        }

        return bestChain;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter words (empty line to finish):");
        
        List<String> words = new ArrayList<>();
        while (true) {
            String input = scanner.nextLine().trim();
            if (input.isEmpty()) break;
            words.add(input);
        }

        if (words.isEmpty()) {
            System.out.println("No words entered");
            return;
        }

        // Поиск цепочки
        List<String> result = linearCrossword(words);

        // Вывод результата
        if (!result.isEmpty()) {
            System.out.println("\nChain found: " + 
                result.stream().collect(Collectors.joining(" -> ")));
        } else {
            System.out.println("\nNo chain found");
        }
    }
}
