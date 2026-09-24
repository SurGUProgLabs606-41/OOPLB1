#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

int** allocateMatrix(int rows, int cols) {
    int** matrix = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[cols]{};
    }
    return matrix;
}

void fillMatrix(int** matrix, int rows, int cols) {
    std::cout << "Введите оценки (0..100) для " << rows
              << " студентов по " << cols << " предметам:\n";
    for (int i = 0; i < rows; ++i) {
        std::cout << "Студент #" << (i + 1) << ": ";
        for (int j = 0; j < cols; ++j) {
            while (true) {
                if (std::cin >> matrix[i][j]) {
                    if (matrix[i][j] >= 0 && matrix[i][j] <= 100) {
                        break;
                    }
                    std::cout << "Оценка должна быть в диапазоне 0..100. Повторите: ";
                } else {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Некорректный ввод. Повторите: ";
                }
            }
        }
    }
}

void printMatrix(int** matrix, int rows, int cols,
                 bool showBorders = true,
                 std::string title = "Matrix") {
    const int width = 6;

    if (showBorders) {
        std::string line(cols * width + 1, '-');
        std::cout << line << "\n";
    }

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

    for (int i = 0; i < rows; ++i) {
        if (showBorders) std::cout << "|";
        for (int j = 0; j < cols; ++j) {
            std::cout << std::setw(width - 1) << matrix[i][j];
            if (showBorders) std::cout << "|";
        }
        std::cout << "\n";
    }

    if (showBorders) {
        std::string line(cols * width + 1, '-');
        std::cout << line << "\n";
    }
    std::cout << "\n";
}

void freeMatrix(int** matrix, int rows) {
    if (matrix == nullptr) return;
    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

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

    int** grades = allocateMatrix(rows, cols);
    fillMatrix(grades, rows, cols);

    printMatrix(grades, rows, cols, true, "Оценки студентов");

    freeMatrix(grades, rows);
    grades = nullptr;

    return 0;
}