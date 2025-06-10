import java.util.*;
import java.util.stream.Collectors;

class PrefixInfo {
    int total_count;
    List<Integer> indices;

    PrefixInfo() {
        this.total_count = 0;
        this.indices = new ArrayList<>();
    }
}

public class Main {
    
    private static void buildChain(List<String> words,
                                  Map<String, PrefixInfo> prefixMap,
                                  List<String> current_chain,
                                  boolean[] used,
                                  List<String> best_chain) {
        String last_word = current_chain.get(current_chain.size() - 1);
        int L = last_word.length();
        boolean found = false;

        for (int k = 2; k <= L; k++) {
            String suffix = last_word.substring(L - k, L);
            System.out.println("Проверка суффикса '" + suffix + "' слова '" + last_word + "'");

            if (prefixMap.containsKey(suffix)) {
                PrefixInfo info = prefixMap.get(suffix);
                for (int idx : info.indices) {
                    if (!used[idx]) {
                        current_chain.add(words.get(idx));
                        used[idx] = true;
                        found = true;
                        System.out.println("Добавлено слово '" + words.get(idx) + "' в цепочку");

                        buildChain(words, prefixMap, current_chain, used, best_chain);

                        current_chain.remove(current_chain.size() - 1);
                        used[idx] = false;
                    }
                }
            }
        }

        if (!found) {
            System.out.println("Продолжение для слова '" + last_word + "' не найдено");
        }

        if (current_chain.size() >= 2 && current_chain.size() > best_chain.size()) {
            best_chain.clear();
            best_chain.addAll(current_chain);
        }
    }

    public static List<String> linearCrossword(List<String> words) {
        if (words.isEmpty()) {
            return new ArrayList<>();
        }

        // Создаем карту префиксов
        Map<String, PrefixInfo> prefixMap = new HashMap<>();

        for (int idx = 0; idx < words.size(); idx++) {
            String word = words.get(idx);
            int L = word.length();
            
            if (L < 2) {
                System.out.println("Пропуск слова '" + word + "' (слишком короткое)");
                continue;
            }

            for (int k = 2; k <= L; k++) {
                String prefix = word.substring(0, k);
                prefixMap.computeIfAbsent(prefix, k1 -> new PrefixInfo());
                PrefixInfo info = prefixMap.get(prefix);
                info.total_count++;
                info.indices.add(idx);
                System.out.println("Добавлен префикс '" + prefix + "' для слова '" + word + "' (индекс " + idx + ")");
            }
        }

        List<String> best_chain = new ArrayList<>();

        for (int start_idx = 0; start_idx < words.size(); start_idx++) {
            String startWord = words.get(start_idx);
            if (startWord.length() < 2) continue;

            List<String> current_chain = new ArrayList<>();
            current_chain.add(startWord);
            
            boolean[] used = new boolean[words.size()];
            used[start_idx] = true;
            
            System.out.println("\nПопытка построить цепочку, начиная со слова '" + startWord + "'");

            buildChain(words, prefixMap, current_chain, used, best_chain);
        }

        return best_chain;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        List<String> words = new ArrayList<>();
        
        System.out.println("Введите слова (пустая строка для завершения):");
        while (true) {
            String input = scanner.nextLine().trim();
            if (input.isEmpty()) {
                break;
            }
            words.add(input);
        }

        if (words.isEmpty()) {
            System.out.println("Слова не введены");
            return;
        }

        List<String> result = linearCrossword(words);

        if (!result.isEmpty()) {
            System.out.println("\nЦепочка найдена: " + 
                result.stream().collect(Collectors.joining(" -> ")));
        } else {
            System.out.println("\nЦепочка не найдена");
        }
    }
}
