#include <raylib.h>
#include <iostream>

using namespace std;

// Рекурсивная функция для построения множества Кантора
void drawCantorSet(float x, float y, float length, int depth, int maxDepth) {
    if (depth > maxDepth) {
        cout << "Достигнута максимальная глубина рекурсии: " << depth << endl;
        return;
    }

    // Отрисовываем текущий отрезок
    DrawLine(x, y, x + length, y, WHITE);
    cout << "Отрисован отрезок: x=" << x << ", y=" << y << ", длина=" << length << ", уровень=" << depth << endl;

    // Рекурсивно рисуем левую и правую трети
    float newLength = length / 3.0f;
    drawCantorSet(x, y + 50, newLength, depth + 1, maxDepth); // Левый 
    drawCantorSet(x + 2 * newLength, y + 50, newLength, depth + 1, maxDepth); // Правый 
}

int main() {
    cout << "Запуск программы для построения множества Кантора" << endl;

    // Инициализация окна
    InitWindow(800, 600, "Множество Кантора");
    if (!IsWindowReady()) {
        cerr << "Ошибка: Не удалось создать окно" << endl;
        return 1;
    }
    SetTargetFPS(60);
    cout << "Окно создано: 800x600 пикселей" << endl;
    
    int maxDepth; // Максимальная глубина рекурсии
    cout << "Введите макс. глубину рекурсии" << endl;
    cin >> maxDepth;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        // Рисуем множество Кантора
        drawCantorSet(50, 50, 700, 0, maxDepth);

        EndDrawing();
    }

    CloseWindow();
    cout << "Программа завершена" << endl;
    return 0;
}
