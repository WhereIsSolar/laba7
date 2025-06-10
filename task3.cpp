#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

// Структура для хранения информации о префиксах
struct PrefixInfo {
    int total_count;    // Количество слов, начинающихся с этого префикса
    vector<int> indices; // Индексы слов с этим префиксом
};

// Рекурсивная функция для построения цепочки слов
void buildChain(const vector<string>& words, 
               const unordered_map<string, PrefixInfo>& prefixMap, 
               vector<string>& current_chain, 
               vector<bool>& used, 
               vector<string>& best_chain) {
    string last_word = current_chain.back(); // Последнее слово в текущей цепочке
    int L = last_word.length(); // Длина последнего слова
    bool found = false; // Флаг, найдено ли продолжение цепочки

    // Проверяем все возможные суффиксы последнего слова
    for (int k = 2; k <= L; k++) {
        string suffix = last_word.substr(L - k, k); // Извлекаем суффикс длиной k
        cout << "Проверка суффикса '" << suffix << "' слова '" << last_word << "'" << endl;

        auto it = prefixMap.find(suffix); // Ищем суффикс среди префиксов
        if (it != prefixMap.end()) {
            // Проверяем все слова с подходящим префиксом
            for (int idx : it->second.indices) {
                if (!used[idx]) { // Если слово ещё не использовано
                    // Добавляем слово в цепочку
                    current_chain.push_back(words[idx]);
                    used[idx] = true; // Отмечаем слово как использованное
                    found = true;
                    cout << "Добавлено слово '" << words[idx] << "' в цепочку" << endl;

                    // Рекурсивно продолжаем строить цепочку
                    buildChain(words, prefixMap, current_chain, used, best_chain);

                    // Откат (backtracking): убираем слово и снимаем отметку
                    current_chain.pop_back();
                    used[idx] = false;
                }
            }
        }
    }

    if (!found) {
        cout << "Продолжение для слова '" << last_word << "' не найдено" << endl;
    }

    // Обновляем лучшую цепочку, если текущая длиннее и содержит хотя бы 2 слова
    if (current_chain.size() >= 2 && current_chain.size() > best_chain.size()) {
        best_chain = current_chain;
    }
}

// Основная функция для построения линейного кроссворда
vector<string> linearCrossword(const vector<string>& words) {
    if (words.empty()) {
        return {}; // Нельзя построить цепочку без слов
    }

    // 1. ИНДЕКСАЦИЯ ПРЕФИКСОВ
    unordered_map<string, PrefixInfo> prefixMap; // Словарь для хранения префиксов

    for (int idx = 0; idx < words.size(); idx++) {
        string word = words[idx]; // Текущее слово
        int L = word.length(); // Длина слова
        if (L < 2) {
            cout << "Пропуск слова '" << word << "' (слишком короткое)" << endl;
            continue;
        }

        // Генерируем все возможные префиксы для текущего слова
        for (int k = 2; k <= L; k++) {
            string prefix = word.substr(0, k); // Извлекаем префикс длиной k
            prefixMap[prefix].total_count++; // Увеличиваем счётчик префикса
            prefixMap[prefix].indices.push_back(idx); // Добавляем индекс слова
            cout << "Добавлен префикс '" << prefix << "' для слова '" << word << "' (индекс " << idx << ")" << endl;
        }
    }

    // 2. ПОСТРОЕНИЕ ЦЕПОЧКИ
    vector<string> best_chain; // Хранит самую длинную цепочку

    // Пробуем начать цепочку с каждого слова
    for (int start_idx = 0; start_idx < words.size(); start_idx++) {
        if (words[start_idx].length() < 2) continue; // Пропускаем короткие слова

        vector<string> current_chain = {words[start_idx]}; // Начинаем цепочку с текущего слова
        vector<bool> used(words.size(), false); // Массив для отслеживания использованных слов
        used[start_idx] = true; // Отмечаем начальное слово как использованное

        cout << "\nПопытка построить цепочку, начиная со слова '" << words[start_idx] << "'" << endl;

        // Строим цепочку рекурсивно
        buildChain(words, prefixMap, current_chain, used, best_chain);
    }

    return best_chain; // Возвращаем самую длинную найденную цепочку
}

// Основная программа
int main() {
    cout << "Введите слова (пустая строка для завершения):" << endl;

    vector<string> words; // Вектор для хранения слов
    string input; // Переменная для ввода строки

    // Ввод слов с клавиатуры
    while (true) {
        getline(cin, input);
        if (input.empty()) break;
        words.push_back(input); // Добавляем слово в вектор
    }

    if (words.empty()) {
        cout << "Слова не введены" << endl;
        return 0;
    }

    // Поиск цепочки
    vector<string> result = linearCrossword(words);

    // Вывод результата
    if (!result.empty()) {
        cout << "\nЦепочка найдена: ";
        for (size_t i = 0; i < result.size(); i++) {
            cout << result[i];
            if (i < result.size() - 1) cout << " -> ";
        }
        cout << endl;
    } else {
        cout << "\nЦепочка не найдена" << endl;
    }

    return 0;
}
