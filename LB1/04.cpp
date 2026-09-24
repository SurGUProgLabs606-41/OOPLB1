/**
 * @file 04.cpp
 * @brief Система учёта оценок студентов с использованием двумерного динамического массива.
 *
 * Программа демонстрирует:
 *  - выделение памяти под двумерный массив (массив указателей + вложенные массивы);
 *  - заполнение матрицы оценок с валидацией ввода;
 *  - красивый вывод матрицы с рамкой и заголовком;
 *  - корректное освобождение памяти в правильном порядке.
 */

#include <iostream>
#include <string> /// std::string - возможность вывести текст;
#include <iomanip> /// std::setw - ширина полей вывода;
#include <limits> /// std::numeric_limits - 

/**
 * @brief Выделяет память под двумерный массив размером rows x cols.
 *
 * Создаётся массив указателей `int*[rows]`, затем для каждой строки —
 * массив `int[cols]{}`, инициализированный нулями.
 *
 * @param rows Количество строк (студентов). Должно быть > 0.
 * @param cols Количество столбцов (предметов). Должно быть > 0.
 * @return Указатель на массив указателей (int**), владеющий выделенной памятью.
 *
 * @note Память должна быть освобождена вызовом freeMatrix().
 * @warning При rows <= 0 или cols <= 0 поведение не определено.
 */
int** allocateMatrix(int rows, int cols) {
    int** matrix = new int*[rows];              /// Массив указателей на строки
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[cols]{};            /// Каждая строка — массив из cols нулей
    }
    return matrix;
}

/**
 * @brief Заполняет матрицу оценками студентов с проверкой диапазона.
 *
 * Запрашивает у пользователя значения для каждой ячейки. Например
 * только числа в диапазоне [0; 100]. При некорректном вводе (не число
 * или выход за диапазон) поток std::cin очищается и запрос повторяется.
 *
 * @param matrix Указатель на двумерный массив (уже выделенный).
 * @param rows   Количество строк.
 * @param cols   Количество столбцов.
 *
 * @see allocateMatrix
 */
void fillMatrix(int** matrix, int rows, int cols) {
    std::cout << "Введите оценки (0..100) для " << rows
              << " студентов по " << cols << " предметам:\n";
    for (int i = 0; i < rows; ++i) {
        std::cout << "Студент #" << (i + 1) << ": ";
        for (int j = 0; j < cols; ++j) {
            while (true) {
                if (std::cin >> matrix[i][j]) {
                    if (matrix[i][j] >= 0 && matrix[i][j] <= 100) {
                        break;                      /// Корректная оценка — выход
                    }
                    std::cout << "Оценка должна быть в диапазоне 0..100. Повторите: ";
                } else {
                    std::cin.clear();               /// Сброс флаг ошибки
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); /// Метод потока очистки буфера
                    std::cout << "Некорректный ввод. Повторите: ";
                }
            }
        }
    }
}

/**
 * @brief Красиво выводит матрицу в консоль.
 *
 * Формирует таблицу с рамкой из символов `-` и `|` (если showBorders == true)
 * и заголовком по центру. Значения выравниваются по правому краю.
 *
 * @param matrix      Указатель на двумерный массив.
 * @param rows        Количество строк.
 * @param cols        Количество столбцов.
 * @param showBorders Рисовать ли рамку вокруг таблицы. По умолчанию true.
 * @param title       Заголовок над таблицей. По умолчанию "Matrix".
 *
 * @note Функция не изменяет данные матрицы.
 *
 * @code
 * printMatrix(grades, 3, 4);                            // всё по умолчанию
 * printMatrix(grades, 3, 4, true, "Оценки студентов");  // свой заголовок
 * @endcode
 */
void printMatrix(int** matrix, int rows, int cols,
                 bool showBorders = true,
                 std::string title = "Matrix") {
    const int width = 6; /// Ширина одной ячейки таблицы

    // Верхняя граница таблицы
    if (showBorders) {
        std::string line(cols * width + 1, '-');
        std::cout << line << "\n";
    }

    // Заголовок по центру
    if (!title.empty()) {
        int totalWidth = cols * width;
        int pad = (totalWidth - static_cast<int>(title.size())) / 2;
        if (pad < 0) pad = 0;
        std::cout << std::string(pad, ' ') << title << "\n";
        if (showBorders) {
            std::string line(cols * width + 1, '-');
            std::cout << line << "\n";
        }
    }

    // Тело таблицы
    for (int i = 0; i < rows; ++i) {
        if (showBorders) std::cout << "|";
        for (int j = 0; j < cols; ++j) {
            std::cout << std::setw(width - 1) << matrix[i][j];
            if (showBorders) std::cout << "|";
        }
        std::cout << "\n";
    }

    // Нижняя граница таблицы
    if (showBorders) {
        std::string line(cols * width + 1, '-');
        std::cout << line << "\n";
    }
    std::cout << "\n";
}

/**
 * @brief Корректно освобождает память, выделенную под двумерный массив.
 *
 * Порядок освобождения:
 *  1. Сначала удаляются все вложенные массивы (`delete[] matrix[i]`).
 *  2. Затем удаляется массив указателей (`delete[] matrix`).
 *
 * Такой порядок обязателен — иначе указатели на строки будут потеряны
 * и возникнет утечка памяти.
 *
 * @param matrix Указатель на двумерный массив. Может быть nullptr.
 * @param rows   Количество строк.
 */
void freeMatrix(int** matrix, int rows) {
    if (matrix == nullptr) return;       /// Защита от нулевого указателя
    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];              /// Сначала вложенные массивы
    }
    delete[] matrix;                     /// Потом массив указателей
}

/**
 * @brief Точка входа. Демонстрирует работу с матрицей оценок.
 *
 * Запрашивает размеры, создаёт матрицу, заполняет её, выводит
 * с заголовком "Оценки студентов" и освобождает память.
 *
 * @return 0 — успешное завершение.
 */
int main() {
    int rows, cols;
    std::cout << "Введите количество студентов (rows): ";
    std::cin >> rows;
    std::cout << "Введите количество предметов (cols): ";
    std::cin >> cols;

    if (rows <= 0 || cols <= 0) {
        std::cout << "Размеры должны быть положительными.\n";
        return 0;
    }

    int** grades = allocateMatrix(rows, cols);   /// Выделение памяти
    fillMatrix(grades, rows, cols);              /// Ввод оценок

    printMatrix(grades, rows, cols, true, "Оценки студентов"); /// Вывод таблицы

    freeMatrix(grades, rows);                    /// Освобождение памяти
    grades = nullptr;                            /// Защита от «болтающегося» указателя

    return 0;
}